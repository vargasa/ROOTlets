// -*- mode: c++ -*- 
//____________________________________________________________________ 
//  
// $Id$ 
// Author: Andrés Vargas 
// Update: 2013-06-02 16:43:53-0500
// Copyright: 2013 (C) Andrés Vargas
//
#ifndef ROOT_CantidadDeMovimiento
#define ROOT_CantidadDeMovimiento
#ifndef ROOT_Velocidad
#include "Velocidad.h"
#endif

class CantidadDeMovimiento : Velocidad
{
protected:
  Double_t fM; //Variable para la Masa del cuerpo
  Double_t fPx, fPy; //Componentes 
public:
  CantidadDeMovimiento(Double_t M, Double_t vx, Double_t vy);
  virtual ~CantidadDeMovimiento() {}
  Double_t GetPx() { return fM*GetVx(); }
  Double_t GetPy() { return fM*GetVy(); }
  void SetM(Double_t m) { fM = m; }
  Double_t GetP();

  ClassDef(CantidadDeMovimiento,0) //Cantidad de Movimiento
};

#endif
//____________________________________________________________________ 
//  
// EOF
//
