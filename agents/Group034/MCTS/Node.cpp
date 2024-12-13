#include "MCTS.h"
#include "Node.h"
#include "GameState.h"
#include <cmath>
#include <stdexcept>
#include <cfloat>
#include <algorithm>
#include <iostream>
#include <memory>
#include <unordered_set>

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator ()(const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2; 
    }
};



// MCTSNode Constructor
MCTSNode::MCTSNode(const GameState& state, MCTSNode* parent)
    : state(state), parent(parent), visits(0), wins(0.0) {}

// Destructor
MCTSNode::~MCTSNode() {}

//Expand node
void MCTSNode::expand() {
    auto legalActions = state.getLegalActions();
    for (const auto& action : legalActions) {
        GameState newState = state;
        newState.applyMove(action.first, action.second);
        children.push_back(std::make_shared<MCTSNode>(newState, this));
    }
}

// Backpropagate result
void MCTSNode::backpropagate(double result) {
    visits++;
    wins += result;
    if (parent) {
        parent->backpropagate(result);

    }
}

std::shared_ptr<MCTSNode> MCTSNode::selectBestChild(double explorationConstant) const {

    if (children.empty()) {
        throw std::runtime_error("ERROR: NODE HAS NO CHILDREN TO SELECT BEST CHILD FROM");
    }

    std::shared_ptr<MCTSNode> bestChild = nullptr;
    double bestValue = -std::numeric_limits<double>::infinity(); //lowest strarting value
    double ucb1;

    for (std::shared_ptr<MCTSNode> child : children) {
        if (child->visits==0) {
            ucb1 = std::numeric_limits<double>::infinity(); //if unvisited give highest priority
        }
        else {
           ucb1 = (child->wins / child->visits) + explorationConstant * std::sqrt(std::log(visits) / child->visits);

        }

        if (ucb1 > bestValue) {
            bestValue = ucb1;
            bestChild = child;
        }

    }

    return bestChild;
}

    