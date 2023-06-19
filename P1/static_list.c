/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Xoel González Pereira LOGIN 1: xoel.gonzalezp
 * AUTHOR 2: Ángel Meijón de la Fuente * LOGIN 2: angel.meijon
 * GROUP: 6.1
 * DATE: 15 / 03 / 2023
 */

#include "static_list.h"


void createEmptyList (tList* L){
    L->lastPos = LNULL;
}

bool isEmptyList(tList L){
    if(L. lastPos == LNULL)
        return true;
    else
        return false;
}

tPosL first(tList L){
    if(L.lastPos != LNULL)
        return 0;
    else
        return LNULL;
}

tPosL last(tList L){
    if(L.lastPos != LNULL)
        return L.lastPos;
    else
        return LNULL;
}

tPosL next (tPosL p, tList L){
    if( p==L.lastPos)
        return LNULL;
    else
        return (p+1);
}

tPosL previous (tPosL p, tList L){
    if (p==0)
        return LNULL;
    else
        return (p-1);
}


bool insertItem(tItemL d, tPosL p, tList* L){
    tPosL i;
    if (L->lastPos == MAX-1){
        return false;
    }
    else {
        L->lastPos++;
        if(p==LNULL){
            L->data[L->lastPos]=d;
        }
        else{
            for(i=L->lastPos;i>=p+1;i--){
                L->data[i]=L->data[i-1];
            }
            L->data[p]=d;
        }
        return true;
    }
}

void deleteAtPosition(tPosL p, tList *L) {
    tPosL i;
    L->lastPos--;
    for( i=p ; i<=L->lastPos ; i++){
        L->data[i] = L->data[i+1];
    }
}

tItemL getItem(tPosL p, tList L){
    return (L.data[p]);
}

void updateItem(tItemL d, tPosL p, tList* L){
    L->data[p] = d;
}

tPosL findItem(tParticipantName d, tList L){
    tPosL p;
    if (L.lastPos == LNULL)
        return LNULL;
    else{
        for (p=0; ((p<L.lastPos) && (strcmp(L.data[p].participantName, d)) != 0);p++)
            ;
        {
            if (strcmp(L.data[p].participantName, d) == 0)
                return p;
            else
                return LNULL;
        }

    }
}