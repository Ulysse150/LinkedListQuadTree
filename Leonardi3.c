#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LENGTH 1000

typedef enum { FALSE, TRUE} bool;

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then

typedef struct bloc_image{
    bool quatre;
    struct bloc_image *hg, *hd, *bg, *bd;

}bloc_image;

typedef bloc_image *image; 

image Blanc(){
    image tmp = (image) malloc(sizeof(bloc_image)) ;
    tmp->quatre = FALSE;
    tmp->hg = NULL;
    tmp->hd = NULL;
    tmp->bg = NULL;
    tmp->bd = NULL;
    return tmp;
}

image Noir(){
    return NULL;
}

image Compose(image i1, image i2, image i3, image i4){
    image tmp = (image) malloc(sizeof(bloc_image)) ;
    tmp->quatre = TRUE;
    tmp->hg = i1;
    tmp->hd = i2;
    tmp->bg = i3;
    tmp->bd = i4;
    return tmp;
}

bool EstNoire(image Img){
    if (Img == NULL){
        return TRUE;
    }else{
        if (Img->quatre == FALSE){
            return FALSE;
        }else{
            return (EstNoire(Img->hg) AND EstNoire(Img->hd)) AND (EstNoire(Img->bg) AND EstNoire(Img->bd));
        }
    }
}

bool EstBlanche(image Img){
    if (Img == NULL){
        return FALSE;
    }else{
        if (!(Img->quatre)){
            return TRUE;
        }else{
            return (EstBlanche(Img->hg) AND EstBlanche(Img->hd)) AND (EstBlanche(Img->bg) AND EstBlanche(Img->bd));
        }
    }
}


image SousLecture(char* input, int* indice){
    char c = input[(*indice)];
    (*indice) = (*indice) -1;
    switch (c)
    {
    case '*': return Compose(SousLecture(input, indice),SousLecture(input, indice),SousLecture(input, indice),SousLecture(input, indice)   );break;
    case 'X': return Noir(); break;
    case 'o': return Blanc();break;
    default : printf("Caractere  interdit!  %c ",c);return NULL; break;
 }

    
}

image Construire(char* input, int taille){
    int Indice = taille - 1;
    return SousLecture(input, &Indice);
}

image Lecture() {
    char input[MAX_LENGTH];
    int i = 0;
    printf("Entrez une chaine de caractères : ");
    
    while (i < MAX_LENGTH - 1) {
        char c = getchar();
        
        if (c == '\n') {
            break;
        }
        
        input[i] = c;
        i++;
    }
    i--;
    return SousLecture(input, &i);
}



void SousaffichePronfondeur(image I, int profondeur){
    if (I == NULL){
        printf("X%d ", profondeur);
    }else{
        if (I->quatre == FALSE){
            printf("o%d ", profondeur);
        }else{
            SousaffichePronfondeur(I->hg, profondeur + 1);
            SousaffichePronfondeur(I->hd, profondeur + 1);
            SousaffichePronfondeur(I->bg, profondeur + 1);
            SousaffichePronfondeur(I->bd, profondeur + 1);
            printf("*");
        }
    }
    
}

void afficheProfondeur(image I){
    SousaffichePronfondeur(I, 0);
    printf("\n");
}


void affichage(image I){
    if (I == NULL){
        printf("X");
    }else{
        if (I->quatre == TRUE){
            affichage(I->hg);
            affichage(I->hd);
            affichage(I->bg);
            affichage(I->bd);
            printf("*");
        }else{
            printf("o");
        }
    } // si l'image est totalement noire
}
image SousTriangle(int p){
    if (p == 1){
        return Compose(Blanc(),Blanc(),Blanc(),Noir());
    }else{
        image I = SousTriangle(p-1);
        return Compose(Blanc(),I,I,Noir());
    }
}

image TriangleBD(int p){
    if (p == 0){
        return Blanc();
    }else{
        return SousTriangle(p);
    }

}




double SousAire(image I, double multiplicateur){
    
    if (I == NULL){
        return multiplicateur;
        
    }else{
        if (I->quatre){
            return SousAire(I->hg,(1.0*multiplicateur)*0.25 ) + 
                    SousAire(I->hd,(1.0*multiplicateur)*0.25 ) +
                    SousAire(I->bg,(1.0*multiplicateur)*0.25 ) +
                    SousAire(I->bd,(1.0*multiplicateur)*0.25 );
        }else{
            return 0.0;
        }
    }

}

double Aire(image I){
    return SousAire(I, 1.0);
}


bool MemeDessin(image image1, image image2){
    if (image1 == NULL){
        return image2 == NULL;
    }else{
        if (image1->quatre){
            if (image2->quatre){
                return (MemeDessin(image1->hg, image2->hg) AND MemeDessin(image1->hd, image2->hd)) AND
                    (MemeDessin(image1->bg,image2->bg) AND MemeDessin(image1->bd, image2->bd))
                ;
            }else{
                return FALSE;
            }
        }else{
            return (image2->quatre);
        }
    }
}

