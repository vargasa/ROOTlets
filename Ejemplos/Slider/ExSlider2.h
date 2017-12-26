// -*- mode: c++ -*- 
//____________________________________________________________________ 
//  
// $Id$ 
// Author: Andrés Vargas 
// Update: 2013-06-05 16:41:31-0500
// Copyright: 2013 (C) Andrés Vargas
//
#ifndef ___ExSlider2
#define ___ExSlider2
#ifndef ROOT_TGFrame
#include "TGFrame.h"
#endif

#ifndef ROOT_TRootEmbeddedCanvas
#include "TRootEmbeddedCanvas.h"
#endif

#ifndef ROOT_TCanvas
#include "TCanvas.h"
#endif

#ifndef ROOT_TEllipse
#include "TEllipse.h"
#endif

#ifndef ROOT_TGTripleSlider
#include "TGTripleSlider.h"
#endif

#ifndef ROOT_TGClient
#include "TGClient.h"
#endif

#include "RQ_OBJECT.h"
#include "TROOT.h"

class ExSlider2 : public TGMainFrame
{
private:
  TRootEmbeddedCanvas *Lienzo;
  TEllipse *Borde;
  TEllipse *Circulo;
  TCanvas *ApLienzo;
  TGTripleHSlider *MiSlider;
  Float_t R;
public:
  ExSlider2();
  virtual ~ExSlider2() {}
  void MoverPunto();
  void ModificarArco();

  ClassDef(ExSlider2,0) // Example Slider 2
};

#endif
//____________________________________________________________________ 
//  
// EOF
//
