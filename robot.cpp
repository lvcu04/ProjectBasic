#include <iostream>
#include <vector>
#include <fstream>
#include<iomanip>
using namespace std;

const int MAX = 100;
int n, m;
bool visited1[MAX][MAX];
bool visited2[MAX][MAX];
int matrix[MAX][MAX];

struct Point {
    int x;
    int y;
};
//Kiểm tra giá trị có hợp lệ hay không
bool isValid1(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && !visited1[x][y];
}
bool isValid2(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && !visited2[x][y];
}
//Lưu kết quả của hai robot
struct Resvector {
    vector<int> Res1;
    vector<int> Res2;
};
//Kiểm tra giá trị hợp lệ lớn nhất của Robot sẽ đi
void checkAndSetMax1(int& maxValue, int& nextX, int& nextY, int x, int y) {
    if (isValid1(x, y) && matrix[x][y] > maxValue) {
        maxValue = matrix[x][y];
        nextX = x;
        nextY = y;
    }
}
void checkAndSetMax2(int& maxValue, int& nextX, int& nextY, int x, int y) {
    if (isValid2(x, y) && matrix[x][y] > maxValue) {
        maxValue = matrix[x][y];
        nextX = x;
        nextY = y;
    }
}
//Đường đi của một robot
vector<int> PathARobot(Point p1) {
    vector<int> res;
    vector<Point> temp;
    temp.push_back(p1);
    visited1[p1.x][p1.y] = true;
    res.push_back(matrix[p1.x][p1.y]);
    while (!temp.empty()) {
        int xRobot = temp.back().x;
        int yRobot = temp.back().y;
        temp.pop_back();
        int maxValue1 = -1;
        int nextX1, nextY1;

        checkAndSetMax1(maxValue1, nextX1, nextY1, xRobot - 1, yRobot);
        checkAndSetMax1(maxValue1, nextX1, nextY1, xRobot + 1, yRobot);
        checkAndSetMax1(maxValue1, nextX1, nextY1, xRobot, yRobot - 1);
        checkAndSetMax1(maxValue1, nextX1, nextY1, xRobot, yRobot + 1);

        if (maxValue1 != -1) {
            visited1[nextX1][nextY1] = true;
            temp.push_back({ nextX1, nextY1 });
            res.push_back(maxValue1);
        }
    }
    return res;

}
// Đường đi của 2 robot
Resvector PathTwoRobots(Point p1, Point p2) {
    vector<Point> temp1, temp2;
    temp1.push_back(p1);
    temp2.push_back(p2);
    visited1[p1.x][p1.y] = true;
    visited2[p2.x][p2.y] = true;

    Resvector res;
    res.Res1.push_back(matrix[p1.x][p1.y]);
    res.Res2.push_back(matrix[p2.x][p2.y]);

    while (!temp1.empty()) {
        int xRobot = temp1.back().x;
        int yRobot = temp1.back().y;
        temp1.pop_back();
        int maxValue1 = -1;
        int nextX1, nextY1;

        checkAndSetMax1(maxValue1, nextX1, nextY1, xRobot - 1, yRobot);
        checkAndSetMax1(maxValue1, nextX1, nextY1, xRobot + 1, yRobot);
        checkAndSetMax1(maxValue1, nextX1, nextY1, xRobot, yRobot - 1);
        checkAndSetMax1(maxValue1, nextX1, nextY1, xRobot, yRobot + 1);

        if (maxValue1 != -1) {
            visited1[nextX1][nextY1] = true;
            temp1.push_back({ nextX1, nextY1 });
            res.Res1.push_back(maxValue1);
        }
    }
    while (!temp2.empty()) {
        int xRobot2 = temp2.back().x;
        int yRobot2 = temp2.back().y;
        temp2.pop_back();

        int maxValue2 = -1;
        int nextX2,nextY2;
        checkAndSetMax2(maxValue2, nextX2, nextY2, xRobot2 - 1, yRobot2);
        checkAndSetMax2(maxValue2, nextX2, nextY2, xRobot2 + 1, yRobot2);
        checkAndSetMax2(maxValue2, nextX2, nextY2, xRobot2, yRobot2 - 1);
        checkAndSetMax2(maxValue2, nextX2, nextY2, xRobot2, yRobot2 + 1);

        if (maxValue2 != -1) {
            visited2[nextX2][nextY2] = true;
            temp2.push_back({ nextX2, nextY2 });
            res.Res2.push_back(maxValue2);
        }
    }

    return res;
}
// Đường đi theo lượt của 2 robot
Resvector RobotTurn(Point p1, Point p2) {
    vector<Point> temp1, temp2;
    temp1.push_back(p1);
    temp2.push_back(p2);
    visited1[p1.x][p1.y] = true;
    visited1[p2.x][p2.y] = true;

    Resvector res;
    res.Res1.push_back(matrix[p1.x][p1.y]);
    res.Res2.push_back(matrix[p2.x][p2.y]);

    while (!temp1.empty() || !temp2.empty()) {
        if (!temp1.empty()) {
            int xRobot1 = temp1.back().x;
            int yRobot1 = temp1.back().y;
            temp1.pop_back();
            int maxValue1 = 100;
            int nextX1, nextY1;

            while (true) {
                checkAndSetMax1(maxValue1, nextX1, nextY1, xRobot1 - 1, yRobot1);
                checkAndSetMax1(maxValue1, nextX1, nextY1, xRobot1 + 1, yRobot1);
                checkAndSetMax1(maxValue1, nextX1, nextY1, xRobot1, yRobot1 - 1);
                checkAndSetMax1(maxValue1, nextX1, nextY1, xRobot1, yRobot1 + 1);

                if (maxValue1 != 100) {
                    visited1[nextX1][nextY1] = true;
                    temp1.push_back({ nextX1, nextY1 });
                    res.Res1.push_back(maxValue1);
                    break;
                }
                else {
                    if (temp1.empty())
                        break;
                    xRobot1 = temp1.back().x;
                    yRobot1 = temp1.back().y;
                    temp1.pop_back();
                }
            }
        }

        if (!temp2.empty()) {
            int xRobot2 = temp2.back().x;
            int yRobot2 = temp2.back().y;
            temp2.pop_back();
            int maxValue2 = 100;
            int nextX2, nextY2;

            while (true) {
                checkAndSetMax1(maxValue2, nextX2, nextY2, xRobot2 - 1, yRobot2);
                checkAndSetMax1(maxValue2, nextX2, nextY2, xRobot2 + 1, yRobot2);
                checkAndSetMax1(maxValue2, nextX2, nextY2, xRobot2, yRobot2 - 1);
                checkAndSetMax1(maxValue2, nextX2, nextY2, xRobot2, yRobot2 + 1);

                if (maxValue2 != 100) {
                    visited1[nextX2][nextY2] = true;
                    temp2.push_back({ nextX2, nextY2 });
                    res.Res2.push_back(maxValue2);
                    break;
                }
                else {
                    if (temp2.empty())
                        break;
                    xRobot2 = temp2.back().x;
                    yRobot2 = temp2.back().y;
                    temp2.pop_back();
                }
            }
        }
    }

    return res;
}
//In ra Terminal
void DisplayTerminal(vector<int>& res) {
    for (int i = 0; i < res.size();i++) {
        cout << res[i] << " ";
    }
    cout << endl;
}
//Các điểm trùng nhau
vector<int> PathOverLap(vector<int>& res1,vector<int>& res2) {
    vector<int> res;
    for (int i = 0;i < res1.size();i++) {
        for (int j = 0; j < res2.size();j++) {
            if (res1[i] == res2[j]) {
                res.push_back(res1[i]);
            }
        }
    }
    return res;
}
//Tính tổng đường đi của robot
int SumPathRobot(vector<int>& res) {
    int sumPath = 0;
    for (int i = 0;i < res.size();i++) {
        sumPath += res[i];
    }
    return sumPath;
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    fin >> n >> m;
    for (int i = 0; i < n;i++) {
        for (int j = 0; j < m;j++) {
            fin >> matrix[i][j];
            cout<<setw(10)<<matrix[i][j];
        }
        cout<<endl;
    }
    fin.close();
    cout << "1. Path A Robot" << endl;
    cout << "2. Path Two Robots" << endl;
    cout << "3. Robot Turn" << endl;
    
    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1: {
            Point robot;
            cout<<"Nhap toa do robot ";
            fout<<"Nhap toa do robot ";
            cin >> robot.x >> robot.y;
            vector<int> res = PathARobot(robot);
            cout << "Duong di cua Robot: ";
            fout << "Duong di cua Robot: ";
            DisplayTerminal(res);
            for (int i = 0;i < res.size();i++) {
                fout << res[i] << " ";
            }
            fout << endl;
            
            cout<<"Tong "<<SumPathRobot(res);
        }

        break;
    case 2: {
            Point robot1;
            cin >> robot1.x >> robot1.y;
            Point robot2;
            cin >> robot2.x >> robot2.y;
            Resvector res = PathTwoRobots(robot1,robot2);
            vector<int> res1 = res.Res1;
            vector<int> res2 = res.Res2;
            fout << "Duong di cua Robot1: ";
            cout << "Duong di cua Robot1: ";
            DisplayTerminal(res1);
            for (int i = 0;i < res1.size();i++) {
                fout << res1[i] << " ";
            }
            fout << endl;
            fout << "Duong di cua Robot2: ";
            cout << "Duong di cua Robot2: ";
            DisplayTerminal(res2);
            for (int j = 0; j < res2.size();j++) {
                fout << res2[j] << " ";
            }
            fout << endl;   
            (SumPathRobot(res1) > SumPathRobot(res2)) ? cout << "Robot1 lon hon voi tong duong di: " << SumPathRobot(res1) << endl :
            cout << "Robot2 lon hon voi tong duong di: "  << SumPathRobot(res2) << endl;
            (SumPathRobot(res1) > SumPathRobot(res2)) ? fout << "Robot1 lon hon voi tong duong di: " << SumPathRobot(res1) << endl :
            fout << "Robot2 lon hon voi tong duong di: "  << SumPathRobot(res2) << endl;
            cout << "Diem trung nhau cua hai robot: ";
            fout << "Diem trung nhau cua hai robot: ";
            for (int x = 0;x < res1.size();x++) {
                for (int z = 0; z < res2.size();z++) {
                    if (res1[x] == res2[z]) {
                        cout << res1[x] << " ";
                        fout << res1[x] << " ";
                    }
                }
            }
        }
        break;
    case 3: {
            Point robot1;
            cin >> robot1.x >> robot1.y;
            Point robot2;
            cin >> robot2.x >> robot2.y;
            Resvector res = RobotTurn(robot1,robot2);
            vector<int> res1 = res.Res1;
            vector<int> res2 = res.Res2;
            cout << "Duong di cua Robot1: ";
            DisplayTerminal(res1);
            cout << "Duong di cua Robot2: ";
            DisplayTerminal(res2);
            fout << "Duong di cua Robot1: "; 
            for (int i = 0;i < res1.size();i++) {
                fout << res1[i] << " ";
            }
            fout << endl;
            fout << "Duong di cua Robot2: ";
            for (int j = 0; j < res2.size();j++) {
                fout << res2[j] << " ";
            }
        }
        break;
    }

    return 0;  

}
