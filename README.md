# Football League Fixture Generator

## Project Overview
This project is a C++ console application that generates football match fixtures for a local league with 10 teams. Each team plays every other team twice (once at home and once away), adhering to the constraint that only two matches (four teams) are played on each weekend. The fixture details are displayed in the console and saved to a CSV file for easy reference.

## Table of Contents
- [Features](#features)
- [Installation](#installation)
- [How to Run](#how-to-run)
- [Input File Format](#input-file-format)
- [Output](#output)
- [Project Structure](#project-structure)
- [License](#license)
- [Notes](#notes)

## Features
- Reads team information from a CSV file.
- Generates fixtures where each team plays every other team home and away.
- Limits matches to two per weekend (four teams).
- Displays generated fixtures in the console.
- Exports the generated fixtures to a CSV file.
- Handles both local derbies (teams from the same town) and regular matches.

## Installation

### Prerequisites
- **C++ Compiler**: You will need a C++ compiler that supports C++11 or higher.
- **CMake** (optional but recommended if using an IDE like CLion).
- **IDE or Text Editor**: You can use any C++ IDE such as CLion, Visual Studio, or Code::Blocks.

### Steps
1. Clone the repository or download the project files.
    ```bash
    git clone https://github.com/OCHOLA-EDDYPHIL/fixture_generator.git
    ```
2. Ensure the `teams.csv` file is placed in the same directory as the executable or adjust the path in the `main.cpp` file if needed.

## How to Run
1. Compile the project using your preferred IDE or the command line:
    ```bash
    g++ -o fixture_generator main.cpp
    ```
2. Run the executable:
    ```bash
    ./main.exe
    ```
3. The program will display the list of teams and the generated fixtures in the console. It will also write the fixtures to a CSV file named `fixtures_output.csv`.

## Input File Format
The input file `teams.csv` contains the list of teams with their town and stadium information. Ensure the CSV file follows this format:
```csv
Team Name,Local Town,Team Stadium
Cklein Starts,Nairobi,Cklein Arena
Wolves FC,Nairobi,Wolves
Dolphins FC,Mombasa,Dolphins
Sea Horses FC,Mombasa,SHorses Arena
Sharks United,Kisumu,Sharks Field
Lake Basin FC,Kisumu,LBasin
Thika United,Thika,Thika Field
Mavuno Comrades FC,Thika,Vuno Grounds
Nakuru FC,Nakuru,Nakuru Field
Ostrich Associates,Nakuru,OAssociates
```

## Output
The fixtures will be displayed in the console with the format:
```yaml
| Weekend: [weekend number] | Match: [Home Team] vs [Away Team] at [Stadium], [Town] (Leg [1 or 2])
```
The program also exports the generated fixtures to a file called `fixtures_output.csv` with the following format:
```csv
Weekend,Home Team,Away Team,Town,Stadium,Leg
1,Cklein Starts,Dolphins FC,Nairobi,Cklein Arena,1
1,Dolphins FC,Cklein Starts,Mombasa,Dolphins,2
...
```

## Project Structure
```bash
.
├── Teams.csv             # Input file containing team data
├── LICENSE               # Project license file
├── CMakeLists.txt        # CMake configuration file
├── fixtures_output.csv   # Generated fixture output file
├── main.cpp              # C++ source code for generating fixtures
└── README.md             # Project README file
```

## License
## Notes
- Make sure to keep the `Teams.csv` file in the same directory as the compiled executable or provide the correct path in the code.
- Ensure that your CSV input format is correct to avoid any errors while reading team data.
- You can adjust the number of teams and format as needed, but the current project assumes a 10-team league.
