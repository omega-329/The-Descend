
#ifndef OOP_ARMOR_H
#define OOP_ARMOR_H

#include "Item.h"
class armor : public Item
{
protected:
    bool ininv=false, isequiped=false;
    float dmgred=0;
public:
    armor() = default;
    armor(float dmgred,const std::string& nume,const std::string& descriere);
    [[nodiscard]] bool getarmor () const;
    void setarmor();
    [[nodiscard]] bool getequiped() const;
    void setequiped();
    float interact () override;
};

#endif //OOP_ARMOR_H