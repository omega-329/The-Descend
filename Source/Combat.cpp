#include "../Header/Combat.h"
#include <random>
[[nodiscard]] bool combat::getturn() const
{
    return whoturn;
}
void combat::setturn(bool& cturn)
{
    if (cturn==true)
        cturn=false;
    else
        cturn=true;
}
void combat::oneset()
{
    int i, curentlimbnrpeople, curentlimbnrenemy;
    float totaldmg=0;
    static std::random_device rd;
    static std::mt19937 gen(rd());
    if (getturn()==true)
    {
        for (i=0; i<3; i++)
        {
            if (people[i].getalive()==true)
            {
                std::uniform_int_distribution<> dist(0, people[i].getlimbcount()-1);
                curentlimbnrpeople = dist(gen);
                while (people[i].getlimb(curentlimbnrpeople).gethp()<=0)
                {
                    std::uniform_int_distribution<> dist(0, people[i].getlimbcount()-1);
                    curentlimbnrpeople = dist(gen);
                }
                // totaldmg=totaldmg+people[i].getcurrentweapon.interact();
            }
        }
        std::uniform_int_distribution<> dist(0, opponent.getlimbcount()-1);
        curentlimbnrenemy = dist(gen);
        while (opponent.getlimb(curentlimbnrenemy).gethp()<=0)
        {
            std::uniform_int_distribution<> dist(0, opponent.getlimbcount()-1);
            curentlimbnrenemy = dist(gen);
        }
        opponent.getlimb(curentlimbnrenemy).sethp(opponent.getlimb(curentlimbnrenemy).gethp()-totaldmg);
        if (opponent.getlimb(curentlimbnrenemy).gethp()<=0)
            opponent.getlimb(curentlimbnrenemy).setintact();
    }
    else
    {
        totaldmg=0;
        std::uniform_int_distribution<> dist(0, opponent.getlimbcount()-1);
        curentlimbnrenemy = dist(gen);
        while (opponent.getlimb(curentlimbnrenemy).gethp()<=0)
        {
            std::uniform_int_distribution<> dist(0, opponent.getlimbcount()-1);
            curentlimbnrenemy = dist(gen);
        }
        totaldmg=totaldmg+opponent.getlimb(curentlimbnrenemy).gethp();
        i=dist(gen)%4;
        curentlimbnrpeople = dist(gen)%people[i].getlimbcount();
        while (people[i].getlimb(curentlimbnrpeople).gethp()<=0)
        {
            std::uniform_int_distribution<> dist(0, people[i].getlimbcount()-1);
            curentlimbnrpeople = dist(gen);
        }
        people[i].getlimb(curentlimbnrpeople).sethp(people[i].getlimb(curentlimbnrpeople).gethp()-totaldmg);
        if (people[i].getlimb(curentlimbnrpeople).gethp()<=0)
            people[i].getlimb(curentlimbnrpeople).setintact();
    }
}