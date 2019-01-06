#include <iostream> // cout, endl
#include <fstream>  // fstream
#include <vector>
#include <string>
#include <algorithm> // copy
#include <iterator>  // ostream_operator
#include <boost/tokenizer.hpp>

#include <istream>
#include <string>
#include <vector>

enum class CSVState
{
    UnquotedField,
    QuotedField,
    EndOfRow
};

void readCSVRow(const std::string &row, std::vector<std::string> &fields, CSVState &state, size_t &i)
{
    char prev;

    for (char c : row)
    {
        if (c == ',' && state == CSVState::UnquotedField)
        {
            fields.push_back("");
            i++;
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
}

std::vector<std::vector<std::string>> readCSV(std::istream &in)
{
    std::vector<std::vector<std::string>> table;
    std::string row;

    size_t i{0};
    std::vector<std::string> fields{""};
    CSVState state = CSVState::UnquotedField;

    while (!in.eof())
    {
        std::getline(in, row);
        row.push_back('\0');

        if (in.bad() || in.fail())
        {
            break;
        }

        readCSVRow(row, fields, state, i);

        if (state == CSVState::EndOfRow)
        {
            table.push_back(fields);

            fields.clear();
            fields.push_back("");
            state = CSVState::UnquotedField;
            i = 0;
        }
    }

    return table;
}

int main()
{
    std::string data("../2.csv");

    std::ifstream in(data.c_str());
    if (!in.is_open())
        return 1;

    auto fileCSV = readCSV(in);

    for (int i{0}; i < fileCSV.size(); i++)
    {
        for (int z{0}; z < fileCSV[i].size(); z++)
        {
            std::cout << "fileCSV[i][z].size(): " << fileCSV[i][z].size() << std::endl;
            std::cout << "fileCSV[i][z]: " << fileCSV[i][z] << std::endl;
        }

        std::cout << "fileCSV[i].size(): " << fileCSV[i].size() << std::endl;

        std::cout << "\n-----------------" << std::endl;
    }

    std::cout << fileCSV.size() << std::endl;
}