#include<iostream>
using namespace std;

class Test
{
private:
    int x;
public:
    Test(int x = 0): x{x} {};
    void setX1(int x) { x = x; }
    void setX2(int x) { this->x = x; }
    void setX3(int x) { x = this->x; }
    void setX4(int& x) { this->x = x; }
    void setX5(int& x) { x = this->x; }
    void print() { cout << "x = " << x << endl; }
};

int main()
{
    Test obj;
    cout << "Initial Value: ";
    obj.print();
    obj.setX1(20);
    cout << "After setX1(20): ";
    obj.print();
    obj.setX2(20);
    cout << "After setX2(20): ";
    obj.print();
    int main_x = 30;
    cout << "main_x starts at 30" << endl;
    obj.setX3(main_x);
    cout << "After setX3(main_x): main_x = " << main_x << ", ";
    obj.print();
    obj.setX4(main_x);
    cout << "After setX4(main_x): main_x = " << main_x << ", ";
    obj.print();
    main_x = 40;
    cout << "main_x set to 40" << endl;
    obj.setX5(main_x);
    cout << "After setX5(main_x): main_x = " << main_x << ", ";
    obj.print();
    return 0;
}
