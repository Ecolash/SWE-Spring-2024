#include <iostream>
#include <algorithm>
#include "TreeIndex.h"
#include <vector>
#include <random>

using namespace std;

VectorDataset train_set;
VectorDataset test_set;

TreeNode::TreeNode(int axis, vector<int> index) : left(NULL), right(NULL)
{
    info = new node;
    info->indices = index;
    info->delta = 0; 
    info->median = -1;
    info->axis = axis; 
}

TreeNode::~TreeNode()
{
    delete info;
    delete left;
    delete right;
}

DataVector TreeNode::KDRule(int dim, int idx)
{
    DataVector result(dim); 
    result.set(idx, 1);       
    return result;
}

DataVector TreeNode::RPRule(int dim)
{
    DataVector result(dim);
    // srand(time(NULL));
    result.random_unit_vec(dim); 
    return result;
}

void TreeNode::MakeTree(int type)
{
    int dim = train_set.getdimension();
    int size = info->indices.size();
    info->delta = 0;

    if (size <= N)
    {
        if (size != 0) cout << "Partition created with " << size << " points!" << endl;
        return;
    }
    info->unit = (type == 0)? KDRule(dim, info->axis) : RPRule(dim); 
    sort(info->indices.begin(), info->indices.end(), [this](int i, int j){ return train_set[i].compare(train_set[j], info->unit); });
    info->median = train_set[info->indices[size / 2]] * info->unit;

    vector<int> L, R;
    int x = rand() % size;
    if (type == 1) info->delta = (((float)rand() / RAND_MAX) * 2 - 1) * 6 * train_set.max_distance(train_set[x]) / sqrt(dim);
    int val = info->median + info->delta;

    for (int i = 0; i < size; ++i)
    {
        int x = info->indices[i];
        if (train_set[x] * info->unit < val) L.push_back(x);
        else R.push_back(x);
    }

    left = new TreeNode((info->axis + 1) % dim, L);
    right = new TreeNode((info-> axis + 1) % dim, R);
    left->MakeTree(type);
    right->MakeTree(type); 
}

VectorDataset TreeNode::search(DataVector d, int k, int type)
{
    HEAP maxheap; 
    recSearch(d, k, maxheap, type);              
    VectorDataset result;                      
    while (!maxheap.empty())
    {
        result.add(train_set[maxheap.top().second]);
        maxheap.pop();
    }
    return result;
}

TreeIndex& TreeIndex::AddDataVector(DataVector v, int type)
{
    train_set.add(v);
    delete(root);
    root = new TreeNode(0, vector<int>(train_set.getsize(), 0));
    for (int i = 0; i < train_set.getsize(); i++) {root->info->indices[i] = i;}
    root->MakeTree(type);
    return (*this);
}

TreeIndex &TreeIndex::RemoveDataVector(int index, int type)
{
    train_set.remove(index);
    delete (root);
    root = new TreeNode(0, vector<int>(train_set.getsize(), 0));
    for (int i = 0; i < train_set.getsize(); i++)
    {
        root->info->indices[i] = i;
    }
    root->MakeTree(type);
    return (*this);
}

void TreeNode::recSearch(DataVector d, int k, HEAP &heap, int type)
{
    if (left == NULL && right == NULL)
    {
        getNearest(d, k, heap);
        return;
    }
    double dis = (d) * info->unit;
    if ((d) * info->unit < info->median + info->delta)
    {
        left->recSearch(d, k, heap, type); 
        if (heap.size() < k || dis < heap.top().first) right->recSearch(d, k, heap, type);
    }
    else
    {
        right->recSearch(d, k, heap, type);
         if (heap.size() < k || dis <= heap.top().first)  left->recSearch(d, k, heap, type);
    }
}

void TreeNode::getNearest(DataVector &data, int k, HEAP &heap)
{
    vector<double> distances;
    for (int i = 0; i < info->indices.size(); i++) distances.push_back(train_set[info->indices[i]].dist(data));
    for (int i = 0; i < info->indices.size(); i++)
    {
        if (heap.size() < k) heap.push({distances[i], info->indices[i]});
        else
        {
            if (heap.top().first > distances[i])
            {
                heap.pop();
                heap.push({distances[i], info->indices[i]});
            }
        }
    }
}

VectorDataset TreeIndex::KNN(DataVector v, int k, int type) { return root->search(v, k, type); }

TreeIndex::TreeIndex(int i, int type) : root(new TreeNode(i, vector<int>(train_set.getsize(), 0)))
{
    for (int i = 0; i < train_set.getsize(); ++i) root->info->indices[i] = i;
    root->MakeTree(type);
};

TreeIndex::~TreeIndex() { delete root; }

KDTreeIndex::KDTreeIndex() : TreeIndex(train_set.getsize() / 2, 0) {}
KDTreeIndex::~KDTreeIndex() {}

RPTreeIndex::RPTreeIndex() : TreeIndex(-1, 1) {}
RPTreeIndex::~RPTreeIndex() {}


KDTreeIndex *KDTreeIndex::instance = NULL;
RPTreeIndex *RPTreeIndex::instance = NULL;

int main()
{
    int k;
    cout << "Enter the value of k: ";
    cin >> k;

    train_set.ReadDataset("fmnist-train100.csv");
    cout << "Reading data vectors completed!" << endl;

    test_set.ReadDataset("fmnist-test100.csv");
    cout << "Reading test vectors completed!" << endl;

    cout << "----------------------------------------------------------------" << endl;
    cout << "KD Trees :" << endl;
    cout << "----------------------------------------------------------------" << endl;
    KDTreeIndex::GetInstance();

    cout << "----------------------------------------------------------------" << endl;
    cout << "RP Trees :" << endl;
    cout << "----------------------------------------------------------------" << endl;
    RPTreeIndex::GetInstance();

    int t = test_set.getsize();
    cout << "----------------------------------------------------------------" << endl;
    cout << "Finding KNN using KD Trees :" << endl;
    cout << "----------------------------------------------------------------" << endl;
    for (int i = 0; i < t; i++)
    {
        DataVector test = test_set[i];
        cout << k << " Nearest Datavectors " << " wrt Datavector at index " << i << " : \n";
        KDTreeIndex::GetInstance().KNN(test, k, 0).print();
        cout << "----------------------------------------------------------------" << endl;
    }

    cout << "----------------------------------------------------------------" << endl;
    cout << "Finding KNN using RP Trees :" << endl;
    cout << "----------------------------------------------------------------" << endl;
    for (int i = 0; i < t; i++)
    {
        DataVector test = test_set[i];
        cout << k << " Nearest Datavectors " << " wrt Datavector at index " << i << " : \n";
        RPTreeIndex::GetInstance().KNN(test, k, 1).print();
        cout << "----------------------------------------------------------------" << endl;
    }

    return 0;
}