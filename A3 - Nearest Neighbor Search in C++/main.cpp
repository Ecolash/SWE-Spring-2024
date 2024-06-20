#include "VectorDataset.h"
#include <algorithm>
#include <chrono>

using namespace chrono;
using namespace std;

// Function to perform k-nearest neighbors (KNN) classification
VectorDataset KNN(VectorDataset &dataset, DataVector &test, int k)
{
    // Vector to store distances and their corresponding indices
    vector<pair<double, int>> distances;

    // Number of data points in the dataset
    int n = dataset.getDimension();

    // Calculate distances between the test point and all points in the dataset
    for (int i = 0; i < n; i++)
    {
        double d = test.dist(dataset.getData(i));
        distances.push_back({d, i});
    }

    // Sort distances in ascending order
    sort(distances.begin(), distances.end());

    // Create a new dataset to store the k-nearest neighbors
    VectorDataset D;

    // Add the k-nearest neighbors to the new dataset
    for (int i = 0; i < min(k, n); i++)
    {
        cout << "Neighbour " << i + 1 << ": " << distances[i].second << endl;
        D.setData(dataset.getData(distances[i].second));
    }

    // Return the dataset containing k-nearest neighbors
    return D;
}

int main()
{
    // User input: value of k for KNN
    int k;
    cout << "Enter the value of k: ";
    cin >> k;

    // Load training dataset
    VectorDataset train;
    string path_train = "fmnist-train.csv";
    train.ReadDataset(path_train);

    // Load testing dataset
    VectorDataset test;
    string path_test = "fmnist-test100.csv";
    test.ReadDataset(path_test);

    // Record start time for performance measurement
    auto start = high_resolution_clock::now();

    // Number of data points in the testing dataset
    int n = test.getDimension();

    // Iterate through each test data point
    for (int i = 0; i < n; i++)
    {
        // Get the current test data point
        DataVector x = test.getData(i);
        cout << "Processing Test Data Point : " << i + 1 << endl;
        cout << "------------------------------" << endl;
        // Perform KNN on the current test data point using the training dataset
        VectorDataset ans(KNN(train, x, k));

        // Print the index of the current test data point
        cout << "------------------------------" << endl;
        cout << "Test Data Point " << i + 1 << " processed." << endl;
        cout << endl;
    }

    // Record stop time for performance measurement
    auto stop = high_resolution_clock::now();

    // Calculate and print the total time taken
    std::chrono::duration<double> d = stop - start;
    cout << "Time taken: " << d.count() << " seconds" << endl;

    // Return 0 to indicate successful execution
    return 0;
}
