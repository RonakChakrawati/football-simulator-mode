#include "loader.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

vector<Team> loadTeams(string filename) {
    vector<Team> teams;
    ifstream file(filename);
    
    if (!file.is_open()) {
        cout << "ERROR: Could not open " << filename << endl;
        return teams;
    }

    string line;
    getline(file, line); 
    
    Team currentTeam;
    
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;
        
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        // trim whitespace
        for (string& t : tokens) {
            size_t start = t.find_first_not_of(" \t\r\n");
            size_t end = t.find_last_not_of(" \t\r\n");
            t = (start == string::npos) ? "" : t.substr(start, end - start + 1);
        }
        
        string teamName = tokens[0];
        
        if (currentTeam.name != teamName && !currentTeam.name.empty()) {
            teams.push_back(currentTeam);
            currentTeam = Team();
        }
        
        currentTeam.name = teamName;
        
        Player p;
        p.name = tokens[1];
        p.nationality = tokens[2];
        p.role = tokens[3];
        p.position = tokens[4];
        p.age = stoi(tokens[5]);
        p.shooting = stoi(tokens[6]);
        p.passing = stoi(tokens[7]);
        p.dribbling = stoi(tokens[8]);
        p.pace = stoi(tokens[9]);
        p.defending = stoi(tokens[10]);
        p.physical = stoi(tokens[11]);
        p.goalkeeping = stoi(tokens[12]);
        currentTeam.players.push_back(p);
    }
    
    if (!currentTeam.name.empty()) {
        teams.push_back(currentTeam);
    }
     
    file.close();
    return teams;
}