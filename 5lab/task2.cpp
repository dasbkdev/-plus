#include "../common/input.h"
#include <limits>
#include <stdexcept>

class fraction {
    double chislo; // Дробь хранится как обычное десятичное число.

    // static: одна проверка результатов для всех объектов класса.
    static fraction checked(long double result) {
        // Не допускаем бесконечность и потерю ненулевого результата до нуля.
        if (!isfinite(result) || fabs(result) > numeric_limits<double>::max())
            throw overflow_error("Результат слишком велик для double.");
        double value = static_cast<double>(result); // Возвращаемся к типу поля.
        if (result != 0 && value == 0)
            throw underflow_error("Результат слишком мал для double.");
        return fraction(value);
    }

public:
    fraction() : chislo(0) {}
    fraction(double value) : chislo(value) {
        if (!isfinite(value)) throw domain_error("Число должно быть конечным.");
    }
    double getValue() const { return chislo; } // const запрещает менять объект.

    // const-ссылка позволяет читать второй объект, не создавая его копию.
    fraction operator+(const fraction& other) const {
        // long double даёт место для проверки слишком большого результата.
        return checked(static_cast<long double>(chislo) + other.chislo);
    }
    fraction operator-(const fraction& other) const {
        return checked(static_cast<long double>(chislo) - other.chislo);
    }
    fraction operator*(const fraction& other) const {
        return checked(static_cast<long double>(chislo) * other.chislo);
    }
    fraction operator/(const fraction& other) const {
        if (other.chislo == 0) throw domain_error("Деление на ноль.");
        return checked(static_cast<long double>(chislo) / other.chislo);
    }

    // Число справа превращается в fraction конструктором с одним аргументом.

    // Слева стоит число: внешний оператор сохраняет порядок операндов.
    friend fraction operator+(double number, const fraction& value) { return fraction(number) + value; }
    friend fraction operator-(double number, const fraction& value) { return fraction(number) - value; }
    friend fraction operator*(double number, const fraction& value) { return fraction(number) * value; }
    friend fraction operator/(double number, const fraction& value) { return fraction(number) / value; }

    fraction& operator++() {
        // this указывает на текущий объект; *this — сам этот объект.
        *this = *this + 1.0;
        return *this;
    }
    fraction operator++(int) {
        fraction old = *this; // Сохраняем прежнее значение для постфикса.
        ++(*this);
        return old;
    }
};

int main() {
    fraction zero;
    cout << setprecision(15) << "Конструктор по умолчанию: " << zero.getValue()
         << "\nДроби вводите десятичными числами, например 0.75 вместо 3/4.\n";
    double maximum = numeric_limits<double>::max();
    while (true) {
        cout << "\n1 +  2 -  3 *  4 /  5 ++a  6 a++  0 Выход\n";
        int choice = readInt("Команда: ", 0, 6);
        if (choice == 0) break;
        int form = 1;
        if (choice <= 4) {
            // Проверяем одинаковую операцию с тремя видами операндов.
            cout << "1 объект/объект; 2 объект/число; 3 число/объект\n";
            form = readInt("Вид операндов: ", 1, 3);
        }
        double left = readDouble("Первое значение: ", -maximum, maximum);
        fraction a(left), result;
        try {
            if (choice >= 5) {
                if (choice == 5) result = ++a;
                else result = a++;
                cout << "a после операции: " << a.getValue() << '\n';
            } else {
                double right = readDouble("Второе значение: ", -maximum, maximum);
                fraction b(right);
                if (form == 1) {
                    if (choice == 1) result = a + b;
                    if (choice == 2) result = a - b;
                    if (choice == 3) result = a * b;
                    if (choice == 4) result = a / b;
                } else if (form == 2) {
                    if (choice == 1) result = a + right;
                    if (choice == 2) result = a - right;
                    if (choice == 3) result = a * right;
                    if (choice == 4) result = a / right;
                } else {
                    if (choice == 1) result = left + b;
                    if (choice == 2) result = left - b;
                    if (choice == 3) result = left * b;
                    if (choice == 4) result = left / b;
                }
            }
            cout << "Результат: " << result.getValue() << '\n';
        } catch (const exception& error) {
            // Ошибка операции не мешает выбрать следующую команду меню.
            cout << "Ошибка: " << error.what() << '\n';
        }
    }
    return 0;
}
