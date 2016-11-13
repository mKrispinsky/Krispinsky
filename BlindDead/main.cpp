/*
   COPYRIGHT (C) 2016 Matthew Krispinsky (3162194) All rights reserved.
   CSI project 2 and 3 - Blind Dead
   Author.  Matthew Krispinsky
   Version. 1.01 11.14.2016.
   Purpose: Place a description here...
*/

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<cctype>
#include<string>
#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::fstream;
using std::ifstream;
using std::string;

//gameArray indicies
//gameArray[0] = players current room
const int CURRENT_ROOM_INDEX = 0;
//gameArray[1] = current room of zombie
const int ZOMBIE_ROOM_INDEX = 1;
//gameArray[2]
const int NUM_BULLETS_INDEX = 2;
//gameArray[3]
const int NUM_ROOMS_INDEX = 3;
//boolean whether player has grail or not
const int HAVE_GRAIL_INDEX = 4;

//roomArray indices
//roomArray[gameArray[CURRENT_ROOM_INDEX]][4] = 1 or 0 if the player is
//	or is not in the current room
const int PLAYER_INDEX = 4;
//roomArray[gameArray[ZOMBIE_ROOM_INDEX]][5] = 1, tracks where the zombie is
const int ZOMBIE_INDEX = 5;
//roomArray[room][6] = the room that the grail is in should be marked 1, all others 0
const int GRAIL_INDEX = 6;
// the number of rooms and number of bullets to fend off the zombies
const int MAX_ROOMS = 11;
const int MAX_BULLETS = 6;

//PART 1A prototypes
//reset simply resets the primary game variables
void reset(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail);
//print game instructions
void instructions(ifstream &);
//print layout of game memory
void printMemory(int gameArray[],int roomArray[][7]);
// the menu (which calls functions printMemory and instructions)
bool menu(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail, int gameArray[],int roomArray[][7], ifstream &);

//PART 1B prototypes
//read in the input file for the map
void readMaze(int roomArray[][7], int gameArray[5], ifstream &);
//return a random room
int getRandomRoom(int gameArray[5]);
//place the zombie
void placeZombie(int roomArray[][7], int gameArray[5]);
//place the grail
void placeGrail(int roomArray[][7], int gameArray[5]);
// the setup function
void setup(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail, int roomArray[][7], int gameArray[5], ifstream &);

bool validateInput(int, int, int, string);

//PART 2 prototypes

bool checkZombie(int roomArray[][7], int);

bool checkGrail(int roomArray[][7], int);

bool checkNearZombie(int roomArray[][7], int);

bool checkNearGrail(int roomArray[][7], int);

int winOrLose(int roomArray[][7], int&, bool);

void showConnectedRooms(int roomArray[][7]);

bool isConnected(int roomArray[][7], int);
//PART 3 prototypes

int main()
{
	// these variables are passed throughout this program
	int roomArray[MAX_ROOMS][7] = {},
	    gameArray[5] = {},
	    currentRoom = 0,
       zombieRoom = 0,
       numBullets = 0,
       numRooms = 0,
       menuSelection = 0;
   bool haveGrail = false;
   ifstream iFile;


   reset(currentRoom, zombieRoom, numBullets, numRooms, haveGrail);

   readMaze(roomArray, gameArray, iFile);

   if(menu(currentRoom, zombieRoom, numBullets, numRooms, haveGrail, gameArray, roomArray, iFile))
   {

   }


	return 0;
}
// build your functions here. Don't forget your pre and post conditions
void reset(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail)
{
    currentRoom = 0, zombieRoom = 0, numBullets = 0, numRooms = 0;
    haveGrail = false;
}

void instructions(ifstream &iFile)
{
    iFile.open("instructions.txt");
    string line;
    while (getline(iFile, line))
        cout << line << endl;
    iFile.close();
}

void printMemory(int gameArray[],int roomArray[][7])
{
    cout << "Game Array:\n\t[current][bullets][  rooms]" << endl;
    cout << "\t[";
    if (gameArray[0] > 9)
        cout << "     ";
    else
        cout << "      ";
    cout << gameArray[0] << "][";
    if (gameArray[2] > 9)
        cout << "     ";
    else
        cout << "      ";
    cout << gameArray[2] << "][";
    if (gameArray[3] > 9)
        cout << "     ";
    else
        cout << "      ";
    cout << gameArray[3] << "]";

    cout << "\n\nRoom Array:\n" << "           [ north][ south]"
    << "[  west][  east][player][zombie][ grail]" << endl;
    for (int i = 0; i < gameArray[3]; i++)
    {
        cout << "   [R";
        if (i + 1 < 10)
            cout << " ";
        cout << i + 1 << "] ->";
        for (int j = 0; j < 7; j++)
        {
            cout << "[    ";
            if(roomArray[i][j] < 10)
                cout << " ";
            cout << roomArray[i][j] << "]";
        }
        cout << endl;
    }


}

