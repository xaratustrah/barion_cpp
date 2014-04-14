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
class TString;


#ifndef __Ring_H__
#define __Ring_H__
class Ring
{
private:
    Double_t circum, mag_rigidity;
    TString name;
    
public:
    Ring();
    Ring(Double_t, Double_t);
    virtual ~Ring();
    Double_t getMagRegidity();
    Double_t getCircumference();
    void setMagRegidity(Double_t);
    void setCircumference(Double_t);
    void setName(TString);
    TString getName();
};

#endif