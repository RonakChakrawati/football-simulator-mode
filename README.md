# Football Simulator (ONGOING)

A console-based football match simulator built in C++ using Object-Oriented Programming and statistical match calculations.

This project simulates football matches between teams using player attributes like shooting, passing, pace, defending, and physicality to generate realistic match outcomes, goal events, and scorelines.

Tiny football engine. Surprisingly solid logic underneath. Humans looked at twenty-two people chasing a ball and thought, “This needs algorithms.” Beautiful species honestly.

---

## Overview

The simulator calculates:

- Team attack and defense ratings
- Match advantages
- Randomized goal generation
- Goal scorer events with timestamps
- Final match results and winners

The project combines:
- OOP concepts
- Data modeling
- Simulation logic
- Random event generation
- Algorithmic thinking

---

## Features

### Match Simulation System

| Feature | Description |
|---|---|
| Team Creation | Create teams with custom players |
| Player Statistics | FIFA-style attributes |
| Attack & Defense Calculation | Dynamic team ratings |
| Goal Event System | Chronological goal timeline |
| Randomized Matches | Different outcomes every run |
| Match Winner Detection | Determines victory or draw |
| Goal Scorer Tracking | Random player goal assignment |

---

### Football Logic

The simulator uses player stats to calculate:

- Team attack power
- Team defensive strength
- Match advantage
- Estimated goal count
- Goal events sorted by time

Not fully realistic yet, but honestly neither is Chelsea spending hundreds of millions to finish mid-table. Simulation remains faithful to football traditions.

---

## Concepts Practiced

This project strengthens understanding of:

- Object-Oriented Programming
- Classes & Objects
- Vectors
- Sorting Algorithms
- Random Number Generation
- Aggregation & Composition
- Data Modeling
- Simulation Design
- Function Decomposition
- Chronological Event Systems

---

## Tech Stack

- **Language:** C++
- **Libraries Used:**
  - `iostream`
  - `vector`
  - `string`
  - `algorithm`
  - `cstdlib`
  - `ctime`

- **Compiler:** g++
- **Platform:** Terminal / Command Line

---

## System Architecture

```text
Player Stats
     ↓
Team Rating Calculation
     ↓
Attack vs Defense Comparison
     ↓
Goal Generation Logic
     ↓
Goal Event Creation
     ↓
Chronological Sorting
     ↓
Final Match Output
```

---

## Project Structure

```text
football-simulator/
├── footballSimulator.cpp
└── README.md
```

---

## Core Classes

### GoalEvent

Stores goal information.

```cpp
class GoalEvent {
    int time;
    string playerName;
};
```

---

### Player

Represents an individual football player with FIFA-style stats.

```cpp
class Player {
    string name;

    int shooting;
    int passing;
    int pace;
    int dribbling;
    int defending;
    int physical;

    int getAttack();
    int getDefense();
};
```

---

### Team

Stores team information and calculates overall ratings.

```cpp
class Team {
    string name;
    vector<Player> players;

    int generateTeamAttack();
    int generateTeamDefend();
    void displayTeam();
};
```

---

### Match

Handles complete match simulation.

```cpp
class Match {
    void score(Team&, Team&);
};
```

---

## Mathematical Model

### Player Attack Rating

$begin:math:display$
Attack \= \\frac\{shooting \+ passing \+ pace \+ dribbling\}\{4\}
$end:math:display$

---

### Player Defense Rating

$begin:math:display$
Defense \= \\frac\{defending \+ physical\}\{2\}
$end:math:display$

---

### Team Attack Calculation

$begin:math:display$
TeamAttack \= \\frac\{\\sum IndividualAttack\}\{Number\\ of\\ Players\}
$end:math:display$

---

### Match Advantage Formula

$begin:math:display$
Advantage \= max\(0\, TeamAttack \- OpponentDefense\)
$end:math:display$

---

### Goal Generation Formula

$begin:math:display$
Goals \= \\frac\{Advantage\}\{10\} \+ random\(0\,2\)
$end:math:display$

---

## Match Simulation Algorithm

```text
1. Calculate team attack ratings
2. Calculate team defense ratings
3. Compare attack vs defense
4. Generate advantages
5. Calculate possible goals
6. Generate random goal events
7. Assign random scorers
8. Sort goals chronologically
9. Display final score and winner
```

Simple algorithm. Effective enough for a first simulation engine.  
Most beginners never even reach this level because they spend three months watching “Top 10 Projects To Impress Recruiters” instead of actually building things.

---

## How to Run

### 1. Compile the Program

```bash
g++ footballSimulator.cpp -o footballSimulator
```

### 2. Run the Executable

#### Linux / macOS

```bash
./footballSimulator
```

#### Windows

```bash
footballSimulator.exe
```

---

## Sample Output

```text
BARCELONA
MESSI | Attack: 93 | Defense: 52
NEYMAR | Attack: 89 | Defense: 54
SUAREZ | Attack: 88 | Defense: 67

REAL MADRID
RONALDO | Attack: 91 | Defense: 60
BALE | Attack: 87 | Defense: 68
BENZEMA | Attack: 81 | Defense: 48

===== MATCH START =====

BARCELONA VS REAL MADRID

23' MESSI
56' SUAREZ
71' RONALDO

BARCELONA 2 - 1 REAL MADRID

BARCELONA wins!

===== FULL TIME =====
```

---

## Time Complexity Analysis

| Operation | Complexity |
|---|---|
| Team Rating Calculation | O(n) |
| Goal Event Generation | O(g) |
| Event Sorting | O(g log g) |
| Match Simulation | O(n + g log g) |

Where:
- `n` = number of players
- `g` = total goals

---

## Current Limitations

| Limitation | Description |
|---|---|
| Hardcoded Teams | No user-created teams |
| No Goalkeeper Logic | GK stats not implemented |
| No Positions | All players weighted equally |
| No League System | Single match only |
| No Persistence | Data resets every run |
| Basic Simulation | No tactics or formations |

Completely normal for Version 1.  
People forget even FIFA started somewhere before becoming a yearly copy-paste economic experiment.

---

## Future Improvements

Planned upgrades for future versions:

- Custom team creation
- Player positions (GK, DEF, MID, FWD)
- Formation systems
- Match statistics
- League & tournament modes
- Save/load functionality
- Transfer market system
- AI tactics engine
- Injury system
- Commentary engine
- GUI version
- Multiplayer simulation

---

## What I Learned

While building this project, I practiced:

- Designing larger-scale C++ projects
- Structuring multiple interacting classes
- Building simulation systems
- Managing vectors and dynamic data
- Using sorting with lambda functions
- Modeling real-world systems mathematically
- Improving program architecture

This project is genuinely valuable for growth because it moves beyond “toy problems” into actual system thinking.  
That transition matters. A lot.

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
