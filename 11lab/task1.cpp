#include "../common/input.h"
#include <cstdlib>
#include <iomanip>

// Серия содержит не больше n выстрелов и заканчивается после попадания.
// Статическое поле p одно для всего класса, отдельный объект не нужен.
// Много серий позволяют оценить вероятность хотя бы одного попадания.
class Shooting {
private:
    static double p;
public:
    static void setProbability(double value) { p = value; }
    static double probability() { return p; }
    static int fire(int n) {
        for (int i = 0; i < n; i++) {
            // Деление переводит случайное целое в число от 0 включительно до 1.
            double random = rand() / (RAND_MAX + 1.0);
            if (random < p) return 1; // Серия завершается при первом попадании.
        }
        return 0;
    }
    static double estimate(int n, int trials) {
        int hits = 0;
        for (int i = 0; i < trials; i++) {
            int result = fire(n);
            hits += result;
        }
        // double нужен, чтобы результат деления не стал целым числом.
        return double(hits) / trials;
    }
    static double theoretical(int n) {
        double result = 0;
        // Это та же вероятность 1-(1-p)^n, посчитанная по выстрелам.
        // Добавляем вероятность попасть после всех предыдущих промахов.
        for (int i = 0; i < n; i++) result += (1 - result) * p;
        return result;
    }
};

double Shooting::p = 0.5; // Одно статическое поле для всех обращений к классу.

int main() {
    srand(2026);
    cout << fixed << setprecision(6);
    int n = 3;
    while (true) {
        cout << "\nПараметры: p = " << Shooting::probability() << ", n = " << n
             << "\n1. Изменить p и n\n2. Одна серия\n3. Оценить вероятность\n"
             << "4. Теоретическая вероятность\n5. Задать начальное число генератора\n0. Выход\n";
        int menu = readInt("Выбор: ", 0, 5);
        if (menu == 0) break;
        if (menu == 1) {
            double p = readDouble("Вероятность p (0..1): ", 0, 1);
            n = readInt("Максимум выстрелов n (0..10000): ", 0, 10000);
            Shooting::setProbability(p);
        }
        if (menu == 2) cout << "Результат серии (0 - промах, 1 - попадание): " << Shooting::fire(n) << '\n';
        if (menu == 3) {
            int limit = 100000;
            // Ограничиваем общий объем работы десятью миллионами выстрелов.
            if (n > 100) limit = 10000000 / n;
            int trials = readInt("Количество серий (1.." + to_string(limit) + "): ", 1, limit);
            cout << "Оценочная вероятность: " << Shooting::estimate(n, trials)
                 << "\nТеоретическая вероятность: " << Shooting::theoretical(n) << '\n';
        }
        if (menu == 4) cout << "Теоретическая вероятность: " << Shooting::theoretical(n) << '\n';
        if (menu == 5) {
            int seed = readInt("Начальное число (0..2147483647): ", 0, 2147483647);
            srand(unsigned(seed));
            cout << "Последовательность генератора перезапущена.\n";
        }
    }
}
