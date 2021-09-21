#include<iostream>
#include"Oferta.h"
#include"Agentie.h"
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;
#pragma warning(disable : 4996)

//variabilele globale din cadrul programului
Agentie a;   //un obiect de tip agentie
string mail;  //mail-ul care corespunde user-ului care este logat in cont

void afisare() {
    system("cls");
    cout << "\t\t\t\t\t\tOferte disponibile - Let's travel!" << endl<<endl;
    cout << "\t\t\t\t\t\t1. Afisare oferte." << endl;
    cout << "\t\t\t\t\t\t2. Afisare oferte in functie de tara. In total oferim sejururi in " << a.tari.size() << " tari." << endl<<endl;
    cout << "\t\t\t\t\t\tAlegeti optiunea: ";

    int optiune; cin >> optiune; cout << endl;
    if (optiune == 1) {
        //Oferta o - trebe sa zic tipul elementelor(Oferta) -> "o" o sa fie pe rand fiecare element din vectorul :oferte
        for (Oferta const& o : a.oferte) {
            cout << o << endl;   //afisez folosind supraincarcarea operatorului
        }
    }
    else {
        for (string const& tara : a.tari) {
            cout << "\t\t\t\t\t\tTARA: " << tara << " ---" << endl << endl;
            for (Oferta o : a.oferte) {
                // string1.compare(string2) -> 0 daca sunt identice stringurile
                if (!tara.compare(o.get_tara())) {
                    o.afisare(); //afisez folosind functie
                    // n am mai folosit supraincarcarea ptc imi afisa si Tara: si nu voiam sa se repete
                    cout << endl;
                }
            }
        }
    }
    system("pause");
}

void corect(char* s)
{
    if (s[0] >= 'a' && s[0] <= 'z')
        s[0] = s[0] - 'a' + 'A';
    for (int i = 1; i < strlen(s); i++)
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] = s[i] + 'a' - 'A';
}

