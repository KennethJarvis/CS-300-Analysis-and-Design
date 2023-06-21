#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
struct Course { // Structure course
    string courseNum;
    string name;
    vector<string> prereq;
};

// Split string to list of strings
vector<string> token(string s, string del = " ") {
    vector<string> stringArray;
    int start = 0;
    int end = s.find(del);
    while (end != -1) {
        stringArray.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    stringArray.push_back(s.substr(start, end - start));
    return stringArray;
}

// Load file and store the details into list
vector<Course> LoadDataStructure() {
    // Create an object of iftsream class
    ifstream fin("ABCU_Advising_Program_Input.txt", ios::in);
    vector<Course> courses;
    string line;
    // Infinite loop
    while (1) {
        getline(fin, line);
        // If end of file is reached then break the loop
        if (line == "-1")
            break;
        Course course;
        // Get information separated by commas
        vector<string> tokenInfo = token(line, ",");
        // Store information
        course.courseNum = tokenInfo[0];
        course.name = tokenInfo[1];
        // If prerequisite then store
        for (int i = 2; i < tokenInfo.size(); i++) {
            course.prereq.push_back(tokenInfo[i]);
        }
        // Append the course into list
        courses.push_back(course);
    }
    // Close the file
    fin.close();
    // Return the list of courses
    return courses;
}

// printing course information of given course in proper format
void printCourse(Course course) {
    string courseNumber = course.courseNum;
    string name = course.name;
    vector<string> prerequisites = course.prereq;
    cout << courseNumber << ", " << name << endl;
    cout << "Prerequisites: ";
    for (int i = 0; i < prerequisites.size(); i++) {
        cout << prerequisites[i];
        if (i < prerequisites.size() -1) { // No trailing commas
            cout << ", ";
        }
    }
    cout << "\n";
}

// Option two list
void printCourse2(Course course) { // Option two list
    string courseNumber = course.courseNum;
    string name = course.name;
    cout << courseNumber << ", " << name << endl;
}

// Printing course information 
void printCourseList(vector<Course> courses) {
    int n = courses.size();
    cout << "Here is a sample schedule:\n\n";
    // Sort the list
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (courses[j].courseNum > courses[j + 1].courseNum) {
                swap(courses[j + 1], courses[j]);
            }
        }
    }
    // Print all course information
    for (int i = 0; i < n; i++) {
        printCourse2(courses[i]);
    }
}

// search data for user entered course number
void searchCourse(vector<Course> courses) {
    int n = courses.size();
    string courseNumber;
    int f = 0;
    cout << "What course do you want to know about? ";
    cin >> courseNumber;
    for (string::iterator i = courseNumber.begin(); i < courseNumber.end(); i++) { // Change anylowercase to uppercase
        *i = toupper(*i);
    }
    for (int i = 0; i < n; i++) {
        // If course found then print
        if (courses[i].courseNum == courseNumber) {
            f = 1;
            printCourse(courses[i]);
            break;
        }
    }
    // if course with given course name not found then print error message
    if (f == 0) {
        cout << "Course not found.\n";
    }
}

int main(int argc, char** argv) {
    vector<Course> courses;
    // Menu
    cout << "Welcome to the course planner.\n";
    int choice;
    do {
        cout << endl;
        cout << "   1. Load Data Structure\n"; // Refresh Menu
        cout << "   2. Print Course List\n";
        cout << "   3. Print Course\n";
        cout << "   4. Exit\n";
        cout << "\nWhat would you like to do? ";
        cin >> choice; // Enter choice
        switch (choice) {
        case 1: courses = LoadDataStructure(); break;
        case 2: printCourseList(courses); break;
        case 3: searchCourse(courses); break;
        case 4: cout << "Thank you for using the course planner!\n"; break;
        default: cout << choice << " is not a valid option.\n";
        }
        
    } while (choice != 4);
    return 0;
}