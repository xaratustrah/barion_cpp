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

#include <TGClient.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TRandom.h>
#include <TGButton.h>
#include <TRootEmbeddedCanvas.h>
#include <TGLabel.h>
#include <TGTextEdit.h>
#include <TGMsgBox.h>
#include <TApplication.h>
#include <TGMenu.h>
#include <TGNumberEntry.h>
#include <TTree.h>
#include <TRootHelpDialog.h>
#include <TGComboBox.h>
#include <Riostream.h>
#include <TSystem.h>
#include <TUnixSystem.h>

#include "Frame.h"
#include "Particle.h"
#include "Ring.h"
#include "Readme.h"

enum EEntriesId {
     kENTRY1,
     kENTRY2
};

enum EMyMessageTypes {
     M_FILE_SAVE,
     M_FILE_EXIT,
     M_HELP_ABOUT
};

enum EStorageRings {
     ID_CR,
     ID_CRYRING,
     ID_CSRe,
     ID_CSR,
     ID_ESR,
     ID_HESR,
     ID_RIRING,
     ID_TSR
};

//______________________________________________________________________________
void Frame::HandleComboStorageRing(Int_t id)
{
     Double_t circum, mag_rigidity;
    
     switch(id){
            
     case ID_CR:
	  circum = 221.45;
	  mag_rigidity = 13;
	  break;
            
     case ID_CRYRING:
	  circum = 51.63;
	  mag_rigidity = 1;
	  break;
            
     case ID_CSRe:
	  circum = 108.36;
	  mag_rigidity = 18;
	  break;
            
     case ID_CSR:
	  circum = 35.0;
	  mag_rigidity = 1;
	  break;
            
     case ID_ESR:
	  circum = 108.36;
	  mag_rigidity = 18;
	  break;
            
     case ID_HESR:
	  circum = 442.5;
	  mag_rigidity = 1;
	  break;
            
     case ID_RIRING:
	  circum = 60.0;
	  mag_rigidity = 1;
	  break;
            
     case ID_TSR:
	  circum = 55.4;
	  mag_rigidity = 1;
	  break;
     }
     ring->setCircumference(circum);
     ring->setMagRegidity(mag_rigidity);
}

//______________________________________________________________________________
void Frame::HandleMenu(Int_t menu_id)
{
     // Handle menu events.
    
     switch (menu_id) {
     case M_FILE_EXIT:
	  // close the window and quit application
	  DoCloseWindow();
	  break;
     case M_FILE_SAVE:
	  //            new TGFileDialog(gClient->GetRoot(), this, kFDOpen, &fi);
	  //            dir = fi.fIniDir;
	  // doesn't do much, but can be used to open a root file...
	  break;
     case M_HELP_ABOUT:
	  hd = new TRootHelpDialog(this, "About barion...", 700, 300);
	  hd->SetText(README_md);
	  hd->Popup();
//	  About();
	  break;
     }
}


