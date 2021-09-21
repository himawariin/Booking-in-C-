#pragma once
#include"Oferta.h"
#include<vector>
#include<iostream>

class Agentie
{
	int logareCont;
	vector<Oferta> oferte;
	int nrTari, nrOferte;
	vector<string>tari;

public:
	Agentie(int = 0, int = 0);
	friend void inregistrareCont();
	friend void delogare();
	friend void rezervare();
	friend void anulare();
	friend void istoric();
	friend void citire_istoric(int&ok,int&i);
	friend void citire_istoric_rez_anulate(int& ok);
	void setTara(const string& s);
	void setOferta(Oferta& o);
	friend void afisare();
	friend void cautare();
	friend ostream& operator<<(ostream&, const Agentie&);
	//static int logareCont;

};