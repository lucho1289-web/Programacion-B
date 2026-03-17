#include <stdio.h>
void conversor(int);

int main()
{
    int convertir;
    printf("Ingrese cantidad de segundos a convertir");
    scanf("%d",&convertir);
    conversor(convertir);
    return 0;

}

void conversor(int convertir)
{
    int h=0,m=0,s=0;
    if (convertir>60)
    {
        s=convertir%60;
        convertir/=60;
        if (convertir>60)
        {
            m=convertir%60;
            h=convertir/60;
        }
        else
            m=convertir;

    }
    else
        s=convertir;

   printf("%d:%d:%d", h, m, s);

}



