#include "Agentie.h"
#include<iostream>
using namespace std;

Agentie::Agentie(int nrOf, int nrT)
	:nrOferte(nrOf), nrTari(nrT), logareCont(0)
{
}

void Agentie::setTara(const string& s)
{
	tari.push_back(s);
}

void Agentie::setOferta(Oferta& o)
{
	oferte.push_back(o);
}

ostream& operator<<(ostream& os, const Agentie& a)
{
	// TODO: insert return statement here
	os << "Nr total oferte: " << a.nrOferte << endl;
	os << "Nr total tari: " << a.nrTari << endl;
	if (a.oferte.size()) {
		for (int i = 0; i < a.oferte.size(); i++) {
			cout << a.oferte.at(i);
		}
	}
	return os;
}