#include "DataVector.h"
#include <cmath>

using namespace std;

DataVector::DataVector(int dimension = 0)
{
    v.resize(dimension);
}

void DataVector::setDimension(int dimension = 0)
{
    v.clear();
    v.resize(dimension, 0.0);
    return;
}

DataVector::~DataVector() {}

int DataVector::getDimension() const
{
    return v.size();
}

void DataVector::setData(vector<double> &info)
{
    v = info;
}

DataVector &DataVector::operator=(const DataVector &other)
{
    if (this != &other)
    {
        v = other.v;
    }
    return *this;
}

DataVector &DataVector::operator=(vector<double> &other)
{
    v = other;
    return *this;
}

vector<double> &DataVector::getData()
{
    return v;
}

DataVector ::DataVector(const DataVector &other)
{
    v = other.v;
}

DataVector DataVector ::operator+(const DataVector &other)
{
    DataVector result;
    if (v.size() != other.getDimension())
    {
        cerr << "Adding vectors of different dimensions is incompatible!";
        exit(0);
    }

    result.setDimension(v.size());
    int n = v.size();
    for (int i = 0; i < n; i++)
    {
        result.v[i] = v[i] + other.v[i];
    }
    return result;
}

DataVector DataVector ::operator-(const DataVector &other)
{
    DataVector result;
    if (v.size() != other.getDimension())
    {
        cerr << "Substracting vectors of different dimensions is incompatible!";
        exit(0);
    }
    result.setDimension(v.size());
    int n = v.size();
    for (int i = 0; i < n; i++)
    {
        result.v[i] = v[i] - other.v[i];
    }
    return result;
}

double DataVector ::operator*(const DataVector &other)
{
    double result = 0;
    if (v.size() != other.getDimension())
    {
        cerr << "Dot product of vectors of different dimensions is incompatible!";
        exit(0);
    }
    int n = v.size();
    for (int i = 0; i < n; i++)
    {
        result += v[i] * other.v[i];
    }
    return result;
}

double DataVector::norm()
{
    return sqrt((*this) * (*this));
}

double DataVector::dist(DataVector b)
{
    return (*this - b).norm();
}

void DataVector ::print()
{
    int n = v.size();
    for (int i = 0; i < n; i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}
