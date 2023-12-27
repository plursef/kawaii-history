#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

struct ScoreT {
    int a;
    int b;
    int c;
};

class StudentT {
public:
    long long number;
    char name[51];
    ScoreT score;

    // 构造函数
    StudentT(long long num, int a, int b, int c, const char* studentName) : number(num), score{a, b, c} {
        strncpy(name, studentName, 50);
        name[50] = '\0';
    }

    // 静态成员函数作为友元函数
    static bool compareStudents(const StudentT& a, const StudentT& b) {
        return a.number < b.number;
    }

    // 显示学生信息
    void display() const {
        cout << number << " " << name << " " << score.a << " " << score.b << " " << score.c << endl;
    }
};

vector<StudentT> students;

bool compareStudentsByScore(const StudentT& a, const StudentT& b) {
    return a.score.a + a.score.b + a.score.c > b.score.a + b.score.b + b.score.c;
}

bool same(const char* a, const char* b) {
    int i = 0;
    while (true) {
        if (a[i] == b[i]) {
            i++;
            if (a[i] == '\0') return true;
        } else {
            return false;
        }
    }
}

void add() {
    long long check;
    bool same = false;
    cin >> check;
    for (int i = 0; i < students.size(); ++i) {
        if (students[i].number == check) {
            same = true;
            break;
        }
    }
    if (students.empty() || !same) {
        int a, b, c;
        cin >> a >> b >> c;
        cin.ignore(1);
        char name[51];
        cin.getline(name, 51);
        students.emplace_back(check, a, b, c, name);
    } else {
        int a, b, c;
        cin >> a >> b >> c;
        cin.ignore(1);
        cin.getline(students.back().name, 51);
    }
}

void modify() {
    long long modinum;
    bool same = false;
    cin >> modinum;
    for (int i = 0; i < students.size(); ++i) {
        if (students[i].number == modinum) {
            same = true;
            break;
        }
    }
    if (same) {
        int a, b, c;
        cin >> a >> b >> c;
        cin.get();
        cin.getline(students.back().name, 51);
    } else {
        cin.ignore(200, '\n');
    }
}

void erase() {
    long long eranum;
    bool same = false;
    cin >> eranum;
    for (int i = 0; i < students.size(); ++i) {
        if (students[i].number == eranum) {
            same = true;
            students.erase(students.begin() + i);
            break;
        }
    }
}

void search_number() {
    long long seanum;
    cin >> seanum;
    for (const auto& student : students) {
        if (student.number == seanum) {
            student.display();
            break;
        }
    }
}

void search_name() {
    cin.ignore();
    char seaname[51];
    cin.getline(seaname, 51);
    for (const auto& student : students) {
        if (strcmp(student.name, seaname) == 0) {
            student.display();
        }
    }
}

void print_number() {
    sort(students.begin(), students.end(), &StudentT::compareStudents);
    for (const auto& student : students) {
        student.display();
    }
}

void print_score() {
    sort(students.begin(), students.end(), &compareStudentsByScore);
    for (const auto& student : students) {
        student.display();
    }
}

int main() {
    int select = 2;
    void (*func[8])() = {nullptr, add, modify, erase, search_number, search_name, print_number, print_score};
    

    string (*fp[])(vector<int>) ={nullptr};
    while (true) {
        cin >> select;
        if (select == 0) return 0;
        else func[select]();
    }

    return 0;
}
