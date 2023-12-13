#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

void print(string text= " "){
    
    cout << text <<endl;
}

string getUserInput(string prompt){
    string input;
    cout <<prompt;
    getline(cin,input);
    return input;
}

string to_upper(string str){
    string container;
    transform(str.begin(),str.end(),back_inserter(container) ,::toupper) ;
    return container;
}
string to_lower(string str){
    string container;
    transform(str.begin(),str.end(),back_inserter(container) ,::tolower) ;
    return container;
}
void showOutput(string result,string robotName){
    string textToShow = "[ "+ to_upper(robotName)+" ] -> "+result;
    print(textToShow);
}

vector<string> split(string command){
    vector<string> commandVector;
    string word = "";
    for( char letter: command){
        if (isspace(letter)){
            commandVector.push_back(word);
            word = "";
        }
        else{
            word = word+letter;
        }
    }
    if (word != ""){
        commandVector.push_back(word);
    }
    return commandVector;
}
vector<int> do_forward(int steps,int direction,vector<int>& position){
    switch (direction){
    case 1:
        position[1]= position[1]+steps;
        break;
    case 2:
        print("here");
        position[0]= position[0]+steps;
        break;
    case 3:
        position[1]= position[1]-steps;
        break;
    case 4:
        position[0]= position[0]-steps;
        break;
    default:
        break;
    }
    return position;
}

string getDirection(int direction){
    switch (direction){
    case 1:
        return "north";
        break;
    case 2:
        return "east";
        break;
    case 3:
        return "south";
        break;
    case 4:
        return "west";
        break;
    default:
        break;
    }
    return "north";
}

bool handleCommand(string command,string robotName,int& direction,vector<int>& currentPosition){
    vector<string> commandVector = split(command);

    command = commandVector[0];
    if (commandVector.size() ==2){
            int argument;
            try{
                argument = stoi(commandVector[1]);
            }
            catch(const exception& e){
                showOutput("I do not understand, please try again.",robotName);
                return true;
            }
        
        if (to_lower(command) == "forward"){
            vector<int> position = do_forward(argument,direction,currentPosition);
            showOutput("Moved forward by "+to_string(argument)+" steps, now at position [x] "+to_string(position[0])+" [y] "+to_string(position[1]),robotName);
        }
        else if (to_lower(command) == "back"){
            vector<int> position = do_forward(-argument,direction,currentPosition);
            showOutput("Moved back by "+to_string(argument)+" steps, now at position "+to_string(position[0])+" "+to_string(position[1]),robotName);
        }
        else{
            showOutput("I do not understand, please try again.",robotName);

        }
    }
    else{
        if (to_lower(command) == "help"){
            showOutput("I can understand these commands:\n"
            "OFF  - Shut down robot\n"
            "HELP - provide information about commands\n"
            "FORWARD - move forward by specified number of steps\n"
            "BACK - move backward by specified number of steps\n"
            "RIGHT - turn right by 90 degrees\n"
            "LEFT - turn left by 90 degrees\n"
            "SPRINT - sprint forward by specified number of steps\n",robotName);
        }
        else if (to_lower(command) == "off"){
            showOutput("Shutting down..",robotName);
            return true;
        }
        else if (to_lower(command) == "right"){
            direction = direction+1;
            if (direction == 5){
                direction = 1;
            }
            showOutput("Turned right, now facing direction "+to_upper(getDirection(direction)),robotName);
        }
        else if (to_lower(command) == "left"){
            direction = direction-1;
            if (direction == 0){
                direction = 4;
            }
            showOutput("Turned left, now facing direction "+to_upper(getDirection(direction)),robotName);
        }
        else if (to_lower(command) == "sprint"){
            int steps = 5;
            for (int i = 1; i <= steps; i++){
                currentPosition = do_forward(i,direction,currentPosition);
            }
            showOutput("Sprinted forward by "+to_string(steps)+" steps, now at position "+to_string(currentPosition[0])+" "+to_string(currentPosition[1]),robotName);
        }
        else{
            showOutput("I do not understand, please try again.",robotName);
        }
    }  
    
    return false;
}

int main(){
    string greeter = "Hello kiddo!\n"
    "Ready to play a game?\n";
    print(greeter);
    string robotName = getUserInput("What do you want to name your robot? ");
    vector<int> position = {0,0};
    int direction = 1;
    bool quit = false;
    string command;
    string commandStyling = "[ "+ to_upper(robotName)+" ] -> What do you want me to do next? : ";
    while (!quit){
        // ask user for commands to the idle robot
        command = getUserInput(commandStyling);
        quit = handleCommand(command,robotName,direction,position);
        
    }
    return 0;
}