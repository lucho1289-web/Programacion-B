#include <stdio.h>
#include <stdlib.h>
//Ingresar una secuencia de caracteres terminada en punto que representa una expresion aritmetica, comprobar que los parentesis esten balanceados, de no ser asi informar si falta izquierdo o derecho, los parentesis son los unicos simbolos a controlar//
void cargacola (tcola *aritmetica)
{
    char elemento;
    iniciac(aritmetica);
    printf("ingrese elemento de la expresion \n");
    scanf(" %c",&elemento);
    ponec(aritmetica,elemento);

    while(elemento!='.')
    {
    printf("ingrese elemento de la expresion \n");
    scanf(" %c",&elemento);
    ponec(aritmetica,elemento);
    }
}

void verificacola(tcola *aritmetica)
{
    tcola aux;
    int abre=0,cierra=0,cumple=1;
    char elemento;
    iniciac(&aux);
    while(!vaciac(*aritmetica)&& cumple)
    {
        sacac(aritmetica,&elemento);
        if(elemento=='(')
        {
            ++abre;
            ponec(&aux,elemento);
        }
        else
        {
            if(elemento==')'&& abre>cierra)
            {
                ++cierra;
                ponec(&aux,elemento);
            }
            else
            {
                if (elemento==')' && abre<=cierra)

                    cumple=0;
                else
                        ponec(&aux,elemento);

            }
        }
    }
    if (abre==cierra && cumple )
    {
       printf("expresion aritmetica correcta \n");
       while (!vaciac(aux))
       {
           sacac(&aux,&elemento);
           ponec(aritmetica,elemento);
       }
    }
    else
    {
       if (abre>cierra)
            printf("expresion aritmetica incorrecta, falta parentesis derecho \n");
       else
            printf("expresion aritmetica incorrecta,falta parentesis izquierdo \n");
    }

}

int main()
{   tcola aritmetica;

    cargacola(&aritmetica);
    verificacola(&aritmetica);
    return 0;
}
