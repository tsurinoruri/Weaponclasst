/*
==========PIVOGEDDON==========
Main file for debuging WeaponClassTest
github.com/tsurinoruri
*/

#include "WeaponClassTest.h"
#include "RangeWeaponClass.h"
#include "MeleeWeaponClass.h"
#include "WeaponException.h"

int main()
{
    setlocale(LC_ALL, "RUS");

    /*
    Порядок для конструктора дальнего боя: 1)Название оружия 2)Урон 3)Макс. патронов 4)текущие патроны
    5)Скорость атаки 6)Радиус атаки 7)Время перезарядки(в секундах) 8)Вес оружия
    9)Тип заряжаемыъ патронов 10)Путь к иконке
    Порядок для конструктора ближнего боя: 1)Название оружия 2)Урон 3)Скорость атаки
    4)Радиус атаки  5)Вес оружия 6)Путь к иконке
    */

#ifdef __DEBUGWEAPONCLASS__

    try {
        cout << "TEST\n" << endl;
        try {
            RangedWeapon avtomat(
                "Автомат", 35, 30, 30, 10.0f, 300.0f, 2.5f, 4.5f, "7.62mm"
            );

            MeleeWeapon sword(
                "Меч", 50, 1.5f, 3.0f, 8.0f
            );

            cout << "\n--- ТЕСТ ДАЛЬНЕГО БОЯ ---" << endl;
            for (int i = 0; i < 15; i++) {
                avtomat.singleShot();
            }
            avtomat.burstFire(5);


            cout << "\n--- ТЕСТ БЛИЖНЕГО БОЯ ---" << endl;
            for (int i = 0; i < 8; i++) {
                sword.normalAttack();
            }
            avtomat.displayInfo();
            sword.displayInfo();
            cout << endl << endl;
            cout << avtomat.calculateDamage() << endl;
            cout << sword.calculateDamage();
        }
        catch (const InvalidParameterException& e) {
            cout << "Ошибка создания оружия: " << e.what() << endl;
            return 1;
        }
        catch (const WeaponException& e) {
            cout << "Ошибка оружия: " << e.what() << endl;
        }
        catch (const exception& e) {
            cout << "Неизвестная ошибка: " << e.what() << endl;
        }

    }
    catch (...) {
        cout << "Ошибка программы" << endl;
        return 1;
    }

#else
    cout << "no debugging" << endl;
#endif

    system("pause > null");
    return 0;
}