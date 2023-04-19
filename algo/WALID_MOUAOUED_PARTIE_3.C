#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h> 

typedef struct bloc_image
{
    bool toutnoir;
    struct bloc_image *fils[4];
} bloc_image;

typedef bloc_image *image;

image Construit_Blanc()
{
    return NULL;
}

image Construit_Noir()
{
    image noir = (image)malloc(sizeof(bloc_image));
    noir->toutnoir = true;
    noir->fils[0] = noir->fils[1] = noir->fils[2] = noir->fils[3] = NULL;
    return noir;
}

image Construit_Composee(image i0, image i1, image i2, image i3)
{
    image composee = (image)malloc(sizeof(bloc_image));
    composee->toutnoir = false;
    composee->fils[0] = i0;
    composee->fils[1] = i1;
    composee->fils[2] = i2;
    composee->fils[3] = i3;
    return composee;
}

void AfficheNormal(image img)
{
    if (img == NULL)
        printf("B");
    else if (img->toutnoir)
        printf("N");
    else
    {
        printf("(");
        AfficheNormal(img->fils[0]);
        AfficheNormal(img->fils[1]);
        AfficheNormal(img->fils[2]);
        AfficheNormal(img->fils[3]);
        printf(")");
    }
    
}

void AfficheProfondeur(image img, int p)
{
    if (img == NULL)
        printf("B%d", p);
    else if (img->toutnoir)
        printf("N%d", p);
    else
    {
        printf("( ");
        AfficheProfondeur(img->fils[0], p + 1);
        AfficheProfondeur(img->fils[1], p + 1);
        AfficheProfondeur(img->fils[2], p + 1);
        AfficheProfondeur(img->fils[3], p + 1);
        printf(" )%d", p);
    }
}

image lecture() {
  char c;
  scanf(" %c", &c);
  if (c == 'B') {
    return NULL;
  }
  else if (c == 'N') {
    return Construit_Noir();
  }
  else {
    image img = (image)malloc(sizeof(bloc_image));
    img->toutnoir = false;
    for (int i = 0; i < 4; i++) {
      img->fils[i] = lecture();
    }
    scanf(" %c", &c); 
    return img;
  }
}


bool EstNoire(image img)
{
	if ((img == NULL)) {
		return false;
	}else{
		return (img->toutnoir)
			||(EstNoire(img->fils[0])
				&& EstNoire(img->fils[1])
				&& EstNoire(img->fils[2])
				&& EstNoire(img->fils[3]));
	}
}

bool EstBlanche(image img) {
	if (img == NULL)
		return true;
	else if (img->toutnoir)
		return false;
	else{
		return (EstBlanche(img->fils[0]) 
				&& EstBlanche(img->fils[1]) 
				&& EstBlanche(img->fils[2]) 
				&& EstBlanche(img->fils[3])
				);
	}
}

image Diagonale(int p)
{
    if (p == 0)
        return Construit_Noir();
    else
    {
        image diag = Construit_Composee(Diagonale(p - 1), Construit_Blanc(), Construit_Blanc(), Diagonale(p - 1));
        return diag;
    }
}


image quartDeTour(image img){
	if((img == NULL) || (img->toutnoir)){
		return img;
	}else{
		return Construit_Composee(
				quartDeTour(img->fils[2]),
				quartDeTour(img->fils[0]),
				quartDeTour(img->fils[3]),
				quartDeTour(img->fils[1]));
	}
}

void negatif(image *img) {
	if (*img == NULL) {
		*img = Construit_Noir();
	}
	else if ((*img)->toutnoir) {
		free(*img);
		*img = Construit_Blanc();
	}
	else {
		for (int i = 0; i < 4; i++) {
			negatif(&((*img)->fils[i]));
		}
	}
}

