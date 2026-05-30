/*
 * main.cpp
 *
 *  Created on: 6 nov 2025
 *      Author: samad
 */


#include "Fahrzeug.h"
#include <iostream>
#include <memory>//smart Pointers
#include <vector>
#include "PKW.h"
#include "Fahrrad.h"
#include <cmath>
#include <iomanip>
#include <algorithm>

double dGlobaleZeit = 0.0;
double dEpsilon = 0.001;
using namespace std;

//Aus E-test

void vAufgabe_AB1()
{

    int l = 0; // Laufindex für gezielte AUsgabe
    vector<int> ausgabe{13};
    double dTakt = 0.4;

    std::vector<unique_ptr<Fahrzeug>> vecFahrzeuge;
    vecFahrzeuge.push_back(make_unique <PKW>("Audi", 217, 10.7));
    vecFahrzeuge.push_back(make_unique <Fahrrad>("BMX", 21.4));
    for (dGlobaleZeit = 0; dGlobaleZeit < 6; dGlobaleZeit += dTakt)
    {
        auto itL = find(ausgabe.begin(), ausgabe.end(), l);
        if (itL != ausgabe.end()) {
            std::cout << std::endl << l <<  " Globalezeit = " << dGlobaleZeit << std::endl;
            Fahrzeug::vKopf();
        }

        for (int i = 0; i < (int) vecFahrzeuge.size(); i++)
        {
            vecFahrzeuge[i]->vSimulieren();
            if (fabs(dGlobaleZeit - 3.0) < dTakt/2)
            {
                vecFahrzeuge[i]->dTanken();
            }
            if (itL != ausgabe.end()) {
                std::cout << *vecFahrzeuge[i] << endl;
            }
        }
        l++;
    }
    char c;
    std::cin >> c;
}

void vAufgabe1() {

    //Statische Objekte

    Fahrzeug f1("Stat1");
    Fahrzeug f2("Stat2");

    //Dinamische Objekte

    Fahrzeug* pf3 = new Fahrzeug("Dyn1");
    Fahrzeug* pf4 = new Fahrzeug("Dyn2");

    //Dynamische Objekte entfernen

    delete pf3;
    delete pf4;

    // unique_ptr:erzeugt 2 Objekte vom Typ Fahrzeug und speicher die Adresse in Smartpointer u1 und u2

    auto u1 = std::make_unique<Fahrzeug>("Uniq1");
    auto u2 = std::make_unique<Fahrzeug>("Uniq2");
    std::cout << "u1 gultig vor move? " << (u1 ? "ja" : "nein") << std::endl;//Gultig = zeigt der Smartpointer auf einem Objekt?
    auto u3 = std::move(u1); //u1 ist jetzt leer und u3 hat ownership
    std::cout << "u1 gultig nach move? " << (u1 ? "ja" : "nein") << std::endl;

    // shared_ptr: mehrfach ownership

    auto s1 = std::make_shared<Fahrzeug>("Shrd1");
    auto s2 = std::make_shared<Fahrzeug>("Shrd2");
    std::cout << "use_count ohne s3 ownership: " << s1.use_count() << std::endl;//output 1
    std::shared_ptr<Fahrzeug> s3 = s1; //erzeuge ein neuen shared_ptr di auf dem gleichen Objekt von s1 zeigt
    std::cout << "s1 use_count mit s3 ownership: " << s1.use_count() << " s3 use_count mit s3 ownership: " << s3.use_count() << std::endl;//output 2

    // Vector mit typ unique_ptr

    std::vector<std::unique_ptr<Fahrzeug>> vU;//Man kann im Vektor nur Objekte von Typ unique_ptr speichern
    vU.push_back(std::move(u1));//erzeugt ein Objekt im Vektor der mit u1 initialisiert ist, u1 wird null ptr
    vU.push_back(std::move(u2));
    vU.push_back(std::move(u3));
    std::cout << "Anzahl Elemente im Vektor vor clear: " << vU.size() << std::endl;
    vU.clear(); //Objekte im Vektor werden entfernt
    std::cout << "Anzahl Elemente im Vektor nach clear: " << vU.size() << std::endl;

    // Vector shared_ptr

    std::vector<std::shared_ptr<Fahrzeug>> vS;
    std::cout << "Anzahl Referenzen auf s1 vor push_back(s1): " << s1.use_count() << std::endl;// output ist 2
    vS.push_back(s1);          // wegen Eigenschaft von shared_ptr hier wird eine Kopie des Ppinter im Vektor gespeichert ->use_count() wird inkrementiert
    std::cout << "Anzahl Referenzen auf s1 nach push_back(s1): " << s1.use_count() << std::endl;// output ist 3 wegen die kopie des Ppointer s1
    vS.push_back(std::move(s2)); //Pointer wird im Vektor verschoben -> use_count() wird nicht inkrementiert, s2 wird null
    std::cout << "Anzahl Elemente im Vektor: " << vS.size() << std::endl;// Output 2
    std::cout << "Anzahl Referenzen auf s1 nach auffullen von Vektor: " << s1.use_count() << std::endl;// output ist 3, s1,s3 und die copie von s1 aus zeile 106
    vS.clear(); // entfernt die shared_ptr innerhalb des Vectors,aber objekt bleibt solange es noch andere shared_ptr gibt
    std::cout << "Anzahl Referenzen auf s1 nach clear(): " << s1.use_count() << std::endl;//output ist 2 weil s1 noch von ausserhalb des Vektors existiert mit s3
}

