#ifndef SIMPLE_CSV_READ_H
#define SIMPLE_CSV_READ_H

#include <fstream>
#include <string>
#include <vector>
#include <istream>

namespace simpleCSV
{
class read
{
  public:
    enum CSVState
    {
        UnquotedField,
        QuotedField,
        EndOfRow
    };
    read(const std::string& file_path);
    ~read() = default;
    std::vector<std::vector<std::string>> to_list(void);

  private:
    std::string  _file_path;
    void _readCSVRow(const std::string& row, std::vector<std::string>& fields, CSVState& state, size_t& i);
};

} // namespace simpleCSV

#endif