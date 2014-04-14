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


#ifndef __Frame_H__
#define __Frame_H__

#include <TGFrame.h>

class TGWindow;
class TGMainFrame;
class TGTextView;
class TGNumberEntry;
class TTree;
class TGMenuBar;
class TGPopupMenu;
class TRootHelpDialog;
class TGLabel;
class TGCheckButton;
class TGComboBox;

class Particle;
class Ring;

class Frame : public TGMainFrame {
    
private:
//    TGMainFrame *fMain;
    TGTextView * fTextView;
    TGNumberEntry *fNumberEntryA;
    TGNumberEntry *fNumberEntryZ;
    TGNumberEntry *fNumberEntryN;
    TGNumberEntry *fNumberEntryE;
    TGNumberEntry *fNumberEntryQ;
    TGNumberEntry *fNumerEntryPathLength;
    TGNumberEntry *fNumberEntryAnalysisf0;
    TGNumberEntry *fNumberEntryCurrent;
    TGLabel * fLabelPathLength;
    TGLabel * fLabelm;
    TGMenuBar     *fMenuBar;     // main menu bar
    TGPopupMenu   *fMenuFile;    // "File" popup menu entry
    TGPopupMenu   *fMenuHelp;    // "Help" popup menu entry
    TRootHelpDialog * hd;
    TGCheckButton *fCheckButtonUseRingCircum;
    TGComboBox *fComboStorageRing;
    Double_t path_length;
    Particle * particle;
    Ring * ring;
    TTree * t;
    
public:
    Frame(const TGWindow *p,UInt_t w,UInt_t h, TTree * t);
    virtual ~Frame();
    void About();
    virtual void DoCloseWindow();
    void DoPrintInfo();         // SLOT //
    void DoPrintResults();      // SLOT //
    void DoEnable(Bool_t on);   // SLOT //
    void navigate1();
    void navigate2();
    void navigate3();
    void navigate4();
    void navigate5();
    void navigate6();
    void navigate7();
    void navigate8();
    void navigate9();
    void HandleMenu(Int_t);
    void HandleComboStorageRing(Int_t);
    void prepareCalculations();
    ClassDef(Frame,0)
};
#endif
