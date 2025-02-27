
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



bool UnPlusDeuxEgalTrois(Liste l){
    if (estVide(l)){
        return TRUE;
    }else{
        int p1 = premier(l);
        int p2;
        int p3;
        if (estVide(suite(l))){
            p2 = 0;
            p3 = 0;
        }else{
            p2 = premier(suite(l));
            if (estVide(suite(suite(l)))){
                p3 = 0;

            }else{
                p3 = premier(suite(suite(l)));
            }
        }
        if (p1 +p2 == p3){
            return TRUE;
        }else{
            return FALSE;
        }

    }
}


bool croissante(Liste l){

    
    bool croiss(Liste l, int element){
        if (estVide(l)){
            return TRUE;
        }else{
            int tete = premier(l);
            if (tete < element){
                return FALSE;
            }else{
                return croiss(suite(l), tete);
            }
        }
    }
    if (estVide(l)){
        return FALSE;
    }else{
        return croiss(suite(l), premier(l));
    }

}

int NombreMemePosition_rec(Liste l1, Liste l2){
    if (estVide(l1) || estVide(l2)){
        return 0;
    }
    else{
        return (premier(l1) == premier(l2)) + NombreMemePosition_rec(suite(l1), suite(l2));
    }
}

int NombreMemePosition_iter(Liste L1, Liste L2){
    int compteur = 0;
    int t1;
    int t2;
    while(!(estVide(L1) || estVide(L2))){
        t1 = premier(L1);
        t2 = premier(L2);
        if (t1 == t2){
            compteur++;
        }
        L1 = suite(L1);
        L2 = suite(L2);
    }
    return compteur;
}


int SousNombreMemePositionTerminale(Liste L1, Liste L2, int acc){
    if (estVide(L1) || estVide(L2)){
        return acc;
    }else{
        return SousNombreMemePositionTerminale(suite(L1), suite(L2), acc + (premier(L1) == premier(L2)) );
    }

}

int NombreMemePositionTerminale(Liste L1, Liste L2){
    return SousNombreMemePositionTerminale(L1, L2, 0);
}

void SousProcedureNombreMemePosition(Liste L1, Liste L2, int *acc){
    if (estVide(L1) || estVide(L2)){
        return;
    }else{
        if (premier(L1) == premier(L2)){
            *acc = *acc + 1;
        }
        SousProcedureNombreMemePosition(suite(L1), suite(L2), acc);
    }
}

int ProcedureNombreMemePosition(Liste L1, Liste L2){
    int compteur = 0;
    SousProcedureNombreMemePosition(L1, L2, &compteur);
    return compteur;
}

Liste SousFoncVireDernierRec(Liste L){
 
    if (estVide(suite(L))){
        Liste vide;
        initVide(&vide);
        return vide;}
    else{
        return ajoute(premier(L), SousFoncVireDernierRec(suite(L)));

    }

}

Liste FoncVireDernierRec(Liste L){
    if (estVide(L)){
        return L;
    }else{
        return SousFoncVireDernierRec(L);
    }
}

Liste FoncVireDernierIter(Liste L){
    if (estVide(L) || estVide(suite(L))){
        Liste vide;
        initVide(&vide);
        return vide;
    }else{
        Liste rep = L;
        Liste tmp = rep;
        while(!(estVide(suite(suite(rep))))){
            rep = suite(rep);

        }
        Liste vide;
        initVide(&vide);
        rep->suivant = vide;
        return tmp;

    }
}




void testUnPlusDeuxEgalTrois(){
    Liste L1;
    initVide(&L1);

    
    empile(29, &L1); empile(4, &L1); empile(8, &L1); empile(5, &L1);  empile(3, &L1); 
    Liste L2; initVide(&L2);
    empile(2, &L2); empile(2, &L2);
    Liste L3; initVide(&L3);
    empile(1, &L3); empile(7, &L3);empile(3, &L3);empile(2, &L3);
    bool aucunProblemes = TRUE;

    if (UnPlusDeuxEgalTrois(L1) == FALSE){
        printf("Erreur UnPlusDeuxEgalTrois sur [3,5,8,4,29].\n");
        aucunProblemes = FALSE;
    }

    if (UnPlusDeuxEgalTrois(L2) == TRUE){
        printf("Erreur UnPlusDeuxEgalTrois sur [2,2].\n");
        aucunProblemes = FALSE;
    }

    if (UnPlusDeuxEgalTrois(L3) == TRUE){
        printf("Erreur UnPlusDeuxEgalTrois sur [2,3,7,1].");
        aucunProblemes = FALSE;
    }
    if (aucunProblemes == TRUE){
        printf("Aucun problèmes pour UnPlusDeuxEgalTrois.\n");
    }

}

