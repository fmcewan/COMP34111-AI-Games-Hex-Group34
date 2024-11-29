#include "GameState.h"
#include <iostream>
#include <cstdlib> // For rand()

// Constructor
GameState::GameState(int size)
    : boardSize(size), currentPlayer(1), terminalState(false), winner(0) {
    board = std::vector<std::vector<int>>(boardSize, std::vector<int>(boardSize, 0));
}

// Copy constructor
GameState::GameState(const GameState& other)
    : board(other.board), boardSize(other.boardSize), currentPlayer(other.currentPlayer),
      terminalState(other.terminalState), winner(other.winner) {}

// Destructor
GameState::~GameState() {}

// Get current player
int GameState::getCurrentPlayer() const {
    return currentPlayer;
}

// Apply a move
void GameState::applyMove(int x, int y) {
    if (board[x][y] == 0) {
        board[x][y] = currentPlayer;
        terminalState = checkWin(x, y, currentPlayer);
        if (terminalState) {
            winner = currentPlayer;
        } else if (getLegalActions().empty()) {
            terminalState = true; // Game ends in a draw
            winner = 0;
        }
        currentPlayer = 3 - currentPlayer; // Switch player
    }
}

// Undo a move
void GameState::undoMove(int x, int y) {
    board[x][y] = 0;
    currentPlayer = 3 - currentPlayer; // Switch back to previous player
    terminalState = false;
    winner = 0;
}

// Check if the game is in a terminal state
bool GameState::isTerminal() const {
    return terminalState;
}

// Get the winner
int GameState::getWinner() const {
    return winner;
}

// Get result for a specific player
int GameState::getResult(int player) const {
    if (winner == player) {
        return 1; // Current player wins
    } else if (winner == 3 - player) {
        return -1; // Opponent wins
    }
    return 0; // Draw or ongoing
}

// Get all legal actions
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

// Print the board
void GameState::printBoard() const {
    for (const auto& row : board) {
        for (int cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}

// Convert the board state to a feature vector
std::vector<float> GameState::toFeatures() const {
    std::vector<float> features;
    for (const auto& row : board) {
        for (int cell : row) {
            features.push_back(static_cast<float>(cell));
        }
    }
    return features;
}

// Overloaded comparison operator
bool GameState::operator==(const GameState& other) const {
    return board == other.board && currentPlayer == other.currentPlayer;
}

// Check if the current player wins
bool GameState::checkWin(int x, int y, int player) const {
    // Example: Check rows, columns, and diagonals for a win condition
    int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
    for (auto& dir : directions) {
        int count = 1;
        for (int step = 1; step < boardSize; ++step) {
            int nx = x + dir[0] * step;
            int ny = y + dir[1] * step;
            if (nx >= 0 && nx < boardSize && ny >= 0 && ny < boardSize && board[nx][ny] == player) {
                ++count;
            } else {
                break;
            }
        }
        for (int step = 1; step < boardSize; ++step) {
            int nx = x - dir[0] * step;
            int ny = y - dir[1] * step;
            if (nx >= 0 && nx < boardSize && ny >= 0 && ny < boardSize && board[nx][ny] == player) {
                ++count;
            } else {
                break;
            }
        }
        if (count >= 5) { // Adjust for specific win condition (e.g., 5 in a row)
            return true;
        }
    }
    return false;
}
