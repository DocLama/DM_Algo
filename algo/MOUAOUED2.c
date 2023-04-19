
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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
/*       Mes Fonctions                           */
/*                                               */
/*************************************************/

bool ZEN123 (Liste l){
    return (( (premier(l) == 0)) || (NOT (estVide(suite(l))) && premier(suite(l))==0) || (NOT (estVide(suite(suite(l)))) && premier(suite(suite(l)))==0));
}



bool pluscourte(Liste l1, Liste l2){
    return (longueur_rec(l2) > (longueur_rec(l1)));
}



bool pluscourte2(Liste l1, Liste l2){
	if (l1!=NULL AND l2!=NULL) return pluscourte2(suite(l1), suite(l2));
    
	if (l1==NULL AND l2!=NULL)return TRUE;

	return FALSE;
}





int nZ_AvantN_Recursive(Liste l, int k){
    if (estVide(l) || k==0) return 0;  // On traite le double cas vide

    if (premier(l)==0) return 1+nZ_AvantN_Recursive(suite(l),k-1); // Cas où on a un 0 donc on ajoute 1 au "compteur" et renvoie directment un appel récursif de la fonction sans le premier élément

    return nZ_AvantN_Recursive(suite(l),k-1); // Cas où on a pas de 0 donc on renvoie directment un appel récursif de la fonction sans le premier élément
}

int nZ_AvantN_Iterative(Liste l, int k){
	int cpt=0;
	for(int i=0;i<k;i++){
		if (premier(l)==0) cpt+=1;
		l=suite(l);
		if (estVide(l) ) break;
	}
	return cpt;
}

int Sous_fonction(Liste l, int k , int acc){ //On utilise le même principe que la récursive basique mais en utilisant une fonction en plus
    if (estVide(l)||k==0) return acc;

    if (premier(l)!=0) return Sous_fonction(suite(l),k-1,acc);

    return Sous_fonction(suite(l),k-1,acc+1);
}

int nZ_AvantN_Sous_F(Liste l1, int k){ // On initialise au cas de base
	return Sous_fonction(l1,k,0);
}

void Sous_procedure(Liste l, int k, int *acc){
    if (NOT(estVide(l)) && k!=0){
        if (premier(l)!=0) Sous_procedure(suite(l),k-1,acc);

        else{
            *acc +=1;
            Sous_procedure(suite(l),k-1,acc);
        }
    }
}

int nZ_AvantN_Sous_P(Liste l, int k){
	int acc=0;
	Sous_procedure(l,k, &acc);
	return acc;
}


void aux_Retro(Liste l, int* k, int* acc){
    if (NOT(estVide(l))){
        aux_Retro(suite(l),k,acc);
        if (*k>0){
            *k-=1;
            if (premier(l)==0){
                *acc +=1;
            }
        }
    }
}

int nZ_Retro(Liste l, int k){
    int acc=0;
    aux_Retro(l,&k,&acc);
    return acc;
}

Liste Fbegaye_recursive(Liste l){ // Comme la fonction est de type de type List lorsqu'on fait un return ... on ajoute à une liste crée
	if (estVide(l)) return l; 

	if (premier(l)>0)return ajoute(premier(l),ajoute(premier(l),Fbegaye_recursive(suite(l))));

	return Fbegaye_recursive(suite(l));
}




/* J'étais bloqué sur cette question pendant 2 jours et quelqu'un m'a indiqué d'utiliser PointeurSuite 
    Toutefois je l'ai fait entièrement tout seul on m'a donné l'indication car je n'y avait pas pensé du tout 
    car je pensais qu'on y était interdit vu que je pensais que si on avait le droit elle serait déja fourni dans l'annexe
*/

Liste* PS(Liste* L){
	if (estVide(*L))return L;

	return &((*L) -> suivant);
}

Liste Fbegaye_iterative(Liste l){
	Liste Return;
	initVide(&Return);
	Liste* S = &Return;
	Liste L = l;
	while(!estVide(L)){
		if(premier(L)>0){
			empile(premier(L), S);
			empile(premier(L), &((*S))->suivant);
			L = suite(L);
			S = PS(&(*S)->suivant);

		}else{
			L = suite(L);
		}
	}
	return Return;
}



void sous_fbeg(Liste l, Liste* stock){
	if(estVide(l)) return;
	else{
		if(premier(l)>0){
			empile(premier(l), stock);
			empile(premier(l), &(*stock)->suivant);
			sous_fbeg(suite(l), PS(&(*stock)->suivant));
		}else{
			sous_fbeg(suite(l), stock);
		}
	}
}

Liste Fbegaye_Terminale(Liste l){
	Liste stock;
	initVide(&stock);
	sous_fbeg(l,&stock);
	return stock;
}




/*************************************************/
/*                                               */
/*       PERMUTATIONS                            */
/*                                               */
/*************************************************/

// Au final on refait les memes trucs qu'on nous a fourni dans l'annexe un peu modifiés


