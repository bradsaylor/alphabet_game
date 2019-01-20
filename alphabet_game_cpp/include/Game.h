/*
 * Game.h
 *
 *  Created on: Jan 20, 2019
 *      Author: Brad Saylor
 */

#ifndef GAME_H_
#define GAME_H_

//
//Classes
//

class Game{
private:
	int numTurnsGame;
	int gameLength;
public:
	Game(int gameLength);
	Game();
	void playGame();
	void setNumTurnsGame();

};

//
//Helper function declarations
//

char pickALetter(const char alphabet[26]);
char promptForResponse(char letter);
bool evaluateResponse(char letter, char response);
void logResult();
void endGame();



#endif /* GAME_H_ */