void testCroissante(){
    Liste L1;
    bool aucunProbleme = TRUE;
    initVide(&L1);
    

    if (croissante(L1) == TRUE){
        printf("Erreur croissante sur [].\n");
        aucunProbleme = FALSE;
    }
    empile(40, &L1); empile(24, &L1); empile(20, &L1); empile(8, &L1);
    if (croissante(L1) == FALSE){
        printf("Erreur croissante sur [8,20,24,40].\n");
        aucunProbleme = FALSE;
    }
    Liste L2;
    empile(40, &L2); empile(24, &L2); empile(100, &L2); empile(8, &L2); empile(1, &L2);
    if (croissante(L2) == TRUE){
        printf("Erreur croissante sur [8,1,100,24,40].\n");
        aucunProbleme = FALSE;
    }
    if (aucunProbleme == TRUE){
        printf("Aucun problèmes pour croissante.\n");
    }
}

void testNombreMemePosition(){
    Liste L1 ;
    Liste L2 ;
    initVide(&L1);
    initVide(&L2);
     
    empile(2, &L1); empile(9, &L1); empile(2, &L1); empile(4, &L1); empile(3, &L1);
    empile(0, &L1); empile(9, &L1); empile(6, &L1); empile(3, &L1);

    empile(5, &L2); empile(2, &L2); empile(2, &L2); empile(2, &L2); empile(2, &L2);
    empile(2, &L2); empile(2, &L2); empile(0, &L2); empile(6, &L2); empile(9, &L2);
    empile(3, &L2);


    bool aucunProbleme = TRUE;
    if (NombreMemePosition_rec(L1,L2) != 4){
        printf("Probleme testNombreMemePosition récursif.\n");
        affiche_rec(L1);
        affiche_rec(L2);
        printf("%d", NombreMemePosition_rec(L1, L2));
        aucunProbleme = FALSE;
    }

    if (NombreMemePosition_iter(L1,L2) != 4){
        printf("Probleme testNombreMemePosition itératif.\n");
        affiche_rec(L1);
        affiche_rec(L2);
        printf("%d", NombreMemePosition_iter(L1, L2));
        aucunProbleme = FALSE;
    }

    if (NombreMemePositionTerminale(L1, L2) != 4){
        printf("Probleme testNombreMemePosition récursif terminale.\n");
        affiche_rec(L1);
        affiche_rec(L2);
        printf("%d", NombreMemePositionTerminale(L1, L2));
        aucunProbleme = FALSE;
    }

    if (ProcedureNombreMemePosition(L1, L2) != 4){
        printf("Probleme testNombreMemePosition sous procédure terminale.\n");
        affiche_rec(L1);
        affiche_rec(L2);
        printf("%d", NombreMemePositionTerminale(L1, L2));
        aucunProbleme = FALSE;
    }



    if (aucunProbleme){
        printf("Aucun probleme sur testNombrePosition en récursif.\n");
        printf("Aucun probleme sur testNombrePosition en itératif.\n");
        printf("Aucun probleme sur testNombrePosition en récursif terminale.\n");
        printf("Aucun probleme sur testNombrePosition en sous procédure terminale.\n");
    }

}



void TestVireDernierRec(){
    Liste L ;
    Liste L1;
    initVide(&L1);
    L1 = FoncVireDernierRec(L1);
    if (!estVide(L1)){
        printf("Erreur vireDernier pour la liste vide\n");
    }else{
        printf("Aucune erreur vireDernier pour la liste vide\n");
    }

    empile(1, &L1);
     L1 = FoncVireDernierRec(L1);
    if (!estVide(L1)){
        printf("Erreur vireDernier pour une liste à un élément.\n");
    }else{
        printf("Aucune erreur vireDernier pour la liste à un élément\n");
    }


    empile(29, &L1); empile(4, &L1); empile(8, &L1); empile(5, &L1);  empile(3, &L1); 
    
    Liste L2 = FoncVireDernierRec(L1);
    printf("Version récursive : Doit afficher 3 5 8 4 : ");
    affiche_rec(L2);
}

void TestVireDernierIter(){
    Liste L ;
    Liste L1;
    initVide(&L1);
    L1 = FoncVireDernierIter(L1);
    if (!estVide(L1)){
        printf("Erreur vireDernierinter pour la liste vide\n");
    }else{
        printf("Aucune erreur vireDernieriter pour la liste vide\n");
    }
    
    empile(1, &L1);
     L1 = FoncVireDernierIter(L1);
    if (!estVide(L1)){
        printf("Erreur vireDernieriter pour une liste à un élément.\n");
    }else{
        printf("Aucune erreur vireDernieriter pour la liste à un élément\n");
    }

    
    empile(29, &L1); empile(4, &L1); empile(8, &L1); empile(5, &L1);  empile(3, &L1); 
    
   Liste L2 = FoncVireDernierIter(L1);
    printf("Version itérative : Doit afficher 3 5 8 4 : ");
   affiche_rec(L2);
}

