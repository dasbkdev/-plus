#include "../common/input.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

// Шаблон Array хранит два массива и складывает их по парам.
// Сначала выбираем тип чисел, затем способ заполнения массивов.
// Клавиатура и файл проверяются до выполнения вычислений.

// Читаем один отдельный фрагмент файла и не разрешаем мусор после числа.
template<class T>
bool fileValue(ifstream& file, T& value) {
    string token;
    if (!(file >> token)) return false;
    istringstream input(token);
    char extra;
    if (!(input >> value)) return false;
    if (input >> extra) return false;
    return true;
}

// В отличие от файла, при ошибке клавиатурного ввода просим число еще раз.
template<class T>
T readValue(const string& prompt) {
    while (true) {
        string line = readLine(prompt);
        istringstream input(line);
        T value;
        char extra;
        bool valid = true;
        if (!(input >> value)) valid = false;
        else {
            if (input >> extra) valid = false;
            if (!isfinite(double(value))) valid = false;
            if (value < -1000000 || value > 1000000) valid = false;
        }
        if (valid) return value;
        cout << "Введите одно число выбранного типа от -1000000 до 1000000.\n";
    }
}

template<class T>
class Array {
private:
    T a[100], b[100];
    int count = 0;
public:
    void keyboard() {
        count = readInt("Размер (1..100): ", 1, 100);
        cout << "Массив A:\n";
        for (int i = 0; i < count; i++) a[i] = readValue<T>("Элемент: ");
        cout << "Массив B:\n";
        for (int i = 0; i < count; i++) b[i] = readValue<T>("Элемент: ");
    }
    void randomFill() {
        count = readInt("Размер (1..100): ", 1, 100);
        for (int i = 0; i < count; i++) {
            // Сначала получаем число -10..10; T приводит его к выбранному типу.
            a[i] = T((rand() % 201 - 100) / 10.0);
            b[i] = T((rand() % 201 - 100) / 10.0);
        }
        cout << "Массивы заполнены числами от -10 до 10.\n";
    }
    void fromFile() {
        string path = readText("Путь к файлу: ", 500);
        ifstream file(path);
        int n;
        T first[100], second[100];
        if (!fileValue(file, n) || n < 1 || n > 100) {
            cout << "Ошибка открытия файла или размера. Данные сохранены.\n"; return;
        }
        // Сначала проверяем весь файл, только потом заменяем массивы.
        for (int i = 0; i < n; i++) {
            bool valid = fileValue(file, first[i]);
            if (valid) {
                if (!isfinite(double(first[i]))) valid = false;
                if (first[i] < -1000000 || first[i] > 1000000) valid = false;
            }
            if (!valid) {
                cout << "Ошибка массива A. Данные сохранены.\n"; return;
            }
        }
        for (int i = 0; i < n; i++) {
            bool valid = fileValue(file, second[i]);
            if (valid) {
                if (!isfinite(double(second[i]))) valid = false;
                if (second[i] < -1000000 || second[i] > 1000000) valid = false;
            }
            if (!valid) {
                cout << "Ошибка массива B. Данные сохранены.\n"; return;
            }
        }
        string extra;
        if (file >> extra) {
            cout << "Лишние данные в файле. Данные сохранены.\n";
            return;
        }
        count = n;
        for (int i = 0; i < count; i++) {
            a[i] = first[i];
            b[i] = second[i];
        }
        cout << "Файл прочитан.\n";
    }
    void show() const {
        if (count == 0) {
            cout << "Массивы пусты.\n";
            return;
        }
        cout << "A: ";
        for (int i = 0; i < count; i++) cout << a[i] << ' ';
        cout << "\nB: ";
        for (int i = 0; i < count; i++) cout << b[i] << ' ';
        cout << '\n';
    }
    void sum() const {
        if (count == 0) {
            cout << "Сначала заполните массивы.\n";
            return;
        }
        long double total = 0;
        // Общая сумма накапливается отдельно от каждой попарной суммы.
        cout << "Попарные суммы: ";
        for (int i = 0; i < count; i++) {
            T result = a[i] + b[i]; // Один алгоритм работает с int и double.
            cout << result << ' ';
            total += result;
        }
        cout << "\nСумма всех элементов двух массивов: " << total << '\n';
    }
};

template<class T>
void run() {
    // Меню одно; тип T меняется только при вызове run из main.
    Array<T> array;
    while (true) {
        cout << "\n1. Клавиатура\n2. Случайные числа\n3. Файл\n4. Показать массивы\n5. Сложить\n0. Назад\n";
        int menu = readInt("Выбор: ", 0, 5);
        if (menu == 0) break;
        if (menu == 1) array.keyboard();
        if (menu == 2) array.randomFill();
        if (menu == 3) array.fromFile();
        if (menu == 4) array.show();
        if (menu == 5) array.sum();
    }
}

int main() {
    srand(unsigned(time(nullptr))); // Начальное значение генератора берется из времени.
    while (true) {
        cout << "\n1. Тип int\n2. Тип double\n0. Выход\n";
        int menu = readInt("Тип: ", 0, 2);
        if (menu == 0) break;
        if (menu == 1) run<int>();
        else run<double>();
    }
}
