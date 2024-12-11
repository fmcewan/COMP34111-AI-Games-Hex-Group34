#include "MCTS.h"
#include "Node.h"
#include "GameState.h"  
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <limits>
#include <random>
#include <iostream>


// MCTS Constructor
MCTS::MCTS(const GameState& initialState, int maxIterations, double explorationConstant)
    : root(std::make_shared<MCTSNode>(initialState)), maxIterations(maxIterations),
      explorationConstant(explorationConstant) {}

// Destructor
MCTS::~MCTS() {}

// Run MCTS and return the best

std::pair<int, int> MCTS::search() {
    for (int i = 0; i < maxIterations; ++i) {

        // If root is terminal, stop searching
        if (root->state.isTerminal()) {
            break;  // If root is terminal, stop searching
        }
        
        // Expand root if it has no children yet
        if (root->children.empty()) {
            root->expand();  
        }

        // if (root->children.empty()) {
        //     root->expand();  // Expand root if it has no children yet
        //     std::cerr << "[DEBUG] Expanded child at search function " << std::endl;
        //     for (size_t i = 0; i < std::min(static_cast<size_t>(10), root->children.size()); ++i) {
        //         const auto& move = root->children[i]->state.getLastMove();
        //         std::cerr << "[DEBUG] Expanded child " << i 
        //           << " with move: (" << move.first << ", " << move.second << ")" 
        //           << std::endl;
        //     }
        // }



        // Selection
        auto selectedNode = root->selectBestChild(explorationConstant);

        // Expansion
        if (!selectedNode->state.isTerminal()) {
            selectedNode->expand();
        }

        // Simulation
        double result = simulate(selectedNode);

        // Backpropagation
        selectedNode->backpropagate(result);
    }

    auto bestChild = root->selectBestChild(explorationConstant); 

    return bestChild->state.getLastMove();
}


double MCTS::simulate(const std::shared_ptr<MCTSNode>& node) {
    GameState tempState = node->state;

    while (!tempState.isTerminal()) {
        auto legalActions = tempState.getLegalActions();
        if (legalActions.empty()) break;

        // Randomly select a move
        auto action = legalActions[rand() % legalActions.size()];
        tempState.applyMove(action.first, action.second);
    }

    int winner = tempState.getWinner();
    if (winner == node->state.getCurrentPlayer()) return 1.0;  // Win
    if (winner == 0) return 0.5;  // Draw
    return 0.0;  // Loss
}
