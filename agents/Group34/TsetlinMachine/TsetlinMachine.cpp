// Imports
#include <algorithm>
#include <iostream>

// Header imports
#include "TsetlinMachine.h"

TsetlinMachine::TsetlinMachine(Memory memoryInput, float memorizeValue, float forgetValue) {

    Memory defaultMemory = Memory(forgetValue, memorizeValue, {});

    if (memoryInput != defaultMemory)  {
        memory = memoryInput;
    } 
    else {
        memory = Memory(forgetValue, memorizeValue, {});
    }

}

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
    std::vector<std::string> remaining_literals = memory.getLiterals();
    
    if (evaluate_condition(observation, memory.getCondition()) == true) {

        for (auto feature : observation) {
            
            std::string feature_string = feature.first;
            auto featureIterator = observation.find(feature_string);

            if (featureIterator->second == true) {
                memory.memorize(feature_string);
                remaining_literals.erase(std::remove(remaining_literals.begin(), remaining_literals.end(), feature_string), remaining_literals.end());
            }

            else if (featureIterator->second == false) {
                memory.memorize(not_string + feature_string);
                remaining_literals.erase(std::remove(remaining_literals.begin(), remaining_literals.end(), not_string+feature_string), remaining_literals.end()); 
            }

        }

    }

    for (auto literal : remaining_literals) {
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
            else if (featureIterator->second == false) {
                memory.always_memorize("NOT " + feature_string);
            } 
        }
    }

}

int main() {


}