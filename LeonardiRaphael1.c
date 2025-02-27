

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

typedef enum { false, true} bool;

/*************************************************/
/*                                               */
/*            factorielle                        */
/*                                               */
/*************************************************/

long fact (int n) 
{ if (n==0) return 1 ;
  else return n * fact(n-1) ; 
}

// itou avec un arg out => passage par adresse

void bisfact(int n, long * r) 
{ if (n==0) 
         *r=1.0 ;
  else { bisfact(n-1,r) ;
         *r = *r *n ;
       }
}

long fact2 (int n)
{ long r ;
  bisfact(n,&r) ;
  return r ;
}

/*************************************************/
/*                                               */
/*            Calcul de e                        */
/*                                               */
/*************************************************/

  // d'après google,
  // e = 2,7182818284 5904523536 0287471352 6624977572 4709369995 
  //       9574966967 6277240766 3035354759 4571382178 5251664274

     // Il est proposé de faire 3 versions pour observer des phénomènes de précision.
     // C'est le même code, seul le type change.

/*************************************************/

float Efloat () { 
    //On commence à calculer à partir de n = 1
    float N = 50; // On prend un N assez grand, ici 1000
    float n = 1;
    float u = 1;
    float f = 1;
    //J'ai utilisé des floats au lieu de int pour
    // ne pas avoir de soucis de calculs
    // comme on va calculer avec des floats de plus
    // en plus petit

    while (n < N){
        u = u + (1/f);
        n = n + 1;
        f = f * n;
    }


    
    return u ; }

/*************************************************/

double Edouble () { 

    double N = 50; // On prend un N assez grand, ici 1000
    double n = 1;
    double u = 1;
    double f = 1;
    while (n < N){
        u = u + (1/f);
        n = n + 1;
        f = f * n;
    }
    return u;
 }
  
/*************************************************/

long double Elongdouble () { 

    long double N = 50; // On prend un N assez grand, ici 50
    long double n = 1;
    long double u = 1;
    long double f = 1;
    while (n < N){
        u = u + (1/f);
        n = n + 1;
        f = f * n;
    }
    return u;}

void afficheYfloat (int n) {
    float e = Efloat();
    float y = e - -1;
    int N = 30;
    for (int n = 1; n <= N; n++){
        y = (n*y) - 1;
        printf("y%d = %f\n",n,y);
    }


}

/*************************************************/

void afficheYdouble (int n) {
    double e = Edouble();
    double y = e - -1;
    int N = 30;
    for (int n = 1; n <= N; n++){
        y = (n*y) - 1;
        printf("y%d = %f\n",n,y);
    }
    };

/*************************************************/

void afficheYlongdouble (int n) {

    long double e = Edouble();
    long double y = e - -1;
    int N = 30;
    for (long int n = 1; n <= N; n++){
        y = (n*y) - 1;
        printf("y%ld = %Lf\n",n,y);
    }
    
}



/*************************************************/
/*                                               */
/*            Puissance                          */
/*                                               */
/*************************************************/


double power1 (double x, long n) { 


  if (n == 0){
      return 1;
  }else{
     double terme;
     if (n > 0){
        terme = x;
     }else{
        terme = 1 /x;
     }
     double r = 1;
     for (int i = 1; i <= n; i++){
        r = r *terme;
     }
  return r;
  }
 }

/*************************************************/

double power2a (double x, long n) { 
    double r = 1;
    double terme;
    if (n > 0){
        terme = x;
     }else{
        terme = 1 /x;
     }
    for (int i = 1; i <=n; i++){
        r = r * terme;
    }
    return r;

}

/*************************************************/

double power2b (double x, long n) { 
    double r = 1;
    while (n > 0){
        r = r *x;
        n--;
    }
    return r;
 }

/*************************************************/


double power3 (double x, long n) { 
    double pow(double x , long n, double *r){
        if (n != 0){
          *r *= x;
          pow(x, n-1, r);
        }    
    };
    
    double r = 1;
    pow(x, n, &r);
    return r;
}

/*************************************************/

double power4 (double x, long n) { 
    double pow(double x, long n, double r){
        if (n == 0){
            return r;}
        else{
           return pow(x, n-1, r*x);
        }

    };

    return pow(x, n, 1);
}

/*************************************************/

     //   Observation (1+1/10^k)^(10^k) : rame : 8 en 1/2s, 9 en qqs s, 10 en 1m

double power5 (double x, long n)
{
    if (n == 0)
         return 1 ;
    else if (n % 2 == 0)
              return (power5(x,n/2)*power5(x,n/2)   ) ;
         else return (power5(x,n/2)*power5(x,n/2) *x) ;   
}

/*************************************************/

double power6 (double x, long n) { 
    
    if (n == 0){return 1;}
    else{   
        double y =  power6(x, n/2);
        if (n % 2 == 0){
            return y * y;
        }else{
            return y*y*x;
        }

    }

}

/*************************************************/

