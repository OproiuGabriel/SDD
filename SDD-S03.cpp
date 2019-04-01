#include<stdlib.h>
#include<string>
#include<stdio.h>
#include<malloc.h>

//Lista simpla inlatuita = o structura de data, fiecare nod contine informatia utila si adresa urmatorului nod
//Lista nu ocupa o zona de memorie contigua, 1(adresa lui 2)............3...............2(adresa lui 3)
//Merge doar de la stanga la dreapta, adica nu ma pot intoarce

struct Ferma {
	char* nume;
	int nrAnimale;
};

struct nod {
	Ferma info; // informatia utila
	nod* next; //adresa urmatorului nod

};

Ferma createFerma(const char * nume, int nrAnimale) {
	Ferma f;
	f.nume = (char*)malloc(sizeof(char)*(strlen(nume) + 1));
	strcpy(f.nume, nume);
	f.nrAnimale = nrAnimale;
	return f;
}

nod* createNod(Ferma f, nod* next) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = f; //facem shallow copy
	nou->next = next;
	return nou;
}

//Inserare la sfarsit in lista
//functia mea returneaza lista in care am inserat, adica prin nod*
nod* inserareSfarsit(nod* cap, Ferma f) {
	nod* nou = createNod(f, nullptr); //pt ca inseram la sfarsit avem nullptr
	if (cap != nullptr) {
		nod* temp = cap;
		while (temp->next != nullptr) {
			temp = temp->next; //ai unde sa te deplasezi pe un nod, atunci ma mut pe el
		}
		temp->next = nou; //pointeaza catre ce am inserat
	}
	else { 
		cap = nou;
	}
	return cap;
}


//Inserare la inceput in lista
nod* inserareInceput(nod* cap, Ferma f) {
	nod* nou = createNod(f, cap);
	//nu trebuie sa verificam daca avem sau nu lista;
	return nou;
}

//Inserare in interiorul listei inainte de un nod
nod* inserareInainteDeUnNodCuValoareaData(nod* cap, const char* nume, Ferma f) {
	nod* nou = createNod(f, nullptr);
	if (cap != nullptr) {
		nod* p = cap; //retinem adresa nodului
		nod* adresaMax = cap;
		while (p) { //cat timp avem lista in p 
			if (p->next && strcmp(p->next->info.nume, nume) == 0) { //daca are numele cautat
				if (p->next->info.nrAnimale > adresaMax->next->info.nrAnimale) { //daca trebuie sa inserez in fata unui nod
					// trebuie sa retin adresa nodului de dinainte
					adresaMax = p;
				}
			}
			p = p->next;
		}
		if (adresaMax == cap) { // daca adresa cap nu s-a deplasat
			if (strcmp(cap->info.nume, nume) == 0) {
				cap = inserareInceput(cap, f);
			}
			else {
				cap = inserareSfarsit(cap, f);//daca nu avem o ferma cu numele respectiv, inseram datele la sfarsit
			}
		}
		else {
			nou->next = adresaMax->next;
			adresaMax->next = nou;
		}
	}
	else {
		cap = nou;
	}
	return cap;
}

void afisareFerma(Ferma f) {
	printf("Ferma %s are %d animale. \n", f.nume, f.nrAnimale);
}

void afisareListaFerme(nod* cap) {
	while (cap) {
		afisareFerma(cap->info);
		cap = cap->next;
	}

	/*for (; i <  cap!=nullptr; cap=cap->next)
	{
		afisareFerma(cap->info);
	}*/
}

//Numarul mediu de animale pentru fermele dintr-o lista
float medieAnimale(nod* cap) {
	if (cap) {
		int nr = 0, s = 0;
		while (cap) { //cat timp avem cap
			nr++; //crestem nr de ferme
			s += cap->info.nrAnimale; //luam nr de animale si il adaugam la suma
			cap = cap->next; //trecem la nodul urmator
		}
		return s / nr; //impartim nr de animale la cate ferme avem
	}
	else 
		return 0;
}

//stergere de la cap catre coada a listei
nod* stergereLista(nod* cap) {
	while (cap) { //cat avem nod de sters, trebuie sa il stergem
		nod* aux = cap; //retinem adresa urmatorului nod
		cap = cap->next; //ne mutam pe urmatorul cap
		free(aux->info.nume); //dezalocam informatia din auxiliar
		free(aux); //dezalocam auxiliarul
	}
	return cap;
}

//stergere recursiva a listei
void stergereListaRecursiv(nod* *cap) { 
	if (*cap != nullptr) { //deferentiem pt ca avem pointer
		stergereListaRecursiv(&(*cap)->next);
		free((*cap)->info.nume);
		free(*cap);
		*cap = nullptr;
	}
}

void main() {
	Ferma f = createFerma("faraAnimale", 1);
	nod* node = createNod(f, nullptr); //nullptr pentru ca exista doar un singur nod si urmatorul nu exista, deci initializez pointerul cu null
	nod* cap = nullptr; //initializam lista cap si vom insera ulterior elemente: la sfarsit, la inceput sau in interior
	cap = inserareSfarsit(cap, createFerma("CocosulVesel", 200));
	cap = inserareSfarsit(cap, createFerma("No Secure", 100));
	cap = inserareSfarsit(cap, createFerma("Vaca vesela", 400));
	cap = inserareSfarsit(cap, createFerma("Crevedia", 1200));
	afisareListaFerme(cap);
	printf("\n");

	cap = inserareInceput(cap, createFerma("Avicola", 555));
	afisareListaFerme(cap);

	printf("\nValoarea medie a animalelor din lista: ");
	printf("%5.2f ", medieAnimale(cap));

	cap=stergereLista(cap); //transmit un pointer prin valoare, ciudat

	printf("\n");
	cap = inserareInceput(cap, createFerma("Ferma", 40));

	afisareListaFerme(cap);

	stergereListaRecursiv(&cap);

	printf("\n");
	//cap = inserareInceput(cap, createFerma("New", 40));
	afisareListaFerme(cap);

	
	printf("\n");
	cap = inserareSfarsit(cap, createFerma("A3", 300));
	cap = inserareSfarsit(cap, createFerma("A3", 200));
	cap = inserareSfarsit(cap, createFerma("A3", 1400));
	cap = inserareSfarsit(cap, createFerma("A3", 150));
	afisareListaFerme(cap);

	cap = inserareInainteDeUnNodCuValoareaData(cap, "A3", createFerma("NOUAA", 90));
	printf("\n");
	afisareListaFerme(cap);

}