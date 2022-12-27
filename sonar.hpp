#ifndef SONAR_HPP
#define SONAR_HPP

struct Coords
{
	int yPos;
	int xPos;
	
	bool operator==(const Coords& i)
	{
		return ((*this).xPos == i.xPos && (*this).yPos == i.yPos);
	}
};

bool isAnswerYes();
void showInstructions();
void getNewBoard(std::array<std::array<char, 60>, 15>&);
void drawBoard(const std::array<std::array<char, 60>, 15>&);
std::string getRow(const std::array<std::array<char, 60>, 15>&, unsigned);
std::vector<Coords> getRandomChests(unsigned);
Coords enterPlayerMove();
bool isValidMove(const int& x, const int& y);
bool isNum(const std::string&);
std::string stringToLower(std::string);
std::string makeMove(std::array<std::array<char, 60>, 15>&, std::vector<Coords>&, int, int);
bool playAgain();
void quit();

#endif
