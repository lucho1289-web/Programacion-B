typedef struct {
                int num;
                int den;
                }Fraccion;

 void crear(int,int);
 int numerador(Fraccion);
 int denominador(Fraccion);
 void sumar(Fraccion,Fraccion,*Fraccion);
 void restar(Fraccion,Fraccion,*Fraccion);
 void multiplicar(Fraccion,Fraccion,*Fraccion);
 void dividir(Fraccion,Fraccion,*Fraccion);
 void simplificar(Fraccion,Fraccion);
 int iguales(Fraccion,Fraccion);

