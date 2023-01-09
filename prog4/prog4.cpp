//	FILE: prog3.cpp
//	R England, Transy U
//	CS 2444, Fall 2021
//
//      Test driver for P3 Bst class
//
//      	to build on Mac command line:
//                g++ prog3.cpp Bst.cpp Mp3.cpp -o p3
//			to run:
//				  ./p3
//
#include	<iostream>
#include	"DataType.h"
#include	"Rbt.h"
using namespace std;

// symbolic constants
const KeyType SENTINEL = (KeyType)(-1);
const int QUIT = 0, PUT = 1, GET = 2;

// function prototypes
void   testPut (Rbt& t);
void   testGet (Rbt& t);
int    getMenuResponse (void);


/////
//// main program
///
//
int main (void) {
    Rbt  t;
    cout << endl << endl
         << "TEST DRIVER FOR BST CLASS" << endl << endl;

// see everything?
    char response;
    cout << "Show Bst contents after each operation? [y/n]: ";
    cin >> response;
    bool showTree = (toupper (response) == 'Y');

// loop as long as user wants
    bool stop = false;
    do {
        if (showTree) {
            cout << endl << endl << "   Current tree contents:" << endl;
            t.printDEBUG ();
        }
        switch (getMenuResponse ()) {
            case QUIT:
                stop = true;
                break;
            case PUT:
                testPut (t);
                break;
            case GET:
                testGet (t);
                break;
            default:
                cout << "Not a valid response. Try again." << endl;
                break;
        }
    } while (!stop);
    cout << endl << endl;

    return 0;
}

// getMenuResponse
//    display a menu; read response from the keyboard
int getMenuResponse (void) {
    cout << endl << endl
         << "Type \t" << PUT << " for insert" << endl
         << '\t' << GET << " for get" << endl
         << '\t' << QUIT << " to quit" << endl << ": ";
    int response;
    cin >> response;
    cout << endl;
    return response;
}

// testPut
//    try out the put function for a Bst object
void testPut (Rbt& t) {
    ValueType value;
    cout << "\nItem to insert: ";
    cin >> value;
    cout << endl << "Insert operation "
         << ((t.put (value)) ? "" : "NOT ")
         << "successful";
}

// testGet
//    try out the get function for a Bst object
void testGet (Rbt& t) {
    KeyType key;
    ValueType value;
    cout << endl << endl << "Next key to get: ";
    cin >> key;
    if (t.get (key, value)) {
        cout << endl << "Success! Got this from tree:" << endl;
        cout << value;
    }
    else {
        cout << endl << "Get operation FAILED on tree for key " << key << endl;
    }
}
