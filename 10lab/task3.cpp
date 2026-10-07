#include "../common/input.h"

// Стек помещает не больше трех целых чисел.
// top хранит индекс вершины; -1 означает пустой стек.
// Исключение не дает добавить четвертое число или удалить отсутствующее.
class Stack {
private:
    static const int max = 3;
    int st[max] = {};
    int top = -1;
public:
    class Rang {
        // Вложенный класс описывает ошибку именно этого стека.
    public:
        string message;
        explicit Rang(string text) : message(text) {}
    };
    void push(int value) {
        if (top == max - 1) throw Rang("стек полон");
        top++;
        st[top] = value;
    }
    int pop() {
        if (top == -1) throw Rang("стек пуст");
        int value = st[top];
        top--; // Вершина меняется только после успешной проверки.
        return value;
    }
    void show() const {
        cout << "Стек от вершины: ";
        if (top == -1) cout << "пусто";
        // Идем от вершины к первому добавленному элементу.
        for (int i = top; i >= 0; i--) cout << st[i] << ' ';
        cout << '\n';
    }
};

int main() {
    Stack stack;
    while (true) {
        cout << "\n1. Push\n2. Pop\n3. Показать стек\n0. Выход\n";
        int menu = readInt("Выбор: ", 0, 3);
        if (menu == 0) break;
        try {
            if (menu == 1) {
                int value = readInt("Целое число: ", -2147483647 - 1, 2147483647);
                stack.push(value);
                cout << "Элемент добавлен.\n";
            }
            if (menu == 2) {
                int value = stack.pop();
                cout << "Удален: " << value << '\n';
            }
            if (menu == 3) stack.show();
        } catch (const Stack::Rang& error) {
            // throw передает сюда причину ошибки; const& не копирует объект.
            cout << "Исключение Rang: " << error.message << ". Состояние стека сохранено.\n";
        }
    }
}
