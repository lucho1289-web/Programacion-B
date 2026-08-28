void genera(int a[], int b[], int N, int M, int i, int j, int c[], int *k)
{
    // Mientras haya elementos en alguno de los dos arreglos
    if (i < N || j < M)
    {
        if (i == N)
        {
            // Si el arreglo 'a' se terminó
            c[*k] = b[j];
            ++(*k);
            genera(a, b, N, M, i, j + 1, c, k);
        }
        else if (j == M)
        {
            // Si el arreglo 'b' se terminó
            c[*k] = a[i];
            ++(*k);
            genera(a, b, N, M, i + 1, j, c, k);
        }
        else
        {
            // Si ambos tienen elementos, comparamos
            if (a[i] == b[j])
            {
                c[*k] = a[i];
                ++(*k);
                // Avanzamos ambos índices para evitar el duplicado en 'c'
                genera(a, b, N, M, i + 1, j + 1, c, k);
            }
            else if (a[i] > b[j])
            {
                c[*k] = b[j];
                ++(*k);
                genera(a, b, N, M, i, j + 1, c, k);
            }
            else
            {
                c[*k] = a[i];
                ++(*k);
                genera(a, b, N, M, i + 1, j, c, k);
            }
        }
    }
}
