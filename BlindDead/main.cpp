/*
   COPYRIGHT (C) 2016 Matthew Krispinsky (3162194) All rights reserved.
   CSI project 2 and 3 - Blind Dead
   Author.  Matthew Krispinsky
   Version. 1.01 11.14.2016.
   Purpose: This code implements the start of the game Blind Dead. This is the entire project, that
   is both project 2 and 3. There are some slight errors throughout the entire project. Realistically,
   they would not exist. Unfortunately, things such as showing the correct connected rooms and also moving into
   said connected rooms. Everything compiles and every other function minus these two/three work as expected.
*/

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<cctype>
#include<string>
#include<limits>
#include <cmath>

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
// validates the input to make sure nothing is entered incorrectly
bool validateInput(int, int, int, string);

//PART 2 prototypes
// checks to see if the zombie is in the room specified by the parameter
bool checkZombie(int roomArray[][7], int);
// checks to see if the grail is in the room specified by the parameter
bool checkGrail(int roomArray[][7], int);
// uses checkZombie() to see if the zombie is in a room adjacent
bool checkNearZombie(int roomArray[][7], int);
// uses checkGrail() to see if the grail is in a room adjacent
bool checkNearGrail(int roomArray[][7], int);
// shows the user they have won or lost the game
int winOrLose(int roomArray[][7], int&, bool);
// show the user all rooms connected to the current one
void showConnectedRooms(int roomArray[][7]);
// tests to see if a room is connected to the current one
bool isConnected(int roomArray[][7], int);
//PART 3 prototypes

void moveRoom(int roomArray[][7], int gameArray[], int, bool &);

void shootRoom(int roomArray[][7], int gameArray[], int);

void moveZombie(int roomArray[][7], int gameArray[]);

bool validateSelection(string);

void doSelection(string select, int roomArray[][7], int gameArray[], bool &haveGrail, int &currentRoom);

void waitForMove(int roomArray[][7], int gameArray[]);

void checkroom(int gameArray[],int roomArray[][7], bool &haveGrail, int &currentRoom, int x);

void running(int gameArray[], int roomArray[][7], bool &haveGrail, int &currentRoom);

int main()
{
    int roomArray[MAX_ROOMS][7] = {},
	// these variables are passed throughout this program
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

   menu(currentRoom, zombieRoom, numBullets, numRooms, haveGrail, gameArray, roomArray, iFile);

	return 0;
}
// build your functions here. Don't forget your pre and post conditions

