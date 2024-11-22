// Imports
#include <string>
#include <sstream>
#include <iostream>
#include <bits/stdc++.h>

class AgentController {

   private:
        std::string input;
        std::string colour;
        int turn = 0;
        int boardSize = 11;

        AgentController(std::string agentColour, int gameBoardSize) {
            boardSize = gameBoardSize;
            colour = agentColour;
        }

        std::string getMessage() {
            return std::getline(std::cin, input);
        }

        void sendMessage() {}

        bool interpretMessag(std::string s) {
            turn++;



        }

        void makeMove(std::string Board) {

        }

    public: 
        
        void run() {
            input = std::getline()

            // Gets string
            std::string message = ""; 

        }

        }   

        static std::string opp(std::string c) {
            if (c == "R") { return "B"; }
            if (c == "B") { return "R"; }
        }

}

int main() {

    std::string inputColour;
    std::string inputBoardSize;
    
    std::cin >> inputColour;
    std::cin >> inputBoardSize;

    int in = std::stol

    AgentController agent = new AgentController(inputColour, inputBoardSize);

}
