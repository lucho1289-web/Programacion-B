//utilizar las estructuras que considere adecuadas para determinar si una palabra almacenada en una cola es palindroma. Se conoce de antemano la cantidad de letras de la palabra (N)//
void palindroma(tcola *palabra, int N)
{
    char vec[MAX],elemento;
    int i=0,verifica=1;

    while(!vaciac(*palabra))
    {
        sacac(palabra,&elemento);
        vec[i]=elemento;
        ++i;
    }
    i=0;
    while (i<=N-1 && verifica)
    {
        if (vec[i]==vec[N-1-i])

               ponec(palabra,vec[i]);


        else
        {
            verifica=0;
            ponec(palabra, vec[i]);
        }

      ++i;
    }
    if (verifica)
        printf("palabra palindroma");
    else
    {
        while (i<=N-1)
        {
          ponec(palabra,vec[i]);
          i++;
        }
        printf("palabra no palindroma");
    }

}
