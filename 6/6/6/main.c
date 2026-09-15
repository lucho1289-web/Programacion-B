#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char st3[34];
typedef char st10[10];

typedef struct nodojug{
    st10 nom;
    unsigned int edad;
    char estado;
    struct nodojug *sig;}
    nodojug;

typedef struct nodojug *tsubjug;

typedef struct nodoeq{
    st3 eq;
    int ptos;
    tsubjug subjug;
    struct nodoeq *sig;}
    nodoeq;

typedef struct nodoeq *tleq;

void cargalista(tleq *listaeq);
void listainicial (tleq listaeq , char k);
void listapuntos (tleq listaeq , int x);
int verificapuntos (tleq listaeq , st3 E, int p);
void eliminainactivos(tleq *listaeq);

/* Subprograma auxiliar para colgar jugadores rápidamente */
void agregar_jug_auto(tsubjug *sub, char nombre[], unsigned int edad, char estado) {
    tsubjug nuevo = (tsubjug)malloc(sizeof(nodojug));
    strcpy(nuevo->nom, nombre);
    nuevo->edad = edad;
    nuevo->estado = estado;
    nuevo->sig = *sub;
    *sub = nuevo;
}

/* Carga automática de equipos y jugadores respetando el orden del torneo */
void cargalista_automatica(tleq *listaeq) {
    tleq eq1, eq2, eq3, eq4;

    /* 1. Equipo: Boca (25 pts) */
    eq1 = (tleq)malloc(sizeof(nodoeq));
    strcpy(eq1->eq, "Boca");
    eq1->ptos = 25;
    eq1->subjug = NULL;
    // Jugadores de Boca (Probamos inicial 'M' y estados 'A'/'S')
    agregar_jug_auto(&(eq1->subjug), "Marcos", 31, 'A');
    agregar_jug_auto(&(eq1->subjug), "Mateo", 22, 'S'); // Inactivo para probar d)
    agregar_jug_auto(&(eq1->subjug), "Lucas", 26, 'A');

    /* 2. Equipo: River (22 pts) */
    eq2 = (tleq)malloc(sizeof(nodoeq));
    strcpy(eq2->eq, "River");
    eq2->ptos = 22;
    eq2->subjug = NULL;
    // Jugadores de River
    agregar_jug_auto(&(eq2->subjug), "Martin", 28, 'A');
    agregar_jug_auto(&(eq2->subjug), "Manuel", 19, 'A');
    agregar_jug_auto(&(eq2->subjug), "Julian", 24, 'S'); // Inactivo para probar d)

    /* 3. Equipo: Independiente (18 pts) - Empate en puntos con Racing */
    eq3 = (tleq)malloc(sizeof(nodoeq));
    strcpy(eq3->eq, "Independiente");
    eq3->ptos = 18;
    eq3->subjug = NULL;
    agregar_jug_auto(&(eq3->subjug), "Maxi", 27, 'A');
    agregar_jug_auto(&(eq3->subjug), "Rodrigo", 30, 'S');

    /* 4. Equipo: Racing (18 pts) - Va después de Independiente por orden alfabético */
    eq4 = (tleq)malloc(sizeof(nodoeq));
    strcpy(eq4->eq, "Racing");
    eq4->ptos = 18;
    eq4->subjug = NULL;
    agregar_jug_auto(&(eq4->subjug), "Gabriel", 25, 'A');
    agregar_jug_auto(&(eq4->subjug), "Tomas", 21, 'A');

    /* Enlace de la lista principal en orden: eq1 -> eq2 -> eq3 -> eq4 -> NULL */
    eq1->sig = eq2;
    eq2->sig = eq3;
    eq3->sig = eq4;
    eq4->sig = NULL;

    /* Asignamos el primer nodo a la cabeza de la lista */
    *listaeq = eq1;

    printf(">>> Lista precargada con exito (4 equipos y 10 jugadores). <<<\n\n");
}
void listainicial (tleq listaeq , char k)
{ int cont = 0, max = 0, contclub;
  st3 maxclub ;
  tleq auxeq = listaeq;
  tsubjug auxjug;

  while (auxeq !=NULL)
  { contclub = 0;
    auxjug = auxeq->subjug;
    while (auxjug !=NULL)
    { if (auxjug->nom[0] == k)
      { printf("jugador que empieza por la letra dada, %c, : %s \n", k,auxjug->nom);//(*auxjug->nom)
        ++cont; ++contclub;
      }
      auxjug = auxjug->sig;
    }
    if (contclub > max)
    { strcpy(maxclub, auxeq->eq);
      max = contclub;
    }
    auxeq = auxeq->sig;
  }
  printf("cant de jugadores listados, %d, club que tiene mas jugadores que cumplen, %s \n", cont, maxclub);//*maxclub
}

