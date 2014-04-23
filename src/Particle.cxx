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


#include <Riostream.h>
#include <TString.h>
#include <TTree.h>
#include <TMath.h>

#include "Particle.h"
#include "Constants.h"
#include "ElBiEn.h"

//______________________________________________________________________________
Particle::Particle(){}

//______________________________________________________________________________
Particle::~Particle(){}


//______________________________________________________________________________
Particle::Particle(TTree * t, Int_t a, Int_t z, Double_t ke_u, Int_t qq, Double_t path_length, Double_t f0, Double_t IB)
{
    this->ke_u = ke_u;
    this->qq = qq;
    this->path_length = path_length;
    this->f0 = f0;
    this->IB = IB;
    
    t->SetBranchAddress("aa", &aa);
    t->SetBranchAddress("zz", &zz);
    t->SetBranchAddress("experimental_flag", &experimental_flag);
    
    t->SetBranchAddress("am_u", &am_u);
    t->SetBranchAddress("am_unc_u", &am_unc_u);
    t->SetBranchAddress("mass_exess_kev", &mass_exess_kev);
    t->SetBranchAddress("mass_exess_unc_kev", &mass_exess_unc_kev);
    t->SetBranchAddress("beu_kev", &beu_kev);
    t->SetBranchAddress("beu_unc_kev", &beu_unc_kev);
    t->SetBranchAddress("decay_e_kev", &decay_e_kev);
    t->SetBranchAddress("decay_e_unc_kev", &decay_e_unc_kev);
    
    t->SetBranchAddress("decay_type", &decay_type);
    t->SetBranchAddress("name", &name);
    
    Int_t nentries=(Int_t)t->GetEntries();
    found = false;
    
    for (int j= 0; j < nentries; j++){
        t->GetEntry(j); // move the tree snapshot to window number j
        if(aa == a && zz == z) {found = true; break; }// found the nuclide
    }
}

//______________________________________________________________________________
TString Particle::getInfo()
{
    TString s;
    s += Form("%d %s\n", aa, name);
    s += Form("z: %d\n", zz);
    s += Form("n: %d\n\n", aa-zz);
    if(experimental_flag == 1) s += "Experimental values:\n"; else s += "** Non-Experimental values! **\n";
    s += Form("\nAtom. Mass:\t\t%.12g [u]\n", getAtomicMassInU());
    s += Form("Atom. Mass Err:\t\t%g [u]\n", am_unc_u);
    s += Form("ME:\t\t\t%g [keV]\n", mass_exess_kev);
    s += Form("ME Err:\t\t\t%g [keV]\n", mass_exess_unc_kev);
    s += Form("BE/u:\t\t\t%g [keV]\n", beu_kev);
    s += Form("BE/u Err:\t\t%g [keV]\n", beu_unc_kev);
    s += Form("Decay:\t\t\t%s\n", decay_type);
    s += Form("Decay E:\t\t%g [keV]\n", decay_e_kev);
    s += Form("Decay E Err:\t\t%g [keV]", decay_e_unc_kev);
    return s;
}