void insere(Liste *T1, int x){
    //insère un élement x juste après le premier élément de la liste
    if (estVide(*T1) ){
        empile(x, T1);
    }else{
        Liste newBloc = (Liste) malloc(sizeof(Bloc));
        CompteMallocListe++;
        newBloc->nombre = x;
        newBloc->suivant = (*T1)->suivant;
        (*T1)->suivant = newBloc;
        

    }
}




void AjouteDevantPremierZero(Liste *L, int x){
    if (estVide(*L)){
        insere(L, x);
    }else{
        Liste tmp = *L;
        if (estVide(suite(tmp))){
            insere(L, x);
        }else{ 
            while( (!estVide(suite(suite(tmp)))) && (premier(suite(tmp)) !=0)){
                tmp = tmp->suivant;
            }
            if (estVide(suite(suite(tmp)))){
                empile(x, &tmp->suivant->suivant);

            }if (premier(suite(tmp)) == 0){
                insere(&tmp, x);
            }

        }

    }
}

void TestAjoutDevantPremierZero(){
    Liste liste;
    initVide(&liste);
    AjouteDevantPremierZero(&liste, 4);
    printf("Test TestAjoutDevantPremierZero pour liste vide, doit afficher 4 : ");
    affiche_rec(liste);
    printf("\n");
    printf("Test TestAjoutDevantPremierZero pour liste 1 élément, doit afficher 4 3 : ");
    AjouteDevantPremierZero(&liste, 3);
    affiche_rec(liste);
    printf("\n");

    printf("Test TestAjoutDevantPremierZero pour liste sans 0, doit afficher 10 7 2 4 3 8 : ");
    empile(2, &liste); empile(7, &liste); empile(10, &liste);
    //10 7 2 4 3
    AjouteDevantPremierZero(&liste, 8);

    affiche_iter(liste);

    Liste l;
    initVide(&l);
    empile(2, &l); empile(8, &l); empile(0, &l); empile(7, &l);
    empile(5, &l); empile(4, &l);
    AjouteDevantPremierZero(&l, 10);
     printf("Test TestAjoutDevantPremierZero, doit afficher 4 5 7 10 0 8 2 : ");
    affiche_iter(l);

    Liste l2;
    initVide(&l2);
    empile(1, &l2); empile(0, &l2); empile(8, &l2); empile(0, &l2); empile(5, &l2); empile(0, &l2); empile(4, &l2);
    AjouteDevantPremierZero(&l2, 7);
    printf("Test TestAjoutDevantPremierZero, doit afficher 4 7 0 5 0 8 0 1 : ");
    affiche_iter(l2);
    }







Liste AuxDernierZeroRec(Liste L, Liste acc){
    //Renvoie le pointeur du bloc contenant le dernier zéro0
    if (estVide(suite(L))){
        if (acc == NULL || (premier(L) == 0)){
            return L;
        }else{
            return acc;
        }
    }else{
        if (premier(suite(L)) == 0){
            return AuxDernierZeroRec(suite(L), L);
        }else{
            return AuxDernierZeroRec(suite(L), acc);
        }
    }
}

void AjouteDevantDernierZeroRec(Liste *L, int x){
    if (estVide(*L) || estVide(suite(*L))){
        insere(L, x);

    }else{
        
        Liste ptr = AuxDernierZeroRec(*L, NULL);
        insere(&ptr, x);
        }

}


void SousADZRT(Liste *L, int x, Liste *acc){
    //cas d'arret
    if (estVide(suite(*L))){
        if (acc == NULL){ //si il n y a aucun zero
            insere(L, x);
        }else{
            insere(acc, x);
        }
    }else{
        if (premier(suite(*L)) == 0){
            SousADZRT(&(*L)->suivant, x, L);
        }else{
            SousADZRT(&(*L)->suivant, x, acc);
        }
    }
}


void AjouteDevantDernierZeroRecTerm(Liste *L, int x){
    if (estVide(*L) || estVide(suite(*L))){
        insere(L, x);
    }else{
        SousADZRT(L, x, NULL);
    }
}


