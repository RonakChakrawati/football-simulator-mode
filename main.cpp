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
        return (shooting + passing + pace + dribbling) / 4;
    }
    int getDefense()
    {
        return (defending + physical) / 2;
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

        for (int i = 0; i < chances1; i++)
        {
            int chancesInToGoals1 = rand() % 10;
            if (chancesInToGoals1 == 0)
            {
                GoalEvent g;
                goals1++;
                int time1 = rand() % 90 + 1;
                g.time = time1;
                int totalShoot = 0;
                for (int j = 0; j < t1.players.size(); j++)
                {
                    totalShoot += t1.players[j].shooting;
                }
                int randomGoalScorer = rand() % totalShoot;
                int c = 0;
                for (int j = 0; j < t1.players.size(); j++)
                {
                    c += t1.players[j].shooting;
                    if (randomGoalScorer < c)
                    {
                        g.playerName = t1.players[j].name;
                        break;
                    }
                }
                events.push_back(g);
            }
        }

        for (int i = 0; i < chances2; i++)
        {
            int chancesInToGoals2 = rand() % 10;
            if (chancesInToGoals2 == 0)
            {
                goals2++;
                GoalEvent g;
                int time2 = rand() % 90 + 1;
                g.time = time2;
                int totalShoot = 0;
                for (int j = 0; j < t2.players.size(); j++)
                {
                    totalShoot += t2.players[j].shooting;
                }
                int randomGoalScorer = rand() % totalShoot;
                int c = 0;
                for (int j = 0; j < t2.players.size(); j++)
                {
                    c += t2.players[j].shooting;
                    if (randomGoalScorer < c)
                    {
                        g.playerName = t2.players[j].name;
                        break;
                    }
                }
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
            cout << t1.name << " wins!\n";
        else if (goals2 > goals1)
            cout << t2.name << " wins!\n";
        else
            cout << "Match Draw!\n";
        cout << "\n===== FULL TIME =====\n";
    }
};

int main()
{
    srand(time(0));
    vector<Team> quickMatchTeams;
    
    Player bar1;
    bar1.name = "MESSI";
    bar1.shooting = 92;
    bar1.passing = 91;
    bar1.pace = 94;
    bar1.dribbling = 95;
    bar1.defending = 40;
    bar1.physical = 65;

    Player bar2;
    bar2.name = "NEYMAR";
    bar2.pace = 92;
    bar2.shooting = 87;
    bar2.dribbling = 94;
    bar2.passing = 85;
    bar2.defending = 40;
    bar2.physical = 68;

    Player bar3;
    bar3.name = "SUAREZ";
    bar3.shooting = 91;
    bar3.pace = 87;
    bar3.dribbling = 91;
    bar3.passing = 83;
    bar3.defending = 50;
    bar3.physical = 85;

    Player bar4;
    bar4.name = "PUYOL";
    bar4.shooting = 58;
    bar4.pace = 78;
    bar4.dribbling = 72;
    bar4.passing = 74;
    bar4.defending = 92;
    bar4.physical = 90;

    Player bar5;
    bar5.name = "PIQUE";
    bar5.shooting = 61;
    bar5.pace = 68;
    bar5.dribbling = 73;
    bar5.passing = 80;
    bar5.defending = 89;
    bar5.physical = 84;

    Player bar6;
    bar6.name = "KOEMAN";
    bar6.shooting = 82;
    bar6.pace = 70;
    bar6.dribbling = 78;
    bar6.passing = 88;
    bar6.defending = 90;
    bar6.physical = 86;

    Team bar;
    bar.name = "BARCELONA";

    bar.players.push_back(bar1);
    bar.players.push_back(bar2);
    bar.players.push_back(bar3);
    bar.players.push_back(bar4);
    bar.players.push_back(bar5);
    bar.players.push_back(bar6);

    Player rma1;
    rma1.name = "RONALDO";
    rma1.pace = 95;
    rma1.shooting = 93;
    rma1.dribbling = 94;
    rma1.passing = 83;
    rma1.defending = 37;
    rma1.physical = 84;

    Player rma2;
    rma2.name = "BALE";
    rma2.pace = 96;
    rma2.shooting = 85;
    rma2.dribbling = 90;
    rma2.passing = 80;
    rma2.defending = 57;
    rma2.physical = 80;

    Player rma3;
    rma3.name = "BENZEMA";
    rma3.pace = 83;
    rma3.shooting = 84;
    rma3.dribbling = 82;
    rma3.passing = 75;
    rma3.defending = 22;
    rma3.physical = 74;

    Player rma4;
    rma4.name = "RAMOS";
    rma4.shooting = 72;
    rma4.pace = 79;
    rma4.dribbling = 75;
    rma4.passing = 76;
    rma4.defending = 91;
    rma4.physical = 89;

    Player rma5;
    rma5.name = "PEPE";
    rma5.shooting = 55;
    rma5.pace = 77;
    rma5.dribbling = 67;
    rma5.passing = 70;
    rma5.defending = 90;
    rma5.physical = 91;

    Player rma6;
    rma6.name = "CANNAVARO";
    rma6.shooting = 50;
    rma6.pace = 80;
    rma6.dribbling = 69;
    rma6.passing = 72;
    rma6.defending = 93;
    rma6.physical = 82;

    Team rma;
    rma.name = "REAL MADRID";

    rma.players.push_back(rma1);
    rma.players.push_back(rma2);
    rma.players.push_back(rma3);
    rma.players.push_back(rma4);
    rma.players.push_back(rma5);
    rma.players.push_back(rma6);

    Player bay1;
    bay1.name = "RIBERY";
    bay1.shooting = 87;
    bay1.passing = 86;
    bay1.pace = 92;
    bay1.dribbling = 94;
    bay1.defending = 45;
    bay1.physical = 56;

    Player bay2;
    bay2.name = "ROBBEN";
    bay2.shooting = 89;
    bay2.passing = 84;
    bay2.pace = 93;
    bay2.dribbling = 93;
    bay2.defending = 48;
    bay2.physical = 60;

    Player bay3;
    bay3.name = "LEWANDOWSKI";
    bay3.shooting = 94;
    bay3.passing = 59;
    bay3.pace = 80;
    bay3.dribbling = 80;
    bay3.defending = 51;
    bay3.physical = 89;

    Player bay4;
    bay4.name = "BECKENBAUER";
    bay4.shooting = 70;
    bay4.pace = 82;
    bay4.dribbling = 81;
    bay4.passing = 88;
    bay4.defending = 95;
    bay4.physical = 84;

    Player bay5;
    bay5.name = "VAN BUYTEN";
    bay5.shooting = 58;
    bay5.pace = 66;
    bay5.dribbling = 60;
    bay5.passing = 68;
    bay5.defending = 88;
    bay5.physical = 90;

    Player bay6;
    bay6.name = "PHILIPP LAHM";
    bay6.shooting = 67;
    bay6.pace = 87;
    bay6.dribbling = 84;
    bay6.passing = 89;
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

    Player mil1;
    mil1.name = "KAKA";
    mil1.shooting = 86;
    mil1.passing = 88;
    mil1.pace = 91;
    mil1.dribbling = 91;
    mil1.defending = 38;
    mil1.physical = 74;

    Player mil2;
    mil2.name = "INZAGHI";
    mil2.shooting = 91;
    mil2.passing = 68;
    mil2.pace = 74;
    mil2.dribbling = 78;
    mil2.defending = 35;
    mil2.physical = 70;

    Player mil3;
    mil3.name = "VAN BASTEN";
    mil3.shooting = 94;
    mil3.passing = 58;
    mil3.pace = 90;
    mil3.dribbling = 86;
    mil3.defending = 52;
    mil3.physical = 81;

    Player mil4;
    mil4.name = "MALDINI";
    mil4.shooting = 62;
    mil4.pace = 84;
    mil4.dribbling = 78;
    mil4.passing = 82;
    mil4.defending = 96;
    mil4.physical = 87;

    Player mil5;
    mil5.name = "NESTA";
    mil5.shooting = 54;
    mil5.pace = 76;
    mil5.dribbling = 72;
    mil5.passing = 79;
    mil5.defending = 94;
    mil5.physical = 86;

    Player mil6;
    mil6.name = "STAM";
    mil6.shooting = 50;
    mil6.pace = 78;
    mil6.dribbling = 65;
    mil6.passing = 70;
    mil6.defending = 92;
    mil6.physical = 93;

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
        cout << "3. EXIT\n\n";

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