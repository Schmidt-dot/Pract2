#include<iostream>
#include<cstdint>

#include "tFerma.h"
#include "exEvclid.h"
#include "modInverse.h"
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

        case Menu::FERMAT: {

            int64_t a, x, p;

            cout << "Введите a: ";
            cin >> a;

            cout << "Введите x: ";
            cin >> x;

            cout << "Введите p: ";
            cin >> p;

            cout << endl;

            uint64_t result = tFerma(a, x, p);

            cout << "Ответ: " << result << endl;

            break;
        }

        case Menu::EX_EVCLID: {

            int64_t a, b;
            int64_t u, v;

            cout << "Расширенный алгоритм Евклида" << endl;

            cout << "Введите a: ";
            cin >> a;

            cout << "Введите b: ";
            cin >> b;

            exEvclid(a, b, u, v);

            break;
        }

        case Menu::MOD_INVERSE: {

            int64_t c, m;

            cout << "Вычисление c^(-1) mod m" << endl;

            cout << "Введите c: ";
            cin >> c;

            cout << "Введите m: ";
            cin >> m;

            if (m == 0) {
                cout << "Ошибка: m не может быть равно 0." << endl;
                break;
            }

            cout << endl;

            int64_t d = modInverse(c, m);

            if (d == -1) {
                break;
            }

            cout << "\nПроверка:" << endl;
            cout << c << " * " << d
                 << " mod " << m
                 << " = " << (c * d) % m << endl;

            break;
        }

        case Menu::HUGHES:

            inputEncryption();
            break;

        case Menu::FRACTION:

            inputFraction();
            break;

        case Menu::EXIT:

            break;

        default:

            cout << "\nОшибка: неверный пункт меню." << endl;
            break;
        }

    } while (choice != 0);

    return 0;
}