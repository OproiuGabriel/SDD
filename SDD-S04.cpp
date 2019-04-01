//DE RECUPERAT JOI 21.03.2019 ; LUNI 25.03.2019 -> ora 12:00 
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<string>

//Lista dublu inlantuita -> contine adresa precedentului nod si a urmatorului nod, iar primul va adresa NULL si ultimul tot adresa NULL
//identific lista prin primul nod si prin ultimul nod in care imi creez o structura cu nodurile prim si ultim
struct Client {
	char* nume;
	int varsta;
	float valoareComanda;
};

struct Nod {
	Client info;
	Nod* next;
	Nod* previous;
};

Client createClient(const char* nume, int varsta, float valoareComanda) {
	Client c;
	c.nume = (char*)malloc(sizeof(char)*(strlen(nume) + 1));
	strcpy(c.nume, nume);
	c.varsta = varsta;
	c.valoareComanda = valoareComanda;
	return c;
}

Nod* createNod(Client c, Nod* next, Nod* previous) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c; //shallow copy
	nou->next = next;
	nou->previous = previous;
	return nou;
}

struct ListaDubluInlantuita {
	Nod* prim;
	Nod* ultim;
};

ListaDubluInlantuita inserareInceput(ListaDubluInlantuita ldi, Client c) {
	Nod* nou = createNod(c, ldi.prim, nullptr); //intotdeauna null la previous cand inseram primul nod;
	if (ldi.prim != nullptr) {
		ldi.prim->previous = nou; //daca exista acest nod ldi ma duc la el si previous va fi nou;
		ldi.prim = nou; //noul nod creat o sa fie iar "primul"
	}
	else {
		ldi.prim = nou;
		ldi.ultim = nou;
	}
	return ldi;
}

ListaDubluInlantuita inserareSfarsit(ListaDubluInlantuita ldi, Client c) {
	Nod* nou = createNod(c, nullptr, ldi.ultim);
	if (ldi.ultim) {
		ldi.ultim->next = nou;
		ldi.ultim = nou;
	}
	else {
		ldi.ultim = nou;
		ldi.prim = nou;
	}
	return ldi;
}


void afisareClient(Client c) {
	printf("%s in varsta de %d ani are de plata %5.2f lei \n", c.nume, c.varsta, c.valoareComanda);
}

void afisareLista(ListaDubluInlantuita ldi, int modParcurgere) { 
	//1 stanga spre dreapta
	//0 dreapta spre stanga
	if (modParcurgere == 1) {
		Nod* temp = ldi.prim;
		while (temp) {
			afisareClient(temp->info);
			temp = temp->next;
		}
	}
	else {
		Nod* temp = ldi.ultim;
		while (temp) {
			afisareClient(temp->info);
			temp = temp->previous;
		}
	}
}

void stergereLista(ListaDubluInlantuita &ldi) { //o transmitem prin referinta sau o returnam
	while (ldi.prim != nullptr) {
		Nod* aux = ldi.prim;
		ldi.prim = ldi.prim->next; //am mutat primul pe al doilea nod
		free(aux->info.nume);
		free(aux);
	}
	ldi.prim = nullptr;
	ldi.ultim = nullptr;

}

Client extragereClientDinListaDupaNume(ListaDubluInlantuita &ldi, const char* nume) { //referinta pentru ca l-am modificat in Stack
	Nod* temp = ldi.prim;
	while (temp && strcmp(temp->info.nume, nume) != 0) {
		temp = temp->next;
	}
	if (temp) {
		Client rezultat = temp->info;//ne salvam clientul gasit
		if (temp->previous != nullptr) { //daca nu e primul
			temp->previous->next = temp->next;
			if (temp->next != nullptr) { //daca nu e ultimul
				temp->next->previous = temp->previous;
			}
			else {
				ldi.ultim = temp->previous; //ultimul element din lista nu mai pointeaza catre ultimul nod ci catre anteriorul, pt ca pe
				//ultimul poate l-am sters;
			}
		}
		else {
			temp->next->previous = nullptr;
			ldi.prim = temp->next;
		}
		free(temp); //sterg informatia despre client-shallow copy pros
		return rezultat;
	}
	else {
		return createClient("", 0, 0);
	}
}

void main() {

	ListaDubluInlantuita ldi;
	ldi.prim = nullptr;
	ldi.ultim = nullptr;

	ldi = inserareInceput(ldi, createClient("Popescu", 20, 1000));
	ldi = inserareInceput(ldi, createClient("Ionescu", 33, 2000));
	ldi = inserareInceput(ldi, createClient("Radulescu", 53, 4000));

	printf("Afisare de la stanga la dreapta dupa inserare la inceput: \n\n");
	afisareLista(ldi, 1);

	printf("\nAfisare de la stanga la dreapta dupa inserare la sfarsit: \n\n");
	ldi = inserareSfarsit(ldi, createClient("Oproiu", 19, 5000));
	afisareLista(ldi, 1);

	stergereLista(ldi);
}