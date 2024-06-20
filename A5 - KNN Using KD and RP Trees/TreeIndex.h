#include <vector>
#include <queue>
#include "VectorDataset.h"

using namespace std;

#define N 100
#define HEAP priority_queue<pair<double, int>>

class TreeNode
{
    node *info;
    TreeNode *left;
    TreeNode *right;
    friend class TreeIndex;

    public:
        DataVector KDRule(int, int);
        DataVector RPRule(int);
        TreeNode(int, vector<int>);
        void MakeTree(int type);
        VectorDataset search(DataVector , int, int type);
        void recSearch(DataVector, int, HEAP &, int type);
        void getNearest(DataVector &, int, HEAP&);
        ~TreeNode();
};

class TreeIndex
{
    TreeNode *root;

    protected:
        TreeIndex(int i, int type);
        ~TreeIndex(); 

    public:
        VectorDataset KNN(DataVector , int, int type);
        TreeIndex &AddDataVector(DataVector, int type);
        TreeIndex &RemoveDataVector(int , int type);
    };

class KDTreeIndex : public TreeIndex
{
private:
    static KDTreeIndex *instance;
    KDTreeIndex();
    ~KDTreeIndex();

public:
    static KDTreeIndex &GetInstance()
    {
        if (!instance) instance = new KDTreeIndex();
        return *instance;
    }

};

class RPTreeIndex : public TreeIndex
{
private:
    static RPTreeIndex *instance;
    RPTreeIndex();
    ~RPTreeIndex();

public:
    static RPTreeIndex &GetInstance()
    {
        if (!instance) instance = new RPTreeIndex();
        return *instance;
    }
};
