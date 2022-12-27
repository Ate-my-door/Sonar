// Sonar

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <random>
#include "sonar.hpp"

int main()
{
	std::cout << "S O N A R !\n\n";
	std::cout << "Would you like to view the instructions? (yes/no)\n";
	
	if (isAnswerYes())
	{
		showInstructions();
	}
	
	while (true)
	{
		// game setup
		unsigned sonarDevices{16};
		std::array<std::array<char, 60>, 15> theBoard;
		getNewBoard(theBoard);
		std::vector<Coords> theChests{getRandomChests(3)};
		drawBoard(theBoard);
		std::vector<Coords> previousMoves;
		std::string extraSsonar;
		std::string extraSchest;
		
		while (sonarDevices > 0)
		{	
			// Start of a turn:
			
			//show sonar device/chest status
			if (sonarDevices > 1)
			{
				extraSsonar = "s";
			}
			else
			{
				extraSsonar = "";
			}
			
			if (theChests.size() > 1)
			{
				extraSchest = "s";
			}
			else
			{
				extraSchest = "";
			}
			
			std::cout << "You have " << sonarDevices << " sonar device" << extraSsonar << " left. ";
			std::cout << theChests.size() << " treasure chest" << extraSchest << " remaining.\n";
			
			Coords plMove{enterPlayerMove()};
			previousMoves.push_back(plMove); // we must track all moves so that sonar devices can be updated.
			
			std::string moveResult{makeMove(theBoard, theChests, plMove.xPos, plMove.yPos)};
			
			if (moveResult == "False")
			{
				continue;
			}
			else
			{
				if (moveResult == "You have found a sunken treasure chest!")
				{
					// update all the sonar devices currently on the map.
					for (auto it{previousMoves.begin()}; it != previousMoves.end(); it++)
					{
						int x{(*it).xPos};
						int y{(*it).yPos};
						
						makeMove(theBoard, theChests, x, y);
					}
				}
				
				drawBoard(theBoard);
				std::cout << moveResult << '\n';
			}
			
			if (theChests.size() == 0)
			{
				std::cout << "You have found all the sunken treasure chests! Congratulations and good game!\n";
				break;
			}
			
			--sonarDevices;
		}
		
		if (sonarDevices == 0)
		{
			std::cout << "We've run out of sonar devices! Now we have to turn the ship around and head\n";
			std::cout << "for home with treasure chests still out there! Game over.\n";
			std::cout << "    The remaining chests were here:\n";
			
			for (auto it{theChests.begin()}; it != theChests.end(); it++)
			{
				int x{(*it).xPos};
				int y{(*it).yPos};
				
				std::cout << "    " << x << ", " << y << "\n";
			}
		}
		
		if (!playAgain())
		{
			break;
		}
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

bool isAnswerYes()
{
	std::string s;
	
	getline(std::cin >> std::ws, s);
	return (tolower(s[0]) == 'y');
}

void showInstructions()
{
	std::cout << "Instructions:\n";
	std::cout << "You are the captain of the Simon, a treasure-hunting ship. Your current mission\n";
	std::cout << "is to find the three sunken treasure chests that are lurking in the part of the\n";
	std::cout << "ocean you are in and collect them.\n\n";
	std::cout << "To play, enter the coordinates of the point in the ocean you wish to drop a\n";
	std::cout << "sonar device. The sonar can find out how far away the closest chest is to it.\n";
	std::cout << "For example, the d below marks where the device was dropped, and the 2's\n";
	std::cout << "represent distances of 2 away from the device. The 4's represent\n";
	std::cout << "distances of 4 away from the device.\n\n";
	std::cout << "    444444444\n";
	std::cout << "    4       4\n";
	std::cout << "    4 22222 4\n";
	std::cout << "    4 2   2 4\n";
	std::cout << "    4 2 d 2 4\n";
	std::cout << "    4 2   2 4\n";
	std::cout << "    4 22222 4\n";
	std::cout << "    4       4\n";
	std::cout << "    444444444\n";
	std::cout << "Press enter to continue...\n";
	
	std::string s;
	getline(std::cin, s);
	
	std::cout << "For example, here is a treasure chest (the c) located a distance of 2 away\n";
	std::cout << "from the sonar device (the d):\n\n";
	std::cout << "    22222\n";
	std::cout << "    c   2\n";
	std::cout << "    2 d 2\n";
	std::cout << "    2   2\n";
	std::cout << "    22222\n\n";
	std::cout << "The point where the device was dropped will be marked with a 2.\n\n";
	std::cout << "The treasure chests don't move around. Sonar devices can detect treasure\n";
	std::cout << "chests up to a distance of 9. If all chests are out of range, the point\n";
	std::cout << "will be marked with O\n\n";
	std::cout << "If a device is directly dropped on a treasure chest, you have discovered\n";
	std::cout << "the location of the chest, and it will be collected. The sonar device will\n";
	std::cout << "remain there.\n\n";
	std::cout << "When you collect a chest, all sonar devices will update to locate the next\n";
	std::cout << "closest sunken treasure chest.\n";
	std::cout << "Press enter to continue...\n";
	
	getline(std::cin, s);
	
	std::cout << '\n';
}

void getNewBoard(std::array<std::array<char, 60>, 15>& board)
{
	std::random_device rd;
	std::uniform_int_distribution<int> dist(0, 1);
	
	for (int y{0}; y < 15; y++)
	{
		for (int x{0}; x < 60; x++)
		{
			board[y].at(x) = dist(rd) ? '`' : '~';
		}
	}
}

void drawBoard(const std::array<std::array<char, 60>, 15>& board)
{
	// Draw the board data structure.
	std::string hline{"    "};
	
	for (int i{1}; i <= 5; i++)
	{
		hline += "         " + std::to_string(i);
	}
	
	// print the numbers across the top
	std::cout << hline << '\n';
	
	std::string nums{""};
	
	for (int i{0}; i < 6; i++)
	{
		nums += "0123456789";
	}
	
	std::cout << "   " << nums << "\n\n";
	std::string extraSpace;
	
	// print each of the 15 rows
	for (unsigned i{0}; i < 15; i++)
	{
		// single-digit numbers need to be padded with an extra space
		if (i < 10)
		{
			extraSpace = " ";
		}
		else
		{
			extraSpace = "";
		}
		
		std::cout << extraSpace << std::to_string(i) << ' ' << getRow(board, i) << ' ' << std::to_string(i) << '\n';
	}
	
	std::cout << '\n';
	std::cout << "   " << nums << '\n';
	std::cout << hline << '\n';
}

std::string getRow(const std::array<std::array<char, 60>, 15>& board, unsigned row)
{
	// Return a string from the board data structure at a certain row.
	std::string boardRow{""};
	
	for (int i = 0; i < 60; i++)
	{
		boardRow += board[row].at(i);
	}
	
	return boardRow;
}

std::vector<Coords> getRandomChests(unsigned numChests)
{
	// Create a vector of chest data structures
	std::vector<Coords> chests;
	std::random_device rd;
	std::uniform_int_distribution<int> dist;
	
	while (chests.size() < numChests)
	{
		dist = std::uniform_int_distribution<int> (0, 14);
		int y{dist(rd)};
		dist = std::uniform_int_distribution<int> (0, 59);
		int x{dist(rd)};
		Coords chest{y, x};
		
		if(std::find(chests.begin(), chests.end(), chest) != chests.end())
		{
			continue;
		}
		else
		{
			chests.push_back(chest);
		}
	}
	
	return chests;
}

Coords enterPlayerMove()
{
	// Let the player type in his move.
	std::cout << "Where do you want to drop the next sonar device? (0-59 0-14) (or type quit)\n";
	std::string movx;
	std::string movy;
	int x, y;
	
	while(true)
	{
		std::cin >> std::ws >> movx;
		movx.erase(0, std::min(movx.find_first_not_of('0'), movx.size()-1));
		
		if (stringToLower(movx) == "quit")
		{
			quit();
		}
		
		getline(std::cin >> std::ws, movy);
		movy.erase(0, std::min(movy.find_first_not_of('0'), movy.size()-1));
		
		if (stringToLower(movy) == "quit")
		{
			quit();
		}
		
		if (isNum(movx) && isNum(movy))
		{
			movx = movx.substr(0, 4);
			movy = movy.substr(0, 4);
			x = stoi(movx);
			y = stoi(movy);
			
			if (isValidMove(x, y))
			{
				Coords m{y, x};
				return m;
			}
		}
		
		std::cout << "Enter a number from 0 to 59, a space, then a number from 0 to 14.\n";
	}
}

bool isValidMove(const int& xp, const int& yp)
{
	// Return true if the coordinates are on the board, otherwise false.
	return ((xp >= 0) && (xp <= 59) && (yp >= 0) && (yp <= 14));
}

bool isNum(const std::string& s)
{
	for (auto it{s.begin()}; it != s.end(); it++)
	{
		if (!isdigit(*it))
		{
			return false;
		}
	}
	
	return true;
}

std::string stringToLower(std::string s)
{
	for (auto it{s.begin()}; it != s.end(); it++)
	{
		*it = tolower(*it);
	}
	
	return s;
}

std::string makeMove(std::array<std::array<char, 60>, 15>& board, std::vector<Coords>& chests, int x, int y)
{
	// Change the board data structure with a sonar device character. Remove treasure chests
	// from the chests vector as they are found. Return "False" if this is an invalid move.
	// Otherwise, return the string of the result of this move.
	if (!isValidMove(x, y))
	{
		return "False";
	}
	
	int smallestDistance{100}; // any chest will be closer than 100.
	int distance;
	
	for (auto it{chests.begin()}; it != chests.end(); it++)
	{
		int cx{(*it).xPos};
		int cy{(*it).yPos};
		
		if (static_cast<int>(abs(cx - x)) > static_cast<int>(abs(cy - y)))
		{
			distance = static_cast<int>(abs(cx - x));
		}
		else
		{
			distance = static_cast<int>(abs(cy - y));
		}
		
		if (distance < smallestDistance)
		{
			smallestDistance = distance;
		}
	}
	
	if (smallestDistance == 0)
	{
		// xy is directly on a treasure chest!
		Coords delChest{y, x};
		chests.erase(std::remove(chests.begin(), chests.end(), delChest), chests.end());
		return "You have found a sunken treasure chest!";
	}
	else
	{
		if (smallestDistance < 10)
		{
			board[y][x] = '0' + smallestDistance;
			return ("Treasure detected at a distance of " + std::to_string(smallestDistance) + " from the sonar device.");
		}
		else
		{
			board[y][x] = 'O';
			return "Sonar did not detect anything. All treasure chests out of range.";
		}
	}
}

bool playAgain()
{
	// This function returns true if the player wants to play again, otherwise it returns false.
	std::string s;
	std::cout << "Do you want to play again? (yes or no)\n";
	getline(std::cin >> std::ws, s);
	
	if (s == "")
	{
		return false;
	}
	else
	{
		return (tolower(s[0]) == 'y');
	}
}

void quit()
{
	std::cout << "Thanks for playing!\n";
	std::exit(EXIT_SUCCESS);
}
