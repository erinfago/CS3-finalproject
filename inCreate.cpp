//
//  inCreate.cpp
//  Fago_finalProject
//
//  Erin Fago
//  Xcode
//

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <random>
#include <string>
#include <numeric>
#include <chrono>



#include "inCreate.hpp"
#include "matchtile.hpp"

using namespace std;

//prototypes of functions so it can be called before they are technically defined
void playGame(vector<tile> &);
void displayGame(vector<tile> &);
string colorOrNum(tile t);

//helper function for random number generator in create
int myRandom (int i)
{
    return rand()%i;
}

/*
 the main function that calls a lot of the others - builds/sets up framework of the game
 */
void inCreate()
{
    
    //create stream to read file
    ifstream inFile;
    //inAns to get replys
    string inAns;
    
    //timeLimit to get next reply
    string ifTimeLimit;
    
    //int representation of limit
    int timeLimit = 0;
    
    //total number of tiles in the game
    int numTiles = 0;
    
    //get info from file second time
    string line;
    
    //intro
    cout << "Hello! Welcome to the matching game!" << endl;
    cout << "------------------------------" << endl;
    cout << "Let's begin by selecting a level." << endl;
    cout << endl;
    cout << "Valid answers are number between 1 and 3" << endl;
    cout << "1 : 4 tiles" << endl;
    cout << "2 : 8 tiles" << endl;
    cout << "3 : 12 tiles" << endl;
    cout << "Note: if you enter invalid input you will be given the easiest level. " << endl;
    cout << "------------------------------" << endl;
    cout << endl;
    cout << "Please enter your desired level : " << endl;
    
    //get user input
    getline(cin, inAns);
    cout << endl;
    
    //try to open the file with respective level - if anything else default to 1
    if(inAns == "2")
        inFile.open("level2.txt", ios::in);

    else if(inAns == "3")
        inFile.open("level3.txt", ios::in);

    else
    {
        inFile.open("level1.txt", ios::in);
        inAns = "1";
    }
    
    cout << "------------------------------" << endl;
    //check to see if file exists/opens property, if not end program
    if (inFile.fail())
    {
        cout << "~~~~Error in opening file!" << endl;
        exit(-1);
    }

    cout << "Ok cool, you selected level " << inAns << "!" << endl;

    //see if they want a time limit - default to no
    cout << "Would you like there to be a time limit? Please enter yes or no." << endl;
    getline(cin, ifTimeLimit);

    //while it is not the end of the file go through and get info about level
    while(!inFile.eof())
    {
        
        //begin to go through file and grab info
        getline(inFile,line);
        
        //grab # of tiles they want from first line of file and create the objects and add to vector of tiles
        numTiles = stoi(line);
        
        
        cout << endl;
        cout << "------------------------------" << endl;
        cout << "Game details: " << endl;
        cout << "------------------------------" << endl;
        
        
        cout << "--> Num tiles: " << numTiles << endl;
    
        getline(inFile, line);
        if(ifTimeLimit == "yes" || ifTimeLimit == "Yes")
        {
            timeLimit = stoi(line);
            cout << "--> Time limit : " << timeLimit << endl;
        }
        
        //otherwise no time limit so just set to 1000 for now
        else
        {
            timeLimit = 1000;
            cout << "--> Time limit : UNLIMITED" << endl;
        }
        
        cout << "------------------------------" << endl;
        cout << endl;
        break;
    
    }
    
    //array to hold tile objects
    vector <tile> tileVect;
    
    int everyTwo = 0;
    
    //seed - only do this once
    srand(unsigned(time(0)));
    
    //create all the tile elements and add each one to an array
    for(int i = 0; i < numTiles; i++)
    {
        //create a tile object
        tile t;
        
        //set color
        t.setColor(color(everyTwo));
        
        //set level
        t.setSelectedLevel(stoi(inAns));
        
        //set time limit - IF THERE IS ONE TO SET otherwise set to FALSE
        if(timeLimit == 1000)
            t.isTimeLimitSet(false);
        
        else
        {
            t.isTimeLimitSet(true);
            t.timeLimitSet(timeLimit);
        }
        
        //we want there to be two of each color so only go forward in the enum indexing every two
        if(i%2)
            everyTwo++;
        
        //add to vector
        tileVect.push_back(t);
    }
    
    //shuffle vector
    random_shuffle(tileVect.begin(), tileVect.end(), myRandom);
    
    cout << "------------------------------" << endl;
    
    //display the vect to make sure it shuffled / for testing purposes
    /*cout << "tile vect contains:" << endl;
    for(int s=0; s < numTiles ; s++)
    {
        cout <<"Tile " << s << " : " << tileVect.at(s).getColor() << endl;
    }*/


    //when finished close the file
    inFile.close();
    
    //call next function to prompt the interactive piece
    playGame(tileVect);
}

