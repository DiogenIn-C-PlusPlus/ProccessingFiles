#include "readfile.h"

using namespace file;


ReadFile::ReadFile(const std::string& name_file)
    : name_file_(name_file)
{}

ReadFile::ReadFile(const std::vector<std::string>& name_files)
{
    for(const std::string& name_file : name_files)
    {
        files_.insert(name_file);
    }
}

void ReadFile::SumFiles(const std::string& result_file, const std::string& add_file)
{
    std::ofstream out(result_file, std::ios::app | std::ios::out);
    std::ifstream add_fil(add_file, std::ios::in);
    while(!add_fil.eof())
    {
        std::string line;
        std::getline(add_fil, line);
        out << line << std::endl;
    }
    out.close();
    add_fil.close();
}

const std::unique_ptr<std::deque<FormatFileMof>> ReadFile::GetReadMof() const
{
    return std::make_unique<std::deque<FormatFileMof>>(file_mof_);
}

void ReadFile::AddFile(std::string_view name_file)
{
    files_.insert(static_cast<std::string>(name_file));
}

void ReadFile::ReadMof()
{
    std::ifstream in(name_file_, std::ios::in);
    if(!in.is_open())
    {
        std::cerr << "File not open -> adress readfile -> function Read()" << std::endl;
        throw std::invalid_argument("Not right pass file or file is not exist or not avaible maybe not have rule for reading");
    }
    while(!in.eof())
    {
        std::string line;
        std::getline(in, line);
        FormatFileMof temp;
        std::istringstream iss(line);
        iss >> temp.trace >> temp.data >> temp.time >> temp.hours >> temp.seconds >> temp.unknown_data >> temp.max_objective_freq >> temp.unknown_data_sec >> temp.time_delay;
        file_mof_.push_back(std::move(temp));
    }
    in.close();
}

void ReadFile::TakeFilesFromDirectory(const std::string& path)
{
    for(const auto& file : std::filesystem::directory_iterator(path))
    {
      files_.insert(file.path().string());
    }
}

void ReadFile::CutRowsInFile(const std::string &path_to_file, size_t count_rows) const
{

}

void TranslateSymbolToZero(std::string& line)
{
  for(char& c : line)
    {
      if(c == 'n')
        {
          c = 48;
        }
    }
}

std::vector<FormatFilePrognosticRadioRouteAustralia> ReadFile::ReadPrognosticFreqAustralia(const std::string& name_file)
{
  std::vector<FormatFilePrognosticRadioRouteAustralia> result;
  std::ifstream in(name_file, std::ios::in);
  if(!in.is_open())
  {
      std::cerr << "File not open -> adress readfile -> function Read()" << std::endl;
      throw std::invalid_argument("Not right pass file or file is not exist or not avaible maybe not have rule for reading");
  }
  while(!in.eof())
  {
      std::string line;
      std::getline(in, line);
      if(line.empty())
        {
          continue;
        }
      TranslateSymbolToZero(line);
      FormatFilePrognosticRadioRouteAustralia temp;
      std::istringstream iss(line);
      iss >> temp.time >> temp.time_persent >> temp.freq_persent_mof >> temp.amplitude_1 >> temp.amplitude_2 >> temp.amplitude_3 >> temp.amplitude_4 >> temp.amplitude_5 >> temp.amplitude_6;
      iss >> temp.freq >> temp.unknow_time >> temp.count_hops;
      iss >>  temp.freq_hop_1 >> temp.freq_hop_2 >> temp.freq_hop_3 >> temp.freq_hop_4 >> temp.freq_hop_5 >> temp.freq_hop_6 >> temp.freq_hop_7 >> temp.freq_hop_8 >> temp.freq_hop_9;
      iss >> temp.freq_hop_10 >> temp.freq_hop_11 >> temp.freq_hop_12 >> temp.freq_hop_13 >> temp.freq_hop_14 >> temp.freq_hop_15 >> temp.freq_hop_16 >> temp.freq_hop_17 >> temp.freq_hop_18;
      iss >> temp.freq_hop_19 >> temp.freq_hop_20 >> temp.max_freq_hop >> temp.freq_hop_22 >> temp.freq_hop_23 >> temp.unknow_data;
      result.push_back(std::move(temp));
  }
  in.close();
  return result;
}

void ReadFile::ReadFileFreqAustralia()
{
    if(files_.empty())
      {
        file_prognostic_freq_australia.push_back(ReadPrognosticFreqAustralia(name_file_));
      }
    else
      {
        for(const std::string& name_file : files_)
          {
              file_prognostic_freq_australia.push_back(ReadPrognosticFreqAustralia(name_file));
          }
      }
}

const std::unique_ptr<std::vector<std::vector<FormatFilePrognosticRadioRouteAustralia>>> ReadFile::GetReadPrognosticFreqAustralia() const
{
    return std::make_unique<std::vector<std::vector<FormatFilePrognosticRadioRouteAustralia>>>(file_prognostic_freq_australia);
}

const std::unique_ptr<std::vector<std::vector<FormatFilePrognosticRadioRouteCyprus>>> ReadFile::GetReadPrognosticFreqCyprus() const
{
  return std::make_unique<std::vector<std::vector<FormatFilePrognosticRadioRouteCyprus>>>(file_prognostic_freq_cyprus);
}

std::vector<FormatFilePrognosticRadioRouteCyprus> ReadFile::ReadPrognosticFreqCyprus(const std::string& name_file)
{
  std::vector<FormatFilePrognosticRadioRouteCyprus> result;
  std::ifstream in(name_file, std::ios::in);
  if(!in.is_open())
  {
      std::cerr << "File not open -> adress readfile -> function Read()" << std::endl;
      throw std::invalid_argument("Not right pass file or file is not exist or not avaible maybe not have rule for reading");
  }
  while(!in.eof())
  {
      std::string line;
      std::getline(in, line);
      if(line.empty())
        {
          continue;
        }
      FormatFilePrognosticRadioRouteCyprus temp;
      std::istringstream iss(line);
      iss >> temp.time >> temp.time_persent >> temp.freq_persent_mof >> temp.amplitude_1 >> temp.amplitude_2 >> temp.amplitude_3 >> temp.amplitude_4 >> temp.amplitude_5 >> temp.amplitude_6;
      iss >> temp.freq >> temp.unknow_time >> temp.count_hops;
      iss >>  temp.freq_hop_1 >> temp.freq_hop_2 >> temp.freq_hop_3 >> temp.freq_hop_4 >> temp.max_freq_hop >> temp.freq_hop_5 >> temp.freq_hop_6 >> temp.unknow_data;
      result.push_back(std::move(temp));
  }
  in.close();
  return result;
}

void ReadFile::ReadFileFreqCyprus()
{
  if(files_.empty())
    {
      file_prognostic_freq_cyprus.push_back(ReadPrognosticFreqCyprus(name_file_));
    }
  else
    {
      for(const std::string& name_file : files_)
        {
            file_prognostic_freq_cyprus.push_back(ReadPrognosticFreqCyprus(name_file));
        }
    }
}
