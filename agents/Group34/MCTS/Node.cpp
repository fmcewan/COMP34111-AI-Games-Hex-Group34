#include "MCTS.h"
#include "Node.h"
#include <cmath>
#include <stdexcept>

// MCTSNode Constructor
MCTSNode::MCTSNode(const GameState& state, MCTSNode* parent)
    : state(state), parent(parent), visits(0), wins(0.0) {}

// Destructor
MCTSNode::~MCTSNode() {}

//Node* Node::getParent() const {

    //return parent;
//}

//std::vector<Node*>Node::getChildren() const {
    //return children;
//}

//int Node::getVisits() const {

//     return visits;
// }

// Select the best child using UCB1
std::shared_ptr<MCTSNode> MCTSNode::selectBestChild(double explorationConstant) const {

    if (children.empty()) {

    throw std::runtime_error("ERROR: NODE HAS NO CHILDREN TO SELECT BEST CHILD FROm");
    
    }


    return *std::max_element(children.begin(), children.end(),
        [explorationConstant, this](const std::shared_ptr<MCTSNode>& a, const std::shared_ptr<MCTSNode>& b) {
            double ucb1A = (a->visits==0) ? std::numeric_limits<double>::infinity() : // check if node hasnt been visited make it top priority by asigning value of infinity if it hasnt
                (a->wins / a->visits) + explorationConstant * std::sqrt(std::log(visits) / a->visits); // calculate ucb value using visits and wins (ucb reduced exploration constant as exploitation increases)
            double ucb1B = (b->visits==0) ? std::numeric_limits<double>::infinity() :
                (b->wins / b->visits) + explorationConstant * std::sqrt(std::log(visits) / b->visits);

            if (std::abs(ucb1A - ucb1B) < FLT_EPSILON) { // if the ucb scores are identical just randomise choice


            
                return rand() % 2 == 0; // random number mod 2 returns 0 or 1 then compared with 0 returns true or false (true = explore node b false = explore node a)
            }



            return ucb1A < ucb1B; // return true if node b is preffered
        });



}


// Expand node
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
        parent->backpropagate(1.0 - result); // Flip result for the opponent
    }
}
