#include "../common/input.h"

// Пользователь записывает и читает элементы массива из 100 чисел.
// Неверный индекс вызывает исключение до обращения к памяти.
// Обработчик показывает ошибку, после чего меню работает дальше.
class SafeArray {
private:
    int data[100] = {};
public:
    class Range {
        // Объект ошибки запоминает индекс, который ввел пользователь.
    public:
        int index;
        explicit Range(int i) : index(i) {}
    };
    void putel(int index, int value) {
        // Проверка должна идти перед записью в массив.
        if (index < 0 || index >= 100) throw Range(index);
        data[index] = value;
    }
    int getel(int index) const {
        if (index < 0 || index >= 100) throw Range(index);
        return data[index];
    }
};

int main() {
    SafeArray array;
    while (true) {
        cout << "\n1. Записать элемент\n2. Прочитать элемент\n3. Показать края массива\n0. Выход\n";
        int menu = readInt("Выбор: ", 0, 3);
        if (menu == 0) break;
        // В try находятся действия, которые могут выбросить Range.
        try {
            if (menu == 1 || menu == 2) {
                int index = readInt("Индекс (допустимы 0..99): ", -2147483647 - 1, 2147483647);
                if (menu == 1) {
                    int value = readInt("Значение: ", -2147483647 - 1, 2147483647);
                    array.putel(index, value);
                    cout << "Элемент записан.\n";
                } else {
                    int value = array.getel(index);
                    cout << "Элемент: " << value << '\n';
                }
            }
            if (menu == 3) {
                cout << "a[0] = " << array.getel(0);
                cout << "; a[99] = " << array.getel(99) << '\n';
            }
        } catch (const SafeArray::Range& error) {
            // const-ссылка дает прочитать ошибку без создания ее копии.
            // После обработки ошибки меню продолжает работу.
            cout << "Исключение Range: индекс " << error.index << " вне диапазона 0..99.\n";
        }
    }
}
