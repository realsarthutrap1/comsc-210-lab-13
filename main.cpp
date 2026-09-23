// COMSC-210 | Lab 13 | Sarthak Pani
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;

const int MAX_STUDENTS = 200;

struct Student {
    long id;
    double score;
};

int readGrades(Student students[], int maxStudents);
void selectionSort(Student students[], int count);
bool writeGrades(const Student students[], int count);
void printStatistics(const Student students[], int count);

int main() {
    return 0;
}
