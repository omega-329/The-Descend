
#include "../Header/Party.h"

void Party::addMember(const Character& c)
{
    members.push_back(c);
}

std::vector<Character>& Party::getMembers()
{
    return members;
}

const std::vector<Character>& Party::getMembers() const
{
    return members;
}