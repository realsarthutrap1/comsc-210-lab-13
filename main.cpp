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

    Student original[MAX_STUDENTS];
    for (int i = 0; i < count; i++) {
        original[i] = students[i];
    }

    selectionSort(students, count);

    if (!writeGrades(students, count)) {
        return 1;
    }
    cout << "Sorted results written to 210-lab-13-grades-sorted.txt" << endl;

    printStatistics(original, count);
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

// selectionSort() sorts Student records by ID from low to high
void selectionSort(Student students[], int count) {
    for (int i = 0; i < count - 1; i++) {
        int smallest = i;
        for (int j = i + 1; j < count; j++) {
            if (students[j].id < students[smallest].id) {
                smallest = j;
            }
        }
        Student temp = students[i];
        students[i] = students[smallest];
        students[smallest] = temp;
    }
}

// writeGrades() writes the sorted records in the original file format
bool writeGrades(const Student students[], int count) {
    ofstream output("210-lab-13-grades-sorted.txt");
    if (!output) {
        cout << "Could not write 210-lab-13-grades-sorted.txt" << endl;
        return false;
    }

    for (int i = 0; i < count; i++) {
        output << students[i].id << " " << fixed << setprecision(1)
               << students[i].score << endl;
    }
    return true;
}

// printStatistics() prints the score summary from the original records
void printStatistics(const Student students[], int count) {
    double minScore = students[0].score;
    double maxScore = students[0].score;
    long minID = students[0].id;
    long maxID = students[0].id;
    double total = 0;

    Student byScore[MAX_STUDENTS];
    for (int i = 0; i < count; i++) {
        byScore[i] = students[i];
        total += students[i].score;
        if (students[i].score < minScore) {
            minScore = students[i].score;
            minID = students[i].id;
        }
        if (students[i].score > maxScore) {
            maxScore = students[i].score;
            maxID = students[i].id;
        }
    }

    for (int i = 0; i < count - 1; i++) {
        int smallest = i;
        for (int j = i + 1; j < count; j++) {
            if (byScore[j].score < byScore[smallest].score) {
                smallest = j;
            }
        }
        Student temp = byScore[i];
        byScore[i] = byScore[smallest];
        byScore[smallest] = temp;
    }

    double mean = total / count;
    double median = (byScore[(count - 1) / 2].score + byScore[count / 2].score) / 2;
    long medianID = students[0].id;
    for (int i = 0; i < count; i++) {
        if (students[i].score == median) {
            medianID = students[i].id;
            break;
        }
    }

    double squaredDifference = 0;
    for (int i = 0; i < count; i++) {
        double difference = students[i].score - mean;
        squaredDifference += difference * difference;
    }

    cout << endl << "--- Summary Statistics ---" << endl;
    cout << "Minimum Score: " << minScore << " (Student ID: " << minID << ")" << endl;
    cout << "Maximum Score: " << maxScore << " (Student ID: " << maxID << ")" << endl;
    cout << "Mean Score: " << mean << endl;
    cout << "Median Score: " << median << " (Student ID: " << medianID << ")" << endl;
    cout << "Standard Deviation: " << sqrt(squaredDifference / count) << endl;
}
