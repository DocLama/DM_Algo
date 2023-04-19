#include <stdio.h>
#include <windows.h>


double e_facto() {
	int i = 1,fac = 1;
	double e = 1;
	while (1.0/fac >= 1e-6){ // J'ai fait des tests sans réel réflexion mais avec cette valeur on obtient déja la bonne valeur aprroché de e soit 2.71828
		e += 1.0 / fac;
		i++;
		fac *= i;
	}
	return e;
}

double e = 2.718279;


float power_v1(float x, int n){
	if (n==0)return 1;

	if (n>=1) return power_v1(x,n-1)*x;	

}



void pow_v3(float x, int n, float *r){
	if(n==0) return;

	*r *= x;
	pow_v3(x, n-1, r);
}

float power_v3(float x, int n){
	float r = 1;
	float *ptr = &r;
	pow_v3(x, n, ptr);
	return r;
}




float pow_v4(float x, int n, float r){ 
	if (n==0) return r;

	r=r*x;
	return pow_v4(x,n-1,r);
}

float power_v4(float x, int n){
	float r=1;
	r=pow_v4(x,n,r); 
	return r;
	
}



float power_v5(float x, int n){
	if (n==0) return 1;

	if (n%2==0)return power_v5(x,n/2)*power_v5(x,n/2);
	
	return power_v5(x,n/2)*power_v5(x,n/2)*x;
	
}



float power_v6(float x, int n){
	if (n==0) return 1;

	float y=power_v6(x, n/2);
	if (n%2==0)return y*y;
	return y*y*x;
}

float power_v7(float x, int n){
	if (n==0) return 1;

	if (n%2==0)return power_v7(x*x,n/2);
	return power_v7(x*x,n/2)*x;
}

float pow_8(float x, int n, float r){
	if (n==0) return r;

	if (n%2==0)return pow_8(x*x,n/2,r);
	return pow_8(x*x,n/2,r*x);
}

float power_v8(float x, int n){
	return pow_8(x,n,1);
}

void pow_v9(float x, int n, float *r){
	if (n==0)return;
	else{
		if (n%2!=0){
			*r=*r * x;
		}
		pow_v9(x*x,n/2,r);
	}
}

float power_v9(float x, int n){
	float r=1;
	float *point= &r;
	pow_v9(x,n,point);
	return r;
}

float power_v10(float x, int n){
	float r=1;
	while (n!=0){
		if (n%2!=0) r=r*x;
		n=n/2;
		x=x*x;
	}
	return r;
}

int acker_V1(int m, int n)
{
	if (m == 0)return n + 1;

	else if (n == 0) return acker_V1(m - 1, 1);

	return acker_V1(m - 1, acker_V1(m, n - 1));
}

int acker_V2(int m, int n) {
	while (m != 0) {
		if (n == 0) n = 1;
		else {
			n = acker_V2(m, n - 1);
		}
		m--;
	}
	return n + 1;
}

int acker_V3(int m , int n){
    int r=1;
    if (m == 0) return n+1;
    else{
        for(int i = 1 ; i<=n+1 ; i++){
            r = acker_V3(m -1, r);
        }
    }
    return r;
}




void tester_power(){
    int N=1000;

    printf("\n1 :%f\n", power_v1(1.0+1.0/N, N));
	printf("Ma fonction power_v2 a un décalage de virgule donc je l'ai enlevé ");
    printf("\n3 :%f\n", power_v3(1.0+1.0/N, N));
    printf("\n4 :%f\n", power_v4(1.0+1.0/N, N));
    printf("\n5 :%f\n", power_v5(1.0+1.0/N, N));
    printf("\n6 :%f\n", power_v6(1.0+1.0/N, N));
    printf("\n7 :%f\n", power_v7(1.0+1.0/N, N));
    printf("\n8 :%f\n", power_v8(1.0+1.0/N, N));
    printf("\n9 :%f\n", power_v9(1.0+1.0/N, N));
    printf("\n10 :%f\n", power_v10(1.0+1.0/N, N));

    printf("\nLa suite tend vers e");
    printf("\nil tourne pendant 20 secondes puis s'arrete sans rien donner ");

}

void tester_acker(){

    for (int i= 0 ; i<5 ; i++){
        printf("\nResultat de acker_V1 de %i e donne %i\n" ,i, acker_V1(i, 0));
        printf("Resultat de acker_V2  de %i  donne %i\n" ,i, acker_V2(i, 0));
        printf("Resultat de acker_V3  de %i  donne %i\n" ,i, acker_V3(i, 0));
        
    }
    printf(" Elle tourne sans donner de resultat sauf la v3 qui arrive à donner le résultat mais il faut mettre en commentaire l'appel des deux autres versions");
}


float suite_Iter(int n) {
	double res = 1.0;
	while (n != 0) {
		res = res + 2.0 / res;
		n--;
	}
	return res;
}

float suite_Rec(int n) {
	if (n == 0) { return 1;}
	else {
		double tmp = suite_Rec(n - 1);
		return tmp + 2.0 / tmp;
	}
}

float sous_fonction(int n) {
    if (n == 0) return 1;
    else {
        double tmp = sous_fonction(n - 1);
		return tmp + 2.0 / tmp;
    }

}

float suite_Fonction(int n) {
    return sous_fonction(n);
}

void sous_Procedure(int n, float *res){
    if (n!=0){
        *res = *res +2.0 / *res;
        sous_Procedure(n-1,res);
    }
}
    


int suite_Procedure(int n){
	float res=1;
	sous_Procedure(n, &res);
	return res;
}



void tester_suite(){
    int val;
    printf("\nChoisissez la valeur: \n");
    scanf("%d", &val);

    printf("\n Pour l'iteratif: %f",suite_Iter(val));
    printf("\n Pour la récursive: %f",suite_Rec(val));
    printf("\n Pour la récursive Fonction: %f",suite_Fonction(val));
    printf("\n Pour la récursive Procedure: %f",suite_Procedure(val));
}

int main() {
    printf("La valeur de e est %f",e_facto());
    printf("\n 1 = test de power \n 2= Test de Ackermann \n 3= Test de Suite");
    int choix;
    printf("\nEntrez votre choix: \n");
    scanf("%d", &choix);
    if (choix == 1) tester_power();
    if (choix == 2) tester_acker();
    if (choix == 3) tester_suite();

    return 0;
}
