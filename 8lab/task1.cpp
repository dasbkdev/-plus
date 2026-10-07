#include "../common/input.h"
#include <iomanip>

// Два клиента могут оплачивать заказы и переводить деньги друг другу.
// Счет существует отдельно, а карта хранится внутри клиента.
// Все суммы считаются в целых копейках, чтобы не терять дробные деньги.
const long long MAX_MONEY = 100000000000LL;

// Разбираем сумму как текст: например, 12.34 превращается в 1234 копейки.
long long readMoney(const string& prompt) {
    while (true) {
        string text = readText(prompt, 100);
        bool valid = true;
        long long cents = 0;
        int decimals = 0;
        bool point = false;
        for (char symbol : text) {
            if (symbol == '.' && !point) {
                point = true;
                continue;
            }
            if (symbol < '0' || symbol > '9') {
                valid = false;
                break;
            }
            // Приписываем очередную цифру справа к уже собранному числу.
            cents = cents * 10 + symbol - '0';
            if (point) decimals++;
            if (cents > MAX_MONEY || decimals > 2) {
                valid = false;
                break;
            }
        }
        if (text.empty() || text.front() == '.' || text.back() == '.') valid = false;
        if (valid) {
            // Для 12 добавляем два нуля, для 12.3 — один ноль.
            for (int i = decimals; i < 2; i++) cents *= 10;
            if (cents > 0 && cents <= MAX_MONEY) return cents;
        }
        cout << "Введите сумму 0.01..1000000000, не более двух знаков после точки.\n";
    }
}

void showMoney(long long cents) {
    // Деление дает целую часть, остаток от деления — копейки.
    cout << cents / 100 << '.' << setw(2) << setfill('0') << cents % 100 << setfill(' ');
}

class Account {
private:
    int number;
    // Целое число здесь означает именно копейки, а не целые денежные единицы.
    long long balance;
    bool active;
public:
    Account(int n, long long b) : number(n), balance(b), active(true) {}
    bool isActive() const { return active; }
    long long getBalance() const { return balance; }
    void show() const {
        cout << "Счет " << number;
        if (active) cout << " открыт; остаток: ";
        else cout << " закрыт; остаток: ";
        showMoney(balance);
        cout << '\n';
    }
    bool deposit(long long amount) {
        if (!active) return false;
        if (amount > MAX_MONEY - balance) return false;
        balance += amount;
        return true;
    }
    bool withdraw(long long amount) {
        if (!active) return false;
        if (amount > balance) return false;
        balance -= amount;
        return true;
    }
    bool transfer(Account& other, long long amount) {
        // other — ссылка на счет получателя, this — адрес текущего счета.
        if (this == &other) return false;
        if (!active || !other.active) return false;
        if (amount > balance) return false;
        if (amount > MAX_MONEY - other.balance) return false;
        balance -= amount; // Проверки завершены до изменения двух счетов.
        other.balance += amount;
        return true;
    }
    bool cancel() {
        // Закрывать счет с оставшимися деньгами нельзя.
        if (!active) return false;
        if (balance != 0) return false;
        active = false;
        return true;
    }
};

class Client {
private:
    class Card {
    private:
        bool blocked = false;
    public:
        bool isBlocked() const { return blocked; }
        void block() { blocked = true; }
    };
    string name;
    Account* account; // Агрегация: счет существует независимо от клиента.
    Card card; // Композиция: карта является частью клиента.
public:
    Client(string n, Account& a) : name(n), account(&a) {}
    void show() const {
        cout << "Клиент: " << name << "; карта: ";
        if (card.isBlocked()) cout << "заблокирована\n";
        else cout << "активна\n";
        account->show();
    }
    Account& getAccount() { return *account; }
    bool canPay() const {
        // Стрелка -> вызывает метод объекта по сохраненному указателю.
        if (!account->isActive()) {
            cout << "Счет закрыт.\n";
            return false;
        }
        if (card.isBlocked()) {
            cout << "Карта заблокирована.\n";
            return false;
        }
        return true;
    }
    void blockCard() { card.block(); }
    void cancelAccount() {
        if (account->cancel()) {
            card.block();
            cout << "Счет аннулирован, карта заблокирована.\n";
        }
        else cout << "Нельзя закрыть: счет уже закрыт или его остаток не равен нулю.\n";
    }
};

class Administrator {
public:
    void blockForExcess(Client& client) const {
        // Блокировка запрещает оплату картой, но не уничтожает остаток счета.
        client.blockCard();
        cout << "Платеж превышает остаток. Администратор заблокировал карту. Деньги не списаны.\n";
    }
};

int main() {
    Account first(1001, 100000), second(1002, 50000);
    Client clients[2] = {Client("Клиент 1", first), Client("Клиент 2", second)};
    Administrator admin;
    int current = 0;
    cout << "Учебные счета: 1001 = 1000.00; 1002 = 500.00.\n";
    while (true) {
        cout << "\nТекущий клиент: " << current + 1 << "\n1. Все счета\n2. Пополнить счет\n"
             << "3. Оплатить заказ\n4. Перевести другому клиенту\n5. Заблокировать карту\n"
             << "6. Аннулировать счет\n7. Сменить клиента\n8. Снять в кассе банка\n0. Выход\n";
        int menu = readInt("Выбор: ", 0, 8);
        if (menu == 0) break;
        // Ссылки позволяют работать с выбранным клиентом без его копии.
        Client& client = clients[current];
        Account& account = client.getAccount();
        if (menu == 1) {
            clients[0].show();
            clients[1].show();
        }
        if (menu == 7) current = readInt("Номер клиента (1 или 2): ", 1, 2) - 1;
        if (menu == 5) {
            client.blockCard();
            cout << "Карта заблокирована клиентом.\n";
        }
        if (menu == 6) client.cancelAccount();
        if (menu == 2 || menu == 8) {
            if (!account.isActive()) {
                cout << "Счет закрыт.\n";
                continue;
            }
            long long amount = readMoney("Сумма: ");
            bool ok;
            if (menu == 2) ok = account.deposit(amount);
            else ok = account.withdraw(amount);
            if (ok) cout << "Операция выполнена.\n";
            else cout << "Недостаточно средств или превышен предел остатка.\n";
        }
        if (menu == 3 || menu == 4) {
            if (!client.canPay()) continue;
            if (menu == 3) readText("Название заказа: ");
            long long amount = readMoney("Сумма платежа: ");
            if (amount > account.getBalance()) {
                admin.blockForExcess(client);
                continue;
            }
            bool ok;
            if (menu == 3) ok = account.withdraw(amount);
            else {
                int receiver = 1 - current;
                ok = account.transfer(clients[receiver].getAccount(), amount);
            }
            if (ok) cout << "Платеж выполнен.\n";
            else cout << "Перевод отклонен: счет получателя закрыт или достигнут предел остатка.\n";
        }
    }
}
