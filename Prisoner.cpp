#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <vector>

using namespace std;

class Prisoner {
private:
    string firstName;
    string lastName;
    string gender;
    int cellNumber;
    int age;
    double height;
    string eyeColor;
    string crime;
    int punishmentMonths;

public:
    Prisoner(string fname, string lname, string g, int cell, int a, double h, string eye, string c, int p)
        : firstName(fname), lastName(lname), gender(g), cellNumber(cell), age(a), height(h), eyeColor(eye), crime(c), punishmentMonths(p) {}

    void displayDetails() {
        cout << "Name: " << firstName << " " << lastName << endl;
        cout << "Cell Number: " << cellNumber << endl;
        cout << "Age: " << age << endl;
        cout << "Gender: " << gender << endl;
        cout << "Height: " << height << " feet" << endl;
        cout << "Eye Color: " << eyeColor << endl;
        cout << "Crime: " << crime << endl;
        cout << "Punishment Duration: " << punishmentMonths << " months" << endl;
    }

    bool readyForRelease() {
        return punishmentMonths <= 0;
    }

    int getCellNumber() {
        return cellNumber;
    }
};

class Prison {
private:
    static const int MAX_PRISONERS = 20;
    vector<Prisoner*> prisoners;

public:
    ~Prison() {
        for (Prisoner* p : prisoners)
            delete p;
    }

    void addPrisoner();
    void displayPrisoners();
    void updateAttendance();
    void releasePrisoner();
    void searchPrisoner();
    void showMenu();
    void displayTime();
};

void Prison::addPrisoner() {
    if (prisoners.size() >= MAX_PRISONERS) {
        cout << "Prison is full! Cannot add more prisoners." << endl;
        return;
    }

    string fname, lname, gender, eye, crime;
    int cell, age, punishment;
    double height;

    cout << "Enter first name: ";
    cin >> fname;
    cout << "Enter last name: ";
    cin >> lname;
    cout << "Enter gender: ";
    cin >> gender;
    cout << "Enter age: ";
    cin >> age;
    cout << "Enter height (in feet): ";
    cin >> height;
    cout << "Enter eye color: ";
    cin >> eye;
    cout << "Enter crime: ";
    cin >> crime;
    cout << "Enter punishment duration (in months): ";
    cin >> punishment;

    prisoners.push_back(new Prisoner(fname, lname, gender, 1001 + prisoners.size(), age, height, eye, crime, punishment));
}

void Prison::displayPrisoners() {
    if (prisoners.empty()) {
        cout << "No prisoners in the system." << endl;
        return;
    }

    cout << "Prisoner Details:" << endl;
    cout << "-------------------------------------------" << endl;
    for (Prisoner* p : prisoners) {
        p->displayDetails();
        cout << "-------------------------------------------" << endl;
    }
}

void Prison::updateAttendance() {
    time_t now = time(0);
    tm* localTime = localtime(&now);
    cout << "Attendance Updated for Date: " << put_time(localTime, "%Y-%m-%d") << endl;
}

void Prison::releasePrisoner() {
    int cellNo;
    cout << "Enter the cell number of the prisoner to release: ";
    cin >> cellNo;

    for (auto it = prisoners.begin(); it != prisoners.end(); ++it) {
        if ((*it)->getCellNumber() == cellNo) {
            if ((*it)->readyForRelease()) {
                char choice;
                cout << "Are you sure you want to release prisoner " << cellNo << "? (Y/N): ";
                cin >> choice;
                if (choice == 'Y' || choice == 'y') {
                    delete *it;
                    prisoners.erase(it);
                    cout << "Prisoner " << cellNo << " released successfully." << endl;
                }
                return;
            } else {
                cout << "Prisoner " << cellNo << " not yet eligible for release." << endl;
                return;
            }
        }
    }
    cout << "Prisoner with cell number " << cellNo << " not found." << endl;
}

void Prison::searchPrisoner() {
    int cellNo;
    cout << "Enter the cell number to search: ";
    cin >> cellNo;

    for (Prisoner* p : prisoners) {
        if (p->getCellNumber() == cellNo) {
            cout << "Prisoner found:" << endl;
            p->displayDetails();
            return;
        }
    }
    cout << "Prisoner with cell number " << cellNo << " not found." << endl;
}

void Prison::showMenu() {
    int choice;
    do {
        cout << "\nPrison Management System Menu:" << endl;
        cout << "1. Add New Prisoner" << endl;
        cout << "2. Display Prisoners" << endl;
        cout << "3. Update Attendance" << endl;
        cout << "4. Release Prisoner" << endl;
        cout << "5. Search Prisoner" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addPrisoner();
                break;
            case 2:
                displayPrisoners();
                break;
            case 3:
                updateAttendance();
                break;
            case 4:
                releasePrisoner();
                break;
            case 5:
                searchPrisoner();
                break;
            case 6:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);
}

void Prison::displayTime() {
    time_t now = time(0);
    tm* localTime = localtime(&now);
    cout << "Current Time: " << put_time(localTime, "%Y-%m-%d %H:%M:%S") << endl;
}

int main() {
    Prison prison;
    prison.displayTime();
    prison.showMenu();
    return 0;
}
