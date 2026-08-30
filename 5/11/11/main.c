#include <stdio.h>
#include <stdlib.h>
#include <colas.h>
//simular una fila de empleados para usar un horno microondas en el comedor de una empresa.\\
 \\para cada empleado se tiene numero de legajo , momento de arribo en segundos a partir de las 12 y la cantidad de segundos que piensa usar el horno, el programa debe mostrar p cada empleado el tiempo en que empieza y termina el uso del horno al finalizar mostrar tiempo promedio de espera y legajo con mayor tiempo de espera//
void cargamicro(tcola *microondas)
{

}
void microondas (tcola *microondas)
{
    telemento r;
    int acum=0,empieza,max=-1,espera,legajomax,acumespera=0,cant=0;
    while(!vaciac(*microondas))
    {
        sacac(microondas,&r);
        if(r.llega>=acum)
        {
            empieza=r.llega;
            acum=r.llega+r.calienta;
        }

        else
        {
            empieza=acum;
            acum=acum+r.calienta;
        }

        printf("llego a las %d,empezo a las %d, se fue a las %d", 12+r.llega/3600,empieza,12+acum/3600);
        ++cant;
        espera=acum-r.llega-r.calienta;
        acumespera+=espera;
        if (espera>max)
        {
            max=espera;
            legajomax=r.legajo;
        }
    }
    printf("espera promedio %d legajo con mas espera %d",acumespera/cant,legajomax);
}
