/* 
 * File:   myhelpers.h
 * Author: ga98wab
 *
 * Created on 16. Mai 2014, 14:58
 */

#ifndef MYHELPERS_H
#define	MYHELPERS_H

#ifdef	__cplusplus
extern "C" {
#endif

#if (defined(__AVR_ATmega644__ )) // begin Atmega stuff
/**
 * not defined in AVR-Toolchain 
 */
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

#include "AvroraPrint.h"

#define PRINTSTRING(m) printStr(m) ///< String printing if AVR Simulator is targeted
#define PRINTSTRINGINT(m,i) printStr(m); printInt16(i) ///< String and int printing if AVR Simulator is targeted
#define PRINTCHAR(c) printChar(c) ///< Char printing if AVR Simulator is targeted

/**
 * Errormessage 
 */
#define ERRMSG "das stimmt noch nicht"


#else // end Atmega stuff

#define PRINTSTRING(m) printf("%s",m) ///< String printing if normal PC is targeted
#define PRINTSTRINGINT(m,i) printf("%s%d",m,i) ///< String and int printing if normal PC is targeted
#define PRINTCHAR(c) printf("%c",c) ///< Char printing if normal PC is targeted

/**
 * a nice Errormessage :) 
 */
#define ERRMSG "\n~~~~~~~~~~~~~~~.++.~~~~~~~~~~~~~~~\nGroß ist seines Laufes Schnelle;\nAber ach, die Kammerschwelle\nIst ihm äußerst hinderlich.\nkurz gesagt: das stimmt noch nicht\n(frei nach Willhelm Busch)\n~~~~~~~~~~~~~~~.++.~~~~~~~~~~~~~~~\n"

#endif 


#ifdef	__cplusplus
}
#endif

#endif	/* MYHELPERS_H */

