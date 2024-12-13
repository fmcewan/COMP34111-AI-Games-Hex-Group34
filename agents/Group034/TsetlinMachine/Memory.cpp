// Imports
#include <string>
#include <algorithm>
#include <cstdlib>
#include <iostream>

// Header imports
#include "Memory.h"


Memory::Memory(): forgetValue(0), memorizeValue(0), memory({}) {}

Memory::Memory(float forgetThreshold, float memorizeThreshold, std::unordered_map<std::string, int> memory_input): 
            forgetValue(forgetThreshold), memorizeValue(memorizeThreshold), memory(memory_input) {}

std::unordered_map<std::string, int> Memory::getMemoryMap() {
    return memory;
}

float Memory::getForgetValue() {
    return forgetValue;
}

float Memory::getMemorizeValue() {
    return memorizeValue;
}

std::vector<std::string> Memory::getLiterals() {

    std::vector<std::string> literals;

    for (const auto& element : memory) {
        literals.push_back(element.first);
    }

    return literals;

}

std::vector<std::string> Memory::getCondition() {

    std::vector<std::string> condition;
    std::vector<std::string> literals = getLiterals();;

    for (auto literal : memory) {

        std::string literal_string = literal.first;
        auto literalIterator = memory.find(literal_string);

        if (literalIterator->second >= 6) {
            condition.push_back(literal_string);
        }
    }
        
    return condition;

}

void Memory::memorize(std::string literal) {

    auto literalIterator = memory.find(literal);
    double random = (double)rand()/RAND_MAX;

    if (random <= memorizeValue && literalIterator->second < 10) {
        literalIterator->second++;
    }

}

void Memory::forget(std::string literal) {

    auto literalIterator = memory.find(literal);    
    double random = (double)rand()/RAND_MAX;

    if (random <= forgetValue && literalIterator->second > 1) {
        literalIterator->second--; 
    }

}

void Memory::always_memorize(std::string literal) {
    
    auto literalIterator = memory.find(literal);

    if (literalIterator->second < 10) {
        literalIterator->second++;
    } 

}

// int main() {

//     std::unordered_map<std::string, int> memory_map = {{"four wheels", 10}, {"not four wheels", 2}, {"transports people", 9}, {"not transports people", 3}, {"wings", 1}, {"not wings", 5}, {"yellow", 1}, {"not yellow", 4}, {"blue", 6}, {"not blue", 4}};

//     memory memory = memory(0.9, 0.1, memory_map);

//     memory.memorize("Blue");
//     memory.memorize("Blue");

//    std::unordered_map<std::string, int> memory_map_2 = memory.getMemory();

//     std::cout << "Memory" << std::endl;
//     for (auto element : memory_map_2) {
//         std::cout << element.first << " " << element.second << std::endl;
//     }
//     std::cout << std::endl;

//     std::vector< std::string > literals = memory.getLiterals();

//     std::cout << "Literals" << std::endl;
//     for (auto literal : literals) {
//         std::cout << literal << std::endl;
//     }
//     std::cout << std::endl;

//     std::vector< std::string > condition = memory.getCondition();

//     std::cout << "Conditions" << std::endl;
//     for (auto literal : condition) {
//         std::cout << literal << std::endl;
//     }
//     std::cout << std::endl;

// }