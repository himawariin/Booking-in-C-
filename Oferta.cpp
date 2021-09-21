#include "Oferta.h"
#include<iostream>
using namespace std;
#pragma warning(disable : 4996)

Oferta::Oferta(string Tara, string Oras, int Pret, int nopti, string d_inceput, string d_sfarsit, string Hotel, int locuri_disp, int Cod)
	:tara(Tara), oras(Oras), pret(Pret),
	nr_nopti(nopti), data_inceput(d_inceput), data_sfarsit(d_sfarsit),
	hotel(Hotel), cod(Cod), locuri_disponibile(locuri_disp) {}

void Oferta::afisare() {
	cout << "Oras: " << oras << endl;
	cout << "Pret: " << pret << endl;
	cout << "Numar de nopti: " << nr_nopti << ", de la " << data_inceput << " pana la " << data_sfarsit << endl;
	cout << "Hotel: " << hotel << endl;
	cout << "Codul acestei oferte este " << cod << endl;
	cout << "Numarul de locuri disponibile: " << locuri_disponibile << endl;
}

ostream& operator <<(ostream& st, const Oferta& o) {
	st << "Tara: " << o.tara << endl;
	st << "Oras: " << o.oras << endl;
	st << "Pret: " << o.pret << endl;
	st << "Numar de nopti: " << o.nr_nopti << ", de la " << o.data_inceput << " pana la " << o.data_sfarsit << endl;
	st << "Hotel: " << o.hotel << endl;
	st << "Codul acestei oferte este " << o.cod << endl;
	st << "Numarul de locuri disponibile: " << o.locuri_disponibile << endl;
	return st;
}

string Oferta::get_tara() {
	return tara;
}

string Oferta::get_di()
{
	return data_inceput;
}
string Oferta::get_ds()
{
	return data_sfarsit;
}

void Oferta::init(string Tara, string Oras, int Pret, int nopti, string d_inceput, string d_sfarsit, string Hotel, int locuri_disp, int Cod) {
	tara = Tara; oras = Oras; pret = Pret;
	nr_nopti = nopti; data_inceput = d_inceput; data_sfarsit = d_sfarsit;
	hotel = Hotel; locuri_disponibile = locuri_disp; cod = Cod;
}