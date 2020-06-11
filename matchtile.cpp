//
//  matchtile.cpp
//  Fago_finalProject
//
//  Erin Fago
//  Xcode
//
#include <string>
#include "matchtile.hpp"

using namespace std;

//string of colors to use alongside the enum
string strColors[] = {"red", "orange", "yellow", "green", "blue", "purple"};

/*
 constructor
 */
tile::tile()
{
    m_isMatched = false;
}

/*
 set selected level
 */
void tile::setSelectedLevel(int level)
{
    m_selectedLevel = level;
}

/*
 get selected level
 */
int tile::getSelectedLevel() const
{
    return m_selectedLevel;
}


/*
 set if time limitations exist
 */
void tile::isTimeLimitSet(bool ans)
{
    m_timeLimitExists = ans;
}

/*
 get if time limitations exist
 */
bool tile::isTimeLimitGet() const
{
    return m_timeLimitExists;
}

/*
 set time limitations
 */
void tile::timeLimitSet(int time)
{
    m_timeLimit = time;
}

/*
 get time limitations
 */
int tile::timeLimitGet() const
{
    return m_timeLimit;
}


/*
 set tile color
 */
void tile::setColor(color c)
{
    m_color = c;
}

/*
 get tile color  - in string form
 */
string tile::getColor() const
{
    return strColors[m_color];
}

/*
 sets you if the tile has been matched
 */
void tile::setIsMatched(bool b)
{
    m_isMatched = b;
}

/*
 tells you if the tile has been matched
 */
bool tile::getIsMatched() const
{
    if(m_isMatched == true)
        return true;
    else
        return false;    
}
