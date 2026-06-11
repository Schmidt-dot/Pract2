#include <iostream>

#include "inputTFerma.h"
#include "inputExEvclid.h"
#include "inputInverse.h"
#include "inputEncryption.h"
#include "inputFraction.h"

using namespace std;

enum class Menu {
    EXIT = 0,
    FERMAT = 1,
    EX_EVCLID = 2,
    MOD_INVERSE = 3,
    HUGHES = 4,
    FRACTION = 6
};

int main() {

    int choice;

    do {
        cout << endl;
        cout << "1 - Теорема Ферма\n";
        cout << "2 - Расширенный алгоритм Евклида\n";
        cout << "3 - Вычисление c^(-1) mod m\n";
        cout << "4 - Алгоритм Хьюза\n";
        cout << "6 - Цепная дробь\n";
        cout << "0 - Выход\n";

        cout << "\nВыберите пункт: ";
        cin >> choice;

        switch (static_cast<Menu>(choice)) {

        case Menu::FERMAT:
            inputTFerma();
            break;

        case Menu::EX_EVCLID:
            inputExEvclid();
            break;

        case Menu::MOD_INVERSE:
            inputInverse();
            break;

        case Menu::HUGHES:
            inputEncryption();
            break;

        case Menu::FRACTION:
            inputFraction();
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