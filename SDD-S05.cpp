#include<stdlib.h>
#include<stdio.h>
#include<string>
//2017 recuperare;
//C:\Users\stud\source\repos\SDD - S05\SDD - S05\SDD - S05.cpp
//LUCRARE 6-7 APRILIE
//LISTE PT TEST
//STIVE SI COZI PT TEST
//TABELE DE DISPERSIE PT TEST
//urmatoarele doua sapt nu facem;

//Stiva= o structura unde se fac la sfarsit sau inceput toate procesarile, ori la sfarsit, ori la inceput, dar in acelasi loc (inseare+extragere)
//Coada= inserare la un capat si extreagere obligatoriu la alt capat
//Stiva - functii: push, pop, functie care verifica daca o stiva e goala sau nu

struct Vagon {
	int nrPasageri;
	float* preturiBilete;
	int id;
};

Vagon createVagon(int nrPasageri, float* preturiBilete, int id) {
	Vagon v;
	v.nrPasageri = nrPasageri;
	v.preturiBilete = (float*)malloc(sizeof(float)*nrPasageri);
	for (int i = 0; i < nrPasageri; i++) {
		v.preturiBilete[i] = preturiBilete[i];
	}
	v.id = id;
	return v;
}

void afisareVagon(Vagon v) {
	printf("%d. Vagonul are %d pasageri care au platit: ", v.id, v.nrPasageri);
	for (int i = 0; i < v.nrPasageri; i++) {
		printf("%5.2f, ", v.preturiBilete[i]);
	}
	printf("\n");
}

struct Nod {
	Vagon info;
	Nod* next;
};

Nod* pushStack(Nod* cap, Vagon v) { //fac o inserare;
	Nod* nou = (Nod*)malloc(sizeof(Nod)); //cream un nod nou;
	nou->info = v;
	nou->next = cap; //vrem inserare la inceput;
	return nou; // noul nod creat devine cap;
}

Vagon popStack(Nod* &cap) {//pop= extragere + stergere nod extras; referinta ca sa pastram adresa lui daca e singur in lista
	if (cap != nullptr) {
		Vagon rezultat = createVagon(cap->info.nrPasageri, cap->info.preturiBilete, cap->info.id); //deep copy
		Nod* aux = cap;
		cap = cap->next; //mutam pe cap pe urmatorul pentru a il sterge pe cel de dinainte;
		free(aux->info.preturiBilete); //sterg deep copy ul ;
		free(aux); //asa stergeam shallow copy daca nu aveam linia de dinainte;
		return rezultat;
	}
	else {
		return createVagon(0, nullptr, 0); 
	}
}

int isEmptyStack(Nod* cap) {
	return cap == nullptr;
}

struct NodDublu {
	Vagon info;
	NodDublu* next;
	NodDublu* previous;
};

struct LDI {
	NodDublu* prim;
	NodDublu* ultim;
};

//coada= bagi pe la un capat si iese pe celalalt;
LDI pushQueue(LDI ldi, Vagon v) {//returneaza lista
	NodDublu* nodNou = (NodDublu*)malloc(sizeof(NodDublu));
	nodNou->info = v; //shallow copy
	nodNou->next = ldi.prim;
	nodNou->previous = nullptr;
	//verific daca am lista
	if (ldi.prim != nullptr) {
		ldi.prim->previous = nodNou;
		ldi.prim = nodNou;
	}
	else {
		//daca nu am lista
		ldi.prim = ldi.ultim = nodNou; //primul si ultimul nod devin unul si acelasi;
	}
	return ldi;
}

Vagon popQueue(LDI &ldi) { //daca vom modifica prim sau ultim va trb sa ramana modificarea si in main
	if (ldi.ultim != nullptr) {
		Vagon rezultat = ldi.ultim->info; //shallow copy;
		if (ldi.ultim != ldi.prim) { //daca am mai multe noduri
			ldi.ultim = ldi.ultim->previous;
			free(ldi.ultim->next);//stergem nodul din coada listei;
			ldi.ultim->next = nullptr; //facem null adresa de pe next a noului ultim nod;
		}
		else {
			free(ldi.ultim);
			ldi.ultim = ldi.prim = nullptr;
		}
		return rezultat;
	}
	else {
		return createVagon(0, nullptr, 0);
	}
}

int isEmptyQueue(LDI ldi) {
	return ldi.prim == nullptr;
}

float getIncasari(LDI ldi) {
	float max = 0, s = 0;
	Vagon primul = popQueue(ldi);
	if (isEmptyQueue(ldi) != 0) {
		for (int i; i <primul.nrPasageri; i++) {
			s = s + primul.preturiBilete[i];
		}
		max = s;
	}

	Vagon aux = popQueue(ldi);
	while (isEmptyQueue(ldi)!=0) {
		s = 0;
		for (int i; i < aux.nrPasageri; i++) {
			s = s + aux.preturiBilete[i];
		}
		if (s > max) {
			max = s;
		}
	}
}


void main() {
	Nod* stiva = nullptr;
	int nrPasageri=3;
	float* vector = (float*)malloc(sizeof(float)*nrPasageri);
	for (int i = 0; i < nrPasageri; i++) {
		vector[i] = i + 10; //ii putem sterge pt ca am facut deep copy anterior
	}
	stiva = pushStack(stiva, createVagon(nrPasageri, vector, 1));
	free(vector);

	int nrPasageri2 = 2;
	float* vector2 = (float*)malloc(sizeof(float)*nrPasageri2);
	for (int i = 0; i < nrPasageri2; i++) {
		vector2[i] = i + 10;
	}
	stiva = pushStack(stiva, createVagon(nrPasageri2, vector2, 2));
	free(vector2); 
	
	//stiva - pot accesa elementul din varful ei, doar din varful ei
	//le scoatem pe toate pe rand ca sa le afisam;
	//while (!isEmptyStack(stiva)) {
	//	Vagon v = popStack(stiva); //pentru a nu lasa memoryleaks;
	//	afisareVagon(v);
	//	free(v.preturiBilete); //dezalocam si preturile la care am fi pierdut referintele;

	//}


	//ex: luati toate elementele din stiva si le puneti in coada;
	LDI coada;
	coada.prim = nullptr;
	coada.ultim = nullptr;
	while (!isEmptyStack(stiva)) {
		coada = pushQueue(coada, popStack(stiva));//am extras elementele din stiva si le-am pus in coada;
	}

	while (!isEmptyQueue(coada)) {
		Vagon v = popQueue(coada); //pentru a nu lasa memoryleaks;
		afisareVagon(v);
		free(v.preturiBilete);
	}

	//ex: determinati vagonul cu cele mai multe incasari prin functie, iar coada sa ramana in aceeasi formula;
	

}