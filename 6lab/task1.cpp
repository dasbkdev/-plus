#include "../common/input.h"
#include <iomanip>

// Программа хранит данные работника и менеджера.
// Менеджер получает общие методы работника через наследование.
// Проверки обычного ввода вынесены в общий файл input.h.
class Employee {
private:
    string name;
    string position;
    double salary;
public:
    // После двоеточия задаются начальные значения полей объекта.
    Employee() : name("Не задано"), position("Не задано"), salary(0) {}
    Employee(string n, string p, double s) : name(n), position(p), salary(s) {}
    ~Employee() {}
    void input() {
        name = readText("Имя: ", 63);
        position = readText("Должность: ", 63);
        salary = readDouble("Оклад в месяц (0..1000000000): ", 0, 1e9);
    }
    double annualSalary() const {
        // В году 12 месяцев. const означает, что поля не изменяются.
        return salary * 12;
    }
    void show() const {
        cout << "Работник: " << name << "\nДолжность: " << position
             << "\nОклад за месяц: " << salary << "\nОклад за год: " << annualSalary() << '\n';
    }
};

// По корректировке методички используется защищенное наследование.
class Manager : protected Employee {
private:
    double annual_bonus;
    string company_car;
    int stock_options;
public:
    Manager() : annual_bonus(0), company_car("Нет"), stock_options(0) {}
    Manager(string n, string p, double s, double b, string car, int options)
        : Employee(n, p, s), annual_bonus(b), company_car(car), stock_options(options) {}
    ~Manager() {}
    void input() {
        // Сначала вводятся общие данные, затем собственные данные менеджера.
        Employee::input();
        annual_bonus = readDouble("Бонус в год: ", 0, 1e9);
        company_car = readText("Машина компании: ", 63);
        stock_options = readInt("Число опционов: ", 0, 1000000);
    }
    // Открытые обертки разрешают обратиться к защищенным методам родителя.
    void showEmployee() const {
        Employee::show();
    }
    double employeeYear() const {
        return annualSalary();
    }
    void showOwn() const {
        cout << "Бонус за год: " << annual_bonus << "\nМашина: " << company_car
             << "\nОпционы: " << stock_options << '\n';
    }
    void show() const {
        Employee::show(); // Закрытые поля доступны через методы родителя.
        showOwn();
        cout << "Доход за год с бонусом: " << annualSalary() + annual_bonus << '\n';
    }
};

int main() {
    Employee employee;
    Manager manager;
    cout << fixed << setprecision(2);
    while (true) {
        // После каждого действия снова показываем меню.
        cout << "\n1. Создать работника\n2. Показать работника\n3. Создать менеджера\n"
             << "4. Только поля менеджера\n5. Все данные менеджера\n6. Объекты по умолчанию\n"
             << "7. Данные родителя через обертку\n8. Годовой оклад через обертку\n0. Выход\n";
        int menu = readInt("Выбор: ", 0, 8);
        if (menu == 0) break;
        if (menu == 1) employee.input();
        if (menu == 3) manager.input();
        if (menu == 2) employee.show();
        if (menu == 4) manager.showOwn();
        if (menu == 5) manager.show();
        if (menu == 7) manager.showEmployee();
        if (menu == 8) cout << "Годовой оклад: " << manager.employeeYear() << '\n';
        if (menu == 6) {
            Employee defaultEmployee;
            Manager defaultManager;
            defaultEmployee.show();
            defaultManager.show();
        }
    }
}
