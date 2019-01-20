/*
 * Game.cpp
 *
 *  Created on: Jan 20, 2019
 *      Author: Brad Saylor
 */

#include <iostream>
#include <cstdlib>
#include <time.h>

#include "Game.h"

//
//Game:: methods
//

Game::Game(){
	this->gameLength = 10;
	this->numTurnsGame = 0;
}

Game::Game(int gameLength){
    this->gameLength = gameLength;
    this->numTurnsGame = 0;
}

void Game::setNumTurnsGame(){
	this->numTurnsGame++;
}

void Game::playGame(){

	//seed rand()
	srand (time(NULL));

	int numTurns = 0;
	const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
	char letter, input;


	//Game play loop
	while(numTurns < this->gameLength)
	{
		letter = pickALetter(alphabet);
		input = promptForResponse(letter);
		if(evaluateResponse(letter, input) == true) std::cout << "\nthat's correct!!";
		else std::cout << "\nthat's incorrect";
		logResult();

		numTurns++;
	}

	endGame();
}

//
//Game helper functions
//

char pickALetter(const char alphabet[26]){
    return alphabet[rand() % 26];
}

char promptForResponse(char letter){
	char input;

	std::cout << "Type the letter " << letter << ":";
	std::cin >> input;
	return input;
}

bool evaluateResponse(char letter, char response){
	if(letter == response) return true;
	else return false;
}

void logResult(){

}

void endGame(){
    std::cout << "\nThanks for playing\n";
}
