
#ifndef OOP_LIMB_H
#define OOP_LIMB_H
#include <string>

class Limb
{
protected:
    float HP=20, DMG=0;
    bool isIntact=true;
    std::string name;
public:
    Limb(std::string name, float hp, float dmg);
    [[nodiscard]] bool getIntact() const;
    void setIntact();
    [[nodiscard]] float getHP() const;
    void setHP(float new_hp);
    [[nodiscard]] float getDMG() const;
    std::string getName() const;
    ~Limb()=default;
};

#endif //OOP_LIMB_H