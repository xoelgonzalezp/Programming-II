/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Xoel González Pereira LOGIN 1: xoel.gonzalezp
 * AUTHOR 2: Ángel Meijón de la Fuente LOGIN 2: angel.meijon
 * GROUP: 6.1
 * DATE: 27 / 04 / 2023
 */

#ifndef PARTICIPANT_LIST_H
#define PARTICIPANT_LIST_H

#include "types.h"

#include <stdlib.h>
#include <string.h>

#define NULLP NULL

/* **************************** Types **************************** */



typedef struct tItemP{

    tParticipantName participantName;
    tNumVotes numVotes;
    tEUParticipant EUParticipant;
}tItemP;

typedef struct tNode* tPosP;

struct tNode{
    tItemP data;
    tPosP next;
};

typedef tPosP tListP;


/* **************************** Functions **************************** */


void createEmptyListP(tListP* L);
/*
 * Goal: Creates an empty list
 * Input: L: List to be created
 * Output: An empty list
 * Postcondition: The list is initialised and has no elements
 */

bool isEmptyListP(tListP L);
/*
 * Goal: Determines whether the list is empty or not
 * Input: L: List to be checked
 * Output: true if the list is empty, false otherwise
 */

tPosP firstP(tListP L);
/*
 * Goal: Returns the position of the first element of the list
 * Input: L: List to be handled
 * Output: Position of the first element
 * Precondition: The list is not empty
 */

tPosP lastP(tListP L);
/*
 * Goal: Returns the position of the last element of the list
 * Input: L: List to be handled
 * Output: Position of the last element
 * Precondition: The list is not empty
 */


tPosP nextP(tPosP p, tListP L);
/*
 * Goal:  Returns the position of the element that follows the current one
 * Input: p: Position of the current element
 *        L: List to be handled
 * Output: Position of the next element,or NULLP if the specified position has no next element
 * Precondition: The indicated position (p) is a valid position in the list
 */

tPosP previousP(tPosP p, tListP L);
/*
 * Goal: Returns the position of the element preceding the current one
 * Input: p: Position of the current element
 *        L: List to be handled
 * Output: Position of the previous element, or NULLP if the specified position has no previous element
 * Precondition: The indicated position (p) is a valid position in the list
 */

bool insertItemP(tItemP d, tListP* L);
/*
 * Goal: Inserts an element in the list ordered by the field participantName. If the element could be inserted, the value true is returned, otherwise false is returned.
 * Input: d: Contents of the element to be inserted
 *        L: List where we are inserting
 * Output: List with the element d inserted and true if it could be inserted, false otherwise
 * Precondition: The specified position (p) is a valid position in the list or a LNULL position
 * Postcondition: The positions of the elements of the list after the inserted one may have changed their value.
 */


void deleteAtPositionP(tPosP p, tListP* L);
/*
 * Goal: Deletes the element at the given position from the list
 * Input: p: Position of the element to delete
 *        L: List to be modified
 * Output: List without the element that was located at position p
 * Precondition: The indicated position (p) is a valid position in the list
 * Postcondition: The positions of the elements in the list following that of the deleted one may have varied
 */

tItemP getItemP(tPosP p, tListP L);
/*
 * Goal: Returns the content of the element at the indicated position (p)
 * Input: p: Position of the desired element
 *        L: List from where the item is to be retrieved
 * Output: Content of the element located at position p
 * Precondition: The indicated position (p) is a valid position in the list
 */

void updateItemP(tItemP d, tPosP p, tListP* L);
/*
 * Goal: Modifies the content of the element at the indicated position (p)
 * Input: d: New content to be assigned to the element at position p
          p: Position of the element that we wish to modify
          L: The list to be modified
 * Output: List with the content of the element modified
 * Precondition: The indicated position (p) is a valid position in the list
 * Postcondition: The order of the elements in the list has not been modified
 */


tPosP findItemP(tParticipantName d, tListP L);
/*
 * Goal: Returns the position of the first element in the list whose participant name matches the given one
 * Input: d: Content of the element to search for
 *        L: List where the search is to be made
 * Output: Position of the element found, or NULLP if it is not found
 */

#endif