void cautare()
{
    system("cls");
    cout << "\t\t\t\t\t\tCAUTARE" << endl<<endl;
    int ok1 = 0, ok2 = 0;// ok1 o sa fie 1 daca  vrea filtru dupa locatie, ok2 daca vrea filtru dupa perioada
    cout << "\t\t\t\t\t\tDaca doresti sa filtrezi ofertele in functie de locatie, APASATI 1, altfel APASATI 0." << '\n';
    int x;
    cin >> x;
    cin.ignore();
    if (x == 1)
        ok1 = 1;

    cout << "\t\t\t\t\t\tDaca doresti sa filtrezi ofertele vazute in functie de perioada, APASATI 1, altfel APASATI 0." << '\n';
    cin >> x;
    cin.ignore();
    if (x == 1)
        ok2 = 1;
    cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << '\n';
    int z = 0;// ca sa  se incrementeze  cand se printeaza oferte, sa stiu daca dupa criteriile utilizatorului s-au gasit sau nu oferte
    //daca z=0  dupa if-uri inseamna ca nu s a agsit vreo oferte pt el
    if (ok1 == 0 && ok2 == 0)// daca nu doreste in functie de tara sau de perioada se afiseaza toate ofertele
    {
        for (string const& tara : a.tari)
        {
            cout << "	---Tara: " << tara << " ---" << endl << endl;
            for (Oferta o : a.oferte)
            {
                // string1.compare(string2) -> 0 daca sunt identice stringurile
                if (!tara.compare(o.get_tara()))
                {
                    o.afisare(); //afisez folosind functie
                    // n am mai folosit supraincarcarea ptc imi afisa si Tara: si nu voiam sa se repete
                    cout << endl;
                    z = 1;
                }
            }
        }
    }
    else
        if (ok1 == 1 && ok2 == 0)//daca vrea in functie de tara
        {
            cout << "Alegeti tara in care doriti sejurul." << '\n';
            cout << "Tara cautata: ";
            char sir[40];
            cin >> sir;
            cin.ignore();
            corect(sir);//folosesc functia in care transform ceva gen FrAnTa in Franta
            cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << '\n';
            for (Oferta o : a.oferte)
            {
                char c[40];
                strcpy(c, o.get_tara().c_str());//am pus stringul care reprezinta tara intr-un char
                if (strcmp(sir, c) == 0)//vad daca tara din oferta e la fel ca tara ceruta de utilizator
                {
                    o.afisare();
                    cout << endl;
                    z = 1;// am afisat ceva deci   pot sa il intreb pe utilizator daca doreste sa  rezerve ceva
                            // sau daca z=0 la sfarsit, stiu  sa mi cer scuze ca nu a gasit nimic
                }
            }
        }
        else if (ok1 == 0 && ok2 == 1)// daca am filtru de perioada
        {
            char ciu[40], csu[40];// char-urile pentru data de inceput si data de sfarsit cerute de utilizator
            // c-char  i-inceput  u- utilizator  deci ciu este char-ul primit de la utilizator pentru data de inceput
            //analog pentru csu(data de sfarsit de la utilizator) cio(data de inceput din oferta), cso(data de sfarsit din oferta)
            cout << "Alegeti perioada minima in care doriti sejurul." << '\n';
            cin >> ciu;
            cin.ignore();
            cout << "Alegeti perioada maxima in care doriti sejurul." << '\n';
            cin >> csu;
            cin.ignore();
            char* piu, * psu;// fiecare pointer pentru a folosii strtok ul pe char-uri, le despart prin . 
            piu = strtok(ciu, ".");
            int viu[4], vsu[4]; // pun in vectori  numerele care reprezinta datele din perioade, ca sa le pot compara
            int i = 0;
            while (piu != NULL)// in acest while  pun in vectorul de numere datele din perioade
            {
                int n = 0;
                for (int j = 0; j < strlen(piu); j++)
                    n = n * 10 + piu[j] - '0';
                viu[i] = n;
                i++;
                piu = strtok(NULL, ".");
            }
            i = 0;
            psu = strtok(csu, ".");
            while (psu != NULL)
            {
                int n = 0;
                for (int j = 0; j < strlen(psu); j++)
                    n = n * 10 + psu[j] - '0';
                vsu[i] = n;
                i++;
                psu = strtok(NULL, ".");
            }

            cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << '\n';
            for (string const& tara : a.tari)
            {
                for (Oferta o : a.oferte)
                    if (!tara.compare(o.get_tara()))
                    {// pentru fiecare  oferta pe care o am in fisier,compar cu perioadele pe care le am primit de la utilizator
                        char cio[40], cso[40];
                        char* pio, * pso;
                        int vio[4], vso[4];
                        strcpy(cio, o.get_di().c_str());
                        strcpy(cso, o.get_ds().c_str());
                        i = 0;
                        pio = strtok(cio, ".");
                        while (pio != NULL)
                        {
                            int n = 0;
                            for (int j = 0; j < strlen(pio); j++)
                                n = n * 10 + pio[j] - '0';
                            vio[i] = n;
                            i++;
                            pio = strtok(NULL, ".");
                        }
                        i = 0;
                        pso = strtok(cso, ".");
                        while (pso != NULL)
                        {
                            int n = 0;
                            for (int j = 0; j < strlen(pso); j++)
                                n = n * 10 + pso[j] - '0';
                            vso[i] = n;
                            i++;
                            pso = strtok(NULL, ".");
                        }
                        int da1 = 0;
                        if (viu[2] < vio[2])// data de la utilizator  de inceput trebuie sa fie <= decat data de la oferta ca sa fie valabil
                            da1 = 1;
                        else if (viu[2] == vio[2])
                        {
                            if (viu[1] < vio[1])
                                da1 = 1;
                            else if (viu[1] == vio[1])
                            {
                                if (viu[0] <= vio[0])
                                    da1 = 1;
                            }
                        }
                        int da2 = 0;
                        if (vsu[2] > vso[2])// data de la utilizator de sfarsit trebuie sa fie >=  decat data din oferta ca sa fie valabila
                            da2 = 1;
                        else if (vsu[2] == vso[2])
                        {
                            if (vsu[1] > vso[1])
                                da2 = 1;
                            else if (vsu[1] == vso[1])
                            {
                                if (vsu[0] >= vso[0])
                                    da2 = 1;
                            }
                        }
                        //daca am in oferta 10.05.2020- 15.05.2020
                        //daca utilizatorul cere 01.05.2020-15.05.2020  deci e buna perioada, afiseaza oferta
                        //daca utilizatorul cere 10.05.2020-15.05.2020 deci e buna, afiseaza oferta
                        // daca utilizatorul cere  10.05.2020-14.05.2020 deci nu e buna, ca nu corespunde data de sfarsit
                                //utilizatorul cere ca vrea ceva pana pe 14 mai dar, oferta e pana pe 15
                        if (da1 == 1 && da2 == 1)//daca si data de inceput si data de sfarsit de la utilizator sunt bine, am oferte
                            //care corespund
                        {
                            cout << "	---Tara: " << tara << " ---" << endl << endl;
                            o.afisare();
                            z = 1;
                            cout << endl;
                        }
                    }
            }
        }
        else if (ok1 == 1 && ok2 == 1)//daca imi cere si tara si perioada fac ce am, facut la ultimele 2 functii dar le combin
        {
            cout << "Alegeti tara in care doriti sejurul." << '\n';
            cout << "Tara cautata: ";
            char sir[40];
            cin >> sir;
            cin.ignore();
            corect(sir);
            char ciu[40], csu[40];
            cout << "Alegeti perioada minima in care doriti sejurul." << '\n';
            cin >> ciu;
            cin.ignore();
            cout << "Alegeti perioada maxima in care doriti sejurul." << '\n';
            cin >> csu;
            cin.ignore();
            char* piu, * psu;
            piu = strtok(ciu, ".");
            int viu[4], vsu[4];
            int i = 0;
            while (piu != NULL)
            {
                int n = 0;
                for (int j = 0; j < strlen(piu); j++)
                    n = n * 10 + piu[j] - '0';
                viu[i] = n;
                i++;
                piu = strtok(NULL, ".");
            }
            i = 0;
            psu = strtok(csu, ".");
            while (psu != NULL)
            {
                int n = 0;
                for (int j = 0; j < strlen(psu); j++)
                    n = n * 10 + psu[j] - '0';
                vsu[i] = n;
                i++;
                psu = strtok(NULL, ".");
            }

            cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << '\n';
            for (string const& tara : a.tari)
            {
                for (Oferta o : a.oferte)
                    if (!tara.compare(o.get_tara()))
                    {
                        char cio[40], cso[40];
                        char* pio, * pso;
                        int vio[4], vso[4];
                        strcpy(cio, o.get_di().c_str());
                        strcpy(cso, o.get_ds().c_str());
                        i = 0;
                        pio = strtok(cio, ".");
                        while (pio != NULL)
                        {
                            int n = 0;
                            for (int j = 0; j < strlen(pio); j++)
                                n = n * 10 + pio[j] - '0';
                            vio[i] = n;
                            i++;
                            pio = strtok(NULL, ".");
                        }
                        i = 0;
                        pso = strtok(cso, ".");
                        while (pso != NULL)
                        {
                            int n = 0;
                            for (int j = 0; j < strlen(pso); j++)
                                n = n * 10 + pso[j] - '0';
                            vso[i] = n;
                            i++;
                            pso = strtok(NULL, ".");
                        }
                        int da1 = 0;
                        if (viu[2] < vio[2])
                            da1 = 1;
                        else if (viu[2] == vio[2])
                        {
                            if (viu[1] < vio[1])
                                da1 = 1;
                            else if (viu[1] == vio[1])
                            {
                                if (viu[0] <= vio[0])
                                    da1 = 1;
                            }
                        }
                        int da2 = 0;
                        if (vsu[2] > vso[2])
                            da2 = 1;
                        else if (vsu[2] == vso[2])
                        {
                            if (vsu[1] > vso[1])
                                da2 = 1;
                            else if (vsu[1] == vso[1])
                            {
                                if (vsu[0] >= vso[0])
                                    da2 = 1;
                            }
                        }
                        char* c = new char[o.get_tara().length() + 1];
                        strcpy(c, o.get_tara().c_str());
                        if (strcmp(sir, c) == 0 && da1 == 1 && da2 == 1)
                        {
                            o.afisare();
                            cout << endl;
                            z = 1;
                        }


                    }
            }

        }
    if (z == 0)
    {
        cout << "Ne pare rau ca nu ati gasit nicio oferta. Puteti cauta iar APASAND 1." << '\n';
        int q;
        cin >> q;
        cin.ignore();
        if (q == 1)
            cautare();
    }

        cout << " Daca doresti sa cauti alta oferta APASATI 1." << '\n';
        int b;
        cin >> b;
        cin.ignore();
        if (b == 1)
            cautare();
}

