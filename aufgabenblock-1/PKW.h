/*
 * PKW.h
 *
 *  Created on: 21 nov 2025
 *      Author: samad
 */

#ifndef PKW_H_
#define PKW_H_
#include "Fahrzeug.h"
#include <limits>
class PKW : public Fahrzeug {
protected:
	//Deklaration von Variablen

	double p_dVerbrauch;
	double p_dTankvolumen;
	double p_dTankinhalt;
public:

    // PKW Konstruktor

    PKW(const std::string& name, double maxG, double verbrauch, double tankvolumen = 55.0);

    // Funktion-Override

    void vSimulieren() override;
    virtual void vAusgeben(std::ostream& o) const override;
    double dTanken(double menge = std::numeric_limits<double>::infinity()) override;

    //Dekonstruktor

    virtual ~PKW();
};



#endif /* PKW_H_ */
