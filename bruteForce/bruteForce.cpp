// Francis Firmeza
// CS 320-02 P02

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include "Point.h"
#include <algorithm>
#include <functional>

using namespace std;

pair<Point, Point> bruteForce(vector<Point>& arr, size_t left, size_t right)
{
    pair<Point, Point> result;
    double min = DBL_MAX;

    for (unsigned int i = left; i < right; i++)
        for (unsigned int j = i + 1; j < right; j++)
        {
            if (arr[i].distance(arr[j]) < min)
            {
                min = arr[i].distance(arr[j]);
                result = make_pair(arr[i], arr[j]);
            }
        }

    return result;
}

void testBruteForce() {
    vector<Point> points = {
        Point(1, 2), Point(3, 4), Point(5, 6),
        Point(7, 8), Point(2, 1), Point(4, 3)
    };

    size_t left = 0;
    size_t right = points.size();

    pair<Point, Point> result = bruteForce(points, left, right);

    cout << "The closest pair of points is: ("
        << result.first.getX() << ", " << result.first.getY()
        << ") and (" << result.second.getX() << ", "
        << result.second.getY() << ")\n";
}

int main() {
    testBruteForce();
    return 0;
}