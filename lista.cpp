#include <stdio.h>
#include "lista.hpp"

//#define LISTDEBUG

ListanSolmu::ListanSolmu()
{
}
ListanSolmu::~ListanSolmu()
{
}
ListanSolmu::ListanSolmu(void *ptr)
{
	payload = ptr;
}
void ListanSolmu::set(void *ptr)
{
	payload = ptr;
}
void ListanSolmu::print()
{

}
Lista::Lista()
{
	//nollataan kaikki osoittimet
	start = 0;
	current = 0;
	end = 0;
	//nollataan solmujen m��r�
	solmuja = 0;
#ifdef LISTDEBUG
	loki->writeToLog("Lista::Lista() : lista luotu");
#endif
}
Lista::~Lista()
{
}

//lis�t��n alkio listan loppuun
void Lista::add(void *dataptr)
{
	ListanSolmu *temp;
	solmuja++;

	if (start == 0) //lis�t��n listaan ensimm�ist� alkiota
	{
		//luodaan uusi solmu
		temp = new ListanSolmu(dataptr);

		//koska solmu on ensimm�inen, n�m� ovat molemmat 0
		temp->previous = 0;
		temp->next = 0;

		//molemmat "p��osoittimet" osoittamaan ekaan solmuun
		start = temp;
		end = temp;

#ifdef LISTDEBUG
		loki->writeToLog("Lista::add : Luotu ensimm�inen listan solmu");
		temp->print();
#endif
	}
	else
	{
		//luodaan uusi solmu listan per�lle
		ListanSolmu *temp = new ListanSolmu(dataptr);
		//seuraavaa solmua ei tietenk��n ole
		temp->next = 0; 

		//menee yhden askeleen lopun j�lkeen. Muutetaan vanha listan loppu osoittamaan t�h�n solmuun
		temp->previous = end;
		end->next = temp;

		//uusi solmu on listan viimeinen
		end = temp;		
#ifdef LISTDEBUG
		loki->writeToLog("Lista::add : Luotu uusi solmu listaan");
		temp->print();
#endif
	}
}

//laitetaan uusi alkio ty�osoittimen kohdalle
bool Lista::insert(void *dataptr)
{
	if (current==0)
	{
		return false; //ty�osoitin ei ole kelvollinen, joten ei tehd� mit��n ja palautetaan false
	}
	//ollaan listan lopussa
	if (current == end)
	{
		add(dataptr); //laitetaan listan loppuun uusi alkio
		return true;
	}
	//lis��minen onnistuu joka tapauksessa t�st� eteenp�in, joten lis�t��n solmujen m��r��
	solmuja++;
	//ollaan listan alussa tai keskell�, joten luodaan uusi solmu
	ListanSolmu *temp = new ListanSolmu(dataptr); 
	//asetetaan uusi solmu osoittamaan seuraavaan solmuun
	temp->next = current->next;
	//seuraavan solmun previous osoittaa uuteen solmuun
	current->next->previous = temp; 
	//seuraava solmu hoideltu
	//uusi solmu tulee v�liin, joten sen edellinen on nykyinen
	temp->previous = current;
	//lopulta s��det��n currentin seuraavan osoitin uuteen
	current->next = temp; 

	//huh
	return true;
}


//poistetaan alkio ty�pointterin kohdalla
bool Lista::remove()
{
	if (start == 0)	//lista tyhj�
	{
#ifdef LISTDEBUG
		loki->writeToLog("Lista::remove : ei ole mit��n poistettavaa");
#endif
		return false; //ei ole mit��n poistettavaa
	}
	if (start == end)		//vain yksi alkio listassa (current == start)
	{
		solmuja--;
#ifdef LISTDEBUG
		loki->writeToLog("Lista::remove : vain yksi alkio listassa");
#endif
		if (current->payload != 0)	//poistetaan lasti jos sit� on
		{
			delete current->payload;
		}
		delete current; //tuhotaan solmu

		start = 0;
		end = 0;
		current = 0; //nollataan pointterit

		return true;
	}
	if (current == end)	//yritet��n poistaa viimeist� alkiota
	{
#ifdef LISTDEBUG
		loki->writeToLog("Lista::remove : poistetaan viimeinen alkio");
#endif
		removeLast();	//solmujen m��r� muutetaan t��ll�
		return false;
	}
	if (current == start) //yritet��n poistaa ensimm�ist� alkiota
	{
		solmuja--;
#ifdef LISTDEBUG
		loki->writeToLog("Lista::remove : poistetaan ensimm�ist� alkiota");
#endif
		ListanSolmu *temp = start->next;	//osoitetaan listan toiseen alkioon
		temp->previous = 0;					//josta tehd��n listan ensimm�inen alkio
		if (start->payload != 0)
		{
			delete start->payload;
		}
		delete start; //poistetaan start-osoittimen osoittama alkio
		start = temp; //ja laitetaan se osoittamaan listan toiseen alkioon, joka on nyt ensimm�inen
		current = temp; //current my�s

		return true;
	}
	//erikoistapaukset k�sitelty

	solmuja--;
	ListanSolmu *temp;
	if (current->next != 0)
		temp = current->next;
	else
		temp = current->previous;

	current->previous->next = current->next; //hyp�t��n currentin ylitse
	current->next->previous = current->previous;

	if (current->payload != 0)
	{
		delete current->payload;
	}
	delete current;
	current = temp; //current on joko seuraava tai edellinen (jos seuraavaa ei ollut)
	return true;
}

