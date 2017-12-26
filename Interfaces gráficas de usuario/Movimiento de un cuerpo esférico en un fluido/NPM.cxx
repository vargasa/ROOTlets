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

#include "WMainNPM.h"

int NPM()
{
  WMainNPM *App = new WMainNPM();
  return 0;
}

#ifndef __CINT__
int main(int argc, char** argv)
{
  TApplication NPMApp("NPMApp", &argc, argv);
  int retVal = NPM();
  NPMApp.Run();
  return retVal;
}
#endif

//____________________________________________________________________ 
//  
// EOF
//
