//
// Created by omega on 06.12.2025.
//

#ifndef OOP_ITEMS_H
#define OOP_ITEMS_H
#include<string>
class Items
{
protected:
    bool unlock=false;
    std::string descriere=" ", nume=" ";
public:
    Items()=default;
    [[nodiscard]] bool getlock() ;
    void setlock();
    [[nodiscard]] std::string getname() const;
    Items(const std::string& descriere,const std::string& nume);
    virtual float interact() =0;
    virtual ~Items()=default;
};

#endif //OOP_ITEMS_H