/*
 * PKW.cpp
 *
 *  Created on: 21 nov 2025
 *      Author: samad
 */

#include "PKW.h"
#include <iostream>
#include <iomanip>

PKW::PKW(const std::string& name, double maxG, double verbrauch, double tankvolumen)
    : Fahrzeug(name, maxG), p_dVerbrauch(verbrauch), p_dTankvolumen(tankvolumen), p_dTankinhalt(tankvolumen/2.0) {}

void PKW::vSimulieren()
{
	 double dZeitDiff = dGlobaleZeit - p_dZeit;

    if(p_dTankinhalt > 0)
    {

        double dStrecke = p_dMaxGeschwindigkeit * dZeitDiff;

        //Berechne wie viele Liter fur die strecke benotige

        double dBenzinVerbrauch = dStrecke * p_dVerbrauch / 100.0;

        //Kontrolliere ob genug Benzin habe

        if(dBenzinVerbrauch > p_dTankinhalt)
        {

            dStrecke = p_dTankinhalt * 100.0 / p_dVerbrauch;//Berechne wie viele Km das pkw noch fahren kann
           p_dTankinhalt = 0.0;
        }
        else
	    {
		   p_dTankinhalt -= dBenzinVerbrauch;
	    }

    	//Variablen gemäß der Simulation aktualisieren

        p_dGesamtStrecke += dStrecke;

    }
    p_dGesamtZeit += dZeitDiff;
    p_dZeit = dGlobaleZeit;
}

void PKW::vAusgeben(std::ostream& o) const
{
    Fahrzeug::vAusgeben(o);
    o << std::resetiosflags(std::ios::right) << std::setiosflags(std::ios::left)
    		  << std::setw(12) << std::fixed << std::setprecision(2) << p_dVerbrauch
              << std::setw(15) << std::fixed << std::setprecision(2) << p_dTankvolumen
              << std::setw(12) << std::fixed << std::setprecision(2) << p_dTankinhalt;
    o << std::endl;
}
PKW::~PKW()
{
    std::cout << "Dekonstrukt PKW (" << p_sName << ")" << std::endl;
}

double PKW::dTanken(double menge)
{
    double benotigteBenzinmenge = p_dTankvolumen - p_dTankinhalt;
    double zuTanken = std::min(benotigteBenzinmenge, menge);
    if ( zuTanken > 0.0) p_dTankinhalt +=  zuTanken;
    return  zuTanken;
}
