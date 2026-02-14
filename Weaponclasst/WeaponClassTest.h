/*
==========PIVOGEDDON==========
Weapon Class Test
Header for main test programm
github.com/tsurinoruri
Start working 14.02.2026
*/

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <random>
#define __DEBUGWEAPONCLASS__
using namespace std;

int setrandvalue() {
    srand(time(NULL));
    unsigned int rand_num = 1 + rand() % 100;
    return rand_num;
}

//enum class RarityType { Common, Rare, Epic, Legendary };
enum class WeaponType { Melee, Ranged };

class Weapon {
protected:
    //weapon characteristics
    int WeaponDamage;
    int maxpatrons;
    int CurentPatrons;
    float AttackSpeed;
    float AttackRange;
    float RechargeTime;
    float WeaponWeight;
    string AmmunitionType;
    string WeaponName;
    string iconpath;
    //RarityType rarity;
    WeaponType WeaponType;
public:
    // Конструктор для оружия дальнего боя
    Weapon(
        const string& name,                            // Название оружия
        int damage,                                  // Урон
        int maxPatrons,               // Максимальное количество патронов
        int curentPatrons,              // Текущее количество патронов
        float attackSpeed,                           // Скорость атаки
        float attackRange,                             // Дальность атаки
        float rechargeTime,                            // Время перезарядки
        float weaponWeight,                           // Вес оружия
        const string& ammoType,                       // Тип боеприпасов
        const string& iconPath = ".png"             // Путь к иконке оружия
        //RarityType rarityType = RarityType::Common // Редкость 
    ) : WeaponDamage(damage),
        maxpatrons(maxPatrons),
        CurentPatrons(curentPatrons),
        AttackSpeed(attackSpeed),
        AttackRange(attackRange),
        RechargeTime(rechargeTime),
        WeaponWeight(weaponWeight),
        AmmunitionType(ammoType),
        WeaponName(name),
        iconpath(iconPath),
        // rarity(rarityType),
        WeaponType(::WeaponType::Ranged) // Фиксированный тип для дальнего боя
    {
        // Валидация параметров
        if (WeaponDamage < 0) WeaponDamage = 0;
        if (maxpatrons < 0) maxpatrons = 0;
        if (AttackSpeed <= 0.0f) AttackSpeed = 1.0f;
        if (AttackRange < 0.0f) AttackRange = 100.0f;
        if (RechargeTime < 0.0f) RechargeTime = 1.0f;
        if (WeaponWeight < 0.0f) WeaponWeight = 1.0f;
    }

    // Конструктор для оружия ближнего боя
    Weapon(
        const string& name,           // Название оружия
        int damage,                    // Урон
        float attackSpeed,              // Скорость атаки
        float attackRange,              // Дальность атаки
        float weaponWeight,              // Вес оружия
        const string& iconPath = ".png"  // Путь к иконке 
        //RarityType rarityType = RarityType::Common // Редкость
    ) : WeaponDamage(damage),
        maxpatrons(0),               // отсутвие патронов так как ближний бой
        AttackSpeed(attackSpeed),
        AttackRange(attackRange),
        RechargeTime(0.0f),            // Фиксированное значение - нет перезарядки
        WeaponWeight(weaponWeight),
        AmmunitionType("none"),         // Фиксированное значение - нет боеприпасов
        WeaponName(name),
        iconpath(iconPath),
        // rarity(rarityType),
        WeaponType(::WeaponType::Melee)  // Фиксированный тип - ближний бой
    {
        // Валидация 
        if (WeaponDamage < 0) WeaponDamage = 0;
        if (AttackSpeed <= 0.0f) AttackSpeed = 1.0f;
        if (AttackRange < 0.0f) AttackRange = 2.0f;  // Маленькая дальность для ближнего боя
        if (AttackRange > 10.0f) AttackRange = 10.0f; // Ограничиваем дальность
        if (WeaponWeight < 0.0f) WeaponWeight = 1.0f;
    }

