#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct Team {
    string name;     ///< Name of the team
    string town;     ///< Town of the team
    string stadium;  ///< Stadium of the team

    Team(const string &name, const string &town, const string &stadium) : name(name), town(town), stadium(stadium) {}
};

struct Match {
    string homeTeam;  ///< Home team name
    string awayTeam;  ///< Away team name
    string localTown; ///< Town where the match is played
    string stadium;   ///< Stadium where the match is played
    int leg;          ///< Leg of the match (1 or 2)
    int weekend;      ///< Weekend number when the match is played
};

vector<Team> readCSV(const string &filename) {
    vector<Team> teams;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "File not found" << endl;
        return teams;
    }

    string line;
    getline(file, line);  // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        string name, town, stadium;

        getline(ss, name, ',');
        getline(ss, town, ',');
        getline(ss, stadium, ',');
        if (name.empty() || town.empty() || stadium.empty()) {
            cout << "Unavailable info: " << line << endl;
            continue;
        }
        teams.push_back({name, town, stadium});
    }

    file.close();
    return teams;
}

void generateFixture(const vector<Team> &teams, vector<Match> &fixtures) {
    int weekend = 1;        // To track which weekend the match is on
    int matchCount = 0;      // Track matches per weekend to ensure we only have 2 matches per weekend
    size_t numTeams = teams.size();

    // Ensure each team plays every other team exactly twice (home and away)
    for (size_t a = 0; a < numTeams; ++a) {
        for (size_t b = a + 1; b < numTeams; ++b) {
            // First leg: team[a] plays at home against team[b]
            fixtures.push_back({teams[a].name, teams[b].name, teams[a].town, teams[a].stadium, 1, weekend});
            matchCount++;

            // Increment weekend after 2 matches
            if (matchCount == 2) {
                weekend++;
                matchCount = 0;  // Reset for next weekend
            }

            // Second leg: team[b] plays at home against team[a]
            fixtures.push_back({teams[b].name, teams[a].name, teams[b].town, teams[b].stadium, 2, weekend});
            matchCount++;

            // Increment weekend after 2 matches
            if (matchCount == 2) {
                weekend++;
                matchCount = 0;
            }
        }
    }

    // At this point, all 45 matches (home and away for 10 teams) should have been generated
}

void writeFixturesToCSV(const vector<Match> &fixtures, const string &filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "Unable to open file: " << filename << endl;
        return;
    }

    outFile << "Weekend,Home Team,Away Team,Town,Stadium,Leg\n";
    for (const auto &fixture: fixtures) {
        outFile << fixture.weekend << ","
                << fixture.homeTeam << ","
                << fixture.awayTeam << ","
                << fixture.localTown << ","
                << fixture.stadium << ","
                << fixture.leg << "\n";
    }

    outFile.close();
    cout << "Fixtures have been written to " << filename << endl;
}

void displayFixtures(const vector<Match> &fixtures) {
    for (const auto &fixture: fixtures) {
        cout << "| Weekend: " << fixture.weekend << " | Match: " << fixture.homeTeam << " vs " << fixture.awayTeam
             << " at " << fixture.stadium << ", " << fixture.localTown << " (Leg " << fixture.leg << ")" << endl;
    }
}

int main() {
    string filename = "Teams.csv";  // Input CSV file

    // Read teams from CSV
    vector<Team> teams = readCSV(filename);

    // Display teams
    for (const auto &team: teams) {
        cout << "Team: " << team.name << ", Town: " << team.town << ", Stadium: " << team.stadium << endl;
    }

    // Generate fixtures
    vector<Match> fixtures;
    generateFixture(teams, fixtures);

    // Display fixtures
    displayFixtures(fixtures);

    // Write fixtures to a CSV file
    writeFixturesToCSV(fixtures, "fixtures_output.csv");

    return 0;
}
