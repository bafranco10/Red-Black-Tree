// FILE: DataType.h
// R England, Transy U
// CS 2444, Fall 2021
//
//	Define a common value type and key type for testing a Bst implementation
//

#ifndef DATATYPE_H
#define DATATYPE_H

// (uncomment the next line to use the Mp3 value type, after you've debugged with int's)
//#define USE_MP3

#ifdef  USE_MP3
#include "Mp3.h"
typedef Code	KeyType;
typedef Mp3   	ValueType;

#else
typedef int 	KeyType;
typedef int 	ValueType;

#endif
#endif
