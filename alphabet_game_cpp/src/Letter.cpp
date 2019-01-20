/*
 * Letter.cpp
 *
 *  Created on: Jan 20, 2019
 *      Author: Brad Saylor
 */

#include "Letter.h"


int Letter::getNumTurnsLetter(){return this->numTurnsLetter;}

void Letter::logResult(bool result){
	if(result == true) this->vbResults.push_back(true);
	else this->vbResults.push_back(false);
	this->numTurnsLetter++;
}
