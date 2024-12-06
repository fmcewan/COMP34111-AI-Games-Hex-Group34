// Imports
#include <unordered_map>
#include <string>
#include <vector>

// Header imports
#include "Memory.h"

class TsetlinMachine {

    private:
        Memory memory;

    public:
        TsetlinMachine(Memory memory);
        
        bool evaluate_condition(std::unordered_map<std::string, bool> observation, std::vector<std::string> condition);

        void type1Feedback(std::unordered_map<std::string, bool> observation);
        void type2Feedback(std::unordered_map<std::string, bool> observation);
        std::string classify(std::unordered_map<std::string, bool> observation, std::vector<std::vector<std::string>> conditions);


};