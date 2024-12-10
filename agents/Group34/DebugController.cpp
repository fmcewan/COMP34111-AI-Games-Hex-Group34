#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "AgentController.h"

#include "MCTS/GameState.h"
#include "MCTS/MCTS.h"
#include "MCTS/Node.h"


std::string AgentController::getMessage() {
    std::string message;
    std::getline(std::cin, message);
    std::cerr << "[DEBUG] Received message: " << message << std::endl;
    return message;
}

void AgentController::sendMessage(std::string message) {
    std::cerr << "[DEBUG] Sending response: " << message << std::endl;
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
        // turn++;
        std::vector<std::string> gameState;
        std::stringstream messagestream(message);
        std::string parts;

        while (std::getline(messagestream, parts, ';')) {
            parts.erase(std::remove_if(parts.begin(), parts.end(), isspace), parts.end());
            gameState.push_back(parts);
        }

        std::cerr << "[DEBUG] Parsed game state:" << std::endl;
        for (const auto& part : gameState) {
            std::cerr << part << std::endl;
        }


        turn = std::stoi(gameState[3]);

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
        std::cerr << "[ERROR] Exception in interpretMessage: " << e.what() << std::endl;
        return false;
    }
    return true;
}

void AgentController::makeMove(std::string Board) {
    std::cerr << "[DEBUG] Current turn: " << turn << std::endl;

    
    if (turn == 2 && rand() % 2 == 1) {
        sendMessage("-1,-1");
        return;
    }

    // Parse board string into GameState
    GameState gameState(boardSize);
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            char cell = Board[i * boardSize + j];
            // if (cell == 'R' || cell == 'B') {
            //     gameState.applyMove(i, j);  // Apply the move without specifying the player
            // }

            if (cell == 'R') gameState.makeBoard(i, j, 1);
            else if (cell == 'B') gameState.makeBoard(i, j, 2);
            // If the cell is occupied by player 1 or player 2, apply the move using the currentPlayer
        }
    }

    // std::cerr << "[DEBUG] Printing gamaestate board " << std::endl;
    // gameState.printBoard();

    std::cerr << "[DEBUG] starting mcts " << turn << std::endl;

    // Now run MCTS to determine the best move
    MCTS mcts(gameState, 1000, 1.41);  // 1000 iterations, exploration constant sqrt(2)
    std::pair<int, int> bestMove = mcts.search();  // Call the search function

    // Send the selected move
    std::cerr << "[DEBUG] MOve to send " << bestMove.first << std::endl;
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