//______________________________________________________________________________
Frame::Frame(const TGWindow *p,UInt_t w,UInt_t h, TTree * t) //
     : TGMainFrame(p,w,h) {
     // Constructor.
    
     // receive the tree
     this->t = t;
    
     // Container frames // ************** // ************** //
    
     TGHorizontalFrame * fHFrameMain = new TGHorizontalFrame(this);
     TGVerticalFrame * fVFrameLeft = new TGVerticalFrame(fHFrameMain);
     TGHorizontalFrame * fHFrameLeftTop = new TGHorizontalFrame(fVFrameLeft);
     TGGroupFrame *fGroupFrameNuclide = new TGGroupFrame (fHFrameLeftTop);
     fGroupFrameNuclide->SetTitle("Nuclide");
     fGroupFrameNuclide->SetLayoutManager(new TGMatrixLayout(fGroupFrameNuclide, 2, 2, 10, 10));
     TGCompositeFrame *fCFrameButtons = new TGCompositeFrame(this, 120, 20,
							     kHorizontalFrame | kFixedWidth);
     fCFrameButtons->SetLayoutManager(new TGMatrixLayout(fCFrameButtons, 3, 3));
    
     TGGroupFrame *fGroupFrameSettings = new TGGroupFrame (fVFrameLeft);
     fGroupFrameSettings->SetTitle("Settings");
    
     fGroupFrameSettings->SetLayoutManager(new TGMatrixLayout(fGroupFrameSettings, 6, 3, 10, 10));
    
     // Menu bar // ************** // ************** //
    
     TString icondir(TString::Format("%s/icons/", gSystem->Getenv("ROOTSYS")));

     fMenuBar = new TGMenuBar(this, 35, 50, kHorizontalFrame);
     fMenuFile = new TGPopupMenu(gClient->GetRoot());
     fMenuFile->AddEntry(" &Save results", M_FILE_SAVE, 0,
			 gClient->GetPicture(icondir+"bld_save.png"));
     fMenuFile->DisableEntry(M_FILE_SAVE);
     fMenuFile->AddSeparator();
     fMenuFile->AddEntry(" E&xit", M_FILE_EXIT, 0,
			 gClient->GetPicture(icondir+"bld_exit.png"));
     fMenuFile->Connect("Activated(Int_t)", "Frame", this,
			"HandleMenu(Int_t)");
     fMenuHelp = new TGPopupMenu(gClient->GetRoot());
     fMenuHelp->AddEntry(" &About...", M_HELP_ABOUT, 0,
			 gClient->GetPicture(icondir+"about.xpm"));
     fMenuHelp->Connect("Activated(Int_t)", "Frame", this,
			"HandleMenu(Int_t)");
     fMenuBar->AddPopup("&File", fMenuFile, new TGLayoutHints(kLHintsTop|kLHintsLeft,
							      0, 4, 0, 0));
     fMenuBar->AddPopup("&Help", fMenuHelp, new TGLayoutHints(kLHintsTop|kLHintsRight));
    
    
     // Navigation buttons // ************** // ************** //
    
     const int NBUTTON = 9;
     TGPictureButton *fButton[NBUTTON];
     for (int i = 0; i< NBUTTON; i++)
     {
	  fButton[i] = new TGPictureButton(fCFrameButtons, gClient->GetPicture(Form("%s/rsrc/a%d.png",gSystem->WorkingDirectory(),i+1)));
	  fCFrameButtons->AddFrame(fButton[i], new TGLayoutHints(kLHintsTop | kLHintsExpandX, 2, 2, 2, 2));
	  fButton[i]->SetToolTipText("Move around nuclidic chart.");
	  fButton[i]->Connect("Clicked()", "Frame", this, Form("navigate%d()", i+1));
     }
     fButton[4]->SetToolTipText("Calculate values.");
    
     // Text field // ************** // ************** //
     fTextView = new TGTextView(fHFrameMain, 600, 300);
    
     // Nuclide Frame // ************** // ************** //
    
     TGLabel * fLabelA = new TGLabel(fGroupFrameNuclide, "A:");
     fNumberEntryA = new TGNumberEntry(fGroupFrameNuclide, 197, 9, kENTRY1, TGNumberFormat::kNESInteger, //style
				       TGNumberFormat::kNEAPositive, //input value filter
				       TGNumberFormat::kNELLimitMinMax, //specify limits
				       1,295);
     fNumberEntryA->Connect("ValueSet(Long_t)", "Frame", this, "DoPrintInfo()");
     TGLabel * fLabelZ = new TGLabel(fGroupFrameNuclide, "Z:");
     fNumberEntryZ = new TGNumberEntry(fGroupFrameNuclide, 79, 9, kENTRY1, TGNumberFormat::kNESInteger, //style
				       TGNumberFormat::kNEANonNegative, //input value filter
				       TGNumberFormat::kNELLimitMinMax, //specify limits
				       0,118);
     fNumberEntryZ->Connect("ValueSet(Long_t)", "Frame", this, "DoPrintInfo()");
     fGroupFrameNuclide->AddFrame(fLabelA, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,2,2,2,2));
     fGroupFrameNuclide->AddFrame(fNumberEntryA, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,2,2,2,2));
     fGroupFrameNuclide->AddFrame(fLabelZ, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,2,2,2,2));
     fGroupFrameNuclide->AddFrame(fNumberEntryZ, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,2,2,2,2));
    
     // Settings frame // ************** // ************** //
    
     TGLabel * fLabelE = new TGLabel(fGroupFrameSettings, "E:");
     fGroupFrameSettings->AddFrame(fLabelE, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,2,2,2,2));
     fNumberEntryE = new TGNumberEntry(fGroupFrameSettings, 400.0, 9, kENTRY1, TGNumberFormat::kNESReal, TGNumberFormat::kNEANonNegative);
     fNumberEntryE->Connect("ValueSet(Long_t)", "Frame", this, "DoPrintResults()");
     fGroupFrameSettings->AddFrame(fNumberEntryE, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,2,2,2,2));
     TGLabel * fLabelMeVu = new TGLabel(fGroupFrameSettings, "MeV/u");
     fGroupFrameSettings->AddFrame(fLabelMeVu, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,2,2,2,2));
    
     TGLabel * fLabelQ = new TGLabel(fGroupFrameSettings, "Q:");
     fGroupFrameSettings->AddFrame(fLabelQ, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,2,2,2,2));
     fNumberEntryQ = new TGNumberEntry(fGroupFrameSettings, 78, 9, kENTRY1, TGNumberFormat::kNESInteger,TGNumberFormat::kNEANonNegative,
				       TGNumberFormat::kNELLimitMinMax, //specify limits
				       0,118);
     fNumberEntryQ->Connect("ValueSet(Long_t)", "Frame", this, "DoPrintResults()");
     fGroupFrameSettings->AddFrame(fNumberEntryQ, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,2,2,2,2));
     TGLabel * fLabelPlus = new TGLabel(fGroupFrameSettings, "+");
     fGroupFrameSettings->AddFrame(fLabelPlus, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,2,2,2,2));
    
     TGLabel * fLabelAnalysisf0 = new TGLabel(fGroupFrameSettings, "Analysis f0:");
     fGroupFrameSettings->AddFrame(fLabelAnalysisf0, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,2,2,2,2));
     fNumberEntryAnalysisf0 = new TGNumberEntry(fGroupFrameSettings, 244.963000, 9, kENTRY1, TGNumberFormat::kNESReal, TGNumberFormat::kNEAPositive);
     fNumberEntryAnalysisf0->Connect("ValueSet(Long_t)", "Frame", this, "DoPrintResults()");
    
     fGroupFrameSettings->AddFrame(fNumberEntryAnalysisf0, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,2,2,2,2));
     TGLabel * fLabelMHz = new TGLabel(fGroupFrameSettings, "MHz");
     fGroupFrameSettings->AddFrame(fLabelMHz, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,2,2,2,2));
    
     TGLabel * fLabelCurrent = new TGLabel(fGroupFrameSettings, "Beam Current:");
     fGroupFrameSettings->AddFrame(fLabelCurrent, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,2,2,2,2));
     fNumberEntryCurrent = new TGNumberEntry(fGroupFrameSettings, 0.324, 9, kENTRY1, TGNumberFormat::kNESReal, TGNumberFormat::kNEAPositive);
     fNumberEntryCurrent->Connect("ValueSet(Long_t)", "Frame", this, "DoPrintResults()");
     fGroupFrameSettings->AddFrame(fNumberEntryCurrent, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,2,2,2,2));
     TGLabel * fLabelmA = new TGLabel(fGroupFrameSettings, "mA");
     fGroupFrameSettings->AddFrame(fLabelmA, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,2,2,2,2));
    
     TGLabel * fLabelStorageRing = new TGLabel(fGroupFrameSettings, "Storage ring:");
     fGroupFrameSettings->AddFrame(fLabelStorageRing, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,2,2,2,2));
     char tmp[9];
     TGLayoutHints *fLComboStorageRing = new TGLayoutHints(kLHintsTop | kLHintsLeft,5,5,5,5);
     // combo box widget
     fComboStorageRing = new TGComboBox(fGroupFrameSettings,100);
    
     fComboStorageRing->AddEntry("CR", ID_CR);
     fComboStorageRing->AddEntry("CRYRING", ID_CRYRING);
     fComboStorageRing->AddEntry("CSRe", ID_CSRe);
     fComboStorageRing->AddEntry("CSR", ID_CSR);
     fComboStorageRing->AddEntry("ESR", ID_ESR);
     fComboStorageRing->AddEntry("HESR", ID_HESR);
     fComboStorageRing->AddEntry("RIRING", ID_RIRING);
     fComboStorageRing->AddEntry("TSR", ID_TSR);
     fComboStorageRing->Resize(85, 20);
     // Entry3 is selected as current
     fComboStorageRing->Select(4);
     fGroupFrameSettings->AddFrame(fComboStorageRing, fLComboStorageRing);
     fComboStorageRing->Connect("Selected(Int_t)", "Frame", this, "DoPrintResults()");
    
     fCheckButtonUseRingCircum = new TGCheckButton(fGroupFrameSettings, "Use Circum.",1);
     fCheckButtonUseRingCircum->SetOn();//SetState(kButtonDown);
     fGroupFrameSettings->AddFrame(fCheckButtonUseRingCircum);
     fCheckButtonUseRingCircum->Connect("Toggled(Bool_t)", "Frame", this, "DoEnable(Bool_t)");
    
     fLabelPathLength = new TGLabel(fGroupFrameSettings, "Path Length:");
     fLabelPathLength->Disable(true);
     fGroupFrameSettings->AddFrame(fLabelPathLength, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,2,2,2,2));
     //    fNumerEntryPathLength->SetEditable(false);
     fNumerEntryPathLength = new TGNumberEntry(fGroupFrameSettings, 108.5, 9, kENTRY1, TGNumberFormat::kNESReal, TGNumberFormat::kNEAPositive);
     fGroupFrameSettings->AddFrame(fNumerEntryPathLength, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,2,2,2,2));
     fNumerEntryPathLength->Connect("ValueSet(Long_t)", "Frame", this, "DoPrintResults()");
     fNumerEntryPathLength->SetState(false);
    
     fLabelm = new TGLabel(fGroupFrameSettings, "m");
     fLabelm->Disable(true);
     fGroupFrameSettings->AddFrame(fLabelm, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,2,2,2,2));
    
    
    
     // Add frames to the window // ************** // ************** //
    
     fHFrameLeftTop->AddFrame(fGroupFrameNuclide, new TGLayoutHints(kLHintsNoHints, 2,2,2,2));
     fHFrameLeftTop->AddFrame(fCFrameButtons, new TGLayoutHints(kLHintsCenterX, 20, 2, 46, 1));
    
     fVFrameLeft->AddFrame(fHFrameLeftTop, new TGLayoutHints(kLHintsCenterX, 2, 2, 2, 2));
     fVFrameLeft->AddFrame(fGroupFrameSettings, new TGLayoutHints(kLHintsCenterX, 2,2,2,2));
    
     fHFrameMain->AddFrame(fVFrameLeft, new TGLayoutHints(kLHintsExpandY, 2,2,2,2));
     fHFrameMain->AddFrame(fTextView, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2,2,2,2));
    
     AddFrame(fMenuBar, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 2, 2, 2, 5));
     AddFrame(fHFrameMain, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY | kLHintsCenterX,2,2,2,2));
    
    
     // refresh the view
     DoPrintInfo();
    
     // following 3 lines make a fixed size TGMainFrame
     TGDimension size = GetDefaultSize();
     SetWMSize(size.fWidth, size.fHeight);
     SetWMSizeHints(size.fWidth, size.fHeight, size.fWidth, size.fHeight, 0, 0);
    
     // Sets window name and shows the main frame
     SetWindowName("barion");
     MapSubwindows();
     Move(200,200);
     Resize(GetDefaultSize());
     Connect("CloseWindow()", "Frame", this, "DoCloseWindow()");
     DontCallClose(); // to avoid double deletions.
     MapWindow();
}

