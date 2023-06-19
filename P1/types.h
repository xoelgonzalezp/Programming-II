/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Xoel González Pereira LOGIN 1: xoel.gonzalezp
 * AUTHOR 2: Ángel Meijón de la Fuente * LOGIN 2: angel.meijon
 * GROUP: 6.1
 * DATE: 15 / 03 / 2023
 */

#ifndef PRO2_2023_P1_TYPES_H
#define PRO2_2023_P1_TYPES_H
#define NAME_LENGTH_LIMIT 25
#include <stdbool.h>

typedef char tParticipantName[NAME_LENGTH_LIMIT];
typedef int tNumVotes;
typedef bool tEUParticipant;

typedef struct tItemL {
    tParticipantName participantName;
    tNumVotes numVotes;
    tEUParticipant EUParticipant;
} tItemL;

#endif //PRO2_2023_P1_TYPES_H
