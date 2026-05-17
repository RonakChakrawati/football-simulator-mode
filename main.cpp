// project for football simulation

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

class GoalEvent
{
public:
    int time;
    string playerName;
};

class Player
{
public:
    string name;
    int shooting, passing, pace, dribbling, defending, physical;
    int getAttack()
    {
        return (shooting * 4 + dribbling * 3 + pace * 2 + passing * 2 + physical) / 12;
    }
    int getDefense()
    {
        return (defending * 4 + physical * 3 + pace * 2) / 9;
    }
};

class Team
{
public:
    string name;
    vector<Player> players; // array that stores the players of a team has type Player

    int generateTeamAttack()
    {
        int attackAvg{0};
        if (players.size() == 0)
            return 0;
        for (int i = 0; i < players.size(); i++)
        {
            attackAvg += players[i].getAttack();
        }
        return attackAvg / players.size();
    }

    int generateTeamDefend()
    {
        int defendAvg{0};
        if (players.size() == 0)
            return 0;
        for (int i = 0; i < players.size(); i++)
        {
            defendAvg += players[i].getDefense();
        }
        return defendAvg / players.size();
    }

    void displayTeam()
    {
        for (int i = 0; i < players.size(); i++)
        {
            cout << players[i].name << " | Attack: " << players[i].getAttack() << " | Defense: " << players[i].getDefense() << "\n";
        }
    }
};

class Match
{
public:
    int winner;
    void score(Team &t1, Team &t2)
    {
        vector<GoalEvent> events;
        int adv = t1.generateTeamAttack() - t2.generateTeamDefend();
        int dis = t2.generateTeamAttack() - t1.generateTeamDefend();

        if (adv < 0)
            adv = 0;
        if (dis < 0)
            dis = 0;

        int chances1 = adv / 2 + (rand() % 3);
        int chances2 = dis / 2 + (rand() % 3);

        int goals1{0}, goals2{0};

        cout << "\n===== MATCH START =====\n";
        cout << t1.name << " VS " << t2.name << "\n ";
        cout << "\nGoal Scorers:\n";

        Player attacker1, defender1, attacker2, defender2;

        for (int i = 0; i < chances1; i++)
        {
            int totalAttack = 0;
            for (int j = 0; j < 3; j++)
            {
                totalAttack += t1.players[j].getAttack();
            }
            int randomAttacker = rand() % totalAttack;
            int c1 = 0;
            for (int j = 0; j < 3; j++)
            {
                c1 += t1.players[j].getAttack();
                if (randomAttacker < c1)
                {
                    attacker1 = t1.players[j];
                    break;
                }
            }

            int c2 = 0;
            int totalDef{0};
            for (int j = 3; j < 6; j++)
            {
                totalDef += t2.players[j].getDefense();
            }
            int randomDef = rand() % totalDef;
            for (int j = 3; j < 6; j++)
            {
                c2 += t2.players[j].getDefense();
                if (randomDef < c2)
                {
                    defender2 = t2.players[j];
                    break;
                }
            }
            int duel = attacker1.getAttack() - defender2.getDefense();
            int chance = duel + rand() % 10;
            if (chance > 6)
            {
                GoalEvent g;
                goals1++;
                g.playerName = attacker1.name;
                g.time = rand() % 90 + 1;
                events.push_back(g);
            }
        }

        for (int i = 0; i < chances2; i++)
        {
            int totalAttack = 0;
            for (int j = 0; j < 3; j++)
            {
                totalAttack += t2.players[j].getAttack();
            }
            int randomAttacker = rand() % totalAttack;
            int c1 = 0;
            for (int j = 0; j < 3; j++)
            {
                c1 += t2.players[j].getAttack();
                if (randomAttacker < c1)
                {
                    attacker2 = t2.players[j];
                    break;
                }
            }

            int c2 = 0;
            int totalDef{0};
            for (int j = 3; j < 6; j++)
            {
                totalDef += t1.players[j].getDefense();
            }
            int randomDef = rand() % totalDef;
            for (int j = 3; j < 6; j++)
            {
                c2 += t1.players[j].getDefense();
                if (randomDef < c2)
                {
                    defender1 = t1.players[j];
                    break;
                }
            }
            int duel = attacker2.getAttack() - defender1.getDefense();
            int chance = duel + rand() % 10;
            if (chance > 6)
            {
                GoalEvent g;
                goals2++;
                g.playerName = attacker2.name;
                g.time = rand() % 90 + 1;
                events.push_back(g);
            }
        }

        // comparision function : [](GoalEvent a, GoalEvent b){return a.time < b.time;} - compares a.time and b.time
        sort(events.begin(), events.end(), [](GoalEvent a, GoalEvent b)
             { return a.time < b.time; });

        for (int j = 0; j < events.size(); j++)
        {
            cout << events[j].time << "' " << events[j].playerName << "\n";
        }
        cout << "\n"
             << t1.name << " " << goals1 << " - " << goals2 << " " << t2.name;
        cout << "\n";
        if (goals1 > goals2)
        {
            cout << t1.name << " wins!\n";
            winner = 1;
        }
        else if (goals2 > goals1)
        {
            cout << t2.name << " wins!\n";
            winner = 2;
        }
        else
        {
            cout << "Match Draw!\n";
            winner = 0;
        }
        cout << "\n===== FULL TIME =====\n";
    }
};

