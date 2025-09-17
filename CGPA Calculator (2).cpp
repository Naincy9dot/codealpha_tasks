//CGPA CALCULATOR 
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Function to convert letter grade to grade points
double gradeToPoint(string grade) {
    if (grade == "A" || grade == "a") return 10.0;
    if (grade == "A-" || grade == "a-") return 9.0;
    if (grade == "B" || grade == "b") return 8.0;
    if (grade == "B-" || grade == "b-") return 7.0;
    if (grade == "C" || grade == "c") return 6.0;
    if (grade == "C-" || grade == "c-") return 5.0;
    if (grade == "D" || grade == "d") return 4.0;
    if (grade == "F" || grade == "f") return 0.0;
    return -1; // invalid
}

int main() {
    int numCourses;
    cout << "Enter number of courses: ";
    cin >> numCourses;

    vector<string> courseName(numCourses);
    vector<string> grade(numCourses);
    vector<int> creditHours(numCourses);

    double totalCredits = 0, totalGradePoints = 0;

    for (int i = 0; i < numCourses; i++) {
        cout << "\nEnter name of course " << i + 1 << ": ";
        cin >> courseName[i];
        cout << "Enter grade (A, A-, B, B-, C, C-, D, F): ";
        cin >> grade[i];
        cout << "Enter credit hours: ";
        cin >> creditHours[i];

        double gp = gradeToPoint(grade[i]);
        if (gp == -1) {
            cout << "Invalid grade entered! Try again.\n";
            i--;
            continue;
        }

        totalCredits += creditHours[i];
        totalGradePoints += gp * creditHours[i];
    }

    double cgpa = totalGradePoints / totalCredits;

    cout << fixed << setprecision(2);
    cout << "\n--- Course Details ---\n";
    for (int i = 0; i < numCourses; i++) {
        cout << courseName[i] << " | Grade: " << grade[i]
             << " | Credits: " << creditHours[i] << endl;
    }

    cout << "\nTotal Credits: " << totalCredits;
    cout << "\nFinal CGPA: " << cgpa << endl;

    return 0;
}