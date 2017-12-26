//____________________________________________________________________
//
// Cantidad de Movimiento
// 

//____________________________________________________________________ 
//  
// $Id$ 
// Author: Andrés Vargas 
// Update: 2013-06-02 16:44:33-0500
// Copyright: 2013 (C) Andrés Vargas
//
#ifndef ROOT_CantidadDeMovimiento
#include "CantidadDeMovimiento.h"
#endif

//____________________________________________________________________
ClassImp(CantidadDeMovimiento);

//____________________________________________________________________
CantidadDeMovimiento::CantidadDeMovimiento(Double_t M, Double_t vx, Double_t vy){
  fM = M; fVx = vx; fVy = vy; 
  fPx = fM*fVx; fPy = fM*fVy;
}
//____________________________________________________________________
Double_t CantidadDeMovimiento::GetP() {
  Double_t fPSquared;
  fPSquared = fPx*fPx + fPy*fPy;
  fP = sqrt(fPSquared);
  return fP;
}

//____________________________________________________________________ 
//  
// EOF
//
