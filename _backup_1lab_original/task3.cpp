#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Worker {
    string surname;
    int age;
    string specialty;
    double salary;
};


struct Factory {    
    string name;
    vector<Worker> workers;
};

int main() {
    int numFactories;
    cout << "Введите количество заводов N: ";
    cin >> numFactories;

    // Создаем вектор из N заводов
    vector<Factory> factories(numFactories);

    // Внешний цикл: проходим по каждому заводу из N
    for (int i = 0; i < numFactories; i++) {
        cout << "\n--- Завод #" << i + 1 << " ---" << endl;
        cout << "Название завода: ";
        cin >> factories[i].name;

        int numWorkers;
        cout << "Введите количество работников на заводе: ";
        cin >> numWorkers;

        // Внутренний цикл: заполняем данные каждого работника текущего завода
        for (int j = 0; j < numWorkers; j++) {
            Worker w; // Временный объект работника
            cout << "\nРаботник #" << j + 1 << ":" << endl;
            cout << "  Фамилия: ";
            cin >> w.surname;
            cout << "  Возраст: ";
            cin >> w.age;
            cout << "  Специальность (например: слесарь, токарь, инженер): ";
            cin >> w.specialty;
            cout << "  Средний оклад: ";
            cin >> w.salary;

            // Добавляем заполненного работника в вектор работников текущего завода
            factories[i].workers.push_back(w);
        }
    }

    int locksmithCount = 0; // Счетчик слесарей
    int turnerCount = 0;    // Счетчик токарей

    // Внешний цикл: обходим все заводы
    for (int i = 0; i < numFactories; i++) {
        // Внутренний цикл (range-based for): обходим каждого работника текущего завода
        for (const auto& worker : factories[i].workers) {
            // Проверяем специальность работника (с учетом регистра первой буквы)
            if (worker.specialty == "слесарь" || worker.specialty == "Слесарь") {
                locksmithCount++; // Инкрементируем счетчик слесарей
            } else if (worker.specialty == "токарь" || worker.specialty == "Токарь") {
                turnerCount++; // Инкрементируем счетчик токарей
            }
        }
    }

    // Вывод итоговых подсчетов
    cout << "\n================ РЕЗУЛЬТАТЫ ================" << endl;
    cout << "Всего слесарей по всем заводам: " << locksmithCount << endl;
    cout << "Всего токарей по всем заводам: " << turnerCount << endl;

    return 0;
}