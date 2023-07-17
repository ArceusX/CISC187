#pragma once

#include <string>
#include "node.h"

void Game20Questions(const char* inFile);
bool getYesNo();
std::string getInput();
void learnNew(Node* current);