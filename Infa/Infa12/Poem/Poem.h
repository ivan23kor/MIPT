#ifndef __HEADER_H__
#define __HEADER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define N 100 //maximum length of a string that can be read
#define MAX_HASH 500 //maximum hash function return

//====================================================================

//line is a fabriced type designed for storing strings in the database

struct line1
{
	char * str; 		// a name of the line
	int index;  		// an index of the array storing the starting lines of each string
	struct line1 * next;    // a pointer to the next line in the list
};
typedef struct line1 line;

//===================================================================

line ** text_ctor (); 	        // creates and returns a pointer to a database - an array of strings (line **)
line * line_ctor ();		// allocates memory for the string
void text_dtor (line ** text);  // frees the memory of the database
int hash (char * str);		// calculates a hash value for the string str
/*	Arguments:
	1) char * str - the string to be found

	Return values:
	Returns hash value of the string (char *) str. */

line * line_add (line ** text, char * str, int index); // adds the string str to the database
/*	Arguments:
	1) line ** text - a pointer to the database
	2) char * str - the string itself
	3) int index - an index in the array of starting lines

	Return values:
	Returns a pointer to the added line. */
line * search_line (line ** text, char * str); // searches for the string str
/*	Arguments:
	1) line ** text - a pointer to the database
	2) char * str - the string itself

	Return values:
	Returns a pointer to the found line, NULL otherwise. */
int remove_line (line ** text, char * str); // removes the string
/*	Arguments:
	1) line ** text - a pointer to the database
	2) char * str - the string itself.

	Return values:
	Returns 0 upon successful deletion, 1 otherwise. */

#endif 
