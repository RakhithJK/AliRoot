/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

/*
  $Log$
  Revision 1.4  2000/11/20 09:50:03  schutz
  AliPHOSCPVHit inherits from AliHit

  Revision 1.3  2000/11/13 11:45:36  schutz
  DEC and HP compilers sufisfied

  Revision 1.2  2000/11/13 09:34:11  martinez
  Copy constructor and operator = changed

  Revision 1.1  2000/11/03 16:49:35  schutz
  New class AliPHOSCPVModule

*/

////////////////////////////////////////////////
//  Manager class for one CPV module          //
//                                            //
//  Author: Yuri Kharlov, IHEP, Protvino      //
//  e-mail: Yuri.Kharlov@cern.ch              //
//  Last modified: 2 November 2000            //
////////////////////////////////////////////////
 
// --- ROOT system ---
#include <TTree.h>

// --- Standard library ---
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream.h>

// --- galice header files ---
#include "AliRun.h"
#include "AliPHOSCPVModule.h"
#include "AliPHOSCPVHit.h"

//==============================================================================
//                              AliPHOSCPVModule
//==============================================================================

ClassImp(AliPHOSCPVModule)

//______________________________________________________________________________

AliPHOSCPVModule::AliPHOSCPVModule(void)
{
  //
  // Allocate an array of hits
  //

  if ( NULL==(fHits         =new TClonesArray("AliPHOSCPVHit",100)) ) {
    Error("CPV","Can not create array of hits per track");
    exit(1);
  }
}

//______________________________________________________________________________
AliPHOSCPVModule::AliPHOSCPVModule(const AliPHOSCPVModule & module)
{
  // Copy constructor
  module.Copy(*this);
}

//____________________________________________________________________________
AliPHOSCPVModule & AliPHOSCPVModule::operator= (const AliPHOSCPVModule &module)
{
  module.Copy(*this);
  return (*this);
}

//______________________________________________________________________________
void AliPHOSCPVModule::Copy(AliPHOSCPVModule & module) const
{
  // Copy *this onto module
  // It takes care about copying array of hits fHits

  // Copy all first
  if(this != &module) {
    ((TObject*) this)->Copy((TObject&)module);
    module.fHits          = fHits;
  }
}

//______________________________________________________________________________

AliPHOSCPVModule::~AliPHOSCPVModule(void)
{
  Clear();
}

//______________________________________________________________________________

void AliPHOSCPVModule::Clear(Option_t *opt)
{
// Clear hit information

  fHits          -> Clear(opt);
}

//______________________________________________________________________________

void AliPHOSCPVModule::AddHit(Int_t shunt, Int_t track, TLorentzVector p, Float_t *xy, Int_t ipart)
{
  //
  // Add this hit to the hit list in CPV detector.
  //

  TClonesArray &lhits = *(TClonesArray *)fHits;
  new(lhits[fHits->GetEntriesFast()]) AliPHOSCPVHit(shunt,track,p,xy,ipart);
}

//______________________________________________________________________________

void AliPHOSCPVModule::Print(Option_t *opt)
{
  //
  // Print AliPHOSCPVModule information.
  // options:  'p' - print hits in the module
  //

  Int_t nhits,hit;
  if (strcmp(opt,"p")==0) {
    printf ("CPV module has %d hits\n",nhits=fHits->GetEntriesFast());
    for (hit=0;hit<nhits;hit++) {
      AliPHOSCPVHit *cpvHit = (AliPHOSCPVHit*)fHits->UncheckedAt(hit);
      cpvHit->Print();
    }
  }
}

//______________________________________________________________________________

void AliPHOSCPVModule::MakeBranch(char *title,Int_t i)
{
  //
  // Create a new branch for a EMC or CPV module #i in the current Root Tree
  //

  char branchname[10];
  sprintf(branchname,"%s%d",title,i);
  gAlice->TreeH()->Branch(branchname,&fHits, 1000);
}

//_____________________________________________________________________________
void AliPHOSCPVModule::SetTreeAddress(char *title, Int_t i)
{
  //
  // Set branch address for the Hits Tree for a CPV or EMC module #i
  //

  TBranch *branch;
  char branchname[20];
  TTree *treeH = gAlice->TreeH();
  if (treeH){
    sprintf(branchname,"%s%d",title,i);
    branch = treeH->GetBranch(branchname);
    if (branch) branch->SetAddress(&fHits);
  }
}
