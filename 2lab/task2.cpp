#include "../common/input.h"
#include <ctime>

// Один объект studGroup описывает одного студента.
// Методы поиска и сортировки ниже вынесены за пределы класса.
class studGroup {
private:
    string name, surname, patronymic, birthDate, phone;

public:
    void input() {
        // Поля заполняются через метод, так как снаружи они закрыты.
        name = readText("Имя: ", 60);
        surname = readText("Фамилия: ", 60);
        patronymic = readText("Отчество (или -): ", 60);
        // Берём текущую дату, чтобы не принять будущую дату рождения.
        time_t now = time(nullptr); //Получаем текущее системное время в виде количества секунд с 1 января 1970 года
        tm* today = localtime(&now); //Преобразуем секунды now в удобную структуру tm с разделением на текущий год, месяц и день.
        int todayNumber = 21001231; //Задаём дефолтное число для текущей даты (31 декабря 2100 года) на случай, если функция localtime вернёт ошибку
        if (today != nullptr) {
            int year = today->tm_year + 1900; //.считаем реальный год (так как tm_year хранит количество лет, прошедших с 1900 года).
            int month = today->tm_mon + 1; //считаем месяц (так как tm_mon нумеруется от 0 до 11)
            todayNumber = year * 10000 + month * 100 + today->tm_mday; //Составляем число в формате ГГГГММДД для удобного сравнения с датой рождения
        }
        do {
            birthDate = readDate("Дата рождения ДД.ММ.ГГГГ: ");
            if (dateNumber(birthDate) > todayNumber) { //Перевод с ввода в числовой формат для сравнения с текущей датой
                cout << "Дата рождения не может быть в будущем.\n";
            }
        } while (dateNumber(birthDate) > todayNumber); //пока не введется корректная дата рождения, которая не превышает текущую дату
        phone = readPhone("Телефон: ");
    }

    void show() const { 
        cout << surname << " | " << name << " | " << patronymic << " | "
             << birthDate << " | " << phone << '\n';
    }

    string field(int choice) const {
        // Номер поля берём из меню поиска или сортировки.
        if (choice == 1) return name;
        if (choice == 2) return surname;
        if (choice == 3) return patronymic;
        if (choice == 4) return birthDate;
        return phone;
    }

    static void showAll(const studGroup group[], int count) {
        if (count == 0) {
            cout << "Группа пуста.\n";
            return;
        }
        cout << "№ | Фамилия | Имя | Отчество | Дата рождения | Телефон\n";
        for (int i = 0; i < count; i++) {
            cout << i + 1 << " | ";
            group[i].show();
        }
    }

    static void remove(studGroup group[], int& count, int index) {
        // Сдвиг записей закрывает место удалённого студента.
        for (int i = index; i < count - 1; i++) {
            group[i] = group[i + 1];
        }
        count--;
    }

    static void sort(studGroup group[], int count, int choice);
    static void search(const studGroup group[], int count, int choice);
};

// По условию поиск и сортировка определены вне класса.
void studGroup::sort(studGroup group[], int count, int choice) {
    // За один проход самая большая запись перемещается в конец.
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            bool swapNeeded;
            if (choice == 4) {
                // Дату сравниваем по году, месяцу и дню, а не как текст.
                int firstDate = dateNumber(group[j].birthDate);
                int secondDate = dateNumber(group[j + 1].birthDate);
                swapNeeded = firstDate > secondDate;
            } else {
                swapNeeded = group[j].field(choice) > group[j + 1].field(choice);
            }
            if (swapNeeded) {
                studGroup temp = group[j];
                group[j] = group[j + 1];
                group[j + 1] = temp;
            }
        }
    }
    showAll(group, count);
}

void studGroup::search(const studGroup group[], int count, int choice) {
    string value;
    if (choice == 4) {
        value = readDate("Дата: ");
    } else if (choice == 5) {
        value = readPhone("Телефон: ");
    } else {
        value = readText("Искомое значение: ", 60);
    }
    bool found = false; // Запоминаем, было ли хотя бы одно совпадение.
    for (int i = 0; i < count; i++) {
        if (group[i].field(choice) == value) {
            group[i].show();
            found = true;
        }
    }
    if (!found) {
        cout << "Студент не найден.\n";
    }
}

int main() {
    studGroup group[100];
    int count = 0; // Меняется при добавлении и удалении студента.
    while (true) {
        cout << "\n1 - добавить, 2 - удалить, 3 - таблица, 4 - сортировка, 5 - поиск, 0 - выход\n";
        int menu = readInt("Выбор: ", 0, 5);
        if (menu == 0) {
            break;
        }
        if (menu == 1) {
            if (count == 100) {
                cout << "Достигнут предел: 100 студентов.\n";
            } else {
                group[count].input();
                count++;
            }
        }
        if (menu == 2) {
            if (count == 0) {
                cout << "Группа пуста.\n";
            } else {
                studGroup::showAll(group, count);
                int number = readInt("Номер для удаления: ", 1, count);
                // Для пользователя номера с 1, а индексы массива начинаются с 0.
                studGroup::remove(group, count, number - 1);
            }
        }
        if (menu == 3) {
            studGroup::showAll(group, count);
        }
        if (menu == 4 || menu == 5) {
            cout << "1 - имя, 2 - фамилия, 3 - отчество, 4 - дата рождения, 5 - телефон\n";
            int field = readInt("Поле: ", 1, 5);
            if (menu == 4) {
                studGroup::sort(group, count, field);
            } else {
                studGroup::search(group, count, field);
            }
        }
    }
}
