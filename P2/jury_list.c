/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Xoel González Pereira LOGIN 1: xoel.gonzalezp
 * AUTHOR 2: Ángel Meijón de la Fuente LOGIN 2: angel.meijon
 * GROUP: 6.1
 * DATE: 27 / 04 / 2023
 */

#include "jury_list.h"

void createEmptyListJ (tListJ* L){
    L->lastPos = NULLJ;
}

bool isEmptyListJ(tListJ L){
    if(L. lastPos == NULLJ)
        return true;
    else
        return false;
}

tPosJ firstJ(tListJ L){
    if(L.lastPos != NULLJ)
        return 0;
    else
        return NULLJ;
}

tPosJ lastJ(tListJ L){
    if(L.lastPos != NULLJ)
        return L.lastPos;
    else
        return NULLJ;
}

tPosJ nextJ (tPosJ p, tListJ L){
    if( p==L.lastPos)
        return NULLJ;
    else
        return (p+1);
}

tPosJ previousJ (tPosJ p, tListJ L){
    if (p==0)
        return NULLJ;
    else
        return (p-1);
}

bool insertItemJ (tItemJ d, tListJ *L){
    tPosJ i;
    if (L->lastPos == MAX-1){
        return false;}
    else{
        if (isEmptyListJ(*L) || (strcmp(d.juryName, L->data[L->lastPos].juryName))>0 ){
            L->lastPos++;
            L->data[L->lastPos] = d;
        }
        else{
            L->lastPos++;
            for (i = L->lastPos; i>0 && strcmp(d.juryName, L->data[i-1].juryName)<0; i--)
                L->data[i] = L->data[i-1];
            L->data[i] = d;
        }
        return true;
    }
}
void deleteAtPositionJ (tPosJ p, tListJ *L) {
    tPosJ i;
    L->lastPos--;
    for (i = p; i <= L->lastPos; i++) {
        L->data[i] = L->data[i+ 1];
    }
}

tItemJ getItemJ(tPosJ p, tListJ L){
    return (L.data[p]);
}

void updateItemJ(tItemJ d, tPosJ p, tListJ* L){
    L->data[p] = d;
}

tPosJ findItemJ (tJuryName d, tListJ L){
    tPosJ p;
    if(L.lastPos == NULLJ)
        return NULLJ;
    else if (strcmp(d, L.data[0].juryName)<0 || strcmp(d, L.data[L.lastPos].juryName)>0){
        return NULLJ;}
    else {
        for(p=0; (p<L.lastPos) && strcmp(L.data[p].juryName, d)<0; p++);

        if (strcmp(L.data[p].juryName, d)==0) return p;
        else return NULLJ;
    }
}
