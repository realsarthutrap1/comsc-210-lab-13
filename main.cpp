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
    Student students[MAX_STUDENTS];
    int count = readGrades(students, MAX_STUDENTS);
    if (count <= 0) {
        return 1;
    }

    cout << "Read " << count << " student records" << endl;
    return 0;
}

// readGrades() reads the file into the Student array
// returns: number of records read, or -1 on an error
int readGrades(Student students[], int maxStudents) {
    ifstream input("210-lab-13-grades.txt");
    if (!input) {
        cout << "Could not open 210-lab-13-grades.txt" << endl;
        return -1;
    }

    int count = 0;
    Student next;
    while (input >> next.id >> next.score) {
        if (count == maxStudents) {
            cout << "Too many student records" << endl;
            return -1;
        }
        students[count] = next;
        count++;
    }

    if (!input.eof()) {
        cout << "Invalid record in 210-lab-13-grades.txt" << endl;
        return -1;
    }
    return count;
}