//reset simply resets the primary game variables
//takes in primary game variables by reference and sets them all to zeros and falses
void reset(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail)
{
    currentRoom = 0, zombieRoom = 0, numBullets = 0, numRooms = 0;
    haveGrail = false;
}
//simply prints out game instructions, only taking in the input file stream
void instructions(ifstream &iFile)
{
    iFile.open("instructions.txt");
    string line;
    while (getline(iFile, line))
        cout << line << endl;
    iFile.close();
}
//takes in both the game array and the room array
//correctly formats all values and puts them in their respected "arrays"
void printMemory(int gameArray[],int roomArray[][7])
{
    cout << "Game Array:\n\t[current][bullets][  rooms]" << endl;
    cout << "\t[";
    if (gameArray[CURRENT_ROOM_INDEX] > 9)
        cout << "     ";
    else
        cout << "      ";
    cout << gameArray[CURRENT_ROOM_INDEX] << "][";
    if (gameArray[NUM_BULLETS_INDEX] > 9)
        cout << "     ";
    else
        cout << "      ";
    cout << gameArray[NUM_BULLETS_INDEX] << "][";
    if (gameArray[NUM_ROOMS_INDEX] > 9)
        cout << "     ";
    else
        cout << "      ";
    cout << gameArray[NUM_ROOMS_INDEX] << "]";

    cout << "\n\nRoom Array:\n" << "           [ north][ south]"
    << "[  west][  east][player][zombie][ grail]" << endl;
    for (int i = 0; i < gameArray[NUM_ROOMS_INDEX]; i++)
    {
        cout << "   [R";
        if (i + 1 < 10)
            cout << " ";
        cout << i + 1 << "] ->";
        for (int j = 0; j < 7; j++)
        {
            cout << "[    ";
            if(roomArray[i][j] < 9)
                cout << " ";
            if(j < 4)
                cout << roomArray[i][j] + 1 << "]";
            else
                cout << roomArray[i][j] << "]";
        }
        cout << endl;
    }


}
//menu is the main function, taking in basically all game variables
//will call necessary functions depending on the case the user chose
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
//takes in the userChoice
//makes sure the input is valid
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
//takes in roomArray, gameArray, and the input file stream
//reads in the given maze that was put in a respected text document
void readMaze(int roomArray[][7], int gameArray[5], ifstream &iFile)
{
    iFile.open("easyMaze.txt");
    iFile >> gameArray[NUM_ROOMS_INDEX];
    for(int i = 0; i < gameArray[NUM_ROOMS_INDEX]; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            iFile >> roomArray[i][j];
            roomArray[i][j]--;
        }
        string boop; //arbitrary name
        getline(iFile, boop);
    }
    iFile.close();
}
//simply takes in gameArray
//returns a random room
int getRandomRoom(int gameArray[5])
{
    return rand() % gameArray[NUM_ROOMS_INDEX];
}
//takes in both the roomArray, gameArray
//places zombie in randomly placed room from getRandomRoom
void placeZombie(int roomArray[][7], int gameArray[5])
{
    int x = getRandomRoom(gameArray);
    while (x < (gameArray[NUM_ROOMS_INDEX] / 2))
    {
        x = getRandomRoom(gameArray);
    }
    roomArray[x][ZOMBIE_INDEX] = 1;
}
//takes in both the roomArray, gameArray
//places grail in randomly placed room from getRandomRoom
void placeGrail(int roomArray[][7], int gameArray[5])
{
    int x = getRandomRoom(gameArray);
    while (x < (gameArray[NUM_ROOMS_INDEX] / 2))
    {
        x = getRandomRoom(gameArray);
    }
    roomArray[x][GRAIL_INDEX] = 1;
}
//takes all necessary game variables
//sets currentRoom to 1, haveGrail to false, numBullets to MAX_BULLETS
//also sets the various current room index and num bullet index to their variables
void setup(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail, int roomArray[][7], int gameArray[5], ifstream &iFile)
{
    srand(time(NULL));
    currentRoom = 1;
    haveGrail = false;
    numBullets = 6;
    readMaze(roomArray, gameArray, iFile);
    placeZombie(roomArray, gameArray);
    placeGrail(roomArray, gameArray);

    gameArray[CURRENT_ROOM_INDEX] = currentRoom;
    gameArray[NUM_BULLETS_INDEX] = numBullets;
    running(gameArray, roomArray, haveGrail, currentRoom);
}
//takes in roomArray and an arbitrary room
//returns a bool of whether the zombie is in that room
bool checkZombie(int roomArray[][7], int x)
{
    return (roomArray[x][ZOMBIE_INDEX] == 1);
}
//takes in roomArray and an arbitrary room
//returns a bool of whether the grail is in that room
bool checkGrail(int roomArray[][7], int x)
{
    return (roomArray[x][GRAIL_INDEX] == 1);
}
//takes in roomArray and an arbitrary room
//returns a bool of whether the zombie is in an adjacent room to that
bool checkNearZombie(int roomArray[][7], int x)
{
    for(int i = 0; i < 4; i++)
    {
        if(checkZombie(roomArray, roomArray[x][i] - 1))
            return true;
    }
    return false;
}
//takes in roomArray and an arbitrary room
//returns a bool of whether the grail is in an adjacent room to that
bool checkNearGrail(int roomArray[][7], int x)
{
    for(int i = 0; i < 4; i++)
    {
        if(checkGrail(roomArray, roomArray[x][i] - 1))
            return true;
    }
    return false;
}
//takes in roomArray, currentRoom and haveGrail
//returns a 0 if they have won, a -1 if they have lost
int winOrLose(int roomArray[][7], int &currentRoom, bool haveGrail)
{
    currentRoom = -1;
    int room = 0;

    while(roomArray[room][PLAYER_INDEX] != 1)
        room++;

    while(roomArray[room][PLAYER_INDEX] != 1)
        room++;
    if (room == 0 && haveGrail)
        return 0;
    if (roomArray[room][ZOMBIE_INDEX] == 1)
        return 1;
}
//takes in just the roomArray
//prints out the connected rooms
void showConnectedRooms(int roomArray[][7])
{
    int room = 0;
    while(roomArray[room][PLAYER_INDEX] != 1)
        room++;
    cout << "Connected rooms: ";
    for(int i = 0; i < MAX_ROOMS; i++)
    {
        if(isConnected(roomArray, i))
            cout << i + 1 << " ";
    }
    cout << endl;
}
//takes in roomArray and an arbitrary room
//returns a bool of whether the room is connected to another room
bool isConnected(int roomArray[][7], int x)
{
    int room = 0;
    while(roomArray[room][PLAYER_INDEX] != 1)
        room++;
    for (int i = 0; i < 4; i++)
    {
        if(roomArray[room][i] = x)
            return true;
    }
    return false;
}

//end of Part I and Part II
//Part III to come shortly