int main()
{
    srand(time(0));
    vector<Team> quickMatchTeams;

    // ==================== BARCELONA ====================

    Player bar1;
    bar1.name = "MESSI";
    bar1.pace = 96;
    bar1.shooting = 95;
    bar1.passing = 91;
    bar1.dribbling = 99;
    bar1.defending = 38;
    bar1.physical = 68;

    Player bar2;
    bar2.name = "NEYMAR";
    bar2.pace = 93;
    bar2.shooting = 89;
    bar2.passing = 86;
    bar2.dribbling = 97;
    bar2.defending = 37;
    bar2.physical = 63;

    Player bar3;
    bar3.name = "SUAREZ";
    bar3.pace = 88;
    bar3.shooting = 97;
    bar3.passing = 85;
    bar3.dribbling = 91;
    bar3.defending = 46;
    bar3.physical = 80;

    Player bar4;
    bar4.name = "PUYOL";
    bar4.pace = 74;
    bar4.shooting = 44;
    bar4.passing = 70;
    bar4.dribbling = 70;
    bar4.defending = 96;
    bar4.physical = 92;

    Player bar5;
    bar5.name = "PIQUE";
    bar5.pace = 69;
    bar5.shooting = 46;
    bar5.passing = 76;
    bar5.dribbling = 72;
    bar5.defending = 93;
    bar5.physical = 82;

    Player bar6;
    bar6.name = "KOEMAN";
    bar6.pace = 66;
    bar6.shooting = 83;
    bar6.passing = 87;
    bar6.dribbling = 73;
    bar6.defending = 87;
    bar6.physical = 80;

    Team bar;
    bar.name = "BARCELONA";
    bar.players.push_back(bar1);
    bar.players.push_back(bar2);
    bar.players.push_back(bar3);
    bar.players.push_back(bar4);
    bar.players.push_back(bar5);
    bar.players.push_back(bar6);

    // ==================== REAL MADRID ====================

    Player rma1;
    rma1.name = "RONALDO";
    rma1.pace = 95;
    rma1.shooting = 97;
    rma1.passing = 83;
    rma1.dribbling = 93;
    rma1.defending = 37;
    rma1.physical = 88;

    Player rma2;
    rma2.name = "BALE";
    rma2.pace = 97;
    rma2.shooting = 85;
    rma2.passing = 72;
    rma2.dribbling = 86;
    rma2.defending = 35;
    rma2.physical = 80;

    Player rma3;
    rma3.name = "BENZEMA";
    rma3.pace = 76;
    rma3.shooting = 92;
    rma3.passing = 88;
    rma3.dribbling = 89;
    rma3.defending = 40;
    rma3.physical = 80;

    Player rma4;
    rma4.name = "RAMOS";
    rma4.pace = 75;
    rma4.shooting = 70;
    rma4.passing = 80;
    rma4.dribbling = 78;
    rma4.defending = 95;
    rma4.physical = 89;

    Player rma5;
    rma5.name = "PEPE";
    rma5.pace = 74;
    rma5.shooting = 48;
    rma5.passing = 66;
    rma5.dribbling = 68;
    rma5.defending = 91;
    rma5.physical = 92;

    Player rma6;
    rma6.name = "CANNAVARO";
    rma6.pace = 82;
    rma6.shooting = 42;
    rma6.passing = 68;
    rma6.dribbling = 74;
    rma6.defending = 93;
    rma6.physical = 83;

    Team rma;
    rma.name = "REAL MADRID";
    rma.players.push_back(rma1);
    rma.players.push_back(rma2);
    rma.players.push_back(rma3);
    rma.players.push_back(rma4);
    rma.players.push_back(rma5);
    rma.players.push_back(rma6);

    // ==================== BAYERN MUNICH ====================

    Player bay1;
    bay1.name = "GERD MULLER";
    bay1.pace = 85;
    bay1.shooting = 98;
    bay1.passing = 74;
    bay1.dribbling = 86;
    bay1.defending = 42;
    bay1.physical = 82;

    Player bay2;
    bay2.name = "ROBBEN";
    bay2.pace = 95;
    bay2.shooting = 91;
    bay2.passing = 80;
    bay2.dribbling = 93;
    bay2.defending = 35;
    bay2.physical = 68;

    Player bay3;
    bay3.name = "LEWANDOWSKI";
    bay3.pace = 76;
    bay3.shooting = 97;
    bay3.passing = 80;
    bay3.dribbling = 88;
    bay3.defending = 45;
    bay3.physical = 90;

    Player bay4;
    bay4.name = "BECKENBAUER";
    bay4.pace = 73;
    bay4.shooting = 68;
    bay4.passing = 92;
    bay4.dribbling = 85;
    bay4.defending = 95;
    bay4.physical = 80;

    Player bay5;
    bay5.name = "VAN BUYTEN";
    bay5.pace = 64;
    bay5.shooting = 50;
    bay5.passing = 64;
    bay5.dribbling = 62;
    bay5.defending = 87;
    bay5.physical = 91;

    Player bay6;
    bay6.name = "PHILIPP LAHM";
    bay6.pace = 85;
    bay6.shooting = 66;
    bay6.passing = 89;
    bay6.dribbling = 88;
    bay6.defending = 91;
    bay6.physical = 78;

    Team bay;
    bay.name = "BAYERN MUNICH";
    bay.players.push_back(bay1);
    bay.players.push_back(bay2);
    bay.players.push_back(bay3);
    bay.players.push_back(bay4);
    bay.players.push_back(bay5);
    bay.players.push_back(bay6);

    // ==================== AC MILAN ====================

    Player mil1;
    mil1.name = "KAKA";
    mil1.pace = 91;
    mil1.shooting = 86;
    mil1.passing = 88;
    mil1.dribbling = 92;
    mil1.defending = 44;
    mil1.physical = 73;

    Player mil2;
    mil2.name = "INZAGHI";
    mil2.pace = 80;
    mil2.shooting = 93;
    mil2.passing = 62;
    mil2.dribbling = 78;
    mil2.defending = 34;
    mil2.physical = 74;

    Player mil3;
    mil3.name = "VAN BASTEN";
    mil3.pace = 80;
    mil3.shooting = 97;
    mil3.passing = 75;
    mil3.dribbling = 89;
    mil3.defending = 40;
    mil3.physical = 84;

    Player mil4;
    mil4.name = "MALDINI";
    mil4.pace = 84;
    mil4.shooting = 55;
    mil4.passing = 83;
    mil4.dribbling = 80;
    mil4.defending = 98;
    mil4.physical = 84;

    Player mil5;
    mil5.name = "NESTA";
    mil5.pace = 76;
    mil5.shooting = 44;
    mil5.passing = 78;
    mil5.dribbling = 74;
    mil5.defending = 97;
    mil5.physical = 86;

    Player mil6;
    mil6.name = "STAM";
    mil6.pace = 76;
    mil6.shooting = 48;
    mil6.passing = 70;
    mil6.dribbling = 68;
    mil6.defending = 92;
    mil6.physical = 95;

    Team mil;
    mil.name = "AC MILAN";
    mil.players.push_back(mil1);
    mil.players.push_back(mil2);
    mil.players.push_back(mil3);
    mil.players.push_back(mil4);
    mil.players.push_back(mil5);
    mil.players.push_back(mil6);

    quickMatchTeams.push_back(bar);
    quickMatchTeams.push_back(rma);
    quickMatchTeams.push_back(bay);
    quickMatchTeams.push_back(mil);

    int choice;
    cout << "\nWELCOME TO FOOTBALL MATCH SIMULATOR";
    cout << "\n";

    while (true)
    {
        cout << "1. CAREER MODE\n";
        cout << "2. QUICK MATCH\n";
        cout << "3. SIMULATION\n";
        cout << "4. EXIT\n\n";

        cout << "ENTER YOUR CHOICE : ";
        cin >> choice;
        system("clear");
        if (choice == 1)
        {
        }

        else if (choice == 2)
        {
            Team a;
            Team b;
            system("clear");

            cout << "=====================================\n";
            cout << "         QUICK MATCH MODE\n";
            cout << "=====================================\n\n";
            cout << "Choose Your Teams\n\n";
            cout << "[1] FC BARCELONA\n";
            cout << "[2] REAL MADRID\n";
            cout << "[3] BAYERN MUNICH\n";
            cout << "[4] AC MILAN\n\n";

            int selectTeam1, selectTeam2;
            cout << "ENTER TEAM 1 NUMBER : ";
            cin >> selectTeam1;
            a = quickMatchTeams[selectTeam1 - 1];
            cout << "\nENTER TEAM 2 NUMBER : ";
            cin >> selectTeam2;
            b = quickMatchTeams[selectTeam2 - 1];

            system("clear");
            cout << "=====================================\n";
            cout << "        MATCH STARTING...\n";
            cout << "=====================================\n\n";

            cout << a.name << "  VS  " << b.name << "\n\n";
            Match q1;
            q1.score(a, b);

            cout << "\n=====================================\n";
            cout << " Press any number to return to menu ";
            cout << "\n=====================================\n";

            string back1;
            cin >> back1;
            cout << "\n";
            system("clear");
        }

        else if (choice == 3)
        {
            system("clear");
            cout << "=====================================\n";
            cout << "         AUTO SIMULATION\n";
            cout << "=====================================\n\n";
            cout << "[1] FC BARCELONA\n";
            cout << "[2] REAL MADRID\n";
            cout << "[3] BAYERN MUNICH\n";
            cout << "[4] AC MILAN\n\n";

            int team1Choice, team2Choice;
            int simulations;
            cout << "ENTER TEAM 1 : ";
            cin >> team1Choice;
            cout << "ENTER TEAM 2 : ";
            cin >> team2Choice;
            cout << "NUMBER OF SIMULATIONS : ";
            cin >> simulations;
            Team sim1 = quickMatchTeams[team1Choice - 1];
            Team sim2 = quickMatchTeams[team2Choice - 1];
            int wins1 = 0;
            int wins2 = 0;
            int draws = 0;
            Match autoSim;
            for (int i = 1; i <= simulations; i++)
            {
                cout << "\n========== MATCH " << i << " ==========\n";
                autoSim.score(sim1, sim2);
                if (autoSim.winner == 1) wins1++;
                else if (autoSim.winner == 2) wins2++;
                else draws++;
            }
            cout << "\n=====================================\n";
            cout << "         FINAL RESULTS\n";
            cout << "=====================================\n";
            cout << sim1.name << " Wins : " << wins1 << endl;
            cout << sim2.name << " Wins : " << wins2 << endl;
            cout << "Draws : " << draws << endl;
            cout << "\n=====================================\n";
            string back;
            cin >> back;
            system("clear");
        }
        else if (choice == 4)
        {
            cout << "THANKS FOR PLAYING !";
            return 0;
        }
        else
        {
            cout << "INVALID INPUT !\n";
        }
    }
    return 0;
}