void vAufgabe1a()
{


    std::cout << "Name und Maximal Geschw. fur 3 Fahrzeuge eingeben:\n";

    //unique_ptr Fahrzeug Vektor erzeugen

    std::vector<std::unique_ptr<Fahrzeug>> vFahrzeuge;

    for (int i = 0; i < 3; ++i)
    {
        std::string sName;
        double dMaxGeschwindigkeit;

        //Input von Daten

        std::cout << "Fahrzeug " << (i+1) << " (Name): ";
        std::cin >> sName;
        std::cout << "Fahrzeug  " << (i+1) << " (Maximale Geschwindigkeit): ";
        std::cin >> dMaxGeschwindigkeit;

        //Erzeuge Fahrzeug mit Smartpointer und setze das im Vektor

        vFahrzeuge.push_back(std::make_unique<Fahrzeug>(sName, dMaxGeschwindigkeit));
    }


    double dSimulationsdauer = 5.0; //Totale Dauer der Simulation
    double dTakt = 1.0;             //Zeittakt in Stunden

    Fahrzeug::vKopf();

    // Simulazione temporale

    while (dGlobaleZeit < dSimulationsdauer)
    {
        dGlobaleZeit += dTakt;

        //Simulation jeder Fahrzeug mit entsprechenden Output

        for (auto& pFahrzeug : vFahrzeuge)
        {
            pFahrzeug->vSimulieren();

            //Rufe die Funktion operator <<

            std::cout << *pFahrzeug << std::endl;
        }
        std::cout << "-------------------------------------\n";
    }
}

void vAufgabe2()
{
    int nPKW, nFahrrad;
    std::cout << "Anzahl PKW: ";
    std::cin >> nPKW;
    std::cout << "Anzahl Fahrrad: ";
    std::cin >> nFahrrad;

    std::vector<std::unique_ptr<Fahrzeug>> fahrzeuge;

    for (int i = 0; i < nPKW; ++i)
    {
        std::string name;
        double vmax, verbrauch, tankvolumen;
        std::cout << "PKW " << i+1 << " (Name, max-Geschw, Verbrauch,Tankvolumen): ";
        std::cin >> name >> vmax >> verbrauch >> tankvolumen;
        fahrzeuge.push_back(std::make_unique<PKW>(name, vmax, verbrauch, tankvolumen));
    }

    for (int i = 0; i < nFahrrad; ++i) {
        std::string name;
        double vmax;
        std::cout << "Fahrrad " << i+1 << " (nome, vmax): ";
        std::cin >> name >> vmax;
        fahrzeuge.push_back(std::make_unique<Fahrrad>(name, vmax));
    }
    double dTakt = 1.0;
    double dSimEnde = 5.0;
    Fahrzeug::vKopf();

    while (dGlobaleZeit < dSimEnde)
    {
        dGlobaleZeit += dTakt;
        for (auto& f : fahrzeuge)
        {
            f->vSimulieren();

            //Rufe die Funktion operator <<

            std::cout << *f << std::endl;
            std::cout << std::endl;
        }
        std::cout << "-----" << std::endl;

        //Kontrolliere ob die differenz zwischen globale zeit und 3 kleiner als 0.00000001 ist. if wird durchgefuhrt wenn globalezeit praktisch gleich 3 ist

        if (std::fabs(dGlobaleZeit - 3.0) < 1e-8)
        {
            for (auto& f : fahrzeuge)
            {
            	//Nehme Objekt aus dem Vektor aus und kontrolliere ob das pkw ist. Wenn das ein Fahrrad ist dann wird das pkw_ptr null sein

                auto pkw_ptr = dynamic_cast<PKW*>(f.get());
                if (pkw_ptr) pkw_ptr->dTanken();
            }
            std::cout << "---- Alle PKW sind getankt ----" << std::endl;
        }
    }
}

void vAufgabe3()
{

    PKW p1("BMW", 180, 7.5);
    PKW p2("Audi", 200, 8.0);
    Fahrrad f1("Dahon", 30);

    Fahrzeug::vKopf();

    //Simulieren

    dGlobaleZeit += 1.0;
    p1.vSimulieren();
    p2.vSimulieren();
    f1.vSimulieren();

    //Output

    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    std::cout << f1 << std::endl;

//hier wird funktion bool Fahrzeug::operator<(const Fahrzeug& other) const aufgerufen
    if (p1 < p2)
    {
        std::cout << p1.getName() << " hat weniger Gesamtstrecke als " << p2.getName() << std::endl;
    }
    else
    {
        std::cout << p2.getName() << " hat weniger Gesamtstrecke als " << p1.getName() << std::endl;
    }
}
int main()
{
	vAufgabe6();
	    return 0;
}

