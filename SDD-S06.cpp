#include<stdio.h>
#include<malloc.h>
#include<string.h>

//hashTable - tabele de dispersie care au cheie si valoare
//prin hash aduc valorile unei liste la o limita anume - un fel de normalizare
//am nevoie de o cheie pe baza careia am o functie care va calula hash ul iar rezultatul va fi pozitia din lista 
//hashTable presupune sa avem un vector prin care inseram elemente

struct Za {
	char* material;
	int diametru;
	int code; //pt cheie
};

Za* createZa(const char* material, int diametru, int code) {
	Za *za = (Za*)malloc(sizeof(Za));
	za->material = (char*)malloc(sizeof(char)*strlen(material) + 1);
	strcpy(za->material, material);
	za->diametru = diametru;
	za->code = code;
	return za;
}

void afisareZa(Za z) {
	printf("%d. Avem o Za din %s cu diametru %d. \n", z.code, z.material, z.diametru);
}

struct HashTable {
	Za* *vector; //vector de pointeri
	int dim;
};

HashTable initilizareHashTable(int dim) {
	HashTable ht;
	ht.dim = dim;
	ht.vector = (Za**)malloc(sizeof(Za*)*dim);
	for (int i = 0; i < dim; i++) {
		ht.vector[i] = NULL;
	}
	return ht;
}

//functia hash va returna un int adica pozitia din vectorul meu
int hashFunction(Za z, HashTable table) {
	return (z.code + z.diametru) % table.dim; // 9%5=4
}

//functie de inserare a unei zale in vector
int inserareZa(HashTable h, Za *z) { //unde inserez si ce inserez // pun pointer ca sa preia continutul ulterior
	if (h.dim > 0)
	{ //daca exista tabela hash
		int pozitie = hashFunction(*z, h);
		if (h.vector[pozitie] != NULL) { //inseamna ca am coliziune intre doua obiecte
			int index = (pozitie + 1) % h.dim; // 4+1=5>4, dar cu modulo% va da 4=4
			while (h.vector[index] != NULL && index != pozitie) { 
				index = (index + 1) % h.dim;
			}
			if (index == pozitie) {
				//dam un mesaj
				return -1;
			}
			else {
				h.vector[index] = z; //am pointer in vector iar z este obiect, deci ii iau adresa obiectului si o bag in vector;
				return index;
				}
		}
		else {//daca locul este gol inseram
			//forma de rezolvare a coliziunii- chaining -Curs
			//forma de rezolvare a coliziunii - liniar probing -Seminar
			h.vector[pozitie] = z;
			return pozitie;
		}
	}
	else 
	{
		return -2;

	}
}

void afisareHashTable(HashTable h) {
	for (int i = 0; i < h.dim; i++)
	{
		if (h.vector[i] != NULL) {
			afisareZa(*h.vector[i]); //deferentiem deoarece acolo avem o adresa in vector;
		}
	}
}

//functie de returnare pointer
int cautaZaInTabela(HashTable h, Za *z) {
	if (h.dim > 0) { //daca am tabela
		int pozitie = hashFunction(*z, h);
		if (h.vector[pozitie]->code == z->code) {
			return pozitie;
		}
		else {
			int index = pozitie;
			do {
				index = (index + 1) % h.dim;
				if (h.vector[index] != NULL && h.vector[index]->code != z->code) {
					break; //imi iese din while;
				}
			} while (index != pozitie);
			if (index == pozitie) {
				return -1;
			}
			else {
				return index;
			}
		}
	}
	else {//daca nu am tabela
		return -2;
	}
}

//extragereZa
Za* extragereZaDintabela(HashTable h, int pozitie) {
	if (h.dim > 0 && pozitie < h.dim && pozitie >= 0) {
		if (h.vector[pozitie]) {
			Za* zaPointer = h.vector[pozitie];
			h.vector[pozitie] = NULL;
			return zaPointer;
		}

	}
	return NULL;
}

void main() {

	HashTable h = initilizareHashTable(5);

	Za* pointerZa = createZa("Otel", 3, 1); //pozitie 4

	inserareZa(h, pointerZa); //le comentam
	inserareZa(h, createZa("Otel", 3, 2)); // le comentam ca sa nu ne intoarca -1 si sa ne insereze pe pozitia 4
	inserareZa(h, createZa("Otel", 3, 3));
	inserareZa(h, createZa("Otel", 3, 4));
	inserareZa(h, createZa("Otel", 3, 5));
	int index = inserareZa(h, createZa("Otel", 3, 6));
	printf("%d", index);

	printf("\n");
	afisareHashTable(h);

	printf("Pozitie:%d", cautaZaInTabela(h, pointerZa)); //pozitie 4

	printf("\n");
	extragereZaDintabela(h, 2);

	afisareHashTable(h);
}


