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

    vector<Factory> factories(numFactories);

    for (int i = 0; i < numFactories; i++) {
        cout << "\n--- Завод #" << i + 1 << " ---" << endl;
        cout << "Название завода: ";
        cin >> factories[i].name;

        int numWorkers;
        cout << "Введите количество работников на заводе: ";
        cin >> numWorkers;

        for (int j = 0; j < numWorkers; j++) {
            Worker w;
            cout << "\nРаботник #" << j + 1 << ":" << endl;
            cout << "  Фамилия: ";
            cin >> w.surname;
            cout << "  Возраст: ";
            cin >> w.age;
            cout << "  Специальность (например: слесарь, токарь, инженер): ";
            cin >> w.specialty;
            cout << "  Средний оклад: ";
            cin >> w.salary;

            factories[i].workers.push_back(w);
        }
    }

    int locksmithCount = 0; // слесари
    int turnerCount = 0;    // токари

    for (int i = 0; i < numFactories; i++) {
        for (const auto& worker : factories[i].workers) {
            if (worker.specialty == "слесарь" || worker.specialty == "Слесарь") {
                locksmithCount++;
            } else if (worker.specialty == "токарь" || worker.specialty == "Токарь") {
                turnerCount++;
            }
        }
    }

    cout << "\n================ РЕЗУЛЬТАТЫ ================" << endl;
    cout << "Всего слесарей по всем заводам: " << locksmithCount << endl;
    cout << "Всего токарей по всем заводам: " << turnerCount << endl;

    return 0;
}