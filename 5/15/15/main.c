#include <stdio.h>
#include <stdlib.h>
#include "colas.h"
#include "pilas.h"
#define MAX 30

//Un sistema de inscripcion a una maraton toma los datos de una cola de competidores (apellido y nombre) y genera las identificaciones apilandolas segun la inicial de los apellidos; debido a la gran cantidad de inscriptos se pide implementar una pila por cada inicial
//mostrar los datos de la pila de los apellidos que comienzan con una letra solicitada al operador//
typedef struct vinicial
{
    char inicial;
    tpila pila;
} vinicial;
typedef char st10[11];


void genera(tcola *inscriptos,vinicial v[])
{
    st10 elemento;
    int i;

    while (!vaciac(*inscriptos))
    {   i=0;
        sacac(inscriptos,&elemento);
        while(v[i].inicial!=elemento[0])
            ++i;
        ponep(v[i].pila,elemento);
    }
}

void muestra(vinicial v[],char letra)
{
    int i=0;
    st10 elemento;

    while (v[i].inicial!=letra)
    ++i;

    while(!vaciap(*(v[i].pila))
    {
        sacap(v[i].pila,&elemento);
        printf("%s",elemento);
    }
}
int main()
{
    vinicial v[MAX];
    tcola inscriptos;
    char letra;
    printf("escriba una letra para ver todos los apellidos \n");
    scanf("%c",&letra);
    genera(&inscriptos,v);
    muestra(v,letra);
    return 0;
}
