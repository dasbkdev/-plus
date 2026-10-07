#include "../common/input.h"

const string stages[3] = {"Равнина", "Горы", "Пустыня"};
class Tatra;

class Kamaz {
    string name; // Марка хранится в закрытом поле.
    double speed[3]; // Скорости на трёх участках маршрута.
    
public:
    Kamaz() : name("КАМАЗ"), speed{0, 0, 0} {}
    // Вводим только положительную скорость, чтобы время можно было вычислить.
    void set() {
        name = readText("Марка КАМАЗа: ", 60);
        for (int i = 0; i < 3; i++) {
            speed[i] = readDouble(stages[i] + ", скорость КАМАЗ (0.1..300 км/ч): ", 0.1, 300);
        }
    }
    // const означает, что метод не меняет данные машины.
    string getName() const { return name; }
    double getSpeed(int i) const { return speed[i]; }
    void show(int i) const { cout << speed[i]; }
    double time(const double distance[]) const {
        double hours = 0;
        // Время всего маршрута равно сумме времён трёх участков.
        for (int i = 0; i < 3; i++) hours += distance[i] / speed[i];
        return hours;
    }
};

class Tatra {
    string name; // Марка хранится в закрытом поле.
    double speed[3]; // Скорости на трёх участках маршрута.
    
public:
    Tatra() : name("Tatra"), speed{0, 0, 0} {}
    // Вводим только положительную скорость, чтобы время можно было вычислить.
    void set() {
        name = readText("Марка Tatra: ", 60);
        for (int i = 0; i < 3; i++) {
            speed[i] = readDouble(stages[i] + ", скорость Tatra (0.1..300 км/ч): ", 0.1, 300);
        }
    }
    // const означает, что метод не меняет данные машины.
    string getName() const { return name; }
    double getSpeed(int i) const { return speed[i]; }
    void show(int i) const { cout << speed[i]; }
    double time(const double distance[]) const {
        double hours = 0;
        for (int i = 0; i < 3; i++) hours += distance[i] / speed[i];
        return hours;
    }
    
};

// const-ссылка передаёт исходный объект без копирования и изменения.
int FrCreater(const Kamaz& kamaz, const Tatra& tatra, int i) {
    if (kamaz.getSpeed(i) > tatra.getSpeed(i)) return 1;
    if (kamaz.getSpeed(i) < tatra.getSpeed(i)) return -1;
    return 0;
}

int main() {
    Kamaz kamaz;
    Tatra tatra;
    double distance[3] = {};
    bool ready = false; // Пока данные не введены, результат считать нельзя.

    cout << "Обычная функция FrCreater получает скорости через getters.\n";
    cout << "Сравнение: 1 — быстрее КАМАЗ, 0 — равны, -1 — быстрее Tatra.\n";
    while (true) {
        cout << "\n1 Ввести данные  2 Таблица и победитель  0 Выход\n";
        int choice = readInt("Команда: ", 0, 2);
        if (choice == 0) break;

        if (choice == 1) {
            cout << "Обе машины проходят одни и те же три участка.\n";
            // В массиве по одной длине для равнины, гор и пустыни.
            for (int i = 0; i < 3; i++) {
                distance[i] = readDouble(stages[i] + ", длина (0.1..100000 км): ", 0.1, 100000);
            }
            kamaz.set();
            tatra.set();
            ready = true;
        }

        if (choice == 2) {
            if (!ready) {
                cout << "Сначала введите данные командой 1.\n";
                continue; // Возвращаемся к меню без вычислений.
            }
            cout << fixed << setprecision(3);
            cout << "\nКАМАЗ: " << kamaz.getName() << "; Tatra: " << tatra.getName() << '\n';
            cout << "Участок | км | КАМАЗ км/ч | Tatra км/ч | FrCreater\n";
            // Каждая итерация печатает результаты одного участка.
            for (int i = 0; i < 3; i++) {
                cout << stages[i] << " | " << distance[i] << " | ";
                kamaz.show(i);
                cout << " | ";
                tatra.show(i);
                cout << " | " << FrCreater(kamaz, tatra, i)  << '\n';
            }
            double kamazHours = kamaz.time(distance);
            double tatraHours = tatra.time(distance);
            cout << setprecision(9) << "Время КАМАЗ (ч): " << kamazHours
                 << "\nВремя Tatra (ч): " << tatraHours << '\n';

            // Из-за округления double очень близкие времена считаем равными.
            if (fabs(kamazHours - tatraHours) <= 1e-9) {
                cout << "Итог: ничья (разница времени не больше 0.000000001 ч).\n";
            } else if (kamazHours < tatraHours) {
                cout << "Победитель: КАМАЗ (" << kamaz.getName() << ")\n";
            } else {
                cout << "Победитель: Tatra (" << tatra.getName() << ")\n";
            }
        }
    }
    return 0;
}
