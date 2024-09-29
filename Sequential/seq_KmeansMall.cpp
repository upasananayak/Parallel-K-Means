#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include<algorithm>
#include<chrono>
using namespace std;

struct Point {
    double x, y;     // coordinates
    int cluster;     // no default cluster
    double minDist;  // default infinite distance to nearest cluster

    Point() : x(0.0), y(0.0), cluster(-1), minDist(__DBL_MAX__) {}
    Point(double x, double y) : x(x), y(y), cluster(-1), minDist(__DBL_MAX__) {}

    //Computes the (square) euclidean distance between this point and another

    double distance(Point p) {
        return (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y);
    }
};

vector<Point> readcsv(const string &filename) {
    vector<Point> points;
    string line;
    ifstream file(filename);

    // Skip the header row
    getline(file, line);

    while (getline(file, line)) {
        stringstream lineStream(line);
        string bit;
        double income, score;

        // Skip CustomerID and Genre, only get Annual Income and Spending Score
        getline(lineStream, bit, ',');  // Skip CustomerID
        getline(lineStream, bit, ',');  // Skip Genre
        getline(lineStream, bit, ',');  // Skip Age
        getline(lineStream, bit, ',');  // Get Annual Income
        income = stof(bit);
        getline(lineStream, bit, '\n'); // Get Spending Score
        score = stof(bit);

        points.push_back(Point(income, score));
    }
    return points;
    
}

/*
points - pointer to vector of points
epochs - number of k means iterations
k - the number of initial centroids
*/
void kMeansClustering(vector<Point>* points, int epochs, int k) {
    int n = points->size();

    // Randomly initialise centroids
    vector<Point> centroids;
    srand(time(0));
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

    // Write to csv
    ofstream myfile("output1.csv");
    myfile << "x,y,c" << endl;
    for (const auto &p : *points) {
        myfile << p.x << "," << p.y << "," << p.cluster << endl;
    }
    myfile.close();

    for (int j = 0; j < k; ++j) {
        cout << "Cluster " << j << ": " <<endl;
        cout << "Number of points: " << count_if(points->begin(), points->end(), [j](Point p) { return p.cluster == j; })<<"\t";
        cout << "Centroid: (" << centroids[j].x << ", " << centroids[j].y << ")" << endl<<endl;
    }
}

    
int main() {
    vector<Point> points = readcsv("Mall_Customers.csv");

    auto start = chrono::high_resolution_clock::now(); // Start time

    // Run k-means with 200 iterations and for 5 clusters
    kMeansClustering(&points, 200, 5);

    auto end = chrono::high_resolution_clock::now(); // End time
    chrono::duration<double> duration = end - start;
    cout << "Total execution time: " << duration.count() << " seconds" << endl;

}