bool  verificareCont(const string& mail1) {
    fstream c;
    c.open("cont.txt", ios::in);
    string m, t, p;
    while (!c.eof())
    {
        c >> m >> t >> p;
        if (!c.eof()) {
            if (!m.compare(mail1))
                return false;
        }
    }
    c.close();
    return true;
}

void creareCont() {
    system("cls");
    string mail1, tel, par;
    cout << "\t\t\t\t\t\tNe bucuram ca vreti sa fiti mai aproape de servicile noastre! LET'S TRAVEL" << endl << endl;
    cout << "\t\t\t\t\t\tPentru a crea un cont va rugam sa introduceti urmatoarele date: " << endl;
    cout << "\t\t\t\t\t\tE-mail: "; cin >> mail1;
    cout << "\n\t\t\t\t\t\tNumar de telefon: "; cin >> tel;
    cout << "\n\t\t\t\t\t\tParola: "; cin >> par;
    if (!verificareCont(mail1))
    {
        cout << "\n\t\t\t\t\t\tDeja exista un cont cu acest email. Va rugam incercati cu alta adresa.\n\n\t\t\t\t\t\t";
        system("pause");
        return;
    }
    fstream c;
    c.open("cont.txt", ios::app);
    if (c.is_open()) {
        c << mail1 << " " << tel << " " << par << endl;
    }
    c.close();
    fstream is;
    is.open("istoric.txt", ios::app);
    is << mail1 << endl;
    is << '*' << endl;
    is.close();
    cout << "\t\t\t\t\t\tMultumim! Contul dvs a fost creat cu succes!\n\t\t\t\t\t\t" << endl;
    system("pause");
}

