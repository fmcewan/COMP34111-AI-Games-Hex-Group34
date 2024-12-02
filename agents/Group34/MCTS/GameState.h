#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include <string>
#include <utility>

class GameState {
private:
    int boardSize;                             // Hex board size (NxN)
    std::vector<std::vector<int>> board;      // Hex board (0: empty, 1: player 1, 2: player 2)
    int currentPlayer;                        // Current player (1 or 2)
    bool terminalState;                       // Whether the game is in a terminal state
    int winner;                               // Winner (0: no winner, 1: player 1, 2: player 2)

    // Hexagonal directions, used for calculating neighbors
    const std::vector<std::pair<int, int>> hexDirections = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, 1}, {1, -1}
    };

    // Depth-first search for checking connected paths
    bool dfsCheckWin(int x, int y, int player, std::vector<std::vector<bool>>& visited) const;

public:
    // Constructors and Destructor
    GameState(int size);
    GameState(const GameState& other);
    ~GameState();

    // Game state-related methods
    int getCurrentPlayer() const;
    bool isTerminal() const;
    int getWinner() const;

    // Retrieve legal moves
    std::vector<std::pair<int, int>> getLegalActions() const;

    // Apply and undo moves
    void applyMove(int x, int y);
    void undoMove(int x, int y);

    // Print the board
    void printBoard() const;

    // Get neighbors for a given position
    std::vector<std::pair<int, int>> getNeighbors(int x, int y) const;

    // Check if a player has won
    bool checkWin(int player) const;

    // Overloaded operator (state comparison)
    bool operator==(const GameState& other) const;
};

#endif // GAMESTATE_H
