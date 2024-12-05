// Imports
#include <vector>
#include <unordered_map>

class Memory {

    private:

        std::unordered_map<std::string, int> memory;        
        float forgetValue;
        float memorizeValue; 

    public:
        Memory(float forget_threshold, float memorize_threshold, std::unordered_map<std::string, int> memory);

        // Getters
        std::unordered_map<std::string, int> getMemory();        
        std::vector<std::string> getLiterals();
        std::vector<std::string> getCondition();

        // Memory methods 
        void memorize(std::string literal);
        void forget(std::string literal);
        void always_memorize(std::string literal);

};