bool verificareInr(const string& mail, const string& parola) {
    ifstream c;
    c.open("cont.txt");
    string m, t, p;

    while (!c.eof()) {
        c >> m >> t >> p;
        if (!c.eof()) {
            if (!m.compare(mail) && !p.compare(parola))
                return true;
        }
    }
    c.close();
    return false;
}

void inregistrareCont() {
    system("cls");
    cout << "\t\t\t\t\t\tWELCOME BACK, NOW LET'S TRAVEL!" << endl << endl;
    cout << "\t\t\t\t\t\tVa rugam sa va inregistrati in cont introducand urmatoarele informatii: " << endl<<endl;
    string parola;
    cout << "\t\t\t\t\t\tE-mail: "; cin >> mail;
    cout << "\n\t\t\t\t\t\tParola: "; cin >> parola;

    if (!verificareInr(mail, parola)) {
        cout << "\n\n\t\t\t\t\t\tDatele nu coincid cu baza noastra de date! Va rugam incercati din nou:)"<<endl;
        system("pause");
        return;
    }
    cout << "\n\t\t\t\t\t\tAti intrat in cont. Acum puteti efectua/anula/vizualiza rezervari" << endl<<endl;
    //Agentie::logareCont += 1;
    a.logareCont = 1;
    system("pause");
}

