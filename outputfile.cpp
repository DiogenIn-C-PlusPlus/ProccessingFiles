#include "outputfile.h"

using namespace file;

OutPutFile::OutPutFile(std::unique_ptr<DataMof> data)
    : data_mof_(std::move(data))
{}

OutPutFile::OutPutFile(std::shared_ptr<DataPrognosticFreq> data_prognostic)
    : data_prognostic_freq_(std::move(data_prognostic))
{}

void OutPutFile::CalculateCountDataInWindowTime()
{
    for(const auto& element : data_mof_->time_per_sec_and_mof_)
    {
       count_points_in_time_window_.push_back(element.second.size());
    }
}

void OutPutFile::PrintCountDataInWindowTime()
{
    CalculateCountDataInWindowTime();
    uint16_t count_numbers_in_row = 0;
    for(const uint16_t element : count_points_in_time_window_)
    {
        std::cout << element << " ";
        if(count_numbers_in_row == 20)
        {
            std::cout << std::endl;
            count_numbers_in_row = 0;
        }
        ++count_numbers_in_row;
    }
}

void OutPutFile::ShowMinimumsColomsDataMof(uint16_t count_minimums)
{
    CalculateCountDataInWindowTime();
    std::sort(count_points_in_time_window_.begin(), count_points_in_time_window_.end());
    for(size_t i = 0, j = 0; i < count_minimums; ++i, ++j)
    {
        if(j == 10)
        {
            std::cout << std::endl;
            j = 0;
        }
        std::cout << count_points_in_time_window_[i] << " ";
    }
}

void OutPutFile::PrintFileMof(std::string name_file, double size_time_window)
{
    std::ofstream output(name_file);
    bool title = true;
    std::ostringstream last_row;
    for(const auto& [time, middle_mof] : data_mof_->time_and_middle_mof_)
    {
        if(title)
        {
            title = false;
            output << "\t| Time |" << "\t| Middle mof |" << "\t| Middl - Stand def |" << "\t| Middl + Stand def |" << std::endl;
            output << "\t " <<  std::setw(5) << Proccess::ChangeMoscowTimeToUtInHours(Proccess::TransformTimeFromSeconds(time, size_time_window))  << "\t\t" << std::setw(10) << middle_mof / coeff_for_double_time_to_int<< "\t   " <<  std::setw(10) << (data_mof_->time_and_middle_mof_[time] - data_mof_->time_and_standart_deviashion_[time]) / coeff_for_double_time_to_int << "\t\t   ";
            output << std::setw(10) << (data_mof_->time_and_middle_mof_[time] + data_mof_->time_and_standart_deviashion_[time]) / coeff_for_double_time_to_int << std::endl;
            continue;
        }
        if(time == 0)
        {
            size_t last_hour = 24;
            last_row << "\t " <<  std::setw(5) << last_hour  << "\t\t" << std::setw(10) << middle_mof / coeff_for_double_time_to_int << "\t   " <<  std::setw(10) << (data_mof_->time_and_middle_mof_[time] - data_mof_->time_and_standart_deviashion_[time]) / coeff_for_double_time_to_int << "\t\t   ";
            last_row << std::setw(10) << (data_mof_->time_and_middle_mof_[time] + data_mof_->time_and_standart_deviashion_[time]) / coeff_for_double_time_to_int << '\n';
        }
        output << "\t " <<  std::setw(5) << Proccess::ChangeMoscowTimeToUtInHours(Proccess::TransformTimeFromSeconds(time, size_time_window))  << "\t\t" << std::setw(10) << middle_mof / coeff_for_double_time_to_int << "\t   " <<  std::setw(10) << (data_mof_->time_and_middle_mof_[time] - data_mof_->time_and_standart_deviashion_[time]) / coeff_for_double_time_to_int << "\t\t   ";
        output << std::setw(10) << (data_mof_->time_and_middle_mof_[time] + data_mof_->time_and_standart_deviashion_[time]) / coeff_for_double_time_to_int << '\n';
    }
    output << last_row.str();
}

void OutPutFile::PrintFilePrognosticFreq(std::string name_file, const std::deque<TimeFreq>& print_data)
{
   std::ofstream output(name_file);
   bool title = true;
    for(const auto& element : print_data)
    {
        if(title)
        {
            title = false;
            output << "\t| Time |" << "\t| Frequency |" << std::endl;
        }
       output << "\t " <<  std::setw(5) << element.time  << "\t\t" << std::setw(10) << element.freq << '\n';
    }
}

void OutPutFile::PrintFilePrognosticFreqAmplitude(std::string name_file) // Доработать на будущее возможность выводить несколько дней
{
  std::ofstream output(name_file);
  bool title = true;
   for(const auto& [time, vec_days] : data_prognostic_freq_->time_amplitude_in_files)
   {
       if(title)
       {
           title = false;
           output << "| Time |" << "\t\t\t| Amplitude |"  << std::endl;
       }
       output << static_cast<double>(time) / coeff_for_double_time_to_int;
       for(const double value : vec_days)
         {
              output << "\t" << std::setw(10) << value;
         }
       output  << '\n';
   }
}
