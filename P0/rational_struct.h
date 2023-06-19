


/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: P0
 * AUTHOR 1: Xoel González Pereira LOGIN 1: xoel.gonzalezp
 * AUTHOR 2: Ángel Meijón de la Fuente LOGIN 2: angel.meijon
 * GROUP: 6.1
 * DATE: 08 / 02 / 23
 */

#ifndef RATIONAL_RATIONAL_STRUCT_H
#define RATIONAL_RATIONAL_STRUCT_H

typedef struct Data Rational;

struct Data {
    int num;
    int den;
};

Rational createRational(int n, int d);

int numerator (Rational r);

int denominator (Rational r);

Rational sum (Rational r1, Rational r2);

#endif //RATIONAL_RATIONAL_STRUCT_H