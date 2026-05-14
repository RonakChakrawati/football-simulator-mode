// project for football simulation

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

class GoalEvent{
public:
    int time;
    string playerName;
};

class Player{
public:
    string name;
    int shooting, passing, pace, dribbling, defending, physical;
    int getAttack(){
        return (shooting + passing + pace + dribbling) / 4;
    }
    int getDefense(){
        return (defending + physical) / 2;
    }
};

class Team{
public:
    string name;
    vector<Player> players; // array that stores the players of a team has type Player

    int generateTeamAttack(){
        int attackAvg{0};
        if (players.size() == 0)return 0;
        for (int i = 0; i < players.size(); i++){
            attackAvg += players[i].getAttack();
        }
        return attackAvg / players.size();
    }

    int generateTeamDefend(){
        int defendAvg{0};
        if (players.size() == 0)return 0;
        for (int i = 0; i < players.size(); i++){
            defendAvg += players[i].getDefense();
        }
        return defendAvg / players.size();
    }

    void displayTeam(){
        for (int i = 0; i < players.size(); i++){
            cout << players[i].name << " | Attack: " << players[i].getAttack() << " | Defense: " << players[i].getDefense() << "\n";
        }
    }
};

class Match{
public:
    void score(Team &t1, Team &t2){
        vector<GoalEvent> events;
        int adv = t1.generateTeamAttack() - t2.generateTeamDefend();
        int dis = t2.generateTeamAttack() - t1.generateTeamDefend();

        if (adv < 0) adv = 0;
        if (dis < 0) dis = 0;

        int chances1 = adv/2 + (rand()%3);
        int chances2 = dis/2 + (rand()%3);

        int goals1{0} , goals2{0};

        cout << "\n===== MATCH START =====\n";
        cout << t1.name << " VS " << t2.name << "\n ";
        cout << "\nGoal Scorers:\n";

        for(int i = 0; i < chances1 ; i++){
        int chancesInToGoals1 = rand()%10;
        if(chancesInToGoals1 == 9){
            GoalEvent g;
            goals1++;
            int time1 = rand() % 90 + 1;
            g.time = time1;
            int totalShoot = 0;
            for(int j = 0; j < t1.players.size(); j++){
                totalShoot += t1.players[j].shooting;
            }
            int randomGoalScorer = rand() % totalShoot;
            int c = 0;
            for(int j = 0; j < t1.players.size(); j++){
                c += t1.players[j].shooting;
                if(randomGoalScorer < c){
                    g.playerName = t1.players[j].name;
                    break;
                }
            }
            events.push_back(g);
            }
        }

        for(int i = 0; i < chances2 ; i++){
        int chancesInToGoals2 = rand()%10;
        if(chancesInToGoals2 == 9){
            goals2++;
            GoalEvent g;
            int time2 = rand() % 90 + 1;
            g.time = time2;
            int totalShoot = 0;
            for(int j = 0; j < t2.players.size(); j++){
                totalShoot += t2.players[j].shooting;
            }
            int randomGoalScorer = rand() % totalShoot;
            int c = 0;
            for(int j = 0; j < t2.players.size(); j++){
                c += t2.players[j].shooting;
                if(randomGoalScorer < c){
                    g.playerName = t2.players[j].name;
                    break;
                }
            }
            events.push_back(g);
            }
        }

        // comparision function : [](GoalEvent a, GoalEvent b){return a.time < b.time;} - compares a.time and b.time
        sort(events.begin(), events.end(), [](GoalEvent a, GoalEvent b){return a.time < b.time; });

        for (int j = 0; j < events.size(); j++){
            cout << events[j].time << "' " << events[j].playerName << "\n";
        }

        cout << "\n"<< t1.name << " " << goals1 << " - " << goals2 << " " << t2.name;
        cout << "\n";

        if (goals1 > goals2)cout << t1.name << " wins!\n";
        else if (goals2 > goals1)cout << t2.name << " wins!\n";
        else cout << "Match Draw!\n";
        cout << "\n===== FULL TIME =====\n";
    }
};