image SimplifieProfP(image img, int p){
	if((img == NULL) || (img->toutnoir)){
		return img;
	}
	if(p==0){
		if(EstNoire(img->fils[0]) && EstNoire(img->fils[1]) && EstNoire(img->fils[2]) && EstNoire(img->fils[3])){
			img = Construit_Noir();
		}
		else if(EstBlanche(img->fils[0]) && EstBlanche(img->fils[1]) && EstBlanche(img->fils[2]) && EstBlanche(img->fils[3])){
			img = Construit_Blanc();
		}
		return img;
	}else{
			if((img->fils[0]!= NULL) && (img->fils[0]->toutnoir)){
				img->fils[0] = SimplifieProfP(img->fils[0], p-1);
		}else if((img->fils[1]!= NULL) && (img->fils[1]->toutnoir)){
				img->fils[1] = SimplifieProfP(img->fils[1], p-1);
        }else if((img->fils[2]!= NULL) && (img->fils[2]->toutnoir)){
				img->fils[2] = SimplifieProfP(img->fils[2], p-1);
        }else if((img->fils[3]!= NULL) && (img->fils[3]->toutnoir)){
				img->fils[3] = SimplifieProfP(img->fils[3], p-1);
        }
		return img;
	}
}



bool Incluse(image a, image b){
	if((a->toutnoir && !b->toutnoir) || (b== NULL)){
		return false;
	}else if((b)-> toutnoir || (a== NULL)){
		return true;
	}else{
		return Incluse(a->fils[0], b->fils[0])
			&& Incluse(a->fils[1], b->fils[1])
			&& Incluse(a->fils[2], b->fils[2])
			&& Incluse(a->fils[3], b->fils[3]);
	}
}


int hautMaxBlanc(image img, int haut) {
  if (img == NULL) {
    return haut;
  } else if (img->toutnoir) {
    return -1;
  } else {
    int hautMax = haut;
    for (int i = 0; i < 4; i++) {
      int hautFils = hautMaxBlanc(img->fils[i], haut + 1);
      if (hautFils > hautMax) hautMax = hautFils;
    }
    return hautMax;
  }
}



void BlanchitProfP(image *img, int p, int x, int y) {
  if (*img == NULL || (*img)->toutnoir || p == 0) {
    return;
  }
  int x1 = x / 2;
  int y1 = y / 2;
  if (x % 2 == 0 && y % 2 == 0) {
    BlanchitProfP(&((*img)->fils[0]), p - 1, x1, y1);
  } else if (x % 2 == 1 && y % 2 == 0) {
    BlanchitProfP(&((*img)->fils[1]), p - 1, x1, y1);
  } else if (x % 2 == 0 && y % 2 == 1) {
    BlanchitProfP(&((*img)->fils[2]), p - 1, x1, y1);
  } else {
    BlanchitProfP(&((*img)->fils[3]), p - 1, x1, y1);
  }
  bool all_white = true;
  for (int i = 0; i < 4; i++) {
    if ((*img)->fils[i] != NULL) {
      all_white = false;
      break;
    }
  }
  if (all_white) {
    free(*img);
    *img = NULL;
  }
}

/*
image Chute(image img) {
  if (img == NULL) {
    return NULL;
  } else if (img->toutnoir) {
    return Construit_Noir();
  } else {
    image i0 = Chute(img->fils[0]);
    image i1 = Chute(img->fils[1]);
    image i2 = Chute(img->fils[2]);
    image i3 = Chute(img->fils[3]);
    // On cherche la première sous-image blanche en partant du bas
    int i;
    for (i = 3; i >= 0; i--) {
      if (img->fils[i] == NULL) {
        break;
      }
    }
    // On décale les sous-images noires vers le bas
    for (int j = i-1; j >= 0; j--) {
      i3 = Construit_Composee(img->fils[j], NULL, NULL, i3);
    }
    // On crée une sous-image blanche en haut si nécessaire
    if (i > 0) {
      i2 = Construit_Composee(Construit_Blanc(), Construit_Blanc(), Construit_Blanc(), Construit_Blanc());
    }
    // On rassemble les sous-images
    return Construit_Composee(i0, i1, i2, i3);
  }
}
*/







void test1(){ // EstBlanche
  image Image1 = Construit_Blanc();
  image Image2 = Construit_Composee(Construit_Blanc(),
                                   Construit_Blanc(),
                                   Construit_Blanc(),
                                   Construit_Blanc());
  assert(EstBlanche(Image1));
  assert(EstBlanche(Image2));
}


void test2(){ // EstNoire
  image Image1 = Construit_Noir();
  image Image2 = Construit_Composee(Construit_Noir(),
                                   Construit_Noir(),
                                   Construit_Noir(),
                                   Construit_Noir());
  assert(EstNoire(Image1));
  assert(EstNoire(Image2));
}


void test3(){ // ConstruitBlanc
  image I1 = Construit_Blanc();
  assert(EstBlanche(I1));
}