void delogare() {
    if (a.logareCont) {
        a.logareCont = 0;
        cout << "\n\t\t\tV-ati delogat. Speram ca v-a placut experienta si va asteptam din nou pe la noi!" << endl;
    }
    else {
        cout << "Trebuie sa fiti mai intai logat pentru a va putea deloga." << endl;
    }
    system("pause");
}
void modificare_oferta(int nr_oferta, int nr_locuri)
{
    fstream of;
    of.open("oferte.txt");
    ofstream aux;
    aux.open("auxiliar.txt");
    string line;
    getline(of, line);
    aux << line << endl;
    int i = 0;
    while (!of.eof())
    {
        i++;
        if (i == nr_oferta)
        {
            string tara, oras, di, ds, h;
            int pret, nopti, locuri;
            of >> tara >> oras >> pret >> nopti >> di >> ds >> h >> locuri;
            locuri -= nr_locuri;
            aux << tara << " " << oras << " " << pret << " " << nopti << " " << di << " " << ds << " " << h << " " << locuri;
        }
        else
        {
            getline(of, line);
            aux << line << endl;
        }
    }
    aux.close();
    of.close();
    char filename1[] = "oferte.txt";
    char filename2[] = "auxiliar.txt";
    if (remove(filename1) != 0)
        perror("File deletion failed");
    else
        cout << "File deleted successfully";

    if (rename(filename2, filename1) != 0)
        perror("Error renaming file");
    else
        cout << "File renamed successfully";
}

void update_istoric(int nr_oferta, int nr_locuri) //numarul ofertei care a fost rezervata + numarul de locuri pt care a fost facuta rezervarea
{
    ifstream is; //deschidem fisierul de istoric din care o sa copiam toate datele
    is.open("istoric.txt");
    ofstream aux; //ne facem un fisier nou in care copiam tot
    aux.open("auxiliar.txt");
    string ma, nl;
    while (!is.eof())
    {
        getline(is, ma);
        if (!is.eof())
        {
            aux << ma << endl;
            if (!ma.compare(mail))
            {
                getline(is, nl);
                while (nl.compare("*"))
                {
                    aux << nl << endl;
                    getline(is, nl);
                }
                aux << nr_oferta << " " << nr_locuri << " " << "1" << endl;
                aux << "*" << endl;
            }
            else
            {
                getline(is, nl);
                while (nl.compare("*"))
                {
                    aux << nl << endl;
                    getline(is, nl);
                }
                aux << "*" << endl;
            }
        }
    }
    aux.close();
    is.close();
    char filename1[] = "istoric.txt";
    char filename2[] = "auxiliar.txt";
    if (remove(filename1) != 0)
        perror("File deletion failed");
    else
        cout << "File deleted successfully";

    if (rename(filename2, filename1) != 0)
        perror("Error renaming file");
    else
        cout << "File renamed successfully";
}

void rezervare() {
    system("cls");
    cout << "\t\t\t\t\t\tAbia asteptam sa rezervi o oferta - LET'S TRAVEL" << endl<<endl;

    //aceasta variabila verifica daca un user este logat in cont sau nu
    if (a.logareCont) {
        cout << "Introduceti codul ofertei pe care doriti sa o rezervati: ";
        int nr;
        cin >> nr;

        if (nr<1 || nr>a.nrOferte) //verificam daca a introdus un cod corect sau nu
        {
            cout << "\nNe pare rau, dar codul ofertei este inexistent." << '\n';
            system("pause");
            return;
        }
        cout << "\nConfirmati ca aceasta este oferta dorita.\n";
        cout << a.oferte[nr - 1]; //afisam oferta
        cout <<"\n\nIntroduceti tasta 1 daca aceasta este oferta dorita,0 in caz contrar: ";
        int conf;
        cin >> conf;

        if (conf == 0)
        {
            cout << "\nPuteti incerca din nou, introducand alt cod." << '\n';
            system("pause");
            return;// il va intoarce la meniu
        }
        cout << "\nCate locuri doriti sa rezervati? ";
        cin >> conf;
        if (conf > a.oferte[nr - 1].locuri_disponibile)  //verificam daca sunt destule locuri disponibile
        {
            cout << "\nNu sunt destule locuri disponibile." << '\n';
            system("pause");
            return;
        }
        //update la locuri disponibile si in clasa
        a.oferte[nr - 1].locuri_disponibile -= conf;
        //adaugam rezervarea la sfarsitul fisierului
        fstream r;
        r.open("rezervare.txt", ios::app);
        if (r.is_open()) {
            r << nr << " " << mail << " " << conf << endl;
        }
        r.close();
        cout << "\nRezervarea a fost efectuata cu succes!" << '\n';
        system("pause");

        update_istoric(nr, conf); //rezervarea trebuie adaugata si in istoric
        modificare_oferta(nr, conf); //oferta trebuie modificata in fisier deoarece s-a schimbat nr de pers disponibile 
    }
    else {
        cout << "\t\t\t\t\t\tNu puteti rezerva oferte daca nu sunteti logat. Nu puteti sa va logati daca nu aveti cont." << endl<<"\n\t\t\t\t\t\t";
        system("pause");
    }
}

