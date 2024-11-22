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

        void sendMessage(std::string message) {
            std::cout << message << "\n" << std::flush;
        
        bool interpretMessage(std::string s) {
            turn++;

            std;:string message = 

        }

        void makeMove(std::string Board) {
            pass;
        }

    public: 
        
        void run() {
            input = std::getline(std::cin, input)

            // Gets string
            while (true) {
                
                try {
                    std::string message = getMessage();
                    bool res = interpretMessage(message);
                    if (res == false) { break; }
                }
                catch {
                    std::cout << "ERROR: Could not establish I/0."
                    break;
                }
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

    int parsedBoardSize = std::stoi(inputBoardSize);

    AgentController agent = new AgentController(inputColour, inputBoardSize);

}
