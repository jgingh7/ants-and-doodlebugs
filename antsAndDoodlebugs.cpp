#include "pch.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

const int GRID_LENGTH = 5; //20
const int GRID_WIDTH = 5; //20
const int INI_NUM_OF_ANTS = 0; //100
const int INI_NUM_OF_DOODLEBUGS = 25; //5
const int NUM_OF_STARVED_STEPS_FOR_DEATH = 3;

class Organism {
	int position;
	int stepsSurvived;
public:
	Organism();
	virtual void move (int direction) = 0;//pure virtual //must be virtual
	int getPosition() const;
	int getStepsSurvived() const;
	void setPosition(int newPosition);
	void setStepsSurvived(int newStepsSurvived);
	int breed(vector<int> positionsOfOrganisms);
};

class Ant : public Organism { //"o"
public:
	Ant(int newPosition);
	Ant();
	virtual void move(int direction);
};

class Doodlebug : public Organism { //"X"
	int stepsNotEaten;
public:
	Doodlebug(int newPosition);
	Doodlebug();
	virtual void move(int direction);
	void starve(vector<Doodlebug>& doodlebugs, int thisIdx);
	int getStepsNotEaten() const;
	void setStepsNotEaten(int newStepsNotEaten);
};

Organism::Organism() : position(-1), stepsSurvived(0) { }

int Organism::getPosition() const {
	return position;
}

int Organism::getStepsSurvived() const {
	return stepsSurvived;
}

void Organism::setPosition(int newPosition) {
	position = newPosition;
}

void Organism::setStepsSurvived(int newStepsSurvived) {
	stepsSurvived = newStepsSurvived;
}

int Organism::breed(vector<int> positionsOfOrganisms) {
	srand(time(NULL));
	int breedPosition, breedRespectivePosition;
	bool breedable;
	breedable = true;

	breedRespectivePosition = rand() % 4;
	breedPosition = 0;

	//0 = up
	if (breedRespectivePosition == 0) {
		for (int i = 0; i < positionsOfOrganisms.size(); i++) {
			if (positionsOfOrganisms[i] == this->getPosition() - GRID_LENGTH
				|| this->getPosition() - GRID_LENGTH < 0
				|| this->getPosition() - GRID_LENGTH == 0) {
				breedable = false;
				breed(positionsOfOrganisms);
			}
		}
		if (breedable) {
			breedPosition = this->getPosition() - GRID_LENGTH;
		}
	}

	//1 = down
	else if (breedRespectivePosition == 1) {
		for (int i = 0; i < positionsOfOrganisms.size(); i++) {
			if (positionsOfOrganisms[i] == this->getPosition() + GRID_LENGTH
				|| this->getPosition() + GRID_LENGTH > GRID_LENGTH * GRID_WIDTH) {
				breedable = false;
				breed(positionsOfOrganisms);
			}
		}
		if (breedable) {
			breedPosition = this->getPosition() - GRID_LENGTH;
		}
	}
	//2 = left
	else if (breedRespectivePosition == 2) {
		for (int i = 0; i < positionsOfOrganisms.size(); i++) {
			if (positionsOfOrganisms[i] == this->getPosition() - 1
				|| this->getPosition() % GRID_LENGTH == 1) {
				breedable = false;
				breed(positionsOfOrganisms);
			}
		}
		if (breedable) {
			breedPosition = this->getPosition() - 1;
		}
	}
	//3 = right
	else if (breedRespectivePosition == 3) {
		for (int i = 0; i < positionsOfOrganisms.size(); i++) {
			if (positionsOfOrganisms[i] == this->getPosition() + 1
				|| this->getPosition() % GRID_LENGTH == 0) {
				breedable = false;
				breed(positionsOfOrganisms);
			}
		}
		if (breedable) {
			breedPosition = this->getPosition() + 1;
		}
	}
	else {
		breedPosition = this->getPosition();
	}

	return breedPosition;
}



Ant::Ant() {
	setPosition(-1);
	setStepsSurvived(0);
}

Ant::Ant(int newPosition) {
	setPosition(newPosition);
	setStepsSurvived(0);
}

void Ant::move(int direction) {
	if (direction == 0) { //up
		setPosition(getPosition() - GRID_LENGTH);
	}
	else if (direction == 1) { //down
		setPosition(getPosition() + GRID_LENGTH);
	}
	else if (direction == 2) { //left
		setPosition(getPosition() - 1);
	}
	else {//direction ==3 //right
		setPosition(getPosition() + 1);
	}
}

Doodlebug::Doodlebug() {
	setPosition(-1);
	setStepsSurvived(0);
	stepsNotEaten = 0;
}

Doodlebug::Doodlebug(int newPosition) {
	setPosition(newPosition);
	setStepsSurvived(0);
	stepsNotEaten = 0;
}

