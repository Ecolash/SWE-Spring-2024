/*
Class Definition:
=================
DataVector: Represents a vector of doubles.
Member variable: vector<double> v to store the vector data.

Constructor and Destructor:
===========================
1) DataVector(int dimension): Constructor to initialize a vector with a specified dimension.
2) ~DataVector(): Destructor to delete the vector

Copy Constructor and Assignment Operators:
==========================================
1) DataVector(const DataVector &other): Copy constructor.
2) DataVector &operator=(const DataVector &other): Assignment operator for copying DataVector objects.
3) DataVector &operator=(vector<double> &other): Assignment operator for assigning a vector<double> to a DataVector.

Set and Get Functions:
======================
1) void setData(vector<double> &info): Set the vector data.
2) vector<double> &getData(): Get the vector data.
3) void setDimension(int dimension): Set the dimension of the vector.
4) int getDimension() const: Get the dimension of the vector.

Vector Operator Overloadings:
=============================
1) DataVector operator+(const DataVector &other): Addition of vectors.
2) DataVector operator-(const DataVector &other): Subtraction of vectors.
3) double operator*(const DataVector &other): Dot product of vectors.

Utility Functions:
=================
1) double norm(): Calculate the Euclidean norm of the vector.
2) double dist(DataVector b): Calculate the Euclidean distance between two vectors.
3) void print(): Print the vector elements.

*/

#include <iostream>
#include <vector>
using namespace std;

class DataVector
{
    vector<double> v;

public:
    DataVector(int dimension);
    ~DataVector();

    DataVector(const DataVector &other);
    DataVector &operator=(const DataVector &other);
    DataVector &operator=(vector<double> &other);

    void setData(vector<double> &info);
    vector<double> &getData();

    int getDimension() const;
    void setDimension(int dimension);

    DataVector operator+(const DataVector &other);
    DataVector operator-(const DataVector &other);
    double operator*(const DataVector &other);

    double norm();
    double dist(DataVector b);
    void print();
};
