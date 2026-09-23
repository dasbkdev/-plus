#include <iostream>
using namespace std;

char power(char n, int p = 2) {
    char result = 1;
    for (int i = 0; i < p; i++) {
        result *= n;
    }
    return result;
}

short int power(short int n, int p = 2) {
    short int result = 1;
    for (int i = 0; i < p; i++) {
        result *= n;
    }
    return result;
}

long int power(long int n, int p = 2) {
    long int result = 1;
    for (int i = 0; i < p; i++) {
        result *= n;
    }
    return result;
}

float power(float n, int p = 2) {
    float result = 1.0f;
    for (int i = 0; i < p; i++) {
        result *= n;
    }
    return result;
}

double power(double n, int p = 2) {
    double result = 1.0;
    for (int i = 0; i < p; i++) {
        result *= n;
    }
    return result;
}

int main() {
    char c = 3;
    short int s = 4;
    long int l = 5;
    float f = 2.5f;
    double d = 3.14;

    cout << "char (3^2): " << (int)power(c) << endl;
    cout << "short int (4^3): " << power(s, 3) << endl;
    cout << "long int (5^4): " << power(l, 4) << endl;
    cout << "float (2.5^2): " << power(f) << endl;
    cout << "double (3.14^3): " << power(d, 3) << endl;

    return 0;
}