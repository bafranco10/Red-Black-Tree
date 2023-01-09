// FILE: Mp3.cpp
// R England, Transy U
// CS 2444, Fall 2021
//
//	Implementation of Mp3 class
//

#include	"Mp3.h"

// Macros: generate comparison operators (external to class)
#define	MP3_OP_EXTERN(_OP) \
bool operator _OP (const Code& code, const Mp3& mp3song) \
	{ return code _OP mp3song.getCode(); }

	MP3_OP_EXTERN (==)	MP3_OP_EXTERN (!=)	MP3_OP_EXTERN (>=)
	MP3_OP_EXTERN (<=)	MP3_OP_EXTERN (>)	MP3_OP_EXTERN (<)

// Overloaded input operator:
//    prompt for and read Mp3 info from the keyboard
const int MAX = 256;
istream& operator>>(istream& s, Mp3& mp3song) {
	Code	code;
	char	cStr[MAX];
	string	name, artist, restOfLine;
	int		year;

	cout << endl << "  Code Number: ";
	s >> code;			s.get();
	cout << "  Song Name: ";
	s.get (cStr, MAX);	s.get();
	name = cStr;
	cout << "  Artist Name: ";
	s.get (cStr, MAX);	s.get();
	artist = cStr;
	cout << "  Year released: ";
	s >> year;			s.get();
	mp3song = Mp3 (code, name, artist, year);
	return s;
}

// inFromFile:
//   get Mp3 info from file
bool inFromFile(Mp3& mp3song, ifstream& inFile) {
	Code	code;
	char	cStr[MAX];
	string	name, artist;
	int		year;

	if(inFile >> code) {
		inFile.get();

		inFile.get (cStr, MAX);	 inFile.get();
		name = cStr;

		inFile.get (cStr, MAX);	 inFile.get();
		artist = cStr;

		inFile >> year;

		mp3song = Mp3 (code, name, artist, year);

		return true;
	}
	return false;
}

// printToFile:
//    output Mp3 info to file
void printToFile(ofstream& outFile, const Mp3& mp3song) {
	outFile << mp3song.getCode() << endl;
	outFile << mp3song.getName() << endl;
	outFile << mp3song.getArtist() << endl;
	outFile << mp3song.getYear() << endl;
}

// Overloaded output operator:
//    display labeled Mp3 info to an output stream
ostream& operator<<(ostream& s, const Mp3& mp3song) {
	s << " CODE NUM: [" << mp3song.getCode () << "]"
	  << " NAME: " << mp3song.getName ()
	  << " ARTIST: " << mp3song.getArtist ()
	  << " YEAR RELEASED: " << mp3song.getYear();
	return s;
}
