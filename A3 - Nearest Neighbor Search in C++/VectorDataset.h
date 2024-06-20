/*
File Reading Function:
======================
1) void ReadDataset(string &filename):  (CSV Reader)
   The ReadDataset function of the VectorDataset class reads a dataset from a file specified by the input filename.
   It opens the file, skips the first line (column numbers), and then iterates through the remaining lines.
   For each line, it parses numeric values separated by commas, creating a DataVector object for each line and adding it to the dataset.
   The function ensures proper handling of errors, such as file opening failures or unexpected characters at the end of data lines.
   The resulting dataset is stored in the class's vector (v).

Constructor and Destructor:
===========================
1) VectorDataset(): Default constructor implementation.
2) VectorDataset(const vector<DataVector> &inputdata): Constructor implementation that initializes the dataset with an existing vector (overload)
3) ~VectorDataset(): Destructor implementation.

Printing Function:
==================
1) void print(): Prints each DataVector in the dataset.

Getter and Setter Functions:
============================
1) int getDimension() const: Returns the size of the dataset.
2) DataVector &getData(int index): Returns a reference to the DataVector at the specified index.
3) void setData(DataVector &a): Adds a DataVector to the dataset.
*/

#include <iostream>
#include "DataVector.h"

using namespace std;

class VectorDataset
{
public:
    vector<DataVector> v;

    VectorDataset();
    VectorDataset(const vector<DataVector> &inputdata);
    ~VectorDataset();
    void ReadDataset(string &fileName);
    int getDimension() const;
    DataVector &getData(int index);
    void setData(DataVector &a);
    void print();
};