#include <iostream>
#include <fstream>
#include <limits>
class enemies
{
    int hp=60, dmg=10;
    std::string descriere, nume, fac;
    public:
    enemies()=default;
    std::string afis()
    {
        return nume;
    }
    friend std::istream& operator>>(std::istream& in, enemies& e)
    {
        std::getline(in, e.nume);
        std::getline(in, e.fac);
        std::getline(in, e.descriere);
        in>>e.hp>>e.dmg;
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return in;
    }
    friend std::ostream& operator<<(std::ostream& out,const enemies& e)
    {
        out<<"Name:"<<e.nume<<std::endl;
        out<<"Faction:"<<e.fac<<std::endl;
        out<<"Health pool:"<<e.hp<<"      "<<"Damage per hit:"<<e.dmg<<std::endl;
        out<<e.descriere<<std::endl<<std::endl;
        return out;
    }
    enemies(int hp, int dmg,const std::string& descriere,const std::string& nume,const std::string& fac)
    {
        this->hp = hp;
        this->dmg = dmg;
        this->descriere = descriere;
        this->nume = nume;
        this->fac = fac;
    }
    ~enemies()=default;
};
class player
{
    int hp=100;
    std::string descriere, nume;
    public:
    player ()=default;
    std::string afis()
    {
        return nume;
    }
    friend std::istream& operator>>(std::istream& in, player& p)
    {
        std::getline(in ,p.nume);
        std::getline(in,p.descriere);
        in>>p.hp;
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return in;
    }
    friend std::ostream& operator<<(std::ostream& out,const player& p)
    {
        out<<"Name:"<<p.nume<<std::endl;
        out<<"Health pool:"<<p.hp<<std::endl;
        out<<p.descriere<<std::endl<<std::endl;
        return out;
    }
    player(int hp,const std::string& descriere,const std::string& nume)
    {
        this->hp = hp;
        this->descriere = descriere;
        this->nume = nume;
    }
    ~player()=default;
};
class gun
{
    int dmg=25, multishot=1;
    std::string descriere, nume;
    public:
    gun()=default;
    std::string afis()
    {
        return nume;
    }
    friend std::istream& operator>>(std::istream& in, gun& g)
    {
        std::getline(in ,g.nume);
        std::getline(in,g.descriere);
        in>>g.dmg>>g.multishot;
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return in;
    }
    friend std::ostream& operator<<(std::ostream& out,const gun& g)
    {
        out<<"Name:"<<g.nume<<std::endl;
        out<<"Damage per bullet:"<<g.dmg<<"      Number of bullets per shot:"<<g.multishot<<std::endl;
        out<<g.descriere<<std::endl<<std::endl;
        return out;
    }
    gun(int dmg, int multishot,const std::string& descriere,const std::string& nume)
    {
        this->dmg = dmg;
        this->multishot = multishot;
        this->descriere = descriere;
        this->nume = nume;
    }
    ~gun()=default;
};
int main()
{
    std::ifstream efis("C:/Users/omega/CLionProjects/The-Descend/enemy.txt");
    std::ifstream pfis("C:/Users/omega/CLionProjects/The-Descend/chara.txt");
    std::ifstream gfis("C:/Users/omega/CLionProjects/The-Descend/thebusiness.txt");
    gun g[8];
    player p[5];
    enemies e[12];
    std::string cursor;
    if (!efis || !pfis || !gfis)
    {
        std::cout << "A muriat codul";
        return 0;
    }
    for (int i=0; i<=2; i++)
    {
        pfis>>p[i];
    }
    for (int i=0; i<=5; i++)
    {
        gfis>>g[i];
    }
    for (int i=0; i<=9; i++)
    {
        efis>>e[i];
    }
    while (cursor != "end")
    {
        int flag = 0, nrene=7, nrgun=3, nrchr=1;
        bool chrg[1], eneg[2], gung[2];
        std::cout<<"Welcome to the informational terminal:"<<std::endl<<"for enemy information type:enemy"<<std::endl<<"for gun information type:gun"<<std::endl<<"for character information type:chara"<<std::endl<<"for termination type:end"<<std::endl;
        std::getline(std::cin, cursor);
        if (cursor == "enemy") flag=1;
        if (cursor == "gun") flag=2;
        if (cursor == "chara") flag=3;
        switch (flag)
        {
            case 1:
                while (cursor != "return")
                {
                    int ok=0;
                    std::cout<<"The enemies are: ";
                    for (int i=0 ;i<=nrene; i++)
                        std::cout<<e[i].afis()<<", ";
                    std::cout<<std::endl;
                    std::cout<<"To go back type:return"<<std::endl;
                    std::getline(std::cin, cursor);
                    for (int i=0 ;i<=9; i++)
                        if (cursor == e[i].afis())
                        {
                            if (i==8 && eneg[0]==0)
                            {
                                nrene++;
                                eneg[0]=true;
                            }
                            if (i==9 && eneg[1]==0)
                            {
                                nrene++;
                                eneg[1]=true;
                            }
                            std::cout<<e[i];
                            ok=1;
                        }
                    if (cursor != "return")
                        if (ok==0)
                            std::cout<<"Invalid enemy"<<std::endl<<std::endl;
                }
                break;
            case 2:
                while (cursor != "return")
                {
                    int ok=0;
                    std::cout<<"The guns are: ";
                    for (int i=0 ;i<=nrgun; i++)
                        std::cout<<g[i].afis()<<", ";
                    std::cout<<std::endl;
                    std::cout<<"To go back type:return"<<std::endl;
                    std::getline(std::cin, cursor);
                    for (int i=0 ;i<=5; i++)
                        if (cursor == g[i].afis())
                        {
                            if (i==4 && gung[0]==0)
                            {
                                nrgun++;
                                gung[0]=true;
                            }
                            if (i==5 && gung[1]==0)
                            {
                                nrgun++;
                                gung[1]=true;
                            }
                            std::cout<<g[i];
                            ok=1;
                        }
                    if (cursor != "return")
                        if (ok==0)
                            std::cout<<"Invalid gun"<<std::endl<<std::endl;
                }
                break;
            case 3:
                while (cursor != "return")
                {
                    int ok=0;
                    std::cout<<"The characters are: ";
                    for (int i=0 ;i<=nrchr; i++)
                        std::cout<<p[i].afis()<<", ";
                    std::cout<<std::endl;
                    std::cout<<"To go back type:return"<<std::endl;
                    std::getline(std::cin, cursor);
                    for (int i=0 ;i<=2; i++)
                        if (cursor == p[i].afis())
                        {
                            if (i==2 && chrg[0]==0)
                            {
                                nrchr++;
                                chrg[0]=true;
                            }
                            std::cout<<p[i];
                            ok=1;
                        }
                    if (cursor != "return")
                        if (ok==0)
                            std::cout<<"Invalid character"<<std::endl<<std::endl;
                }
                break;
            default:
                if (cursor != "end")
                std::cout<<"Invalid command"<<std::endl<<std::endl;
                break;
        }
    }
    return 0;
}