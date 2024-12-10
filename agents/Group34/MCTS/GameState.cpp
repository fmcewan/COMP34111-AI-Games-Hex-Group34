#include "GameState.h"
#include <iostream>
#include <stack>
#include <vector>

// Constructor
GameState::GameState(int size)
    : boardSize(size), currentPlayer(1), terminalState(false), winner(0) {
    board = std::vector<std::vector<int>>(boardSize, std::vector<int>(boardSize, 0));
}

// Copy constructor
GameState::GameState(const GameState& other)
    : boardSize(other.boardSize), board(other.board), currentPlayer(other.currentPlayer),
      terminalState(other.terminalState), winner(other.winner) {}

// Destructor
GameState::~GameState() {}

// Get the current player
int GameState::getCurrentPlayer() const {
    return currentPlayer;
}

// Check if the game is in a terminal state
bool GameState::isTerminal() const {
    return terminalState;
}

// Get the winner of the game
int GameState::getWinner() const {
    return winner;
}

// // Retrieve legal moves
// std::vector<std::pair<int, int>> GameState::getLegalActions() const {
//     std::vector<std::pair<int, int>> actions;
//     for (int i = 0; i < boardSize; ++i) {
//         for (int j = 0; j < boardSize; ++j) {
//             if (board[i][j] == 0) {
//                 actions.emplace_back(i, j); // Add empty positions
//             }
//         }
//     }
//     return actions;
// }

std::vector<std::pair<int, int>> GameState::getLegalActions() const {
    std::vector<std::pair<int, int>> actions;
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            if (board[i][j] == 0) {
                actions.emplace_back(i, j);
            }
        }
    }

    // // Debug: Print all legal actions
    // std::cerr << "[DEBUG] Legal actions:";
    // if (actions.empty()) {
    //     std::cerr << " No legal actions found. Board might be full or incorrectly initialized." << std::endl;
    // } else {
    //     for (const auto& action : actions) {
    //         std::cerr << " (" << action.first << ", " << action.second << ")";
    //     };
    //     std::cerr << std::endl;
    // }

    return actions;
}







// // Apply a move
// void GameState::applyMove(int x, int y) {
//     if (board[x][y] == 0) {
//         board[x][y] = currentPlayer; // Current player places a piece

//         lastMove = std::make_pair(x, y); // Store the last move
        
//         if (checkWin(currentPlayer)) { // Check if the current player has won
//             terminalState = true;
//             winner = currentPlayer;
//         } else if (getLegalActions().empty()) { // Check for a draw
//             terminalState = true;
//             winner = 0;
//         }
//         currentPlayer = 3 - currentPlayer; // Switch to the other player
//     }
// }

void GameState::applyMove(int x, int y) {
    if (board[x][y] == 0) {
        board[x][y] = currentPlayer; // Use the provided player
        lastMove = std::make_pair(x, y); // Store the last move

        if (checkWin(currentPlayer)) { // Check if the player has won
            terminalState = true;
            winner = currentPlayer;
        } else if (getLegalActions().empty()) { // Check for a draw
            terminalState = true;
            winner = 0;
        }
        currentPlayer = 3 - currentPlayer; // Switch to the other player

        //std::cerr << "[DEBUG] Last move: (" << lastMove.first << ", " << lastMove.second << ")" << std::endl;
    }
}




// Return last move
std::pair<int, int> GameState::getLastMove() const {
    return lastMove;
}

// make board
void GameState::makeBoard(int x, int y, int player) {
    if (board[x][y] == 0) {
        board[x][y] = player; // Use the provided player
        lastMove = std::make_pair(x, y); // Store the last move
        // print la

       

        if (checkWin(player)) { // Check if the player has won
            terminalState = true;
            winner = player;
        } else if (getLegalActions().empty()) { // Check for a draw
            terminalState = true;
            winner = 0;
        }



    }
}

// Print the board
void GameState::printBoard() const {
    for (int i = 0; i < boardSize; ++i) {
        // Add indentation to align the hexagonal board
        std::cerr << std::string(i, ' ');
        for (int j = 0; j < boardSize; ++j) {
            std::cerr << board[i][j] << " ";
        }
        std::cerr << std::endl;
    }
}

// Get neighbors for a given position
std::vector<std::pair<int, int>> GameState::getNeighbors(int x, int y) const {
    std::vector<std::pair<int, int>> neighbors;
    for (const auto& dir : hexDirections) {
        int nx = x + dir.first;
        int ny = y + dir.second;
        if (nx >= 0 && nx < boardSize && ny >= 0 && ny < boardSize) {
            neighbors.emplace_back(nx, ny);
        }
    }
    return neighbors;
}

// Check if a player has won (using depth-first search)
bool GameState::checkWin(int player) const {
    std::vector<std::vector<bool>> visited(boardSize, std::vector<bool>(boardSize, false));

    // Player 1 connects from the left to the right
    if (player == 1) {
        for (int i = 0; i < boardSize; ++i) {
            if (board[i][0] == 1 && dfsCheckWin(i, 0, 1, visited)) {
                return true;
            }
        }
    }

    // Player 2 connects from the top to the bottom
    if (player == 2) {
        for (int j = 0; j < boardSize; ++j) {
            if (board[0][j] == 2 && dfsCheckWin(0, j, 2, visited)) {
                return true;
            }
        }
    }

    return false;
}

// Depth-first search helper function
bool GameState::dfsCheckWin(int x, int y, int player, std::vector<std::vector<bool>>& visited) const {
    if (player == 1 && y == boardSize - 1) return true; // Player 1 connects to the right
    if (player == 2 && x == boardSize - 1) return true; // Player 2 connects to the bottom

    visited[x][y] = true;
    for (const auto& [nx, ny] : getNeighbors(x, y)) {
        if (!visited[nx][ny] && board[nx][ny] == player) {
            if (dfsCheckWin(nx, ny, player, visited)) {
                return true;
            }
        }
    }
    return false;
}

// Overload comparison operator (compare states)
bool GameState::operator==(const GameState& other) const {
    return board == other.board && currentPlayer == other.currentPlayer;
}


// void GameState::applyMove(int x, int y, int player) {
//     if (board[x][y] == 0) {
//         board[x][y] = player;
//         currentPlayer = 3 - player;
//     }
// }