    // Конструктор по умолчанию 
    Weapon()
        :WeaponDamage(10),
        maxpatrons(0),
        CurentPatrons(0),
        AttackSpeed(1.0f),
        AttackRange(2.0f),
        RechargeTime(0.0f),
        WeaponWeight(1.0f),
        AmmunitionType("none"),
        WeaponName("Default Weapon"),
        iconpath("default_icon.png"),
        //rarity(RarityType::Common),
        WeaponType(WeaponType::Melee) {
    }

    // Конструктор копирования
    Weapon(const Weapon& copyweapon)
        :WeaponDamage(copyweapon.WeaponDamage),
        maxpatrons(copyweapon.maxpatrons),
        CurentPatrons(copyweapon.CurentPatrons),
        AttackSpeed(copyweapon.AttackSpeed),
        AttackRange(copyweapon.AttackRange),
        RechargeTime(copyweapon.RechargeTime),
        WeaponWeight(copyweapon.WeaponWeight),
        AmmunitionType(copyweapon.AmmunitionType),
        WeaponName(copyweapon.WeaponName),
        iconpath(copyweapon.iconpath),
        //rarity(copyweapon.rarity),
        WeaponType(copyweapon.WeaponType) {
    }

    // Геттеры для доступа к данным
    string getName() const { return WeaponName; }
    int getDamage() const { return WeaponDamage; }
    int getMaxPatrons() const { return maxpatrons; }
    int getCurentPatrons() const { return CurentPatrons; }
    float getAttackSpeed() const { return AttackSpeed; }
    float getAttackRange() const { return AttackRange; }
    float getRechargeTime() const { return RechargeTime; }
    float getWeight() const { return WeaponWeight; }
    string getAmmoType() const { return AmmunitionType; }
    //RarityType getRarity() const { return rarity; }
    ::WeaponType getWeaponType() const { return WeaponType; }

    // Вывод информации об оружии
    string getInfo() const {
        string info = "=== " + WeaponName + " ===\n";
        info += "Тип: " + string(WeaponType == WeaponType::Melee ? "Ближний бой" : "Дальний бой") + "\n";
        info += "Урон: " + to_string(WeaponDamage) + "\n";
        info += "Скорость атаки: " + to_string(AttackSpeed) + "\n";
        info += "Дальность: " + to_string(AttackRange) + "\n";
        info += "Вес: " + to_string(WeaponWeight) + " кг\n";

        if (WeaponType == WeaponType::Ranged) {
            info += "Патроны: " + to_string(maxpatrons) + "\n";
            info += "Текущее количесиво патронов: " + to_string(CurentPatrons) + "\n";
            info += "Время перезарядки: " + to_string(RechargeTime) + " сек\n";
            info += "Тип боеприпасов: " + AmmunitionType + "\n";
        }
        else {
            info += "(Боеприпасы не требуются)\n";
        }

        /* switch (rarity) {
         case RarityType::Common: info += "Редкость: Обычное\n"; break;
         case RarityType::Rare: info += "Редкость: Редкое\n"; break;
         case RarityType::Epic: info += "Редкость: Эпическое\n"; break;
         case RarityType::Legendary: info += "Редкость: Легендарное\n"; break;
         }*/

        return info;
    }

    //добавление патронов
    void addAmmo(int amount) {
        if (WeaponType == ::WeaponType::Ranged) {
            CurentPatrons = min(CurentPatrons + amount, maxpatrons);
            cout << "Добавлено " << amount << " патронов. Текущие: " << CurentPatrons << "/" << maxpatrons << endl;
        }
    }

    //виртуальные методы
    virtual void displayInfo() const {
        string information = getInfo();
        cout << information;
    }

    //проигрывание звукрв оружия(в дальнейшем добавит путь к звуку)
    virtual string getWeaponSound() const = 0;

    virtual void reload() {
        if (WeaponType == ::WeaponType::Ranged) {
            if (CurentPatrons == maxpatrons) {
                cout << WeaponName << " заряжен" << endl;
            }
            CurentPatrons = maxpatrons;
            cout << WeaponName << " перезаряжено. Патронов: " << CurentPatrons << "/" << maxpatrons << endl;
        }
        else {
            cout << WeaponName << " не требует перезарядки" << endl;
        }
    }

    virtual int calculateDamage() const {
        return WeaponDamage;
    }

    virtual ~Weapon() noexcept = default;
};
