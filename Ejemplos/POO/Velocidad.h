// -*- mode: c++ -*- 
//____________________________________________________________________ 
//  
// $Id$ 
// Author: Andrés Vargas 
// Update: 2013-06-02 16:26:54-0500
// Copyright: 2013 (C) Andrés Vargas
//
#ifndef ROOT_Velocidad
#define ROOT_Velocidad
#include "TROOT.h"

class Velocidad
{
private:
  protected:
  Double_t fVx; //Componente horizontal
  Double_t fVy; //Componente vertical
  public:
  Velocidad(Double_t vx,Double_t vy);
  virtual ~Velocidad() {}
  Double_t GetVx() { return fVx; }
  Double_t GetVy() { return fVy; }
  void SetVx(Double_t vx) { fVx = vx; }
  void SetVy(Double_t vy) { fVy = vy; }

  ClassDef(Velocidad,0) //Velocidad

};

#endif
//____________________________________________________________________ 
//  
// EOF
//