void citire_istoric(int&ok,int&i) {
    ifstream is;
    is.open("istoric.txt");
    string ma, nl;
    int nr_oferta, nr_locuri, valabil;
    while (!is.eof())
    {
        getline(is, ma);
        if (!is.eof())
        {
            if (!ma.compare(mail))
            {
                getline(is, nl);
                while (nl.compare("*"))
                {
                    stringstream s(nl);
                    s >> nr_oferta >> nr_locuri >> valabil;
                    if (valabil) {
                        cout << "Numarul rezervarii: " << i<<endl;
                        cout << "Nr locuri rezervate: " << nr_locuri << endl;
                        cout << a.oferte[nr_oferta-1]<<endl<<endl;
                        i++;
                        ok = 1;
                    }
                    getline(is, nl);
                }
                break;
            }
            else
            {
                getline(is, nl);
                while (nl.compare("*"))
                {
                    getline(is, nl);
                }
            }
        }
    }
    is.close();
}

void update_istoric_anulare(int&alegere) {
    ifstream is;
    is.open("istoric.txt");
    ofstream aux;
    aux.open("auxiliar.txt");
    string ma, nl;
    int nr_oferta, nr_locuri, valabil, i = 1;
    while (!is.eof())
    {
        getline(is, ma);
        if (!is.eof())
        {
            aux << ma << endl;
            if (!ma.compare(mail))
            {
                getline(is, nl);
                while (nl.compare("*"))
                {
                    stringstream s(nl);
                    s >> nr_oferta >> nr_locuri >> valabil;
                    if (valabil) {
                        if (i == alegere) {
                            aux << nr_oferta <<" "<< nr_locuri <<" "<< 0<<endl;
                        }
                        else {
                            aux << nr_oferta << " " << nr_locuri << " " << 1 << endl;
                        }
                        i++;
                    }
                    else {
                        aux << nr_oferta << " " << nr_locuri << " " << 0 << endl;
                    }
                    getline(is, nl);
                }
                aux << "*"<<endl;
            }
            else
            {
                getline(is, nl);
                while (nl.compare("*"))
                {
                    aux << nl << endl;
                    getline(is, nl);
                }
                aux << "*" << endl;
            }
        }
    }
    aux.close();
    is.close();
    char filename1[] = "istoric.txt";
    char filename2[] = "auxiliar.txt";
    if (remove(filename1) != 0)
        perror("File deletion failed");
    else
        cout << "File deleted successfully";

    if (rename(filename2, filename1) != 0)
        perror("Error renaming file");
    else
        cout << "File renamed successfully";
}