typedef struct BlocListe
{
    Liste liste;
    struct BlocListe *suivant;
} BlocListe;

typedef BlocListe *Listception;

void initVide2(Listception *L) {
     *L = NULL; }

bool estVide2(Listception l) {
     return l == NULL; }

Liste premier2(Listception l) {
     return l->liste; }

Listception ajoute2(Liste x, Listception l) {
  Listception tmp = (Listception)malloc(sizeof(BlocListe));
  tmp->liste = x;
  tmp->suivant = l;
  return tmp;
}

void empile2(Liste x, Listception *L) { 
    *L = ajoute2(x, *L); }

Listception suite2(Listception l) {
     return l->suivant; }


void affiche_iter2(Listception l) {
  while (NOT(estVide2(l))){
    affiche_rec(premier2(l));
    l = suite2(l);
  }    
}





// C'est que de la compréhension de pseudo-code qui est assez claire

Listception ATPTL(int n, Listception ll);
Listception concatene(Listception l1, Listception l2);
Listception ATP(int n, Liste l);
Listception AETTL(int x, Listception ll);

Listception permutation(int n) {
  if (n == 0) {
    Listception tmp2;
    Liste tmp;
    initVide2(&tmp2);
    initVide(&tmp);
    empile2(tmp, &tmp2);
    return tmp2;
  } else {
    return ATPTL(n, permutation(n - 1));
  }
}

Listception ATPTL(int n, Listception ll ) {
  if (estVide2(ll)) {
    Listception tmp2;
    initVide2(&tmp2);
    return tmp2;
  } else {
    return concatene(ATP(n, premier2(ll)), ATPTL(n, suite2(ll)));
  }
}

Listception concatene(Listception l1, Listception l2) {
    if (estVide2(l1)) return l2;
    return ajoute2(premier2(l1), concatene(suite2(l1), l2));
}

Listception ATP(int n, Liste l) {
    if (estVide(l)) {
        Listception tmp2;
        initVide2(&tmp2);

        Liste tmp;
        initVide(&tmp);
        empile(n, &tmp);
        empile2(tmp, &tmp2);
        return tmp2;
        } else {
            return ajoute2(ajoute(n, l), AETTL(premier(l), ATP(n, suite(l))));
  }
}

Listception AETTL(int x, Listception ll) {
    if (estVide2(ll)) {
        Listception tmp2;
        initVide2(&tmp2);
        return tmp2;
  } else {
        return ajoute2(ajoute(x, premier2(ll)), AETTL(x, suite2(ll)));
  }
}









/*************************************************/
/*                                               */
/*       Mes TESTERS                             */
/*                                               */
/*************************************************/

void tester_Zen(){
    Liste l1 ; // l.size = 5

        initVide (&l1) ;
        empile(4, &l1) ;
        empile(5, &l1) ;
        empile(0, &l1) ;
        empile(3, &l1) ;
    Liste l2 ; // l2.size = 5

		initVide (&l2) ;
		empile(3, &l2) ;
		empile(0, &l2) ;
    Liste l3 ; // l2.size = 5

		initVide (&l3) ;
		empile(0, &l3) ;
		empile(1, &l3) ;
    Liste l4 ; // l.size = 5

        initVide (&l4) ;
        empile(0, &l4) ;
        empile(5, &l4) ;
        empile(5, &l4) ;
        empile(3, &l4) ;
        empile(3, &l4) ;    
    
    printf("\nl1: ");
    affiche_rec(l1);
    if (ZEN123(l1)) printf("Si affiche alors l1 good\n");
    printf("\nl2: ");
    affiche_rec(l2);
    if (ZEN123(l2)) printf("Si affiche alors l2 good\n");
    printf("\nl3: ");
    affiche_rec(l3);
    if (ZEN123(l3)) printf("Si affiche alors l3 good\n");
    printf("\nl4: ");
    affiche_rec(l4);
    if (ZEN123(l4)) printf("Si affiche alors l4 good\n");
}

void tester_Short(){
    Liste l ; // l.size = 5

        initVide (&l) ;
        empile(4, &l) ;
        empile(5, &l) ;
        empile(0, &l) ;
        empile(3, &l) ;
        empile(2, &l) ;

	Liste l2 ; // l2.size = 5

		initVide (&l2) ;
		empile(3, &l2) ;
		empile(0, &l2) ;
        empile(1, &l2) ;
		empile(1, &l2) ;
		empile(0, &l2) ;
    Liste l3 ; // l3.size = 6

		initVide (&l3) ;
		empile(3, &l3) ;
		empile(0, &l3) ;
        empile(5, &l3) ;
		empile(0, &l3) ;
        empile(1, &l3) ;
	    empile(1, &l3) ;
    printf("\nl: ");
    affiche_rec(l);
    printf("\nl2: ");
    affiche_rec(l2);
    printf("\nl3: ");
    affiche_rec(l3);

    if (pluscourte(l,l2)) then printf("Si affiche : l < l2\n");
    if (pluscourte2(l,l2)) then printf("Si affiche2 : l < l2\n");
    if (pluscourte(l2,l)) then printf("Si affiche : l2 < l\n");
    if (pluscourte2(l2,l)) then printf("Si affiche2 : l2 < l\n");
    if (pluscourte(l,l3)) then printf("Si affiche : l < l3\n");
    if (pluscourte2(l,l3)) then printf("Si affiche2 : l < l3\n");
    if (pluscourte(l3,l)) then printf("Si affiche : l3 < l\n");
    if (pluscourte2(l3,l)) then printf("Si affiche2 : l3 < l\n");
	
}
/*
int test_assert ( int x )
{
   assert( x <  1 );    
   return x;
}*/


