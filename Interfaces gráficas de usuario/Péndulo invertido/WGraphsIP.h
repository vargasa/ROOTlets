/************************************************
 * Copyright: 2013 (C) Andrés Vargas            *
 * All rights reserved                          *
 * For the licensing terms see:                 * 
 * https://www.gnu.org/licenses/gpl-2.0.html    *
 ***********************************************/

#ifndef _IP_WGraphsIP
#define _IP_WGraphsIP

#include "TGClient.h"
#include "RQ_OBJECT.h"
#include "TGFrame.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TRootEmbeddedCanvas.h"

class WGraphsIP {

  RQ_OBJECT("WGraphsIP");

private:
  TGTransientFrame *TFGraphs;
  void CreateGraphs();
  TGraph *GEnergyU,*GEnergyK2,*GEnergyK1,*GEnergyE,*GPhaseBase,*GPhi,*GPhiP;
  TRootEmbeddedCanvas *CEnergy,*CPhaseBase,*CPhi,*CPhiP;

public:
  WGraphsIP(const TGWindow *p,const TGWindow *main);
  ~WGraphsIP();
  TGraph* GetGraphEnergyU(){return GEnergyU;}
  TGraph* GetGraphEnergyK2(){return GEnergyK2;}
  TGraph* GetGraphEnergyK1(){return GEnergyK1;}
  TGraph* GetGraphEnergyE(){return GEnergyE;}
  TGraph* GetGraphPhaseBase(){return GPhaseBase;}
  TGraph* GetGraphPhi(){return GPhi;}
  TGraph* GetGraphPhiP(){return GPhiP;}
  TCanvas* GetCanvasEnergy(){return CEnergy->GetCanvas();}
  TCanvas* GetCanvasPhaseBase(){return CPhaseBase->GetCanvas();}
  TCanvas* GetCanvasPhi(){return CPhi->GetCanvas();}
  TCanvas* GetCanvasPhiP(){return CPhiP->GetCanvas();}
  void SetHidden(Bool_t Opt);
  void Hidden(){ SetHidden(kTRUE); Emit("Hidden()"); } //*SIGNAL*//
  void CleanGraphs();

  ClassDef(WGraphsIP,0);

};

#endif /*_IP_WGraphsIP*/

#ifdef __CINT__
#include "WGraphsIP.cxx"
#endif
//____________________________________________________________________ 
//  
// EOF
//
