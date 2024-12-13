// Default imports
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <exception>

enum messageType {
    START,
    CHANGE,
    SWAP
};

class AgentController {

    private: 
        std::stringstream input;
        std::string messageInput;
        std::string colour;
        int turn;
        int boardSize;

        std::string getMessage();
        messageType stringToEnum(std::string message);
        void sendMessage(std::string message);
        bool interpretMessage(std::string message);
        void makeMove(std::string board);

    public:
        AgentController(std::string inputColour, int boardSize);
        void run();
        static std::string opp(std::string colour);

};