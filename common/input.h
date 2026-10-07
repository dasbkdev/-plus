#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
using namespace std;

// Здесь только ввод. Алгоритмы самих задач находятся в файлах taskN.cpp.
// inline позволяет хранить эти небольшие функции в общем заголовочном файле.
inline string readLine(string prompt) {
    cout << prompt;
    string line;
    if (!getline(cin, line)) {
        cout << "\nВвод завершён.\n";
        exit(0);
    }
    return line;
}

inline string readText(string prompt, size_t maxLength = 100) {
    while (true) {
        string text = readLine(prompt);
        if (text.size() > maxLength) {
            cout << "Ошибка: введите непустой текст (до " << maxLength << " байт UTF-8).\n";
            continue;
        }
        // Убираем пробелы в начале и конце ответа.
        while (!text.empty() && (text.front() == ' ' || text.front() == '\t' || text.front() == '\r')) {
            text.erase(0, 1);
        }
        while (!text.empty() && (text.back() == ' ' || text.back() == '\t' || text.back() == '\r')) {
            text.pop_back();
        }

        bool valid = true;
        if (text.empty()) {
            valid = false;
        }
        for (unsigned char c : text) {
            // Служебные символы не должны ломать таблицу в консоли.
            if (c < 32 || c == 127) {
                valid = false;
            }
        }
        if (valid) {
            return text;
        }
        cout << "Ошибка: введите непустой текст (до " << maxLength << " байт UTF-8).\n";
    }
}

inline int readInt(string prompt, int low, int high) {
    while (true) {
        string line = readLine(prompt);
        // Читаем число из всей строки, чтобы не принять 12abc за число 12.
        istringstream input(line);
        int value = 0;
        char extra;
        input >> value;
        bool valid = !input.fail();
        if (input >> extra) {
            valid = false;
        }
        if (value < low || value > high) {
            valid = false;
        }
        if (valid) {
            return value;
        }
        cout << "Ошибка: нужно целое число от " << low << " до " << high << ".\n";
    }
}

inline double readDouble(string prompt, double low, double high) {
    while (true) {
        istringstream input(readLine(prompt));
        double value = 0;
        char extra;
        input >> value;
        bool valid = !input.fail();
        if (input >> extra) {
            valid = false;
        }
        // isfinite отсеивает бесконечность и недопустимый результат NaN.
        if (!isfinite(value) || value < low || value > high) {
            valid = false;
        }
        if (valid) {
            return value;
        }
        cout << "Ошибка: нужно конечное число от " << low << " до " << high
             << ". Дробная часть отделяется точкой.\n";
    }
}

inline bool validDate(string date) {
    if (date.size() != 10 || date[2] != '.' || date[5] != '.') {
        return false;
    }
    for (int i = 0; i < 10; i++) {
        if (i != 2 && i != 5 && (date[i] < '0' || date[i] > '9')) {
            return false;
        }
    }
    // substr берёт часть строки, stoi переводит её в целое число.
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));
    if (year < 1900 || year > 2100 || month < 1 || month > 12) {
        return false;
    }
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // Високосный год добавляет один день в феврале.
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) {
        days[1] = 29;
    }
    return day >= 1 && day <= days[month - 1];
}

// Запись ГГГГММДД позволяет правильно сравнить две даты как числа.
inline int dateNumber(string date) {
    return stoi(date.substr(6, 4)) * 10000 + stoi(date.substr(3, 2)) * 100
         + stoi(date.substr(0, 2));
}

inline string readDate(string prompt) {
    while (true) {
        string date = readText(prompt, 10);
        if (validDate(date)) {
            return date;
        }
        cout << "Ошибка: нужна существующая дата ДД.ММ.ГГГГ, год 1900..2100.\n";
    }
}

inline string readTime(string prompt) {
    while (true) {
        string time = readText(prompt, 5);
        bool valid = time.size() == 5;
        if (valid) {
            valid = time[2] == ':';
            for (int i = 0; i < 5; i++) {
                if (i != 2 && (time[i] < '0' || time[i] > '9')) {
                    valid = false;
                }
            }
        }
        if (valid) {
            int hours = stoi(time.substr(0, 2));
            int minutes = stoi(time.substr(3, 2));
            if (hours <= 23 && minutes <= 59) {
                return time;
            }
        }
        cout << "Ошибка: время должно быть от 00:00 до 23:59.\n";
    }
}

inline string readPhone(string prompt) {
    while (true) {
        string phone = readText(prompt, 16);
        size_t start = 0;
        if (phone[0] == '+') {
            start = 1;
        }
        bool valid = phone.size() - start >= 7 && phone.size() - start <= 15;
        for (size_t i = start; i < phone.size(); i++) {
            if (phone[i] < '0' || phone[i] > '9') {
                valid = false;
            }
        }
        if (valid) {
            return phone;
        }
        cout << "Ошибка: нужно 7..15 цифр; знак + допустим только в начале.\n";
    }
}

#endif
