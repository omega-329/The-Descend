
#include "../Header/Item.h"
[[nodiscard]] bool Item::getLock() const
{
    return unlock;
};
void Item::setLock()
{
    unlock=true;
};
[[nodiscard]] std::string Item::getName() const
{
    return nume;
};
Item::Item(const std::string& descriere, const std::string& nume): descriere(descriere), nume(nume) {}