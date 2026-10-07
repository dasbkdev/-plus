#include "../common/input.h"

// Номер дня с начала 1900 года позволяет вычитать даты без часовых поясов.
int dayNumber(const string& date) {
    // Вырезаем день, месяц и год из строки ДД.ММ.ГГГГ.
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));
    int result = day - 1;
    // Сначала прибавляем дни всех полных лет.
    for (int y = 1900; y < year; y++) {
        if (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0)) {
            result += 366;
        } else {
            result += 365;
        }
    }
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) {
        days[1] = 29;
    }
    // Затем прибавляем дни полных месяцев текущего года.
    for (int m = 1; m < month; m++) {
        result += days[m - 1];
    }
    return result;
}

class Soft {
private:
    // В одном объекте находятся сведения об одной программе.
    string name, developer, endDate;
    double size;

public:
    // Первый конструктор задаёт начальные значения, второй получает готовые данные.
    Soft() : name(""), developer(""), endDate("01.01.1900"), size(0) {}
    Soft(string n, string d, double s, string date) : name(n), developer(d), endDate(date), size(s) {}
    ~Soft() {} // Поля string сами освобождают свою память.

    void input() {
        // Проверку числа дней в месяце выполняет readDate.
        name = readText("Название программы: ", 80);
        developer = readText("Разработчик: ", 80);
        size = readDouble("Объём в МБ (0..1000000000): ", 0, 1000000000);
        endDate = readDate("Дата окончания лицензии ДД.ММ.ГГГГ: ");
    }

    int daysLeft(const string& today) const {
        // Одинаковая дата даёт разность 0, прошедшая — отрицательную.
        int endDay = dayNumber(endDate);
        int currentDay = dayNumber(today);
        return endDay - currentDay;
    }

    void show(const string& today) const {
        int days = daysLeft(today);
        cout << name << " | " << developer << " | " << size << " МБ | " << endDate << " | ";
        // Знак разности показывает, истекла ли лицензия.
        if (days > 0) {
            cout << "осталось дней: " << days;
        } else if (days == 0) {
            cout << "истекает сегодня";
        } else {
            cout << "истекла дней назад: " << -days;
        }
        cout << '\n';
    }
};

int main() {
    Soft programs[100];
    int count = 0; // Фактическое число записей в массиве.
    while (true) {
        cout << "\n1 - добавить программу, 2 - вывести сроки лицензий, 0 - выход\n";
        int menu = readInt("Выбор: ", 0, 2);
        if (menu == 0) {
            break;
        }
        if (menu == 1) {
            if (count == 100) {
                cout << "Достигнут предел: 100 программ.\n";
            } else {
                programs[count].input();
                count++;
            }
        }
        if (menu == 2) {
            if (count == 0) {
                cout << "Программ нет.\n";
                continue;
            }
            string today = readDate("Дата расчёта ДД.ММ.ГГГГ: ");
            // Все лицензии проверяем относительно одной даты.
            cout << "Программа | Разработчик | Объём | Лицензия | Срок\n";
            for (int i = 0; i < count; i++) {
                programs[i].show(today);
            }
        }
    }
}
