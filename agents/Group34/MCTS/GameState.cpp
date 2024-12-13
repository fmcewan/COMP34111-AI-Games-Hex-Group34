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
      terminalState(other.terminalState), winner(other.winner), lastMove(other.lastMove){}

// Destructor
GameState::~GameState() {}

int GameState::getCurrentPlayer() const {
    return currentPlayer;
}

bool GameState::isTerminal() const {
    return terminalState;
}

int GameState::getWinner() const {
    return winner;
}

std::vector<std::pair<int, int>> GameState::getLegalActions() const {
    std::vector<std::pair<int, int>> actions;
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            if (board[i][j] == 0) {
                actions.emplace_back(i, j);
            }
        }
    }

    return actions;
}


void GameState::applyMove(int x, int y) {
    if (board[x][y] == 0) {
        board[x][y] = currentPlayer; 
        lastMove = std::make_pair(x, y); 

        if (checkWin(currentPlayer)) { // Check if the player has won
            terminalState = true;
            winner = currentPlayer;
        } else if (getLegalActions().empty()) { // Check for a draw
            terminalState = true;
            winner = 0;
        }
        currentPlayer = 3 - currentPlayer; // Switch to the other player
    }
}

std::pair<int, int> GameState::getLastMove() const {
    return lastMove;
}

// make board
void GameState::makeBoard(int x, int y, int player) {
    if (board[x][y] == 0) {
        board[x][y] = player; 
        lastMove = std::make_pair(x, y); 
        
        if (checkWin(player)) { // Check if the player has won
            terminalState = true;
            winner = player;
        } else if (getLegalActions().empty()) { // Check for a draw
            terminalState = true;
            winner = 0;
        }



    }
}

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

    // Player 1 connects from the top to the bottom
    if (player == 1) {
        for (int j = 0; j < boardSize; ++j) {
            if (board[0][j] == 1 && dfsCheckWin(0, j, 1, visited)) {
                return true;
            }
        }
    }
    
    // Player 2 connects from the left to the right
    if (player == 2) {
        for (int i = 0; i < boardSize; ++i) {
            if (board[i][0] == 2 && dfsCheckWin(i, 0, 2, visited)) {
                return true;
            }
        }
    }


    return false;
}

// Depth-first search helper function
bool GameState::dfsCheckWin(int x, int y, int player, std::vector<std::vector<bool>>& visited) const {
    if (player == 1 && x == boardSize - 1) return true; // Player 1 connects to the bottom
    if (player == 2 && y == boardSize - 1) return true; // Player 2 connects to the right

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









