/*
==========PIVOGEDDON==========
File for exception handling
github.com/tsurinoruri
*/

#pragma once

#include <stdexcept> 
#include <exception> 

#include "WeaponClassTest.h"

// Базовый класс для исключений оружия
class WeaponException : public exception {
protected:
    string message;
public:
    WeaponException(const string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Исключение: нет патронов
class NoAmmoException : public WeaponException {
public:
    NoAmmoException(const string& weaponName)
        : WeaponException("Ошибка: У оружия \"" + weaponName + "\" нет патронов") {
    }
};

// Исключение: неправильный тип оружия
class WrongWeaponTypeException : public WeaponException {
public:
    WrongWeaponTypeException(const string& weaponName, const string& expectedType)
        : WeaponException("Ошибка: Оружие \"" + weaponName + "\" не является оружием " + expectedType + " боя!") {
    }
};

// Исключение: неверные параметры
class InvalidParameterException : public WeaponException {
public:
    InvalidParameterException(const string& paramName, const string& reason)
        : WeaponException("Ошибка: Неверный параметр " + paramName + " - " + reason) {
    }
};