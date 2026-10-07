#include "../common/input.h"
#include <cmath>

// Один метод считает площадь прямоугольника, другой — квадрата.
// Одинаковое имя с разными аргументами называется перегрузкой.
// Неправильные стороны обрабатываются через исключение.
class Rectangle {
public:
    class SizeError {};
    double rect_area(double a, double b) const {
        if (!isfinite(a) || !isfinite(b)) throw SizeError();
        if (a <= 0 || b <= 0) throw SizeError();
        double area = a * b;
        // Слишком большое или слишком малое произведение нельзя выдавать за площадь.
        if (!isfinite(area) || area <= 0) throw SizeError();
        return area;
    }
    double rect_area(double side) const {
        return rect_area(side, side); // Перегрузка для квадрата использует общую проверку.
    }
};

int main() {
    Rectangle figure;
    while (true) {
        cout << "\n1. Площадь прямоугольника\n2. Площадь квадрата\n0. Выход\n";
        int menu = readInt("Выбор: ", 0, 2);
        if (menu == 0) break;
        double a = readDouble("Первая сторона (должна быть положительной): ", -1e9, 1e9);
        try {
            // Вызывается перегрузка с одним или с двумя размерами.
            double result;
            if (menu == 1) {
                double b = readDouble("Вторая сторона: ", -1e9, 1e9);
                result = figure.rect_area(a, b);
            } else result = figure.rect_area(a);
            cout << "Площадь: " << result << '\n';
        } catch (const Rectangle::SizeError&) {
            // После catch цикл снова покажет меню.
            cout << "Исключение SizeError: стороны и площадь должны быть положительными и конечными.\n";
        }
    }
}
