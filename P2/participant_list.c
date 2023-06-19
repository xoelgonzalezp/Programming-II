/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Xoel González Pereira LOGIN 1: xoel.gonzalezp
 * AUTHOR 2: Ángel Meijón de la Fuente LOGIN 2: angel.meijon
 * GROUP: 6.1
 * DATE: 27 / 04 / 2023
 */

#include "participant_list.h"



bool createNode(tPosP* p);


void createEmptyListP(tListP* L){
    *L = NULLP;
}

bool createNode(tPosP* p){
    *p = malloc(sizeof(**p));
    return (*p != NULLP);
}


bool isEmptyListP(tListP L){
    return (L == NULLP);
}

tPosP firstP(tListP L){
    return L;
}

tPosP lastP(tListP L){
    tPosP p;
    for(p = L; p->next != NULLP; p = p->next)
        ;
    return p;
}

tPosP nextP(tPosP p, tListP L){
    if (p->next == NULL)
        return NULLP;
    else
        return (p->next);
}

tPosP previousP(tPosP p, tListP L){
    tPosP i;
    if (p == firstP(L))
        return NULLP;
    else{
        i = firstP(L);
        for(i = firstP(L); i->next != NULLP && i->next != p; i = i->next)
            ;
        if(i->next == p)
            return i;
        else
            return NULLP;
    }
}




bool insertItemP(tItemP d, tListP *L) {
    tPosP q, p;
    if (!createNode(&q))
        return false;
    else {
        q->data = d;
        q->next = NULLP;

        if (*L == NULLP) {
            *L = q;
        } else if (strcmp(d.participantName, (*L)->data.participantName) < 0) {
            q->next = *L;
            *L = q;
        } else {
            p = *L;
            while ((p->next != NULLP) && (strcmp(p->next->data.participantName, d.participantName) < 0))
                p = p->next;
            q->next = p->next;
            p->next = q;
        }
        return true;
    }
}

void deleteAtPositionP (tPosP p, tListP* L){
    tPosP q;
    if (p == *L)
        *L = p->next;
    else
    if(p->next == NULLP)
    {
        for(q=*L; q->next != p; q=q->next)
            ;
        q->next = NULLP;
    }
    else
    {
        for(q=*L; q->next != p; q=q->next);
        q->next = p->next;
    }
}

tItemP getItemP(tPosP p, tListP L){
    return (p->data);
}

void updateItemP(tItemP n, tPosP p, tListP* L){
    p->data = n;
}

tPosP findItemP(tParticipantName d, tListP L) {
    tPosP p;
    if (isEmptyListP(L)){
        return NULLP;}
    else {
        for (p = L; ((p != NULLP) && (strcmp(p->data.participantName, d) < 0)); p = p->next)
            ;
        if (p != NULLP && strcmp(p->data.participantName, d) == 0)
            return p;
        else
            return NULLP;

    }
}

