
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
[[nodiscard]] int Item::getQuantity() const
{
    return quantity;
}
void Item::setQuantity(int q)
{
    quantity=q;
}
void Item::decreaseQuantity()
{
    if (quantity>0) quantity--;
}
[[nodiscard]] bool Item::isConsumable() const
{
    return false;
}
Item::Item(const std::string& descriere, const std::string& nume): descriere(descriere), nume(nume) {}