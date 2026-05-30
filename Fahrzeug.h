/*
 * Fahrzeug.h
 *
 *  Created on: 23 ott 2025
 *      Author: samad
 *      File zu Deklaration der Variablen und Funktionen
 */


#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_
#include <string>
using std::string;
extern double dGlobaleZeit;//Globale Uhr
#include <limits>
#include <ostream>
class Fahrzeug
{
protected:

	//Protected Membervariablen deklarieren

	std::string p_sName;
	const int p_iId;
	static int p_iMaxId;//KlassenVariable
	double p_dMaxGeschwindigkeit;
	double p_dGesamtStrecke;
	double p_dGesamtZeit;//Summe der Simulationsschritte indem sich das Fahrzeug bewegt hat
	double p_dZeit;//Speichert den letzten globalen Zeitpunkt, zu dem dieses Objekt simuliert wurde


public:

	//Copy konstruktor deaktivieren

	Fahrzeug(const Fahrzeug& other) = delete;

	//Default Konstruktor

	Fahrzeug();

	//Parametric Konstruktor mit Referenz als Parameter

	Fahrzeug(const string& name);

	//Konstruktor mit Name und maximale Geschwindigkeit als Parameter

	Fahrzeug(string p_sName, double p_dMaxGeschwindigkeit);

	//Dekonstruktor

	virtual ~Fahrzeug();

	//Deklaration von output Funktion

	static void vKopf();

	//stream operator als parameter

	virtual void vAusgeben(std::ostream& o) const;

	//Deklaration von Funktion vSimulieren()

	 virtual void vSimulieren();
	 virtual double dTanken(double menge = std::numeric_limits<double>::infinity());
	 virtual double dGeschwindigkeit() const;

	 //Funktion Definition

	 bool operator<(const Fahrzeug& other) const;
	 Fahrzeug& operator=(const Fahrzeug& other);
	 const std::string& getName() const { return p_sName; }


};

std::ostream& operator<<(std::ostream& o, const Fahrzeug& f);



#endif /* FAHRZEUG_H_ */
