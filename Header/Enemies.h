//
// Created by omega on 06.12.2025.
//

#ifndef OOP_ENEMIES_H
#define OOP_ENEMIES_H

#include "Limb.h"
#include <string>
#include <vector>
class enemies
{
protected:
    std::string descriere=" ", nume=" ";
    bool unlock=false, isalive=true;
    int nrlimb=6;
    std::vector<limb>limbs;
public:
    enemies()=default;
    [[nodiscard]] bool getlock() const;
    void setlock();
    [[nodiscard]] std::string getnume() const;
    [[nodiscard]] bool getalive() const;
    void setalive();
    [[nodiscard]] int getlimbcount() const;
    void updatelimbstatus(limb curentlimb);
    enemies(std::string& descriere,std::string& nume, const int &nrlimb, const std::vector<limb>& limbs) :descriere(std::move(descriere)), nume(std::move(nume)), nrlimb(nrlimb), limbs(limbs) {};
    friend std::istream& operator>>(std::istream& in, enemies& e);
    friend std::ostream& operator<<(std::ostream& out,const enemies& e);
    [[nodiscard]] limb getlimb(int i) const;
    ~enemies()=default;
};

#endif //OOP_ENEMIES_H