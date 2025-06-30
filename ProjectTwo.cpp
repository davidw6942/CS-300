// ProjectTwo.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Name        : ProjectTwo.cpp
// Author      : David Wasson
// Version     : 1.0
// Southern New Hampshire University
// Date: 6/29/2025
// Hash table for sorting and printing course information and their prerequisites by reading a csv file

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Structure for course info
struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;
};

// Hash table storing courses and using courseNumber as a key
unordered_map<string, Course> courseTable;

// Function to read and load courses from CSV file
void loadCourses(string fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "File coudn't be opened." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        Course course;
        string token;
        stringstream ss(line);

        // Get the name and number of the course
        getline(ss, course.courseNumber, ',');
        getline(ss, course.courseName, ',');

        // Get the prerequisites if any for the course
        while (getline(ss, token, ',')) {
            course.prerequisites.push_back(token);
        }

        // Add couirse to hash table
        courseTable[course.courseNumber] = course;
    }

    file.close();
    cout << "Courses loaded successfully." << endl;
}

// Function to print all courses alphanumerically by their course number
void printCourseList() {
    vector<Course> courseList;

    // Get a copy of courses from the hash table to sort
    for (auto it = courseTable.begin(); it != courseTable.end(); ++it) {
        courseList.push_back(it->second);
    }

    // Sort courses by their courseNumber
    sort(courseList.begin(), courseList.end(), [](Course a, Course b) {
        return a.courseNumber < b.courseNumber;
        });

    // Print the sorted courses
    for (int i = 0; i < courseList.size(); ++i) {
        cout << courseList[i].courseNumber << ": " << courseList[i].courseName << endl;
    }
}

// Function that prompts a user for course number and prints course information including prerequisites
void printCourseInfo() {
    string courseNum;
    cout << "Enter course number: ";
    cin >> courseNum;

    // Look up course in hash table
    if (courseTable.find(courseNum) == courseTable.end()) {
        cout << "Course not found." << endl;
        return;
    }

    Course course = courseTable[courseNum];

    // Print course title from hash table
    cout << course.courseNumber << ": " << course.courseName << endl;

    // Print prerequisites
    if (course.prerequisites.size() == 0) {
        cout << "Prerequisites: None" << endl;
    }
    else {
        cout << "Prerequisites:" << endl;
        for (int i = 0; i < course.prerequisites.size(); ++i) {
            string prereqNum = course.prerequisites[i];
            if (courseTable.find(prereqNum) != courseTable.end()) {
                Course prereq = courseTable[prereqNum];
                cout << "  " << prereq.courseNumber << ": " << prereq.courseName << endl;
            }
            else {
                cout << "  " << prereqNum << " (Not found in system)" << endl;
            }
        }
    }
}

// Main program with menu
int main() {
    int choice;
    string fileName;

    do {
        cout << endl;
        cout << "Menu:" << endl;
        cout << "  1. Load Course Data File" << endl;
        cout << "  2. Print Alphanumeric Course List" << endl;
        cout << "  3. Print Course Info and prerequisites" << endl;
        cout << "  9. Exit the program" << endl;
        cout << "> ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter file name: ";
            cin >> fileName;
            loadCourses(fileName);
        }
        else if (choice == 2) {
            printCourseList();
        }
        else if (choice == 3) {
            printCourseInfo();
        }
        else if (choice == 9) {
            cout << "Goodbye!" << endl;
        }
        else {
            cout << "Input invalid. Try again." << endl;
        }
    } while (choice != 9);

    return 0;
}

