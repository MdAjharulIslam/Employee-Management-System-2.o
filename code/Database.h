#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Employee.h"

using namespace std;

class Database {
public:
    // Load employees from a file into an array
    static Employee* loadEmployees(const string& filename, int& count) {
        ifstream file(filename);
        string line;
        count = 0;
        
        // Ensure the file is open
        if (!file.is_open()) {
            cerr << "Error opening file for reading: " << filename << endl;
            return nullptr;
        }

        // Count how many employees are in the file
        while (getline(file, line)) {
            count++;
        }
        
        file.clear();
        file.seekg(0, ios::beg);  // Go back to the beginning of the file
        
        // Dynamically allocate array for employees
        Employee* employees = new Employee[count];
        
        int index = 0;
        while (getline(file, line)) {
            stringstream ss(line);
            int id;
            string name, department, position;
            double salary;
            bool isManager;

            ss >> id;
            ss.ignore(); // Ignore the space after the ID
            getline(ss, name, ',');
            getline(ss, department, ',');
            getline(ss, position, ',');
            ss >> salary >> isManager;

            employees[index] = Employee(id, name, department, position, salary, isManager);
            index++;
        }

        file.close();
        return employees;
    }

    // Save employees to a file
    static bool saveEmployees(const string& filename, Employee* employees, int count) {
        ofstream file(filename);
        
        // Ensure the file is open
        if (!file.is_open()) {
            cerr << "Error opening file for writing: " << filename << endl;
            return false;  // Return false if the file can't be opened
        }

        for (int i = 0; i < count; i++) {
            file << employees[i].id << ", " << employees[i].name << ", " 
                 << employees[i].department << ", " << employees[i].position << ", " 
                 << employees[i].salary << ", " << employees[i].isManager << endl;
        }

        file.close();
        return true;  // Return true if employees are successfully saved
    }

    // Search employees by keyword
    static Employee* searchEmployeesByKeyword(Employee* employees, int count, const string& keyword, int& foundCount) {
        Employee* foundEmployees = new Employee[count];  // Temporary array for storing found employees
        foundCount = 0;

        for (int i = 0; i < count; i++) {
            if (employees[i].name.find(keyword) != string::npos || employees[i].department.find(keyword) != string::npos) {
                foundEmployees[foundCount] = employees[i];
                foundCount++;
            }
        }

        return foundEmployees;
    }

    // Find employee by ID
    static Employee* findEmployeeByID(Employee* employees, int count, int id) {
        for (int i = 0; i < count; i++) {
            if (employees[i].id == id) {
                return &employees[i];  // Return the pointer to the employee
            }
        }
        return nullptr;  // Return nullptr if not found
    }
};

#endif
