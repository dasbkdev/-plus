#include "../common/input.h"
#include <cmath>
#include <iomanip>

// Общий класс Figure задает обязательный метод вычисления площади.
// Круг, квадрат и треугольник подставляют в него свою формулу.
// Одна функция showArea умеет вывести площадь любой из этих фигур.
const double pi = 3.14;

class Figure {
protected:
    double R;
public:
    Figure() : R(1) {}
    explicit Figure(double r) : R(r) {}
    virtual ~Figure() {} // При удалении через родителя вызывается нужный деструктор.
    virtual double area() const = 0; // Абстрактный класс задает общий интерфейс.
};

class Circle : public Figure {
public:
    Circle(double r = 1) : Figure(r) {}
    double area() const override {
        // override подтверждает, что мы меняем виртуальный метод родителя.
        return pi * R * R;
    }
};

class Square : public Figure {
public:
    Square(double r = 1) : Figure(r) {}
    double area() const override {
        return R * R;
    }
};

class Triangle : public Figure {
public:
    Triangle(double r = 1) : Figure(r) {}
    double area() const override {
        return sqrt(3.0) * R * R / 4;
    }
};

void showArea(const Figure& figure) {
    // const Figure& передает объект без копирования и запрещает менять его.
    double area = figure.area(); // Один виртуальный вызов для любой фигуры.
    if (area < 0.000001) cout << scientific;
    cout << "Площадь: " << area << '\n';
    cout << fixed;
}

int main() {
    cout << fixed << setprecision(6);
    while (true) {
        cout << "\n1. Круг\n2. Квадрат\n3. Равносторонний треугольник\n"
             << "4. Все фигуры с R = 1\n0. Выход\n";
        int menu = readInt("Выбор: ", 0, 4);
        if (menu == 0) break;
        if (menu == 4) {
            Circle circle;
            Square square;
            Triangle triangle;
            cout << "Круг. ";
            showArea(circle);
            cout << "Квадрат. ";
            showArea(square);
            cout << "Треугольник. ";
            showArea(triangle);
            continue;
        }
        string prompt = "Сторона: ";
        if (menu == 1) prompt = "Радиус: ";
        double r = readDouble(prompt, 0.000001, 1e9);
        if (menu == 1) {
            Circle figure(r);
            showArea(figure);
        }
        if (menu == 2) {
            Square figure(r);
            showArea(figure);
        }
        if (menu == 3) {
            Triangle figure(r);
            showArea(figure);
        }
    }
}
