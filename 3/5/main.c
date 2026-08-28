//Determinar mediante una funcion logica si una matriz cuadrada de dimension NXN es simetrica con respecto a su diagonal//
int simetrica(int N,int M ,int mat[][MAX], int j, int i)
{
    if (i==N)
        return(1);
    else
    {
        if(j<M-1)
        {
            if (mat[i][j]==mat[j][i])
                return(simetrica(N,M,mat,j+1,i));
            else
                return(0);
        }
        else
        {
            if(j==M-1)
                if (mat [i][j]==mat[j][i])
                    return(simetrica(N,M,mat,0,i+1));
                else
                    return (0);
        }
    }

}
