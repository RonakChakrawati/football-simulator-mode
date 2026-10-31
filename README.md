# Football Simulator (ONGOING)

A console-based football match simulator written in C++.

The project loads real squads from CSV files and simulates matches using player attributes such as shooting, passing, dribbling, pace, defending, physicality, and goalkeeping. It supports quick matches, repeated match simulations, and an in-progress FIFA World Cup 2026 mode.

Tiny football engine. Surprisingly solid logic underneath. Humans looked at twenty-two people chasing a ball and thought, "This needs algorithms." Beautiful species honestly.

---

## Overview

The simulator currently provides:

- A menu-driven console interface
- 16 classic club teams loaded from `clubs_teams.csv`
- 48 national teams loaded from `wc_nations.csv`
- Weighted attacker and defender selection based on player ratings
- Chance creation driven by team attack, midfield, and defense
- Randomized goal events with scorer names and match minutes
- Automatic winner detection and match summaries
- Batch simulation mode that counts wins, losses, and draws
- A World Cup 2026 group-stage setup (work in progress)

The project combines:

- Object-oriented programming
- CSV data loading and parsing
- Data modeling
- Simulation logic
- Random event generation
- Algorithmic thinking

---

## Features

| Feature | Description |
|---|---|
| Quick Match | Choose any two of the 16 loaded clubs and play a single match |
| Simulation Mode | Play the same fixture N times and tally wins and draws |
| WC 2026 Mode | Builds 12 groups of four from the 48-nation dataset |
| Career Mode | Menu placeholder, not implemented yet |
| CSV Data Loading | Squads and attributes are read from flat CSV files |
| Player Statistics | FIFA-style attributes on a 0–100 scale |
| Team Ratings | Separate attack, midfield, defense, and goalkeeping ratings |
| Goal Events | Chronological goal timeline with scorer and minute |
| Randomized Matches | Different scorelines and scorers every run |
| Winner Detection | Identifies the winning team or a draw |

### Current Menu

```text
1. CAREER MODE
2. QUICK MATCH
3. SIMULATION
4. WC 2026
5. EXIT
```

- **Career Mode** is currently a no-op placeholder.
- **Quick Match** loads teams by index from memory.
- **Simulation** runs the requested number of matches and prints aggregate results.
- **WC 2026** assigns the 48 nations to 12 groups. Fixtures and standings display are not implemented yet.

---

## Tech Stack

- **Language:** C++
- **Standard:** C++17
- **Compiler:** g++
- **Platform:** macOS / Linux terminal
- **Libraries:**
  - `iostream`
  - `fstream`
  - `sstream`
  - `vector`
  - `string`
  - `algorithm`
  - `cstdlib`
  - `ctime`

The program calls `system("clear")`, which is specific to Unix-like terminals. Windows support would require changing this to `system("cls")`.

---

## Project Structure

```text
football-simulator/
├── main.cpp          # Entry point and menu-driven game loop
├── models.h          # Player, Team, GoalEvent, Standing, Group classes
├── loader.h          # CSV loader declaration
├── loader.cpp        # CSV parsing and Team construction
├── match.h           # Match class declaration
├── match.cpp         # Match simulation engine
├── data.h            # Header for the legacy dataset (currently includes models.h only)
├── data.cpp          # 16 hardcoded classic teams (not linked by the main build)
├── wc_loader.h       # Empty placeholder for a future World Cup loader
├── clubs_teams.csv   # Club squads: 16 teams, 11 players each
├── wc_nations.csv    # National squads: 48 teams, 11 players each
├── football          # Compiled executable (generated)
└── README.md
```

`data.cpp` and `data.h` contain an older, hardcoded club dataset. The current `main.cpp` does not call `createTeams()` and instead uses `loadTeams()` with the CSV files.

---

## Core Classes

### Player

Represents an individual footballer.

