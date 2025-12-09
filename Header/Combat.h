
#ifndef OOP_COMBAT_H
#define OOP_COMBAT_H
#include "Character.h"
#include "enemies.h"
class combat
{
protected:
    bool whoturn=true;
    character people[4];
    enemies opponent;
public:
    combat()=default;
    [[nodiscard]] bool getturn() const;
    void setturn(bool& cturn);
    void oneset();
};
#endif //OOP_COMBAT_H