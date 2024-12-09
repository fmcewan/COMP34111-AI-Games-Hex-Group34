// Imports
#pragma once

#include <vector>
#include <memory>
#include "GameState.h"


class MCTSNode {
// each node represents a game state




    public:

        int visits; // times node has been visited
        double wins; // award accumulated by node
        bool end; // true if node is terminal


        MCTSNode* parent; // a pointer to another node object (the parent of this node)
        // I think this is needed for backpropagation
        // this is null if its the root

        std::vector<std::shared_ptr<MCTSNode>> children; // an array of pointers to other node objects (the children of this node)

        // so we'll need a method to add children to this list


        GameState state; // each node represents a game state

        MCTSNode(const GameState& state, MCTSNode* parent = nullptr); 
        ~MCTSNode();


        std::shared_ptr<MCTSNode> selectBestChild(double explorationConstant) const; // using ucb1

        // ACCESSING PRIVATE VARIABLES (get):

        //int getVisits() const;
        //float getAccReward() const;
        //bool getEnd() const;

        //MCTSNode* getParent() const;

        //std::vector<MCTSNode*> getChildren() const;

        // CHANGING THE STATE OF THE NODE (set)

        //void addVisit();
        //void addReward(float reward);
        //void setEnd(bool end);

        //void addChild(MCTSNode* child);


        void expand();
        void backpropagate(double result);


};