// Imports
#include <unordered_map>
#include <string>
#include <vector>

class TsetlinMachine {

    public:
        TsetlinMachine();
        
        bool evaluate_condition(std::unordered_map<std::string, bool> observation, std::vector<std::string> condition);

        void type_1_feedback(std::unordered_map<std::string, bool> observation);
        void type_2_feedback(std::unordered_map<std::string, bool> observation);

};