/*
 returns if color or number should be displayed
 */
string colorOrNum(tile t, int b)
{
    //length of tile in terminal
    int length = 8;
    string total = "";
    string beginning = "";
    string end = "";
    string middle;
    
    //if it is a match then we are going to display the associated color
    if(t.getIsMatched())
    {
        middle = t.getColor();
        length -= middle.length();
        
        //diving up spacing for the word in tile
        if(length%2)
        {
            for(int i = 0; i < length/2; i++)
            {
                beginning += " ";
                end += " ";
            }
            end += " ";
        }
        else
        {
            for(int i = 0; i < length/2; i++)
            {
                beginning += " ";
                end += " ";
            }
        }
        
        total = beginning + middle + end + "    ";
        return total;
    }
    //otherwise we are going to display the number "on the back of the tile"
    else
    {
        middle = to_string(b);
        //how much length this takes up
        length -= middle.length();
        
        //size spacing for before and after
        //if it is evenly divisible by 2:
        if(length%2)
        {
            for(int i = 0; i < length/2; i++)
            {
                beginning += " ";
                end += " ";
            }
            end += " ";
        }
        else
        {
            for(int i = 0; i < length/2; i++)
            {
                beginning += " ";
                end += " ";
            }
        }
            
        total = beginning + middle + end + "    ";
        return total;
    }
}


/*
 displays the game and calls other functions to update itself
 */
void displayGame(vector<tile> &tileVect)
{
    for(int b = 0; b < tileVect.size(); b+=4)
    {

        cout << " --------   " << " --------   " << " --------   " << " --------   " << endl;
        cout << "|        |  " << "|        |  " << "|        |  " << "|        |   " << endl;
        cout << " " << colorOrNum(tileVect.at(b), b+1) << colorOrNum(tileVect.at(b+1),b+2) << colorOrNum(tileVect.at(b+2),b+3)<< colorOrNum(tileVect.at(b+3),b+4) << endl;
        cout << "|        |  " << "|        |  " << "|        |  " << "|        |   "<< endl;
        cout << " --------   " << " --------   " << " --------   " << " -------- "<<endl;
    }
    cout << endl;


}

/*
 the interactive element of the game- tracks game time, number of guesses, checks guesses ,etc
 */
