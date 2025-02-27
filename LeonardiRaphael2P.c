
#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/*                                               */
/*                sucre syntaxique               */
/*                                               */
/*************************************************/

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then


int CompteMallocInt = 0;
int CompteMallocListe = 0;



typedef enum { FALSE, TRUE} bool;

/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/

typedef struct Bloc
{
    int nombre;
    struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste ;

/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/

/* initialise une Liste � vide */
void initVide(Liste *L);

/* renvoie 1 si la Liste en parametre est vide, 0 sinon */
bool estVide(Liste l);

/* renvoie le premier element de la Liste en parametre */
int premier(Liste l);

/* renvoie une nouvelle Liste correspondant a celle en parametre, avec l'element x ajoute en haut de la pile */
Liste ajoute(int x, Liste l);

/* modifie la Liste en parametre: x est ajoute comme premier element */
void empile(int x, Liste* L);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son premier element */
Liste suite(Liste l);

/* modifie la Liste en parametre: le premier element est retire */
void depile(Liste* l);

/* affichage simple en recursif et en iteratif */
void affiche_rec(Liste l);
void affiche_iter(Liste l);

/* longueur en recursif et en iteratif */
int longueur_rec (Liste l);
int longueur_iter (Liste l);

/*  Elimination du dernier element en recursif et en iteratif  */
/*  VD est la sousprocedure utilitaire de la version recursive */
void VD (Liste *L);
void VireDernier_rec (Liste *L);
void VireDernier_iter (Liste *L);


/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/


void initVide( Liste *L)
{
    *L = NULL ;
}

bool estVide(Liste l)
{
    return l == NULL ;
}

int premier(Liste l)
{
    return l->nombre ; 
}

Liste ajoute(int x, Liste l)
{
    Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    CompteMallocInt++;
    tmp->nombre = x ;
    tmp->suivant = l ;
    return tmp ;
}

void empile(int x, Liste *L)
{
      *L = ajoute(x,*L) ; 
}

Liste suite(Liste l)
{
    return l->suivant ;
}


void depile(Liste *L)
{
    Liste tmp = *L ;
    *L = suite(*L) ;
    free(tmp) ;
}

/*************************************************/
/*                                               */
/*     Affiche, avec les briques de base         */
/*                                               */
/*************************************************/




void affiche_rec(Liste l)
{
    if(estVide(l))
        printf("\n");
    else
    {
        printf("%d ", premier(l));
        affiche_rec(suite(l));
    }
}


void affiche_iter(Liste l)
{
    Liste L2 = l;
    while(!estVide(L2))
    {
        printf("%d ", premier(L2));
        L2 = suite(L2);
    }
    printf("\n");
}

/*************************************************/
/*                                               */
/*     Longueur, sans les briques de base        */
/*                                               */
/*************************************************/

int longueur_rec (Liste l)
{
    if (l == NULL)
         return 0 ;
    else return (1 + longueur_rec(l->suivant)) ;
}


int longueur_iter (Liste l)
{
    Liste P = l;
    int cpt = 0 ;
    while (P ISNOT NULL)
    {   P = P->suivant ;
        cpt++ ;
    }
    return cpt ;
}

/*************************************************/
/*                                               */
/*       VireDernier,                            */
/*               sans les briques de base,       */
/*               ni le "->"                      */
/*                                               */
/*************************************************/

void VD (Liste *L)
          // *L non NULL ie liste non vide
{
     if ( ((**L).suivant) == NULL )
            depile(L) ;   // moralement : depile(& (*L)) ;
     else VD (& ( (**L).suivant )) ;
}

void VireDernier_rec (Liste *L)
{
     if ( (*L) ISNOT NULL )
          VD(L);        // moralement : VD(& (*L)) ;
}

void VireDernier_iter (Liste *L)
{
    if ( (*L) ISNOT NULL)
    {
        while ( ((**L).suivant) ISNOT NULL )
                 L = & ( (**L).suivant ) ;
        free(*L) ;
        *L = NULL ;
     }
}


/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideListe(Liste *L)
{
    if(NOT(estVide(*L)))
    {
        depile(L);
        VideListe(L);
    }
      
}

/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/






void poup (Liste l)
{
        printf("Double Affichage \n") ;
        affiche_rec(l) ;
        affiche_iter(l) ;

        printf("Longueur en double %d %d \n\n", 
                           longueur_rec(l), 
                           longueur_iter(l) 
               ) ;
}



typedef struct Bloc_liste{
    Liste liste;
    struct Bloc_liste *suivant;
    
}Bloc_liste;

typedef Bloc_liste *Liste_liste;

void initvideLL(Liste_liste *LL){
    *LL = NULL;
}
int estVideLL(Liste_liste LL){
    return LL == NULL;
}

Liste_liste ajouteLL(Liste L, Liste_liste LL){
    
    Liste_liste tmp = (Liste_liste) malloc(sizeof(Bloc_liste)) ;
    CompteMallocListe++;
    tmp->suivant = LL;
    tmp->liste = L;
    return tmp ;
}

Liste premierLL(Liste_liste LL){
    return LL->liste;
}

Liste_liste suiteLL(Liste_liste LL){
    return LL->suivant;
}

void afficheLL(Liste_liste LL){
    if (estVideLL(LL)){
        printf("\n");
    }else{
        affiche_iter(premierLL(LL));
        afficheLL(suiteLL(LL));
    }

}

int tailleLL(Liste_liste *LL){
    if (estVideLL(*LL)){
        return 0;
    }else{
        return 1 + tailleLL(&(*LL)->suivant);
    }
}



Liste_liste Concat(Liste_liste LL1, Liste_liste LL2){
    if (estVideLL(LL1)){
        return LL2;
    }else{
        return ajouteLL(premierLL(LL1), Concat(suiteLL(LL1), LL2));
    }
}


void TestConcat(){
    printf("test concat\n");
    Liste li1;
    initVide(&li1);
    empile(4, &li1);  empile(2, &li1); empile(3, &li1);
    empile(7, &li1);
    // li1 = [7,3,2,4]

    Liste li2;
    initVide(&li2);
    empile(8, &li2);  empile(5, &li2);  empile(6, &li2); 
    // li2 = [6,5,8]
    Liste li3;
    initVide(&li3);
    empile(13, &li3); empile(11, &li3);  empile(1, &li3); 
    empile(4, &li3); empile(15, &li3);  
    // li3 = [15,4,1,11,13]

    Liste li4;
    initVide(&li4);
    empile(19, &li4); empile(80, &li4);  
    // li4 = [80, 19]-+

    Liste_liste LL2;initvideLL(&LL2);
    Liste_liste LL1; initvideLL(&LL1);

    LL1 = ajouteLL(li1, LL1);
    LL1 = ajouteLL(li2, LL1);

    //afficheLL(LL2);
    LL2 = ajouteLL(li3, LL2);
    LL2 = ajouteLL(li4, LL2);
    Liste_liste LL3 = Concat(LL1, LL2);
    printf("Test concat, doit afficher en sautant à la ligne à chaque |  : ");
    printf("6 5 8 | 7 3 2 4| 80 19 | 15 4 1 11 13 \n");
    afficheLL(LL3);
}


Liste_liste AETTL(int x , Liste_liste LL){
    if (estVideLL(LL)){
        return LL;
    }else{
        return ajouteLL(ajoute(x, premierLL(LL)), AETTL(x, suiteLL(LL)));
    }
}

Liste_liste ATP(int x, Liste l1){
    if (estVide(l1)){
        Liste_liste L;initvideLL(&L);
        Liste liste; initVide(&liste); empile(x, &liste);
        return ajouteLL(liste, L);
    }else{
        return ajouteLL(ajoute(x, l1), AETTL(premier(l1), ATP(x, suite(l1))));
    }
}


Liste_liste ATLTP(int x, Liste_liste L){
    if (estVideLL(L)){
        return L;
    }else{
        return Concat(ATP(x, premierLL(L)), ATLTP(x, suiteLL(L)));
    }
}

Liste_liste Permutations(int n){
    if (n == 0){
        Liste_liste L;initvideLL(&L);
        Liste liste; initVide(&liste);
        return ajouteLL(liste, L);
    }else{
        return ATLTP(n, Permutations(n -1));
    }
}

void TestPermutation(){
    printf("Test permutation  sur liste vide, ne doit rien afficher : \n");
    Liste_liste LL = Permutations(0);
    afficheLL(LL);
    CompteMallocInt = 0;
    CompteMallocListe = 0;
    LL = Permutations(3);
    printf("Test permutation pour n = 3, doit afficher toutes les permutations de 1 2 3 :\n");

    afficheLL(LL);
    printf("Toujours pour n = 3, On a fait %d malloc pour les entiers et %d malloc pour les liste d'entiers.\n", CompteMallocInt, CompteMallocListe);
    printf("\n");
    CompteMallocInt = 0;
    CompteMallocListe = 0;
    LL = Permutations(4);
    printf("Test longueur liste permutation pour n = 4 , doit afficher 24 : %d\n", tailleLL(&LL));
    printf("Toujours pour n = 4, On a fait %d malloc pour les entiers et %d malloc pour les liste d'entiers.\n", CompteMallocInt, CompteMallocListe);
    printf("\n");
    CompteMallocInt = 0;
    CompteMallocListe = 0;
    LL = Permutations(5);
    printf("Test longueur liste permutation pour n = 5 , doit afficher 120 : %d\n", tailleLL(&LL));
    printf("Toujours pour n = 5, On a fait %d malloc pour les entiers et %d malloc pour les liste d'entiers.\n", CompteMallocInt, CompteMallocListe);
    printf("\n");
     CompteMallocInt = 0;
    CompteMallocListe = 0;
    LL = Permutations(6);
    printf("Test longueur liste permutation pour n = 6 , doit afficher 720 : %d\n", tailleLL(&LL));
    printf("Toujours pour n = 6, On a fait %d malloc pour les entiers et %d malloc pour les liste d'entiers.\n", CompteMallocInt, CompteMallocListe);
    printf("\n");
}


int main(int argc, char** argv)
{
    Liste l ;

        initVide (&l) ;

          poup(l) ;

             empile(4, &l) ;

          poup(l) ;

             empile(5, &l) ;
             empile(6, &l) ;
             empile(7, &l) ;
             empile(8, &l) ;
             empile(9, &l) ;

          poup(l) ;

        VireDernier_rec  (&l) ;
        VireDernier_iter (&l) ;
        depile(& l) ;

          poup(l) ;

    TestConcat();
    TestPermutation();

    printf("\n");
    return 0;
}




