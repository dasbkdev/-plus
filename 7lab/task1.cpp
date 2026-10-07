#include "../common/input.h"
#include <limits>

// Три класса по-разному складывают одни и те же два массива.
// Виртуальный метод выбирается по настоящему типу объекта.
// Массивы обычные: не более 100 чисел в каждом.
class Array1 {
public:
    static const int MAX = 100;
private:
    unsigned a[MAX], b[MAX];
    int count;
protected:
    unsigned first(int i) const { return a[i]; }
    unsigned second(int i) const { return b[i]; }
    int size() const { return count; }
    void printSum(unsigned x, unsigned y) const {
        // До сложения проверяем, поместится ли результат в unsigned.
        if (x > numeric_limits<unsigned>::max() - y) cout << "Переполнение ";
        else cout << x + y << ' ';
    }
public:
    Array1(int n = 1, unsigned value = 0) : count(n) {
        for (int i = 0; i < count; i++) a[i] = b[i] = value;
    }
    Array1(int n, const unsigned x[], const unsigned y[]) : count(n) {
        for (int i = 0; i < count; i++) {
            a[i] = x[i];
            b[i] = y[i];
        }
    }
    virtual ~Array1() {}
    virtual void sum() const {
        cout << "Все пары: ";
        for (int i = 0; i < count; i++) printSum(a[i], b[i]);
        cout << '\n';
    }
};

class Array2 : public Array1 {
private:
    unsigned a[MAX], b[MAX];
    int count;
public:
    Array2(int n = 1, unsigned value = 0) : Array1(n, value), count(n) {
        for (int i = 0; i < count; i++) a[i] = b[i] = value;
    }
    Array2(int n, const unsigned x[], const unsigned y[]) : Array1(n, x, y), count(n) {
        for (int i = 0; i < count; i++) {
            a[i] = x[i];
            b[i] = y[i];
        }
    }
    ~Array2() override {}
    // Переопределение сохраняет сигнатуру и меняет действие: берем четные значения.
    void sum() const override {
        cout << "Суммы только четных значений в каждой паре: ";
        for (int i = 0; i < count; i++) {
            unsigned firstEven = 0;
            unsigned secondEven = 0;
            // Нечетное значение не участвует в сумме этой пары.
            if (a[i] % 2 == 0) firstEven = a[i];
            if (b[i] % 2 == 0) secondEven = b[i];
            printSum(firstEven, secondEven);
        }
        cout << '\n';
    }
};

class Array3 : public Array1 {
public:
    Array3(int n, const unsigned x[], const unsigned y[]) : Array1(n, x, y) {}
    void sum() const override {
        cout << "Пары на нечетных позициях (1, 3, ...): ";
        // Индексы 0, 2, 4 соответствуют позициям 1, 3, 5.
        for (int i = 0; i < size(); i += 2) printSum(first(i), second(i));
        cout << '\n';
    }
};

int main() {
    while (true) {
        cout << "\n1. Ввести массивы и показать все вызовы\n2. Конструкторы с нулями\n0. Выход\n";
        int menu = readInt("Выбор: ", 0, 2);
        if (menu == 0) break;
        if (menu == 2) {
            Array1 a;
            Array2 b;
            a.sum();
            b.sum();
            continue;
        }
        int n = readInt("Размер (1..100): ", 1, Array1::MAX);
        unsigned x[Array1::MAX], y[Array1::MAX];
        cout << "Первый массив:\n";
        for (int i = 0; i < n; i++) x[i] = readInt("Элемент: ", 0, 2147483647);
        cout << "Второй массив:\n";
        for (int i = 0; i < n; i++) y[i] = readInt("Элемент: ", 0, 2147483647);
        Array1 base(n, x, y);
        Array2 even(n, x, y);
        Array3 oddPositions(n, x, y);
        cout << "Прямые вызовы:\n";
        base.sum();
        even.sum();
        oddPositions.sum();
        // Указатель хранит адрес; & берет адрес существующего объекта.
        Array1* pointer = &even;
        cout << "Через указатель базового класса:\n";
        pointer->sum(); // Выбирается метод реального объекта Array2.
        Array1& reference = oddPositions;
        // Ссылка — другое имя того же объекта, копия не создается.
        cout << "Через ссылку базового класса:\n";
        reference.sum();
        cout << "Явный вызов базового метода для Array2:\n";
        even.Array1::sum();
    }
}
