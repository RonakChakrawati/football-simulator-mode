#include "match.h"
using namespace std;

//   [0]  = GK
//   [1] [2] [3] = Defenders (DEF)
//   [4] [5] [6] [7] = Midfielders (MID)
//   [8] [9] [10]    = Attackers (ATT)

void Match::score(const Team &t1, const Team &t2)
{
    homeGoals = 0;
    awayGoals = 0;
    winner = 0;
    vector<GoalEvent> events;
    int adv = (t1.getTeamAttack() * 3 + t1.getTeamMidfield() * 2) - (t2.getTeamDefense() * 2 + t2.getTeamMidfield() / 2);
    int dis = (t2.getTeamAttack() * 3 + t2.getTeamMidfield() * 2) - (t1.getTeamDefense() * 2 + t1.getTeamMidfield() / 2);
    if (adv < 0) adv = 0;
    if (dis < 0) dis = 0;
    int chances1 = (adv / 18) + 1 + (rand() % 3);
    int chances2 = (dis / 18) + 1 + (rand() % 3);

    for (int i = 0; i < chances1; i++)
    {
        int totalAttack = 0;
        for (int j = 0; j < 11; j++)
        {
            if (t1.players[j].role == "Attacker")
            {
                totalAttack += t1.players[j].getAttack();
            }
        }
        Player attacker1;
        int randomAttacker = rand() % totalAttack;
        int cAtk = 0;
        for (int j = 0; j < 11; j++)
        {
            if (t1.players[j].role == "Attacker")
            {
                cAtk += t1.players[j].getAttack();
                if (randomAttacker < cAtk)
                {
                    attacker1 = t1.players[j];
                    break;
                }
            }
        }

        int totalDef = 0;
        for (int j = 0; j < 11; j++)
        {
            if (t2.players[j].role == "Defender")
            {
                totalDef += t2.players[j].getDefense();
            }
        } 
        Player defender2;
        int randomDef = rand() % totalDef;
        int cDef = 0;
        for (int j = 0; j < 11; j++)
        {
            if (t2.players[j].role == "Defender")
            {
                cDef += t2.players[j].getDefense();
                if (randomDef < cDef){
                    defender2 = t2.players[j];
                    break;
                }
            }
        }

        double scoringChance = ((double)attacker1.getAttack()+(double)t1.getTeamMidfield()) / (t2.getTeamMidfield() + defender2.getDefense() + t2.getTeamGoalkeeping() + (double)attacker1.getAttack()+(double)t1.getTeamMidfield());
        int roll = rand() % 100;
        if (roll < scoringChance * 20)
        {
            GoalEvent g;
            g.playerName = attacker1.name;
            g.time = rand() % 90 + 1;
            homeGoals++;
            events.push_back(g);
        }
    }

    for (int i = 0; i < chances2; i++)
    {
        int totalAttack = 0;
        for (int j = 0; j < 11; j++)
        {
            if (t2.players[j].role == "Attacker")
            {
                totalAttack += t2.players[j].getAttack();
            }
        }

        Player attacker2;
        int randomAttacker = rand() % totalAttack;
        int cAtk = 0;
        for (int j = 0; j < 11; j++)
        {
            if (t2.players[j].role == "Attacker")
            {
                cAtk += t2.players[j].getAttack();
                if (randomAttacker < cAtk)
                {
                    attacker2 = t2.players[j];
                    break;
                }
            }
        }

        int totalDef = 0;
        for (int j = 0; j < 11; j++)
        {
            if (t1.players[j].role == "Defender")
            {
                totalDef += t1.players[j].getDefense();
            }
        }

        Player defender1;
        int randomDef = rand() % totalDef;
        int cDef = 0;
        for (int j = 0; j < 11; j++)
        {
            if (t1.players[j].role == "Defender")
            {
                cDef += t1.players[j].getDefense();
                if (randomDef < cDef){
                defender1 = t1.players[j];
                break;
                }
            }
        }

        double scoringChance = ((double)attacker2.getAttack() + (double)t2.getTeamMidfield()) / (t1.getTeamMidfield() + defender1.getDefense() + t1.getTeamGoalkeeping() + (double)attacker2.getAttack() + (double)t2.getTeamMidfield());
        int roll = rand() % 100;
        if (roll < scoringChance *  20)
        {
            GoalEvent g;
            g.playerName = attacker2.name;
            g.time = rand() % 90 + 1;
            awayGoals++;
            events.push_back(g);
        }
    }

    cout << "\n===== MATCH START =====\n";
    cout << t1.name << " VS " << t2.name << "\n";

    sort(events.begin(), events.end(), [](const GoalEvent &a, const GoalEvent &b)
         { return a.time < b.time; });

    if (!events.empty())
    {
        cout << "\nGoal Scorers:\n";
        for (const GoalEvent &g : events)
            cout << "  " << g.time << "' " << g.playerName << "\n";
    }
    else
    {
        cout << "\n  No goals scored.\n";
    }

    cout << "\n"
         << t1.name << "  " << homeGoals << " - " << awayGoals << "  " << t2.name << "\n";

    if (homeGoals > awayGoals)
    {
        cout << t1.name << " wins!\n";
        winner = 1;
    }
    else if (awayGoals > homeGoals)
    {
        cout << t2.name << " wins!\n";
        winner = 2;
    }
    else
    {
        cout << "Match Draw!\n";
        winner = 0;
    }

    cout << "===== FULL TIME =====\n";
}