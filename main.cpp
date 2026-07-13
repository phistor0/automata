#include <iostream>
using namespace std;

double triangleArea() {
    double b;
    double h;
    double a;

    cout << "Your triangle length is: ";
    cin >> b;
    cout << "Your triangle height is: ";
    cin >> h;

    a = (b * h)/2;
    return a;
};

int main() {
    double area;
    area = triangleArea();
    cout << "The area is: " << area;
    
    return 0;
};