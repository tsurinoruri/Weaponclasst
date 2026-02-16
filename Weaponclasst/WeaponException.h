/*
==========PIVOGEDDON==========
File for exception handling
github.com/tsurinoruri
*/

#pragma once

#include <stdexcept> 
#include <exception> 

#include "WeaponClassTest.h"
setlocale(KC_ALL,"RUS");
// Áàçîâûé êëàññ äëÿ èñêëþ÷åíèé îðóæèÿ
class WeaponException : public exception {
protected:
    string message;
public:
    WeaponException(const string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Èñêëþ÷åíèå: íåò ïàòðîíîâ
class NoAmmoException : public WeaponException {
public:
    NoAmmoException(const string& weaponName)
        : WeaponException("Îøèáêà: Ó îðóæèÿ \"" + weaponName + "\" íåò ïàòðîíîâ") {
    }
};

// Èñêëþ÷åíèå: íåïðàâèëüíûé òèï îðóæèÿ
class WrongWeaponTypeException : public WeaponException {
public:
    WrongWeaponTypeException(const string& weaponName, const string& expectedType)
        : WeaponException("Îøèáêà: Îðóæèå \"" + weaponName + "\" íå ÿâëÿåòñÿ îðóæèåì " + expectedType + " áîÿ!") {
    }
};

// Èñêëþ÷åíèå: íåâåðíûå ïàðàìåòðû
class InvalidParameterException : public WeaponException {
public:
    InvalidParameterException(const string& paramName, const string& reason)
        : WeaponException("Îøèáêà: Íåâåðíûé ïàðàìåòð " + paramName + " - " + reason) {
    }
};
