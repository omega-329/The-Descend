

#ifndef OOP_PARTY_H
#define OOP_PARTY_H

#pragma once
#include <vector>
#include "Character.h"

class Party
{
public:
    void addMember(const Character& c);
    std::vector<Character>& getMembers();
    const std::vector<Character>& getMembers() const;

private:
    std::vector<Character> members;
};

#endif //OOP_PARTY_H