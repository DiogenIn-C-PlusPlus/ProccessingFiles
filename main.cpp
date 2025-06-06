#include <iostream>
#include <cassert>
#include <cmath>
#include <cstdint>

#include "readfile.h"
#include "proccess.h"
#include "outputfile.h"

// Для считывания файла меняем структуру Format_file, под файл который у нас будет,
// далее меняем в методе Read() считываемые поля Format_line

//void TestMiddleValue()
//{
//    using namespace file;
//    std::vector<double> numbers = {1,2,3,4,5,6,7,8,9,10}; // Подсчет
//    Proccess prosses;
//    assert(std::abs(5.5 - prosses.MiddleValue(numbers)) < 1e-5);
//    std::vector<double> numbers1; // empty
//    assert(std::abs(0 - prosses.MiddleValue(numbers1)) < 1e-5);
//    std::vector<double> numbers2{2};
//    assert(std::abs(2 - prosses.MiddleValue(numbers2)) < 1e-5);
//}

//void TestDispersion()
//{
//    using namespace file;
//    Proccess proccess;
//    std::vector<double> numbers = {12,23,45,33,65,54,54};
//    double middle = proccess.MiddleValue(numbers);
//    assert(std::abs(40.857 - middle)  < 1e-3);
//    double dispersion = proccess.ComputeDispersion(numbers, middle);
//    assert(std::abs(359.81 - dispersion) < 1e-2); // Заменить на СКО
//    std::vector<double> test;
//    assert(std::abs(0 - proccess.ComputeDispersion(test, 0)) < 1e-5);
//}

//void TestStandartDeviation()
//{
//    using namespace file;
//    Proccess proccess;
//    std::vector<double> numbers = {12,23,45,33,65,54,54};
//    double middle = proccess.MiddleValue(numbers);
//    assert(std::abs(40.857 - middle)  < 1e-3);
//    double dispersion = proccess.ComputeDispersion(numbers, middle);
//    assert(std::abs(sqrt(359.81) - proccess.ComputeStandartDeviation(dispersion)) < 1e-2); // Заменить на СКО
//    assert(std::abs(0 - proccess.ComputeStandartDeviation(-1)) < 1e-5);
//}

//void TestChangeTimeToUt()
//{
//    using namespace file;
//    Proccess proccess;
//    uint32_t time_early = 7000;
//    assert(proccess.ChangeMoscowTimeToUt(time_early) == 17800);
//    uint32_t time_late = 82800;
//    assert(proccess.ChangeMoscowTimeToUt(time_late) == 7200);
//}

//void TestComputeStandartDeviation()
//{
//    using namespace file;
//    Proccess proccess;
//    std::vector<double> numbers = {12,23,45,33,65,54,54};
//    double middle = proccess.MiddleValue(numbers);
//    assert(std::abs(40.857 - middle)  < 1e-3);
//    double dispersion = proccess.ComputeDispersion(numbers, middle);
//    assert(std::abs(359.81 - dispersion) < 1e-2);
//    std::vector<double> numbers1{};
//    assert(std::abs(0 - proccess.ComputeDispersion(numbers1, 2)) < 1e-2);
//    std::vector<double> numbers2{4};
//    assert(std::abs(0 - proccess.ComputeDispersion(numbers2, 2)) < 1e-2);
//}

//void TestTakeInfoTimeAndMof()
//{
//    using namespace file;
//    Proccess proccess;
//    uint16_t size_window = 10800;
//    proccess.SetTimeWindow(size_window);
//    ReadFile read("test.txt");
//    read.ReadMof();
//    proccess.TakeInfoTimeAndMof();
//    assert(proccess.mof_.time_per_sec_and_mof_[1].size() != 0); // Если стреляет данный ассерт, посмотри, сколько данных в файле - возможно нужно изменить размер временного окна (На самом деле, это символическая проверка)
//}

//void TestComputeTimeAndMiddleMof()
//{
//    using namespace file;
//    Proccess proccess;
//    uint16_t size_window = 10800;
//    proccess.SetTimeWindow(size_window);
//    ReadFile read("test.txt");
//    read.ReadMof();
//    proccess.ComputeTimeAndMiddleMof();
//    assert(proccess.mof_.time_and_middle_mof_.size() != 0);
//  //  assert(proccess.mof_.time_and_middle_mof_.size() == ) кол-во строк в файле <Если стреляет данный ассерт, посмотри, сколько данных в файле - возможно нужно изменить размер временного окна> так и есть в одно окно может несколько значений попадать, отсюда равенства не будет
//}

//void TestComputeTimeAndDispersionMof()
//{
//    using namespace file;
//    Proccess proccess;
//    uint16_t size_window = 10800;
//    proccess.SetTimeWindow(size_window);
//    ReadFile read("test.txt");
//    read.ReadMof();
//    proccess.ComputeTimeAndDispersionAndStandartDeviashionMof();
//    assert(proccess.mof_.time_and_dispersion_.size() != 0);
////  assert(proccess.mof_.time_and_middle_mof_.size() == ) кол-во строк в файле <Если стреляет данный ассерт, посмотри, сколько данных в файле - возможно нужно изменить размер временного окна> так и есть в одно окно может несколько значений попадать, отсюда равенства не будет
//}

