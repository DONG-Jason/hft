#ifndef DATA_TRANSFORMER_H_
#define DATA_TRANSFORMER_H_

#include <iostream>
#include <fstream>
#include <memory>
#include "struct/market_snapshot.h"
#include "util/common_tools.h"
#include "util/time_controller.h"
#include "util/history_worker.h"
#include "util/ThreadPool.h"
#include <zlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/sysinfo.h>

class DataTransformer {
 public:
  DataTransformer(int num);
  DataTransformer();
  ~DataTransformer();
  static void BinToLog(const std::string & source_path, const std::string & dest_dir="", const std::string & file_name = "");
  static void BinToCsv(const std::string & source_path, const std::string & dest_dir="", const std::string & file_name = "");

  static void LogToBin(const std::string & source_path, const std::string & dest_dir="", const std::string & file_name = "");
  static void LogToCsv(const std::string & source_path, const std::string & dest_dir="", const std::string & file_name = "");

  static void CsvToBin(const std::string & source_path, const std::string & dest_dir="", const std::string & file_name = "");
  static void CsvToLog(const std::string & source_path, const std::string & dest_dir="", const std::string & file_name = "");

  static void GzToCsv(const std::string & source_path, const std::string & dest_dir="", const std::string & file_name = "");
  static void GzToLog(const std::string & source_path, const std::string & dest_dir="", const std::string & file_name = "");

  static void CsvCatContract(const std::string & source_path, const std::string & dest_dir="", const std::string & file_name = "");
  static void BinCatContract(const std::string & source_path, const std::string & dest_dir="", const std::string & file_name = "");
  static void GzCatContract(const std::string & source_path, const std::string & dest_dir="", const std::string & file_name = "");
  static void GzDirectCat(const std::string & source_path, const std::string & dest_dir="", const std::string & file_name = "");
  static void BinDirectCat(const std::string & source_path, const std::string & dest_dir="", const std::string & file_name = "");

  void BatchRun();

 private:
  static std::string GenFileName(const std::string & source_path, const std::string & file_name, const std::string & post_prefix);
  TimeController* tc;
  int cpu_count;
  ThreadPool * pool;
};

#endif  // DATA_TRANSFORMER_H_
