/*
 * Fahrzeug.cpp
 *
 *  Created on: 23 ott 2025
 *      Author: samad
 *      File zur Definition des Codes
 */

#include "Fahrzeug.h"
#include <iostream>
#include <iomanip>// Fur setw()


int Fahrzeug::p_iMaxId = 0;   // Initialisierung static Variabel

// Default Konstruktor

Fahrzeug::Fahrzeug()
    : p_sName(""), p_iId(++p_iMaxId), p_dMaxGeschwindigkeit(0), p_dGesamtStrecke(0), p_dGesamtZeit(0), p_dZeit(dGlobaleZeit) // Initialisierungsliste
{
    std::cout << "Konstruktor (default): Name=\"" << p_sName
              << "\", ID=" << p_iId << std::endl;
}

// Konstruktor mit Parameter

Fahrzeug::Fahrzeug(const std::string& name)
    : p_sName(name), p_iId(++p_iMaxId), p_dMaxGeschwindigkeit(0), p_dGesamtStrecke(0), p_dGesamtZeit(0), p_dZeit(dGlobaleZeit)
{
    std::cout << "Konstruktor (param): Name=\"" << p_sName
              << "\", ID=" << p_iId << std::endl;
}

//Konstruktor mit Name und maximale Geschwindigkeit als Parameter

Fahrzeug::Fahrzeug(std::string p_sName, double p_dMaxGeschwindigkeit)
    :p_sName(p_sName), p_iId(++p_iMaxId), p_dMaxGeschwindigkeit(p_dMaxGeschwindigkeit > 0 ? p_dMaxGeschwindigkeit : 0), p_dGesamtStrecke(0), p_dGesamtZeit(0), p_dZeit(dGlobaleZeit)
{
	std::cout << "Konstruktor (param): Name=\"" << p_sName
	          << "\" Maximal Geschwindigkeit: " << p_dMaxGeschwindigkeit
	          << ", ID=" << p_iId << std::endl;
}

// Destruktor

Fahrzeug::~Fahrzeug()
{
    std::cout << "Destruktor: Name=\"" << p_sName
              << "\", ID=" << p_iId << std::endl;
}

void Fahrzeug::vKopf()
{
	//Default rechts-Ausrichtung ausschalten und Links-Ausrichtung einschalten

    std::cout << std::resetiosflags(std::ios::right) << std::setiosflags(std::ios::left)
              << std::setw(5)  << "ID"
              << std::setw(10) << "Name"
              << std::setw(20) << "MaxGeschwindigkeit"
              << std::setw(20) << "Geschwindigkeit"
              << std::setw(15) << "Gesamtstrecke"
              << std::setw(12) << "Verbrauch"
              << std::setw(15) << "Tankvolumen"
              << std::setw(12) << "Tankinhalt"
              << std::endl;
    std::cout << "---------------------------------------------------------------------------------------------------------" << std::endl;

    //Links-Ausrichtung zurücksetzen, damit zukünftiger Output nicht beeinflusst wird

    std::cout << std::resetiosflags(std::ios::left);
}

//Output Funktion

void Fahrzeug::vAusgeben(std::ostream& o) const
{
    o << std::resetiosflags(std::ios::right) << std::setiosflags(std::ios::left)
      << std::setw(5)  << p_iId
      << std::setw(10) << p_sName
      << std::setw(20) << std::fixed << std::setprecision(2) << p_dMaxGeschwindigkeit
      << std::setw(20) << std::fixed << std::setprecision(2) << dGeschwindigkeit()
      << std::setw(15) << std::fixed << std::setprecision(2) << p_dGesamtStrecke;
    o << std::resetiosflags(std::ios::left);
}

//Definition der Funktion vSimulieren()


void Fahrzeug::vSimulieren()
{
    double dZeitDiff = dGlobaleZeit - p_dZeit;

    //Kontrolliere ob zeit vergangen ist seit die letzte Simulation

    if (dZeitDiff > 0.0)
    {
    	//Variablen gemäß der Simulation aktualisieren

        double aktuelleGeschwindigkeit = dGeschwindigkeit();
        p_dGesamtStrecke += aktuelleGeschwindigkeit * dZeitDiff;
        p_dGesamtZeit += dZeitDiff;
        p_dZeit = dGlobaleZeit;
    }
}

double Fahrzeug::dTanken(double menge)
{
       return 0.0;
}

double Fahrzeug::dGeschwindigkeit() const
{
    return p_dMaxGeschwindigkeit;
}

bool Fahrzeug::operator<(const Fahrzeug& other) const
{
    return p_dGesamtStrecke < other.p_dGesamtStrecke;
}

//Funktion die die Stammdaten eines Objekt in einen anderen kopiert

Fahrzeug& Fahrzeug::operator=(const Fahrzeug& other)
{
	// kontrolliere ob Objekte nicht das gleiche sind

    if (this != &other)
    {
        this->p_sName = other.p_sName;
        this->p_dMaxGeschwindigkeit = other.p_dMaxGeschwindigkeit;
    }
    return *this;
}


;

std::ostream& operator<<(std::ostream& o, const Fahrzeug& f)
{
    f.vAusgeben(o);
    return o;
}




