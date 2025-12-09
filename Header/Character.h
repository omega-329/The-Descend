//
// Created by omega on 06.12.2025.
//

#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include "Limb.h"
#include "Weapons.h"
#include "Armor.h"
#include <string>
#include <vector>

class character
{
protected:
    std::string descriere=" ", nume=" ";
    int nrlimb=6;
    bool unlock=false, isalive=true;
    std::vector<limb>limbs;
    weapons currentweapon;
    armor currentarmor;
public:
    character ()=default;
    [[nodiscard]] bool getlock() const;
    void setlock();
    [[nodiscard]] std::string& getnume();
    [[nodiscard]] bool getalive() const;
    void setalive();
    [[nodiscard]] int getlimbcount() const;
    void updatelimbstatus(limb curentlimb);
    character(std::string& descriere, std::string& nume,const  int &nrlimb, const std::vector<limb>& limbs) :descriere(std::move(descriere)), nume(std::move(nume)), nrlimb(nrlimb), limbs(limbs) {};
    friend std::istream& operator>>(std::istream& in, character& p);
    friend std::ostream& operator<<(std::ostream& out,const character& p);
    weapons equipweapon(const weapons& noww);
    weapons& getcurrentweapon();
    armor equiparmor(const armor& nowa);
    ~character()=default;
    [[nodiscard]] limb getlimb(int i) const;
};
#endif //OOP_PLAYER_H