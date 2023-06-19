/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Xoel González Pereira LOGIN 1: xoel.gonzalezp
 * AUTHOR 2: Ángel Meijón de la Fuente LOGIN 2: angel.meijon
 * GROUP: 6.1
 * DATE: 27 / 04 / 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "jury_list.h"

#define MAX_BUFFER 255

void create(tJuryName juryName, tNumVotes totalVoters, tListJ *list);

/*
 * Goal: the jury is added to the list with its number of voters set to the given value.
 * Input: the jury, the number of totalvoters and the list of juries.
 * Output: The list with the new jury.
 * Precondition: The list exists.
 * Postcondition: none.
 */

void new(tJuryName juryName, tParticipantName participantName, char *EUParticipant, tListJ *list);

/*
 * Goal:: A new participant is added to a jury with its number of votes set to 0. EUParticipant can take the value eu or non-eu.
 * Input: The name of the jury where the participant is added, the name of the participant we want to add, its location (eu or non-eu) and the list to be modified.
 * Output: The list with the new participant.
 * Precondition: The list exists.
 * Postcondition: none.
 */

void vote(tJuryName juryName, tParticipantName participantName, tListJ *list);

/*
 * Goal: Add one vote to that participant at that jury.
 * Input: The name of the jury to which the participant belongs, the name of the participant we want to vote and the list to be modified.
 * Output: The updated list.
 * Precondition: The list exists.
 * Postcondition: none.
 */


void disqualify(tParticipantName participantName, tListJ *list);

/*
 * Goal: Disqualifies a participant. The participant is removed from the lists of all juries and all its votes become null votes.
 * Input: The name of the participant to be disqualified and the list to be modified.
 * Output: The updated list with the corresponding participants removed.
 * Precondition: The list exists.
 * Postcondition: none.
 */


void stats(tListJ *list);

/*
 * Goal: : Calculates the statistics of turnout and votes.
 * Input: The list to be modified.
 * Output: none.
 * Precondition: The list exists.
 * Postcondition: none.
 */


void Remove(tListJ *list);
/*
 * Goal: : Removes all juries with 0 valid votes.
 * Input: The list to be modified.
 * Output: The updated list with the corresponding juries removed.
 * Precondition: The list exists.
 * Postcondition: none.
 */

void winners(tListJ *list);

/*
 * Goal: : For each jury it shows the winners among the countries belonging to the European Union and among those not belonging to it.
 * Input: The list to be modified.
 * Output: none.
 * Precondition: The list exists.
 * Postcondition: none.
 */


/* ****************************************************************************************************************** */

void create(tJuryName juryName, tNumVotes totalVoters, tListJ *list) {

    tItemJ jury;
    tPosJ positionJ = findItemJ(juryName, *list); //We store the position in the list for the juryName

    if (positionJ == NULLJ) { //if the position for that jury is null

        jury.totalVoters = totalVoters; // we set the totalvoters for that jury, its nullvotes and validvotes
        jury.nullVotes = 0;
        jury.validVotes = 0;
        strcpy(jury.juryName, juryName);
        createEmptyListP(&jury.participantList); //for that jury, we create its participants list

        if (insertItemJ(jury, list)) { //if it could be inserted at the end of the list, we print the message

            printf("* Create: jury %s totalvoters %d", jury.juryName, jury.totalVoters);

        } else { //if it could not be inserted, an error message will be displayed
            printf("+ Error: Create not possible");
        }

    } else { // the jury is already in the list, so we cannot create it

        printf("+ Error: Create not possible");

    }

}


void new(tJuryName juryName, tParticipantName participantName, char *EUParticipant, tListJ *list) {


    tItemJ jury;
    tItemP participant;
    tPosJ positionJ = findItemJ(juryName, *list); //We store the positionJ in the list for the juryName
    tPosP positionP; //we create the position for the participant in the participants list for that jury


    if (positionJ != NULLJ) { //if the jury is not in the list

        jury = getItemJ(positionJ, *list); //we take the current jury
        strcpy(jury.juryName, juryName); //we store the name of the jury in the field juryName

        positionP = findItemP(participantName,
                              jury.participantList); // we store the position for the participant int list of participants of that jury

        if (positionP == NULLP) { //if the position is null

            strcpy(participant.participantName, participantName); //we store the name of the participant
            participant.numVotes = 0; //we set its votes to zero

            if (strcmp(EUParticipant, "eu") == 0) {
                participant.EUParticipant = true;
            } else if (strcmp(EUParticipant, "non-eu") == 0) {
                participant.EUParticipant = false;
            }

            if (insertItemP(participant,
                            &jury.participantList)) { //if it could be inserted at the end of the list, we print the message

                printf("* New: jury %s participant %s location %s", jury.juryName, participant.participantName,
                       participant.EUParticipant ? "eu" : "non-eu");

                updateItemJ(jury, positionJ, list); //we update the list of juries
            } else { //if it could not be inserted, an error message will be displayed
                printf("+ Error: New not possible");
            }

        } else { //if the position is not null

            printf("+ Error: New not possible");

        }

    } else {//if the jury does not exist
        printf("+ Error: New not possible");
    }
}


