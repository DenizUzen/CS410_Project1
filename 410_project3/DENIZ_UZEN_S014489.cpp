#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Data
{
public:
    int inputAlphVarNum;
    string inputAlph;
    int tapeAlphVarNum;
    string tapeAlph;
    char blank;
    int numStates;
    string allStates;
    string startState;
    string acceptState;
    string rejectState;
    vector<string> states;
    string detectedStr;
};

string simulateTuringMachine(string input, Data machine)
{

    char tape[input.length() + 2];

    for (int i = 1; i < input.length() + 1; i++)
    {
        tape[i] = input[i];
    }
    tape[0] = machine.blank;
    tape[input.length() + 1] = machine.blank;

    string currentState = machine.startState;

    vector<string> visitedStates;
    visitedStates.push_back("ROUT: ");
    int head = 1;

    while (currentState != machine.acceptState && currentState != machine.rejectState)
    {

        visitedStates.push_back(currentState);

        for (auto i = machine.states.begin(); i < machine.states.end(); i++)
        {
            if ((*i).substr(0, 2) == currentState && (*i)[3] == tape[head])
            {
                tape[head] = (*i)[5];

                if ((*i)[7] == 'R' && tape[head + 1] != 'b')
                {
                    head++;
                    currentState = (*i).substr(9, 11);
                }
                else if ((*i)[7] == 'R' && tape[head + 1] == 'b')
                {
                    currentState = (*i).substr(9, 11);
                }
                else if ((*i)[7] == 'L' && tape[head - 1] != 'b')
                {
                    head--;
                    currentState = (*i).substr(9, 11);
                }
                else if ((*i)[7] == 'L' && tape[head - 1] == 'b')
                {
                    currentState = (*i).substr(9, 11);
                }
            }
        }

        string result;

        for (auto i = visitedStates.begin(); i < visitedStates.end(); i++)
        {
            result = result + " " + *i;
        }

        if (currentState == machine.acceptState)
        {
            result += "\nRESULT: accepted";
        }
        else if (currentState == machine.rejectState)
        {
            result += "\nRESULT: rejected";
        }
        else
        {
            result += "\nRESULT: looped";
        }

        return result;
    }
}

void readInputFile(Data &data)
{

    int counter = 0;
    string line;

    ifstream MyReadFile("Input_DENIZ_UZEN_S014489.txt");

    while (getline(MyReadFile, line))
    {

        if (counter == 0)
        {
            data.inputAlphVarNum = stoi(line);
        }
        else if (counter == 1)
        {
            data.inputAlph = line;
        }
        else if (counter == 2)
        {
            data.tapeAlphVarNum = stoi(line);
        }
        else if (counter == 3)
        {
            data.tapeAlph = line;
        }
        else if (counter == 4)
        {
            data.blank = line[0];
        }
        else if (counter == 5)
        {
            data.numStates = stoi(line);
        }
        else if (counter == 6)
        {
            data.allStates = line;
        }
        else if (counter == 7)
        {
            data.startState = line;
        }
        else if (counter == 8)
        {
            data.acceptState = line;
        }
        else if (counter == 9)
        {
            data.rejectState = line;
        }
        else
        {
            data.states.push_back(line);
        }

        counter++;
    }
    data.detectedStr = data.states.back();
    data.states.pop_back();
    MyReadFile.close();
}

int main()
{

    Data data;

    readInputFile(data);

    string result = simulateTuringMachine(data.detectedStr, data);
    cout << result << endl;

    return 0;
}