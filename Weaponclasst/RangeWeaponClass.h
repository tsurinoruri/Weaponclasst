/*
==========PIVOGEDDON==========
File for Range Weapon Class
github.com/tsurinoruri
*/

#pragma once

#include "WeaponClassTest.h"
#include "WeaponException.h"

class RangedWeapon : public Weapon {
public:
    RangedWeapon(
        const string& name,
        int damage,
        int maxPatrons,
        int curentPatrons,
        float attackSpeed,
        float attackRange,
        float rechargeTime,
        float weaponWeight,
        const string& ammoType,
        const string& iconPath = ".png"
    ) : Weapon(name, damage, maxPatrons, curentPatrons, attackSpeed, attackRange,
        rechargeTime, weaponWeight, ammoType, iconPath) {
        // Проверка корректности параметров
        try {
            if (damage <= 0) {
                throw InvalidParameterException("damage", "должен быть положительным");
            }
            if (maxPatrons < 0) {
                throw InvalidParameterException("maxPatrons", "не может быть отрицательным");
            }
            if (curentPatrons < 0 || curentPatrons > maxPatrons) {
                throw InvalidParameterException("curentPatrons",
                    "должен быть в диапазоне 0-" + to_string(maxPatrons));
            }
            if (attackSpeed <= 0.0f) {
                throw InvalidParameterException("attackSpeed", "должна быть положительной");
            }
            if (attackRange <= 0.0f) {
                throw InvalidParameterException("attackRange", "должна быть положительной");
            }
            if (weaponWeight <= 0.0f) {
                throw InvalidParameterException("weaponWeight", "должен быть положительным");
            }
        }
        catch (const InvalidParameterException& e) {
            cerr << "Ошибка создания оружия: " << e.what() << endl;
            throw;
        }
    }

    string getWeaponSound() const override {
        try {
            if (WeaponName.empty()) {
                throw WeaponException("Ошибка: Имя оружия не может быть пустым");
            }
            if (WeaponName.find("пистолет") != string::npos ||
                WeaponName.find("Пистолет") != string::npos) {
                return "звук пистолета";
            }
            else if (WeaponName.find("дробовик") != string::npos ||
                WeaponName.find("Дробовик") != string::npos) {
                return "звук дробовика";
            }
            else if (WeaponName.find("автомат") != string::npos ||
                WeaponName.find("Автомат") != string::npos) {
                return "звук автомата";
            }

            return "звук";
        }
        catch (const exception& e) {
            cerr << "Ошибка в getWeaponSound: " << e.what() << endl;
            return "Звук оружия недоступен";
        }
    }

    void displayInfo() const override {
        try {
            Weapon::displayInfo();

            cout << "Тип оружия: Дальний бой" << endl;
            cout << "Патроны: " << CurentPatrons << "/" << maxpatrons << endl;
            cout << "Время перезарядки: " << RechargeTime << " сек" << endl;
        }
        catch (const exception& e) {
            cerr << "Ошибка при отображении информации: " << e.what() << endl;
        }
    }

    void reload() override {
        try {
            if (WeaponType != ::WeaponType::Ranged) {
                throw WrongWeaponTypeException(WeaponName, "дальнего");
            }

            if (maxpatrons == 0) {
                throw InvalidParameterException("maxpatrons", "не может быть 0 для оружия дальнего боя");
            }

            if (CurentPatrons == maxpatrons) {
                cout << WeaponName << " уже полностью заряжено" << endl;
                return;
            }

            cout << "Перезаряжаем " << WeaponName << "... ";
            cout << "Время перезарядки: " << RechargeTime << " сек" << endl;

            Weapon::reload();
        }
        catch (const WrongWeaponTypeException& e) {
            cerr << e.what() << endl;
        }
        catch (const InvalidParameterException& e) {
            cerr << e.what() << endl;
        }
        catch (const exception& e) {
            cerr << "Неизвестная ошибка при перезарядке: " << e.what() << endl;
        }
    }

    // Метод для одиночного выстрела
    void singleShot() {
        try {
            // Проверка типа оружия
            if (WeaponType != ::WeaponType::Ranged) {
                throw WrongWeaponTypeException(WeaponName, "дальнего");
            }
            // Проверка патронов
            if (CurentPatrons <= 0) {
                throw NoAmmoException(WeaponName);
            }

            CurentPatrons--;

#ifdef __DEBUGWEAPONCLASS__

            cout << WeaponName << " произвел одиночный выстрел. ";
            cout << "Осталось патронов: " << CurentPatrons << "/" << maxpatrons << endl;
#endif
            //getWeaponSound() проигрывание звука
        }
        catch (const NoAmmoException& e) {
            cerr << e.what() << " Перезарядитесь!" << endl;
        }
        catch (const WrongWeaponTypeException& e) {
            cerr << e.what() << endl;
        }
        catch (const exception& e) {
            cerr << "Неизвестная ошибка при выстреле: " << e.what() << endl;
        }
    }

    // Метод для непрерывной стрельбы 
    void burstFire(int shotsCount) {
        try {
            if (shotsCount <= 0) {
                throw InvalidParameterException("shotsCount", "должен быть положительным");
            }

            if (shotsCount > maxpatrons) {
                throw InvalidParameterException("shotsCount", "не может превышать 10");
            }
#ifdef __DEBUGWEAPONCLASS__

            cout << "Произошло " << shotsCount << " выстрелов:" << endl;

#endif
            for (int i = 0; i < shotsCount; i++) {
                try {
                    singleShot(); // Используем уже существующий метод с исключениями
                }
                catch (const NoAmmoException& e) {
                    cerr << "Очередь прервана: " << e.what() << endl;
                    break;
                }
            }
        }
        catch (const InvalidParameterException& e) {
            cerr << e.what() << endl;
        }
    }
#ifdef __DEBUGWEAPONCLASS__

    // Метод для проверки возможности выстрела
    bool canShoot() const {
        try {
            if (WeaponType != ::WeaponType::Ranged) {
                return false;
            }
            if (CurentPatrons <= 0) {
                return false;
            }
            return true;
        }
        catch (...) {
            return false;
        }
    }

    int calculateDamage() const override {
        int RangeDamage = WeaponDamage;
        float rangefactor = 0;
        if (AttackRange > 50) {
            rangefactor = 20;
        }
        int finaldamage = RangeDamage - rangefactor;
        return finaldamage;
    }

#endif
};
