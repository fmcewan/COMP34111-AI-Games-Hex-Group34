// Default imports
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <exception>
#include <algorithm>  
#include <cctype>     
#include <cstdlib>    
#include <ctime>      

// Header imports
#include "AgentController.h"

// enum declarations

std::string AgentController::getMessage() {
    
    std::string message;
    std::cin >> message;

    return message;
}

void AgentController::sendMessage(std::string message) {
    std::cout << message << "\n" << std::flush;
}

messageType AgentController::stringToEnum(std::string message) {
    if (message == "START") return START;
    if (message == "CHANGE") return CHANGE;
    if (message == "SWAP") return SWAP;
}

bool AgentController::interpretMessage(std::string message) {
    turn++;

    // Splitting and stripping the incoming message
    std::vector< std::string > gameState;

    std::stringstream messagestream(message);
    std::string parts;

    std::cout << message << std::endl;

    while (std::getline(messagestream, parts, ';')) {
        parts.erase(std::remove_if(parts.begin(), parts.end(), isspace), parts.end());
        gameState.push_back(parts);
    }

    for (int i = 0; i<gameState.size(); i++) {
        std::cout << gameState[i];
    }
    std::cout << std::endl;

    // Interpreting move
    std::string board = gameState[2];
    std::cout << board << std::endl;
    
    switch (stringToEnum(gameState[0])) {
        case START:
            if (colour == "R") {
                makeMove(board);
            }
            break;
        case CHANGE:
            makeMove(board);
            break;
        case SWAP:
            colour = opp(colour);
            makeMove(board);
            break;
        default:
            return false;
    }

}

void AgentController::makeMove(std::string Board) {
    
    if (turn == 2 && rand() % 2 == 1){
        sendMessage("-1,-1");
        return;
    }

    //Splitting board string
    std::stringstream split(Board);
    std::vector<std::string> lines;
    std::string each;

    std::cout << Board <<std::endl;

    while (std::getline(split, each, ',')) {
        lines.push_back(each);
    }

    for (int i=0; i<lines.size(); i++) {
        std::cout << lines[i];
    }
    std::cout << std::endl;

    //Finding all posible moves
    std::vector< std::vector<int> > choices;

    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
            if (lines[i][j] == '0') {
                std::vector<int> newElement(i, j);
                choices.push_back(newElement);
            }
        }
    }

    //Choosing random move
    if (choices.size() > 0){
        int choice_index = rand() % (choices.size());
        std::vector<int> choice = choices[choice_index];
        std::string msg = std::to_string(choice[0]) + "," + std::to_string(choice[1])+ "\n" ;
        sendMessage(msg);
    }       
}

AgentController::AgentController(std::string agentColour, int gameBoardSize) {
    boardSize = gameBoardSize;
    colour = agentColour;
}

void AgentController::run() {
    std::cin >> messageInput;

    // Gets string
    while (true) {
        
        try {
            std::string message = getMessage();
            bool res = interpretMessage(message);
            if (res == false) { break; }
        }
        catch (...) {
            std::cout << "ERROR: Could not establish I/0.\n";
            break;
        }
    }
}

std::string AgentController::opp(std::string colour) {
    if (colour == "R") { return "B"; }
    if (colour == "B") { return "R"; }
}


int main(int argc, char *argv[]) {

    std::string inputColour;
    std::string inputBoardSize;

    if (argc == 3) {
        inputColour = argv[1];
        inputBoardSize = argv[2];
    }
    else {
        throw std::invalid_argument("Input must be colour and board size.");
    }

    int parsedBoardSize = std::stoi(inputBoardSize);

    AgentController agent(inputColour, parsedBoardSize);
    agent.run();

}
