// Imports
#include <algorithm>
#include <iostream>

// Header imports
#include "TsetlinMachine.h"

TsetlinMachine::TsetlinMachine() {}

bool TsetlinMachine::evaluate_condition(std::unordered_map<std::string, bool> observation, std::vector<std::string> condition) {

    bool truth_value = true;

    for (auto feature : observation) {

        bool truth_value = false;

        std::string not_string = "NOT ";
        std::string feature_string = feature.first;

        bool isInCondition = (std::find(condition.begin(), condition.end(), feature_string) != condition.end());
        bool notIsInCondition = (std::find(condition.begin(), condition.end(), not_string+feature_string)) != condition.end();

        auto featureIterator = observation.find(feature_string); 

        if (isInCondition == true && featureIterator->second == false) {
            truth_value = false;
            break;
        }

        if (notIsInCondition == true && featureIterator->second) {
            truth_value = false;
            break;
        }

    }

    return truth_value;

}

int main() {

    std::unordered_map<std::string, bool> observation = {{"Four Wheels", true}, {"Transports People", true}, {"Wings", false}, {"Yellow", false}, {"Blue", true}};

    std::vector<std::string> condition = {"Four Wheels", "Transports People", "NOT Wings"};

    TsetlinMachine* machine = new TsetlinMachine();

    std::cout << machine->evaluate_condition(observation, condition);

}