void AjouteDevantDernierZeroIter(Liste *L, int x){
    if (estVide(*L) || estVide(suite(*L))){
        insere(L, x);
    }else{
        Liste ptr = NULL;
        Liste parcours = *L;
        Liste s;
        while (!(estVide(suite(parcours)))){
            if (premier(suite(parcours)) == 0){
                ptr = parcours;
            }
            parcours = suite(parcours);
        }
        insere(&ptr, x);

    }
}



void TestAjouteDevantDernierZero(){
    //Test pour version récsursive simple

    
    Liste l;
    initVide(&l);

    AjouteDevantDernierZeroRec(&l, 1);
    printf("Test ajouteDevantDernierZero récursif pour liste vide, doit afficher 1 : ");
    affiche_iter(l);

    Liste l1;
    initVide(&l1);
    empile(4, &l1);
    AjouteDevantDernierZeroRec(&l1, 7);
    printf("Test ajouteDevantDernier zero recursif pour liste a un element , doit afficher 4 7 : ");
    affiche_iter(l1);

    empile(0, &l); empile(8, &l); empile(0, &l); empile(5, &l);
    empile(0, &l); empile(4, &l);
     
    AjouteDevantDernierZeroRec(&l, 7);
    printf("Test ajouteDevantDernierZero recursif pour liste normale, doit afficher 4 0 5 0 8 7 0 1 : ");
    affiche_iter(l);

    //Test pour version récursive terminale
    initVide(&l);

    AjouteDevantDernierZeroRecTerm(&l, 1);
    printf("Test ajouteDevantDernierZero récursif terminale pour liste vide, doit afficher 1 : ");
    affiche_iter(l);

    initVide(&l1);
    empile(4, &l1);
    AjouteDevantDernierZeroRecTerm(&l1, 7);
    printf("Test ajouteDevantDernier zero recursif terminale pour liste a un element, doit afficher 4 7 : ");
    affiche_iter(l1);

    empile(0, &l); empile(8, &l); empile(0, &l); empile(5, &l);
    empile(0, &l); empile(4, &l);
     
    AjouteDevantDernierZeroRecTerm(&l, 7);
    printf("Test ajouteDevantDernierZero recursif terminale pour liste normale, doit afficher 4 0 5 0 8 7 0 1 : ");
    affiche_iter(l);

    //Test pour version itérative
    initVide(&l);

    AjouteDevantDernierZeroIter(&l, 1);
    printf("Test ajouteDevantDernierZero itératif pour liste vide, doit afficher 1 : ");
    affiche_iter(l);

    initVide(&l1);
    empile(4, &l1);
    AjouteDevantDernierZeroIter(&l1, 7);
    printf("Test ajouteDevantDernier zero itérative pour liste a un element, doit afficher 4 7 : ");
    affiche_iter(l1);

    empile(0, &l); empile(8, &l); empile(0, &l); empile(5, &l);
    empile(0, &l); empile(4, &l);
     
    AjouteDevantDernierZeroIter(&l, 7);
    printf("Test ajouteDevantDernierZero itérative pour liste normale, doit afficher 4 0 5 0 8 7 0 1 : ");
    affiche_iter(l);
    

}

Liste *SouSTic1(Liste *L){ //Ajoute les 0 devant les termes non nuls 
    if (estVide(*L)){
        return NULL;
    }else{
        if (premier(*L) == 0){
            return L;
        }else{
            empile(0, L);
            return SouSTic1(&(*L)->suivant->suivant);
        }
    }

}

void SousTic2(Liste *L){
    if (estVide(*L)){
        return;
    }else{
        if (premier(*L) == 0){
            depile(L);
            SousTic2(L);
            }
        else{
            return;
        }
    }
}

void Tic(Liste *L) {
    if (estVide(*L)){
        return;
    }
    Liste *first = SouSTic1(L);
    SousTic2(first);
}

void TestTic(){
    Liste vide;
    initVide(&vide);
    Tic(&vide);
    printf("Test Tic pour liste vide doit renvoyer 1 pour liste vide : ");
    printf("%d\n", estVide(vide));
    
    Liste L;
    initVide(&L);
    empile(1, &L); empile(2, &L);empile(0, &L);empile(0, &L);
    empile(9, &L); empile(8, &L); empile(0, &L);empile(0, &L);empile(0, &L);
    empile(2, &L);  empile(7, &L); empile(3, &L);

    Tic(&L);
    printf("Test Tic doit afficher 0 3 0 7 0 2 8 9 0 0 2 1 : ");
    affiche_iter(L);



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

    VideListe(&l);
    testUnPlusDeuxEgalTrois();
    testCroissante();
    testNombreMemePosition();
    TestVireDernierRec();
    TestVireDernierIter();
    TestAjoutDevantPremierZero();
    TestAjouteDevantDernierZero();
    TestTic();

    printf("\n");
    return 0;
}




