#include "MCTS.h"
#include "Node.h"
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


// Select the best child using UCB1
// std::shared_ptr<MCTSNode> MCTSNode::selectBestChild(double explorationConstant) const {

//     if (children.empty()) {

//     throw std::runtime_error("ERROR: NODE HAS NO CHILDREN TO SELECT BEST CHILD FROm");
    
    
//     }

//     std::unordered_set<std::pair<int, int>, pair_hash> visitedMoves; 

//     for (const auto& child : children) {
//         visitedMoves.insert(child->state.getLastMove());
//     }


//     return *std::max_element(children.begin(), children.end(),
//         [&visitedMoves, explorationConstant, this](const std::shared_ptr<MCTSNode>& a, const std::shared_ptr<MCTSNode>& b) {

//              if (visitedMoves.find(a->state.getLastMove()) != visitedMoves.end()) {
//                 return false;  // Skip node 'a'
//             }
//             if (visitedMoves.find(b->state.getLastMove()) != visitedMoves.end()) {
//                 return true;  // Prefer node 'b' if 'a' is revisited
//             }

//             double ucb1A = (a->visits==0) ? std::numeric_limits<double>::max() : // check if node hasnt been visited make it top priority by asigning value of infinity if it hasnt
//                 (a->wins / a->visits) + explorationConstant * std::sqrt(std::log(visits) / a->visits); // calculate ucb value using visits and wins (ucb reduced exploration constant as exploitation increases)
//             double ucb1B = (b->visits==0) ? std::numeric_limits<double>::max() :
//                 (b->wins / b->visits) + explorationConstant * std::sqrt(std::log(visits) / b->visits);

//             if (std::abs(ucb1A - ucb1B) < FLT_EPSILON) { // if the ucb scores are identical just randomise choice


            
//                 return rand() % 2 == 0; // random number mod 2 returns 0 or 1 then compared with 0 returns true or false (true = explore node b false = explore node a)
//             }



//             return ucb1A < ucb1B; // return true if node b is preffered
//         });



//}


// Expand node
// void MCTSNode::expand() {
//     auto legalActions = state.getLegalActions();
//     for (const auto& action : legalActions) {
//         GameState newState = state;
//         newState.applyMove(action.first, action.second);
//         children.push_back(std::make_shared<MCTSNode>(newState, this));
//     }
// }

void MCTSNode::expand() {
    auto legalActions = state.getLegalActions();
    if (legalActions.empty()) {
        std::cout << "[DEBUG] No legal actions available during expansion." << std::endl;
    }
    for (const auto& action : legalActions) {
        GameState newState = state;
        int count = 0;
        newState.applyMove(action.first, action.second);
        // std::cout << "[DEBUG] checking newState lastMove"<<newState.getLastMove().second << std::endl;
        
        children.push_back(std::make_shared<MCTSNode>(newState, this));
    }


    // if(count < 10){
    //     const auto& move = newState.getLastMove();
    //         std::cerr << "[DEBUG] Expanded newState " 
    //                 << " with move: (" << move.first << ", " << move.second << ")" 
    //                 << std::endl;
    //     count++;
    //     }



        //  Log to a file or a separate stream if needed
         //std::cerr << "[DEBUG] Expanded child with move: " << newState.getLastMove().first << std::endl;


        // std::cerr << "[DEBUG] Expanding move: (" << action.first << ", " << action.second << ")" << std::endl;
        // std::cerr << "[DEBUG] Parent state:" << std::endl;
        // state.printBoard();
        // std::cerr << "[DEBUG] Child state after move:" << std::endl;
        // newState.printBoard();

        // children.push_back(std::make_shared<MCTSNode>(newState, this));


    

    // std::cerr << "[DEBUG] Expanded child at expand function " << std::endl;
    // for (size_t i = 0; i < std::min(static_cast<size_t>(10), children.size()); ++i) {
    //     const auto& move = children[i]->state.getLastMove();
    //     std::cerr << "[DEBUG] Expanded child " << i 
    //               << " with move: (" << move.first << ", " << move.second << ")" 
    //               << std::endl;
    // }
    

}


// Backpropagate result
void MCTSNode::backpropagate(double result) {
    visits++;
    wins += result;
    if (parent) {
        parent->backpropagate(1.0 - result); // Flip result for the opponent


    }
}



std::shared_ptr<MCTSNode> MCTSNode::selectBestChild(double explorationConstant) const {

     if (children.empty()) {

     throw std::runtime_error("ERROR: NODE HAS NO CHILDREN TO SELECT BEST CHILD FROM");
    
    }

    std::shared_ptr<MCTSNode> bestChild = nullptr;

    double bestValue = FLT_EPSILON;

    double ucb1;

    for (std::shared_ptr<MCTSNode> child : children) {
        if (child->visits==0) {
            ucb1 = std::numeric_limits<double>::infinity();
        }
        else {
           ucb1 = (child->wins / child->visits) + explorationConstant * std::sqrt(std::log(visits) / child->visits);

        }


        if (ucb1 > bestValue) {

            bestValue = ucb1;
            bestChild = child;
        
        }

         // check if node hasnt been visited make it top priority by asigning value of infinity if it hasnt
         // calculate ucb value using visits and wins (ucb reduced exploration constant as exploitation increases)

    }

    return bestChild;
}

    