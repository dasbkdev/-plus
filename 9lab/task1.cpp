#include "../common/input.h"

// Две шаблонные функции ищут максимум и сортируют массив.
// T заменяется на int или double при вызове функции.
// Сам алгоритм для обоих типов остается одинаковым.
template<class T>
T maximum(const T data[], int n) {
    // Считаем первый элемент максимальным и проверяем остальные.
    T result = data[0];
    for (int i = 1; i < n; i++)
        if (data[i] > result) result = data[i];
    return result;
}

template<class T>
void sortArray(T data[], int n) {
    // Каждый проход ставит на свое место наименьший оставшийся элемент.
    for (int i = 0; i < n - 1; i++) {
        int smallest = i;
        for (int j = i + 1; j < n; j++)
            if (data[j] < data[smallest]) smallest = j;
        T temporary = data[i];
        // Временная переменная не дает потерять число при обмене.
        data[i] = data[smallest];
        data[smallest] = temporary;
    }
}

template<class T>
void process(T data[], int n) {
    // Общая последовательность действий для массива любого выбранного типа.
    cout << "До сортировки: ";
    for (int i = 0; i < n; i++) cout << data[i] << ' ';
    cout << "\nМаксимум: " << maximum(data, n) << '\n';
    sortArray(data, n); // Компилятор создает вариант для нужного типа T.
    cout << "По возрастанию: ";
    for (int i = 0; i < n; i++) cout << data[i] << ' ';
    cout << '\n';
}

int main() {
    while (true) {
        cout << "\n1. Целые числа (int)\n2. Вещественные числа (double)\n0. Выход\n";
        int menu = readInt("Выбор: ", 0, 2);
        if (menu == 0) break;
        int n = readInt("Размер (1..100): ", 1, 100);
        if (menu == 1) {
            int data[100];
            for (int i = 0; i < n; i++) data[i] = readInt("Элемент: ", -1000000, 1000000);
            process(data, n); // Здесь T становится int.
        } else {
            double data[100];
            for (int i = 0; i < n; i++) data[i] = readDouble("Элемент: ", -1e6, 1e6);
            process(data, n); // Здесь T становится double.
        }
    }
}
