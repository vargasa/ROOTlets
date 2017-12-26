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

#include "WMainIP.h"

int IP()
{
  WMainIP *App = new WMainIP();
  return 0;
}

#ifndef __CINT__
int main(int argc, char** argv)
{
  TApplication IPApp("IPApp", &argc, argv);
  int retVal = IP();
  IPApp.Run();
  return retVal;
}
#endif /*__CINT__*/

//____________________________________________________________________ 
//  
// EOF
//
