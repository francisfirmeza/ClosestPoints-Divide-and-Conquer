// Francis Firmeza
// CS 320-02 P02

#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include "Point.h"
#include <algorithm>
#include <functional>

using namespace std;

pair<Point, Point> bruteForce(vector<Point>& arr, unsigned int left, unsigned int right)
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

template <typename Comparable>

void mergeSort(vector<Comparable>& a, vector<Comparable>& tmpArray, unsigned int left, unsigned int right,
    function<bool(const Point& p1, const Point& p2)> comparator)
{
    if (left < right)
    {
        int center = (left + right) / 2;

        mergeSort(a, tmpArray, left, center, comparator);
        mergeSort(a, tmpArray, center + 1, right, comparator);
        merge(a, tmpArray, left, center + 1, right, comparator);
    }
}

template <typename Comparable>

void merge(vector<Comparable>& a, vector<Comparable>& tmpArray, int leftPos, int rightPos, int rightEnd,
    function<bool(const Point& p1, const Point& p2)> comparator)
{
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    //Merge the two subarrays using comparator
    while (leftPos <= leftEnd && rightPos <= rightEnd)
    {
        if (comparator(a[leftPos], a[rightPos]))
        {
            tmpArray[tmpPos++] = std::move(a[leftPos++]);
        }
        else
        {
            tmpArray[tmpPos++] = std::move(a[rightPos++]);
        }
    }

    //Copy any remaining elements from the left subarray to tmpArray
    while (leftPos <= leftEnd) { tmpArray[tmpPos++] = std::move(a[leftPos++]); }
    //Copy any remaining elements from the right subarray to tmpArray
    while (rightPos <= rightEnd) { tmpArray[tmpPos++] = std::move(a[rightPos++]); }

    //Copy the sorted elements back to the original array

    for (int i = 0; i < numElements; ++i, --rightEnd)
    {
        a[rightEnd] = std::move(tmpArray[rightEnd]);
    }
}

pair<Point, Point> closestAcrossStrip(vector<Point>& strip, double d, pair<Point, Point> closestPair)
{
    if (strip.size() < 2)
    {
        return closestPair;
    }

    // Sort strip according to Y coordinates
    vector<Point> tmp(strip.size());
    mergeSort(strip, tmp, 0, strip.size() - 1, Point::CompareYCoordinate());

    // Find the smallest distance in the strip
    for (size_t i = 0; i < strip.size(); i++)
    {
        for (size_t j = i + 1; j < strip.size() && (strip[j].getY() - strip[i].getY() < d); j++)
        {
            double distance = strip[j].distance(strip[i]);
            if (distance < d)
            {
                d = distance;
                closestPair = make_pair(strip[i], strip[j]);
            }
        }
    }
    return closestPair;
}


pair<Point, Point> smallestDistance(vector<Point>& arr, size_t left, size_t right)
{
    //Base case
    if (right - left < 5)
    {
        return bruteForce(arr, left, right);
    }

    //Recursively find the smallest distances in both subarrays
    int mid = (left + right) / 2;
    pair<Point, Point> leftPointPair = smallestDistance(arr, left, mid);
    pair<Point, Point> rightPointPair = smallestDistance(arr, mid + 1, right);

    double dl = leftPointPair.first.distance(leftPointPair.second);
    double dr = rightPointPair.first.distance(rightPointPair.second);

    double d = min(dl, dr);

    //Find the closest pair from both sides
    pair<Point, Point> closestPair;
    if (dl < dr)
    {
        closestPair = leftPointPair;
    }
    else {
        closestPair = rightPointPair;
    }

    //Add points to strip that within d distance of midline
    vector<Point> strip;
    for (size_t i = left; i < right; i++)
    {
        if (abs(arr[i].getX() - arr[mid].getX()) < d)
        {
            strip.push_back(arr[i]);
        }
    }

    return closestAcrossStrip(strip, d, closestPair);
}

pair<Point, Point> closest(vector<Point> p)
{
    vector<Point> tmp = p;
    size_t n = p.size() - 1;
    mergeSort(p, tmp, 0, n, Point::CompareXCoordinate());
    return smallestDistance(tmp, 0, n);
}

double getDistance(pair<Point, Point>& points)
{
    return points.first.distance(points.second);
}

void printClosestPoints(pair<Point, Point>& p)
{
    cout << "Closest points are: (" << p.first.getX() << ", " << p.first.getY()
        << ") and ("
        << p.second.getX() << ", " << p.second.getY()
        << ") with distance = " << p.first.distance(p.second) << endl;
}

int main()
{
    ifstream file;
    string fileName;
    cout << "Enter Filename: ";
    cin >> fileName;
    file.open(fileName);

    if (fileName.length() >= 4 && fileName.substr(fileName.length() - 4) == ".txt")
    {
        ifstream file(fileName);
        if (!file)
        {
            cout << "Error opening the file" << endl;
            return 1;
        }
    }
    else
    {
        cout << "Invalid file extension, you should provide .txt files" << endl;
        return 1;
    }

    vector<Point> points;
    Point p;
    while (file >> p)
    {
        points.emplace_back(p);
    }
    file.close();

    // Check if the number of points read is greater than 1
    if (points.size() < 2)
    {
        cout << "Error: at least 2 points needed" << endl;
        return 1;
    }

    pair<Point, Point> closestPoints = closest(points);
    printClosestPoints(closestPoints);

    return 0;
}