int main(){
    srand(time(0));
    vector<Team> quickMatchTeams;
    Player p1;
    p1.name = "MESSI";
    p1.shooting = 92;
    p1.passing = 91;
    p1.pace = 94;
    p1.dribbling = 95;
    p1.defending = 40;
    p1.physical = 65;

    Player p2;
    p2.name = "NEYMAR";
    p2.pace = 92;
    p2.shooting = 87;
    p2.dribbling = 94;
    p2.passing = 85;
    p2.defending = 40;
    p2.physical = 68;

    Player p3;
    p3.name = "SUAREZ";
    p3.shooting = 91;
    p3.pace = 87;
    p3.dribbling = 91;
    p3.passing = 83;
    p3.defending = 50;
    p3.physical = 85;

    Team t1; // creates a team of name t1 array which stores the players name
    t1.name = "BARCELONA";
    // cout << "\n" << t1.name << "\n";
    t1.players.push_back(p1);
    t1.players.push_back(p2);
    t1.players.push_back(p3);
    // t1.displayTeam();

    Player p4;
    p4.name = "RONALDO";
    p4.pace = 95;
    p4.shooting = 93;
    p4.dribbling = 94;
    p4.passing = 83;
    p4.defending = 37;
    p4.physical = 84;

    Player p5;
    p5.name = "BALE";
    p5.pace = 96;
    p5.shooting = 85;
    p5.dribbling = 90;
    p5.passing = 80;
    p5.defending = 57;
    p5.physical = 80;

    Player p6;
    p6.name = "BENZEMA";
    p6.pace = 83;
    p6.shooting = 84;
    p6.dribbling = 82;
    p6.passing = 75;
    p6.defending = 22;
    p6.physical = 74;

    Team t2;
    t2.name = "REAL MADRID";
    // cout << "\n" << t2.name << "\n";
    t2.players.push_back(p4);
    t2.players.push_back(p5);
    t2.players.push_back(p6);
    // t2.displayTeam();

    Player b1;
    b1.name = "RIBERY";
    b1.shooting = 87;
    b1.passing = 86;
    b1.pace = 92;
    b1.dribbling = 94;
    b1.defending = 45;
    b1.physical = 56;

    Player b2;
    b2.name = "ROBBEN";
    b2.shooting = 89;
    b2.passing = 84;
    b2.pace = 93;
    b2.dribbling = 93;
    b2.defending = 48;
    b2.physical = 60;

    Player b3;
    b3.name = "LEWANDOWSKI";
    b3.shooting = 94;
    b3.passing = 59;
    b3.pace = 80;
    b3.dribbling = 80;
    b3.defending = 51;
    b3.physical = 89;

    Team t3;
    t3.name = "BAYERN MUNICH";
    // cout << "\n"<< t3.name << "\n";
    t3.players.push_back(b1);
    t3.players.push_back(b2);
    t3.players.push_back(b3);
    // t3.displayTeam();

    Player a1;
    a1.name = "KAKA";
    a1.shooting = 86;
    a1.passing = 88;
    a1.pace = 91;
    a1.dribbling = 91;
    a1.defending = 38;
    a1.physical = 74;

    Player a2;
    a2.name = "INZAGHI";
    a2.shooting = 91;
    a2.passing = 68;
    a2.pace = 74;
    a2.dribbling = 78;
    a2.defending = 35;
    a2.physical = 70;

    Player a3;
    a3.name = "VAN BASTEN";
    a3.shooting = 94;
    a3.passing = 58;
    a3.pace = 90;
    a3.dribbling = 86;
    a3.defending = 52;
    a3.physical = 81;

    Team t4;
    t4.name = "AC MILAN";
    // cout << "\n"<< t4.name << "\n";
    t4.players.push_back(a1);
    t4.players.push_back(a2);
    t4.players.push_back(a3);
    // t4.displayTeam();

    quickMatchTeams.push_back(t1);
    quickMatchTeams.push_back(t2);
    quickMatchTeams.push_back(t3);
    quickMatchTeams.push_back(t4);

    int choice;
    cout << "\nWELCOME TO FOOTBALL MATCH SIMULATOR";
    cout << "\n";

    while (true){
        cout << "1. CAREER MODE\n";
        cout << "2. QUICK MATCH\n";
        cout << "3. EXIT\n\n";

        cout << "ENTER YOUR CHOICE : ";
        cin >> choice;
        system("clear");
        if (choice == 1){
        }

        else if (choice == 2){
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
        else if (choice == 3){
            cout << "THANKS FOR PLAYING !";
            return 0;
        }
        else{
            cout << "INVALID INPUT !\n";
        }
    }
    return 0;
}