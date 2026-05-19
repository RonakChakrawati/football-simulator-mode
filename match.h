#ifndef MATCH_H
#define MATCH_H

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "models.h"

class Match
{
public:
    int homeGoals{0};
    int awayGoals{0};
    int winner{0};

    void score(const Team& t1, const Team& t2);
};

#endif