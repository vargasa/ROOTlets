/************************************************
 * Copyright: 2013 (C) Andrés Vargas            *
 * All rights reserved                          *
 * For the licensing terms see:                 * 
 * https://www.gnu.org/licenses/gpl-2.0.html    *
 ***********************************************/

#ifndef __CINT__
#ifndef ROOT_TApplication
#include "TApplication.h"
#endif 
#endif /*__CINT__*/

#include "CaidaLibreGui.h"

int Aplicacion()
{
  CaidaLibreGui *APP = new CaidaLibreGui();
  return 0;
}

#ifndef __CINT__
int main(int argc, char** argv)
{
  TApplication AplicacionApp("AplicacionApp", &argc, argv);
  int retVal = Aplicacion();
  AplicacionApp.Run();
  return retVal;
}
#endif /*__CINT__*/

//____________________________________________________________________ 
//  
// EOF
//
