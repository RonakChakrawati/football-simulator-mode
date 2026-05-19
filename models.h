#ifndef MODELS_H
#define MODELS_H

#include <iostream>
#include <string>
#include <vector>

class GoalEvent {
public:
  int time;
  std::string playerName;
};

class Player {
public:
  std::string name;
  std::string nationality;

  std::string role;
  std::string position;

  int age;

  int shooting;
  int passing;
  int dribbling;
  int pace;

  int defending;
  int physical;

  int goalkeeping;

  int getAttack() const {
    return (shooting * 4 + dribbling * 3 + pace * 2 + passing * 2 + physical) /
           12;
  }

  int getDefense() const {
    return (defending * 4 + physical * 3 + pace * 2) / 9;
  }

  int getMidfield() const {
    return (passing * 4 + dribbling * 3 + defending * 2 + physical) / 10;
  }

  int getGoalkeeping() const { return goalkeeping; }
};

class Team {
public:
  std::string name;
  std::vector<Player> players;

  int getTeamAttack() const {
    int attackAvg{0};
    if (players.empty())
      return 0;

    for (const Player &p : players) {
      attackAvg += p.getAttack();
    }

    return attackAvg / (int)players.size();
  }

  int getTeamDefense() const {
    int defendAvg{0};

    if (players.empty())
      return 0;

    for (const Player &p : players) {
      defendAvg += p.getDefense();
    }

    return defendAvg / (int)players.size();
  }

  int getTeamMidfield() const {
    int midfieldAvg{0};

    if (players.empty())
      return 0;

    for (const Player &p : players) {
      midfieldAvg += p.getMidfield();
    }

    return midfieldAvg / (int)players.size();
  }

  int getTeamGoalkeeping() const {
    for (const Player &p : players) {
      if (p.position == "GK") {
        return p.getGoalkeeping();
      }
    }

    return 0;
  }

  void displayTeam() const {
    std::cout << "\n=====================================\n";
    std::cout << "TEAM : " << name << "\n";
    std::cout << "=====================================\n\n";

    for (const Player &p : players) {
      std::cout << p.name << " | " << p.position << " | ATK: " << p.getAttack()
                << " | DEF: " << p.getDefense()
                << " | MID: " << p.getMidfield();

      if (p.position == "GK") {
        std::cout << " | GK: " << p.getGoalkeeping();
      }

      std::cout << "\n";
    }

    std::cout << "\n-------------------------------------\n";
    std::cout << "TEAM ATTACK      : " << getTeamAttack() << "\n";
    std::cout << "TEAM DEFENSE     : " << getTeamDefense() << "\n";
    std::cout << "TEAM MIDFIELD    : " << getTeamMidfield() << "\n";
    std::cout << "TEAM GOALKEEPING : " << getTeamGoalkeeping() << "\n";
    std::cout << "-------------------------------------\n";
  }
};

#endif