#include "../common/input.h"

// Каждый объект хранит данные одного товара.
// Доход считаем простой формулой: разница цен * количество.
class Nomenclature {
private:
    // Пользователь изменяет закрытые поля только через input.
    string name;
    double wholesale, retail;
    int quantity;

public:
    // Конструктор создаёт объект с определёнными начальными значениями.
    Nomenclature() : name(""), wholesale(0), retail(0), quantity(0) {}
    Nomenclature(string n, double w, double r, int q) : name(n), wholesale(w), retail(r), quantity(q) {}
    // Динамическую память не выделяем, поэтому деструктор пустой.
    ~Nomenclature() {}

    void input() {
        // Отрицательные цены и количество отклоняет общий ввод.
        name = readText("Название товара: ", 80);
        wholesale = readDouble("Оптовая цена (0..1000000): ", 0, 1000000);
        retail = readDouble("Розничная цена (0..1000000): ", 0, 1000000);
        quantity = readInt("Количество (0..1000000): ", 0, 1000000);
    }

    double profit() const {
        double difference = retail - wholesale;
        return difference * quantity;
    }

    void show() const {
        // setprecision(2) оставляет две цифры после точки у цен и дохода.
        cout << fixed << setprecision(2) << name << " | " << wholesale << " | " << retail
             << " | " << quantity << " | " << profit() << '\n';
    }

    static void showAll(const Nomenclature goods[], int count) {
        // static-метод получает сразу весь массив товаров.
        cout << "Товар | Оптовая цена | Розничная цена | Количество | Доход\n";
        double total = 0;
        // Складываем доходы всех введённых товаров.
        for (int i = 0; i < count; i++) {
            goods[i].show();
            total += goods[i].profit();
        }
        if (count == 0) {
            cout << "Склад пуст.\n";
        }
        cout << fixed << setprecision(2) << "Общий доход: " << total << '\n';
    }

    double numberField(int field) const {
        // Эта функция выбирает числовое поле для поиска и сортировки.
        if (field == 2) return wholesale;
        if (field == 3) return retail;
        return quantity;
    }

    static void sort(Nomenclature goods[], int count, int field) {
        // Сравниваем соседние товары и меняем их местами.
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - 1 - i; j++) {
                bool exchange;
                if (field == 1) {
                    exchange = goods[j].name > goods[j + 1].name;
                } else {
                    exchange = goods[j].numberField(field) > goods[j + 1].numberField(field);
                }
                if (exchange) {
                    // Временно сохраняем товар, чтобы поменять две записи местами.
                    Nomenclature temp = goods[j];
                    goods[j] = goods[j + 1];
                    goods[j + 1] = temp;
                }
            }
        }
        showAll(goods, count);
    }

    static void search(const Nomenclature goods[], int count, int field) {
        string text;
        double value = 0;
        if (field == 1) {
            text = readText("Название: ", 80);
        } else if (field == 4) {
            value = readInt("Количество: ", 0, 1000000);
        } else {
            value = readDouble("Цена: ", 0, 1000000);
        }
        bool found = false;
        // Сравниваем текст с текстом, а цену или количество — с числом.
        for (int i = 0; i < count; i++) {
            bool matches;
            if (field == 1) {
                matches = goods[i].name == text;
            } else {
                matches = goods[i].numberField(field) == value;
            }
            if (matches) {
                goods[i].show();
                found = true;
            }
        }
        if (!found) {
            cout << "Товар не найден.\n";
        }
    }
};

int main() {
    // При создании массива вызывается конструктор по умолчанию.
    Nomenclature goods[100];
    int count = 0;
    while (true) {
        cout << "\n1 - добавить товар, 2 - таблица и доход, 3 - сортировка, 4 - поиск, 0 - выход\n";
        int menu = readInt("Выбор: ", 0, 4);
        if (menu == 0) {
            break;
        }
        if (menu == 1) {
            if (count == 100) {
                cout << "Достигнут предел: 100 товаров.\n";
            } else {
                goods[count].input();
                // Новая запись занимает следующую свободную ячейку.
                count++;
            }
        }
        if (menu == 2) {
            Nomenclature::showAll(goods, count);
        }
        if (menu == 3 || menu == 4) {
            cout << "1 - название, 2 - оптовая цена, 3 - розничная цена, 4 - количество\n";
            int field = readInt("Поле: ", 1, 4);
            if (menu == 3) {
                Nomenclature::sort(goods, count, field);
            } else {
                Nomenclature::search(goods, count, field);
            }
        }
    }
}
