/*
PIC 10C Homework 6, myttt.cpp
Purpose: Throwing expections for Tic-Tac-Toe
Author: Aral Muftuoglu
Date: 11/07/2022
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

char square[10] = {'o','1','2','3','4','5','6','7','8','9'};
int checkwin();
void print_board(int gameType);
void mark_square(int choice, char mark);

// helper functions
bool onePlayerGame();   // both will return false if game is restarted (game is not completed by will)
bool twoPlayerGame();   // will return true if game ends or the user quits

bool isNumber(string x);
void resetBoard();

string playerOne;
string playerTwo;

int main()
{
    bool validGame = false;
    string gameType;
    
    // prompts users to ONLY choose a one-player or two-player game
    while (validGame == false)
    {
        cout << "Do you want to play a 1-player or 2-player game? Please enter 1 or 2: ";
        getline(cin, gameType);
        
        try {
            if (gameType != "1" && gameType != "2")
            {
                throw "You can only input 1 or 2 (with no additional spaces) to choose the game type. Please try again.";
            }
            else
            {
                validGame = true;
            }
        }
        
        catch (const char* errorMessage)
        {
            cout << errorMessage << endl;
        }
    }
    
    if (gameType == "1")
    {
        if (onePlayerGame() == false)   // when we enter this condition, it will still call the function, and then check if it is false
        {
            resetBoard();
            return main();
        }
    }
    
    if (gameType == "2")
    {
        bool validOne = false;
        bool validTwo = false;
        
        while (validOne == false)
        {
            cout << "Enter name for player 1: ";
            getline(cin, playerOne);
        
            try {
                if (playerOne.size() == 0)
                {
                    throw "You must enter a name. Please try again.";
                }
                else
                {
                    validOne = true;
                }
            }
            catch (const char* errorMessage)
            {
                cout << errorMessage << endl;
            }
        }
        
        while (validTwo == false)
        {
            cout << "Enter name for player 2: ";
            getline(cin, playerTwo);
        
            try {
                if (playerTwo.size() == 0)
                {
                    throw "You must enter a name. Please try again.";
                }
                else
                {
                    validTwo = true;
                }
            }
            catch (const char* errorMessage)
            {
                cout << errorMessage << endl;
            }
        }
        
        if (twoPlayerGame() == false)
        {
            resetBoard();
            return main();
        }
    }
    
    
    
    return 0;
}


/*********************************************
    FUNCTION TO RETURN GAME STATUS
    1 FOR GAME IS OVER WITH RESULT
    -1 FOR GAME IS IN PROGRESS
    O GAME IS OVER AND NO RESULT
**********************************************/
int checkwin()
{
    if (square[1] == square[2] && square[2] == square[3])
        return 1;
    else if (square[4] == square[5] && square[5] == square[6])
        return 1;
    else if (square[7] == square[8] && square[8] == square[9])
        return 1;
    else if (square[1] == square[4] && square[4] == square[7])
        return 1;
    else if (square[2] == square[5] && square[5] == square[8])
        return 1;
    else if (square[3] == square[6] && square[6] == square[9])
        return 1;
    else if (square[1] == square[5] && square[5] == square[9])
        return 1;
    else if (square[3] == square[5] && square[5] == square[7])
        return 1;
    // the board is full
    else if (   square[1] != '1' && square[2] != '2' && square[3] != '3'
             && square[4] != '4' && square[5] != '5' && square[6] != '6'
             && square[7] != '7' && square[8] != '8' && square[9] != '9')
        return 0; // tie situation
    else
        return -1; // game in progress
}

/*******************************************************************
     FUNCTION TO DRAW BOARD OF TIC TAC TOE WITH PLAYER MARKS
********************************************************************/

void print_board(int gameType)
{
    cout << "\n \t Tic Tac Toe \n";
    if (gameType == 1)
    {
        cout << "You (X)  -  Computer (O)" << endl << endl;
    }
    else if (gameType == 2)
    {
        cout << playerOne << " (X) - " <<  playerTwo << " (O)" << endl << endl;
    }
    cout << "     |     |     " << endl;
    cout << "  " << square[1] << "  |  " << square[2] << "  |  " << square[3] << endl;
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    cout << "  " << square[4] << "  |  " << square[5] << "  |  " << square[6] << endl;
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    cout << "  " << square[7] << "  |  " << square[8] << "  |  " << square[9] << endl;
    cout << "     |     |     " << endl << endl;
}

// update the square array accoring to player's move
void mark_square(int choice, char mark)
{
    square[choice] = mark;
}


