//____________________________________________________________________
//
// Example Slider 2
// 

//____________________________________________________________________ 
//  
// $Id$ 
// Author: Andrés Vargas
// Update: 2013-06-05 16:41:40-0500
// Copyright: 2013 (C) Andrés Vargas
//
#ifndef ___ExSlider2
#include "ExSlider2.h"
#endif

#ifndef ROOT_TMath
#include "TMath.h"
#endif


//____________________________________________________________________
ClassImp(ExSlider2);

//____________________________________________________________________
ExSlider2::ExSlider2()
{
  // Default constructor
  TGMainFrame *Ventana = new TGMainFrame(gClient->GetRoot());
  Ventana->SetWindowName("Ejemplo Slider");
  Ventana->SetWMSizeHints(300,300,300,300,0,0);

  TGLayoutHints *Centrar = new TGLayoutHints(kLHintsExpandX|
					     kLHintsExpandY|
					     kLHintsCenterX|
					     kLHintsCenterY,5,5,5,5);
  
  
  Lienzo = new TRootEmbeddedCanvas("ECanvas",Ventana,400,400);
  ApLienzo = Lienzo->GetCanvas();
  ApLienzo->Range(-10,-10,10,10);

  R = 5.0;

  Borde = new TEllipse(0.0,0.0,R,R,0,360);
  Borde->SetFillColor(0);
  Borde->SetFillStyle(0);
  Borde->SetNoEdges();
  Borde->Draw();
  
  Circulo = new TEllipse(5.0,0.0,0.5,0.5,0,360);
  Circulo->SetFillColor(4);
  Circulo->Draw();

  MiSlider = new TGTripleHSlider(Ventana);
  MiSlider->SetRange(0.0,360.0);
  MiSlider->SetPosition(0.0,360.0);

  MiSlider->Connect("PointerPositionChanged()","ExSlider2",
		    this,"MoverPunto()");
  MiSlider->Connect("PositionChanged()","ExSlider2",
		    this,"ModificarArco()");
  // MiSlider->Connect("PositionChanged()","ExSlider2",
  // 		    this,"MoverPunto()");

  
  Ventana->AddFrame(Lienzo,Centrar);
  Ventana->AddFrame(MiSlider, new TGLayoutHints(kLHintsExpandX,5,5,5,5));
  
  Ventana->MapSubwindows();
  Ventana->Resize();
  Ventana->MapWindow();
}
//____________________________________________________________________ 
void ExSlider2::MoverPunto(){
  Circulo->SetX1(R*cos(MiSlider->GetPointerPosition()*TMath::Pi()/180));
  Circulo->SetY1(R*sin(MiSlider->GetPointerPosition()*TMath::Pi()/180));
  Circulo->Draw();
  ApLienzo->Update();
}
//____________________________________________________________________ 
void ExSlider2::ModificarArco(){
  Borde->SetPhimax(MiSlider->GetMaxPosition());
  Borde->SetPhimin(MiSlider->GetMinPosition());
  Borde->Draw();
  ApLienzo->Update();
}


//____________________________________________________________________ 
//  
// EOF
//
