#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct node {
    string name;
    int age;
    int rollNumber;  
    vector<string> subjects;  
    node* next;
};

class school {
public:
    node* head;

    school() : head(nullptr) {}

    ~school() {
        node* temp = head;
        while (temp != nullptr) {
            node* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
    }

    void addStudent(string n, int a, int r) {
        if (isRollNumberTaken(r)) {
            cout << "Roll number (" << r << ") is already taken. Cannot add student." << endl;
            return;
        }

        node* newNode = new node();
        newNode->name = n;
        newNode->age = a;
        newNode->rollNumber = r;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
        } else {
            node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        cout << "Student (" << n << ") with roll number (" << r << ") added successfully." << endl;
    }

    void deleteStudent(int r) {
        node* temp = head;
        node* before = nullptr;

        if (temp == nullptr) {
            cout << "Student list is empty. Cannot delete." << endl;
            return;
        }

        if (temp->rollNumber == r) {
            head = temp->next;
            delete temp;
            cout << "Student with roll number (" << r << ") deleted successfully." << endl;
            return;
        }

        while (temp != nullptr && temp->rollNumber != r) {
            before = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Student with roll number (" << r << ") not found in the list." << endl;
            return;
        }

        before->next = temp->next;
        delete temp;
        cout << "Student with roll number (" << r << ") deleted successfully." << endl;
    }

    void updateDetails(int r, string newName, int newAge) {
        node* temp = head;
        while (temp != nullptr && temp->rollNumber != r) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Student with roll number (" << r << ") not found in the list." << endl;
            return;
        }

        temp->name = newName;
        temp->age = newAge;
        cout << "Student with roll number (" << r << ") details updated successfully." << endl;
    }

    void addSubject(int r, string subject) {
        node* temp = head;
        while (temp != nullptr && temp->rollNumber != r) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Student with roll number (" << r << ") not found." << endl;
            return;
        }

        temp->subjects.push_back(subject);
        cout << "Subject (" << subject << ") added to student with roll number (" << r << ")." << endl;
    }

    void removeSubject(int r, string subject) {
        node* temp = head;
        while (temp != nullptr && temp->rollNumber != r) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Student with roll number (" << r << ") not found." << endl;
            return;
        }

        for (auto it = temp->subjects.begin(); it != temp->subjects.end(); ++it) {
            if (*it == subject) {
                temp->subjects.erase(it);
                cout << "Subject (" << subject << ") removed from student with roll number (" << r << ")." << endl;
                return;
            }
        }

        cout << "Subject (" << subject << ") not found for student with roll number (" << r << ")." << endl;
    }

    void searchStudent(int r) {
        node* temp = head;
        while (temp != nullptr && temp->rollNumber != r) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Student with roll number (" << r << ") not found." << endl;
            return;
        }

        cout << "Student details:\n";
        cout << "  Roll Number: " << temp->rollNumber << endl;
        cout << "  Name: " << temp->name << endl;
        cout << "  Age: " << temp->age << endl;
        cout << "  Subjects: ";
        if (temp->subjects.empty()) {
            cout << "No subjects assigned." << endl;
        } else {
            for (const string& subject : temp->subjects) {
                cout << subject << " ";
            }
            cout << endl;
        }
    }

    void display() {
        if (head == nullptr) {
            cout << "No students in the list." << endl;
            return;
        }

        node* temp = head;
        int count = 1;
        while (temp != nullptr) {
            cout << "Student " << count++ << ":\n";
            cout << "  Roll Number: " << temp->rollNumber << endl;
            cout << "  Name: " << temp->name << endl;
            cout << "  Age: " << temp->age << endl;
            cout << "  Subjects: ";
            if (temp->subjects.empty()) {
                cout << "No subjects assigned." << endl;
            } else {
                for (const string& subject : temp->subjects) {
                    cout << subject << " ";
                }
                cout << endl;
            }
            temp = temp->next;
        }
    }

    void saveToFile() {
    ofstream myfile("student.txt");
    if (!myfile) {
        cout << "Error opening file for writing." << endl;
        return;
    }

    node* temp = head;
    while (temp != nullptr) {
        myfile << temp->rollNumber << "," << temp->name << "," << temp->age;

        if (!temp->subjects.empty()) {
            myfile << ",Subjects:";
            for (size_t i = 0; i < temp->subjects.size(); ++i) {
                myfile << temp->subjects[i];
                if (i != temp->subjects.size() - 1) {
                    myfile << ";"; 
                }
            }
        }
        myfile << endl; 
        temp = temp->next;
    }

    myfile.close();
    cout << "Data saved to file successfully." << endl;
}

private:
    bool isRollNumberTaken(int r) {
        node* temp = head;
        while (temp != nullptr) {
            if (temp->rollNumber == r) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
};

int main() {
    school student;

    student.addStudent("Musab", 22, 101);
    student.addStudent("Ammar", 32, 102);
    student.addStudent("Samir", 15, 103);
    student.addStudent("Kalil", 20, 104);

    student.addSubject(101, "Maths");
    student.addSubject(102, "Algebra");
    student.addSubject(103, "Physics");
    student.display();

    cout << "\nSearching for student with roll number (103):" << endl;
    student.searchStudent(103);

    cout << "\nRemoving subject (Maths) from student with roll number (101):" << endl;
    student.removeSubject(101, "Maths");
    
    cout << "\nList of students after subject removal:" << endl;
    student.display();

    student.saveToFile();

    return 0;
}