// Autogenerated Class (Source File)
// Author : G.Gavalian
// Date   : Tue Mar 27 16:46:05 EST 2007
//

#include "TCTVariable.h"
#include "TCTVector.h"
#include "TCTParticle.h"


ClassImp(TCTVariable)



TCTVariable::TCTVariable (const char *name, double value)
{
  fVarType  = CTVAR_STATIC;
  fVarValue = value;
  SetName(name);
  fCutValue_Low  = -1016.;
  fCutValue_High =  1016.;
}

TCTVariable::TCTVariable (const char *name, const char *sys_name, const char *sys_var, int type)
{
  fVarType  = CTVAR_VECTOR;
  SetName(name);
  fSystemName = sys_name;
  fSystemVar  = sys_var;
  fVarType    = type;
  fVarValue   = 0.;
  fCutValue_Low  = -1000.;
  fCutValue_High =  1000.;
}

TCTVariable::TCTVariable (const char *name, const char *oper, const char *var_1, const char *var_2)
{
  SetName(name);
  fVarType   = CTVAR_VARIABLE;
  fOperation = oper;
  fOperand_1 = var_1;
  fOperand_2 = var_2;
  fCutValue_Low  = -1000.;
  fCutValue_High =  1000.;
}

TCTVariable::~TCTVariable (){

}

//-----------------
//-----------------
//-----------------
Int_t     TCTVariable::GetStatus()
{

  if(fCutValue_Low<-1000.&&fCutValue_High>1000.) return 1;
  if(fVarValue>fCutValue_Low&&fVarValue<fCutValue_High) return 1;
  return -1;
}

Int_t     TCTVariable::SetCuts(double __low, double __high)
{
  fCutValue_Low  = __low;
  fCutValue_High = __high;
}

void  TCTVariable::Fill(TObjArray *farr, const char *system)
{
  if(fVarType==CTVAR_STATIC) return;
  TString  fsys = system;

  //_____  PARTICLE variable _________________
  if(fsys.CompareTo("PARTICLE")==0&&fVarType==CTVAR_PARTICLE){
    TCTParticle *fptr = static_cast<TCTParticle*> (farr->FindObject(fSystemName.Data()));
    if(fptr==NULL){
      fVarValue = 0.;
    } else {
      fVarValue = fptr->Get(fSystemVar.Data());
    }
  }
  //______ Vector Variable _________________
  if(fsys.CompareTo("VECTOR")==0&&fVarType==CTVAR_VECTOR){
    TCTVector *fptr = static_cast<TCTVector*> (farr->FindObject(fSystemName.Data()));
    if(fptr==NULL){
      printf("ERROR:CTVariable::Fill():: The vector (%s) can not be found\n",fSystemName.Data());
      fVarValue = -2450.;
    } else {
      fVarValue = fptr->Get(fSystemVar.Data());
    }
  }
  //_______ Variable Variable ______________
  if(fsys.CompareTo("VARIABLE")==0&&fVarType==CTVAR_VARIABLE){
    TCTVariable *fptr_1 = static_cast<TCTVariable*> (farr->FindObject(fOperand_1.Data()));
    TCTVariable *fptr_2 = static_cast<TCTVariable*> (farr->FindObject(fOperand_2.Data()));
    if(fptr_1!=NULL&&fptr_2!=NULL){
      DoOperation(fptr_1->Get(),fptr_2->Get());
    } else {
      fVarValue = -1000.;
    }
  }
}

void      TCTVariable::Print()
{
  printf("|%12s|%12s|%12s|%12.4f|%12.4f|%12.4f|\n",GetName(),fSystemName.Data(),fSystemVar.Data(),fVarValue,fCutValue_Low,fCutValue_High);
//   if(fVarType==CTVAR_STATIC){
//     printf("[%12s] | [%9.5f] | %9.5f %9.5f \n",GetName(),fVarValue,fCutValue_Low,fCutValue_High);
//   }
//   if(fVarType==CTVAR_PARTICLE){
//     printf("[%12s] | [%12s] => [%12s] | %9.5f %9.5f \n",GetName(),fSystemName.Data(),fSystemVar.Data(),fCutValue_Low,fCutValue_High);
//   }
//   if(fVarType==CTVAR_VECTOR){
//     printf("[%12s] | [%12s] => [%12s] = %9.5f | %9.5f %9.5f\n",GetName(),fSystemName.Data(),fSystemVar.Data(),fVarValue,fCutValue_Low,fCutValue_High);
//   }
//   if(fVarType==CTVAR_VARIABLE){
//     printf("[%12s] | [%12s] (%6s)  [%12s]  = %9.5f | %9.5f %9.5f\n",GetName(),fOperand_1.Data(),
// 	   fOperation.Data(),fOperand_2.Data(),fVarValue,fCutValue_Low,fCutValue_High);
//   }
  
}



void      TCTVariable::DoOperation(double v1,double v2)
{
  if(fOperation.CompareTo("add")  ==0) fVarValue = v1 + v2;
  if(fOperation.CompareTo("sub")  ==0) fVarValue = v1 - v2;
}