//takes in all of our variables being kept tracked of
//is used to move into adjacent rooms that are allowed
void moveRoom(int gameArray [], int roomArray[][7], int x, bool &haveGrail, int &currentRoom)
{
    int room = 0;
    while(roomArray[room][PLAYER_INDEX] != 1)
        room++;
    if(isConnected(roomArray, x))
    {
        roomArray[room][PLAYER_INDEX] = 0;
        roomArray[x][PLAYER_INDEX] = 1;
        gameArray[CURRENT_ROOM_INDEX] = x;
    }
    else
        cout << "You've walked into a wall, cannot walk here\n";
    if (gameArray[GRAIL_INDEX] = x)
        haveGrail = true;
    if (haveGrail)
    {
        for(int i = 0; i < MAX_ROOMS; i++)
        {
            roomArray[i][GRAIL_INDEX] = 0;
        }
        roomArray[x][GRAIL_INDEX] = 1;
    }
    if (winOrLose(roomArray, currentRoom, haveGrail) == 0)
    {
        cout << "You have won the game!\n";
        exit(0);
    }
}

//takes in roomArray, game array and an arbitrary room
//shoots into an allowed adjacent room and decrements num bullets
void shootRoom(int roomArray[][7], int gameArray[], int x)
{
    int room = 0;
    while(roomArray[room][PLAYER_INDEX] != 1)
        room++;
    if(isConnected(roomArray, x))
    {
        gameArray[NUM_BULLETS_INDEX]--;
        if (checkZombie(roomArray, x))
        {
            roomArray[gameArray[ZOMBIE_INDEX]][ZOMBIE_ROOM_INDEX] = 0;
            gameArray[ZOMBIE_INDEX] = -1;
        }
        else
            cout << "Darn, you missed!\n";
    }
    else
        cout << "Cannot shoot into this room\n";
}

//takes in roomArray and gameArray
//randomly moves zombie into an allowed adjacent room
void moveZombie(int roomArray[][7], int gameArray[])
{
    if(gameArray[ZOMBIE_INDEX] != -1)
    {
        int move = rand() % 4;
        if (roomArray[gameArray[ZOMBIE_INDEX]][move] != -1)
        {
            roomArray[roomArray[gameArray[ZOMBIE_INDEX]][move]][ZOMBIE_ROOM_INDEX] = 1;
            roomArray[gameArray[ZOMBIE_INDEX]][ZOMBIE_ROOM_INDEX] = 0;
        }
    }
}

//takes in a string select
//returns a bool of whether the selection is valid
bool validateSelection(string select)
{
    return ('Q' == select[0] || 'D' == select[0] ||'S' == select[0] ||'M' == select[0]);
}

//takes in most of our current variables
//uses a switch statement fir the input selection
void doSelection(string select, int roomArray[][7], int gameArray[], bool &haveGrail, int &currentRoom)
{
    switch(select[0])
    {
    case 'Q':
        exit(0);
        break;
    case 'D':
        printMemory(gameArray, roomArray);
        break;
    case 'S':
    {
        string str = select.substr(1, 3);
        int digit = atoi((str.c_str()));
        shootRoom(roomArray, gameArray, digit - 1);
        break;
    }
    case 'M':
        {
        string str = select.substr(1, 3);
        int digit = atoi((str.c_str()));
        moveRoom(gameArray, roomArray, digit - 1, haveGrail, currentRoom);
        break;
        }
    }
}

//takes in roomArray, gameArray, haveGrail, and currentRoom
//prints menu, accepts a selection and calls doSelection
void waitForMove(int roomArray[][7], int gameArray[], bool &haveGrail, int &currentRoom)
{
    cout << "Q - quit the game\nD - print memory\nS #- shoot into the indicated room\nM #- move into the indicated room\n";
    string boop;
    do
    {
        getline(cin, boop);
    }
    while(!validateSelection(boop));
    doSelection(boop, roomArray, gameArray, haveGrail, currentRoom);
}

//takes in roomArray, gameArray, haveGrail, and currentRoom
//prints various conditions
void checkroom(int gameArray[], int roomArray[][7], bool &haveGrail, int &currentRoom)
{
    cout << "Current Room: " << gameArray[PLAYER_INDEX] + 1 << endl;
    cout << "Number of Bullets: " << gameArray[NUM_BULLETS_INDEX] << endl;
    if(haveGrail)
        cout << "You have the Holy Grail!" << endl;
    if(gameArray[ZOMBIE_INDEX] == gameArray[CURRENT_ROOM_INDEX])
        {
        if(winOrLose(roomArray, currentRoom, haveGrail) == 1)
            {
                cout << "You have lost!\n";
                exit(0);
            }
        }
    if(checkNearZombie(roomArray, gameArray[PLAYER_INDEX]))
        cout << "You hear the Zombie";
    if(checkNearGrail(roomArray, gameArray[PLAYER_INDEX]))
        cout << "You sense the Grail\n";
    showConnectedRooms(roomArray);
    waitForMove(roomArray, gameArray, haveGrail, currentRoom);
}

//takes in roomArray, gameArray, haveGrail, and currentRoom
//continuously runs checkroom while current room doesnt equal -1
void running(int gameArray[], int roomArray[][7], bool &haveGrail, int &currentRoom)
{
    while(currentRoom != -1)
        checkroom(gameArray, roomArray, haveGrail, currentRoom);
}
