// This file is part of barion project.
//
// (c) Copyright M. Shahab SANJARI 2014
//
// barion is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// barion is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
//
// along with barion.  If not, see <http://www.gnu.org/licenses/>.


#ifndef __Particle_H__
#define __Particle_H__

#include <TTree.h>

const Double_t CC = 299792458; // m/s
const Double_t UU = 931.4940023; // MeV/C^2
const Double_t EE = 1.602176565e-19; // Coulombs

class Particle
{
private:
    Int_t aa, zz, experimental_flag, qq;
    Double_t am_u, am_unc_u, mass_exess_kev, mass_exess_unc_kev, beu_kev, beu_unc_kev, decay_e_kev, decay_e_unc_kev, ke_u, path_length, f0, IB;
    char name [4];
    char decay_type [3];
    
public:
    Particle();
    Particle(TTree *, Int_t, Int_t, Double_t, Int_t, Double_t, Double_t, Double_t);
    virtual ~Particle();
    TString getInfo();
    TString getResults();
    Double_t toMeV(Double_t);
    Double_t toKg(Double_t);
    Double_t toU(Double_t);
    Double_t getTotalCharge(Int_t);
    Double_t getTotalEnergyMeV();
    Double_t getGamma();
    Double_t getBeta();
    Double_t getRelativisticMass();
    Double_t getRelativisticMomentum();
    Double_t getMagneticRigidity();
    Double_t getElectricRigidity();
    Double_t getVelocity();
    Double_t getRevolutionFrequency();
    Int_t getRevolutionHarmonic();
    Double_t getNumberOfIons();
    Double_t getAtomicMassInU();
    Bool_t found;
};


#endif // __Particle_H__
