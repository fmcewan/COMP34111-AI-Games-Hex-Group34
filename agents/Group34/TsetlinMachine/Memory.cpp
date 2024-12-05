// Imports
#include <string>
#include <algorithm>
#include <cstdlib>

// Header imports
#include "Memory.h"


Memory::Memory(): forgetValue(0), memorizeValue(0), memory({}) {}

Memory::Memory(float forgetThreshold, float memorizeThreshold, std::unordered_map<std::string, int> memory_input): 
            forgetValue(forgetThreshold), memorizeValue(memorizeThreshold), memory(memory_input) {}

std::unordered_map<std::string, int> Memory::getMemory() {
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

bool operator!=(Memory& memory1, Memory& memory2) {

    if (memory1.getMemory() != memory2.getMemory() 
    || memory1.getForgetValue() != memory2.getForgetValue() 
    || memory1.getMemorizeValue() != memory2.getMemorizeValue()) {
        return true;   
    }

    return false;

}

int main() {

    return 0;
}