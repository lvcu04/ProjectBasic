#include <iostream>
using namespace std;

class Student {
protected: 
    string code;
    string name;
    string location;
    int total_credits;
    float avg_score;

public:
    void Input() {
        cout << "Nhap ma sinh vien: ";
        cin >> code;
        cout << "Nhap ho ten sinh vien: ";
        cin.ignore();
        getline(cin, name);
        cout << "Nhap dia chi sinh vien: ";
        getline(cin, location);
        cout << "Nhap so tin chi cua sinh vien: ";
        cin >> total_credits;
        cout << "Nhap diem trung binh cua sinh vien: ";
        cin >> avg_score;
    }

    void Output() {
        cout << "Ma sinh vien: " << code << endl;
        cout << "Ho ten sinh vien: " << name << endl;
        cout << "Dia chi sinh vien: " << location << endl;
        cout << "So tin chi cua sinh vien: " << total_credits << endl;
        cout << "Diem trung binh cua sinh vien: " << avg_score << endl;
    }
    float getAvgScore() {
        return avg_score;
    }
};

class univercitySt : public Student {
private:
    string thesis_name;
    float thesis_point;

public:
    void Input() {
        Student::Input();
        cout << "Nhap ten luan van: ";
        cin.ignore();
        getline(cin, thesis_name);
        cout << "Nhap diem luan van: ";
        cin >> thesis_point;
    }

    void Output() {
        Student::Output();
        cout << "Ten luan van: " << thesis_name << endl;
        cout << "Diem luan van: " << thesis_point << endl;
    }

    bool univercityGraduate() {
        if(total_credits >= 145 && avg_score >= 5 && thesis_point >= 5){
            return true;
        }
        else{
            return false;
        }
    }
    
};

class collegeSt : public Student {
private:
    float final_exam_score;

public:
    void Input() {
        Student::Input();
        cout << "Nhap diem thi tot nghiep: ";
        cin >> final_exam_score;
    }

    void Output() {
        Student::Output();
        cout << "Diem thi tot nghiep: " << final_exam_score << endl;
    }

    bool collegeGraduate() {
        if(total_credits >= 110 && avg_score >= 5 && final_exam_score >= 5){
            return true;
        }
        else{
            return false;
        }
    }
};

Student findStudentWithHighestAverageScore(Student students[], int numStudents) {
    if (numStudents == 0) {
        return Student();
    }

    Student highestAvgStudent = students[0];
    for (int i = 1; i < numStudents; i++) {
        if (students[i].getAvgScore() > highestAvgStudent.getAvgScore()) {
            highestAvgStudent = students[i];
        }
    }
    return highestAvgStudent;
}

int main() {
    const int maxSize = 100;
    univercitySt US[maxSize];
    collegeSt CS[maxSize];
    int numUS= 0;
    int numCS=0;
       char choice;
    do {
        cout << "Chon loai sinh vien (D/Dai hoc, C/Cao dang, Q/Quit): ";
        cin >> choice;

        if (choice == 'Q' || choice == 'q') {
            break;
        }

        if (choice == 'D' || choice == 'd') {
            if (numUS < maxSize) {
                US[numUS].Input();
                numUS++;
            } else {
                cout << "Khong the them sinh vien dai hoc, danh sach day!" << endl;
            }
        } else if (choice == 'C' || choice == 'c') {
            if (numCS < maxSize) {
                CS[numCS].Input();
                numCS++;
            } else {
                cout << "Khong the them sinh vien cao dang, danh sach day!" << endl;
            }
        }
    } while (choice != 'Q' && choice != 'q');

    
    cout << "Danh sach sinh vien dai hoc:" << endl;
    for (int i = 0; i < numUS; i++) {
        US[i].Output();
        if (US[i].univercityGraduate()) {
            cout << "Sinh vien dai hoc co du dieu kien tot nghiep." << endl;
        } else {
            cout << "Sinh vien dai hoc khong du dieu kien tot nghiep." << endl;
        }
    }

    cout << "Danh sach sinh vien cao dang:" << endl;
    for (int i = 0; i < numCS; i++) {
        CS[i].Output();
        if (CS[i].collegeGraduate()) {
            cout << "Sinh vien cao dang co du dieu kien tot nghiep." << endl;
        } else {
            cout << "Sinh vien cao dang khong du dieu kien tot nghiep." << endl;
        }
    }

   //e
    Student highestAvgStudentUS = findStudentWithHighestAverageScore(US, numUS);
    Student highestAvgStudentCS = findStudentWithHighestAverageScore(US, numCS);
    cout << "Sinh vien co diem trung binh cao nhat:" << endl;
    if (highestAvgStudentUS.getAvgScore() > highestAvgStudentCS.getAvgScore()) {
        highestAvgStudentUS.Output();
    } else if (highestAvgStudentCS.getAvgScore() > highestAvgStudentUS.getAvgScore()) {
        highestAvgStudentCS.Output();
    } else {
        cout << "Khong co sinh vien nao co diem trung binh cao nhat." << endl;
    }
    //f
    cout << "Sinh vien dai hoc co diem trung binh cao nhat:" << endl;
    highestAvgStudentUS.Output();

    return 0;
}
   