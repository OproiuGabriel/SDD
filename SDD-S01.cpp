//SEMINAR 1

#include<stdio.h>
#include<stdlib.h>


void citire(int dim, int*vector) {
	for (int i = 0; i < dim; i++)
	{
		scanf("%d", &vector[i]);
	}
}

void afisare(int dim, int* vector) {
	for (int i = 0; i < dim; i++)
	{
		printf("%d ", vector[i]);
	}
}

//specifica c++
void citire2(int &dim, int* &vector) { //acel dim este o valoare, iar programatorul a luat adresa si cand facem referire la acea valoare sa se duca la adresa pe care o are el
	scanf("%d", &dim); //cand citim
	vector = (int*)malloc(dim * sizeof(int));
	for (int i = 0; i < dim; i++)
	{
		scanf("%d", &vector[i]);
	}

}

void citire3(int* dim, int **vector) { //** vector este un pointer catre un vector
	scanf("%d", dim);
	*vector = (int*)malloc(*dim * sizeof(int));
	for (int i = 0; i < *dim; i++)
	{
		scanf("%d", &(*vector)[i]);
	}
}

void cMatrice(int *m, int *n, int ***a) {
	scanf("%d", m);
	scanf("%d", n);
	*a = (int**)malloc(sizeof(int*)*(*m));
	for (int i = 0; i < *m; i++) {
		
		(*a)[i] = (int*)malloc(sizeof(int)*(*n)); //a[i] pentru ca indexam fiecare coloana
		//citim de la tastatura valori pentru fiecare coloana
		for (int j = 0; j < *n; j++) {
			scanf("%d", &(*a)[i][j]); //*vector+i cand deferentiez si o sa obtin o adresa
		}
	}
}

void aMatrice(int m, int n, int **matrice) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", matrice[i][j]);
		}
		printf("\n");

	}
}

int main() {

	/*int dimensiune;
	int *vector;*/
	//scanf("%d", &dimensiune);
	//vector = (int*)malloc(dimensiune * sizeof(int));

	/*for (int i = 0; i < dimensiune; i++) 
	{
		scanf("%d", &vector[i]);
	}*/
	/*for (int i = 0; i < dimensiune; i++)
	{
		printf("%d", vector[i]);
	}*/
	
	/*citire3(&dimensiune, &vector);
	afisare(dimensiune, vector);*/
	int **matrice;
	int m, n;
	cMatrice(&m, &n, &matrice);
	aMatrice(m, n, matrice);

}