void update_rezervare_anulare(int& alegere, int&COD, int&PERSOANE) {
    ifstream is;
    is.open("rezervare.txt");
    ofstream aux;
    aux.open("auxiliar.txt");
    string ma,nl;
    int nr_oferta, nr_locuri, i = 1;
    while (!is.eof())
    {
        getline(is, nl);
        if (!is.eof())
        {
            stringstream s(nl);
            s >> nr_oferta >> ma >> nr_locuri;
            //cout << nr_oferta << " " << ma << " " << nr_locuri;
            if (!ma.compare(mail))
            {
                if (i != alegere) {
                    aux << nr_oferta << " " << ma << " " << nr_locuri << endl;
                }
                else {
                    COD = nr_oferta;
                    PERSOANE = nr_locuri;
                }
                i++;
            }
            else
            {
                aux << nr_oferta << " " << ma << " " << nr_locuri << endl;
            }
        }
    }
    aux.close();
    is.close();
    char filename1[] = "rezervare.txt";
    char filename2[] = "auxiliar.txt";
    if (remove(filename1) != 0)
        perror("File deletion failed");
    else
        cout << "File deleted successfully";

    if (rename(filename2, filename1) != 0)
        perror("Error renaming file");
    else
        cout << "File renamed successfully";
}

void modificare_oferta_anulare(int&COD, int&PERSOANE) {
    fstream of;
    of.open("oferte.txt");
    ofstream aux;
    aux.open("auxiliar.txt");
    string line;
    getline(of, line);
    aux << line << endl;
    int i = 0;
    while (!of.eof())
    {
        i++;
        if (i == COD)
        {
            string tara, oras, di, ds, h;
            int pret, nopti, locuri;
            of >> tara >> oras >> pret >> nopti >> di >> ds >> h >> locuri;
            locuri += PERSOANE;
            aux << tara << " " << oras << " " << pret << " " << nopti << " " << di << " " << ds << " " << h << " " << locuri;
        }
        else
        {
            getline(of, line);
            aux << line << endl;
        }
    }
    aux.close();
    of.close();
    char filename1[] = "oferte.txt";
    char filename2[] = "auxiliar.txt";
    if (remove(filename1) != 0)
        perror("File deletion failed");
    else
        cout << "File deleted successfully";

    if (rename(filename2, filename1) != 0)
        perror("Error renaming file");
    else
        cout << "File renamed successfully";
}

void anulare()
{
    system("cls");
    cout << "\t\t\t\t\t\tNe pare rau ca ati ajuns in acest punct:(" << endl << endl;
    if (a.logareCont)
    {
        int ok = 0,i=1;
        citire_istoric(ok,i);
        if (ok) {
            int alegere;
            cout << "\tAlegeti numarul rezervarii pe care doriti sa o anulati "; cin >> alegere;
            if (alegere >= 1 && alegere < i) {
                cout << "\nRezervarea dvs a fost anulata!\n" << endl;
                system("pause");
                update_istoric_anulare(alegere);
                int COD, PERSOANE;
                update_rezervare_anulare(alegere, COD, PERSOANE);
                modificare_oferta_anulare(COD,PERSOANE);
                a.oferte[COD - 1].locuri_disponibile += PERSOANE;
            }
            else {
                cout << "\t\t\tCod invalid, incercati din nou"<<endl;
                system("pause");
            }  
        }
        else {
            cout << "Nu aveti nici o rezervare facuta, nu aveti ce sa anulati."<<endl;
            system("pause");
        }
    }
    else
    {
        cout << "Nu puteti anula o rezervare daca nu sunteti logat. Nu puteti sa va logati daca nu aveti cont." << endl;
        system("pause");
    }
}

void citire_istoric_rez_anulate(int&ok) {
    ifstream is;
    is.open("istoric.txt");
    string ma, nl;
    int nr_oferta, nr_locuri, valabil;
    while (!is.eof())
    {
        getline(is, ma);
        if (!is.eof())
        {
            if (!ma.compare(mail))
            {
                getline(is, nl);
                while (nl.compare("*"))
                {
                    stringstream s(nl);
                    s >> nr_oferta >> nr_locuri >> valabil;
                    if (!valabil) {
                        //cout << "Numarul rezervarii: " << i << endl;
                        cout << "Nr locuri rezervate: " << nr_locuri << endl;
                        cout << a.oferte[nr_oferta - 1] << endl;
                        //i++;
                        ok = 1;
                    }
                    getline(is, nl);
                }
                break;
            }
            else
            {
                getline(is, nl);
                while (nl.compare("*"))
                {
                    getline(is, nl);
                }
            }
        }
    }
    is.close();
}

