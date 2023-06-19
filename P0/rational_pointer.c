
/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: P0
 * AUTHOR 1: Xoel González Pereira LOGIN 1: xoel.gonzalezp
 * AUTHOR 2: Ángel Meijón de la Fuente LOGIN 2: angel.meijon
 * GROUP: 6.1
 * DATE: 08 / 02 / 23
 */

#include <stdlib.h>
#include "rational_pointer.h"

Rational createRational(int n, int d) {

    Rational temp;

    temp = malloc(sizeof(*temp));

    temp->num = n;
    temp->den = d;

    return temp;
}


int numerator(Rational r){

    return r->num;
}

int denominator(Rational r){

    return r->den;
}

Rational sum(Rational r1, Rational r2){

    Rational s = malloc(sizeof (*s));

    s->num = r1->num * r2->den + r1->den * r2->num;

    s->den = r1->den * r2->den;

    return s;

}