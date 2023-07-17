#include "turn.h"
#include "game.h"
#include "utility.h"

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

// --------------------- Player Turn Functions --------------------
bool playerTurn(const string& playerName, vector<int>* ptr_board) {
   std::cout << playerName << "'s turn\n";
   
   int pile, stones;
   
   // Get a valid number for pile and stones from the user.
   if ((*ptr_board).size() != 1)
      pile = getInt("Which Heap? ", (*ptr_board).size(), "   Invalid heap.");
   else
      pile = 1;

   stones = getInt("How Many Stones? ",  (*ptr_board).at(pile-1),
                       "   Invalid number of stones.");
   
   // Adjust the game board and return true if the player has won.
   return adjustGameBoard(pile, stones, ptr_board); //NOTE: sending pointer
}

void swapPlayers(string& playerA, string& playerB) {
   string temp = playerA;
   playerA = playerB;
   playerB = temp;
}

void displayPlayers(const string& player1, const string& player2) {
   std::cout << "Player 1: " << player1 << "\n"; 
   std::cout << "Player 2: " << player2 << "\n";
}

// -------------------- Computer Turn Functions -------------------
bool computerTurn(vector<int>* ptr_board) {
   std::cout << COMPUTER_NAME << "'s turn\n";
   
   // Use the nim sum to determine how many stones to take from which pile.
   int pile = whichPile(*ptr_board);
   int stones = howManyStones(*ptr_board, pile);
   
   std::cout << COMPUTER_NAME << " removed " << stones
             << " from heap " << pile << ".\n";
             
   // Adjust the game board and return true if the player has won.
   return adjustGameBoard(pile, stones, ptr_board); //NOTE: sending pointer
}

int calculateNimSum(const vector<int>& board) {
   auto nimSum = board.at(0);

   for (unsigned s = 1; s < board.size(); s++)
      nimSum = nimSum ^ board.at(s); //bitwise XOR
   return nimSum;
}

int whichPile(const vector<int>& board) {
   // If the nim sum is zero, randomly select a pile.
   if (calculateNimSum(board) == 0)
      return (rand() % board.size() + 1); //between 1 and board.size()
  
   // Otherwise find the pile where removing stones will lead
   //to the nim sum becoming zero.
   int result;
   for (unsigned pile = 0; pile < board.size(); pile++) {
      // Note the variable 'pile' is indexed starting at 0.
      auto tempBoard = board;
      tempBoard.at(pile) = 0;
      if (calculateNimSum(tempBoard) <= board.at(pile)) {
         result = pile + 1;
      }
   }
   return result;
}

int howManyStones(const vector<int>& board, const int& pile) {
   // If the nim sum is zero, randomly select stones to remove from the pile.
   if (calculateNimSum(board) == 0)
      return (rand() % board.at(pile - 1) + 1);
   
   // Otherwise find the stones needed to remove from the pile 
   //to make the nim sum zero.
   auto tempBoard = board;
   tempBoard.at(pile - 1) = 0;
   return board.at(pile - 1) - calculateNimSum(tempBoard);   
}

// ------------------ Moves done Each Turn -------------------
void displayGameBoard(const vector<int>& board) {
   for (unsigned i = 0; i < board.size(); i++) {
      string extraSpace = board.at(i) < 10 ? " " : "";
      std::cout << "Heap " << i + 1 << " [" << extraSpace << board.at(i)
                << "]: " << string(board.at(i), '*') << "\n";
   }
   std::cout << "\n";
}

bool adjustGameBoard(const int& pile, const int& stones, 
                     vector<int>* ptr_board) {
   bool endGame = false;
   
   // If taking last stone(s)..
   if ((*ptr_board).size() == 1 && (*ptr_board).at(0) == stones)
      endGame = true; //end game

   // If otherwise taking all stones in pile..
   else if ((*ptr_board).at(pile - 1) == stones) 
      (*ptr_board).erase((*ptr_board).begin() + pile - 1); //remove pile

   // Otherwise, reduce pile by the given number of stones.
   else
      (*ptr_board).at(pile - 1) = (*ptr_board).at(pile - 1) - stones; 
  
   return endGame;
}


