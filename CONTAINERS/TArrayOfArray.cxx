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
*/
#include "TArrayOfArray.h"
#include "iostream.h"




ClassImp(TArrayOfArray)
ClassImp(TArrayOfArray_vStack)
ClassImp(TArrayOfArray_vList)
 

TArrayOfArray_vStack::TArrayOfArray_vStack()
{ 
  fIndex = 0;
  fArray = 0;
}     
  
TArrayOfArray_vStack::TArrayOfArray_vStack(const char *classname)
{
  fIndex = 0;
  fArray = 0;
  SetClass(classname);
} 

  
TArrayOfArray_vStack::~TArrayOfArray_vStack()  
{
  if (fIndex) delete fIndex;
  if (fArray) delete fArray;
} 

Bool_t TArrayOfArray_vStack::SetClass(const char * classname)
{
  //
  //set class
  if (fIndex==0) fIndex = new AliObjectArray("Int_t");
  if (fArray==0) fArray = new AliObjectArray;
  else fArray->Delete();
  return fArray->SetClass(classname);
}


void  TArrayOfArray_vStack::Clear(Option_t *)
{
  //
  // clear contents
  //if (fIndex) fIndex->Clear();
  //if (fArray) fArray->Clear();
  if (fIndex) fIndex->Resize(0);
  if (fArray) fArray->Resize(0);
  
}

void * TArrayOfArray_vStack::At(UInt_t index0, UInt_t index1)
{
  //get pointer to the object
  if ( (fIndex!=0) && (index0+1<fIndex->GetSize()) 
       && ((*((UInt_t*)(fIndex->Unchecked1DAt(index0+1)))
	    >(*((UInt_t*)(fIndex->Unchecked1DAt(index0)))+index1)) ) )
    return Unchecked1DAt(index0,index1);
  else 
    return 0;
}
void  TArrayOfArray_vStack::Dump(UInt_t index0, UInt_t index1)
{
  void * p = At(index0,index1);
  if ( (p) && fArray->GetClassInfo()) fArray->GetClassInfo()->ObjectDump(p); 
  else{    
    printf("Index %d,%d out of range\n",index0,index1);
    cout<<flush;
  }
  
}

Int_t TArrayOfArray_vStack::Resize(Int_t index, UInt_t newsize)
{ 
  //expand array with index index to newsize
  if (index<0) index = fIndex->GetSize()-2;
  if  ((UInt_t)index==(fIndex->GetSize()-2)){
    Int_t arrindex = *((Int_t*)(fIndex->At(index)));
    fArray->Resize(arrindex+newsize);
    *(Int_t*)(fIndex->At(index+1)) = arrindex+newsize;        
  }
  else{
    cout<<"out\n"; 
  }
  return 0;
}

UInt_t TArrayOfArray_vStack::Push(UInt_t size)
{
  //make new array with size  - return starting index
  if ( (fIndex==0) || (fArray==0)) return 0;
  UInt_t index1 = fIndex->GetSize(); 
  UInt_t indexa = fArray->GetSize();
  fArray->Resize(indexa+size);
  if (index1==0) { 
    fIndex->Resize(2);
    (*(Int_t*)fIndex->Unchecked1DAt(0))=0;
    (*(Int_t*)fIndex->Unchecked1DAt(1))=size;
    return 0;
  }
  else{
    fIndex->Resize(index1+1);
    (*(Int_t*)fIndex->Unchecked1DAt(index1))=indexa+size;
  }
  return index1-1;
}

Int_t TArrayOfArray_vStack::ArraySize(UInt_t index)
{
  //size if subarray with index index
  if ( (fIndex) && fIndex->GetSize()>index+1) 
    return (*(Int_t*)fIndex->Unchecked1DAt(index+1))-(*(Int_t*)fIndex->Unchecked1DAt(index));
  else 
    return 0;
}
