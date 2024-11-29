#ifndef MCTS_H
#define MCTS_H

#include "GameState.h"
#include "Node.h"
#include <memory>

//class MCTSNode {
//public:
    //GameState state;
    //MCTSNode* parent;
    //std::vector<std::shared_ptr<MCTSNode>> children;
    //int visits;
    //double wins;

    //MCTSNode(const GameState& state, MCTSNode* parent = nullptr);
    //~MCTSNode();

    //std::shared_ptr<MCTSNode> selectBestChild(double explorationConstant) const;
    //void expand();
    //void backpropagate(double result);
//};

class MCTS {
private:
    std::shared_ptr<MCTSNode> root;
    int maxIterations;
    double explorationConstant;

public:
    MCTS(const GameState& initialState, int maxIterations = 1000, double explorationConstant = 1.41);
    ~MCTS();

    std::pair<int, int> run();
};

#endif // MCTS_H
