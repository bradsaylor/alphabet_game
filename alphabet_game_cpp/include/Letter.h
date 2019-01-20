/*
 * Letter.h
 *
 *  Created on: Jan 20, 2019
 *      Author: Brad Saylor
 */

#ifndef LETTER_H_
#define LETTER_H_

#include <vector>

class Letter{
private:
	std::vector<bool> vbResults;
    int numTurnsLetter;
public:
    void logResult(bool result);
	int getNumTurnsLetter();
};


#endif /* LETTER_H_ */