//poistetaan listan viimeinen alkio

bool Lista::removeLast()
{
	if (start == 0)
	{
#ifdef LISTDEBUG
		loki->writeToLog("Lista::removeLast : ei ole mit��n poistettavaa");
#endif
		return false; //ei ole mit��n poistettavaa
	}
	else
	{
		solmuja--;
		if (end->previous == 0) //jos listassa on vain yksi alkio
		{
#ifdef LISTDEBUG
			loki->writeToLog("Lista::removeLast : vain yksi alkio");
#endif
			if (end->payload != 0) //jos lista osoittaa johonkin
			{
				delete end->payload;
			}
			delete end;	//poistetaan viimeinen alkio
			end = 0;	//nollataan n�m�, muuten ne osoittavat jonnekin jota ei ole en�� olemassa
			start = 0;
			current = 0;
		}
		else		//poistetaan viimeinen alkio
		{
#ifdef LISTDEBUG
			loki->writeToLog("Lista::removeLast");
#endif
			//solmu, joka osoittaa edelliseen
			ListanSolmu *temp = end->previous;

			//tuhotaan viimeisen solmun lasti
			if (end->payload != 0)
			{
				delete end->payload;
			}
			//jos current osoittaa loppuun, vaihdetaan se osoittamaan uuteen loppuun (muuten ryskis)
			if (current == end)
			{
				current = current->previous;
			}
			delete end;
			end = temp;
			temp->next = 0;
		}
		return true; //poisto onnistui
	}
}

//tuhotaan koko lista
void Lista::destroy()
{
	int temp = solmuja; //solmuja muuttuu removeLastissa, joten siksi tehd��n siit� kopio nyt
#ifdef LISTDEBUG
	loki->writeToLog("Lista::destroy");
#endif
	for (int i=0;i<temp;i++)
		removeLast();
}

bool Lista::goToStart()
{
	if (start!=0)
	{
#ifdef LISTDEBUG
		loki->writeToLog("Lista::goToStart() onnistui");
#endif
		current = start;	//lista on olemassa
		return true;
	}
#ifdef LISTDEBUG
	loki->writeToLog("Lista::goToStart() ep�onnistui");
#endif
	current = 0;
	return false;
}
bool Lista::goToEnd()
{
	if (end!=0)
	{
#ifdef LISTDEBUG
		loki->writeToLog("Lista::goToEnd() onnistui");
#endif
		current = end;	//lista on olemassa
		return true;
	}
#ifdef LISTDEBUG
	loki->writeToLog("Lista::goToStart() ep�onnistui");
#endif
	current = 0;
	return false;
}
bool Lista::goForward()
{
	if (current == end)
	{
#ifdef LISTDEBUG
		loki->writeToLog("Lista::goForward() yritti menn� lopusta ylitse!");
#endif
		return false;
	}
	if (current->next!=0)
	{
#ifdef LISTDEBUG
		loki->writeToLog("Lista::goForward() onnistui");
#endif
		current = current->next;
		return true;
	}
#ifdef LISTDEBUG
	loki->writeToLog("Lista::goForward() ep�onnistui");
#endif
	return false;
}
bool Lista::goBackwards()
{
	if (current->previous!=0)
	{
#ifdef LISTDEBUG
		loki->writeToLog("Lista::goBackwards() onnistui");
#endif
		current = current->previous;
		return true;
	}
#ifdef LISTDEBUG
	loki->writeToLog("Lista::goBackwards() ep�onnistui");
#endif
	return false;
}

bool Lista::goToNode(int number)
{
	/* paskaa koodia! */
	bool value;
	goToStart();

	for (int i=0;i<number;i++)
	{
		value = goForward();
	}
	return value;
}
int Lista::getCurrentNodeNumber()
{
	/* paskaa koodia! */
	int i=0;
	ListanSolmu *walker = start;
	while (walker != current)
	{
		i++;
		walker = walker->next;
	}
	return i;

}


void *Lista::getFirst()
{
	return start->payload;
}
void *Lista::getLast()
{
	return end->payload;
}
void *Lista::getCurrent()
{
	return current->payload;
}
void Lista::setCurrent(void *ptr)
{
	if (current->payload) //tuhotaan vanha
	{
		delete current->payload;
	}
	current->payload = ptr; 
}
int Lista::getNodeCount()
{
	return solmuja;
}

bool Lista::isAtEnd()
{
	if (current == end)
		return true;
	else return false;
}

bool Lista::isAtStart()
{
	if (current == start)
		return true;
	else return false;
}

void Lista::print()
{
#ifdef LISTDEBUG
	loki->writeToLog("Lista::print");
#endif
	ListanSolmu *walker = start;
	if (walker == 0)
		return; //listassa ei ole mit��n
	while (walker!=0)
	{
		walker->print();
		walker = walker->next;
	}
}
 
