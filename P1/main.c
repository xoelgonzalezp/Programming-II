/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Xoel González Pereira LOGIN 1: xoel.gonzalezp
 * AUTHOR 2: Ángel Meijón de la Fuente * LOGIN 2: angel.meijon
 * GROUP: 6.1
 * DATE: 15 / 03 / 2023
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_BUFFER 255
#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef STATIC_LIST

#include "static_list.h"

#endif


void new(char *participantName, char *EUParticipant, tList *list);
/*
 * Goal: Create a new participant and add it to the list with its votes as 0.
 * Input: The name of the participant we want to add, its location (eu or non-eu) and the list to be modified.
 * Output: The list with the new participant.
 * Precondition: The list exists.
 * Postcondition: none.
 */
void vote(char *participantName, tList *list, int *NullVotes);
/*
 * Goal: Add a vote to the desired participant or to the null count if that is the case.
 * Input: The name of the participant we want to vote, the list to be modified and the count of null votes.
 * Output: The updated list.
 * Precondition: The list exists.
 * Postcondition: none.
 */
void disqualify(char *participantName, tList *list, int *NullVotes);
/*
 * Goal: Remove an existent participant from the list and add its votes to the null count if it has any.
 * Input: The name of the participant we want to disqualify, the list to be modified and the count of null votes.
 * Output: The updated list.
 * Precondition: The list exists.
 * Postcondition: none.
 */
void stats(int totalvoters, tList *list, const int *NullVotes);
/*
 * Goal: Show data about participation and votes from the current list.
 * Input: The total number of people who can vote, the list to be modified and the count of null votes.
 * Output: none.
 * Precondition: The list exists.
 * Postcondition: none.
 */


/* ****************************************************************************************************************** */


void new(char *participantName, char *EUParticipant, tList *list) {

    tItemL participant;
    tPosL position = findItem(participantName, *list); //We store the position in the list for the participantName
    if (position == LNULL) { //if the participant is not in the list, we set its votes to zero and its location
        participant.numVotes = 0;
        if (strcmp(EUParticipant, "eu") == 0) {
            participant.EUParticipant = true;
        } else if (strcmp(EUParticipant, "non-eu") == 0) {
            participant.EUParticipant = false;
        }
        strcpy(participant.participantName, participantName);
        if (insertItem(participant, position, list)) { //if it could be inserted at the end of the list, we print the message
            printf("* New: participant %s location %s", participant.participantName,
                   participant.EUParticipant ? "eu" : "non-eu");
        } else { //if it could not be inserted, an error message will be displayed
            printf("+ Error: New not possible");
        }
    } else {//if the participant is already in the list, an error message will be displayed
        printf("+ Error: New not possible");
    }
}


void vote(char *participantName, tList *list, int *NullVotes) {
    tItemL participant;
    tPosL position = findItem(participantName, *list); //We store the position in the list for the participantName
    if (!isEmptyList(*list)) { //if the list is not empty
        if (position != LNULL) {//if the participant is in the list, we increment its votes by one
            strcpy(participant.participantName, participantName);
            participant.numVotes = getItem(position, *list).numVotes + 1;
            participant.EUParticipant = getItem(position, *list).EUParticipant;
            updateItem(participant, position, list); //we update the content in that position
            printf("* Vote: participant %s location %s numvotes %d", participantName,
                   participant.EUParticipant ? "eu" : "non-eu", getItem(position, *list).numVotes);
        } else { //if the participant is not in the list, an error message will be displayed and the vote will be considered as null. It will be stored in NullVotes
            *NullVotes = *NullVotes + 1;
            strcpy(participant.participantName, participantName);
            printf("+ Error: Vote not possible. Participant %s not found. NULLVOTE", participant.participantName);
        }
    } else {//if the list is empty, an error message will be displayed and the vote will be considered as null. It will be stored in NullVotes
        *NullVotes = *NullVotes + 1;
        strcpy(participant.participantName, participantName);
        printf("+ Error: Vote not possible. Participant %s not found. NULLVOTE", participant.participantName);
    }
}