//______________________________________________________________________________
void Frame::prepareCalculations(){
     Int_t aa, zz, qq;
     Double_t ke_u, f0, IB;
    
     aa = fNumberEntryA->GetIntNumber();
     zz = fNumberEntryZ->GetIntNumber();
     ke_u = fNumberEntryE->GetNumber();
     qq = fNumberEntryQ->GetNumberEntry()->GetIntNumber();
     f0 = fNumberEntryAnalysisf0->GetNumber();
     IB = fNumberEntryCurrent->GetNumber();
    
     ring = new Ring();
    
     if(fCheckButtonUseRingCircum->IsOn())
     {
	  HandleComboStorageRing(fComboStorageRing->GetSelected());
	  path_length = ring->getCircumference();
     }
     else
     {
	  path_length = fNumerEntryPathLength->GetNumber();
     }
     particle = new Particle(t, aa, zz, ke_u, qq, path_length, f0, IB);
}


//______________________________________________________________________________
void Frame::DoPrintInfo(){
    
     prepareCalculations();
     fTextView->ShowTop(); // show top of the buffer.
     if(particle->found){
	  fTextView->LoadBuffer(particle->getInfo());
     }
     else
	  fTextView->LoadBuffer("No such nuclide in AME2012.");
}

//______________________________________________________________________________
void Frame::DoPrintResults(){
     Int_t zz = fNumberEntryZ->GetNumberEntry()->GetIntNumber();
     Int_t qq = fNumberEntryQ->GetNumberEntry()->GetIntNumber();
     if (qq > zz)         fTextView->LoadBuffer("Charge state must be smaller than proton number.");
     else{
	  prepareCalculations();
	  if(particle->found)
	       fTextView->LoadBuffer(particle->getResults());
	  else
	       fTextView->LoadBuffer("No such nuclide in AME2012.");
     }
}

