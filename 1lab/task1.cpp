#include <iostream>
using namespace std;

double power(double N, int P = 2);

int main() {
    double N;
    char choice;

    char repeat = 'y';
    // Повторяем расчёт, пока пользователь отвечает y.
    while (repeat == 'y' || repeat == 'Y') {
        cout << "Введите число N: ";
        cin >> N;

        cout << "Хотите ввести степень P? (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            int P;
            cout << "Введите степень P: ";
            cin >> P;

            if (P <= 2) {
                cout << "Ошибка: степень должна быть больше !" << endl;
                return 1;
            }

            cout << "Результат: " << power(N, P) << endl;
        } else {
            cout << "Результат (в квадрате по умолчанию): " << power(N) << endl;
        }

        cout << "Повторить расчёт? (y/n): ";
        cin >> repeat;
        if (!cin) break;
    }

    return 0;
}

double power(double N, int P) {
    double result = 1.0;

    for (int i = 0; i < P; i++) {
        result *= N;
    }

    return result;
}