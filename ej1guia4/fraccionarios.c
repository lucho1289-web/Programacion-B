#include <stdio.h>
#include "fraccionarios.h"


void crear(int numeradorr,int denominadorr,Fraccion *frac)
{
frac->den=denominadorr;
frac->num=numeradorr;
}
int numerador(Fraccion f)
{ int nume;
nume=f->num;
return(nume);
}
int denominador(Fraccion f)
{
    int deno;
    deno=f->den;
    return(deno);
}

void sumar(Fraccion f1, Fraccion f2, Fraccion *total) {
    if (f1.den == f2.den) {
        total->num = f1.num + f2.num;
        total->den = f1.den;
    } else {
        // Fórmula general: (a*d + b*c) / (b*d)
        total->num = (f1.num * f2.den) + (f2.num * f1.den);
        total->den = f1.den * f2.den;
    }
}

void restar(Fraccion f1, Fraccion f2, Fraccion *total) {
    if (f1.den == f2.den) {
        total->num = f1.num - f2.num;
        total->den = f1.den;
    } else {
        total->num = (f1.num * f2.den) - (f2.num * f1.den);
        total->den = f1.den * f2.den;
    }
}

void multiplicar(Fraccion f1,Fraccion f2,Fraccion *total)
{

    total->den=f1.den*f2.den;
    total->num=f1.num*f2.num;

}





int iguales(Fraccion f1, Fraccion f2) {

    return (f1.num * f2.den == f2.num * f1.den);
}


