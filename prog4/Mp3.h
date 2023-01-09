// FILE: Mp3.h
// R England, Transy U
// CS 2444, Fall 2021
//
//    Interface of Mp3 class
//        Code objects (Key type) and Mp3 objects (Value type) are comparison compatible
//
#ifndef	MP3_H
#define	MP3_H

#include	<fstream>
#include	<iostream>
#include	<string>
using namespace std;

// a Code object is just a regular ol' integer
typedef int Code;

// an Mp3 object has a Code as well as other data about a song
class Mp3 {
public:

//// public member functions:

// constructors, destructor
	Mp3 (const Code& code,
	     const string& name,
	     const string& artist,
		 const int& year) {
		this -> code = code;
		this -> name = name;
		this -> artist = artist;
		this -> year = year;
	}
	Mp3 (void) { code = 0; name = ""; artist = ""; year = 0; }
	~Mp3 (void) {}

// standard accessors
	Code	getCode (void) const { return code; }
	string	getName (void) const { return name; }
	string	getArtist (void) const { return artist; }
	int		getYear (void) const { return year; }

// cast operator (to type Code)
	operator Code() const { return code; }

// assignment operator
	Mp3& operator= (const Mp3& other) {
		if (this != &other) {
			code = other.code;
			name = other.name;
			artist = other.artist;
			year = other.year;
		}
		return *this;
	}

// Macros: generate comparison operators (local to class)
#define	MP3_OP_LOCAL(_OP) \
bool operator _OP (const Mp3& other) const \
	{ return code _OP other.code; } \
bool operator _OP (const Code& code) const \
	{ return this->code _OP code; }

	MP3_OP_LOCAL (==)	MP3_OP_LOCAL (!=)	MP3_OP_LOCAL (>=)
	MP3_OP_LOCAL (<=)	MP3_OP_LOCAL (>)	MP3_OP_LOCAL (<)

private:
	Code	code;
	string	name, artist;
	int		year;
};

// Macros: generate comparison operators (external to class)
#define	MP3_OP_EXTERN_(_OP) \
bool operator _OP (const Code& code, const Mp3& mp3song);

	MP3_OP_EXTERN_(==)	MP3_OP_EXTERN_(!=)	MP3_OP_EXTERN_(>=)
	MP3_OP_EXTERN_(<=)	MP3_OP_EXTERN_(>)	MP3_OP_EXTERN_(<)

// input operator overload: prompt for and read Mp3 info from the keyboard
istream& operator>>(istream& s, Mp3& mp3song);

// output operator overload: display labeled Mp3 info to the screen
ostream& operator<<(ostream& s, const Mp3& mp3song);

// external functions
bool inFromFile(Mp3& mp3song, ifstream& inFile);
void printToFile(ofstream& outFile, const Mp3& mp3song);

#endif
