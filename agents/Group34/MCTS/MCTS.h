#ifndef MCTS_H
#define MCTS_H

#include "GameState.h"
#include "Node.h"
#include <memory>


class MCTS {
private:
    std::shared_ptr<MCTSNode> root;
    int maxIterations;
    double explorationConstant;
    int player;

public:
    MCTS(const GameState& initialState, int maxIterations = 1000, double explorationConstant = 1.41, int player = 1);
    ~MCTS();


    // Perform the MCTS search and return the best move
    std::pair<int, int> search();

private:
    // Simulate a random game from the given node and return the result (1.0 = win, 0.0 = loss, 0.5 = draw)
    double simulate(const std::shared_ptr<MCTSNode>& node);
};

#endif // MCTS_H


// public:
//     MCTS(const GameState& initialState, int maxIterations, double explorationConstant);
//     ~MCTS();

//     // Perform the MCTS search and return the best move
//     std::pair<int, int> search();
// };


