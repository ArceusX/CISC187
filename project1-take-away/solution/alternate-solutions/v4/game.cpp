#include "game.h"
#include "turn.h"
#include "utility.h"

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

void playTakeAway(bool defaultGame, int piles, int stones) {
   // Use the same board for each replay.
   vector<int> gameBoard = generateGameBoard(piles, stones);

   if (defaultGame) {
      // Ask for player names.
      string player1 = getString("First Player Name: ");
      string player2 = getString("Second Player Name: ");
      
      // Continue to play as long as user wishes to play again.
      while (playOneGame(player1, player2, gameBoard))
         std::cout << "\n";
   }
   else {
      // Ask for human player name.
      string humanName = getString("Human Player Name: ");
      
      // Continue to play as long as user wishes to play again.
      while (playOneGame(humanName, gameBoard))
         std::cout << "\n";
   }
}

bool playOneGame(const string& humanName, vector<int> gameBoard) {
   //Prep for game.
   bool humanTurn = false;
   bool wonGame = false;

   //Starting game ..
   while (!wonGame) {
      humanTurn = !humanTurn; //first turn is human turn
      displayGameBoard(gameBoard);
      
      if (humanTurn)
         wonGame = playerTurn(humanName, &gameBoard); //send address
      else
         wonGame = computerTurn(&gameBoard); //send address
   }
   std::cout << (humanTurn? humanName : COMPUTER_NAME) << " wins!!\n";
   return playAgain();
}

bool playOneGame(const string& player1, const string& player2,
                       vector<int> gameBoard) { 
   //Prep for game.
   string playerA = player1;
   string playerB = player2;

   //Starting game ..
   while (true) {
      displayPlayers(player1, player2);
      displayGameBoard(gameBoard);
      
      if (playerTurn(playerA, &gameBoard)) //send address
         break;
      
      swapPlayers(playerA, playerB);
   }
   std::cout << playerA << " wins!!\n";
   return playAgain();
}

vector<int> generateGameBoard(int piles, int stones) {
   // Return a vector where each index represents a pile and the value at
   //each index represents the number of stones in the corresponding pile.
   
   // If the user didn't specify number of piles (piles = 0), make it random.
   if (!piles)
      piles = (rand() % MAX_PILES + 1); // between 1-MAX_PILES
   
   vector<int> board (piles, stones);
   
   // If the user didn't specify number of stones in each pile (stones = 0),
   // make them random.
   if (!stones)
      for (int n = 0; n < piles; n++)
         board.at(n) = (rand() % MAX_STONES) + 1; // between 1-MAX_STONES 

   return board;
}

bool playAgain() {   
   while (true) {
      string response = getString("Play another game? [y/n] ");
      if (response == "y")
         return true;
      if (response == "n")
         return false;
      std::cout << "Enter [y/n]. Try again.\n";
   }
}

