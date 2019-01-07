#ifndef SIMPLE_CSV_WRITE_H
#define SIMPLE_CSV_WRITE_H

#include <string>
#include <vector>

namespace simpleCSV
{
class write
{
  public:
    write(const std::string& file_path, std::vector<std::vector<std::string>>& data);
    ~write() = default;

  private:
    std::string  _file_path;
    std::vector<std::vector<std::string>> _data;
    void _writeCSVToFile(void);
};

} // namespace simpleCSV

#endif