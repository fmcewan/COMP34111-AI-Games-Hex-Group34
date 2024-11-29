#include "MCTS.h"
#include "Node.h"
#include <cmath>
#include <algorithm>
#include <cstdlib>

// // MCTSNode Constructor
// MCTSNode::MCTSNode(const GameState& state, MCTSNode* parent)
//     : state(state), parent(parent), visits(0), wins(0.0) {}

// // Destructor
// MCTSNode::~MCTSNode() {}

// // Select the best child using UCB1
// std::shared_ptr<MCTSNode> MCTSNode::selectBestChild(double explorationConstant) const {
//     return *std::max_element(children.begin(), children.end(),
//         [explorationConstant, this](const std::shared_ptr<MCTSNode>& a, const std::shared_ptr<MCTSNode>& b) {
//             double ucb1A = (a->wins / a->visits) +
//                            explorationConstant * std::sqrt(std::log(visits) / a->visits);
//             double ucb1B = (b->wins / b->visits) +
//                            explorationConstant * std::sqrt(std::log(visits) / b->visits);
//             return ucb1A < ucb1B;
//         });
// }


// // Expand node
// void MCTSNode::expand() {
//     auto legalActions = state.getLegalActions();
//     for (const auto& action : legalActions) {
//         GameState newState = state;
//         newState.applyMove(action.first, action.second);
//         children.push_back(std::make_shared<MCTSNode>(newState, this));
//     }
// }

// // Backpropagate result
// void MCTSNode::backpropagate(double result) {
//     visits++;
//     wins += result;
//     if (parent) {
//         parent->backpropagate(1.0 - result); // Flip result for the opponent
//     }
// }

// MCTS Constructor
MCTS::MCTS(const GameState& initialState, int maxIterations, double explorationConstant)
    : root(std::make_shared<MCTSNode>(initialState)), maxIterations(maxIterations),
      explorationConstant(explorationConstant) {}

// Destructor
MCTS::~MCTS() {}

// Run MCTS and return the best
