#include "simplecsvread.h"

namespace simpleCSV
{

read::read(const std::string& file_path) : _file_path(file_path) {}

void read::_readCSVRow(const std::string& row, std::vector<std::string>& fields, CSVState& state, size_t& i)
{
    char prev;

    for (char c : row)
    {
        if (c == ',' && state == CSVState::UnquotedField)
        {
            fields.push_back("");
            i++;
        }
        else if (c == '"' && prev == NULL && state == CSVState::UnquotedField)
        {
           state = CSVState::QuotedField;
        }
        else if (prev == '"' && c == ',' && state == CSVState::QuotedField)
        {
            fields[i].pop_back();
            fields.push_back("");
            i++;
            state = CSVState::UnquotedField;
        }
        else if (c == '"' && state == CSVState::QuotedField)
        {
            fields[i].push_back('"');
        }
        else if (prev != '"' && c == '\0' && state == CSVState::QuotedField)
        {
            fields[i].push_back('\n');
        }
        else if (prev == ',' && c == '"' && state == CSVState::UnquotedField)
        {
            state = CSVState::QuotedField;
        }
        else if (prev == '"' && c == '\0' && state == CSVState::QuotedField)
        {
            fields[i].pop_back();
            state = CSVState::EndOfRow;
        }
        else if (c == '\0' && state == CSVState::UnquotedField)
        {
            state = CSVState::EndOfRow;
        }
        else
        {
            fields[i].push_back(c);
        }

        prev = c;
    }
};

std::vector<std::vector<std::string>> read::to_list(void)
{
    std::vector<std::vector<std::string>> table;
    std::string row;
    
    std::ifstream infile(read::_file_path);
    
    if (!infile.is_open())
        throw std::runtime_error("ERROR: file not open. " + read::_file_path);

    size_t i{0};
    std::vector<std::string> fields{""};
    CSVState state = CSVState::UnquotedField;

    while (!infile.eof())
    {
        std::getline(infile, row);
        row.push_back('\0');

        if (infile.bad() || infile.fail())
        {
            break;
        }

        _readCSVRow(row, fields, state, i);

        if (state == CSVState::EndOfRow)
        {
            table.push_back(fields);

            fields.clear();
            fields.push_back("");
            state = CSVState::UnquotedField;
            i = 0;
        }
    }

    infile.close();

    return table;
};
} // namespace simpleCSV