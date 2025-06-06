#pragma once

#include "readfile.h"
#include <unordered_map>
#include <numeric>
#include <forward_list>
#include <iomanip>
#include <map>
// maximum_objective_frequency == mof

namespace file
{
inline const size_t time_day_in_second = 24 * 3600;
inline const size_t time_in_hour = 3600;
inline const size_t coeff_for_double_time_to_int = 1000;

struct DataMof
{
    std::map<size_t, double> time_and_dispersion_;
    std::map<size_t, double> time_and_middle_mof_;
    std::map<size_t, double> time_and_standart_deviashion_;
    std::map<size_t, std::vector<double>> time_per_sec_and_mof_;
};

struct DataPrognosticFreq
{
    std::map<size_t, std::vector<double>> time_freq;
    std::map<size_t, std::vector<double>> time_amplitude_in_files;
};

struct TimeFreq
{
    TimeFreq() = default;
    explicit TimeFreq(double time_, double freq_)
    :time(time_), freq(freq_)
  {}
    double time;
    double freq;
};

class Proccess
{
public:
    Proccess() = default; // Тестовая версия (боевая delete)
    explicit Proccess(std::unique_ptr<std::deque<FormatFileMof>> file_mof, uint16_t time_window);
    explicit Proccess(std::unique_ptr<std::vector<std::vector<FormatFilePrognosticRadioRouteAustralia>>> file_prognostic_freq, size_t steps_mof, uint16_t detla_amplitude);
    explicit Proccess(std::unique_ptr<std::vector<std::vector<FormatFilePrognosticRadioRouteCyprus>>> file_prognostic_freq, size_t steps_mof, uint16_t delta_amplitude);

    uint32_t ChangeMoscowTimeToUtInSeconds(uint32_t time_moscow);
    double ChangeMoscowTimeToUtInHours(double time_moscow);
    void SetTimeWindow(uint16_t time_per_second);
    uint16_t GetTimeWindow() const;
    std::vector<uint32_t> SearchObjectInFileFormatTxt(std::string object); // Реализовать (не понятно, что искать) число или строку, скорее всего число
    double TransformTimeFromSeconds(double time_in_sec, double size_time_window);
    // Mof
    void ComputeTimeAndMiddleMof();
    void TakeInfoTimeAndMof();
    void ComputeTimeAndDispersionAndStandartDeviashionMof();
    const std::unique_ptr<DataMof> GetDataMof() const;
    // PrognosticFreq
    void TakeInfoTimeAndFreqPrognosticRouteAustralia(); // Может брать амплитуду только одного дня
    void TakeInfoTimeAndFreqPrognosticRouteCyprus(); // Аналогично
    std::deque<TimeFreq> ComputeMiddlePrognosticMof();
    const std::shared_ptr<DataPrognosticFreq> GetDataPrognosticFreq() const;

private: // тестировочный режим in comment
    DataMof mof_;
    DataPrognosticFreq prognostic_freq_;
    double MiddleValue(const std::vector<double>& vec) const;
    double ComputeDispersion(const std::vector<double>& values, double middle_value) const;
    double ComputeStandartDeviation(double dispersion) const;
    std::unique_ptr<std::deque<FormatFileMof>> file_mof_;
    std::unique_ptr<std::vector<std::vector<FormatFilePrognosticRadioRouteAustralia>>> file_prognostic_route_australia_;
    std::unique_ptr<std::vector<std::vector<FormatFilePrognosticRadioRouteCyprus>>> file_prognostic_route_cyprus_;
    uint16_t time_window_;
    size_t steps_mof_ = 4;
    uint16_t detla_amplitude_ =  30;
};

}
