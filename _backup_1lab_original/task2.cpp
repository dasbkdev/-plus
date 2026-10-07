#include <iostream>
using namespace std;

char power(char n, int p = 2) {
    char result = 1; // 1 потому что умножение на 1 не меняет число
    for (int i = 0; i < p; i++) {
        result *= n; // result = result * n То есть мы берём текущее значение result и умножаем его на n
    }
    return result;
}
//short int - 2 байта (16 бит) от -32 768 до 32 767
short int power(short int n, int p = 2) {
    short int result = 1;
    for (int i = 0; i < p; i++) {
        result *= n;
    }
    return result;
}
//long - 4-8 байта, от -2 147 483 648 до 2 147 483 647 в зависимости от 32 или 64 битная система
long int power(long int n, int p = 2) {
    long int result = 1;
    for (int i = 0; i < p; i++) {
        result *= n;
    }
    return result;
}
//float - 4 байта
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