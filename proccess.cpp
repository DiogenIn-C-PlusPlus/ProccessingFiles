#include "proccess.h"
#include <iomanip>
#include <cmath>

using namespace file;

Proccess::Proccess(std::unique_ptr<std::deque<FormatFileMof>> file_mof, uint16_t time_window)
    :file_mof_(std::move(file_mof)),time_window_(time_window)
{}

Proccess::Proccess(std::unique_ptr< std::vector<std::vector<FormatFilePrognosticRadioRouteAustralia>>> file_prognostic_route, size_t steps_mof, uint16_t detla_amplitude)
  :file_prognostic_route_australia_(std::move(file_prognostic_route)), steps_mof_(steps_mof), detla_amplitude_(detla_amplitude)
{}

Proccess::Proccess(std::unique_ptr<std::vector<std::vector<FormatFilePrognosticRadioRouteCyprus>>> file_prognostic_freq, size_t steps_mof, uint16_t delta_amplitude)
  : file_prognostic_route_cyprus_(std::move(file_prognostic_freq)), steps_mof_(steps_mof), detla_amplitude_(delta_amplitude)
{}

double Proccess::MiddleValue(const std::vector<double>& vec) const
{
    return vec.empty() ? 0 : std::accumulate(vec.begin(), vec.end(), 0.0) / vec.size();
}

void Proccess::TakeInfoTimeAndMof()
{
    for(const auto& element : *file_mof_)
    {
        size_t time_key = (element.seconds / time_window_);
        mof_.time_per_sec_and_mof_[time_key].push_back(element.max_objective_freq);
    }
}

uint32_t Proccess::ChangeMoscowTimeToUtInSeconds(uint32_t time_moscow)
{
    uint32_t delta = 3 * 3600;
     if(time_moscow < delta)
    {
        return time_day_in_second - time_moscow;
    }
  return time_moscow - delta;
}

void Proccess::ComputeTimeAndMiddleMof()
{
    for(const auto& [time_window, array_mor] : mof_.time_per_sec_and_mof_)
    {
        mof_.time_and_middle_mof_[time_window] = MiddleValue(array_mor);
    }
}

double Proccess::ComputeDispersion(const std::vector<double>& values, double middle_value) const
{
    if(values.empty() || values.size() == 1)
    {
        return 0;
    }
   return (std::accumulate(values.begin(), values.end(), 0.0, [middle_value](double& result, double temp)
             {
                return result += ((temp - middle_value) * (temp - middle_value));
             })) / (values.size() - 1);
}

void Proccess::ComputeTimeAndDispersionAndStandartDeviashionMof()
{
    for(const auto& [time_window, array_mof] : mof_.time_per_sec_and_mof_)
    {
           auto middle_value = mof_.time_and_middle_mof_[time_window];
           mof_.time_and_dispersion_[time_window] = ComputeDispersion(array_mof, middle_value);
           mof_.time_and_standart_deviashion_[time_window] = ComputeStandartDeviation(ComputeDispersion(array_mof, middle_value));
    }
}

const std::unique_ptr<DataMof> Proccess::GetDataMof() const
{
    return std::make_unique<DataMof>(mof_);
}

void Proccess::SetTimeWindow(uint16_t time_per_second)
{
    time_window_ = time_per_second;
}

uint16_t Proccess::GetTimeWindow() const
{
    return time_window_;
}

double Proccess::ComputeStandartDeviation(double dispersion) const
{
    return dispersion < 0 ? 0 : sqrt(dispersion);
}

double Proccess::ChangeMoscowTimeToUtInHours(double time_moscow)
{
    int16_t delta = 3;
    int16_t hours_in_day = 24;
    if((hours_in_day - delta) > time_moscow)
    {
        return time_moscow + delta;
    }
    return time_moscow + delta - hours_in_day;
}

double Proccess::TransformTimeFromSeconds(double time_in_sec, double size_time_window)
{
    return time_in_sec *  size_time_window / time_in_hour;
}

const std::shared_ptr<DataPrognosticFreq> Proccess::GetDataPrognosticFreq() const
{
    return std::make_shared<DataPrognosticFreq>(prognostic_freq_);
}

void Proccess::TakeInfoTimeAndFreqPrognosticRouteAustralia() // Доделать исходя из посчитанного файла дома
{
    for(const auto& one_day : *file_prognostic_route_australia_)
    {
        std::vector<double> amplitude_per_step;
        size_t iterator = 0;
        for(const auto& element : one_day)
          {
            if(std::abs(element.amplitude_3 - 0) > 1e-3)
              {
                 amplitude_per_step.push_back(element.amplitude_3);
              }
            ++iterator;
              if(iterator == steps_mof_)
                {
                  std::sort(amplitude_per_step.begin(), amplitude_per_step.end());
                  if(!amplitude_per_step.empty())
                    {
                      std::vector<double> temp;
                      for(const double el : amplitude_per_step)
                        {
                          if(std::abs(amplitude_per_step.back() - el) < detla_amplitude_)
                            {
                              temp.push_back(el);
                            }
                        }
                      if(!temp.empty())
                        {
                           prognostic_freq_.time_amplitude_in_files[element.time_persent * coeff_for_double_time_to_int] = temp;
                        }
                    }
                  prognostic_freq_.time_freq[element.time_persent * coeff_for_double_time_to_int].push_back(element.max_freq_hop);
                  amplitude_per_step.clear();
                  iterator = 0;
                }
          }
    }
}

void Proccess::TakeInfoTimeAndFreqPrognosticRouteCyprus()
{
  for(const auto& one_day : *file_prognostic_route_cyprus_)
  {
      std::vector<double> amplitude_per_step;
      size_t iterator = 0;
      for(const auto& element : one_day)
        {
          if(std::abs(element.amplitude_3 - 0) > 1e-3)
            {
               amplitude_per_step.push_back(element.amplitude_3);
            }
          ++iterator;
            if(iterator == steps_mof_)
              {
                std::sort(amplitude_per_step.begin(), amplitude_per_step.end());
                if(!amplitude_per_step.empty())
                  {
                    std::vector<double> temp;
                    for(const double el : amplitude_per_step)
                      {
                        if(std::abs(amplitude_per_step.back() - el) < detla_amplitude_)
                          {
                            temp.push_back(el);
                          }
                      }
                    if(!temp.empty())
                      {
                         prognostic_freq_.time_amplitude_in_files[element.time_persent * coeff_for_double_time_to_int] = temp;
                      }
                  }
                prognostic_freq_.time_freq[element.time_persent * coeff_for_double_time_to_int].push_back(element.max_freq_hop);
                amplitude_per_step.clear();
                iterator = 0;
              }
        }
  }
}

std::deque<TimeFreq> Proccess::ComputeMiddlePrognosticMof()
{
    std::deque<TimeFreq> result;
    for(const auto& [time, day_mof] : prognostic_freq_.time_freq)
      {
        result.push_back(TimeFreq{(static_cast<double>(time) / coeff_for_double_time_to_int), MiddleValue(day_mof)});
      }
    return result;
}