```cpp
class Player {
public:
    string name;
    string nationality;
    string role;        // Goalkeeper, Defender, Midfielder, Attacker
    string position;    // GK, CB, RB, LB, CDM, CM, CAM, RW, ST, LW, ...
    int age;

    int shooting;
    int passing;
    int dribbling;
    int pace;
    int defending;
    int physical;
    int goalkeeping;

    int getAttack() const;
    int getDefense() const;
    int getMidfield() const;
    int getGoalkeeping() const;
};
```

### Team

Holds a squad and computes team-level ratings by role.

```cpp
class Team {
public:
    string name;
    vector<Player> players;

    int getTeamAttack() const;      // average attack of players with role "Attacker"
    int getTeamDefense() const;     // average defense of players with role "Defender"
    int getTeamMidfield() const;    // average midfield of players with role "Midfielder"
    int getTeamGoalkeeping() const; // goalkeeping of the first player with position "GK"
    void displayTeam() const;
};
```

### GoalEvent

Stores one goal.

```cpp
class GoalEvent {
public:
    int time;          // 1–90
    string playerName;
};
```

### Match

Runs a single match and stores its result.

```cpp
class Match {
public:
    int homeGoals{0};
    int awayGoals{0};
    int winner{0};     // 0 = draw, 1 = t1 wins, 2 = t2 wins

    void score(const Team& t1, const Team& t2);
};
```

### Standing and Group

Used by the unfinished World Cup mode.

```cpp
class Standing {
public:
    Team team;
    int points;
    int goalsFor;
    int goalsAgainst;
    int goalsDiff;
    int wins;
    int losses;
    int draws;
};

class Group {
public:
    string name;
    vector<Standing> standings;
    void displayTable() const;   // currently empty
};
```

---

## Mathematical Model

### Player Ratings

```text
Attack   = (shooting*4 + dribbling*3 + pace*2 + passing*2 + physical) / 12
Defense  = (defending*4 + physical*3 + pace*2) / 9
Midfield = (passing*4 + dribbling*3 + defending*2 + physical) / 10
```

Goalkeeping is used directly from the player's `goalkeeping` attribute.

### Team Ratings

Each team rating is the average of the relevant player rating for that role:

```text
TeamAttack   = average(getAttack())   for role == "Attacker"
TeamDefense  = average(getDefense())  for role == "Defender"
TeamMidfield = average(getMidfield()) for role == "Midfielder"
TeamGK       = goalkeeping            for the player at position "GK"
```

### Match Advantage

```text
Advantage(t1) = max(0, (t1.TeamAttack*3 + t1.TeamMidfield*2)
                       - (t2.TeamDefense*2 + t2.TeamMidfield/2))
```

The away team's advantage is calculated the same way with the teams swapped.

### Chance Creation

```text
Chances = (Advantage / 18) + 1 + random(0..2)
```

A larger advantage produces more attacking chances.

### Goal Probability

For every chance, the simulator picks one attacker and one defender using weighted random selection. It then computes:

```text
P(goal) = (attacker.Attack + team.Midfield)
          / (opponent.Midfield + defender.Defense + opponent.GK
             + attacker.Attack + team.Midfield)
```

The chance succeeds when:

```text
random(0..99) < P(goal) * 20
```

This scaling keeps scorelines in a plausible football range while remaining highly variable.

---

## Match Simulation Algorithm

```text
1. Reset home goals, away goals, and winner.
2. Calculate each team's attack advantage.
3. Convert each advantage into a number of chances.
4. For each chance:
   a. Pick a weighted-random attacker from the attacking team.
   b. Pick a weighted-random defender from the defending team.
   c. Calculate the scoring probability.
   d. Roll a random number and record a goal if successful.
5. Assign a random minute (1–90) to every goal.
6. Sort all goals chronologically.
7. Display the goal timeline, final score, and winner.
```

---

## Data Files

### `clubs_teams.csv`

Contains 16 club squads with 11 players each:

```text
BARCELONA, REAL MADRID, MANCHESTER UNITED, CHELSEA,
LIVERPOOL, MANCHESTER CITY, AC MILAN, JUVENTUS,
INTER MILAN, BAYERN MUNICH, ARSENAL, ATLETICO MADRID,
PSG, DORTMUND, LEVERKUSEN, LYON
```

