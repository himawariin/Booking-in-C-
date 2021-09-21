#pragma once
#include<string>
using namespace std;

class Oferta
{
    string tara, oras;
    int cod, pret, locuri_disponibile, nr_nopti;
    string data_inceput, data_sfarsit, hotel;
public:
    Oferta() {}
    Oferta(string Tara, string Oras, int Pret, int nopti, string d_inceput, string d_sfarsit, string Hotel, int locuri_disp, int Cod);
    void afisare();
    void init(string Tara, string Oras, int Pret, int nopti, string d_inceput, string d_sfarsit, string Hotel, int locuri_disp, int Cod);
    friend ostream& operator <<(ostream&, const Oferta&);
    friend void rezervare();
    friend void citire_istoric(int&ok, int&i);
    friend void citire_istoric_rez_anulate(int& ok);
    friend void anulare();
    string get_tara();
    string get_di();
    string get_ds();
};