#ifndef MODELS_H
#define MODELS_H

#include <iostream>
#include <string>
#include <vector>
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
  string nationality;
  string role;
  string position;
  int age;
  int shooting;
  int passing;
  int dribbling;
  int pace;
  int defending;
  int physical;
  int goalkeeping;

  int getAttack() const
  {
    return (shooting * 3 + dribbling * 3 + pace * 2 + passing * 2 + physical) / 11;
  }
  int getDefense() const
  {
    return (defending * 4 + physical * 3 + pace * 2) / 9;
  }
  int getMidfield() const
  {
    return (passing * 4 + dribbling * 3 + defending * 2 + physical) / 10;
  }
  int getGoalkeeping() const { return goalkeeping; }
};

class Team
{
public:
  string name;
  vector<Player> players;

  int getTeamAttack() const
  {
    int attackAvg{0};
    if (players.empty())
      return 0;
    int count{0};
    for (const Player &p : players)
    {
      if (p.role == "Attacker")
      {
        count++;
        attackAvg += p.getAttack();
      }
    }
    if (count == 0)
      return 0;
    return attackAvg / count;
  }

  int getTeamDefense() const
  {
    int defendAvg{0};
    if (players.empty())
      return 0;
    int count{0};
    for (const Player &p : players)
    {
      if (p.role == "Defender")
      {
        count++;
        defendAvg += p.getDefense();
      }
    }
    if (count == 0)
      return 0;
    return defendAvg / count;
  }

  int getTeamMidfield() const
  {
    int midfieldAvg{0};
    if (players.empty())
      return 0;
    int count{0};
    for (const Player &p : players)
    {
      if (p.role == "Midfielder")
      {
        count++;
        midfieldAvg += p.getMidfield();
      }
    }
    if (count == 0)
      return 0;
    return midfieldAvg / count;
  }

  int getTeamGoalkeeping() const
  {
    for (const Player &p : players)
    {
      if (p.position == "GK")
      {
        return p.getGoalkeeping();
      }
    }
    return 0;
  }

  void displayTeam() const
  {
    cout << "\n=====================================\n";
    cout << "TEAM : " << name << "\n";
    cout << "=====================================\n\n";

    for (const Player &p : players)
    {
      cout << p.name << " | " << p.position << " | ATK: " << p.getAttack() << " | DEF: " << p.getDefense() << " | MID: " << p.getMidfield();

      if (p.position == "GK")
      {
        cout << " | GK: " << p.getGoalkeeping();
      }

      cout << "\n";
    }

    cout << "\n-------------------------------------\n";
    cout << "TEAM ATTACK      : " << getTeamAttack() << "\n";
    cout << "TEAM DEFENSE     : " << getTeamDefense() << "\n";
    cout << "TEAM MIDFIELD    : " << getTeamMidfield() << "\n";
    cout << "TEAM GOALKEEPING : " << getTeamGoalkeeping() << "\n";
    cout << "-------------------------------------\n";
  }
};

class Standing
{
public:
  Team team;
  int points;
  int goalsFor;
  int goalsAgainst;
  int goalsDiff;
  int wins;
  int losses;
  int draws;
  Standing(const Team &t) : team(t)
  {
    points = 0;
    goalsFor = 0;
    goalsAgainst = 0;
    goalsDiff = 0;
    wins = 0;
    losses = 0;
    draws = 0;
  }
};

class Group
{
  public:
  string name;
  vector<Standing> standings;
};

#endif
