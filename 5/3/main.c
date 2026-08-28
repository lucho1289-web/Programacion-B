//ingresar los numeros de dni de los votantes de una mesa a medida que van votando y mostrar los ultimos N (es dato) votantes. en el orden inverso, comenzando por el ultimo y luego en el orden que sufragaron

void ingresa(tpila *votan)
{
    st8 dni;
    iniciap(votan);
    printf("ingrese dni , x para salir /n");
    scanf("%s ",dni);
    while(strcmp(dni,"x")!=0)
    {

        ponep(votan,dni);
        printf("ingrese dni, x para salir\n");
        scanf("%s ",dni);
    }
}

void muestra(tpila *votan,int N)
{
    st8 dni;
    int i=1;
    tpila aux;
    iniciap(&aux);
    while(i<=N && !vaciap(*votan))
    {
        sacap(votan,dni);
        printf("%s",dni);
        ponep(&aux,dni);
        ++i;
    }
    while(!vaciap(aux))
    {
        sacap(&aux,&dni);
        ponep(votan,dni);
    }
}

void muestrareves(tpila *votan, int N)
{
    st8 dni;
    tpila aux;
    int i=1;

    iniciap(&aux);

    while(i<=N && !vaciap(*votan))
    {
        sacap(votan,dni);
        ponep(&aux,dni);
        ++i;
    }

    while(!vaciap(aux))
    {
        sacap(&aux,dni);
        printf("%s",dni);
        ponep(votan,dni);
    }
}
