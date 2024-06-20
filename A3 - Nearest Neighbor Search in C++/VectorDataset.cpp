#include "VectorDataset.h"

#include <fstream>
#include <sstream>
using namespace std;

void VectorDataset ::ReadDataset(string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line);
    while (getline(file, line))
    {
        vector<double> row;
        istringstream iss(line);
        double cell;
        char sep;

        while (iss >> cell)
        {
            if (iss >> sep and sep != ',')
            {
                cout << "Error! Unexpected character at end of data!";
                return;
            }
            double value = cell;
            row.push_back(value);
        }

        DataVector x(row.size());
        x.setData(row);
        v.push_back(x);
    }
    file.close();
}

VectorDataset::VectorDataset() {}
VectorDataset::VectorDataset(const vector<DataVector> &inputdata) : v(inputdata) {}
VectorDataset::~VectorDataset() {}

void VectorDataset ::print()
{
    int n = v.size();
    for (int i = 0; i < n; i++)
    {
        DataVector x = v[i];
        x.print();
    }
}

int VectorDataset ::getDimension() const
{
    return v.size();
}

DataVector &VectorDataset ::getData(int index)
{
    return v[index];
}

void VectorDataset ::setData(DataVector &a)
{
    return v.push_back(a);
}