void istoric() {
    system("cls");
    cout << "Aici puteti vizualiza tot ce ati facut in aplicatie pana in acest punct." << endl << endl;
    if (a.logareCont) {
        int ok = 0, i = 1;
        cout << "RERZERVARI VALABILE: " << endl<<endl;
        citire_istoric(ok, i);
        if (!ok) {
            cout << "Nu aveti nici o rezervare valabila." << endl;
        }

        ok = 0;
        cout << "RERZERVARI ANULATE: " << endl<<endl;
        citire_istoric_rez_anulate(ok);
        if (!ok) {
            cout << "Nu ati anulat nici o rezervare pana in acest moment" << endl;
        }
        cout << endl;
        system("pause");

    }
    else {
        cout << "\n\t\t\tNu puteti vizualiza istoricul daca nu sunteti logat. Nu puteti sa va logati daca nu aveti cont." << endl;
        system("pause");
    }
}

void init() {
    fstream fisier;
    fisier.open("oferte.txt", ios::in);
    //primul rand din fisier: 2 2 Spania Franta -> numarul de oferte, numarul de tari, tarile
    //apoi pe fiecare rand este scrisa cate o oferta

    //variabile pe care le folosesc la citirea din fisier
    string t, o, di, ds, h, tara;
    int pr, nopti, pers, n, n_tari;
    int i = 0, j = 0;

    fisier >> n; //citesc numarul de oferte
    fisier >> n_tari; //citesc numarul de tari

    Agentie aux(n, n_tari); //imi creez un obiect de tip agentie
    a = aux; //il copiez in agentia mea a care este variabila globala - sa o pot accesa in toate functiile

    //citesc tarile
    while (j < n_tari) {
        fisier >> tara;
        a.setTara(tara); //adaug tara in vectorul de tari din cadrul agentiei
        j++;
    }

    //citesc fiecare oferta din fisier
    if (fisier.is_open()) {
        while (1) {
            fisier >> t >> o >> pr >> nopti >> di >> ds >> h >> pers;
            if (fisier.eof())
                break;
            Oferta o(t, o, pr, nopti, di, ds, h, pers, i + 1); //creez obiectul pt oferta pe care am citit-o
            i++;
            a.setOferta(o); //adaug oferta in vectorul de oferte din cadrul agentiei
        }
    }
    fisier.close();
}

void legenda(int& n) {
    cout << "\t\t\t\t\t\tMeniu - Let's travel " << endl<<endl<<endl;
    cout << "\t\t\t\t\t\t1) Vizualizare oferte" << endl;
    cout << "\t\t\t\t\t\t2) Cautare oferte" << endl<<endl;
    cout << "\t\t\t\t\t\t3) Rezervare oferta" << endl;
    cout << "\t\t\t\t\t\t4) Anulare rezervare" << endl;
    cout << "\t\t\t\t\t\t5) Vizualizare istoric" << endl<<endl;
    cout << "\t\t\t\t\t\t6) Creare cont" << endl;
    cout << "\t\t\t\t\t\t7) Intra in cont" << endl;
    cout << "\t\t\t\t\t\t8) Iesi din cont" << endl<<endl;
    cout << "\t\t\t\t\t\t0) Inchide aplicatia"<<endl<<endl;
    cout << "\t\t\t\t\t\tAlegerea dumneavoastra: ";
    cin >> n;
}
void meniu()
{
    int n;
    legenda(n);
    while (n != 0)
    {
        if (n == 1) afisare();
        else if (n == 2) cautare();
        else if (n == 3) rezervare();
        else if (n == 4) anulare();
        else if (n == 5) istoric();
        else if (n == 6) creareCont();
        else if (n == 7) inregistrareCont();
        else if (n == 8) delogare();
        else if (n == 0) break;
        else cout << "\n   Nu ati introdus o optiune valida";

        system("cls");
        legenda(n);
    }
}

int main()
{
    init();
    meniu();
}