bool onePlayerGame()
{
    std::vector<int> choiceHistory;
    std::vector<int> cpuAllowedChoices = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    int player = -1; // player = 1 or -1
    int if_win = -1;
    char mark;
    
    string choice; // player's move
    int numberChoice;
    
    
    while (if_win == -1)
    {
        bool validChoice = false;
        print_board(1);
            
        while (validChoice == false)
        {
            cout << "Please enter a number (or enter 'Q' to quit or 'N' to start a new game): ";
            getline(cin, choice);
            
             
            if (choice == "Q")
            {
                cout << "The game has ended because the user quit." << endl;
                return true;
            }
            
            if (choice == "N")
            {
                cout << "A new game has started." << endl;
                return false;
            }
            
            if (choice.size() != 0 && isNumber(choice) == true)
            {
                numberChoice = std::stoi(choice);
            }
            
            auto iter = std::find(choiceHistory.begin(), choiceHistory.end(), numberChoice);
            
            try {
                if (choice.size() != 1)
                {
                    throw "You must input only one character with no spaces.";
                }
                else if (isNumber(choice) == false || numberChoice == 0)
                {
                    throw "You must input a number 1 to 9 (inclusive) to choose your move. Please try again.";
                }
                else if (iter != choiceHistory.end())
                {
                    throw "You cannot input a number that has already been chosen. Please try again.";
                }
                else
                {
                    validChoice = true;
                    choiceHistory.push_back(numberChoice);
                    auto find = std::find(cpuAllowedChoices.begin(), cpuAllowedChoices.end(), numberChoice);
                    cpuAllowedChoices.erase(find);
                }
            }
                
            catch (const char* errorMessage)
            {
                cout << errorMessage << endl;
            }
        }
        
        mark = 'X';
        // update square array according to player's move
        mark_square(numberChoice, mark);
        
        // check if game stops
        if_win = checkwin();
        if (if_win == 1)
        {
            break;
        }
        
        // cpu's turn
        mark = 'O';
        
        // cpu should not have a turn if the user has won on their turn
        if (cpuAllowedChoices.empty() == false && if_win == -1)
        {
            player *= -1;
            int cpuChoice = cpuAllowedChoices[rand() % cpuAllowedChoices.size()];
        
            choiceHistory.push_back(cpuChoice);
            
            auto find = std::find(cpuAllowedChoices.begin(), cpuAllowedChoices.end(), cpuChoice);
            cpuAllowedChoices.erase(find);
        
            mark_square(cpuChoice, mark);

            if_win=checkwin();
        }
        
    }

    
    print_board(1);
    
    if (if_win == 1)
        {
            if (player == -1)
            {
                cout << "Congrats! You have won!" << endl;
                return true;
            }
            else // cpu player id is 1
            {
                cout << "The CPU has won. You'll get them next time!" << endl;
                return true;
            }
        }
    else
        {
            cout<< "\nTie Game.\n";
            return true;
        }
    
    return true;
}


bool twoPlayerGame()
{
    std::vector<int> choiceHistory;
    
    // print information to let users know they can exit by entering Q and restart by entering N
    int player = -1; // player = 1 or -1
    int if_win = -1;
    char mark;
    
    string choice; // player's move
    int numberChoice;
    
    while (if_win == -1)
    {
        bool validChoice = false;
        print_board(2);
            
        while (validChoice == false)
        {
            if (player == -1)
            {
                cout << playerOne << ", enter a number (or enter 'Q' to quit or 'N' to start a new game): ";
            }
            else if (player == 1)
            {
                cout << playerTwo << ", enter a number (or enter 'Q' to quit or 'N' to start a new game): ";
            }
            getline(cin, choice);
 
            if (choice == "Q")
            {
                cout << "The game has ended because the user quit." << endl;
                return true;
            }
 
            if (choice == "N")
            {
                cout << "A new game has started." << endl;
                return false;
            }
 
            if (choice.size() != 0 && isNumber(choice) == true)
            {
                numberChoice = std::stoi(choice);
            }
                
            auto iter = std::find(choiceHistory.begin(), choiceHistory.end(), numberChoice);
            
            try {
                if (choice.size() != 1)
                {
                    throw "You must input only one character with no spaces.";
                }
                else if (isNumber(choice) == false || numberChoice == 0)
                {
                    throw "You must input a number 1 to 9 (inclusive) to choose your move. Please try again.";
                }
                else if (iter != choiceHistory.end())
                {
                    throw "You cannot input a number that has already been chosen. Please try again.";
                }
                else
                {
                    validChoice = true;
                    choiceHistory.push_back(numberChoice);
                }
            }
            
            catch (const char* errorMessage)
            {
                cout << errorMessage << endl;
            }
            
        }   // end of getting a valid input
            
            
        // select player's mark symbol
        if (player == -1)
            {
                mark = 'X';
            }
        else if (player == 1)
            {
                mark = 'O';
            }
            
        // update square array according to player's move
        mark_square(numberChoice, mark);
            
        // check if game stops
        if_win = checkwin();
            
        if (if_win == 1)
        {
            break;  // breaks from loop to announce winner before player changes
        }
            
        // change to next player's move
        player *= -1;
            
    }  // end of turn

    print_board(2);
    
    if (if_win==1)
    {
        cout<< "\nPlayer " << (-player+3)/2 << " wins! \n ";
    }
    else
    {
        cout<< "\nTie Game.\n";
    }
    
    return true;
}


bool isNumber(string x)
{
    for (int i = 0; i < x.size(); i++)
    {
        if (isdigit(x[i]) == false)
        {
            return false;
        }
    }
    
    return true;
}

void resetBoard()
{
    for (int i = 1; i < 10; i++)
    {
        char c = '0' + i;
        square[i] = c;
    }
}