void listapuntos (tleq listaeq , int x)
{ tleq auxeq = listaeq;
  tsubjug auxjug;
  int cantjug , acumedad ;

  while (auxeq->ptos > x)
  { auxjug = auxeq->subjug;
    cantjug = 0; acumedad = 0;
    printf("club %s \n", auxeq->eq);

    while (auxjug != NULL)
    { printf("jugador: %s \n", auxjug->nom);//*(auxjug->nom)
      ++cantjug;
      acumedad += auxjug->edad;
      auxjug=auxjug->sig;
    }
    printf("promedio de edad: %d \n", acumedad/cantjug);
    auxeq=auxeq->sig;
  }
}

int verificapuntos (tleq listaeq, st3 E, int p)
{ tleq auxeq = listaeq;

  while ( auxeq->ptos > p && strcmp(auxeq->eq, E) != 0)
      auxeq = auxeq->sig;
  if (auxeq==NULL)
    return(0);

  if (strcmp(auxeq->eq, E) == 0 && auxeq->ptos == p)
      return(1);

  else
  { if (auxeq->ptos == p)
    { while (strcmp(auxeq->eq, E) != 0 && auxeq->ptos == p)
          auxeq = auxeq->sig;
      if (auxeq->ptos != p)
          return(0);
      else
          return(1);
    }
    else
        return(0);
  }
}

void eliminainactivos(tleq *listaeq)
{ tleq auxeq = *listaeq;
  tsubjug actjug, antjug, elim;

  while (auxeq != NULL)
  { antjug = NULL;
    actjug = auxeq->subjug;

    while (actjug != NULL)
    {
      if (actjug->estado == 'S')
      { elim = actjug; actjug = actjug->sig;
        if (antjug == NULL)
            auxeq->subjug = actjug;
        else
            antjug->sig = actjug;
        free(elim);
      }
      else
      { antjug = actjug;
        actjug = actjug->sig;
      }


    }
    auxeq=auxeq->sig;

  }
}

int main()
{ tleq listaeq =NULL;
  char k;
  int x, p;
  st3 E;
  cargalista_automatica(&listaeq);
  printf("Ingrese caracter para listar nombres de jugadores con esa inicial, ademas de mostrar cantidad de jugadores que cumplen y club que mas jugadores con esa inicial tienen \n");
  scanf("%c", &k);
  listainicial (listaeq, k);

  printf("Ingrese puntos para mostrar equipos que al menos tengan esos puntos, ademas de todos sus jugadores y promedio de edad \n");
  scanf("%d", &x);
  listapuntos ( listaeq,  x);

  printf("Ingrese equipo y puntos para verificar si ese equipo tiene esos puntos \n");
  scanf("%s", E);
  scanf("%d", &p);

  if (verificapuntos (listaeq,  E,  p) == 1)
      printf("El equipo %s tiene esos puntos \n", E);
  else
      printf("El equipo %s no tiene esos puntos \n", E);

  eliminainactivos(&listaeq);
  return(1);
}
