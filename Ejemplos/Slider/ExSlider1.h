// -*- mode: c++ -*- 
//____________________________________________________________________ 
//  
// $Id$ 
// Author: Andrés Vargas
// Update: 2013-06-05 16:41:31-0500
// Copyright: 2013 (C) Andrés Vargas
//
#ifndef ___ExSlider1
#define ___ExSlider1

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

#ifndef ROOT_TGSlider
#include "TGSlider.h"
#endif

#ifndef ROOT_TGClient
#include "TGClient.h"
#endif

#include "RQ_OBJECT.h"
#include "TROOT.h"

class ExSlider1 : public TGMainFrame
{
private:
  TRootEmbeddedCanvas *Lienzo;
  TEllipse *Borde;
  TEllipse *Circulo;
  TCanvas *ApLienzo;
  TGHSlider *MiSlider;
  Float_t R;
public:
  ExSlider1();
  virtual ~ExSlider1() {}
  void MoverPunto();

  ClassDef(ExSlider1,0) // Example Slider 1
};

#endif

//____________________________________________________________________ 
//  
// EOF
//
