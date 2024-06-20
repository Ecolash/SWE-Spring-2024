#include "VectorDataset.h"
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

void VectorDataset ::ReadDataset(string filename)
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

        DataVector x(row);
        data.push_back(x);
    }
    file.close();
}

VectorDataset::VectorDataset() {}
VectorDataset::~VectorDataset() {}
DataVector &VectorDataset::operator[](int i) { return data[i]; }

double VectorDataset::max_distance(DataVector &vec)
{
    double result = 0;
    for (int i = 0; i < data.size(); i++) result = max(result, data[i].dist(vec));
    return result;
}

void VectorDataset::remove(int idx)
{
    int n = data.size();
    data.erase(data.begin() + idx);
}

double VectorDataset::get(int index, int axis)
{
    return data[index].get(axis);
}
DataVector &VectorDataset::getVector(int index) { return data[index]; }

void VectorDataset ::print() 
{
    int n = data.size();
    for (int i = 0; i < n; i++)
    {
        DataVector x = data[i];
        cout << "Point " << i + 1 <<": ";
        x.print();
        cout << endl;
    }
}

void VectorDataset ::print(int idx)
{
    DataVector x = data[idx];
    cout << "Neighbour" << idx + 1;
    x.print();
}

int VectorDataset ::getsize() { return data.size(); }
int VectorDataset ::getdimension() {return data[0].getDimension();}
void VectorDataset ::add(const DataVector &a) { return data.push_back(a); }

