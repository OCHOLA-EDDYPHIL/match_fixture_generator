#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Struct to store team information
struct Team {
    string name;
    string town;
    string stadium;
};

// Function to read team data from CSV file
vector<Team> readCSV(const string& filename) {
    vector<Team> teams;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return teams;
    }

    // Skip header line
    string line;
    getline(file, line);

    // Read each line of the CSV file
    while (getline(file, line)) {
        stringstream ss(line);
        string name, town, stadium;

        getline(ss, name, ',');
        getline(ss, town, ',');
        getline(ss, stadium, ',');

        teams.push_back({name, town, stadium});
    }

    return teams;
}

// Function to write fixtures to a CSV file
void writeFixturesToCSV(const vector<Team>& teams, const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    file << "Matchday,Team 1,Team 2,Location 1,Location 2,Stadium 1,Stadium 2\n";

    int numTeams = teams.size();
    if (numTeams % 2 != 0) {
        cerr << "Number of teams should be even for balanced fixtures." << endl;
        return;
    }

    for (int i = 0; i < numTeams; i += 2) {
        file << (i / 2 + 1) << ","
             << teams[i].name << ","
             << teams[i + 1].name << ","
             << teams[i].town << ","
             << teams[i + 1].town << ","
             << teams[i].stadium << ","
             << teams[i + 1].stadium << "\n";
    }

    file.close();
}

// Main function
int main() {
    string inputFilename = "C:\\Users\\Ocholla\\Desktop\\proj\\Teams.csv"; // Update the path
    string outputFilename = "C:\\Users\\Ocholla\\Desktop\\proj\\fixtures.csv";

    vector<Team> teams = readCSV(inputFilename);

    if (!teams.empty()) {
        writeFixturesToCSV(teams, outputFilename);
        cout << "Fixtures have been written to " << outputFilename << endl;
    } else {
        cerr << "No teams found or error reading the file." << endl;
    }

    return 0;
}