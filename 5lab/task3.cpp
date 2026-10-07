#include "../common/input.h"

class Figure {
public:
    // Два аргумента означают длину и ширину прямоугольника.
    double rect_area(double width, double height) const {
        return width * height;
    }
    double rect_area(double side) const {
        return side * side; // Для квадрата достаточно одного размера.
    }
};

int main() {
    Figure figure;
    // После расчёта можно выбрать следующую фигуру.
    while (true) {
            cout << "\n1 Прямоугольник  2 Квадрат  0 Выход\n";
            int choice = readInt("Команда: ", 0, 2);
            if (choice == 0) break;
            // Этот диапазон сторон исключает переполнение при умножении.
            double a = readDouble("Сторона a (0.000001..1000000): ", 0.000001, 1000000);
            double area;
            if (choice == 1) {
                double b = readDouble("Сторона b (0.000001..1000000): ", 0.000001, 1000000);
                area = figure.rect_area(a, b);
            } else {
                area = figure.rect_area(a);
            }
            cout << setprecision(15) << "Площадь: " << area << '\n';
    }
    return 0;
}