void test4(){ //ConstruitNoir
  image I2 = Construit_Noir();
  assert(EstNoire(I2));
}


void test5(){ //ConstruitComposee
        image I1 = Construit_Composee(Construit_Blanc(),
                                Construit_Noir(),
                                Construit_Blanc(),
                                Construit_Blanc());

  image I2 = Construit_Composee(Construit_Blanc(),
                               Construit_Blanc(),
                               Construit_Blanc(),
                               Construit_Blanc());
  assert(EstBlanche(I2));

  image I3 = Construit_Composee(Construit_Noir(),
                               Construit_Noir(),
                               Construit_Noir(),
                               Construit_Noir());
  assert(EstNoire(I3));


  assert(EstBlanche(I1->fils[0]) && EstNoire(I1->fils[1]));


}

void testLecture(){
  printf("\nTapez n'importe quel image \n");
  
  image Ilue = lecture();
  printf("L'image obtenu: ");
  AfficheNormal(Ilue);


}

void testDIag(){
    printf("\nDiagonale(3): ");
    AfficheNormal(Diagonale(3));
}


void testNegatif(){
    printf("\nTest negatif: \n");
  image Image1 = Construit_Composee(Construit_Noir(),
                                   Construit_Noir(),
                                   Construit_Noir(),
                                   Construit_Composee(Construit_Noir(),
                                                     Construit_Blanc(),
                                                     Construit_Blanc(),
                                                     Construit_Noir())) ;

  image Image2 = Construit_Composee(Construit_Blanc(),
                                   Construit_Blanc(),
                                   Construit_Blanc(),
                                   Construit_Composee(Construit_Blanc(),
                                                     Construit_Noir(),
                                                     Construit_Noir(),
                                                     Construit_Blanc())) ;

  negatif(&Image1);
  printf("\n I1: ");
  AfficheNormal(Image1);
  printf("\n I2: ");
  AfficheNormal(Image2);
  printf("\nRentrez une valeur pour obtenir sa négation: ");
  image test = lecture();
  negatif(&test);
  AfficheNormal(test);
  printf("\n");
}

void testSimplifie(){
    printf("\nSimplifie: ");
  image test = lecture();
  printf("\nResultat: ");
  SimplifieProfP(test,2);
  AfficheNormal(test);
}

void testInc(){
    image Image1 = Construit_Composee(Construit_Noir(), Construit_Blanc(), Construit_Noir(), Construit_Blanc() );
    image Image2 = Construit_Noir();
    if(Incluse(Image2, Image1)) printf("\n Fonctionnel\n");
}


void testBlanchit(){
    image Image1 = Construit_Composee(Construit_Noir(), Construit_Blanc(), Construit_Noir(), Construit_Blanc() );
    BlanchitProfP(&Image1,2,1,3);
    AfficheNormal(Image1);

}

void testHaut(){
    printf( "\n Test HMB: \n");
    image Image0 = Construit_Blanc();
    image Image1 = Construit_Composee(Construit_Blanc(), Construit_Blanc(), Construit_Blanc(), Construit_Blanc() );
    if ( hautMaxBlanc(Image1,0) == 1) printf("\nCORRECT");
    if ( hautMaxBlanc(Image0,0) == 0) printf("\nCORRECT");

}


void testQuartDeTour(){
	//revoir les dangers des parentheses en extra
    printf("\nQuart: ");
	image im = lecture();
	image qIm = quartDeTour(im);
    printf("\n");
	AfficheNormal(qIm);
}
/*
void testChute(){
    image img1 = Construit_Composee(Construit_Noir(), Construit_Blanc(), Construit_Noir(), Construit_Noir());
    printf("\n Chute: ");
    AfficheNormal(Chute(img1));
    printf("\n");
    assert(Chute(img1) == Construit_Composee(Construit_Noir(), Construit_Noir(), Construit_Blanc(), Construit_Noir()));
}
*/

int main() {
// 

  test1(); // EstBlanche
  test2(); // EstNoire
  test3(); // Construit_Blanc
  test4(); // Construit_Noir
  test5(); //// Construit_Composee
  testLecture();
  testDIag();
  //testQuart();
  testNegatif();
  testSimplifie();
  testInc();
  testBlanchit();
  testHaut();
  testQuartDeTour();
  //testChute();
  return 0;
}
