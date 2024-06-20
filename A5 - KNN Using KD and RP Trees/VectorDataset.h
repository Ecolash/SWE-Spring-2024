#include "DataVector.h"

class TreeIndex;
class VectorDataset
{
    vector<DataVector> data;

    public:
        VectorDataset();
        ~VectorDataset();

        DataVector &operator[](int i);
        void add(const DataVector &);
        void remove(int idx);
        DataVector &getVector(int);
        double get(int, int);

        void print(int idx);
        int getsize();
        int getdimension();
        double get_median(node *, int); 
        double get_median(node *, vector<double> &);
        void print();
        double max_distance(DataVector &);
        void ReadDataset(string );
};