/*
 * main.cpp
 *
 *  Created on: Jan 20, 2019
 *      Author: Brad Saylor
 */
#include <iostream>
#include <vector>

#include "Letter.h"
#include "Game.h"
#include "Turn.h"

int main(){

	Game myGame(5);
	myGame.playGame();

	return 0;
}
