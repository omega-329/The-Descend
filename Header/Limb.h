//
// Created by omega on 06.12.2025.
//

#ifndef OOP_LIMB_H
#define OOP_LIMB_H

class limb
{
protected:
    float hp=20, dmg=0;
    bool isintact=true;
public:
    limb()=default;
    [[nodiscard]] bool getintact() const;
    void setintact();
    [[nodiscard]] float gethp() const;
    void sethp(float new_hp);
    [[nodiscard]] float getdmg() const;
    limb(float hp, float dmg);
    ~limb()=default;
};

#endif //OOP_LIMB_H