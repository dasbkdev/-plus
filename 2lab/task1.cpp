#include "../common/input.h" //Подключаем сторонний заголовочный файл input.h, который лежит на папку выше (../) в папке common. В нём объявлены вспомогательные функции для безопасного ввода данных (например, readText, readTime, readInt).

// Один объект Aeroflot хранит один рейс.
// Все рейсы вместе хранятся в обычном массиве в main.
class Aeroflot { //чертежа (класса)
private:
    // private запрещает менять поля напрямую из main.
    string number, departure, destination, arrivalTime, departureTime, registration;

public:
    // Методы внутри класса являются встроенными (inline).
    void input() {
        // readText и readTime повторяют запрос, если ответ неверный.
        number = readText("Номер рейса: ", 20);
        departure = readText("Пункт отправления: ", 60);
        destination = readText("Пункт назначения: ", 60);
        arrivalTime = readTime("Время прибытия ЧЧ:ММ: ");
        departureTime = readTime("Время отправления ЧЧ:ММ: ");
        registration = readText("Место регистрации: ", 30);
    }

    // const: этот метод только показывает данные и не меняет их.
    void show() const { 
        cout << number << " | " << departure << " | " << destination << " | "
             << arrivalTime << " | " << departureTime << " | " << registration << '\n';
    }

    string field(int choice) const {
        // Возвращаем поле, которое пользователь выбрал для сортировки по индексу.
        if (choice == 1) return number; //Если передали 1 — возвращаем номер рейса.
        if (choice == 2) return departure;
        if (choice == 3) return destination;
        if (choice == 4) return arrivalTime;
        if (choice == 5) return departureTime;
        return registration;
    }

    static void showAll(const Aeroflot flights[], int count) {
        // static: метод работает с переданным массивом, а не с одним рейсом.
        if (count == 0) {
            cout << "Рейсов нет.\n";
            return;
        }
        cout << "Рейс | Откуда | Куда | Прибытие | Отправление | Регистрация\n";
        for (int i = 0; i < count; i++) {
            flights[i].show();
        }
    }

    static void sort(Aeroflot flights[], int count, int choice) {
        // Пузырьковая сортировка меняет местами соседние записи.
        for (int i = 0; i < count - 1; i++) { 
            // После каждого прохода один элемент уже стоит в конце правильно.
            for (int j = 0; j < count - 1 - i; j++) { //Внутренний цикл: сравнивает соседние пары элементов. С каждым шагом i правая часть массива уже отсортирована, поэтому вычитаем i
                if (flights[j].field(choice) > flights[j + 1].field(choice)) { //Сравниваем значение выбранного поля у левого элемента (j) и правого (j + 1). Если левое "больше" (по алфавиту/строково), их нужно поменять местами.
                    Aeroflot temp = flights[j]; //Создаём временный объект temp и сохраняем в него левый рейс.
                    flights[j] = flights[j + 1]; //Перезаписываем левый рейс правым
                    flights[j + 1] = temp; //В правый рейс записываем сохранённый из temp левый.
                }
            }
        }
        showAll(flights, count);
    }

    static void search(const Aeroflot flights[], int count) {
        string place = readText("Пункт назначения для поиска: ", 60);
        bool found = false;
        // Просматриваем все рейсы: совпадений может быть несколько.
        for (int i = 0; i < count; i++) {
            if (flights[i].destination == place) {
                flights[i].show();
                found = true;
            }
        }
        if (!found) {
            cout << "Рейс не найден.\n";
        }
    }
};

int main() {
    const int MAX = 100;
    Aeroflot flights[MAX];
    int count = 0; // Сколько ячеек массива уже занято.
    // После каждой операции снова показываем меню.
    while (true) {
        cout << "\n1 - добавить рейс, 2 - таблица, 3 - сортировка, 4 - поиск, 0 - выход\n";
        int menu = readInt("Выбор: ", 0, 4);
        // Для каждого пункта меню вызываем нужный метод класса.
        if (menu == 0) {
            break;
        }
        if (menu == 1) {
            if (count == MAX) {
                cout << "Достигнут предел: 100 рейсов.\n";
            } else {
                flights[count].input();
                count++;
            }
        }
        if (menu == 2) {
            Aeroflot::showAll(flights, count);
        }
        if (menu == 3) {
            cout << "1 - номер, 2 - отправление, 3 - назначение, 4 - прибытие,\n"
                 << "5 - время отправления, 6 - регистрация\n";
            int field = readInt("Поле: ", 1, 6);
            Aeroflot::sort(flights, count, field);
        }
        if (menu == 4) {
            Aeroflot::search(flights, count);
        }
    }
}
