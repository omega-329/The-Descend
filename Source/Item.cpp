
#include "../Header/Item.h"
[[nodiscard]] bool Item::getlock() const
{
    return unlock;
};
void Item::setlock()
{
    unlock=true;
};
[[nodiscard]] std::string Item::getname() const
{
    return nume;
};
Item::Item(const std::string& descriere, const std::string& nume): descriere(descriere), nume(nume) {}