void disqualify(char *participantName, tList *list, int *NullVotes) {
    tItemL participant;
    tPosL position;
    position = findItem(participantName, *list); //We store the position in the list for the participantName
    if (!isEmptyList(*list)) { //if the list is not empty
        if (position != LNULL) {//if the participant is in the list, we will set its votes to null and we will delete the participant from the list
            strcpy(participant.participantName, participantName);
            *NullVotes += getItem(position, *list).numVotes;
            deleteAtPosition(position, list);
            printf("* Disqualify: participant %s location %s", participant.participantName,
                   participant.EUParticipant ? "eu" : "non-eu");
        } else {//if the participant is not in the list, an error message will be displayed
            printf("+ Error: Disqualify not possible");
        }
    } else { //if the list is empty, an error message will be displayed
        printf("+ Error: Disqualify not possible");
    }
}


void stats(int totalvoters, tList *list, const int *NullVotes) {
    tPosL position;
    int total = 0;
    if (!isEmptyList(*list)) { //if the list is not empty


        for (position = first(*list); position != LNULL; position = next(position, *list)) {
            total = getItem(position, *list).numVotes + total; //we iterate over the list to collect the total for valid votes
        }


        //we iterate over the list to print the message with the participantName,its location, the number of votes received per participant and its percentage (number of votes received / total valid votes)
        for (position = first(*list); position != LNULL; position = next(position, *list)) {
            if (getItem(position, *list).numVotes == 0) { //if the participant has no valid votes, we print the message
                printf("Participant %s location %s numvotes %d (0.00%s)\n", getItem(position, *list).participantName,
                       getItem(position, *list).EUParticipant ? "eu" : "non-eu", getItem(position, *list).numVotes,
                       "%");
            } else { //if the participant has received valid votes, we print the message with its corresponding percentage
                printf("Participant %s location %s numvotes %d (%.2f%s)\n", getItem(position, *list).participantName,
                       getItem(position, *list).EUParticipant ? "eu" : "non-eu", getItem(position, *list).numVotes,
                       ((float) getItem(position, *list).numVotes) / (float) total * 100, "%");
            }
        }
        printf("Null votes %d\n", *NullVotes);
        total = total + *NullVotes; //to compute the participation percentage ( total valid votes + NullVotes / totalvoters ), we have to add the nullvotes to total
        if (total == 0) {//if there are no votes
            printf("Participation: %d votes from %d voters (0.00%s)\n", total, totalvoters, "%");
        } else {
            printf("Participation: %d votes from %d voters (%.2f%s)\n", total, totalvoters,
                   (float) (total) / (float) totalvoters * 100, "%");
        }
    } else { //if the list is empty,  an error message will be displayed
        printf("+ Error: Stats not possible");
    }
}


/* ****************************************************************************************************************** */

void processCommand(char *commandNumber, char command, char *param1, char *param2, tList *list, int *NullVotes) {

    switch (command) {

        case 'N':
            printf("********************\n");
            printf("%s %c: participant %s location %s\n", commandNumber, command, param1, param2);
            new(param1, param2, list);
            printf("\n");
            break;
        case 'V':
            printf("********************\n");
            printf("%s %c: participant %s\n", commandNumber, command, param1);
            vote(param1, list, NullVotes);
            printf("\n");
            break;
        case 'D':
            printf("********************\n");
            printf("%s %c: participant %s\n", commandNumber, command, param1);
            disqualify(param1, list, NullVotes);
            printf("\n");
            break;
        case 'S':
            printf("********************\n");
            char *endptr; //pointer to the first non-numerical character
            int totalvoters = strtol(param1, &endptr,
                                     10); // we convert param1 into an int number and we store it in totalvoters, the radix is 10 because we are using a decimal base for the conversion
            printf("%s %c: totalvoters %d\n", commandNumber, command, totalvoters);
            stats(totalvoters, list, NullVotes);
            break;
        default:
            break;
    }
}


/* ****************************************************************************************************************** */

void readTasks(char *filename) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");



    tList list;
    createEmptyList(&list); //We create an empty list

    tNumVotes NullVotes = 0; //We declare a variable for storing nullvotes

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, &list, &NullVotes);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}

/* ****************************************************************************************************************** */


int main(int nargs, char **args) {

    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
#ifdef INPUT_FILE
        file_name = INPUT_FILE;
#endif
    }

    readTasks(file_name);

    return 0;
}