//SEMINAR 2
//Tema -> De facut quiz-uri si de incarcat pe online.ase.ro
#include<stdlib.h>
#include<stdio.h>
#include<string>

struct Bilet {
	int cod;
	float pretBilet;
	char* destinatie;
};

Bilet initializare(int c, float p, const char* den) {
	Bilet b;
	b.cod = c;
	b.pretBilet = p;
	b.destinatie = (char*)malloc(sizeof(char)*(strlen(den) + 1));
	strcpy(b.destinatie , den);
	return b;
}


void afisare(Bilet b) {
	printf("Codul:%d \n", b.cod);
	printf("Pretul:%f \n", b.pretBilet);
	printf("Destinatie:%s \n", b.destinatie);
}

 Bilet citire() {
	 Bilet b1;
	 char nume[10];
	 scanf("%d \n", &b1.cod);
	 scanf("%f \n", &b1.pretBilet);
	 scanf("%s", nume);
	 b1.destinatie = (char*)malloc(sizeof(char)*(strlen(nume) + 1));
	 strcpy(b1.destinatie, nume);
	 return b1;
}
 Bilet* citire_vector_bilete(int* nrLinii) {
	 Bilet* b;
	 scanf("%d", nrLinii);
	 b = (Bilet*)malloc(*nrLinii * sizeof(Bilet));
	 for (int i = 0; i < *nrLinii; i++)
	 {
		 b[i] = citire();
	 }
	 return b;
 }

 void afisare_vector_bilete(Bilet* b, int nrColoane) {
	 for (int i = 0; i < nrColoane; i++)
	 {
		 afisare(b[i]);
	 }
 }

 Bilet** citire_masiv(int* nr_lini, int* *coloane) {
	 printf("\n Introdu nr de lini: ");
	 scanf("%d", nr_lini);
	 Bilet** b;
	 b = (Bilet**)malloc((*nr_lini) * sizeof(Bilet*));
	 *coloane = (int*)malloc(sizeof(int)* (*nr_lini));
	 for (int i = 0; i < *nr_lini; i++)
	 {
		 printf("Nr.elemente de pe linie %d: ", i + 1);
		 scanf("%d", &(*coloane)[i]);
		 b[i] = (Bilet*)malloc((*coloane)[i] * sizeof(Bilet));
		 for (int j = 0; j < (*coloane)[i]; j++)
		 {
			 printf("Introdu biletul[%d][%d]:",i+1,j+1);
			 b[i][j] = citire();
		 }
	 }
	 return b;
 }

 void afisareMatrice(Bilet** b, int nrLinii, int* nrColoane) {
	 for (int i=0; i < nrLinii; i++)
	 {
		 printf("Biletele de pe linia %d\n", i);
		 for (int j = 0; j < nrColoane[i]; j++) {
			 afisare(b[i][j]);
		 }
	 }
 }


void main() {

	Bilet b1 = initializare(1, 99.77, "Malibu");
	afisare(b1);
	//Bilet b2 = citire();
	//afisare(b2);
	
	Bilet** matrice;
	int* nrColoane=NULL;
	int nrLinii = 0;
	matrice = citire_masiv(&nrLinii, &nrColoane);
	afisareMatrice(matrice, nrLinii, nrColoane);

	for (int i = 0; i < nrLinii; i++)
	{
		for (int j = 0; j < nrColoane[i]; j++)
		{
			free(matrice[i][j].destinatie);
		}
		free(matrice[i]);
	}
	free(matrice);
	free(nrColoane);
	free(b1.destinatie);
	//free(b2.destinatie);

	Bilet* vector;
	int nrLiniiVector;
	vector = citire_vector_bilete(&nrLiniiVector);
	afisare_vector_bilete(vector, nrLiniiVector);
	

}