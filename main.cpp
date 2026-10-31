// project for football simulation

#include "wc_loader.h"
#include "loader.h"
#include "match.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
  srand(time(0));
  vector<Team> teams = loadTeams("clubs_teams.csv");
  int choice;
  cout << "\nWELCOME TO FOOTBALL MATCH SIMULATOR";
  cout << "\n";

  while (true)
  {
    cout << "1. CAREER MODE\n";
    cout << "2. QUICK MATCH\n";
    cout << "3. SIMULATION\n";
    cout << "4. WC 2026\n";
    cout << "5. EXIT\n\n";

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
      cout << "[3] MAN UNITED\n";
      cout << "[4] CHELSEA\n";
      cout << "[5] LIVERPOOL\n";
      cout << "[6] MAN CITY\n";
      cout << "[7] AC MILAN\n";
      cout << "[8] JUVENTUS\n";
      cout << "[9] INTER MILAN\n";
      cout << "[10] BAYERN MUNICH\n";
      cout << "[11] ARSENAL\n";
      cout << "[12] ATLETICO MADRID\n";
      cout << "[13] PSG\n";
      cout << "[14] DORTMUND\n";
      cout << "[15] LEVERKUSAN\n";
      cout << "[16] LYON\n\n";

      int selectTeam1, selectTeam2;
      cout << "ENTER TEAM 1 NUMBER : ";
      cin >> selectTeam1;
      a = teams[selectTeam1 - 1];
      cout << "\nENTER TEAM 2 NUMBER : ";
      cin >> selectTeam2;
      b = teams[selectTeam2 - 1];

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
      cout << "[3] MAN UNITED\n";
      cout << "[4] CHELSEA\n";
      cout << "[5] LIVERPOOL\n";
      cout << "[6] MAN CITY\n";
      cout << "[7] AC MILAN\n";
      cout << "[8] JUVENTUS\n";
      cout << "[9] INTER MILAN\n";
      cout << "[10] BAYERN MUNICH\n";
      cout << "[11] ARSENAL\n";
      cout << "[12] ATLETICO MADRID\n";
      cout << "[13] PSG\n";
      cout << "[14] DORTMUND\n";
      cout << "[15] LEVERKUSAN\n";
      cout << "[16] LYON\n\n";

      int team1Choice, team2Choice;
      int simulations;
      cout << "ENTER TEAM 1 : ";
      cin >> team1Choice;
      cout << "ENTER TEAM 2 : ";
      cin >> team2Choice;
      cout << "NUMBER OF SIMULATIONS : ";
      cin >> simulations;
      Team sim1 = teams[team1Choice - 1];
      Team sim2 = teams[team2Choice - 1];
      int wins1 = 0;
      int wins2 = 0;
      int draws = 0;
      Match autoSim;
      for (int i = 1; i <= simulations; i++)
      {
        cout << "\n========== MATCH " << i << " ==========\n";
        autoSim.score(sim1, sim2);
        if (autoSim.winner == 1)
          wins1++;
        else if (autoSim.winner == 2)
          wins2++;
        else
          draws++;
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
      system("clear");
      cout << "=====================================\n";
      cout << "         FIFA WORLD CUP 2026\n";
      cout << "=====================================\n\n";

      vector<Team> wcTeams = loadTeams("wc_nations.csv");
      vector<Group> groups(12);
      groups[0].name = "GROUP A";
      groups[1].name = "GROUP B";
      groups[2].name = "GROUP C";
      groups[3].name = "GROUP D";
      groups[4].name = "GROUP E";
      groups[5].name = "GROUP F";
      groups[6].name = "GROUP G";
      groups[7].name = "GROUP H";
      groups[8].name = "GROUP I";
      groups[9].name = "GROUP J";
      groups[10].name = "GROUP K";
      groups[11].name = "GROUP L";

      // GROUP A
      groups[0].standings.push_back(Standing(wcTeams[21])); 
      groups[0].standings.push_back(Standing(wcTeams[26])); 
      groups[0].standings.push_back(Standing(wcTeams[41]));
      groups[0].standings.push_back(Standing(wcTeams[35])); 

      // GROUP B
      groups[1].standings.push_back(Standing(wcTeams[22])); 
      groups[1].standings.push_back(Standing(wcTeams[33])); 
      groups[1].standings.push_back(Standing(wcTeams[29]));
      groups[1].standings.push_back(Standing(wcTeams[34])); 

      // GROUP C
      groups[2].standings.push_back(Standing(wcTeams[2]));
      groups[2].standings.push_back(Standing(wcTeams[12]));
      groups[2].standings.push_back(Standing(wcTeams[44])); 
      groups[2].standings.push_back(Standing(wcTeams[41]));

      // GROUP D
      groups[3].standings.push_back(Standing(wcTeams[20]));
      groups[3].standings.push_back(Standing(wcTeams[46]));
      groups[3].standings.push_back(Standing(wcTeams[30]));
      groups[3].standings.push_back(Standing(wcTeams[38]));

      // GROUP E
      groups[4].standings.push_back(Standing(wcTeams[6]));
      groups[4].standings.push_back(Standing(wcTeams[15]));
      groups[4].standings.push_back(Standing(wcTeams[43]));
      groups[4].standings.push_back(Standing(wcTeams[17]));

      // GROUP F
      groups[5].standings.push_back(Standing(wcTeams[8])); 
      groups[5].standings.push_back(Standing(wcTeams[25]));
      groups[5].standings.push_back(Standing(wcTeams[37]));
      groups[5].standings.push_back(Standing(wcTeams[19]));

      // GROUP G
      groups[6].standings.push_back(Standing(wcTeams[9]));
      groups[6].standings.push_back(Standing(wcTeams[17]));
      groups[6].standings.push_back(Standing(wcTeams[27]));
      groups[6].standings.push_back(Standing(wcTeams[31]));

      // GROUP H
      groups[7].standings.push_back(Standing(wcTeams[3]));
      groups[7].standings.push_back(Standing(wcTeams[28]));
      groups[7].standings.push_back(Standing(wcTeams[10]));
      groups[7].standings.push_back(Standing(wcTeams[13]));

      // GROUP I
      groups[8].standings.push_back(Standing(wcTeams[1]));
      groups[8].standings.push_back(Standing(wcTeams[13]));
      groups[8].standings.push_back(Standing(wcTeams[36]));
      groups[8].standings.push_back(Standing(wcTeams[18]));

      // GROUP J
      groups[9].standings.push_back(Standing(wcTeams[0]));
      groups[9].standings.push_back(Standing(wcTeams[16]));
      groups[9].standings.push_back(Standing(wcTeams[39]));
      groups[9].standings.push_back(Standing(wcTeams[47]));

      // GROUP K
      groups[10].standings.push_back(Standing(wcTeams[4]));
      groups[10].standings.push_back(Standing(wcTeams[42]));
      groups[10].standings.push_back(Standing(wcTeams[24]));
      groups[10].standings.push_back(Standing(wcTeams[32]));

      // GROUP L
      groups[11].standings.push_back(Standing(wcTeams[5])); 
      groups[11].standings.push_back(Standing(wcTeams[11]));
      groups[11].standings.push_back(Standing(wcTeams[23])); 
      groups[11].standings.push_back(Standing(wcTeams[45])); 
      
    }

    else if (choice == 5)
    {
      cout << "THANKS FOR PLAYING !" << endl;
      return 0;
    }
    else
    {
      cout << "INVALID INPUT !\n";
    }
  }
  return 0;
}