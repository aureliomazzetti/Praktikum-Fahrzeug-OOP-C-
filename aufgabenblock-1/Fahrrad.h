/*
 * Fahrrad.h
 *
 *  Created on: 21 nov 2025
 *      Author: samad
 */

#ifndef FAHRRAD_H_
#define FAHRRAD_H_
#include "Fahrzeug.h"
class Fahrrad : public Fahrzeug {
public:

    // Fahrrad Konstruktor

    Fahrrad(const std::string& name, double maxG);

    // Funktion-Override

    void vSimulieren() override;
    virtual void vAusgeben(std::ostream& o) const override;


    virtual double dTanken(double menge = std::numeric_limits<double>::infinity()) override;

    //Dekonstruktor

    virtual ~Fahrrad();
    double dGeschwindigkeit() const override;
};



#endif /* PKW_H_ */