### `wc_nations.csv`

Contains 48 national squads with 11 players each, used by the WC 2026 mode.

### CSV Format

The first line is skipped as a header. Every following line is one player:

```csv
TEAM, NAME, NATIONALITY, ROLE, POSITION, AGE, SHOOTING, PASSING, DRIBBLING, PACE, DEFENDING, PHYSICAL, GOALKEEPING
```

The loader groups consecutive rows that share the same team name into a single `Team`. Team names must therefore stay grouped together in the file.

---

## How to Run

### 1. Compile

Run from the project directory:

```bash
g++ -std=c++17 -Wall -Wextra -g main.cpp loader.cpp match.cpp -o football
```

`data.cpp` is not required by the current entry point.

### 2. Run

```bash
./football
```

The program reads `clubs_teams.csv` and `wc_nations.csv` from the current working directory, so both files must be present when the executable runs.

---

## Sample Output

```text
===== MATCH START =====
BARCELONA VS REAL MADRID

Goal Scorers:
  23' LIONEL MESSI
  56' DAVID VILLA
  71' CRISTIANO RONALDO

BARCELONA  2 - 1  REAL MADRID
BARCELONA wins!
===== FULL TIME =====
```

Simulation mode finishes with an aggregate summary:

```text
=====================================
         FINAL RESULTS
=====================================
BARCELONA Wins : 7
REAL MADRID Wins : 2
Draws : 1
```

---

## Time Complexity Analysis

Let `n` be the number of players, `c` the total chances, and `g` the number of goals.

| Operation | Complexity |
|---|---|
| CSV Loading | O(n) |
| Team Rating Calculation | O(n) |
| Chance Generation | O(1) |
| Attacker / Defender Selection | O(n) per chance |
| Match Simulation | O(c · n) |
| Goal Sorting | O(g log g) |
| Overall Match | O(c · n + g log g) |

---

## Current Limitations

| Limitation | Description |
|---|---|
| Career Mode | Not implemented; selecting it returns to the menu |
| World Cup Mode | Groups are created, but fixtures, tables, and knockouts are missing |
| No Persistence | Results reset every run; nothing is saved |
| Fixed Squad Shape | Match logic assumes at least 11 players and indexes positions 0–10 |
| No Tactics | No formations, substitutions, injuries, or cards |
| No Season System | No league table or multi-match progression |
| Basic Match Engine | Chances depend on ratings and randomness only |
| Unix-Only Screen Clearing | Uses `system("clear")` |
| Unused Legacy Data | `data.cpp` is not part of the current build |

Completely normal for Version 1. People forget even FIFA started somewhere before becoming a yearly copy-paste economic experiment.

---

## Future Improvements

Planned upgrades:

- Finish World Cup 2026 group fixtures, tables, and knockout rounds
- Implement Career Mode
- Add a proper standings calculator and `Group::displayTable()`
- Validate CSV input and handle malformed rows
- Remove hardcoded player indexing in the match engine
- Add player positions and formation systems
- Track possession, shots, and other match statistics
- Add league and tournament modes
- Add save/load functionality
- Add injuries, cards, and substitutions
- Add a commentary engine
- Add a GUI or web front end
- Add unit tests for ratings and simulation behavior

---

## What I Learned

While building this project, I practiced:

- Designing a multi-file C++ project
- Structuring interacting classes
- Parsing structured data from CSV files
- Building a simulation engine
- Using weighted random selection
- Sorting events with lambda functions
- Modeling real-world systems mathematically
- Iterating from a tiny prototype toward a larger application

This project is valuable for growth because it moves beyond toy problems into actual system thinking. That transition matters. A lot.

---

## Author

**Ronak Chakrawati**

B.Tech student exploring:

- C++
- DSA
- Software Development
- Simulation Systems
- AI & Cloud

Building systems one bug at a time.

---

## License

This project is open source and available for educational purposes.
