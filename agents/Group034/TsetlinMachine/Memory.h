// Imports
#include <vector>
#include <unordered_map>

class Memory {

    private:
        std::unordered_map<std::string, int> memory;        

        int forgetValue;
        int memorizeValue;

    public:
        Memory();
        Memory(float forgetThreshold, float memorizeThreshold, std::unordered_map<std::string, int> memory);

        // Getters
        std::unordered_map<std::string, int> getMemoryMap();
        float getForgetValue();
        float getMemorizeValue();        
        std::vector<std::string> getLiterals();
        std::vector<std::string> getCondition();

        // Memory methods 
        void memorize(std::string literal);
        void forget(std::string literal);
        void always_memorize(std::string literal);

        // Operator overloads
        friend bool operator!=(Memory& memory1, Memory& memory2) {

            if (memory1.getMemoryMap() != memory2.getMemoryMap() 
            || memory1.getForgetValue() != memory2.getForgetValue() 
            || memory1.getMemorizeValue() != memory2.getMemorizeValue()) {
                return true;   
            }

            return false;
        }


};