int Doodlebug::getStepsNotEaten() const {
	return stepsNotEaten;
}

void Doodlebug::setStepsNotEaten(int newStepsNotEaten) {
	stepsNotEaten = newStepsNotEaten;
}

void Doodlebug::move(int direction) {
	if (direction == 0) { //up
		setPosition(getPosition() - GRID_LENGTH);
	}
	else if (direction == 1) { //down
		setPosition(getPosition() + GRID_LENGTH);
	}
	else if (direction == 2) { //left
		setPosition(getPosition() - 1);
	}
	else {//direction ==3 //right
		setPosition(getPosition() + 1);	
	}
}

void Doodlebug::starve(vector<Doodlebug>& doodlebugs, int thisIdx) {
	doodlebugs.erase(doodlebugs.begin() + thisIdx);
}

void showGrid(vector<Doodlebug> doodlebugs, vector<Ant> ants) {
	int positionIdx = 0;
	int position[GRID_LENGTH * GRID_WIDTH];
	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_LENGTH; j++) {
			bool emtpy = true;
			position[positionIdx] = positionIdx + 1;
			for (int z = 0; z < doodlebugs.size(); z++) {
				if (position[positionIdx] == doodlebugs[z].getPosition()) {
					cout << "X";
					emtpy = false;
				}
			}
			for (int z = 0; z < ants.size(); z++) {
				if (position[positionIdx] == ants[z].getPosition()) {
					cout << "o";
					emtpy = false;
				}
			}
			if (emtpy) {
				cout << "-";
			}
			positionIdx++;
		}
		cout << endl;
	}
}

vector<int> findAnts(vector<Ant> ants, vector<Doodlebug> doodlebugs, int doodleIdx) {
	vector<int> nearbyAntDirections;

	for (int j = 0; j < ants.size(); j++) {
		if (doodlebugs[doodleIdx].getPosition() - GRID_LENGTH == ants[j].getPosition()) {
			nearbyAntDirections.push_back(0);
		}
		else if (doodlebugs[doodleIdx].getPosition() + GRID_LENGTH == ants[j].getPosition()) {
			nearbyAntDirections.push_back(1);
		}
		else if (doodlebugs[doodleIdx].getPosition() - 1 == ants[j].getPosition()) {
			nearbyAntDirections.push_back(2);
		}
		else if (doodlebugs[doodleIdx].getPosition() + 1 == ants[j].getPosition()) {
			nearbyAntDirections.push_back(3);
		}
	}

	return nearbyAntDirections; //returns with numbers that indicate the position where nearbyants are
}


