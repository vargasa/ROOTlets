/************************************************
 * Copyright: 2013 (C) Andrés Vargas            *
 * All rights reserved                          *
 * For the licensing terms see:                 * 
 * https://www.gnu.org/licenses/gpl-2.0.html    *
 ***********************************************/

#ifndef __NPM__
#define __NPM__

#include "TGClient.h"
#include "RQ_OBJECT.h"
#include "TGButton.h"
#include "TGFrame.h"
#include "TEllipse.h"
#include "TArrow.h"
#include "TTimer.h"
#include "TRootEmbeddedCanvas.h"
#include "TCanvas.h"
#include "TGNumberEntry.h"
#include "TGComboBox.h"
#include "TGraph.h"
#include "TGLabel.h"
#include "TMath.h"

class WMainNPM {
  RQ_OBJECT("WMainNPM");

  //Elementos de la interfaz
  TGMainFrame *fMain; //Ventana principal
  TRootEmbeddedCanvas *ECGraph; //Lienzo para las gr\'aficas
  TCanvas *CGPos;
  TRootEmbeddedCanvas *ECGPos; //Lienzo para la animaci\'on
  TCanvas *CGraph;
  TGNumberEntry *NEMass; //Entrada num\'erica para la masa
  TGNumberEntry *NERadio; // para el radio
  TGNumberEntry *NERho; // para la densidad $\rho$
  TGNumberEntry *NECPull; // para el coeficiente de arrastre
  TGNumberEntry *NEGr; // para la gravedad
  TGNumberEntry *NEDt; // para el intervalo de tiempo
  TGNumberEntry *NEX0; // para la posici\'on inicial en x 
  TGNumberEntry *NEY0; // para la posici\'on inicial en y
  TGNumberEntry *NEV0; // para la rapidez inicial
  TGNumberEntry *NEAlpha; // para el \'angulo del lanzamiento
  TGComboBox *CBRho; //Lista de selecci\'on para la densidad $\rho$
  TGComboBox *CBGr; //Lista de selecci\'on para la gravedad $g$
  TGraph *GGraph; //Gr\'afica
  TEllipse *EBody; //Elipse que representar\'a el cuerpo
  TGTextButton *TBPlay; //Bot\'on para iniciar y pausar la simulaci\'on
  TGTextButton *TBClear; //Bot\'on para limpiar la ejecuci\'on
  TGCheckButton *CHBRastro; //Opci\'on para mostrar (o no) el rastro
  TGCheckButton *CHBVVel; //Opci\'on para mostrar (o no) el vector $\vec{v}$
  TGCheckButton *CHBVForce; //Opci\'on para mostrar (o no) los vectores de fuerza
  //Flechas que representan el vector velocidad
  //y sus componentes
  TArrow *AV,*AXP,*AYP;
  //Flechas que representan las fuerzas que act\'uan 
  //sobre el cuerpo
  TArrow *AW,*AFe,*AFrx,*AFry,*AFr; 

  //Variables para la soluci\'on num\'erica
  TTimer *Cont; //Contador
  Double_t m; //$m$ = masa del cuerpo
  Double_t g; //$g$ = valor de la aceleraci\'on gravitacional
  Double_t Rho; //$\rho$ = densidad del medio
  Double_t R; //$R$ = Radio del cuerpo
  Double_t c; //$c$ = coeficiente de arrastre
  Double_t Alpha; //$\alpha$ = \'angulo de lanzamiento
  Double_t FW; //peso
  Double_t FFe; //Fuerza de empuje
  Double_t FFrx; //Componente en x de la fricci\'on
  Double_t FFry; //Componente en y de la fricci\'on
  Double_t FFr; //Fuerza de fricci\'on (Resultante)
  Double_t X; // $X(t)$ = posici\'on en el eje $x$ del centro de masa
  Double_t XP; // $\dot{X(t)}$ = componente en $x$ de la velocidad
  Double_t Y; // $Y(t)$ =  posici\'on en el eje $y$ del centro de masa
  Double_t YP; // $\dot{Y(t)}$ = componente en $x$ de la velocidad
  Double_t t; // tiempo
  Double_t dt; // paso (intervalo de tiempo)
  Double_t V; // magnitud de $\vec{v}$
  Double_t p; // magnitud de $\vec{p}$
  Double_t U; //Energ\'ia potencial
  Double_t K; //Energ\'ia cin\'etica
  Double_t E; //Energ\'ia mec\'anica

  //Objetos auxiliares
  Double_t *GX,*GY; //Apuntadores a variables dependiente e independiente del gr\'afico
  Int_t IsActive; //Variable auxiliar para determinar el estado de la simulaci\'on

  //Funciones
  Double_t Mod(Double_t CX,Double_t CY); //funci\'on que calcula el m\'odule de un vector bidimensional
  Double_t XPP(Double_t, Double_t); //$\ddot{X(t)}$
  Double_t YPP(Double_t, Double_t); //$\ddot{Y(t)}$

  //Funciones auxiliares
  void Disable();
  void Enable();
  
public:
  
  WMainNPM();
  ~WMainNPM(){};

  //Slots
  void CBGrSelected(Int_t Opt);
  void NERadioValueSet();
  void NEY0ValueSet();
  void NEX0ValueSet();
  void CBXGraphSelected(Int_t);
  void CBYGraphSelected(Int_t);
  void CBRhoSelected(Int_t);
  void TBClearClicked();
  void TBExitClicked();
  void TBPlayClicked();
  void DoDraw();

  ClassDef(WMainNPM,0);

};
#endif //__NPM__//

#ifdef __CINT__
#include "WMainNPM.cxx"
#endif
