#include "../common/input.h"

// Автобаза хранит водителей, автомобили и назначенные рейсы.
// Перед назначением проверяем, свободны ли водитель и машина.
// Выполненный рейс освобождает их для следующего задания.
class Driver {
private:
    string name;
    // Отстранение и занятость — разные причины запрета нового рейса.
    bool suspended = false;
    bool busy = false;
public:
    void setName(string value) { name = value; }
    bool available() const {
        if (suspended) return false;
        if (busy) return false;
        return true;
    }
    void setBusy(bool value) { busy = value; }
    void suspend(bool value) { suspended = value; }
    void show() const {
        cout << name;
        if (suspended) cout << "; отстранен";
        else cout << "; допущен";
        if (busy) cout << "; в рейсе\n";
        else cout << "; свободен\n";
    }
};

class Car {
private:
    string number;
    // Даже свободную машину нельзя назначать, если ей нужен ремонт.
    bool repair = false;
    bool busy = false;
public:
    void setNumber(string value) { number = value; }
    bool available() const {
        if (repair) return false;
        if (busy) return false;
        return true;
    }
    bool isBusy() const { return busy; }
    void setBusy(bool value) { busy = value; }
    void setRepair(bool value) { repair = value; }
    void show() const {
        cout << number;
        if (repair) cout << "; требуется ремонт";
        else cout << "; исправен";
        if (busy) cout << "; в рейсе\n";
        else cout << "; свободен\n";
    }
};