//______________________________________________________________________________
TString Particle::getResults()
{
    TString s;
    s += Form("%d %s %d+\n", aa, name, qq);
    s += Form("z: %d\n", zz);
    s += Form("n: %d\n\n", aa-zz);
    s += Form("Beta:\t\t\t%0.12g\n", getBeta());
    s += Form("Gamma:\t\t\t%0.12g\n", getGamma());
    s += Form("Brho:\t\t\t%0.12g [Tm]\n", getMagneticRigidity());
    s += Form("Path length:\t\t%0.12g [m]\n", path_length);
    s += Form("El. Binding En.:\t%d [eV]\n", getElBiEn(zz,qq));
    s += Form("m/Q:\t\t\t%0.12g\n", getAtomicMassInU()/qq);
    s += Form("Rev. freq.:\t\t%0.12g [MHz]\n", getRevolutionFrequency());
    s += Form("%dth harmonic\t\t%0.12g [kHz] @ %0.12g [MHz]\n", getRevolutionHarmonic(),1000*((getRevolutionFrequency()*getRevolutionHarmonic())-f0), getRevolutionFrequency()*getRevolutionHarmonic());
    s += Form("%dth harmonic\t\t%0.12g [kHz] @ %0.12g [MHz]\n", getRevolutionHarmonic()+1,1000*((getRevolutionFrequency()*(getRevolutionHarmonic()+1))-f0), getRevolutionFrequency()*(getRevolutionHarmonic()+1));
    s += Form("Number of ions:\t\t%g\n", getNumberOfIons());
    s += "\nDetailed information:\n";
    s += "---------------------\n\n";
    s += Form("Atom. Mass:\t\t%.12g [u]\n", getAtomicMassInU());
    s += Form("Ion. Mass:\t\t%.12g [u]\n", getIonicMassInU());
    s += Form("\t\t\t%.12g [MeV/c^2]\n", toMeV(getIonicMassInU()));
    s += Form("\t\t\t%.12g [Kg]\n", toKg(getIonicMassInU()));
    s += Form("Kin. En./u\t\t%.12g [MeV/u]\n", ke_u);
    s += Form("Tot. Kin. En.\t\t%.12g [MeV]\n", getTotalEnergyMeV());
    s += Form("Beta * Gamma:\t\t%0.12g\n", getBeta()*getGamma());
    s += Form("Velocity:\t\t%0.12g [m/s]\n", getVelocity());
    s += Form("Rel. Mass:\t\t%0.12g [MeV/c^2]\n", getRelativisticMass());
    s += Form("\t\t\t%.12g [u]\n", toU(getRelativisticMass()));
    s += Form("\t\t\t%.12g [Kg]\n", toKg(toU(getRelativisticMass())));
    s += Form("Rel. Mom.:\t\t%0.12g [MeV/c]\n", getRelativisticMomentum());
    s += Form("Rel. Mom./u:\t\t%0.12g [MeV/c/u]\n", getRelativisticMomentum()/aa);
    s += Form("pc:\t\t\t%0.12g [MeV]\n", getRelativisticMomentum()*CC);
    s += Form("Erho:\t\t\t%0.12g [kV]\n", getElectricRigidity());
    s += Form("Analysis f0:\t\t%0.12g [MHz]\n", f0);
    s += Form("Ion beam current:\t%0.12g\n", IB);
    
    return s;
}

//______________________________________________________________________________
Int_t Particle::getElBiEn(Int_t zz, Int_t qq)
{
    // Total energy that will be freed, by building an ion
    // out of a nucleaus and a (z-q) electrons
    // 0 is set out
    //[row is from 1 to 101][col is 1 to 100]
    return ElBiEn[zz][zz - qq];
}

//______________________________________________________________________________
Int_t Particle::getRevolutionHarmonic()
{
    return (Int_t)(f0/getRevolutionFrequency());
}

//______________________________________________________________________________
Double_t Particle::getNumberOfIons(){
    return (IB/(getRevolutionFrequency()*1.0e6*qq*EE));
}

//______________________________________________________________________________
Double_t Particle::getRevolutionFrequency(){
    return getVelocity()/path_length/1.0e6;
}

//______________________________________________________________________________
Double_t Particle::getVelocity(){
    return getBeta()*CC;
}

//______________________________________________________________________________
Double_t Particle::getElectricRigidity(){
    return getMagneticRigidity()*getVelocity()/1.0e3;
}

//______________________________________________________________________________
Double_t Particle::getMagneticRigidity(){
    return getRelativisticMomentum()*1.0e6/qq/CC;
}

//______________________________________________________________________________
Double_t Particle::getRelativisticMomentum(){
    return toMeV(getAtomicMassInU())*getBeta()*getGamma();
}

//______________________________________________________________________________
Double_t Particle::getRelativisticMass(){
    return toMeV(getAtomicMassInU())*getGamma();
}

//______________________________________________________________________________
Double_t Particle::getBeta(){
    return TMath::Sqrt(1.0-1.0/TMath::Power(getGamma(),2));
}

//______________________________________________________________________________
Double_t Particle::getGamma(){
    return getTotalEnergyMeV()/toMeV(getAtomicMassInU()) + 1.0;
}

//______________________________________________________________________________
Double_t Particle::getAtomicMassInU(){
    return am_u;
}

//______________________________________________________________________________
Double_t Particle::getIonicMassInU(){
    return getAtomicMassInU()+toU((getElBiEn(zz, 0)-getElBiEn(zz, qq))/1.0e6-qq*ME);
}

//______________________________________________________________________________
Double_t Particle::getTotalEnergyMeV(){
    return ke_u * aa;
}

//______________________________________________________________________________
Double_t Particle::toMeV(Double_t m_u){
    return m_u * UU;
}

//______________________________________________________________________________
Double_t Particle::toU(Double_t am_mev){
    return am_mev / UU;
}

//______________________________________________________________________________
Double_t Particle::toKg(Double_t m_u){
    return m_u * UU * 1.0e6 * EE / TMath::Power(CC, 2);
}

//______________________________________________________________________________
Double_t Particle::getTotalCharge(Int_t qq){
    return qq * EE;
}
