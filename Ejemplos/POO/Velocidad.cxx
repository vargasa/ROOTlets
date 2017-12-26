//____________________________________________________________________
//
// Velocidad
// 

//____________________________________________________________________ 
//  
// $Id$ 
// Author: Andrés Vargas 
// Update: 2013-06-02 16:26:59-0500
// Copyright: 2013 (C) Andrés Vargas
//
#ifndef ROOT_Velocidad
#include "Velocidad.h"
#endif

//____________________________________________________________________
ClassImp(Velocidad);

//____________________________________________________________________
Velocidad::Velocidad(Double_t vx,Double_t vy)
{
  // Default constructor
  fVx = vx; fVy = vy;
}

//____________________________________________________________________ 
//  
// EOF
//
