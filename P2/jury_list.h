/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Xoel González Pereira LOGIN 1: xoel.gonzalezp
 * AUTHOR 2: Ángel Meijón de la Fuente LOGIN 2: angel.meijon
 * GROUP: 6.1
 * DATE: 27 / 04 / 2023
 */

#ifndef JURY_LIST_H
#define JURY_LIST_H

#include "types.h"

#include "participant_list.h"
#include <stdbool.h>
#include <string.h>
#define LIST_SIZE 10
#define NULLJ (-1)  /*Constant used to represent null positions.*/
#define MAX 1000



/* **************************** Types **************************** */

typedef struct tItemJ {
    tJuryName juryName;
    tNumVotes totalVoters;
    tNumVotes validVotes;
    tNumVotes nullVotes;
    tListP    participantList;


} tItemJ;


typedef int tPosJ;    /*Position of an element in the jury list*/

typedef struct tListJ{   /*Represents a list of juries*/
    tPosJ lastPos;
    tItemJ data[LIST_SIZE];
} tListJ;

/* **************************** Functions **************************** */

void createEmptyListJ (tListJ * L);
/*
 * Goal: Creates an empty list
 * Input: L: List to be created
 * Output: An empty list
 * Postcondition: The list is initialised and has no elements
 */

bool isEmptyListJ(tListJ L);
/*
 * Goal: Determines whether the list is empty or not
 * Input: L: List to be checked
 * Output: true if the list is empty, false otherwise
 */

tPosJ firstJ(tListJ L);
/*
 * Goal: Returns the position of the first element of the list
 * Input: L: List to be handled
 * Output: Position of the first element
 * Precondition: The list is not empty
 */

tPosJ lastJ(tListJ);
/*
 * Goal: Returns the position of the last element of the list
 * Input: L: List to be handled
 * Output: Position of the last element
 * Precondition: The list is not empty
 */

tPosJ nextJ(tPosJ p, tListJ L);
/*
 * Goal:  Returns the position of the element that follows the current one
 * Input: p: Position of the current element
 *        L: List to be handled
 * Output: Position of the next element,or NULLJ if the specified position has no next element
 * Precondition: The indicated position (p) is a valid position in the list
 */

tPosJ previousJ(tPosJ p, tListJ L);
/*
 * Goal: Returns the position of the element preceding the current one
 * Input: p: Position of the current element
 *        L: List to be handled
 * Output: Position of the previous element, or NULLJ if the specified position has no previous element
 * Precondition: The indicated position (p) is a valid position in the list
 */

bool insertItemJ(tItemJ  d, tListJ* L);
/*
 * Goal:Inserts an element in the list ordered by the field juryName. If the element could be inserted, the value true is returned, otherwise false is returned.
 *
 * Input: d: Contents of the element to be inserted
 *        L: List where we are inserting
 * Output: List with the element d inserted and true if it could be inserted, false otherwise
 * Precondition: The specified position (p) is a valid position in the list or a NULLJ position
 * Postcondition: The positions of the elements of the list after the inserted one may have changed their value.
 */

void deleteAtPositionJ(tPosJ p, tListJ* L);
/*
 * Goal: Deletes the element at the given position from the list
 * Input: p: Position of the element to delete
 *        L: List to be modified
 * Output: List without the element that was located at position p
 * Precondition: The indicated position is a valid position in the list, and the list of participants of that jury is empty.
 * Postcondition: The positions of the elements in the list following that of the deleted one may have varied.
 */

tItemJ getItemJ(tPosJ p, tListJ L);
/*
 * Goal: Returns the content of the element at the indicated position (p)
 * Input: p: Position of the desired element
 *        L: List from where the item is to be retrieved
 * Output: Content of the element located at position p
 * Precondition: The indicated position (p) is a valid position in the list
 */

void updateItemJ(tItemJ d, tPosJ p, tListJ* L);
/*
 * Goal: Modifies the content of the element at the indicated position (p)
 * Input: d: New content to be assigned to the element at position p
          p: Position of the element that we wish to modify
          L: The list to be modified
 * Output: List with the content of the element modified
 * Precondition: The indicated position (p) is a valid position in the list
 * Postcondition: The order of the elements in the list has not been modified
 */


tPosJ findItemJ(tJuryName d, tListJ L);
/*
 * Goal: Returns the position of the first element in the list whose jury name matches the given one
 * Input: d: Content of the element to search for
 *        L: List where the search is to be made
 * Output: Position of the element found, or NULLJ if it is not found
 */

#endif