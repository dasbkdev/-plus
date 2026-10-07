#include "../common/input.h"
#include <fstream>

// Стек хранит состав: последний добавленный вагон выходит первым.
// При разделении четные номера идут на один путь, нечетные — на другой.
// Шаблон позволяет использовать этот же стек и для другого типа данных.

// Число в файле должно занимать целый токен, без приписанных символов.
bool fileInt(ifstream& file, int& value) {
    string token;
    if (!(file >> token)) return false;
    istringstream input(token);
    char extra;
    if (!(input >> value)) return false;
    if (input >> extra) return false;
    return true;
}

template<class T>
class Stack {
private:
    T data[100];
    int count = 0;
public:
    bool push(T value) {
        // Сначала проверяем вместимость, затем меняем массив и размер.
        if (count == 100) return false;
        data[count] = value;
        count++;
        return true;
    }
    bool pop(T& value) {
        if (count == 0) return false;
        count--;
        value = data[count]; // Ссылка передает найденный вагон обратно в вызывающий код.
        return true;
    }
    void show() const {
        if (!count) cout << "пусто";
        for (int i = count - 1; i >= 0; i--) cout << data[i] << ' ';
        cout << '\n';
    }
};

void split(const Stack<int>& train) {
    // Работаем с копией, чтобы исходный состав можно было показать еще раз.
    Stack<int> copy = train;
    Stack<int> even;
    Stack<int> odd;
    // & берет адрес стека, а -> вызывает его метод через указатель.
    Stack<int>* source = &copy;
    Stack<int>* evenTrack = &even;
    Stack<int>* oddTrack = &odd;
    int wagon;
    while (source->pop(wagon)) {
        // pop возвращает false, когда все вагоны из копии уже извлечены.
        if (wagon % 2 == 0) evenTrack->push(wagon);
        else oddTrack->push(wagon);
    }
    cout << "Общий состав (сохраненная копия): ";
    train.show();
    cout << "Входной путь после разделения: ";
    source->show();
    cout << "Четное направление: ";
    evenTrack->show();
    cout << "Нечетное направление: ";
    oddTrack->show();
}

int main() {
    Stack<int> train;
    cout << "Номера вагонов: 1..1000000. Показ от вершины стека к основанию.\n";
    while (true) {
        cout << "\n1. Состав с клавиатуры\n2. Состав из файла\n3. Показать состав\n4. Разделить\n"
             << "5. Добавить вагон\n6. Удалить верхний вагон\n0. Выход\n";
        int menu = readInt("Выбор: ", 0, 6);
        if (menu == 0) break;
        if (menu == 1) {
            Stack<int> next;
            int n = readInt("Вагонов (0..100): ", 0, 100);
            for (int i = 0; i < n; i++) {
                int wagon = readInt("Номер вагона: ", 1, 1000000);
                next.push(wagon);
            }
            train = next;
        }
        if (menu == 2) {
            string path = readText("Путь к файлу: ", 500);
            ifstream file(path);
            int n;
            if (!fileInt(file, n) || n < 0 || n > 100) {
                cout << "Ошибка открытия файла или числа вагонов.\n"; continue;
            }
            Stack<int> next;
            bool correct = true;
            // Новый состав пока временный: ошибка файла не испортит старый.
            for (int i = 0; i < n; i++) {
                int wagon;
                if (!fileInt(file, wagon) || wagon < 1 || wagon > 1000000) {
                    correct = false;
                    break;
                }
                next.push(wagon);
            }
            string extra;
            // После указанного количества вагонов в файле не должно быть данных.
            if (file >> extra) correct = false;
            if (correct) {
                train = next;
                cout << "Состав загружен.\n";
            }
            else cout << "Ошибка файла. Предыдущий состав сохранен.\n";
        }
        if (menu == 3) {
            cout << "Общий состав: ";
            train.show();
        }
        if (menu == 4) split(train);
        if (menu == 5) {
            int wagon = readInt("Номер вагона: ", 1, 1000000);
            if (train.push(wagon)) cout << "Вагон добавлен.\n";
            else cout << "Стек заполнен.\n";
        }
        if (menu == 6) {
            int wagon;
            if (train.pop(wagon)) cout << "Удален вагон " << wagon << '\n';
            else cout << "Стек пуст.\n";
        }
    }
}
