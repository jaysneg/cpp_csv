#include <iostream> // cout, endl
#include <fstream>  // fstream
#include "simplecsvread.h"

int main()
{

    auto fileCSV = simpleCSV::read("../2.csv").to_list();

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