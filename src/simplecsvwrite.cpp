#include <fstream>
#include <vector>
#include "simplecsvwrite.h"

namespace simpleCSV
{

write::write(const std::string &file_path, std::vector<std::vector<std::string>> &data)
    : _file_path(file_path), _data(data)
{
  _writeCSVToFile();
};

void write::_writeCSVToFile(void)
{
  std::ofstream f(_file_path);

  for (int i{0}; i < _data.size(); i++)
  {
    for (int z{0}; z < _data[i].size(); z++) 
    {
      if(z != 0)
        f << ','; 
      f << '"' << _data[i][z] << '"';
    }
    f << std::endl;
  }
};
} // namespace simpleCSV