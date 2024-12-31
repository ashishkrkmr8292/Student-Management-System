#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>

using namespace std;

// Structure to hold student information
struct Student {
    string name;
    int rollNumber;
    string faculty;
    int attendance; // Attendance percentage
    char grade;     // Grade

    void display() const {
        cout << "Name: " << name << ", Roll No: " << rollNumber 
             << ", Faculty: " << faculty << ", Attendance: " 
             << attendance << "%, Grade: " << grade << endl;
    }
};

// Global vector to hold student records
vector<Student> students;

// Function declarations
void addStudent(const string& name, int rollNumber, const string& faculty, int attendance, char grade);
void displayStudents();
void updateAttendance(int rollNumber, int attendance);
void updateGrade(int rollNumber, char grade);
void saveToFile();
void loadFromFile();

int main() {
    loadFromFile(); // Load existing data

    int choice;
    string name, faculty;
    int rollNumber;
    int attendance;
    char grade;

    while (true) {
        cout << "\n1. Add Student\n2. Display Students\n3. Update Attendance\n4. Update Grade\n5. Save and Exit\n";
        cout << "Enter your choice: ";

        // Check for valid input
        while (!(cin >> choice)) { // Loop until valid input is entered
            cout << "Invalid input. Please enter a number between 1 and 5." << endl;
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
        }

        // Clear the input buffer to avoid issues with getline
        cin.ignore(); // This will ignore the newline character left in the buffer

        switch (choice) {
            case 1:
                cout << "Enter student name: ";
                getline(cin, name); // Use getline to allow spaces in names
                cout << "Enter roll number: ";
                cin >> rollNumber;
                cin.ignore(); // Ignore the newline character
                cout << "Enter faculty: ";
                getline(cin, faculty); // Allow spaces in faculty names
                cout << "Enter attendance percentage: ";
                cin >> attendance; // Prompt for attendance
                cout << "Enter grade: ";
                cin >> grade; // Prompt for grade
                addStudent(name, rollNumber, faculty, attendance, grade); // Add student
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                cout << "Enter roll number to update attendance: ";
                cin >> rollNumber;
                cout << "Enter new attendance percentage: ";
                cin >> attendance;
                updateAttendance(rollNumber, attendance);
                break;
            case 4:
                cout << "Enter roll number to update grade: ";
                cin >> rollNumber;
                cout << "Enter new grade: ";
                cin >> grade;
                updateGrade(rollNumber, grade);
                break;
            case 5:
                saveToFile(); // Save before exiting
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}

void addStudent(const string& name, int rollNumber, const string& faculty, int attendance, char grade) {
    Student newStudent = {name, rollNumber, faculty, attendance, grade};
    students.push_back(newStudent);
}

void displayStudents() {
    for (const auto& student : students) {
        student.display();
    }
}

void updateAttendance(int rollNumber, int attendance) {
    for (auto& student : students) {
        if (student.rollNumber == rollNumber) {
            student.attendance = attendance;
            cout << "Attendance updated for Roll No: " << rollNumber << endl;
            return;
        }
    }
    cout << "Student with Roll No: " << rollNumber << " not found." << endl;
}

void updateGrade(int rollNumber, char grade) {
    for (auto& student : students) {
        if (student.rollNumber == rollNumber) {
            student.grade = grade;
            cout << "Grade updated for Roll No: " << rollNumber << endl;
            return;
        }
    }
    cout << "Student with Roll No: " << rollNumber << " not found." << endl;
}

void saveToFile() {
    ofstream file("students.txt");
    for (const auto& student : students) {
        file << student.name << "," << student.rollNumber << "," 
             << student.faculty << "," << student.attendance << "," 
             << student.grade << endl;
    }
    file.close();
    cout << "Data saved to file." << endl;
}

void loadFromFile() {
    ifstream file("students.txt");
    if (!file) {
        cout << "No existing data found." << endl;
        return;
    }

    Student student;
    while (getline(file, student.name, ',') &&
           file >> student.rollNumber &&
           file.ignore() &&
           getline(file, student.faculty, ',') &&
           file >> student.attendance &&
           file.ignore() &&
           file >> student.grade) {
        students.push_back(student);
    }
    file.close();
    cout << "Data loaded from file." << endl;
}