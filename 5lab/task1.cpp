#include "../common/input.h"
#include <limits>
#include <stdexcept>

class Int {
    int value; // Значение объекта закрыто от прямого изменения.

    // static: эта проверка общая для всех объектов Int.
    static int checked(long double result) {
        // Проверяем границы до преобразования обратно в int.
        if (result < numeric_limits<int>::min() ||
            result > numeric_limits<int>::max())
            throw overflow_error("Переполнение типа int.");
        return static_cast<int>(result);
    }

public:
    Int(int number = 0) : value(number) {}
    // const: чтение значения не меняет объект.
    int getValue() const { return value; }

    // const Int& передаёт второй объект без копирования и без изменения.
    Int operator+(const Int& other) const {
        // static_cast меняет тип до сложения, чтобы int не переполнился.
        return Int(checked(static_cast<long double>(value) + other.value));
    }
    Int operator-(const Int& other) const {
        return Int(checked(static_cast<long double>(value) - other.value));
    }
    Int operator*(const Int& other) const {
        return Int(checked(static_cast<long double>(value) * other.value));
    }
    Int operator/(const Int& other) const {
        // Нулевой делитель проверяем до самой операции.
        if (other.value == 0) throw domain_error("Деление на ноль.");
        return Int(checked(static_cast<long double>(value) / other.value));
    }
    Int& operator++() {
        this->value = checked(static_cast<long double>(value) + 1);
        return *this; // Префикс возвращает уже изменённый объект.
    }
    Int operator++(int) {
        Int old = *this;
        ++(*this);
        return old; // Постфикс возвращает значение до изменения.
    }
};

int main() {
    cout << "Int: диапазон " << numeric_limits<int>::min() << ".."
         << numeric_limits<int>::max() << ". Деление целочисленное.\n";
    try {
        // Цикл позволяет проверить разные операции за один запуск.
        while (true) {
            cout << "\n1 +  2 -  3 *  4 /  5 ++a  6 a++  0 Выход\n";
            int choice = readInt("Команда: ", 0, 6);
            if (choice == 0) break;
            // readInt повторяет ввод, если введены буквы или число вне границ.
            Int a(readInt("a: ", numeric_limits<int>::min(), numeric_limits<int>::max()));
            Int result;
            if (choice <= 4) {
                Int b(readInt("b: ", numeric_limits<int>::min(), numeric_limits<int>::max()));
                if (choice == 1) result = a + b;
                if (choice == 2) result = a - b;
                if (choice == 3) result = a * b;
                if (choice == 4) result = a / b;
            } else if (choice == 5) {
                result = ++a;
            } else {
                result = a++;
            }
            cout << "Результат: " << result.getValue() << '\n';
            if (choice >= 5) cout << "a после операции: " << a.getValue() << '\n';
        }
    } catch (const exception& error) {
        cout << "Ошибка: " << error.what() << " Программа завершена.\n";
        return 1;
    }
    return 0;
}
