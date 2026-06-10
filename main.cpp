#include <iostream>

#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "task4.h"
#include "task6.h"

using namespace std;

enum class Menu {
    EXIT = 0,
    FERMAT = 1,
    EX_EVCLID = 2,
    MOD_INVERSE = 3,
    HUGHES = 4,
    DIOPHANTINE = 6
};

int main() {

    int choice;

    do {
        cout << endl;
        cout << "1 - Теорема Ферма\n";
        cout << "2 - асширенный алгоритм Евклида)\n";
        cout << "3 - Вычисление c^(-1) mod m\n";
        cout << "4 - Алгоритм Хьюза\n";
        cout << "6 - Цепная дробь\n";
        cout << "0 - Выход\n";

        cout << "\nВыберите пункт: ";
        cin >> choice;

        switch (static_cast<Menu>(choice)) {

        case Menu::FERMAT:
            task1();
            break;

        case Menu::EX_EVCLID:
            task2();
            break;

        case Menu::MOD_INVERSE:
            task3();
            break;

        case Menu::HUGHES:
            task4();
            break;

        case Menu::DIOPHANTINE:
            task6();
            break;

        case Menu::EXIT:
            break;

        default:
            cout << "\nОшибка: неверный пункт меню.\n";
            break;
        }

    } while (choice != 0);

    return 0;
}