#include <stdio.h>
#include <stdlib.h>
//desarrollar subprogramas que trabajando sobre una pila de enteros a.cuenta la cantidad de ceros que contiene b. obtenga el valor promedio sin perder la info de la pila c.calcule los valores maximo y minimo de la pila sin perder la informacion de lap ila d. quite todos los valores mayores al ultimo//

void cuentacero(tpila *penteros)
{
    int elemento,cant=0;
        while (!vaciap(*penteros))
        {
            sacap(penteros,&elemento);
            if (elemento==0)
                ++cant;
        }
        printf("cantidad de ceros %d ",cant);
}

void promedio(tpila *penteros)
{
    int elemento,cant=0,suma=0;
    tpila aux;
    iniciap(&aux);
    while(!vaciap(*penteros))
    {
        sacap(penteros,&elemento);
        ++cant;
        suma+=elemento;
        ponep(&aux,elemento);
    }
    while(!vaciap(aux))
    {
        sacap(&aux,&elemento);
        ponep(penteros,elemento);

    }
    printf("promedio %d \n",suma/cant);
}

void maxymin(tpila *penteros)
{
    int elemento, max,min;
    tpila aux;
    iniciap(&aux);
    if(!vaciap(*penteros))
    {
    sacap(penteros,&elemento);
    min=max=elemento;
    ponep(&aux,elemento);
    }
    else
    {
        printf("la pila esta vacia");
    }

    while(!vaciap(*penteros))
    {
        sacap(penteros,&elemento);
        if (elemento<min)
            min=elemento;
        else
         if (elemento>max)
            max=elemento;
        ponep(&aux,elemento);
    }
    while(!vaciap(aux))
    {
        sacap(&aux,&elemento);
        ponep(penteros,elemento);
    }
}

void quita (tpila *penteros)
{
    tpila aux;
    int ultimo,elemento;
    iniciap(&aux);
    while (!vaciap(*penteros))
    {
        sacap(penteros,&elemento);
         ponep(&aux,elemento);
    }
    ultimo=elemento;
    while(!vaciap(aux))
    {
        sacap(&aux,&elemento);
        if (elemento<=ultimo)
            ponep(penteros,elemento);
    }
}
int main()
{ tpila penteros;
    iniciap(&penteros);
    cargapila(&penteros);
    cuentacero(&penteros);
    promedio(&penteros);
    maxymin(&penteros);
    quita(&penteros);

    return 0;
}
