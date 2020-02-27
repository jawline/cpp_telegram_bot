#ifndef _CSV_LOADER_H_
#define _CSV_LOADER_H_
#include <functional>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <string_view>

typedef std::function<void(std::vector<std::string> const&)> CsvCallbackMethod;

class CsvLoader {
private:
  CsvCallbackMethod m_callbackMethod;
  std::string m_deliminator;

public:
  CsvLoader(std::string& deliminator);
  virtual ~CsvLoader();

  void set_callback(CsvCallbackMethod callbackMethod);
  void run(std::istream& stream);
};

#endif
