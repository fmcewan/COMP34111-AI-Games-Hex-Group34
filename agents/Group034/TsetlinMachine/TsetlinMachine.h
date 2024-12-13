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
        TsetlinMachine();
        TsetlinMachine(Memory memory);
        
        Memory getMemory();

        bool evaluate_condition(std::unordered_map<std::string, bool> observation, std::vector<std::string> condition);

        void type1Feedback(std::unordered_map<std::string, bool> observation);
        void type2Feedback(std::unordered_map<std::string, bool> observation);
        bool classify(std::unordered_map<std::string, bool> observation, std::vector<Memory> win_rule, std::vector<Memory> loss_rule);


};