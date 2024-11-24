#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <iostream>

using namespace std;

class Employee {
public:
    int id;
    string name;
    string department;
    string position;
    double salary;
    bool isManager;

    // Constructor
    Employee(int _id = 0, const string& _name = "", const string& _department = "",
             const string& _position = "", double _salary = 0.0, bool _isManager = false)
        : id(_id), name(_name), department(_department), position(_position),
          salary(_salary), isManager(_isManager) {}

    // Display employee information
    void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Department: " << department
             << ", Position: " << position << ", Salary: " << salary
             << ", Manager: " << (isManager ? "Yes" : "No") << endl;
    }
};

#endif
