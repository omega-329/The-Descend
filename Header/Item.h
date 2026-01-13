
#ifndef OOP_ITEMS_H
#define OOP_ITEMS_H
#include<string>
class Item
{
protected:
    bool unlock=false;
    std::string descriere=" ", nume=" ";
public:
    Item()=default;
    [[nodiscard]] bool getlock() const;
    void setlock();
    [[nodiscard]] std::string getname() const;
    Item(const std::string& descriere,const std::string& nume);
    virtual float interact() =0;
    virtual ~Item()=default;
    friend std::istream& operator>>(std::istream& in, Item& i);
};

#endif //OOP_ITEMS_H