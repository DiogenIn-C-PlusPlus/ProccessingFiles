#pragma once

#include <fstream>
//#include <filesystem>
#include <string>
#include <string_view>
#include <vector>
#include <set>
#include <deque>
#include <sstream>
#include <memory>
#include <iostream>


namespace file
{

struct FormatFileMof
{
    std::string trace;
    std::string data;
    std::string time;
    double hours;
    size_t seconds;
    std::string unknown_data;
    double max_objective_freq;
    std::string unknown_data_sec;
    double time_delay;
};

struct FormatFilePrognosticRadioRouteAustralia // Изменить название добавить у частоты обыкновенную и необыкновенную
{
    double time;
    double time_persent;
    double freq_persent_mof;
    double amplitude_1;
    double amplitude_2;
    double amplitude_3;
    double amplitude_4;
    double amplitude_5;
    double amplitude_6;
    double freq;
    double unknow_time;
    size_t count_hops;
    double freq_hop_1;
    double freq_hop_2;
    double freq_hop_3;
    double freq_hop_4;
    double freq_hop_5;
    double freq_hop_6;
    double freq_hop_7;
    double freq_hop_8;
    double freq_hop_9;
    double freq_hop_10;
    double freq_hop_11;
    double freq_hop_12;
    double freq_hop_13;
    double freq_hop_14;
    double freq_hop_15;
    double freq_hop_16;
    double freq_hop_17;
    double freq_hop_18;
    double freq_hop_19;
    double freq_hop_20;
    double max_freq_hop;
    double freq_hop_22;
    double freq_hop_23;
    double unknow_data;
};

struct FormatFilePrognosticRadioRouteCyprus
{
    double time;
    double time_persent;
    double freq_persent_mof;
    double amplitude_1;
    double amplitude_2;
    double amplitude_3;
    double amplitude_4;
    double amplitude_5;
    double amplitude_6;
    double freq;
    double unknow_time;
    size_t count_hops;
    double freq_hop_1;
    double freq_hop_2;
    double freq_hop_3;
    double freq_hop_4;
    double max_freq_hop;
    double freq_hop_5;
    double freq_hop_6;
    double unknow_data;
};

class ReadFile
{
public:
    ReadFile() = default; // Тестовая версия (боевая delete)
    explicit ReadFile(const std::string& name_file);
    explicit ReadFile(const std::vector<std::string>& name_files);

    void ReadMof();
    void ReadFileFreqAustralia();
    void ReadFileFreqCyprus();
    const std::unique_ptr<std::deque<FormatFileMof>> GetReadMof() const;
    const std::unique_ptr<std::vector<std::vector<FormatFilePrognosticRadioRouteAustralia>>> GetReadPrognosticFreqAustralia() const;
    const std::unique_ptr<std::vector<std::vector<FormatFilePrognosticRadioRouteCyprus>>> GetReadPrognosticFreqCyprus() const;

    void AddFile(std::string_view name_file);
    void SumFiles(const std::string& result_file, const std::string& add_file);
    void CutRowsInFile(const std::string& path_to_file, size_t count_rows) const;
    void TakeFilesFromDirectory(const std::string& path);

private: // тестировочный режим in comment
    std::vector<FormatFilePrognosticRadioRouteAustralia> ReadPrognosticFreqAustralia(const std::string& file_name);
    void TranslateSymbolToZero(std::string& line);
    std::vector<FormatFilePrognosticRadioRouteCyprus> ReadPrognosticFreqCyprus(const std::string& file_name);
    std::set<std::string> files_;
    std::string name_trace_; // На перспективу
    std::string name_file_;
    std::deque<FormatFileMof> file_mof_;
    std::vector<std::vector<FormatFilePrognosticRadioRouteAustralia>> file_prognostic_freq_australia;
    std::vector<std::vector<FormatFilePrognosticRadioRouteCyprus>> file_prognostic_freq_cyprus;
};
}
