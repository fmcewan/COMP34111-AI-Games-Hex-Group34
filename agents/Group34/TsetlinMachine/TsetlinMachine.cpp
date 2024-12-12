// Imports
#include <algorithm>
#include <iostream>

// Header imports
#include "TsetlinMachine.h"

// Constructor

TsetlinMachine::TsetlinMachine(): memory(Memory(0,0,{})) {}

TsetlinMachine::TsetlinMachine(Memory memoryInput): memory(memoryInput) {}

// Getters and setters

Memory TsetlinMachine::getMemory() {
    return memory;
}

// Class methods

bool TsetlinMachine::evaluate_condition(std::unordered_map<std::string, bool> observation, std::vector<std::string> condition) {

    bool truth_value = true;

    for (auto feature : observation) {

        bool truthValue = false;

        std::string notString = "NOT ";
        std::string featureString = feature.first;

        bool isInCondition = (std::find(condition.begin(), condition.end(), featureString) != condition.end());
        bool notIsInCondition = (std::find(condition.begin(), condition.end(), notString+featureString)) != condition.end();

        auto featureIterator = observation.find(featureString); 

        if (isInCondition == true && featureIterator->second == false) {
            truthValue = false;
            break;
        }

        if (notIsInCondition == true && featureIterator->second) {
            truthValue = false;
            break;
        }

    }

    return truth_value;

}

void TsetlinMachine::type1Feedback(std::unordered_map<std::string, bool> observation) {

    std::string not_string = "NOT ";
    std::vector<std::string> literals = memory.getLiterals();

    if (evaluate_condition(observation, memory.getCondition()) == true) {

        for (auto feature : observation) {
            
            std::string feature_string = feature.first;
            auto featureIterator = observation.find(feature_string);

            if (featureIterator->second == true) {
                memory.memorize(feature_string);
                literals.erase(std::remove(literals.begin(), literals.end(), feature_string), literals.end());
            }

            else if (featureIterator->second == false) {
                memory.memorize(not_string + feature_string);
                literals.erase(std::remove(literals.begin(), literals.end(), not_string+feature_string), literals.end()); 
            }

        }

    }

    for (auto literal : literals) {
        memory.forget(literal);
    }

}

void TsetlinMachine::type2Feedback(std::unordered_map<std::string, bool> observation) {
    
    std::string not_string = "NOT ";

    if (evaluate_condition(observation, memory.getCondition()) == true) {
        
        for (auto feature : observation) {

            std::string feature_string = feature.first;
            auto featureIterator = observation.find(feature_string);
        
            if (featureIterator->second == false) {
                memory.always_memorize(feature_string);
            }
            else if (featureIterator->second == true) {
                memory.always_memorize(not_string + feature_string);
    
            } 
        }
    }

}

bool TsetlinMachine::classify(std::unordered_map<std::string, bool> observation, std::vector<Memory> win_rules, std::vector<Memory> loss_rules) {

    int sum = 0;

    for (auto win_rule : win_rules) {
        if (evaluate_condition(observation, win_rule.getCondition()) == true) {
            sum++;
        }
    }

    for (auto loss_rule : loss_rules) {
        if (evaluate_condition(observation, loss_rule.getCondition()) == true) {
            sum--;
        }
    }

    if (sum >= 0) {
        return true;
    }
    else {
        return false;
    }

}

