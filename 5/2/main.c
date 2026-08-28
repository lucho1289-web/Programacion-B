//ingresar en una pila los caracteres almacenados (uno por linea ) en un archivo de texto.Mostrar el contenido de la pila, manteniendo la info en la pila

void ingresa (tpila *ptexto)
{
    FILE *texto;
    char caracter;

    texto=fopen("texto.txt","rt");
    iniciap(ptexto);
    while(fscanf(texto,"%c",&caracter)==1)
    {
        ponep(ptexto,caracter);
    }
    fclose(texto);

}

void muestra(tpila *ptexto)
{
    tpila aux;
    char caracter;
    iniciap(&aux);
    while(!vaciap(*ptexto))
    {
        sacap(ptexto,&caracter);
        printf("%c",caracter);
        ponep(&aux,caracter);
    }

    while(!vaciap(aux))
    {
        sacap(&aux,caracter);
        ponep(ptexto,caracter);
    }
}
