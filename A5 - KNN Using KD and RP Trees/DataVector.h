#include <iostream>
#include <vector>
using namespace std;

class TreeIndex;
class KDTreeIndex;
class RPTreeIndex;

class DataVector
{
    vector<double> v;

    public:
        DataVector(int dimension = 0);
        ~DataVector();

        void set(int idx, int value);
        double get(int idx);

        DataVector(vector<double>);
        DataVector(const DataVector &);

        DataVector &operator=(const DataVector &);
        DataVector &operator=(const vector<double> &);
        double operator[](int i);
        void setDimension(int dimension = 0);
        int getDimension();

        void showDataVector();
        DataVector operator+(const DataVector &);
        DataVector operator-(const DataVector &);
        double operator*(const DataVector &);
        double norm();
        double dist(DataVector &);
        bool compare(DataVector &other, DataVector &rule);

        void print();
        void random_unit_vec(int);
};

typedef struct node
{
    vector<int> indices;
    int axis;
    DataVector unit; // Stores Datavector with only one 1(KD Tree) or random unit vector(RP Tree)
    double delta;
    double median;
} node;