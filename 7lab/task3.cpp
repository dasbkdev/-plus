#include "../common/input.h"
#include <iomanip>

// Программа переводит доллары и евро в рубли и обратно.
// Currency хранит общие данные, а потомки задают разные курсы.
// Курсы 74 и 99 взяты из задания и не меняются через интернет.
class Currency {
protected:
    double amount;
    bool toRubles;
public:
    Currency(double a, bool to) : amount(a), toRubles(to) {}
    virtual ~Currency() {}
    virtual double conv() const = 0;
    virtual void showConv() const { cout << conv() << '\n'; }
};

class Dollar : public Currency {
public:
    Dollar(double a, bool to) : Currency(a, to) {}
    double conv() const override {
        if (toRubles) return amount * 74;
        return amount / 74;
    }
    void showConv() const override {
        if (toRubles) cout << amount << " USD = " << conv() << " RUB\n";
        else cout << amount << " RUB = " << conv() << " USD\n";
    }
};

class Euro : public Currency {
public:
    Euro(double a, bool to) : Currency(a, to) {}
    double conv() const override {
        if (toRubles) return amount * 99;
        return amount / 99;
    }
    void showConv() const override {
        if (toRubles) cout << amount << " EUR = " << conv() << " RUB\n";
        else cout << amount << " RUB = " << conv() << " EUR\n";
    }
};

void show(const Currency& currency) {
    // Ссылка на родителя позволяет передать доллар или евро в одну функцию.
    currency.showConv(); // Виртуальный метод выбирается по типу валюты.
}

int main() {
    cout << fixed << setprecision(2);
    cout << "Учебные курсы: 1 USD = 74 RUB, 1 EUR = 99 RUB.\n";
    while (true) {
        cout << "\n1. Доллары в рубли\n2. Рубли в доллары\n3. Евро в рубли\n4. Рубли в евро\n0. Выход\n";
        int menu = readInt("Выбор: ", 0, 4);
        if (menu == 0) break;
        double amount = readDouble("Сумма: ", 0, 1e9);
        if (menu <= 2) {
            bool toRubles = (menu == 1);
            Dollar dollar(amount, toRubles);
            show(dollar);
        } else {
            bool toRubles = (menu == 3);
            Euro euro(amount, toRubles);
            show(euro);
        }
    }
}
