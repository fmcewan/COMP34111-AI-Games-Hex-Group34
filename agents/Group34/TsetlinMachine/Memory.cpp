// Imports
#include <string>
#include <algorithm>

// Header imports
#include "Memory.h"

Memory::Memory(float forgetThreshold, float memorizeThreshold, std::unordered_map<std::string, int> memory_input): 
            forgetValue(forgetThreshold), memorizeValue(memorizeThreshold), memory(memory_input) {}

std::unordered_map<std::string, int> Memory::getMemory() {
    return memory;
}

std::vector<bool> Memory::getLiterals() {

    std::vector<bool> literals;
    auto key_selector = [](auto pair) { return pair.first; };

    transform(memory.begin(), memory.end(), literals.begin(), key_selector);

    return literals;

}

std::vector<bool> Memory::getCondition() {

    std::vector<bool> condition;
    std::vector<bool> literals = getLiterals();

    for (bool literal : literals) {
        if (memory.find(literal) >= 6) {
            condition.push_back(literal);
        }
    }

    return condition;

}

void Memory::memorize(std::string literal) {

}

void Memory::forget(std::string literal) {

}

int main() {

    return 0;
}