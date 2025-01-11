#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib> // For rand() and srand()
using namespace std;

struct Point {
    double x, y;     // coordinates
    int cluster;     // no default cluster
    double minDist;  // default infinite distance to nearest cluster

    Point() : x(0.0), y(0.0), cluster(-1), minDist(__DBL_MAX__) {}
    Point(double x, double y) : x(x), y(y), cluster(-1), minDist(__DBL_MAX__) {}

    // Computes the (square) Euclidean distance between this point and another
    double distance(Point p) {
        return (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y);
    }
};

// Generates a dataset of random points based on user input
vector<Point> generateRandomData(int numPoints) {
    vector<Point> points;
    srand(static_cast<unsigned>(time(0)));
    
    for (int i = 0; i < numPoints; ++i) {
        double x = static_cast<double>(rand()) / RAND_MAX * 100.0;
        double y = static_cast<double>(rand()) / RAND_MAX * 100.0;
        points.push_back(Point(x, y));
    }
    return points;
}

/*
points - pointer to vector of points
epochs - number of k-means iterations
k - the number of initial centroids
*/
void kMeansClustering(vector<Point>* points, int epochs, int k) {
    int n = points->size();

    // Randomly initialize centroids
    vector<Point> centroids;
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < k; ++i) {
        centroids.push_back(points->at(rand() % n));
    }

    for (int i = 0; i < epochs; ++i) {
        // Assign points to the nearest centroid
        for (auto &c : centroids) {
            for (auto &p : *points) {
                double dist = c.distance(p);
                if (dist < p.minDist) {
                    p.minDist = dist;
                    p.cluster = &c - &centroids[0];  // clusterId
                }
            }
        }

        // Prepare data for centroid update
        vector<int> nPoints(k, 0);
        vector<double> sumX(k, 0.0), sumY(k, 0.0);

        for (auto &p : *points) {
            int clusterId = p.cluster;
            nPoints[clusterId] += 1;
            sumX[clusterId] += p.x;
            sumY[clusterId] += p.y;

            p.minDist = __DBL_MAX__;  // reset distance for next iteration
        }

        // Update centroids
        for (int j = 0; j < k; ++j) {
            if (nPoints[j] > 0) {  // Avoid division by zero
                centroids[j].x = sumX[j] / nPoints[j];
                centroids[j].y = sumY[j] / nPoints[j];
            }
        }
    }

    // Write data points to a file
    ofstream pointsFile("output_data_points.txt");
    pointsFile << "x,y,cluster" << endl;
    for (const auto &p : *points) {
        pointsFile << p.x << "," << p.y << "," << p.cluster << endl;
    }
    pointsFile.close();

    // Write centroids to a separate file
    ofstream centroidsFile("centroids.txt");
    centroidsFile << "x,y,cluster" << endl;
    for (int j = 0; j < k; ++j) {
        centroidsFile << centroids[j].x << "," << centroids[j].y << "," << j << endl;
    }
    centroidsFile.close();

    for (int j = 0; j < k; ++j) {
        cout << "Cluster " << j << ":" << endl;
        cout << "Number of points: " 
             << count_if(points->begin(), points->end(), [j](Point p) { return p.cluster == j; }) << "\t";
        cout << "Centroid: (" << centroids[j].x << ", " << centroids[j].y << ")" << endl << endl;
    }
}

int main() {
    int numPoints, k;

    cout << "Enter the number of data points: ";
    cin >> numPoints;
    cout << "Enter the number of clusters: ";
    cin >> k;

    // Generate random data points
    vector<Point> points = generateRandomData(numPoints);

    auto start = chrono::high_resolution_clock::now(); // Start time

    // Run k-means with 200 iterations
    kMeansClustering(&points, 200, k);

    auto end = chrono::high_resolution_clock::now(); // End time
    chrono::duration<double> duration = end - start;
    cout << "Total execution time: " << duration.count() << " seconds" << endl;

    cout << "Data points and cluster assignments have been saved to output_data_points.txt" << endl;
    cout << "Centroids have been saved to centroids.txt" << endl;

    return 0;
}