void vote(tJuryName juryName, tParticipantName participantName, tListJ *list) {

    tItemJ jury;
    tPosJ positionJ = findItemJ(juryName, *list); //We store the positionJ in the list for the juryName

    tPosP positionP;

    if (positionJ != NULLJ) { //if the position is not null

        jury = getItemJ(positionJ, *list); //we store the current jury
        positionP = findItemP(participantName,jury.participantList); //we store the position for  the participant that is in the participants list for that jury

        if (positionP != NULLP) {//if the participant is in the jury list, we increment its votes by one

            tItemP participant = getItemP(positionP, jury.participantList); //we take the current participant
            strcpy(participant.participantName, participantName);

            participant.numVotes =
                    getItemP(positionP, jury.participantList).numVotes + 1; //we increment its votes by one

            participant.EUParticipant = getItemP(positionP, jury.participantList).EUParticipant;

            updateItemP(participant, positionP, &jury.participantList); //we update the content in that position

            printf("* Vote: jury %s participant %s location %s numvotes %d", jury.juryName, participant.participantName,
                   participant.EUParticipant ? "eu" : "non-eu", getItemP(positionP, jury.participantList).numVotes);

            jury.validVotes = getItemJ(positionJ, *list).validVotes + 1; //we increment the valid votes for that jury
            updateItemJ(jury, positionJ, list); //we update the list of juries

        } else { //if the participant is not in the list, an error message will be displayed and the vote will be considered as null. It will be stored in NullVotes
            jury.nullVotes = getItemJ(positionJ, *list).nullVotes + 1; //we increment the number of null votes by one
            updateItemJ(jury, positionJ, list);
            printf("+ Error: Vote not possible. Participant %s not found in jury %s.  NULLVOTE",
                   participantName, jury.juryName);
        }

    } else {
        printf("+ Error: Vote not possible");
    }
}




void disqualify(tParticipantName participantName, tListJ *list) {

    tPosJ positionJ;

    if (!isEmptyListJ(*list)) { //if the list of juries is empty

        for (positionJ = firstJ(*list);positionJ != NULLJ; positionJ = nextJ(positionJ, *list)) { //we iterate over the list of juries

            tItemJ jury = getItemJ(positionJ, *list); //we take the jury
            printf("Jury %s\n", jury.juryName);


            if (jury.participantList != NULLP) { //if the participant list exists for the jury

                tPosP positionP = findItemP(participantName, jury.participantList); //we store the position of the participant in the participant list for the current jury

                if (positionP != NULLP) { // if the participant is in the local list

                    tItemP participant = getItemP(positionP, jury.participantList); //we take the participant
                    strcpy(participant.participantName, participantName);
                    jury.validVotes -=  getItemP(positionP, jury.participantList).numVotes;
                    jury.nullVotes +=  getItemP(positionP, jury.participantList).numVotes; //  participant´s votes now will be considered as null ones
                    deleteAtPositionP(positionP, &jury.participantList); //we delete the participant from the list of participants
                    updateItemJ(jury, positionJ, list); //we update the list
                    printf("Participant %s disqualified\n", participant.participantName);

                } else { //if the participant does not exist in the given local list, we print the message

                    printf("No participant %s\n", participantName);

                }

            }

            printf("\n");

        }

    } else { //if the list of juries is empty, we print the error message

        printf("+ Error: Disqualify not possible\n");

    }
}