double power7 (double x, long n) { 
    if (n == 0){
        return 1;
    }else{
        if (n %2 == 0){
            return power7(x*x, n/2);}
        else{
            return power7(x*x, n/2)*x;
        }
    }
}

/*************************************************/

double power8 (double x, long n) { 
    double pow(double x, long n, double r){
        if (n == 0){
            return r;
        }else{
            if (n % 2 == 0){
                return pow(x*x, n/2, r);
            }else{
                return pow(x*x, n/2, r*x);
            }
        }
    };
    return pow(x, n, 1);

}

/*************************************************/

double power9 (double x, long n) {
    double r = 1;
    double pow(double x, long n, double *r){
        if (n != 0){
            if (n % 2 == 1){
                *r = *r * x;
                
            }pow(x*x, n/2, r);
        }
    };
    pow(x, n, &r);
    return r;
 }

/*************************************************/

     //   Observation (1+1/10^k)^(10^k) : calcul immédiat

double power10 (double x, long n)
{
    double r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}

/*************************************************/
    // memes versions que la 10 mais avec des long double, puis des floats
    // but du jeu : observer des variations de precision

   // observation :
   //   imprécision à partir de k~5 (float), k~12 (double), k~14 (long double)
   //   rend 1 à partir de k=8 (float), k=16 (double)
   //   rend 1 non observé sur les long double, maxint atteint avant

long double power11 (long double x, long n)
{
    long double r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}

/*************************************************/
double power (double x, long n, int i)
{ switch (i)  
   {
   case 1 : return power1(x,n) ; break ;
   case 2 : return power2a(x,n) ; break ;  // 2 pour 2a
   case 0 : return power2b(x,n) ; break ; // 0 pour 2b
   case 3 : return power3(x,n) ; break ;
   case 4 : return power4(x,n) ; break ;
   case 5 : return power5(x,n) ; break ;
   case 6 : return power6(x,n) ; break ;
   case 7 : return power7(x,n) ; break ;
   case 8 : return power8(x,n) ; break ;
   case 9 : return power9(x,n) ; break ;
  case 10 : return power10(x,n) ; break ;
  case 11 : return power11(x, n); break;
     default : return 0 ; 
   }
}

   // remarque : les break sont ici inutiles car les returns font déjà des break

/*************************************************/



float power12 (float x, long n)
{
    float r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}
/*
 (1 + 1/N)^N semble tendre vers la constante e
*/

/*************************************************/
/*                                               */
/*             Ackermann                         */
/*                                               */
/*************************************************/

int Ackermman1(int m, int n){
    if (m == 0){
        return n + 1;
    }else{
        if (m > 0){
            if (n == 0){
                return Ackermman1(m-1, 1);
            }else{
                return Ackermman1(m-1, Ackermman1(m, n-1));
            }
        }
    }

}


int Ackermann2(int m, int n) {  
    if (m == 0){
        return n+1; 
    }else{
        int r = 1;
        for (int i = 1; i <= n+1; i++){
            r = Ackermann2(m-1, r);
        }
        return r;
    }
}

/*************************************************/


int Ackermann3 (int m, int n) { 
    return 0;

 }

/*************************************************/

int Ackermann4 (int m) { return 0 ; }

/*************************************************/

int Ackermann5 (int m) { return 0 ; }

/*************************************************/
  
int Ackermann (int m, int i)
{ switch (i)  
   {
   case 1 : return 0; // break ;
   case 2 : return 0 ; // break ;
   case 3 : return 0 ; // break ;
   case 4 : return 0 ; // break ;
   case 5 : return 0 ; // break ;
   default : return 0 ; 
   }
}

/**Suite d'entiers X_n */
int ln2(long n){
  if (n == 1){
      return 0;
  }else{
      return 1 + ln2(n/2);
  }
}

long int X1(int n){
    long int x = 2;
    for (int i = 1; i < n+1; i++){
        x = x + ln2(x);
    }return x;
}


long int X2(int n){
    if (n == 0){
        return 2;
    }else{
        long int previous = X2(n-1);
        return ln2(previous) + previous;
    }

}


long int X3(int n){
    
    long int next(int i, long int acc, int N_max){
        if (i == N_max){
            return acc;
        }else{
            return next(i+1, acc+ln2(acc), N_max);
        }
    };
    return next(0, 2, n);

}


long int X4(int n){
    long int x1 = 2;
    void next2(int indice, long int *acc, int N_max){
        
        if (indice < N_max){
            *acc = *acc+ln2(*acc);
            next2(indice+1,acc , N_max);}
        
    };
    next2(0, &x1, n);
    return x1;
}


long int X(int n, int version){
    //Renvoie la version du n ième élément de la suite X_n
    switch(version){
        case 1 : return X1(n);
        case 2 : return X2(n);
        case 3 : return X3(n);
        case 4 : return X4(n);
    }
}


/*************************************************/
/*                                               */
/*               main                            */
/*                                               */
/*************************************************/


