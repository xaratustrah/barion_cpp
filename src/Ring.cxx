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


#include <TMath.h>
#include <TString.h>
#include "Ring.h"


//______________________________________________________________________________
Ring::Ring(){}

//______________________________________________________________________________
Ring::~Ring(){}

//______________________________________________________________________________
Ring::Ring(Double_t circum, Double_t mag_rigidity)
{

}

//______________________________________________________________________________
Double_t Ring::getMagRegidity()
{
    return mag_rigidity;
}

//______________________________________________________________________________
Double_t Ring::getCircumference()
{
    return circum;
}

//______________________________________________________________________________
void Ring::setMagRegidity(Double_t mag_rigidity)
{
    this->mag_rigidity = mag_rigidity;
}

//______________________________________________________________________________
void Ring::setCircumference(Double_t circum)
{
    this->circum = circum;
}

//______________________________________________________________________________
TString Ring::getName(){
    return name;
}
//______________________________________________________________________________
void Ring::setName(TString name){
    this->name = name;
}