//______________________________________________________________________________
void Frame::navigate1()
{
     // isobar up
     Int_t zz = fNumberEntryZ->GetNumberEntry()->GetIntNumber();
     fNumberEntryZ->SetIntNumber(zz+1);
     DoPrintInfo();
}

//______________________________________________________________________________
void Frame::navigate2()
{
     // isotone Up
     Int_t aa = fNumberEntryA->GetNumberEntry()->GetIntNumber();
     Int_t zz = fNumberEntryZ->GetNumberEntry()->GetIntNumber();
     fNumberEntryA->SetIntNumber(aa+1);
     fNumberEntryZ->SetIntNumber(zz+1);
     DoPrintInfo();
}

//______________________________________________________________________________
void Frame::navigate3()
{
     Int_t aa = fNumberEntryA->GetNumberEntry()->GetIntNumber();
     Int_t zz = fNumberEntryZ->GetNumberEntry()->GetIntNumber();
     fNumberEntryA->SetIntNumber(aa+2);
     fNumberEntryZ->SetIntNumber(zz+1);
     DoPrintInfo();
}

//______________________________________________________________________________
void Frame::navigate4()
{
     // isotope Down
     Int_t aa = fNumberEntryA->GetNumberEntry()->GetIntNumber();
     fNumberEntryA->SetIntNumber(aa-1);
     DoPrintInfo();
}

