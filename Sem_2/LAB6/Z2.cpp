//
// Created by Elmo on 15/04/2026.
//

#include <cstdint>
#include <fstream>
#include <iostream>
#include <list>
#include <string>

using namespace std;


class DuplicateRecordException : public std::exception {
public:
    DuplicateRecordException() = default;

    virtual const char *what() const noexcept {
        return "DuplicateRecordException";
    };
};

class DatabaseFormatException : public std::exception {
public:
    DatabaseFormatException() = default;

    virtual const char *what() const noexcept {
        return "DatabaseFormatException";
    };
};

struct StudentRecord {
    uint32_t id;
    char name[32];
    uint16_t age;
    float grade;

    bool operator!=(const StudentRecord &student_record) const {
        if (id != student_record.id) return true;
        if (age != student_record.age) return true;
        if (grade != student_record.grade) return true;
        if (strcmp(name, student_record.name) != 0) return true;
        return false;
    };
};

string filename = "students.bin";

list<StudentRecord> read_students_from_file(const string &file_name) {
    ifstream file(file_name);
    if (!file.is_open()) {
        throw runtime_error("Unable to open file");
    }

    try {
        list<StudentRecord> students;
        int len = 0;
        file.read(reinterpret_cast<char *>(&len), sizeof(int));
        for (int i = 0; i < len || file.eof(); i++) {
            StudentRecord student;
            file.read(reinterpret_cast<char *>(&student), sizeof(StudentRecord));
            students.push_back(student);
        }
        file.close();
        return students;
    } catch (...) {
        throw DatabaseFormatException();
        file.close();
    }
}

void write_students_to_file(const list<StudentRecord> &students, const string &file_name) {
    ofstream file(file_name);
    if (!file.is_open()) {
        throw runtime_error("Unable to open file");
    }

    int len = students.size();
    file.write(reinterpret_cast<char *>(&len), sizeof(int));
    for (auto student: students) {
        file.write(reinterpret_cast<char *>(&student), sizeof(StudentRecord));
    }

    file.close();
}

auto delete_student(const int ID, const string &file_name) {
    auto students = read_students_from_file(file_name);
    auto new_list = list<StudentRecord>();
    for (auto student: students) {
        if (student.id != ID) {
            new_list.push_back(student);
        }
    }

    write_students_to_file(new_list, file_name);
    return new_list;
}

auto find_student(const int ID, const string &file_name) {
    auto students = read_students_from_file(file_name);
    for (auto student: students) {
        if (student.id == ID) {
            cout << "---------------------------------" << endl;
            cout << "Id: " << student.id << endl;
            cout << "Name: " << student.name << endl;
            cout << "Age: " << student.age << endl;
            cout << "Grade: " << student.grade << endl << endl;
            return student;
        }
    }
    StudentRecord s = {0, "", 0, 0.0};
    cout << "Unable to find student with provided ID." << endl;
    return s;
}

auto add_student(const StudentRecord &student, const string &file_name) {
    auto students = read_students_from_file(file_name);

    if (find_student(student.id, file_name) != (StudentRecord){0, "", 0, 0.0}) {
        throw DuplicateRecordException();
    }

    students.push_back(student);
    write_students_to_file(students, file_name);
    return students;
}

auto update_student(const int ID, StudentRecord updated_student, const string &file_name) {
    auto students = read_students_from_file(file_name);
    auto new_list = list<StudentRecord>();
    for (auto student: students) {
        if (student.id != ID) {
            new_list.push_back(student);
            continue;
        }
        new_list.push_back(updated_student);
        new_list.end()->id = ID;
    }
    write_students_to_file(new_list, file_name);
    return new_list;
}

void print_students(const list<StudentRecord> &students) {
    for (auto student: students) {
        cout << "---------------------------------" << endl;
        cout << "Id: " << student.id << endl;
        cout << "Name: " << student.name << endl;
        cout << "Age: " << student.age << endl;
        cout << "Grade: " << student.grade << endl << endl;
    }
}

auto list_students(const string &file_name) {
    auto students = read_students_from_file(file_name);
    print_students(students);
    return students;
}

int main() {
    StudentRecord student1 = {1, "1", 1, 1.0};
    StudentRecord student2 = {2, "2", 2, 2.0};
    StudentRecord student3 = {3, "3", 3, 3.0};
    StudentRecord student4 = {4, "4", 4, 4.0};

    list<StudentRecord> students = {student1, student2, student3, student4};
    write_students_to_file(students, filename);
    students.clear();
    students = read_students_from_file(filename);
    students = add_student({5, "5", 5, 5.0}, filename);

    delete_student(3, filename);

    find_student(3, filename);
    find_student(2, filename);
    update_student(2, {2, "22", 22, 22.0}, filename);

    list_students(filename);
}