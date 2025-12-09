//
// Created by omega on 06.12.2025.
//

#ifndef OOP_ARMOR_H
#define OOP_ARMOR_H

#include "Items.h"
class armor : public Items
{
protected:
    bool ininv=false, isequiped=false;
    float dmgred=0;
public:
    armor()=default;
    explicit armor(float dmgred);
    [[nodiscard]] bool getarmor () const;
    void setarmor();
    [[nodiscard]] bool getequiped() const;
    void setequiped();
    float interact () override;
};

#endif //OOP_ARMOR_H