//______________________________________________________________________________
void Frame::navigate5()
{
     DoPrintResults();
}

//______________________________________________________________________________
void Frame::navigate6()
{
     // isotope up
     Int_t aa = fNumberEntryA->GetNumberEntry()->GetIntNumber();
     fNumberEntryA->SetIntNumber(aa+1);
     DoPrintInfo();
}

//______________________________________________________________________________
void Frame::navigate7()
{
     Int_t aa = fNumberEntryA->GetNumberEntry()->GetIntNumber();
     Int_t zz = fNumberEntryZ->GetNumberEntry()->GetIntNumber();
     fNumberEntryA->SetIntNumber(aa-2);
     fNumberEntryZ->SetIntNumber(zz-1);
     DoPrintInfo();
}

//______________________________________________________________________________
void Frame::navigate8()
{
     // isotone Down
     Int_t aa = fNumberEntryA->GetNumberEntry()->GetIntNumber();
     Int_t zz = fNumberEntryZ->GetNumberEntry()->GetIntNumber();
     fNumberEntryA->SetIntNumber(aa-1);
     fNumberEntryZ->SetIntNumber(zz-1);
     DoPrintInfo();
}

//______________________________________________________________________________
void Frame::navigate9()
{
     // isobar up
     Int_t zz = fNumberEntryZ->GetNumberEntry()->GetIntNumber();
     fNumberEntryZ->SetIntNumber(zz-1);
     DoPrintInfo();
}

//______________________________________________________________________________
void Frame::DoCloseWindow()
{
     // Got close message for this MainFrame. Calls parent CloseWindow()
     // (which destroys the window) and terminate the application.
     // The close message is generated by the window manager when its close
     // window menu item is selected.
    
     if (particle) { delete particle; particle = 0; }
     if (ring) { delete ring; ring = 0; }
     if (t) { delete t; t = 0; }
    
     fMenuFile->Disconnect("Activated(Int_t)", this, "HandleMenu(Int_t)");
     fMenuHelp->Disconnect("Activated(Int_t)", this, "HandleMenu(Int_t)");
    
     TGMainFrame::CloseWindow();
     gApplication->Terminate(0);
}

//______________________________________________________________________________
void Frame::DoEnable(Bool_t on)
{
     fLabelPathLength->Disable(on);
     fLabelm->Disable(on);
     fLabelPathLength->Disable(on);
     fNumerEntryPathLength->SetState(!on);
     DoPrintResults();
}

//______________________________________________________________________________
void Frame::About()
{
     //new TGMsgBox (gClient->GetRoot(),this, "About barion", Form("barion %s\n\n\nShahab SANJARI (c) 2014\n\n\nBased on data published in\n\nG. Audi et al 2012 Chinese Phys. C 36 1287 doi:10.1088/1674-1137/36/12/002.", VERSION), 0, kMBOk, 0,kVerticalFrame,kTextCenterX);
}

//______________________________________________________________________________
Frame::~Frame() {
     // Clean up used widgets: frames, buttons, layouthints
     // fMain->Cleanup();
     // delete fMain;
}