void SArrondit(image *I, int p){
    if (p == 0){
        double A = Aire(*I);
        if (A > 0.5){
            *I = NULL;
        }else{
            (*I)->quatre = FALSE;
            (*I)->bg = NULL;
            (*I)->bd = NULL;
            (*I)->hg = NULL;
            (*I)->hd = NULL;
        }
    }else{
        if (*I == NULL){
            return;
        }else{
            if ((*I)->quatre){
                SArrondit(&(*I)->hg, p - 1);
                SArrondit(&(*I)->hd, p - 1);
                SArrondit(&(*I)->bg, p - 1);
                SArrondit(&(*I)->bd, p - 1);
            }
        }
    }
}

void Arrondit(image I, int p){
    SArrondit(&I, p);
}

int SousDamier(image I, bool regarder){
    if (regarder){

        if ((I == NULL) || (!(I->quatre))){
        return 0;
    }        //on va regarder les 4 cases pour voir si on a bien Blanc, noir,noir et Blanc
        //et egalement noter les cases que l'on devra parcourir
        bool estDamier = TRUE; // on considère que c'est un damier jusqu'à preuve du contraire
        bool Hg;  image HG = I->hg;
        bool Hd;  image HD = I->hd;
        bool Bg;  image BG = I->bg;
        bool Bd;  image BD = I->bd;
        //les booleens c est pour dire si on parcourera le sous arbre correspondant
        
        if (HG == NULL){//si le haut gauche est noir c'est pas un damier
            estDamier = FALSE;
            Hg = FALSE; //on a plus besoin de parcourir à gauche
        }else{
            if (HG->quatre){ // si il a des fils
                estDamier = FALSE;  //ce n'est pas un damier
                Hg =  TRUE; // on devra donc le parcourir
            }
        }

        if (HD == NULL){//si haut droite est noire, pas besoin de le parcourir
            Hd  = FALSE;
        }else{//sinon
            estDamier = FALSE; // cette commande peur etre redondante si on sait deja que c'est pas un damier
            Hd = HD->quatre; // on parcoure
        }

        if (BG == NULL){ // si bas gauche est noire
            BG = FALSE; // pas besoin de le reparcourir
        }else{
            estDamier = FALSE;
            Bg =BG->quatre;

        }

         if (BD == NULL){//si le haut gauche est noir c'est pas un damier
            estDamier = FALSE;
            Bd = FALSE; //on a plus besoin de parcourir à gauche
        }else{
            if (BD->quatre){ // si il a des fils
                estDamier = FALSE;  //ce n'est pas un damier
                Bd =  TRUE; // on devra donc le parcourir
            }
        }
        if (estDamier){ //si le sous arbre est un damier, on renvoie 1, on n'aura rien à parcourir.
            return 1;
        }
        int A1 = SousDamier(HG, Hg);
        int A2 = SousDamier(HD, Hd);
        int A3 = SousDamier(BG, Bg);
        int A4 = SousDamier(BD, Bd);

        //si on a le meme nombre de damiers dans chaque sous arbre superieur à 0, et, alors cette arbre est un damier
        int abreSupplémentaire = ((A1 > 0) && (A1 == A2)) && ((A2 == A3) && (A3 == A4));

        //on renvoie le nombre de sous arbres,  
        return A1 + A2 + A3 + A4 + abreSupplémentaire;

    }else{
        return 0;
    }
}



int CompteDamiers(image I){
    if ((I == NULL) || (!(I->quatre))){
        return 0;
    }
    return SousDamier(I, TRUE);
}


void Tests(){





    image B = Blanc();
    printf("Test Blanc() , doit afficher o0 ");
    afficheProfondeur(B);
    image N = Noir();
    printf("Test Noir(), doit afficher x0 ");
    afficheProfondeur(N);
    printf("Test Compose(Blanc(),Blanc(),Noir(),Noir()) doit afficher o1 o1 x1 x1 : ");
    image I = Compose(Blanc(),Blanc(),Noir(),Noir());
     afficheProfondeur(I);
    printf("Test Lecture : vous devez entrer votre chaine de caractères et avoir la meme chaine de caracteres affiches en profondeur :\n ");
    //image I1 = Lecture();
    //afficheProfondeur(I1);




    int compte = 20;
    image I2 = SousLecture("ooooo*oooo*o*oooooo**", &compte);
    printf("Teste pour  EstBlanche(ooooo*oooo*o*oooooo**) doit afficher 1 : ");
    printf("%d\n",EstBlanche(I2));

    printf("Teste pour  EstNoire(ooooo*oooo*o*oooooo**) doit afficher 0 : ");
    printf("%d\n",EstNoire(I2));

     printf("Test estBlanche() pour Blanche(), doit afficher 1 : ");
     printf("%d\n", EstBlanche(Blanc()));

    int com = 36;
    printf("Test Arrondit pour XXXooX*oXXo*oooX**oXo*oXXoooXXX**oX** ,2, doit afficher XXoXo*oXooX** : \n  ");
    image I3 = SousLecture("XXXooX*oXXo*oooX**oXo*oXXoooXXX**oX**", &com);
    Arrondit(I3, 2);
    

    affichage(I3);
    printf("\n");}




int main(){
    Tests();
    //afficheProfondeur(i1);
    //image I =Lecture();
    //afficheProfondeur(I);

     //I2 = Lecture();
    //afficheProfondeur(I2);




    printf("Fini\n");



    //printf("Fini");
    //afficheProfondeur(I2);
    /* char *st = getUserInput();
    printf("You entered: %s\n", st); */
    return 1;
}