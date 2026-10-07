#include "../common/input.h"
#include <iomanip>

// Здесь сравниваются три способа доступа к методам родителя.
// Поля работника и менеджера во всех вариантах остаются закрытыми.
// Изменяется только способ вызова общих методов извне.
class Employee {
private:
    string name;
    string position;
    double salary;
public:
    Employee(string n, string p, double s) : name(n), position(p), salary(s) {}
    // const нужен, потому что расчет не меняет данные работника.
    double annualSalary() const { return salary * 12; }
    void show() const {
        cout << "Работник: " << name << ", должность: " << position << ", оклад: " << salary
             << ", за год: " << annualSalary() << '\n';
    }
};

// private-наследование закрывает доступ извне, но не из методов потомка.
class ManagerWrapper : private Employee {
private:
    double annual_bonus;
    string company_car;
    int stock_options;
public:
    ManagerWrapper(string n, string p, double s, double b, string car, int options)
        : Employee(n, p, s), annual_bonus(b), company_car(car), stock_options(options) {}
    void showManager() const {
        Employee::show();
        cout << "Бонус: " << annual_bonus << "; машина: " << company_car
             << "; опционы: " << stock_options << '\n';
    }
    double managerYear() const { return annualSalary(); }
};

class ManagerUsing : private Employee {
private:
    double annual_bonus;
    string company_car;
    int stock_options;
public:
    ManagerUsing(string n, string p, double s, double b, string car, int options)
        : Employee(n, p, s), annual_bonus(b), company_car(car), stock_options(options) {}
    using Employee::show; // Выборочно возвращаем public-доступ к методу.
    // Само закрытое поле salary при этом не открывается.
    using Employee::annualSalary;
    void showOwn() const {
        cout << "Бонус: " << annual_bonus << "; машина: " << company_car
             << "; опционы: " << stock_options << '\n';
    }
};

// При public-наследовании открытые методы родителя доступны сразу.
class ManagerPublic : public Employee {
private:
    double annual_bonus;
    string company_car;
    int stock_options;
public:
    ManagerPublic(string n, string p, double s, double b, string car, int options)
        : Employee(n, p, s), annual_bonus(b), company_car(car), stock_options(options) {}
    void showOwn() const {
        cout << "Бонус: " << annual_bonus << "; машина: " << company_car
             << "; опционы: " << stock_options << '\n';
    }
};

int main() {
    cout << fixed << setprecision(2);
    while (true) {
        cout << "\n1. Метод-обертка\n2. Объявление using\n3. Public-наследование\n"
             << "4. Пояснение доступа\n0. Выход\n";
        int menu = readInt("Выбор: ", 0, 4);
        if (menu == 0) break;
        if (menu == 4) {
            cout << "Private-поля Employee недоступны потомку напрямую при любом наследовании.\n"
                 << "Доступ к ним дают методы Employee; при необходимости поле объявляют protected.\n"
                 << "Private-наследование закрывает public/protected-члены от внешнего кода.\n"
                 << "Обертка, using или public-наследование открывают нужные методы извне.\n";
            continue;
        }
        string name = readText("Имя: ", 63);
        string position = readText("Должность: ", 63);
        double salary = readDouble("Оклад: ", 0, 1e9);
        double bonus = readDouble("Бонус за год: ", 0, 1e9);
        string car = readText("Машина компании: ", 63);
        int options = readInt("Опционы: ", 0, 1000000);
        if (menu == 1) {
            // Обертка сама вызывает закрывшийся для внешнего кода метод.
            ManagerWrapper manager(name, position, salary, bonus, car, options);
            manager.showManager();
            cout << "Годовой оклад через обертку: " << manager.managerYear() << '\n';
        }
        if (menu == 2) {
            // using открыл метод show(), поэтому его можно вызвать напрямую.
            ManagerUsing manager(name, position, salary, bonus, car, options);
            manager.show();
            manager.showOwn();
            cout << "Годовой оклад через using: " << manager.annualSalary() << '\n';
        }
        if (menu == 3) {
            ManagerPublic manager(name, position, salary, bonus, car, options);
            manager.show();
            manager.showOwn();
            cout << "Годовой оклад через public: " << manager.annualSalary() << '\n';
        }
    }
}
