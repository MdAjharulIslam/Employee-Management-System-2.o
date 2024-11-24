#include <iostream>
#include <string>
#include "Employee.h"
#include "Database.h"
#include <cstdlib>  
#include <fstream>
using namespace std;

// Function Prototypes
void displayMenu();
void displayEmployeeStatistics(Employee* employees, int count);
void handleSort(Employee* employees, int count);
void handleEmployeeAddition(Employee*& employees, int& count);
void handleEmployeeSearch(Employee* employees, int count);
void handleEmployeeUpdate(Employee* employees, int count);
void handleEmployeeDeletion(Employee*& employees, int& count);
void backupData(Employee* employees, int count);
void restoreData(Employee*& employees, int& count);

int main() {
    int count = 0;
    Employee* employees = Database::loadEmployees("employees.txt", count);

    int choice;
    do {
        system("cls");  // Clears the screen before displaying the menu
        displayMenu();
        cin >> choice;
        cin.ignore();  // To clear the newline character left in the buffer

        switch (choice) {
            case 1:
                system("cls");
                cout << "\n--- Displaying All Employees ---\n";
                for (int i = 0; i < count; ++i) {
                    employees[i].display();
                }
                break;
            case 2:
                handleEmployeeAddition(employees, count);
                break;
            case 3:
                handleEmployeeSearch(employees, count);
                break;
            case 4:
                handleEmployeeUpdate(employees, count);
                break;
            case 5:
                handleSort(employees, count);
                break;
            case 6:
                displayEmployeeStatistics(employees, count);
                break;
            case 7:
                handleEmployeeDeletion(employees, count);
                break;
            case 8:
                backupData(employees, count);
                break;
            case 9:
                restoreData(employees, count);
                break;
            case 10:
                system("cls");
                cout << "Exiting the system.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }

        if (choice != 10) {
            cout << "\nPress Enter to return to the menu...";
            cin.get();  // Wait for Enter key specifically
        }

    } while (choice != 10);

    delete[] employees;  // Free the dynamically allocated memory
    return 0;
}

void displayMenu() {
    cout << "\nAdvanced Employee Management System\n";
    cout << "1. Display All Employees\n";
    cout << "2. Add New Employee\n";
    cout << "3. Search Employees\n";
    cout << "4. Update Employee\n";
    cout << "5. Sort Employees\n";
    cout << "6. Display Statistics\n";
    cout << "7. Delete Employees\n";
    cout << "8. Backup Data\n";
    cout << "9. Restore Data\n";
    cout << "10. Exit\n";
    cout << "Enter your choice: ";
}

void handleEmployeeAddition(Employee*& employees, int& count) {
    system("cls");  // Clear screen before adding employee
    cout << "\n--- Add New Employee ---\n";
    int id;
    string name, department, position;
    double salary;
    bool isManager;

    cout << "Enter Employee ID: ";
    cin >> id;
    cin.ignore();  // Clear leftover newline character from buffer
    cout << "Enter Employee Name: ";
    getline(cin, name);
    cout << "Enter Department: ";
    getline(cin, department);
    cout << "Enter Position: ";
    getline(cin, position);
    cout << "Enter Salary: ";
    cin >> salary;
    cin.ignore();  // Clear leftover newline character from buffer
    cout << "Is this employee a Manager? (1 for Yes, 0 for No): ";
    cin >> isManager;
    cin.ignore();  // Clear leftover newline character from buffer

    // Add new employee to the array
    Employee* temp = new Employee[count + 1];
    for (int i = 0; i < count; ++i) {
        temp[i] = employees[i];
    }
    temp[count] = Employee(id, name, department, position, salary, isManager);

    delete[] employees;  // Delete old array
    employees = temp;    // Update pointer
    count++;

    Database::saveEmployees("employees.txt", employees, count);
    cout << "Employee added successfully.\n";

    cout << "\nPress Enter to return to the menu...";
    cin.get();  // Wait for Enter key specifically
}

void handleEmployeeSearch(Employee* employees, int count) {
    system("cls");  // Clear screen before search
    cout << "\n--- Search Employees ---\n";
    string keyword;
    cout << "Enter search keyword (name or department): ";
    cin.ignore();  // Clear any leftover newline
    getline(cin, keyword);

    int foundCount = 0;
    Employee* foundEmployees = Database::searchEmployeesByKeyword(employees, count, keyword, foundCount);
    if (foundCount == 0) {
        cout << "No employees found.\n";
    } else {
        for (int i = 0; i < foundCount; ++i) {
            foundEmployees[i].display();
        }
        delete[] foundEmployees;  // Free memory after use
    }

    cout << "\nPress Enter to return to the menu...";
    cin.get();  // Wait for Enter key specifically
}

void handleEmployeeUpdate(Employee* employees, int count) {
    system("cls");  // Clear screen before updating employee
    cout << "\n--- Update Employee Information ---\n";
    int id;
    cout << "Enter Employee ID to update: ";
    cin >> id;
    cin.ignore();  // Clear any leftover newline

    Employee* emp = Database::findEmployeeByID(employees, count, id);
    if (emp) {
        string name, department, position;
        double salary;
        bool isManager;

        cout << "Enter new name (leave blank to keep current): ";
        getline(cin, name);
        cout << "Enter new department (leave blank to keep current): ";
        getline(cin, department);
        cout << "Enter new position (leave blank to keep current): ";
        getline(cin, position);
        cout << "Enter new salary (0 to keep current): ";
        cin >> salary;
        cin.ignore();  // Clear any leftover newline
        cout << "Is this employee a Manager? (1 for Yes, 0 for No): ";
        cin >> isManager;
        cin.ignore();  // Clear any leftover newline

        if (!name.empty()) emp->name = name;
        if (!department.empty()) emp->department = department;
        if (!position.empty()) emp->position = position;
        if (salary > 0) emp->salary = salary;
        emp->isManager = isManager;

        Database::saveEmployees("employees.txt", employees, count);
        cout << "Employee updated successfully.\n";
    } else {
        cout << "Employee not found.\n";
    }

    cout << "\nPress Enter to return to the menu...";
    cin.get();  // Wait for Enter key specifically
}

void handleEmployeeDeletion(Employee*& employees, int& count) {
    system("cls");  // Clear screen before deleting employee
    cout << "\n--- Delete Employee ---\n";
    int id;
    cout << "Enter Employee ID to delete: ";
    cin >> id;
    cin.ignore();  // Clear any leftover newline

    int index = -1;
    for (int i = 0; i < count; ++i) {
        if (employees[i].id == id) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        // Delete employee
        Employee* temp = new Employee[count - 1];
        for (int i = 0, j = 0; i < count; ++i) {
            if (i != index) {
                temp[j++] = employees[i];
            }
        }

        delete[] employees;
        employees = temp;
        count--;

        Database::saveEmployees("employees.txt", employees, count);
        cout << "Employee deleted successfully.\n";
    } else {
        cout << "Employee not found.\n";
    }

    cout << "\nPress Enter to return to the menu...";
    cin.get();  // Wait for Enter key specifically
}

void displayEmployeeStatistics(Employee* employees, int count) {
    system("cls");  // Clear screen before displaying statistics
    cout << "\n--- Employee Statistics ---\n";
    double totalSalary = 0;
    int managerCount = 0;

    for (int i = 0; i < count; ++i) {
        totalSalary += employees[i].salary;
        if (employees[i].isManager) {
            managerCount++;
        }
    }

    double averageSalary = count > 0 ? totalSalary / count : 0;
    cout << "Total Employees: " << count << endl;
    cout << "Average Salary: " << averageSalary << endl;
    cout << "Number of Managers: " << managerCount << endl;

    cout << "\nPress Enter to return to the menu...";
    cin.get();  // Wait for Enter key specifically
}

void handleSort(Employee* employees, int count) {
    system("cls");  // Clear screen before sorting
    cout << "\n--- Sorting Employees ---\n";
    int sortOption;
    cout << "1. Sort by Salary\n";
    cout << "2. Sort by Name\n";
    cout << "Enter your choice: ";
    cin >> sortOption;

    switch (sortOption) {
        case 1:
            // Sort by salary
            for (int i = 0; i < count - 1; ++i) {
                for (int j = i + 1; j < count; ++j) {
                    if (employees[i].salary > employees[j].salary) {
                        swap(employees[i], employees[j]);
                    }
                }
            }
            cout << "Employees sorted by salary.\n";
            break;
        case 2:
            // Sort by name
            for (int i = 0; i < count - 1; ++i) {
                for (int j = i + 1; j < count; ++j) {
                    if (employees[i].name > employees[j].name) {
                        swap(employees[i], employees[j]);
                    }
                }
            }
            cout << "Employees sorted by name.\n";
            break;
        default:
            cout << "Invalid option.\n";
    }

    cout << "\nPress Enter to return to the menu...";
    cin.get();  // Wait for Enter key specifically
}

void backupData(Employee* employees, int count) {
    system("cls");  // Clear screen before backup
    cout << "\n--- Backup Data ---\n";
    
    // Save employee data to backup file
    if (Database::saveEmployees("backup_employees.txt", employees, count)) {
        cout << "Data backed up successfully.\n";
    } else {
        cout << "Failed to back up data.\n";
    }

    cout << "\nPress Enter to return to the menu...";
    cin.get();  // Wait for Enter key specifically
}

void restoreData(Employee*& employees, int& count) {
    system("cls");  // Clear screen before restore
    cout << "\n--- Restore Data ---\n";

    // Load employee data from the backup file
    Employee* restoredEmployees = Database::loadEmployees("backup_employees.txt", count);
    
    if (restoredEmployees) {
        // Delete the old employee data (if it exists)
        delete[] employees;

        // Point employees to the restored employee array
        employees = restoredEmployees;

        // Save the restored data back to the main employee file
        if (Database::saveEmployees("employees.txt", employees, count)) {
            cout << "Data restored and saved successfully.\n";
        } else {
            cout << "Failed to save restored data to the main file.\n";
        }
    } else {
        cout << "Failed to restore data. Please check the backup file.\n";
    }

    cout << "\nPress Enter to return to the menu...";
    cin.get();  // Wait for Enter key specifically
}