int main()
{
	string timeStepYorN;
	bool wrong, dontEnd;
	int timeCounter, positionIdx;
	int position[GRID_LENGTH*GRID_WIDTH]; //initialize grid
	vector<Ant> ants(INI_NUM_OF_ANTS);
	vector<Doodlebug> doodlebugs(INI_NUM_OF_DOODLEBUGS);

	srand(time(NULL));

	timeCounter = 0;
	dontEnd = true;

	//initialize grid positions
	vector<int> possiblePositions;
	int maxPositionNum = GRID_LENGTH * GRID_WIDTH;
	int randNum;
	for (int i = 0; i < GRID_LENGTH * GRID_WIDTH; i++) {
		possiblePositions.push_back(i + 1);
	}

	//set doodlebugPositions
	for (int i = 0; i < doodlebugs.size(); i++) {
		randNum = rand() % maxPositionNum;
		doodlebugs[i].setPosition(possiblePositions[randNum]);
		possiblePositions.erase(possiblePositions.begin() + randNum);
		maxPositionNum--;
	}

	//set antPositions
	for (int i = 0; i < ants.size(); i++) {
		randNum = rand() % maxPositionNum;
		ants[i].setPosition(possiblePositions[randNum]);
		possiblePositions.erase(possiblePositions.begin() + randNum);
		maxPositionNum--;
	}

	// show grid
	showGrid(doodlebugs, ants);

	while (dontEnd) {
		cout << "Number of Ants: " << ants.size() << endl;
		cout << "Number of Doodlebugs: " << doodlebugs.size() << endl << endl;

		wrong = true;
		while (wrong) {
			cout << "Press Enter if you want to do another time step.\n"
				<< "Type 'n' or 'N' if you want to stop" << endl;
			getline(cin, timeStepYorN);

			if (timeStepYorN.length() == 0) {
				dontEnd = true;
				timeCounter++;
				wrong = false;

				for (int i = 0; i < doodlebugs.size(); i++) {
					vector<int> nearbyAntDirections;
					nearbyAntDirections = findAnts(ants, doodlebugs, i);
					cout << "currPos: " << doodlebugs[i].getPosition() << endl;
					if (nearbyAntDirections.size() == 0) {
						if (doodlebugs[i].getStepsNotEaten() + 1 == NUM_OF_STARVED_STEPS_FOR_DEATH) {
							//starve when no ants are around and an addition of starved step is 3
							doodlebugs[i].starve(doodlebugs, i);
							i--;
						}
						else {
							vector<int> directionsToGo;
							vector<int> directionsNotToGo;

							for (int j = 0; j < 4; j++) {
								directionsToGo.push_back(j); //0 1 2 3
							}

							for (int j = 0; j < doodlebugs.size(); j++) {
								if (doodlebugs[i].getPosition() - GRID_LENGTH
									== doodlebugs[j].getPosition()
									|| doodlebugs[i].getPosition() - GRID_LENGTH <= 0) {
									directionsNotToGo.push_back(0);
								}
								else if (doodlebugs[i].getPosition() + GRID_LENGTH
									== doodlebugs[j].getPosition()
									|| doodlebugs[i].getPosition() + GRID_LENGTH > GRID_LENGTH * GRID_WIDTH) {
									directionsNotToGo.push_back(1);
								}
								else if (doodlebugs[i].getPosition() - 1
									== doodlebugs[j].getPosition()
									|| (doodlebugs[i].getPosition() - 1) % GRID_LENGTH == 0) {
									directionsNotToGo.push_back(2);
								}
								else if (doodlebugs[i].getPosition() + 1
									== doodlebugs[j].getPosition()
									|| (doodlebugs[i].getPosition() + 1) % GRID_LENGTH == 1) {
									directionsNotToGo.push_back(3);
								}
							}

							for (int j = 0; j < directionsToGo.size(); j++) {
								for (int z = 0; z < directionsNotToGo.size(); z++) {
									if (directionsToGo[j] == directionsNotToGo[z]) {
										directionsToGo.erase(directionsToGo.begin() + j);
										j--;
										break;
									}
								}
							}
								
							if (directionsToGo.size() == 0) { 
								cout << "nowhere to go" << endl;
							} //some doodlebugs dont end up here when supposed to
							else {
								int doodlebugMovingDirection = directionsToGo[rand() % directionsToGo.size()];
								doodlebugs[i].move(doodlebugMovingDirection);
							}
							cout << "nextPos: " << doodlebugs[i].getPosition() << endl;

							doodlebugs[i].setStepsNotEaten(doodlebugs[i].getStepsNotEaten() + 1);
							cout << "steps not eaten: " << doodlebugs[i].getStepsNotEaten() << endl;
							
							doodlebugs[i].setStepsSurvived(doodlebugs[i].getStepsSurvived() + 1);
							cout << "steps survived: " << doodlebugs[i].getStepsSurvived() << endl;
						}
					}
					else {
						int antEatingDirection = nearbyAntDirections[rand() % nearbyAntDirections.size()];
						doodlebugs[i].move(antEatingDirection);
						for (int j = 0; j < ants.size(); j++) {
							if (antEatingDirection == 0
								&& ants[j].getPosition() == doodlebugs[i].getPosition()) {
								ants.erase(ants.begin() + j);
								j--;
								doodlebugs[i].setStepsNotEaten(0);
							}
							else if (antEatingDirection == 1
								&& ants[j].getPosition() == doodlebugs[i].getPosition()) {
								ants.erase(ants.begin() + j);
								j--;
								doodlebugs[i].setStepsNotEaten(0);
							}
							else if (antEatingDirection == 2
								&& ants[j].getPosition() == doodlebugs[i].getPosition()) {
								ants.erase(ants.begin() + j);
								j--;
								doodlebugs[i].setStepsNotEaten(0);
							}
							else if (antEatingDirection == 3
								&& ants[j].getPosition() == doodlebugs[i].getPosition()) {
								ants.erase(ants.begin() + j);
								j--;
								doodlebugs[i].setStepsNotEaten(0);
							}
						}
						cout << "nextPos: " << doodlebugs[i].getPosition() << endl;

						doodlebugs[i].setStepsSurvived(doodlebugs[i].getStepsSurvived() + 1);
						cout << "steps survived: " << doodlebugs[i].getStepsSurvived() << endl;
					}
				}
				
				
				vector<int> positionsOfOrganisms;
				//getting positions of doodlebugs
				for (int i = 0; i < doodlebugs.size(); i++) {
					positionsOfOrganisms.push_back(doodlebugs[i].getPosition());
				}
				//getting positions of ants
				for (int i = 0; i < ants.size(); i++) {
					positionsOfOrganisms.push_back(ants[i].getPosition());
				}

				for (int i = 0; i < positionsOfOrganisms.size(); i++) {
					cout << positionsOfOrganisms[i] << " ";
				}
				cout << endl;

				
				for (int i = 0; i < ants.size(); i++) {
					int direction = rand() % 4;
					cout << "ant were in: " << ants[i].getPosition() << endl;
					
					vector<int> directionsToGo;
					vector<int> directionsNotToGo;

					for (int j = 0; j < 4; j++) {
						directionsToGo.push_back(j); //0 1 2 3
					}

					for (int j = 0; j < positionsOfOrganisms.size(); j++) {
						if (ants[i].getPosition() - GRID_LENGTH == positionsOfOrganisms[j]
							|| ants[i].getPosition() - GRID_LENGTH <= 0) {
							directionsNotToGo.push_back(0);
						}
						else if (ants[i].getPosition() + GRID_LENGTH == positionsOfOrganisms[j]
							|| ants[i].getPosition() + GRID_LENGTH > GRID_LENGTH * GRID_WIDTH) {
							directionsNotToGo.push_back(1);
						}
						else if (ants[i].getPosition() - 1 == positionsOfOrganisms[j]
							|| (ants[i].getPosition() - 1) % GRID_LENGTH == 0) {
							directionsNotToGo.push_back(2);
						}
						else if (ants[i].getPosition() + 1 == positionsOfOrganisms[j]
							|| (ants[i].getPosition() + 1) % GRID_LENGTH == 1) {
							directionsNotToGo.push_back(3);
						}
					}

					for (int j = 0; j < directionsToGo.size(); j++) {
						for (int z = 0; z < directionsNotToGo.size(); z++) {
							if (directionsToGo[j] == directionsNotToGo[z]) {
								directionsToGo.erase(directionsToGo.begin() + j);
								j--;
								break;
							}
						}
					}


					if (directionsToGo.size() == 0) {}
					else {
						int antMovingDirection = directionsToGo[rand() % directionsToGo.size()];
						ants[i].move(antMovingDirection);
					}

					cout << "ant moved to: " << ants[i].getPosition() << endl;
					
					ants[i].setStepsSurvived(ants[i].getStepsSurvived() + 1);
					cout << "ants survived for: " << ants[i].getStepsSurvived() << endl;
				}
				
				//breed doodlebugs
				positionsOfOrganisms.clear();
				for (int i = 0; i < doodlebugs.size(); i++) {
					int breedPosition;
					//getting positions of doodlebugs
					for (int j = 0; j < doodlebugs.size(); j++) {
						positionsOfOrganisms.push_back(doodlebugs[j].getPosition());
					}
					//getting positions of ants
					for (int j = 0; j < ants.size(); j++) {
						positionsOfOrganisms.push_back(ants[j].getPosition());
					}
					if (doodlebugs[i].getStepsSurvived() == 8) { //breed if survived 8 times.
						breedPosition = doodlebugs[i].breed(positionsOfOrganisms);
						doodlebugs[i].setStepsSurvived(0);
						if (breedPosition != doodlebugs[i].getPosition()) {
							cout << "new doodlebug" << endl;
							Doodlebug newDoodlebug(breedPosition);
							doodlebugs.push_back(newDoodlebug);
						}
					}
				}

				//breed ants
				positionsOfOrganisms.clear();
				for (int i = 0; i < ants.size(); i++) {
					int breedPosition;
					//getting positions of doodlebugs
					for (int j = 0; j < doodlebugs.size(); j++) {
						positionsOfOrganisms.push_back(doodlebugs[j].getPosition());
					}
					//getting positions of ants
					for (int j = 0; j < ants.size(); j++) {
						positionsOfOrganisms.push_back(ants[j].getPosition());
					}
					if (ants[i].getStepsSurvived() == 3) { //breed if survived 3 times.
						breedPosition = ants[i].breed(positionsOfOrganisms);
						ants[i].setStepsSurvived(0);
						if (breedPosition != ants[i].getPosition()) {
							Ant newAnt(breedPosition);
							ants.push_back(newAnt);
						}
					}
				}

				positionsOfOrganisms.clear();
				//getting positions of doodlebugs
				for (int i = 0; i < doodlebugs.size(); i++) {
					positionsOfOrganisms.push_back(doodlebugs[i].getPosition());
				}
				//getting positions of ants
				for (int i = 0; i < ants.size(); i++) {
					positionsOfOrganisms.push_back(ants[i].getPosition());
				}

				for (int i = 0; i < positionsOfOrganisms.size(); i++) {
					cout << positionsOfOrganisms[i] << " ";
				}
				cout << endl;
			}
			else if ((timeStepYorN == "n") || (timeStepYorN == "N")) {
				dontEnd = false;
				wrong = false;
			}
			else {
				cout << endl << "Illegal input." << endl;
			}
		}
		cout << endl;
		// show current grid
		showGrid(doodlebugs, ants);

	}
	cout << "finish" << endl;
	cout << "timeCounter: " << timeCounter << endl;
	//show the final grid

    return 0;
}