class Depot {
private:
    class Trip {
        // Вложенный класс нужен только для рейсов этой автобазы.
    private:
        string route;
        // В рейсе храним индексы водителя и машины из общих массивов.
        int driver = 0, car = 0;
        bool done = false;
    public:
        void create(string r, int d, int c) {
            route = r;
            driver = d;
            car = c;
        }
        int driverIndex() const { return driver; }
        int carIndex() const { return car; }
        bool completed() const { return done; }
        void finish() { done = true; }
        void show() const {
            cout << route << "; водитель " << driver + 1 << "; авто " << car + 1;
            if (done) cout << "; выполнен\n";
            else cout << "; выполняется\n";
        }
    };
    Driver* drivers;
    Car* cars; // Агрегация: эти массивы созданы снаружи автобазы.
    int driverCount = 0, carCount = 0, tripCount = 0;
    Trip trips[100]; // Композиция: рейсы принадлежат автобазе.
public:
    // Указатели сохраняют адреса массивов, которые созданы в main.
    Depot(Driver d[], Car c[]) : drivers(d), cars(c) {}
    void addDriver() {
        // Проверяем место до записи нового человека в массив.
        if (driverCount == 100) {
            cout << "Список водителей заполнен.\n";
            return;
        }
        string name = readText("ФИО водителя: ");
        drivers[driverCount].setName(name);
        driverCount++;
    }
    void addCar() {
        if (carCount == 100) {
            cout << "Список автомобилей заполнен.\n";
            return;
        }
        string number = readText("Номер автомобиля: ", 20);
        cars[carCount].setNumber(number);
        carCount++;
    }
    void show() const {
        cout << "Водители:\n";
        // В массиве индексы с нуля, а пользователю показываем номера с единицы.
        for (int i = 0; i < driverCount; i++) {
            cout << i + 1 << ". ";
            drivers[i].show();
        }
        cout << "Автомобили:\n";
        for (int i = 0; i < carCount; i++) {
            cout << i + 1 << ". ";
            cars[i].show();
        }
        cout << "Рейсы:\n";
        for (int i = 0; i < tripCount; i++) {
            cout << i + 1 << ". ";
            trips[i].show();
        }
        if (!tripCount) cout << "Рейсов нет.\n";
    }
    void assign() {
        // Для нового рейса нужны записи в обоих списках и свободное место.
        if (!driverCount || !carCount || tripCount == 100) {
            cout << "Нужны водитель, автомобиль и свободное место в списке рейсов.\n"; return;
        }
        int d = readInt("Номер водителя: ", 1, driverCount) - 1;
        int c = readInt("Номер авто: ", 1, carCount) - 1;
        if (!drivers[d].available() || !cars[c].available()) {
            cout << "Водитель или автомобиль недоступен. Рейс не назначен.\n"; return;
        }
        string route = readText("Маршрут заявки: ");
        trips[tripCount].create(route, d, c);
        tripCount++;
        // Один автомобиль и один водитель не могут выполнять два рейса сразу.
        drivers[d].setBusy(true);
        cars[c].setBusy(true);
        cout << "Рейс назначен.\n";
    }
    void finish() {
        if (tripCount == 0) {
            cout << "Рейсов нет.\n";
            return;
        }
        int t = readInt("Номер рейса: ", 1, tripCount) - 1;
        if (trips[t].completed()) {
            cout << "Рейс уже выполнен.\n";
            return;
        }
        int broken = readInt("Состояние авто: 0 - исправно, 1 - нужен ремонт: ", 0, 1);
        trips[t].finish();
        int d = trips[t].driverIndex();
        int c = trips[t].carIndex();
        // Завершение рейса одновременно освобождает человека и машину.
        drivers[d].setBusy(false);
        cars[c].setBusy(false);
        cars[c].setRepair(broken == 1);
        cout << "Рейс выполнен, состояние автомобиля сохранено.\n";
    }
    void repairRequest() {
        if (driverCount == 0 || carCount == 0) {
            cout << "Нет водителей или автомобилей.\n";
            return;
        }
        int d = readInt("Номер водителя: ", 1, driverCount) - 1;
        int c = readInt("Номер авто: ", 1, carCount) - 1;
        if (cars[c].isBusy()) {
            bool assigned = false;
            // Ищем действующий рейс с этой парой водителя и автомобиля.
            for (int i = 0; i < tripCount; i++) {
                if (trips[i].completed()) continue;
                if (trips[i].driverIndex() != d) continue;
                if (trips[i].carIndex() != c) continue;
                assigned = true;
            }
            if (!assigned) {
                cout << "Этот автомобиль закреплен за другим водителем.\n";
                return;
            }
            cout << "Сначала завершите рейс и укажите, что нужен ремонт.\n";
            return;
        }
        cars[c].setRepair(true);
        // Флаг ремонта сразу исключает машину из новых назначений.
        cout << "Заявка водителя на ремонт принята.\n";
    }
    void suspendDriver() {
        // Допуск влияет на будущие рейсы, а текущий остается в истории.
        if (driverCount == 0) {
            cout << "Водителей нет.\n";
            return;
        }
        int d = readInt("Номер водителя: ", 1, driverCount) - 1;
        int value = readInt("1 - отстранить, 0 - допустить: ", 0, 1);
        drivers[d].suspend(value == 1);
        cout << "Допуск изменен. Текущий рейс можно завершить; новый получит только допущенный водитель.\n";
    }
    void repairComplete() {
        // Отмечать ремонт завершенным можно только у свободной машины.
        if (carCount == 0) {
            cout << "Автомобилей нет.\n";
            return;
        }
        int c = readInt("Номер авто: ", 1, carCount) - 1;
        if (cars[c].isBusy()) {
            cout << "Нельзя ремонтировать автомобиль во время рейса.\n";
            return;
        }
        cars[c].setRepair(false);
        cout << "Автомобиль исправен.\n";
    }
};

int main() {
    // Массивы существуют все время работы, их адреса остаются действительными.
    Driver drivers[100];
    Car cars[100];
    Depot depot(drivers, cars);
    while (true) {
        cout << "\n1. Добавить водителя\n2. Добавить авто\n3. Списки\n4. Назначить рейс\n"
             << "5. Завершить рейс\n6. Заявка водителя на ремонт\n7. Допуск водителя\n8. Ремонт завершен\n0. Выход\n";
        int menu = readInt("Выбор: ", 0, 8);
        if (menu == 0) break;
        if (menu == 1) depot.addDriver();
        if (menu == 2) depot.addCar();
        if (menu == 3) depot.show();
        if (menu == 4) depot.assign();
        if (menu == 5) depot.finish();
        if (menu == 6) depot.repairRequest();
        if (menu == 7) depot.suspendDriver();
        if (menu == 8) depot.repairComplete();
    }
}
