#include <stdio.h>
#include <stdlib.h>
int* crea();
void asigna(int*);
int suma(int,int,int);

int main()
{int *pint1,*pint2,*pint3,*pint4;
pint1=crea();
asigna(pint1);
pint2=crea();
asigna(pint2);
pint3=crea();
asigna(pint3);
 printf("%d",suma(*pint1,*pint2,*pint3));
free(pint1);
free(pint2);
free(pint3);
free(pint4);
return 0;


}
int* crea()
{ int *p;
p=(int*)malloc(sizeof(int));
return(p);
}
void asigna(int *p)
{printf("Ingrese valor");
scanf("%d",p);
}
int suma(int p1,int p2,int p3)
{
return(p1+p2+p3);
}



