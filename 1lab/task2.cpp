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
    int number;
    char c;
    short int s;
    long int l;
    float f;
    double d;

    // Через int вводим числовое значение char, а не код символа цифры.
    cout << "Введите число для char: ";
    cin >> number;
    cout << "Введите число для short int: ";
    cin >> s;
    cout << "Введите число для long int: ";
    cin >> l;
    cout << "Введите число для float: ";
    cin >> f;
    cout << "Введите число для double: ";
    cin >> d;

    if (!cin) {
        cout << "Ошибка ввода числа." << endl;
        return 1;
    }
    c = number;

    cout << "char (" << (int)c << "^2): " << (int)power(c) << endl;
    cout << "short int (" << s << "^3): " << power(s, 3) << endl;
    cout << "long int (" << l << "^4): " << power(l, 4) << endl;
    cout << "float (" << f << "^2): " << power(f) << endl;
    cout << "double (" << d << "^3): " << power(d, 3) << endl;

    return 0;
}
