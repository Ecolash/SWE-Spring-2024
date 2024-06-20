#include "DataVector.h"
#include <cmath>
#include <iostream>

using namespace std;

DataVector::DataVector(int dimension) : v(dimension, 0.0) {}
DataVector::DataVector(vector<double> vec) : v(vec) {}
DataVector::DataVector(const DataVector &other) : v(other.v) {}

DataVector::~DataVector() {}
void DataVector::set(int idx, int value) {v[idx] = 1;}
double DataVector::get(int idx) { return v[idx]; }

DataVector &DataVector::operator=(const DataVector &other)
{
    if (v != other.v) v = other.v;
    return (*this);
}

DataVector &DataVector::operator=(const vector<double> &vect) { v = vect; return (*this);}
double DataVector::operator[](int i) { return v[i]; }

void DataVector::setDimension(int dimension) { v.clear(); v.resize(dimension, 0.0); }
int DataVector::getDimension() { return v.size(); }

DataVector DataVector ::operator+(const DataVector &other)
{
    DataVector result;
    if (v.size() != other.v.size())
    {
        cerr << "Adding vectors of different dimensions is incompatible!";
        exit(0);
    }

    result.setDimension(v.size());
    int n = v.size();
    for (int i = 0; i < n; i++) result.v[i] = v[i] + other.v[i];
    return result;
}

DataVector DataVector ::operator-(const DataVector &other)
{
    DataVector result;
    if (v.size() != other.v.size())
    {
        cerr << "Subtracting vectors of different dimensions is incompatible!";
        exit(0);
    }
    result.setDimension(v.size());
    int n = v.size();
    for (int i = 0; i < n; i++) result.v[i] = v[i] - other.v[i];
    return result;
}

double DataVector ::operator*(const DataVector &other)
{
    double result = 0;
    if (v.size() != other.v.size())
    {
        cerr << "Dot product of vectors of different dimensions is incompatible!";
        exit(0);
    }
    int n = v.size();
    for (int i = 0; i < n; i++) result += v[i] * other.v[i];
    return result;
}

double DataVector::norm()
{
    return sqrt((*this) * (*this));
}

double DataVector::dist(DataVector &b){ return (*this - b).norm(); }

void DataVector ::print()
{
    int n = v.size();
    for (int i = 0; i < min(n, 32); i++) cout << v[i] << " ";
    cout << "...";
}

bool DataVector::compare(DataVector &other, DataVector &rule) { return (*this) * rule < other * rule; }

void DataVector ::random_unit_vec(int n)
{
    v.clear();
    v.resize(n);
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        v[i] = (float)rand() / RAND_MAX;
        sum += v[i] * v[i];
    }
    double norm = sqrt(sum);
    for (int i = 0; i < n; i++) v[i] = v[i]/ norm;
    return;
}
