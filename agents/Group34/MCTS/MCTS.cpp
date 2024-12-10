#include "MCTS.h"
#include "Node.h"
#include "GameState.h"  
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <limits>
#include <random>



// MCTS Constructor
MCTS::MCTS(const GameState& initialState, int maxIterations, double explorationConstant)
    : root(std::make_shared<MCTSNode>(initialState)), maxIterations(maxIterations),
      explorationConstant(explorationConstant) {}

// Destructor
MCTS::~MCTS() {}

// Run MCTS and return the best

std::pair<int, int> MCTS::search() {
    for (int i = 0; i < maxIterations; ++i) {

        if (root->state.isTerminal()) {
            break;  // If root is terminal, stop searching
        }
        
        if (root->children.empty()) {
         root->expand();  // Expand root if it has no children yet
        }

        // Selection: Select the best child node based on UCB1
        auto selectedNode = root->selectBestChild(explorationConstant);

        // Expansion: Expand the selected node if it is not terminal
        if (!selectedNode->state.isTerminal()) {
            selectedNode->expand();
        }

        // Simulation: Simulate the game from the current node and get the result
        double result = simulate(selectedNode);

        // Backpropagation: Backpropagate the result up to the root
        selectedNode->backpropagate(result);
    }

    // After running the search, select the best child node based on the number of visits
    auto bestChild = root->selectBestChild(explorationConstant); // You can directly use selectBestChild

    // Return the move of the best child node
    return bestChild->state.getLastMove();
}



// Simulate a random game from the current node and return the result
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