bool menu(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail, int gameArray[],int roomArray[][7], ifstream &iFile)
{
    int input = 1;
    do
    {
        cout << "\tEnter, if you dare..." << endl
        << "*** THE TOMB OF THE BLIND DEAD ***\n\n"
        << "\t\tMain Menu" << endl << "1. Instructions\n"
        << "2. Begin\n3. Exit" << endl << endl << "Enter Menu Selection: ";

        do
        {
            cin >> input;
        }
        while(validateInput(input, 1, 3, "Try again..."));
        switch (input)
        {
        case 1:
            instructions(iFile);
            break;
        case 2:
            setup(currentRoom, zombieRoom, numBullets, numRooms, haveGrail, roomArray, gameArray, iFile);
            printMemory(gameArray, roomArray);
            break;
        case 3:
            return false;
            break;
        }
    }
    while(input == 1);
}

bool validateInput(int userChoice, int range1, int range2, string message)
{
  bool goodOrNot = false;
  if ((cin.fail()) || ((userChoice < range1) || (userChoice > range2)))
  {
 	cout << message << endl;
    goodOrNot = true;
  }
  cin.clear();
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return goodOrNot;
}

void readMaze(int roomArray[][7], int gameArray[5], ifstream &iFile)
{
    iFile.open("easyMaze.txt");
    iFile >> gameArray[3];
    for(int i = 0; i < gameArray[3]; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            iFile >> roomArray[i][j];
        }
        string boop;
        getline(iFile, boop);
    }
    iFile.close();
}

int getRandomRoom(int gameArray[5])
{
    return rand() % gameArray[3];
}

void placeZombie(int roomArray[][7], int gameArray[5])
{
    int x = getRandomRoom(gameArray);
    while (x < (gameArray[3] / 2))
    {
        x = getRandomRoom(gameArray);
    }
    roomArray[x][5] = 1;
}

void placeGrail(int roomArray[][7], int gameArray[5])
{
    int x = getRandomRoom(gameArray);
    while (x < (gameArray[3] / 2))
    {
        x = getRandomRoom(gameArray);
    }
    roomArray[x][6] = 1;
}

void setup(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail, int roomArray[][7], int gameArray[5], ifstream &iFile)
{
    srand(time(NULL));
    currentRoom = 1;
    haveGrail = false;
    numBullets = 6;
    readMaze(roomArray, gameArray, iFile);
    placeZombie(roomArray, gameArray);
    placeGrail(roomArray, gameArray);

    gameArray[0] = currentRoom;
    gameArray[2] = numBullets;

}

bool checkZombie(int roomArray[][7], int x)
{
    return (roomArray[x][5] == 1);
}

bool checkGrail(int roomArray[][7], int x)
{
    return (roomArray[x][6] == 1);
}

bool checkNearZombie(int roomArray[][7], int x)
{
    for(int i = 0; i < 4; i++)
    {
        if(checkZombie(roomArray, roomArray[x][i] - 1))
            return true;
    }
    return false;
}

bool checkNearGrail(int roomArray[][7], int x)
{
    for(int i = 0; i < 4; i++)
    {
        if(checkGrail(roomArray, roomArray[x][i] - 1))
            return true;
    }
    return false;
}

int winOrLose(int roomArray[][7], int &currentRoom, bool haveGrail)
{
    currentRoom = -1;
    int room = 0;
    while(roomArray[room][4] != 1)
        room++;
    if (room == 0 && haveGrail)
        return 0;
    if (roomArray[room][5] == 1)
        return 1;
}

void showConnectedRooms(int roomArray[][7])
{
    int room = 0;
    while(roomArray[room][4] != 1)
        room++;
    cout << "Connected rooms: ";
    for(int i = 0; i < 4; i++)
        if (roomArray[room][i] > 0)
            cout << roomArray[room][i] << " ";
    cout << endl;
}

bool isConnected(int roomArray[][7], int x)
{
    int room = 0;
    while(roomArray[room][4] != 1)
        room++;
    for (int i = 0; i < 4; i++)
    {
        if(roomArray[room][i] = x)
            return true;
    }
    return false;
}