void stats(tListJ *list) {

    int total = 0;

    tPosJ positionJ; //We store the positionJ in the list for the juryName
    if (!isEmptyListJ(*list)) { //if the list is not empty

        for (positionJ = firstJ(*list);
             positionJ != NULLJ; positionJ = nextJ(positionJ, *list)) { //we iterate over the list of juries

            tPosP positionP;
            tItemJ jury = getItemJ(positionJ, *list); //we take the jury


            printf("Jury %s\n", jury.juryName);


            if (jury.participantList == NULLP) { //if the list of participants does not exist

                printf("No participants\n");

            } else {
                for (positionP = firstP(jury.participantList);
                     positionP != NULLP; positionP = nextP(positionP,
                                                           jury.participantList)) { //we iterate over the list of participants of that jury


                    tItemP participant = getItemP(positionP,jury.participantList); //we store the current participant for the participant list in that jury


                    if (getItemP(positionP, jury.participantList).numVotes ==
                        0) { //if the participant has no valid votes, we print the message
                        printf("Participant %s location %s numvotes %d (0.00%s)\n", participant.participantName,
                               participant.EUParticipant ? "eu" : "non-eu", participant.numVotes, "%");

                    } else { //if the participant has received valid votes, we print the message with its corresponding percentage

                        printf("Participant %s location %s numvotes %d (%.2f%s)\n", participant.participantName,
                               participant.EUParticipant ? "eu" : "non-eu", participant.numVotes,
                               (float) getItemP(positionP, jury.participantList).numVotes / (float) jury.validVotes *
                               100, "%");
                    }

                }

            }

            printf("Nullvotes %d\n", jury.nullVotes); // we print the nullvotes
            total = jury.validVotes +
                    jury.nullVotes; //to compute the participation percentage ( total valid votes + NullVotes / totalvoters ), we have to add the nullvotes to total
            if (total == 0) {//if there are no votes
                printf("Participation: %d votes from %d voters (0.00%s)\n", total, jury.totalVoters, "%");
                printf("\n");
            } else {
                printf("Participation: %d votes from %d voters (%.2f%s)\n", total, jury.totalVoters,
                       (float) (total) / (float) jury.totalVoters * 100, "%");

            }

            printf("\n");
        }

    } else { //if the list is empty,  an error message will be displayed
        printf("+ Error: Stats not possible");
    }
}


void Remove(tListJ *list){

    tItemJ jury;
    tPosJ positionJ;
    char removed[10][10];
    int counter = 0;

    if (!isEmptyListJ(*list)) { //if the list of juries is not empty

        for (positionJ = lastJ(*list);positionJ != NULLJ;positionJ= previousJ(positionJ,*list)) { //we iterate over the list of juries from the last

             jury = getItemJ(positionJ, *list); //we take the jury

            if (jury.validVotes == 0) { //if the valid votes for the current jury are zero

                strcpy(removed[counter], jury.juryName); //we store in the array the name of the jury we are going to remove
                deleteAtPositionJ(positionJ,list); //we delete the jury from the list of juries
                counter++; //we increment the counter by one everytime we delete a jury

            }
        }

        if(counter > 0 ){ //if the counter is higher than zero, that means at least one jury has been removed

            for(int i = counter -1 ; i >= 0; i--){ //we iterate in reverse order to print in the correct order the juries removed

                printf("* Remove: jury %s\n", removed[i]);
            }

        } else{ //if the counter is not incremented, that means there are no deletions, so we print the error message
            printf("+ Error: Remove not possible\n");

        }

    } else {

        printf("+ Error: Remove not possible\n");

    }
}