void tester_Avant(){
     
    Liste l ; // l.size = 5

        initVide (&l) ;
        empile(4, &l) ;
        empile(5, &l) ;
        empile(0, &l) ;
        empile(3, &l) ;
        empile(2, &l) ;
        empile(3, &l) ;
		empile(0, &l) ;
        empile(5, &l) ;
		empile(1, &l) ;
        printf("\nl: ");
        affiche_rec(l);

        int tested;
        printf("\nEntrez le k a tester: ");
        scanf("%d", &tested); 
        printf("\nIterative: Nombre de 0: %d\n",nZ_AvantN_Iterative(l,tested));
        printf("Recurive banal: Nombre de 0: %d\n",nZ_AvantN_Recursive(l,tested));
        printf("Sous fonction: Nombre de 0: %d\n",nZ_AvantN_Sous_F(l,tested));
        printf("Sous procedure: Nombre de 0: %d\n",nZ_AvantN_Sous_P(l,tested));
        //if (nb0k_vi(l,7)) then printf("Si");
    

}

void tester_Retro(){
     
    Liste l ; // l.size = 5

        initVide (&l) ;
        empile(3, &l) ;
        empile(2, &l) ;
        empile(3, &l) ;
		empile(0, &l) ;
        empile(5, &l) ;
		empile(0, &l) ;
        printf("\nl: ");
        affiche_rec(l);
    Liste l2 ; // l2.size = 5

		initVide (&l2) ;
		empile(5, &l2) ;
		empile(0, &l2) ;
        empile(0, &l2) ;
		empile(3, &l2) ;
        printf("\nl2: ");
        affiche_rec(l2);

        int tested;
        printf("\nEntrez le k a tester: ");
        scanf("%d", &tested); 
        printf("\nRetro: Nombre de 0 pour l: %d\n",nZ_Retro(l,tested));
        printf("Retro: Nombre de 0 pour l2: %d\n",nZ_Retro(l2,tested));
}



void tester_Begaye1(){
     
    Liste l ; // l.size = 5

        initVide (&l) ;
        empile(4, &l) ;
        empile(5, &l) ;
        empile(0, &l) ;
        empile(3, &l) ;
        empile(2, &l) ;
        empile(3, &l) ;
		empile(0, &l) ;
        empile(5, &l) ;
		empile(0, &l) ;
        printf("\nl: ");
        affiche_rec(l);
        printf("\nBegaye recurive: ");
        affiche_rec(Fbegaye_recursive(l));
        printf("\nBegaye iterative: ");
        affiche_rec(Fbegaye_iterative(l));
        printf("\nBegaye terminale: ");
        affiche_rec(Fbegaye_Terminale(l));

}

void tester_Proc(){

    Printf("Je l'avais reussi mais je ne sais pas pk mais je n'arrive plus pourtant je me rappelle que c'etait bete");

}


void tester_Permutations(){
    Liste l ; // l.size = 5

        initVide (&l) ;
        empile(4, &l) ;
        empile(5, &l) ;
        empile(0, &l) ;
        empile(3, &l) ;
        empile(2, &l) ;
        empile(3, &l) ;
		empile(0, &l) ;
        empile(5, &l) ;
		empile(0, &l) ;
        printf("\nl: ");
        affiche_rec(l);

        Listception permutationTest;
        permutationTest = permutation(5);
        affiche_iter2(permutationTest);

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

int main(int argc, char** argv)
{
    printf(" Voici mon espace de test:\n \n    -1= Tests de ZeroEnPositionUnOuDeuxOuTrois \n    -2= Tests de PlusCourte(il ya 2 versions)\n    -3= Tests de NombreDe0AvantPositionK \n    -4= Tests de NombreDe0ApresRetroPositionK \n    -5= Tests de FctBegaye \n    -6= Tests de ProcBegaye \n    -7= Test de Permutation\n\n");
    int choix;
    printf("Entrez votre choix: \n");
    scanf("%d", &choix);
    if (choix == 1) tester_Zen();
    if (choix ==2 ) tester_Short();
    if (choix ==3 ) tester_Avant();
    if (choix ==4 ) tester_Retro();
    if (choix ==5 ) tester_Begaye1();
    if (choix ==6 ) tester_Proc();
    if (choix ==7 ) tester_Permutations();

    return 0;
}




