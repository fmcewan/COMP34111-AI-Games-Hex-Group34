// Imports
#include <string>
#include <algorithm>
#include <cstdlib>

// Header imports
#include "Memory.h"

Memory::Memory(float forgetThreshold, float memorizeThreshold, std::unordered_map<std::string, int> memory_input): 
            forgetValue(forgetThreshold), memorizeValue(memorizeThreshold), memory(memory_input) {}

std::unordered_map<std::string, int> Memory::getMemory() {
    return memory;
}

std::vector<std::string> Memory::getLiterals() {

    std::vector<std::string> literals;
    auto key_selector = [](auto pair) { return pair.first; };

    transform(memory.begin(), memory.end(), literals.begin(), key_selector);

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

    if ((rand() % 10) + 1 <= memorizeValue && literalIterator->second < 10) {
        literalIterator->second++;
    }

}

void Memory::forget(std::string literal) {


    auto literalIterator = memory.find(literal);

    if ((rand() % 10) + 1 <= forgetValue && literalIterator->second > 1) {
        literalIterator->second--;
    }

}

void Memory::always_memorize(std::string literal) {
    
    auto literalIterator = memory.find(literal);

    if (literalIterator->second < 10) {
        literalIterator->second++;
    } 

}

int main() {

    return 0;
}