/*
 * Fahrrad.cpp
 *
 *  Created on: 21 nov 2025
 *      Author: samad
 */

#include "Fahrrad.h"
#include <iostream>

Fahrrad::Fahrrad(const std::string& name, double maxG)
    : Fahrzeug(name, maxG) {}

void Fahrrad::vSimulieren()
{
    Fahrzeug::vSimulieren();
}

void Fahrrad::vAusgeben(std::ostream& o) const
{
    Fahrzeug::vAusgeben(o);
}

Fahrrad::~Fahrrad()
{
    std::cout << "Dekonstrukt Fahrrad (" << p_sName << ")" << std::endl;
}


double Fahrrad::dTanken(double menge)
{
    return 0.0;
}


//Gechwindingkeit Funktion

double Fahrrad::dGeschwindigkeit() const
{
		//Berechne die Anzahl ganzer 20-km-Abschnitte in p_dGesamtStrecke

	    int segments = static_cast<int>(p_dGesamtStrecke / 20.0);

	    // Fur jedes 20-km-Abschnitte/Segment wird 10% der Geschwindigkeit abgezogen

	    double speedFactor = 1.0 - 0.10 * segments;

	    // Neue geschwindigkeit ausrechnen

	    double v = p_dMaxGeschwindigkeit * speedFactor;

	    //Kontrolliere ob Geschwindigkeit > 12 ist

	    if (v < 12.0)
	        v = 12.0;

	    return v;
}
