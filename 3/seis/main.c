//dada una matriz de NxM enteros, determinar si la suma de los elementos de cada fila es mayor a la suma de los elementos de la fila anterior

int sumant(int mat[][MAX],int N,int M ,int i,int j,int ant,int act)
{
    if(i==N )

            return 1;

    else
    {

            if (j<=M-1)
                return(sumant(mat,N,M,i,j+1,ant,act+mat[i][j]));
            else
            {
                if(act>ant)
                    return(sumant(mat,N,M,i+1,0,act,0));
                else
                    return 0;
            }

    }

}