void playGame(vector<tile> &tileVect)
{
    cout << "Ok, time to get to matching! Here is the board: " << endl;
    
    //start time
    auto start = std::chrono::system_clock::now();
    
    //display board
    displayGame(tileVect);
    
    bool allGuessed = false;
    int first = 0;
    int second = 0;
    string error = "no";
    
    int numGuesses = 1;
    
    //while all the tiles arent all matched
    while(allGuessed == false)
    {
        cout << "---------------------------------" << endl;
        
       //ask for guess - ensure proper input try / throw / catch
        cout << "Enter first tile number: " << endl;
        try
        {
            cin >> first;
            if (first > tileVect.size() || first < 1)
                throw error;
        }
        catch(string error)
        {
            cout << "Out of bounds!!" << endl;
            exit(-1);
        }
        cout << "Enter second tile number: " << endl;
        try
        {
            cin >> second;
            if (second > tileVect.size() || second < 1)
                throw error;
        }
        catch(string error)
        {
            cout << "Out of bounds!! Sorry if you can't play by the rules then you can't play at all!" << endl;
            exit(-1);
        }
        
        //check current time
        auto curr = std::chrono::system_clock::now();
        
        //compare to beginning to get number of seconds that have gone by
        auto int_sec = std::chrono::duration_cast<std::chrono::milliseconds>(curr - start);
        
        //convert using duration cast
        std::chrono::duration<int, std::micro> ellapsed = int_sec;
        
        //store in int and multiply to get count in seconds
        int ellap = (ellapsed/1000000).count();
        
        cout << endl;
        cout << "---------------------------------" << endl;
        cout << endl;
        
        //display amount of time passed if they asked to be timed
        cout << endl;
        if(tileVect.at(1).isTimeLimitGet())
        {
            cout << "->Ellapsed time: " << ellap << " seconds." << endl;
            cout << endl;
        }
        
        //check if user wanted a time limit
        if(tileVect.at(first-1).isTimeLimitGet())
        {
            //check to see if they have passed the time limit - if so exit
            if(ellap > tileVect.at(first-1).timeLimitGet())
            {
                cout << "You are out of time!! Answer invalid. Game over!" << endl;
                exit(0);
            }
            //if not update them on their status
           else
           {
               //calculate the amount of time left
               double difference = tileVect.at(first-1).timeLimitGet() - ellap;
               
               //tell them the current time
               cout << "->Seconds remaining..." << difference << endl;
               cout << "->Number of guesses... " << numGuesses << endl;
               cout << endl;
               cout << "---------------------------------" << endl;
               cout << endl;
           }
        }
        
        //check to see if user inputted the same tile twice
        if(first == second)
        {
            cout << "Please enter two different numbers. A card cannot be its own match, silly!" << endl;
            cout << "Number of guesses... " << numGuesses << endl;
            cout << endl;
            numGuesses++;
        }
        //check if input are a match
        else if(tileVect.at(first -1).getColor() == tileVect.at(second-1).getColor())
        {
            //mark both as true
            tileVect.at(first-1).setIsMatched(true);
            tileVect.at(second-1).setIsMatched(true);
            cout << "That's a match!! Tile " << first << " and tile " << second << " are both the color " << tileVect.at(first-1).getColor() << endl;
            cout << "Number of guesses... " << numGuesses << endl;
            cout << endl;
            numGuesses++;
        }
        //if not give a hint
        else
        {
            cout << "Sorry! Those don't match :( " << endl;
            cout << "Tile: " << first << " is: " << tileVect.at(first-1).getColor() << endl;
            cout << "Tile: " << second << " is: " << tileVect.at(second-1).getColor() << endl;
            cout << endl;
            cout << "Number of guesses... " << numGuesses << endl;
            cout << endl;
            numGuesses++;
        }
        
        
        //check to see if all tiles are matched
        int tot = 0;
        for(int t=0 ; t < tileVect.size(); t++)
        {
            if(tileVect.at(t).getIsMatched())
            {
                tot++;
            }
        }
        
        //display an updated version of the game
        displayGame(tileVect);
        
        //check current time now
        auto end = std::chrono::system_clock::now();
        
        //compare to beginning to get number of seconds that have gone by
        auto int_s = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
        
        //convert using duration cast
        std::chrono::duration<int, std::micro> here = int_s;
        
        //store in int and multiply to get count in seconds
        int now = (here/1000000).count();
        
        //if all are answered exit loop and say goodbye
        if(tot == tileVect.size())
        {
            //check to see if it is a high score for time or for numGuesses
            fstream file;
            file.open("highscores.txt", ios::in);
            
            //make sure file opens correctly
            if (file.fail())
            {
                cout << "~~~~Error in opening highscore file!" << endl;
                exit(-1);
            }
            
            //grab info from file incase you have to overwrite a value
            int L1time = 0, L1guess = 0, L2time = 0, L2guess = 0, L3time = 0, L3guess = 0, tracker = 0;
            string line = "";
            
            for(int j = 0; j<6 ; j++)
            {
                getline(file, line);
                if(tracker == 0)
                {
                    L1time = stoi(line);
                    tracker++;
                }
                else if(tracker == 1)
                {
                    L1guess = stoi(line);
                    tracker++;
                }
                else if(tracker == 2)
                {
                    L2time = stoi(line);
                    tracker++;
                }
                else if(tracker == 3)
                {
                    L2guess = stoi(line);
                    tracker++;
                }
                else if(tracker == 4)
                {
                    L3time = stoi(line);
                    tracker++;
                }
                else
                {
                    L3guess = stoi(line);
                    tracker++;
                }
            }
            //close file - done reading
            file.close();
            
            //open for writing
            fstream outfile;
            outfile.open("highscores.txt", ios::out | ios::trunc);
            
            //make sure file opens correctly
            if (outfile.fail())
            {
                cout << "~~~~Error in opening highscore file!" << endl;
                exit(-1);
            }
            
            //check what level they were on
            //  level 1 : first two lines of file (time, guess)
            //  level 2 : middle two lines of file (time, guess)
            //  level 3 : last two lines of file (time guess)

            int level = tileVect.at(1).getSelectedLevel();
            
            if(level == 1)
            {
                //can only recieve time highscore if they wanted to be timed
                if(now < L1time && tileVect.at(1).isTimeLimitGet())
                {
                    //write out new highscore to file! (including rewriting all the others)
                    outfile << now << '\n' << L1guess << '\n' << L2time << '\n' << L2guess << '\n' << L3time << '\n' << L3guess;
                    
                    cout << endl;
                    cout << "**NEW HIGHSCORE**" << endl;
                    cout << "You are the fastest to complete level " << tileVect.at(1).isTimeLimitGet() <<"!" << endl;
                    cout << "Previous high score: " << L1time << endl;
                    cout << "New high score: " << now << endl;
                    cout << endl;
                }

                //check if lowest # of guesses
                if(numGuesses < L1guess)
                {
                    //write out new highscore to file! (including rewriting all the others)
                    outfile << L1time << '\n' << numGuesses << '\n' << L2time << '\n' << L2guess << '\n' << L3time << '\n' << L3guess;
                    
                    cout << "**NEW HIGHSCORE**" << endl;
                    cout << "You completed level " << tileVect.at(1).isTimeLimitGet() <<" in the fewest guesses!" << endl;
                    cout << "Previous high score: " << L1guess << endl;
                    cout << "New high score: " << numGuesses << endl;
                    cout << endl;
                }
            }
            else if (level == 2)
            {

                //can only recieve time highscore if they wanted to be timed
                if(now < L2time && tileVect.at(1).isTimeLimitGet())
                {
                    //write out new highscore to file! (including rewriting all the others)
                    outfile << L1time << '\n' << L1guess << '\n' << now << '\n' << L2guess << '\n' << L3time << '\n' << L3guess;
                    
                    cout << "**NEW HIGHSCORE**" << endl;
                    cout << "You are the fastest to complete level " << tileVect.at(1).isTimeLimitGet() <<"!" << endl;
                    cout << "Previous high score: " << L2time << endl;
                    cout << "New high score: " << now << endl;
                    cout << endl;
                }

                //check if lowest # of guesses
                if(numGuesses < L2guess)
                {
                    //write out new highscore to file!(including rewriting all the others)
                    outfile << L1time << '\n' << L1guess << '\n' << L2time << '\n' << numGuesses << '\n' << L3time << '\n' << L3guess;
                    
                    cout << "**NEW HIGHSCORE**" << endl;
                    cout << "You completed level " << tileVect.at(1).isTimeLimitGet() <<" in the fewest guesses!" << endl;
                    cout << "Previous high score: " << L2guess << endl;
                    cout << "New high score: " << numGuesses << endl;
                    cout << endl;
                }
            }
            //level 3
            else
            {
                //can only recieve time highscore if they wanted to be timed
                if(now < L3time && tileVect.at(1).isTimeLimitGet())
                {
                    //write out new highscore to file! (including rewriting all the others)
                    outfile << L1time << '\n' << L1guess<< '\n' << L2time << '\n' << L2guess << '\n' << now << '\n' << L3guess;
                    
                    cout << "**NEW HIGHSCORE**" << endl;
                    cout << "You are the fastest to complete level " << tileVect.at(1).isTimeLimitGet() << "!" << endl;
                    cout << "Previous high score: " << L3time << endl;
                    cout << "New high score: " << now << endl;
                    cout << endl;
                }

                
                //check if lowest # of guesses
                if(numGuesses < L3guess)
                {
                    //write out new highscore to file! (including rewriting all the others)
                    outfile << L1time << '\n' << L1guess << '\n' << L2time << '\n' << L2guess << '\n' << L3time << '\n' << numGuesses;
                    
                    cout << "**NEW HIGHSCORE**" << endl;
                    cout << "You completed level " << tileVect.at(1).isTimeLimitGet() <<" in the fewest guesses!" << endl;
                    cout << "Previous high score: " << L3guess << endl;
                    cout << "New high score: " << numGuesses << endl;
                    cout << endl;
                }
            }
            //close file when done using it
            outfile.close();
            
            //set condition to true to exit loop
            allGuessed = true;
            
            //only praised about time if they were timed
            if(tileVect.at(1).isTimeLimitGet())
                cout << "Congrats! You got them all in "<<  numGuesses <<" tries, in "<< now  << " seconds! Thanks for playing."<< endl;
            else
                cout << "Congrats! You got them all in "<<  numGuesses << " tries. Thanks for playing."<< endl;
        }
        else
            cout << "Keep guessing!" << endl;
   
        
    }//end while
    
}
