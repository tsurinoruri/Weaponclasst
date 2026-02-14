/*
==========PIVOGEDDON==========
File for Melee Weapon Class
github.com/tsurinoruri
*/

#pragma once

#include "WeaponClassTest.h"
#include "WeaponException.h"

class MeleeWeapon : public Weapon {
public:
    MeleeWeapon(
        const string& name,
        int damage,
        float attackSpeed,
        float attackRange,
        float weaponWeight,
        const string& iconPath = ".png"
    ) : Weapon(name, damage, attackSpeed, attackRange, weaponWeight, iconPath) {

        try {
            if (damage <= 0) {
                throw InvalidParameterException("damage", "должен быть положительным");
            }
            if (attackSpeed <= 0.0f) {
                throw InvalidParameterException("attackSpeed", "должна быть положительной");
            }
            if (attackRange <= 0.0f || attackRange > 10.0f) {
                throw InvalidParameterException("attackRange", "должна быть в диапазоне 0-10");
            }
            if (weaponWeight <= 0.0f) {
                throw InvalidParameterException("weaponWeight", "должен быть положительным");
            }
        }
        catch (const InvalidParameterException& e) {
            cerr << "Ошибка создания оружия ближнего боя: " << e.what() << endl;
            throw;
        }
    }

    string getWeaponSound() const override {
        try {
            if (WeaponName.find("меч") != string::npos ||
                WeaponName.find("Меч") != string::npos) {
                return "Звук меча";
            }
            return "звук";
        }
        catch (const InvalidParameterException& e) {
            return "звук отсутствует";
        }
    }

    void displayInfo() const override {
        try {
            Weapon::displayInfo();

            cout << "Тип оружия: Ближний бой" << endl;
            cout << "Дальность удара: " << AttackRange << " м" << endl;
        }
        catch (const exception& e) {
            cerr << "Ошибка при отображении информации: " << e.what() << endl;
        }
    }

    void reload() override {
        try {
            cout << WeaponName << " не требует перезарядки!" << endl;
        }
        catch (const exception& e) {
            cerr << "Ошибка: " << e.what() << endl;
        }
    }

#ifdef __DEBUGWEAPONCLASS__

    void normalAttack() {
        try {
            if (WeaponType != ::WeaponType::Melee) {
                throw WrongWeaponTypeException(WeaponName, "ближнего");
            }

            cout << WeaponName << " наносит удар" << endl;
            //getWeaponSound() проигрывание звука
            cout << "Урон: " << WeaponDamage << endl;

        }
        catch (const exception& e) {
            cerr << "Неизвестная ошибка: " << e.what() << endl;
        }
    }

    int calculateDamage() const override {
        int MeleeDamage = WeaponDamage;
        return MeleeDamage;
    }

#endif
};