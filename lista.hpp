#ifndef _LISTA_HPP_
#define _LISTA_HPP_

class ListanSolmu
{
public:

	//muodostimet ja tuhoajat
	ListanSolmu();
	ListanSolmu(void *ptr);
	~ListanSolmu();

	//asettaa solmun datan halutuksi
	void set(void *ptr);

	//tulostaa tiedot
	void print();

	//osoittimet seuraaviin osiin
	class ListanSolmu *next;
	class ListanSolmu *previous;

	//data, jota solmu kantaa
	void *payload;

};

class Lista
{
public:
	Lista();
	~Lista();
	
	//lis�t��n listan loppuun alkio (onnistuu aina)
	void add(void *dataptr);
	//poistetaan listan viimeinen alkio (palauttaa false jos lista on tyhj�)
	bool removeLast();
	//lis�t��n ty�pointterin j�lkeen alkio (palauttaa false jos ty�pointteri ei ole kelvollinen)
	bool insert(void *dataptr);
	//poistetaan alkio ty�pointterin kohdalta
	bool remove();

	//tuhotaan koko lista ja vapautetaan kaikki tiedot
	void destroy();

	//asettaa ty�pointterin listan alkuun (palauttaa false jos lista on tyhj�)
	bool goToStart();
	//asettaa ty�pointterin listan loppuun (palauttaa false jos lista on tyhj�)
	bool goToEnd();
	//liikuttaa ty�pointteria eteenp�in (palauttaa false jos lista on loppu)
	bool goForward();
	//liikuttaa ty�pointteria taaksep�in (palauttaa false jos ollaan alussa)
	bool goBackwards();
	//menee haluttuun nodeen (palauttaa false jos ei onnistu)
	bool goToNode(int number); 

	//tutkii, ollaanko ekassa nodessa
	bool isAtEnd();
	//tutkii, ollaanko vikassa nodessa
	bool isAtStart();

	//antaa ensimm�isen noden osoittaman tiedon
	void *getFirst();
	//antaa viimeisen noden osoittaman tiedon
	void *getLast();
	//antaa ty�pointterin osoittaman tiedon
	void *getCurrent();
	//asettaa ty�pointterin nodeen uuden tiedon (tuhoaa vanhan jos siell� sellaista on)
	void setCurrent(void *ptr);
	//kertoo kuinka monta solmua listassa on
	int getNodeCount();
	//kertoo nykyisen noden
	int getCurrentNodeNumber();

	//tulostetaan lista lokiin (debug)
	void print();
private:
	int solmuja;
	ListanSolmu *start;
	ListanSolmu *current;
	ListanSolmu *end;

};

#endif 
