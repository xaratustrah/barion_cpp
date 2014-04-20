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


#include <TApplication.h>
#include <TTree.h>
#include <TFile.h>
#include <Riostream.h>
#include <TGMsgBox.h>
#include <cstdlib>

#include "Frame.h"


//______________________________________________________________________________
Bool_t fexists(const char *filename)
{
     ifstream ifile(filename);
     return ifile;
}

//______________________________________________________________________________
void save_tree(TTree * tree, const char * filename)
{
     // Open a file , save the tree and close the file
     TFile ofile(filename ,"RECREATE");
     tree->Write();
     ofile.Close ();
     cout << "Binary file successfully generated." << endl;
     return;
}

//______________________________________________________________________________
TTree * read_tree (const char* filename){
     TTree *t;
     TFile * f;
    
     if((Bool_t)fexists(Form("../Resources/%s", filename)))
     {
	  f = new TFile(Form("../Resources/%s", filename));
//	  cout << "Found database file in the Application Bundle." << endl;
     }
     else if((Bool_t)fexists(Form("./rsrc/%s", filename)))
     {
	  f = new TFile(Form("./rsrc/%s", filename));
//	  cout << "Found database file in the resources directory." << endl;
     }
     else if((Bool_t)fexists(filename))
     {
	  f = new TFile(filename);
//	  cout << "Found database file in the current directory." << endl;
     }
     else
     {
	  cout << "Database file is missing. Please create the database first." << endl;
	  return t;
     }

     t = (TTree *)f->Get("t");
     if(!t){
	  cout << "Database file does not contain a tree. Please create the database first." << endl;
     }
     return t;
}

//______________________________________________________________________________
void make_tree(const char * filename)
{
     Int_t aa, zz, experimental_flag;
     Double_t am_u, am_unc_u, mass_exess_kev, mass_exess_unc_kev, beu_kev, beu_unc_kev, decay_e_kev, decay_e_unc_kev;
     string decay_type_tmp, name_tmp;
     char name [4];
     char decay_type [3];
    
     // Initialize the tree
     TTree * t = new TTree();
     t->SetName("t");
     t->SetTitle("Measurement Data");
    
     t->Branch("aa", &aa, "aa/I");
     t->Branch("zz", &zz, "zz/I");
     t->Branch("experimental_flag", &experimental_flag, "experimental_flag/I");
    
     t->Branch("am_u", &am_u, "am_u/D");
     t->Branch("am_unc_u", &am_unc_u, "am_unc_u/D");
     t->Branch("mass_exess_kev", &mass_exess_kev, "mass_exess_kev/D");
     t->Branch("mass_exess_unc_kev", &mass_exess_unc_kev, "mass_exess_unc_kev/D");
     t->Branch("beu_kev", &beu_kev, "beu_kev/D");
     t->Branch("beu_unc_kev", &beu_unc_kev, "beu_unc_kev/D");
     t->Branch("decay_e_kev", &decay_e_kev, "decay_e_kev/D");
     t->Branch("decay_e_unc_kev", &decay_e_unc_kev, "decay_e_unc_kev/D");
    
     t->Branch("decay_type", &decay_type, "decay_type/C");
     t->Branch("name", &name, "name/C");
    
     ifstream datafile;
     datafile.open(filename);
    
     while (true) {
	  if (!datafile.good()) break;
        
	  datafile >> aa >> zz >> am_u >> am_unc_u >> mass_exess_kev >> mass_exess_unc_kev >> beu_kev >> beu_unc_kev >> decay_e_kev >> decay_e_unc_kev >> experimental_flag >> decay_type_tmp >> name_tmp;
        
	  // TTree accepts only c character pointer with null termination
	  strcpy(decay_type, decay_type_tmp.c_str());
	  strcpy(name, name_tmp.c_str());
        
	  t->Fill();
     }
    
     datafile.close();
     save_tree(t, "database.root");
     return;
}

//______________________________________________________________________________
void showFrame(TTree * t) {
     // Popup the GUI...
     new Frame(gClient->GetRoot(),400,400, t);
}

//______________________________________________________________________________
int ParseCmdLine(int argc, char *argv[], char **inFileName) {
     int n = 1;
     if (argc > 3) {
	  cout << "Usage:\n\n";
	  cout << "    barion -c reduced.mass.file\n\nor\n\n    barion path_to/database.root\n\nor if the database.root is in the current directory, just\n\n    barion\n\n";
	  exit(EXIT_SUCCESS);
     }
     while (n < argc) {
	  if (!strncmp(argv[n], "-c", 2) || !strncmp(argv[n], "-C", 2)) {
	       *inFileName = argv[++n];
	  } else {
	       cout << "Usage:\n\n";
	  cout << "    barion -c reduced.mass.file\n\nor\n\n    barion path_to/database.root\n\nor if the database.root is in the current directory, just\n\n    barion\n\n";
	       exit(EXIT_SUCCESS);
	  }
	  ++n;
     }
     return 0;
}

//______________________________________________________________________________
int main(int argc, char **argv) {

     char * filename_base;
     TTree * t;
     if (argc < 3){    
	  if (argc == 1){
	       t = read_tree("database.root");
	  }
	  else if (argc == 2){
	       t = read_tree(argv[1]);
	  }
	  if(!t) exit(-1);
	  TApplication theApp("App",&argc,argv);
	  showFrame(t);
	  theApp.Run();
     }
     else
     {
	  ParseCmdLine(argc, argv, &filename_base);
	  make_tree(filename_base);
     }
     return 0;
}
