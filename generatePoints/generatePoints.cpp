// Francis Firmeza
// CS 320-02 P02

#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector>
using namespace std;

vector<double> generateRandomPoints(int numPoints)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0.0, 10000.0);
    vector<double> points;
    for (int i = 0; i < numPoints; ++i)
    {
        points.push_back(dis(gen));
        points.push_back(dis(gen));
    }
    return points;
}

void writePointsToFile(const vector<double>& points, const string& filename)
{
    ofstream outputFile(filename);
    if (outputFile.is_open())
    {
        for (size_t i = 0; i < points.size(); i += 2)
        {
            outputFile << points[i] << " " << points[i + 1] << endl;
        }
        outputFile.close();
        cout << "File \"" << filename << "\" has been created with "
            << points.size() / 2 << " pairs of random points" << endl;
    }
    else
    {
        cout << "Unable to create file \"" << filename << "\"" << endl;
    }
}

int main()
{
    int numPoints;
    cout << "Enter the number of pairs of points: ";
    cin >> numPoints;

    if (numPoints <= 0)
    {
        cout << "Error: enter a positive integer" << endl;
        return 1;
    }

    vector<double> points = generateRandomPoints(numPoints);
    string filename = "file" + to_string(numPoints) + ".txt";
    writePointsToFile(points, filename);
    return 0;
}