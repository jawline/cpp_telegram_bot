#include "csv_loader.hpp"
#include "spdlog/spdlog.h"

CsvLoader::CsvLoader(std::string& deliminator) {
  spdlog::debug("CsvLoader created");
  this->m_deliminator = deliminator;
}

CsvLoader::~CsvLoader() {
  spdlog::debug("CsvLoader destroyed");
}

void CsvLoader::set_callback(CsvCallbackMethod callbackMethod) {
  this->m_callbackMethod = callbackMethod;
  spdlog::debug("CsvLoader callback set");
}

void CsvLoader::run(std::istream& stream) {
  spdlog::info("CsvLoader starting on stream");
  std::vector<std::string> csv_array;

  for (std::string line; std::getline(stream, line);) {
    spdlog::debug("Processing line {}", line);

    //Find all the elements in the line by scanning for the deliminator
    size_t last_pos = 0;
    size_t idx = 0;

    while (true) {
      idx = line.find(this->m_deliminator, last_pos);

      if (idx == std::string::npos) {
        break;
      }

      spdlog::debug("Indices {}-{}", last_pos, idx);
      std::string element_view = line.substr(last_pos, idx - last_pos);
      csv_array.push_back(element_view);

      last_pos = idx + this->m_deliminator.size();
    }

    csv_array.push_back(line.substr(last_pos));
   
    this->m_callbackMethod(csv_array); 

    //Clear the view container after each line
    csv_array.clear(); 
  }
}