void winners(tListJ *list) {

    tPosJ positionJ; //We store the positionJ in the list for the juryName

    if (!isEmptyListJ(*list)) { //if the list of juries is not empty

        for (positionJ = firstJ(*list);positionJ != NULLJ; positionJ = nextJ(positionJ, *list)) { //we iterate over the list of juries

            tPosP positionP;
            tItemJ jury = getItemJ(positionJ, *list); //we take the jury

            printf("Jury %s\n", jury.juryName); //we print the corresponding jury name

            if (jury.participantList ==NULLP) { //if the list of participants does not exist, there will not be valid winners

                printf("Location eu: No winner\n");
                printf("Location non-eu: No winner\n");

            } else {

                for (positionP = firstP(jury.participantList); positionP != NULLP; positionP = nextP(positionP,jury.participantList)) { //we iterate over the list of participants of that jury

                    tItemP participant = getItemP(positionP,jury.participantList); //we store the current participant for the participant list in that jury
                    tPosP pos2 = nextP(positionP,jury.participantList); //we store the next position to compare the votes of the current participant with the ones of participant2


                    if (participant.EUParticipant == true) {  //if both participants are from the same location (eu) we compare its votes

                        if (pos2 != NULLP) { //if the next position exists, it means theres more than one participant

                            tItemP participant2 = getItemP(pos2, jury.participantList);

                            if (participant2.EUParticipant == true) {

                                if (participant.numVotes <
                                    participant2.numVotes) { //we select the participant with the highest amount of votes

                                    printf("Location eu: Participant %s numvotes %d \n",
                                           participant2.participantName, participant2.numVotes);

                                } else if (participant.numVotes ==
                                           participant2.numVotes) { // if there is a tie, there is no valid winner

                                    printf("Location eu: No winner\n");

                                } else {

                                    printf("Location eu: Participant %s numvotes %d \n",
                                           participant.participantName, participant.numVotes);
                                }

                            }

                        } else {

                            if (participant.numVotes == 0 && firstP(jury.participantList) ==
                                                             lastP(jury.participantList)) { //if there is a participant with 0 votes and there is a match with the first and last position in the list, this participant will
                                //only be the valid winner
                                printf("Location eu: Participant %s numvotes %d \n", participant.participantName,
                                       participant.numVotes);
                            }

                        }
                    }else if (participant.EUParticipant == false) {//if both participants are from the same location (non-eu) we compare its votes



                        if (pos2 != NULLP) { //if the next position exists, it means there is more than one participant

                            tItemP participant2 = getItemP(pos2, jury.participantList);

                            if (participant2.EUParticipant == false) {

                                if (participant.numVotes < participant2.numVotes) { //we take the highest vote

                                    printf("Location non-eu: Participant %s numvotes %d \n",
                                           participant.participantName, participant.numVotes);

                                }
                                if (participant.numVotes ==
                                    participant2.numVotes) { //if there is a tie, there is no valid winner

                                    printf("Location non-eu: No winner\n");

                                } else {

                                    printf("Location non-eu: Participant %s numvotes %d \n",
                                           participant.participantName, participant.numVotes);

                                }
                            }
                        } else {

                            if (participant.numVotes == 0 &&
                                firstP(jury.participantList) == lastP(jury.participantList)) {

                                printf("Location non-eu: Participant %s numvotes %d \n", participant.participantName,
                                       participant.numVotes);
                            }

                        }

                    }

                }

            }
            printf("\n");
        }


    } else { //if the list is empty,  an error message will be displayed
        printf("+ Error: Winners not possible");

    }

}



/* ****************************************************************************************************************** */


void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, tListJ *list) {

    switch (command) {
        case 'C':
            printf("********************\n");
            printf("%s %c: jury %s totalvoters %s\n", commandNumber, command, param1, param2);
            char *endptr; //pointer to the first non-numerical character
            int totalvoters = strtol(param2, &endptr, 10);
            create(param1, totalvoters, list);
            printf("\n");
            break;
        case 'N':
            printf("********************\n");
            printf("%s %c: jury %s participant %s location %s\n", commandNumber, command, param1, param2, param3);
            new(param1, param2, param3, list);
            printf("\n");
            break;
        case 'V':
            printf("********************\n");
            printf("%s %c: jury %s participant %s \n", commandNumber, command, param1, param2);
            vote(param1, param2, list);
            printf("\n");

            break;
        case 'D':
            printf("********************\n");
            printf("%s %c: participant %s \n", commandNumber, command, param1);
            disqualify(param1, list);
            printf("\n");
            break;
        case 'S':
            printf("********************\n");
            printf("%s %c:\n", commandNumber, command);
            stats(list);

            break;
        case 'R':

            printf("********************\n");
            printf("%s %c:\n", commandNumber, command);
            Remove(list);
            printf("\n");

            break;
        case 'W':
            printf("********************\n");
            printf("%s %c:\n", commandNumber, command);
            winners(list);

        default:
            break;
    }
}


/* ****************************************************************************************************************** */

void readTasks(char *filename) {

    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    tListJ list;
    createEmptyListJ(&list); //We create an empty list of juries

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3, &list);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}

/* ****************************************************************************************************************** */

int main(int nargs, char **args) {

    char *file_name = "create.txt";

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