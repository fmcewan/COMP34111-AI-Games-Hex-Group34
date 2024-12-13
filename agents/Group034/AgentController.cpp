// Default imports
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <cstdlib>
#include <ctime>

// Header imports
#include "AgentController.h"

#include "MCTS/GameState.h"
#include "MCTS/MCTS.h"
#include "MCTS/Node.h"


std::string AgentController::getMessage() {
    std::string message;
    std::getline(std::cin, message);
    return message;
}

void AgentController::sendMessage(std::string message) {
    std::cout << message << "\n" << std::flush;
}

messageType AgentController::stringToEnum(std::string message) {
    if (message == "START") return START;
    if (message == "CHANGE") return CHANGE;
    if (message == "SWAP") return SWAP;
    return START;
}

bool AgentController::interpretMessage(std::string message) {
    try {
        
        // Splitting and stripping the incoming message
        std::vector<std::string> gameState;
        std::stringstream messagestream(message);
        std::string parts;

        while (std::getline(messagestream, parts, ';')) {
            parts.erase(std::remove_if(parts.begin(), parts.end(), isspace), parts.end());
            gameState.push_back(parts);
        }

        // Saving turn
        turn = std::stoi(gameState[3]);

        // Interpreting move
        std::string board = gameState[2];
        switch (stringToEnum(gameState[0])) {
            case START:
                if (colour == "R") makeMove(board);
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
    } catch (std::exception& e) {
        return false;
    }
    return true;
}

// void AgentController::makeMove(std::string Board) {
//     if (turn == 2 && rand() % 2 == 1) {
//         sendMessage("-1,-1");
//         return;
//     }

//     //Splitting board string
//     std::stringstream split(Board);
//     std::vector<std::string> lines;
//     std::string each;

//     while (std::getline(split, each, ',')) {
//         lines.push_back(each);
//     }

//     //Finding all posible moves
//     std::vector<std::vector<int>> choices;

//     for (int i = 0; i < boardSize; i++) {
//         for (int j = 0; j < boardSize; j++) {
//             if (lines[i][j] == '0') {
//                 choices.push_back({i, j});
//             }
//         }
//     }

//     //Choosing random move
//     if (!choices.empty()) {
//         int choice_index = rand() % choices.size();
//         std::vector<int> choice = choices[choice_index];
//         std::string msg = std::to_string(choice[0]) + "," + std::to_string(choice[1]);
//         sendMessage(msg);
//     }
// }

void AgentController::makeMove(std::string Board) {
    if (turn == 2 && rand() % 2 == 1) {
        sendMessage("-1,-1"); // Random swap decision for turn 2
        return;
    }

    // Removing , from BOard String
    std::string cleanBoard;
    for (char c : Board) {
        if (c != ',') {
            cleanBoard += c;
        }
    }

    // Parse board string into GameState
    GameState gameState(boardSize);
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            char cell = cleanBoard[i * boardSize + j];
            
            if (cell == 'R') gameState.makeBoard(i, j, 1);
            else if (cell == 'B') gameState.makeBoard(i, j, 2);
        }
    }
    
    //Swapping logic for mcts
    int player;
    if (colour == "R") {
        player = 1;
    }
    if (colour == "B") {
        player = 2;
    }

    // Running MCTS to determine the best move
    MCTS mcts(gameState, 1000, 1.41, player);  
    std::pair<int, int> bestMove = mcts.search();  

    // Send the selected move
    std::string msg = std::to_string(bestMove.first) + "," + std::to_string(bestMove.second);
    sendMessage(msg);
}



AgentController::AgentController(std::string agentColour, int gameBoardSize) {
    boardSize = gameBoardSize;
    colour = agentColour;
    turn = 0;
}

void AgentController::run() {
    srand(time(nullptr));
    while (true) {
        std::string message = getMessage();
        if (!interpretMessage(message)) break;
    }
}

std::string AgentController::opp(std::string colour) {
    return colour == "R" ? "B" : "R";
}

int main(int argc, char* argv[]) {
    if (argc != 3) throw std::invalid_argument("Input must be colour and board size.");
    std::string inputColour = argv[1];
    int parsedBoardSize = std::stoi(argv[2]);

    AgentController agent(inputColour, parsedBoardSize);
    agent.run();
}
