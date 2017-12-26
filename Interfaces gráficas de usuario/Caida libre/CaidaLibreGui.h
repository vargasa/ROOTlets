/************************************************
 * Author: Andrés Vargas <amvargash@gmail.com>  *
 * Copyright: 2013 (C) Andrés Vargas            *
 * All rights reserved                          *
 * For the licensing terms see:                 * 
 * https://www.gnu.org/licenses/gpl-2.0.html    *
 * For details see:                             *
 * https://github.com/amvargash                 *
 ***********************************************/

#ifndef CaidaLibreGui_
#define CaidaLibreGui_

#include "TGNumberEntry.h"
#include "TRootEmbeddedCanvas.h"
#include "TCanvas.h"
#include "TEllipse.h"
#include "TTimer.h"
#include "TGClient.h"
#include "RQ_OBJECT.h"

class CaidaLibreGui
{
  
  RQ_OBJECT("CaidaLibreGui");
  
private:
  TGNumberEntry *NEMasa; //Entrada Num\'erica para la masa
  TGNumberEntry *NEGravedad; //Entrada Num\'erica para la gravedad
  TGNumberEntry *NEAltura; //Entrada Num\'erica para la altura del cuerpo
  TRootEmbeddedCanvas *ECanvas; //Lienzo embebido
  TCanvas *fCanvas; //Referencia al lienzo
  TEllipse *E1; //Elipse que representar\'a el cuerpo
  TTimer *Contador; //Cron\'ometro
  void CuadrarRangoCanvas(Double_t h);
  Double_t g;   // $g$ = Aceleraci\'on gravitacional
  Double_t Y;   // $Y = Y(t)$
  Double_t YP;  // $YP = \dot{Y(t)}$
  Double_t m;   // $m$ = Masa
  Double_t h;   // $h$ = Altura Inicial
  Double_t dt;  // $dt$ = Paso (Intervalo de Tiempo)
  
public:
  CaidaLibreGui();
  ~CaidaLibreGui() {;}
  void PBPlayClicked();
  void MNumerico();
  void Exit();

  ClassDef(CaidaLibreGui,0);
};

#endif /*CaidaLibreGui_*/

#ifdef __CINT__
#include "CaidaLibreGui.cxx"
#endif

//____________________________________________________________________ 
//  
// EOF
//
