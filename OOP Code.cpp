#include <iostream>
#include <string>
using namespace std;

class Person {
public:
    virtual void displayDetails() = 0; 
};

class Teacher : public Person {
private:
    string name;
public:
    Teacher(string n) { name = n; }
    void displayDetails() {
        cout << "Teacher: " << name << endl;
    }
    string getName() { return name; }
};

class Department {
private:
    string depName;
public:
    Department(string name) { depName = name; }
    string getDepName() { return depName; }
};

class GPA {
private:
    float value;
public:
    GPA(float v = 0.0) { value = v; }
    GPA operator+(GPA obj) {
        return GPA(value + obj.value);
    }
    float getValue() { return value; }
};


class Student : public Person {
private:
    string name;
    int rollNo;
    Department* dep;
    Teacher* teachers[8][5]; 
    float marks[8][5];       
    GPA semesterGPA[8];
    static int studentCount;

public:
    Student(string n, int r, Department* d) {
        name = n;
        rollNo = r;
        dep = d;
        studentCount++;
    }

    void addMarks(int sem, float m[]) {
        for (int i = 0; i < 5; i++) {
            marks[sem][i] = m[i];
        }
    }

    void assignTeachers(int sem, Teacher* t[]) {
        for (int i = 0; i < 5; i++) {
            teachers[sem][i] = t[i];
        }
    }

    void calculateGPA(int sem) {
        float total = 0.0;
        for (int i = 0; i < 5; i++) {
            total += marks[sem][i];
        }
        float avgMarks = total / 5.0;

        float gpaOn4;
        if (avgMarks >= 80)
            gpaOn4 = 4.0;
        else if (avgMarks >= 70)
            gpaOn4 = 3.0;
        else if (avgMarks >= 60)
            gpaOn4 = 2.0;
        else if (avgMarks >= 50)
            gpaOn4 = 1.0;
        else
            gpaOn4 = 0.0;

        semesterGPA[sem] = GPA(gpaOn4);
    }

    float getGPA(int sem) {
        return semesterGPA[sem].getValue();
    }

    float getCGPA(int uptoSem) {
        GPA sum;
        for (int i = 0; i <= uptoSem; i++) {
            sum = sum + semesterGPA[i];
        }
        return sum.getValue() / (uptoSem + 1);
    }

    void displayDetails() {
        cout << "\nStudent Name: " << name << endl;
        cout << "Roll No: " << rollNo << endl;
        cout << "Department: " << dep->getDepName() << endl;
    }

    void displaySemester(int sem) {
        cout << "Semester " << sem + 1 << " Teachers:" << endl;
        for (int i = 0; i < 5; i++) {
            cout << "- " << teachers[sem][i]->getName() << endl;
        }
    }

    ~Student() {
        cout << "\nStudent " << name << " removed from system.\n";
    }

    static int getStudentCount() {
        return studentCount;
    }
};

int Student::studentCount = 0;

int main() {
    int numStudents;
    cout << "How many students do you want to add? ";
    cin >> numStudents;

    Student* students[numStudents];

    for (int sIdx = 0; sIdx < numStudents; sIdx++) {
        cout << "\n=== Enter Details for Student " << sIdx + 1 << " ===\n";

        string name, depName;
        int roll;

        cout << "Enter Student Name: ";
        cin >> name;
        cout << "Enter Roll No: ";
        cin >> roll;
        cout << "Enter Department: ";
        cin >> depName;

        Department* dep = new Department(depName);
        Student* s = new Student(name, roll, dep);

        for (int sem = 0; sem < 8; sem++) {
            cout << "\n--- Semester " << sem + 1 << " ---" << endl;

            Teacher* teachers[5];
            cout << "Enter names of 5 teachers for Semester " << sem + 1 << ":\n";
            for (int i = 0; i < 5; i++) {
                string tname;
                cout << "Teacher " << i + 1 << ": ";
                cin >> tname;
                teachers[i] = new Teacher(tname);
            }
            s->assignTeachers(sem, teachers);

            float m[5];
            cout << "Enter marks (out of 100) for 5 subjects for Semester " << sem + 1 << ":\n";
            for (int i = 0; i < 5; i++) {
                cout << "Marks for Subject " << i + 1 << ": ";
                cin >> m[i];
            }
            s->addMarks(sem, m);

            s->calculateGPA(sem);

            if (sem == 0) {
                s->displayDetails();
            }
            s->displaySemester(sem);
            cout << "Semester " << sem + 1 << " GPA (4.0 scale): " << s->getGPA(sem) << endl;
            cout << "CGPA up to Semester " << sem + 1 << ": " << s->getCGPA(sem) << endl;

            for (int i = 0; i < 5; i++) {
                delete teachers[i];
            }
        }

        students[sIdx] = s;

        delete dep; 
    }

    cout << "\nTotal students added: " << Student::getStudentCount() << endl;

    for (int i = 0; i < numStudents; i++) {
        delete students[i];
    }

    return 0;
}