//void TestProccess()
//{
//    TestMiddleValue();
//    TestDispersion();
//    TestChangeTimeToUt();
//    TestStandartDeviation();
////    TestTakeInfoTimeAndMof();
////    TestComputeTimeAndMiddleMof();
////    TestComputeTimeAndDispersionMof();
//}

//void TestSumFiles()
//{
//    using namespace file;
//    std::string name = "first.txt";
//    std::string name1 = "second.txt";
//    std::ofstream file_first(name);
//    std::ofstream file_second(name1);
//    file_first << "first" << std::endl <<"or no?" << std::endl;
//    file_second << "second" << std::endl <<"or no?" << std::endl;
//    assert(file_first.tellp() == 2);
//    ReadFile read;
//    read.SumFiles(name, name1);
//    assert(file_first.tellp() == 4);
//}

//void TestAddFile()
//{
//    using namespace file;
//    ReadFile read;
//    std::string text = "start.txt";
//    assert(read.files_.size() == 0);
//    read.AddFile(text);
//    assert(read.files_.size() == 1);
//}

//void TestReadMof()
//{
//    using namespace file;
//    ReadFile read("test.txt");
//    read.ReadMof();
//    assert(read.file_.size() != 0);
//}

//void TestReadFile()
//{
//    TestSumFiles();
//    TestAddFile();
//    TestReadMof();
//}

//void TestCalculateCountDataInWindowTime()
//{
//    using namespace file;
//    ReadFile read("test.txt");
//    read.ReadMof();
//    Proccess proccess(read, 500);
//    OutPutFile output(proccess);
//    assert(output.count_points_in_time_window_.size() != 0);
//}

//void TestTransformTimeFromSeconds()
//{
//   using namespace file;
//   OutPutFile outfile;
//    assert(2 == outfile.TransformTimeFromSeconds(7200, 3600));
//}

//void TestOutPutFile()
//{
//    TestCalculateCountDataInWindowTime();
//    TestTransformTimeFromSeconds();
//}

//void Tests()
//{
//    std::cout << "\t Start" << std::endl;
// //   TestReadFile();
//    TestProccess();
// //   TestOutPutFile();
//    std::cout << "\t End" << std::endl;
//}

void SolveMof()
{
      std::string path = "e:\\Alis_spring_\\01_25.dat";
      std::string name_result_file = "01_25_Al(070525).txt";
      uint16_t time_window_in_sec = 3600;
      file::ReadFile readfile(path);
      readfile.ReadMof();
      file::Proccess proccess(readfile.GetReadMof(), time_window_in_sec);
      proccess.TakeInfoTimeAndMof();
      proccess.ComputeTimeAndMiddleMof();
      proccess.ComputeTimeAndDispersionAndStandartDeviashionMof();
      file::OutPutFile output(proccess.GetDataMof());
      output.ShowMinimumsColomsDataMof(10);
      output.PrintFileMof(std::move(name_result_file), time_window_in_sec);
}

void SolvePrognosticFreqAustralia()
{
  std::string path = "E:\\Ionosphere\\MOF\\Data_prognostic\\Alis_spring_dasf_1024\\Al_d_151024.txt";
  std::string name_file_freq = "10_24_Als_F.txt";
  std::string name_file_amplitude = "10_24_Als_A.txt";
  file::ReadFile readfile(path);
  //readfile.TakeFilesFromDirectory(path); если несколько файлов
  readfile.ReadFileFreqAustralia();
  file::Proccess proccess(readfile.GetReadPrognosticFreqAustralia(), 5, 30);
  proccess.TakeInfoTimeAndFreqPrognosticRouteAustralia();
  file::OutPutFile output(proccess.GetDataPrognosticFreq());
  output.PrintFilePrognosticFreq(name_file_freq, proccess.ComputeMiddlePrognosticMof());
  output.PrintFilePrognosticFreqAmplitude(name_file_amplitude);
}

void SolvePrognosticFreqCyprus()
{
  std::string path = "f:\\Gorbage\\kipr_dasf_151024.txt";
  std::string name_file_freq = "10_24_Cyp_F.txt";
  std::string name_file_amplitude = "10_24_Cyp_A.txt";
//  readfile.TakeFilesFromDirectory(path); если несколько файлов
  file::ReadFile readfile(path);
  readfile.ReadFileFreqCyprus();
  file::Proccess proccess(readfile.GetReadPrognosticFreqCyprus(), 5, 30);
  proccess.TakeInfoTimeAndFreqPrognosticRouteCyprus();
  file::OutPutFile output(proccess.GetDataPrognosticFreq());
  output.PrintFilePrognosticFreq(name_file_freq, proccess.ComputeMiddlePrognosticMof());
  output.PrintFilePrognosticFreqAmplitude(name_file_amplitude);
}

int main()
{
  //  Tests();
//  SolvePrognosticFreqAustralia();
  SolveMof();
  //SolvePrognosticFreqCyprus();
    return 0;
}
