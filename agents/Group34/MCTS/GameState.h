#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include <utility>
#include <string>

class GameState {
private:
    int currentPlayer;                      // Current player (1 or 2)
    std::vector<std::vector<int>> board;   // Game board (0: empty, 1: player 1, 2: player 2)
    int boardSize;                         // Board size (NxN)
    bool terminalState;                    // Whether the game is in a terminal state
    int winner;                            // Winner (0: no winner, 1: player 1, 2: player 2)

    // Check if the current state is a win for the current player
    bool checkWin(int x, int y, int player) const;

public:
    GameState(int size);
    GameState(const GameState& other); // Copy constructor
    ~GameState();

    int getCurrentPlayer() const;
    void applyMove(int x, int y);
    void undoMove(int x, int y);
    bool isTerminal() const;
    int getWinner() const;
    int getResult(int player) const;
    std::vector<std::pair<int, int>> getLegalActions() const;
    void printBoard() const;
    std::vector<float> toFeatures() const;
    bool operator==(const GameState& other) const;
};

#endif // GAMESTATE_H
