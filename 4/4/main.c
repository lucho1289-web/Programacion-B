//Dada una matriz A de NXM float, retornar la cantidad de veces que un valor X aparece en A


int cantapariciones(float mat[][MAX],int N, int j, int M, float x)
{
    if(N==0 && M==0)
        return(mat[N][M]==x);
    else
    {
        if(M>0)
            return((mat[N][M]==x)+cantapariciones(mat,N,j,M-1,x));
        else
            return((mat[N][M]==x)+cantapariciones(mat,N-1,j,j,x));


    }


}
