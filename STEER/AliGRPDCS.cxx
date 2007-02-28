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

/* $Id$ */

//-----------------------------------------------------------------
//                AliGRPDCS class
//   This class deals with the DCS related info of the GRP
//   Origin: Panos Christakoglou, UOA-CERN, Panos.Christakoglou@cern.ch
//-----------------------------------------------------------------

#include "AliGRPDCS.h"
#include "AliDCSValue.h"
#include "AliLog.h"

class TObjString;

#include <TObjArray.h>

ClassImp(AliGRPDCS)

//_______________________________________________________________
AliGRPDCS::AliGRPDCS():
  TObject(), fDCSArray(new TObjArray()) {
  // default constructor
  
}

//_______________________________________________________________
AliGRPDCS::AliGRPDCS(TObjArray *dcsArray):
  TObject(), fDCSArray(new TObjArray()) {
  // constructor
  fDCSArray = dcsArray;
}

//___________________________________________________________________________
AliGRPDCS::AliGRPDCS(const AliGRPDCS& grpDcs):
  TObject(grpDcs) {
  //copy constructor

  if (grpDcs.fDCSArray) fDCSArray = new TObjArray();
}

//_______________________________________________________________
const char* AliGRPDCS::ProcessDCS(Int_t iType) {
  // process the dcs dps
  //0:Int - 1:UInt - 2:Float - 3:String - 4:Bool
  TString fDCSDataPointValue;
  switch (iType) {
  case 0: {
    fDCSDataPointValue += ProcessInt();
    break;
  }
  case 1: {
    fDCSDataPointValue += ProcessUInt();
    break;
  }
  case 2: {
    fDCSDataPointValue += ProcessFloat();
    break;
  }
  case 3: {
    fDCSDataPointValue += ProcessString();
    break;
  }
  case 4: {
    fDCSDataPointValue += ProcessBoolean();
    break;
  }
  default: break;
  }//switch

  return fDCSDataPointValue.Data();
}

//_______________________________________________________________
const char* AliGRPDCS::ProcessInt() {
  Float_t fFDCSArraySum = 0.0, fFDCSArrayMean = 0.0;
  for(Int_t i = 0; i < fDCSArray->GetEntries(); i++) {
    AliDCSValue *v = (AliDCSValue *)fDCSArray->At(i);
    fFDCSArraySum += v->GetInt();
  }
  fFDCSArrayMean = fFDCSArraySum/fDCSArray->GetEntries();
  TString fDCSDataPointValue; fDCSDataPointValue += fFDCSArrayMean;

  return fDCSDataPointValue.Data();
}

//_______________________________________________________________
const char* AliGRPDCS::ProcessUInt() {
  Float_t fFDCSArraySum = 0.0, fFDCSArrayMean = 0.0;
  for(Int_t i = 0; i < fDCSArray->GetEntries(); i++) {
    AliDCSValue *v = (AliDCSValue *)fDCSArray->At(i);
    fFDCSArraySum += v->GetUInt();
  }
  fFDCSArrayMean = fFDCSArraySum/fDCSArray->GetEntries();
  TString fDCSDataPointValue; fDCSDataPointValue += fFDCSArrayMean;

  return fDCSDataPointValue.Data();
}

//_______________________________________________________________
const char* AliGRPDCS::ProcessFloat() {
  Float_t fFDCSArraySum = 0.0, fFDCSArrayMean = 0.0;
  for(Int_t i = 0; i < fDCSArray->GetEntries(); i++) {
    AliDCSValue *v = (AliDCSValue *)fDCSArray->At(i);
    fFDCSArraySum += v->GetFloat();
  }
  fFDCSArrayMean = fFDCSArraySum/fDCSArray->GetEntries();
  TString fDCSDataPointValue; fDCSDataPointValue += fFDCSArrayMean;

  return fDCSDataPointValue.Data();
}

//_______________________________________________________________
const char* AliGRPDCS::ProcessString() {
  TString fDCSString, fDCSTemp;
  AliDCSValue *v = (AliDCSValue *)fDCSArray->At(0);
  fDCSTemp = v->GetChar();
  for(Int_t i = 0; i < fDCSArray->GetEntries(); i++) {
    AliDCSValue *v1 = (AliDCSValue *)fDCSArray->At(i);
    fDCSString = v1->GetChar();
    if(fDCSTemp != fDCSString) AliFatal("DCS data point value changed within the run!!!");
  }
  TString fDCSDataPointValue = fDCSString;

  return fDCSDataPointValue.Data();
}

//_______________________________________________________________
const char* AliGRPDCS::ProcessBoolean() {
  Bool_t fDCSBool = kTRUE, fDCSTemp = kTRUE;
  AliDCSValue *v = (AliDCSValue *)fDCSArray->At(0);
  fDCSTemp = v->GetBool();
  for(Int_t i = 0; i < fDCSArray->GetEntries(); i++) {
    AliDCSValue *v1 = (AliDCSValue *)fDCSArray->At(i);
    fDCSBool = v1->GetBool();
    if(fDCSTemp != fDCSBool) AliFatal("DCS data point value changed within the run!!!");
  }
  TString fDCSDataPointValue = fDCSBool;

  return fDCSDataPointValue.Data();
}