int main(int argc, char** argv)
{

       double x ;
       long double y ;
       float z ;
  
       long nx ;
       
       int i,j ; 
       
/******************************************************************************/
 
    // mettre "if true" vs "if false" selon que vous voulez les tests ou non
  
/****************  petit test sur le fonctionnement du switch  ************/

if (true) {

 switch (2)  
   {
   case 1 : printf("toc\n") ;  break ;
   case 2 : printf("pata") ; 
   case 3 : printf("pouf\n") ;  break ;
   case 4 : printf("youpla") ; 
   default : printf("boum\n") ; 
   }


 switch (4)  
   {
   case 1 : printf("toc\n") ;  break ;
   case 2 : printf("pata") ; 
   case 3 : printf("pouf\n") ;  break ;
   case 4 : printf("youpla") ; 
   default : printf("boum\n") ; 
   }

   printf("\n") ; 

}
      
      
/************************  taille des nombres  *************************/
      
if (true) {     
       
       printf("ce programme suppose que les long font 8 octets\n") ;
       printf("S'ils n'en font que 4, il faudra utiliser long long\n") ;

       printf("short : %d octets\n", (int) sizeof(short));
       printf("int : %d octets\n", (int) sizeof(int));
       printf("long : %d octets\n", (int) sizeof(long));
       printf("long long : %d octets\n", (int) sizeof(long long));
       printf("float : %d octets\n", (int) sizeof(float));
       printf("double : %d octets\n", (int) sizeof(double));
       printf("long double : %d octets\n", (int) sizeof(long double));
       printf("\n") ;
 
       x = 1.0 ;
       int cptx = 0 ;
       while ( (1.0 + x) - 1.0 != 0 )
          { x = x/10 ; cptx ++ ; }
       printf("1+1/10^c devient 1 a partir de c=%d pour les double\n", cptx) ; 
       printf("et 1+1/10^%d vaut en fait 1+%lf\n", cptx-1, (1.0 + 10*x) - 1.0) ;
        
       printf("ce programme suppose que les doubles font au moins 8 octets\n") ;
       printf("et que ((double) 1+1/10^-15) n'est pas 1 \n") ;       
       printf("Si ce n'est pas le cas, utiliser des long double \n") ;
       
       printf("\n") ;      
}

/************************  factorielle  *************************/

if (true) {

     printf("%ld \n",fact(5)) ;
     printf("%ld \n",fact2(5)) ;
     printf("\n") ;
}


/******************    Autour de e      *******************************/

  // d'après google,
  // e = 2,7182818284 5904523536 0287471352 6624977572 4709369995 
  //       9574966967 6277240766 3035354759 4571382178 5251664274

if (true) {  
       

        printf(" e1 = %.20f \n", Efloat()) ;
        printf(" e3 = %.30lf \n", Edouble()) ; 
        printf(" e3 = %.40Lf \n", Elongdouble()) ; 
        
}

if (true) {  
            afficheYfloat(30) ;
            afficheYdouble(30) ;
            afficheYlongdouble(30) ;
}
        
/******************    power     *******************************/

if (true) {  

        //   test simplet, vérifie le B.A. BA, test de 2^10 pour toutes les versions
        
        for(i=0 ; i<=10 ; i++)
        printf("Power %d dit que power(2,10) vaut %.0lf \n", i, power(2,10,i) ) ;
        
        printf("\n") ;
      
}

        
if (false) {  

        i=5 ;  // numéro de la version que l'on teste

        // test de la résistance de power version i, calcul de (1+1/N)^N
        // pour des N puissances de 10 de plus en plus grosses
     
        x = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=15 ; j++)
        {
        printf("power %d ((1+10^-%2d)^(10^%2d)) rend %.12lf\n", i, j, j, power(1+x,nx,i)) ;
        x = x/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;
       
}
     
if (true) {

        // tests sur la précision que l'on obtient suivant que
        // l'on utilise float, double, long double

        printf("VERSION 12 avec float \n") ;
        z = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12f\n", j, j, power12(1+z,nx)) ;
        z = z/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;


        printf("VERSION 10 avec double \n") ;
        x = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12lf\n", j, j, power10(1+x,nx)) ;
        x = x/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;


        printf("VERSION 11 avec long double \n") ;
        y = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12LF\n", j, j, power11(1+y,nx)) ;
        y = y/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;
        //Seules ces versions semblent pouvoir calculer les puissances efficacement,
        //Les autres prennent beaucoup trop de temps à calculer.


}

/******************    Ackermann    *******************************/
                
if (false) { 
 
        for(i=1 ; i<=5 ; i++)  // numéro de version
        
        for(j=0 ; j<=5 ; j++)  // test de A(j,0) pour j de 0 à 5
        
        printf("Ack%d(%d) = %d \n", i, j, Ackermann(j,i)) ;
}

/***********************************************************************/
/*Test de ln2(x)*/
if (true){
    for (long x = 1; x < 256; x = 2 *x){
        printf("ln2(%ld) = %d\n",x, ln2(x) );
    }}

//Test de la suite X
    for (int i = 1; i <= 4; i++){
        printf("Valeur de X version %d pour n = 100 : %ld\n", i, X(100, i));
    }




    return 0;
}





