#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct Team {
    string name;
    string town;
    string stadium;

    Team(const string &name, const string &town, const string &stadium) : name(name), town(town), stadium(stadium) {}
};

struct Match {
    string homeTeam;
    string awayTeam;
    string localTown;
    string stadium;
    int leg;
    int weekend;
};

// Read teams from the CSV
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

// Generate the fixtures
void generateFixture(const vector<Team> &teams, vector<Match> &fixtures) {
    int weekend = 1;
    int matchCount = 0;  // Counter to ensure 2 matches per weekend
    vector<Match> rivalry;
    vector<Match> nonDerby;
    size_t numTeams = teams.size();

    for (size_t a = 0; a < numTeams; ++a) {
        for (size_t b = a + 1; b < numTeams; ++b) {
            if (teams[a].town != teams[b].town) {
                // Non-derby fixtures
                nonDerby.push_back({teams[a].name, teams[b].name, teams[a].town, teams[a].stadium, 1, weekend});
                nonDerby.push_back({teams[b].name, teams[a].name, teams[b].town, teams[b].stadium, 2, weekend});
            } else {
                // Derbies
                rivalry.push_back({teams[a].name, teams[b].name, teams[a].town, teams[a].stadium, 1, weekend});
                rivalry.push_back({teams[b].name, teams[a].name, teams[b].town, teams[b].stadium, 2, weekend});
            }
        }
    }

    // Schedule non-derby matches first (2 matches per weekend)
    for (size_t i = 0; i < nonDerby.size(); i += 2) {
        // Schedule two matches per weekend
        if (matchCount == 2) {
            weekend++;
            matchCount = 0;
        }
        fixtures.push_back(nonDerby[i]);
        matchCount++;

        if (i + 1 < nonDerby.size()) {
            fixtures.push_back(nonDerby[i + 1]);
            matchCount++;
        }
    }

    // Now schedule the local derbies
    matchCount = 0;  // Reset the counter for the derbies
    for (auto &rivals: rivalry) {
        if (matchCount == 2) {
            weekend++;
            matchCount = 0;
        }
        rivals.weekend = weekend;
        fixtures.push_back(rivals);
        matchCount++;
    }

    // Handling odd number of teams by adding a bye
    if (numTeams % 2 != 0) {
        fixtures.push_back({"N/A", teams.back().name, "N/A", "N/A", 0, weekend++});
    }
}

// Output fixtures to a CSV file
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

// Display fixtures
void displayFixtures(const vector<Match> &fixtures) {
    for (const auto &fixture: fixtures) {
        cout << "| Weekend: " << fixture.weekend << " | Match: " << fixture.homeTeam << " vs " << fixture.awayTeam
             << " at " << fixture.stadium << ", " << fixture.localTown << " (Leg " << fixture.leg << ")" << endl;
    }
}

int main() {
    string filename = "C:\\Users\\Ocholla\\Desktop\\proj\\cmake-build-debug\\Teams.csv";  // Input CSV file

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
    writeFixturesToCSV(fixtures, "../fixtures_output.csv");

    return 0;
}
