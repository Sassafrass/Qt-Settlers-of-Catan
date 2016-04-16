/****************************************************************************
** **Settlers of Catan**
** Token Enumeration
** author: Frank Sasto / Dore Weber
** date: 3/27/2012
**
** The TOKEN enumeration represents the possible chit numbers.
** Each chit is a number between 2 and 12 excluding 7.
****************************************************************************/

#ifndef TOKEN_H
#define TOKEN_H

namespace TOKEN {

enum ENUM { //type of tokens
    NONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    EIGHT,
    NINE,
    TEN,
    ELEVEN,
    TWELVE
};

//Returns the token enumeration for the given token value
extern ENUM ToEnum( int value );

} //namespace TOKEN

#endif // TOKEN_H
