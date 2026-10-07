#include "../common/input.h"

// Компьютер объединяет сведения о мониторе и материнской плате.
// Это пример наследования сразу от двух классов.
// Каждый пункт меню показывает отдельную часть данных.
class Display {
private:
    string type;
    long colors;
    int x_resolution, y_resolution;
public:
    Display(string t, long c, int x, int y)
        // Конструктор сразу заполняет закрытые поля монитора.
        : type(t), colors(c), x_resolution(x), y_resolution(y) {}
    ~Display() {}
    void showDisplay() const {
        cout << "Монитор: " << type << ", цветов: " << colors
             << ", разрешение: " << x_resolution << 'x' << y_resolution << '\n';
    }
};

class MotherBoard {
private:
    int processor, speed, RAM;
public:
    MotherBoard(int p, int s, int r) : processor(p), speed(s), RAM(r) {}
    ~MotherBoard() {}
    void showBoard() const {
        cout << "Код процессора: " << processor << ", частота (МГц): " << speed
             << ", ОЗУ (ГБ): " << RAM << '\n';
    }
};

// У компьютера два родителя с разными механизмами доступа.
class Computer : public Display, protected MotherBoard {
private:
    string name;
    int hard_disk;
public:
    Computer(string t, long c, int x, int y, int p, int s, int r, string n, int disk)
        // Сначала создаются оба родителя, затем поля самого компьютера.
        : Display(t, c, x, y), MotherBoard(p, s, r), name(n), hard_disk(disk) {}
    ~Computer() {}
    void showOwn() const {
        cout << "Марка: " << name << ", диск (ГБ): " << hard_disk << '\n';
    }
    void showMotherBoard() const {
        MotherBoard::showBoard(); // Открытый метод-обертка восстанавливает доступ.
    }
    void Show() const {
        // Полная информация состоит из трех частей.
        showOwn();
        showDisplay();
        showMotherBoard();
    }
};

int main() {
    Computer computer("IPS", 16777216, 1920, 1080, 5, 3200, 16, "Учебный ПК", 512);
    while (true) {
        cout << "\n1. Ввести компьютер\n2. Поля самого компьютера\n3. Все данные\n"
             << "4. Монитор\n5. Плата через открытый метод\n6. Проверить отдельных родителей\n0. Выход\n";
        int menu = readInt("Выбор: ", 0, 6);
        if (menu == 0) break;
        if (menu == 1) {
            string type = readText("Тип монитора: ", 31);
            int colors = readInt("Цветов: ", 2, 1073741824);
            int x = readInt("Разрешение X: ", 1, 32768);
            int y = readInt("Разрешение Y: ", 1, 32768);
            int processor = readInt("Код процессора: ", 1, 1000000);
            int speed = readInt("Частота (МГц): ", 1, 100000);
            int ram = readInt("ОЗУ (ГБ): ", 1, 1048576);
            string name = readText("Марка: ", 63);
            int disk = readInt("Объем диска (ГБ): ", 1, 1000000000);
            computer = Computer(type, colors, x, y, processor, speed, ram, name, disk);
        }
        if (menu == 2) computer.showOwn();
        if (menu == 3) computer.Show();
        if (menu == 4) computer.showDisplay();
        if (menu == 5) computer.showMotherBoard();
        if (menu == 6) {
            // Родительские классы можно использовать и без компьютера.
            Display display("IPS", 16777216, 1920, 1080);
            MotherBoard board(5, 3200, 16);
            display.showDisplay();
            board.showBoard();
        }
    }
}
