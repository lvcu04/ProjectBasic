#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Date {
    int day;
    int month;
    int year;
};

// Lớp cha
class nhanVien {
protected:
    string name;
    Date birthday;

public:
    nhanVien() {
        this->name = "";
        this->birthday = {0, 0, 0};
    }

    virtual int tinhLuong() {
        return 0;
    }

    virtual void InputInfor() {
        cout << "Nhap ten Nhan vien: ";
        cin.ignore();
        getline(cin, name);
        cout << "Nhap ngay sinh nhan vien " << name << ": ";
        cin >> birthday.day >> birthday.month >> birthday.year;
    }

    virtual void OutputInfor() {
        cout << "Ten Nhan vien: " << name << endl;
        cout << "Ngay sinh nhan vien " << name << ": " << birthday.day << "/" << birthday.month << "/" << birthday.year << endl;
    }
     string getName() {
        return name;
    }
};
// Lớp con
class nhanVienVanPhong : public nhanVien {
private:
    int soNgayLamViec;

public:
    nhanVienVanPhong() : soNgayLamViec(0) {}  // Hàm tạo mặc định

    void InputInfor() override{
        nhanVien::InputInfor();
        cout << "Nhap so ngay lam viec: ";
        cin >> soNgayLamViec;
    }

    int tinhLuong() override{
        return soNgayLamViec * 100000.0;
    }

    void OutputInfor() override {
        nhanVien::OutputInfor();
        cout << "Luong nhan vien van phong cua "<<name<<":"<< tinhLuong() << " VND" << endl;
    }
};

// Lớp con
class nhanVienSanXuat : public nhanVien {
private:
    int luongCoBan = 5000000;
    int soSanPham;

public:
    nhanVienSanXuat() : luongCoBan(0), soSanPham(0) {}  // Hàm tạo mặc định

    void InputInfor() override{
        nhanVien::InputInfor();
        cout << "Nhap so san pham: ";
        cin >> soSanPham;
    }

    int tinhLuong() override{
        return luongCoBan + soSanPham * 5000.0;
    }

    void OutputInfor() override{
        nhanVien::OutputInfor();
        cout << "Luong nhan vien san xuat cua " <<name<<":"<< tinhLuong() << " VND" << endl;
    }
};
//e,f,g
//...


int main() {
    vector<nhanVien*> listNhanVien;
    int n;
    cout << "Nhap so luong nhan vien: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        int loai;
        cout << "Nhap loai nhan vien (1 - Van phong, 2 - San xuat): ";
        cin >> loai;

        if (loai == 1) {
            nhanVienVanPhong* nvvp = new nhanVienVanPhong();
            nvvp->InputInfor();
            listNhanVien.push_back(nvvp);
        } else if (loai == 2) {
            nhanVienSanXuat* nvsx = new nhanVienSanXuat();
            nvsx->InputInfor();
            listNhanVien.push_back(nvsx);
        } else {
            cout << "Loai nhan vien khong hop le!" << endl;
            i--;
        }
    }
    cout<<"----------------------------------------"<<endl;
    cout<<"\t Danh sach nhan vien\n";
    cout<<"-----------------------------------------\n";
    // Xuất thông tin danh sách nhân viên theo lương và tính tổng lương
    
    int tongLuongCongTy = 0;
    for (nhanVien* nv : listNhanVien) {
        nv->OutputInfor();
        int luong = nv->tinhLuong();
        tongLuongCongTy += luong;
    }

    cout << "Tong luong cua cong ty: " << tongLuongCongTy << " VND" << endl;
//e
    //tim nhan vien co luong thap nhat
 nhanVien* fnv = listNhanVien[0];
 int minSalary = fnv->tinhLuong();
 for (nhanVien* nv : listNhanVien){
     int luong = nv->tinhLuong();
     if (luong < minSalary) {
         minSalary = luong;
         fnv = nv;
     }
 }
 cout << "Nhan vien co luong thap nhat la: "<< minSalary << " VND" << endl;
 //f
    string targetName;
    cout << "Nhap ten nhan vien can tim: ";
    cin.ignore();
    getline(cin, targetName);

    bool found = false;

    for (nhanVien* nv : listNhanVien) {
        if (nv->getName() == targetName) { 
            nv->OutputInfor();
            found = true;
        }
    }

    if (!found) {
        cout << "Khong tim thay nhan vien co ten " << targetName << endl;
    }

    //g
    int totalSalary = 0;
    int numberOfEmployees = 0;

    for (nhanVien* nv : listNhanVien) {
        totalSalary += nv->tinhLuong();
        numberOfEmployees++;
    }

    if (numberOfEmployees > 0) {
        double averageSalary = static_cast<double>(totalSalary) / numberOfEmployees;

        int employeesBelowAverageSalary = 0;

        for (nhanVien* nv : listNhanVien) {
            if (nv->tinhLuong() < averageSalary) {
                employeesBelowAverageSalary++;
            }
        }

        cout << "Cong ty co " << employeesBelowAverageSalary << " nhan vien co luong thap hon luong trung binh." << endl;
    } else {
        cout << "Khong co nhan vien nao trong cong ty." << endl;
    }

    // Giải phóng bộ nhớ
    for (nhanVien* nv : listNhanVien) {
        delete nv;
    }

    return 0;
}
