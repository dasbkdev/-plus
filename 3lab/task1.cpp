#include "../common/input.h"
#include <ctime>

// Три конструктора заполняют одно и то же поле seconds.
// Разница только в том, как пользователь задаёт время.
class Timer {
private:
    int seconds;

public:
    // Перегрузка позволяет задать время тремя способами.
    Timer(int value) : seconds(value) {}
    // atoi переводит заранее проверенную строку цифр в целое число.
    Timer(const char* value) : seconds(atoi(value)) {}
    Timer(int minutes, int value) : seconds(minutes * 60 + value) {}

    void run() {
        while (seconds > 0) {
            cout << seconds << '\n' << flush;
            clock_t start = clock();
            if (start == clock_t(-1)) {
                cout << "Таймер процессора недоступен.\n";
                return;
            }
            // По условию используем clock: отсчитывается процессорное время.
            while (true) {
                clock_t current = clock();
                if (current == clock_t(-1) || current < start) {
                    cout << "Ошибка часов процессора.\n";
                    return;
                }
                double passed = double(current - start) / CLOCKS_PER_SEC;
                if (passed >= 1.0) {
                    break;
                }
            }
            seconds--; // Одна секунда прошла, уменьшаем остаток.
        }
        cout << "0\nВремя вышло!\a\n";
    }
};

int main() {
    while (true) {
        cout << "\n1 - секунды числом, 2 - секунды строкой, 3 - минуты и секунды, 0 - выход\n";
        int menu = readInt("Выбор: ", 0, 3);
        if (menu == 0) {
            break;
        }
        if (menu == 1) {
            int seconds = readInt("Секунды (0..3600): ", 0, 3600);
            Timer timer(seconds);
            timer.run();
        }
        if (menu == 2) {
            string text;
            int value;
            bool valid;
            do {
                text = readText("Строка секунд (0..3600): ", 4);
                valid = true;
                // До atoi проверяем каждый символ, чтобы не принять текст за ноль.
                for (char c : text) {
                    if (c < '0' || c > '9') {
                        valid = false;
                    }
                }
                value = 0;
                if (valid) {
                    value = atoi(text.c_str());
                }
                if (!valid || value > 3600) {
                    cout << "Ошибка: введите цифрами число от 0 до 3600.\n";
                }
            } while (!valid || value > 3600);
            Timer timer(text.c_str()); // c_str даёт строку в формате const char*.
            timer.run();
        }
        if (menu == 3) {
            int minutes = readInt("Минуты (0..60): ", 0, 60);
            int maxSeconds = 59;
            if (minutes == 60) {
                maxSeconds = 0; // Общее время не должно превышать час.
            }
            int seconds = readInt("Секунды: ", 0, maxSeconds);
            Timer timer(minutes, seconds);
            timer.run();
        }
    }
}
