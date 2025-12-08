#include <iostream>
#include <fstream>
#include <limits>
class enemies
{
    std::string descriere, nume;
    bool unlock=false;
    int nrlimbs=6;
    public:
    enemies()=default;
    [[nodiscard]] bool checklock() const
    {
        return unlock;
    }
    void changelock()
    {
        unlock=true;
    }
    [[nodiscard]] std::string& afis()

    {
        return nume;
    }
    friend std::istream& operator>>(std::istream& in, enemies& e)
    {
        std::getline(in, e.nume);
        std::getline(in, e.descriere);
        in>>e.nrlimbs;
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return in;
    }
    friend std::ostream& operator<<(std::ostream& out,const enemies& e)
    {
        out<<"Name:"<<e.nume<<std::endl;
        out<<"Limb amount:"<<e.nrlimbs<<std::endl;
        out<<e.descriere<<std::endl<<std::endl;
        return out;
    }
    enemies(int nrlimbs,const std::string& descriere,const std::string& nume)
    {
        this->descriere = descriere;
        this->nume = nume;
        this->nrlimbs = nrlimbs;
    }
    ~enemies()=default;
};
class characters
{
    int nrlimbs=6;
    std::string descriere, nume;
    bool unlock=false;
    public:
    characters ()=default;
    [[nodiscard]] bool checklock() const
    {
        return unlock;
    }
    void changelock()
    {
        unlock=true;
    }
    [[nodiscard]] std::string& afis()
    {
        return nume;
    }
    friend std::istream& operator>>(std::istream& in, characters& p)
    {
        std::getline(in ,p.nume);
        std::getline(in,p.descriere);
        in>>p.nrlimbs;
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return in;
    }
    friend std::ostream& operator<<(std::ostream& out,const characters& p)
    {
        out<<"Name:"<<p.nume<<std::endl;
        out<<"Limb amount:"<<p.nrlimbs<<std::endl;
        out<<p.descriere<<std::endl<<std::endl;
        return out;
    }
    characters(int nrlimbs,const std::string& descriere,const std::string& nume)
    {
        this->nrlimbs = nrlimbs;
        this->descriere = descriere;
        this->nume = nume;
    }
    ~characters()=default;
};
class items
{
    std::string descriere, nume;
    bool unlock=false;
    public:
    items()=default;
    [[nodiscard]] bool checklock() const
    {
        return unlock;
    }
    void changelock()
    {
        unlock=true;
    }
    [[nodiscard]] std::string& afis()
    {
        return nume;
    }
    friend std::istream& operator>>(std::istream& in, items& g)
    {
        std::getline(in ,g.nume);
        std::getline(in,g.descriere);
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return in;
    }
    friend std::ostream& operator<<(std::ostream& out,const items& g)
    {
        out<<"Name:"<<g.nume<<std::endl;
        out<<g.descriere<<std::endl<<std::endl;
        return out;
    }
    items(const std::string& descriere,const std::string& nume)
    {
        this->descriere = descriere;
        this->nume = nume;
    }
    ~items()=default;
};
int main()
{
    std::ifstream efis("C:/Users/omega/CLionProjects/The-Descend/enemy.txt");
    std::ifstream pfis("C:/Users/omega/CLionProjects/The-Descend/chara.txt");
    std::ifstream gfis("C:/Users/omega/CLionProjects/The-Descend/thebusiness.txt");
    items g[8];
    characters p[5];
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
        int flag = 0;
        std::cout<<"Welcome to the informational terminal:"<<std::endl<<"for enemy information type:enemy"<<std::endl<<"for item information:item"<<std::endl<<"for character information type:chara"<<std::endl<<"for termination type:end"<<std::endl;
        std::getline(std::cin, cursor);
        if (cursor == "enemy") flag=1;
        if (cursor == "item") flag=2;
        if (cursor == "chara") flag=3;
        switch (flag)
        {
            case 1:
                while (cursor != "return")
                {
                    int ok=0;
                    std::cout<<"The enemies are: ";
                    for (int i=0 ;i<=9; i++)
                        if (e[i].checklock()==true)
                        std::cout<<e[i].afis()<<", ";
                    std::cout<<std::endl;
                    std::cout<<"To go back type:return"<<std::endl;
                    std::getline(std::cin, cursor);
                    for (int i=0 ;i<=9; i++)
                        if (cursor == e[i].afis())
                        {
                            if (e[i].checklock()==false)
                                e[i].changelock();
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
                    std::cout<<"The items are: ";
                    for (int i=0 ;i<=5; i++)
                        if (g[i].checklock()==true)
                        std::cout<<g[i].afis()<<", ";
                    std::cout<<std::endl;
                    std::cout<<"To go back type:return"<<std::endl;
                    std::getline(std::cin, cursor);
                    for (int i=0 ;i<=5; i++)
                        if (cursor == g[i].afis())
                        {
                            if (g[i].checklock()==false)
                                g[i].changelock();
                            std::cout<<g[i];
                            ok=1;
                        }
                    if (cursor != "return")
                        if (ok==0)
                            std::cout<<"Invalid item"<<std::endl<<std::endl;
                }
                break;
            case 3:
                while (cursor != "return")
                {
                    int ok=0;
                    std::cout<<"The characters are: ";
                    for (int i=0 ;i<=2; i++)
                        if (p[i].checklock()==true)
                        std::cout<<p[i].afis()<<", ";
                    std::cout<<std::endl;
                    std::cout<<"To go back type:return"<<std::endl;
                    std::getline(std::cin, cursor);
                    for (int i=0 ;i<=2; i++)
                        if (cursor == p[i].afis())
                        {
                            if (p[i].checklock()==false)
                                p[i].changelock();
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