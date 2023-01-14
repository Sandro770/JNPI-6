#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

class TooManyDiceException : public std::exception { };

class TooFewDiceException : public std::exception { };

class TooManyPlayersException : public std::exception { };

class TooFewPlayersException : public std::exception { };

#endif
