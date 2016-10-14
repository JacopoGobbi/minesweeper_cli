#include <stdio.h>

/* STANDARD, BIANCO, ROSSO, VERDE, ARANCIO, BLU, VIOLA, CELESTE, GRIGIO, ROSSOCHIARO, VERDECHIARO, GIALLO, CELESTE, ROSA, AZZURRO
	SOTTOLINEATO, LAMPEGGIANTE, NEROSUGRIGIO, LAMPCOLORE, SOTTCOLORE, RIGA(ROSSA-VERDE-ARANCIO-BLU-VIOLA-AZZURRO) */


#define STANDARD		"\x1b[0m"

#define BIANCO			"\x1b[1m"

#define SOTTOLINEATO	"\x1b[4m"
#define LAMPEGGIANTE	"\x1b[5m"

#define BIANCONERO	 	"\x1b[7m"

#define ROSSO			"\x1b[31m"
#define VERDE			"\x1b[32m"
#define ARANCIO			"\x1b[33m"
#define BLU				"\x1b[34m"
#define VIOLA			"\x1b[35m"
#define CELESTE			"\x1b[36m"
#define GRIGIO			"\x1b[90m"
#define ROSSOCHIARO		"\x1b[91m"
#define VERDECHIARO		"\x1b[92m"  
#define GIALLO			"\x1b[93m"
#define BLUINO			"\x1b[94m"
#define ROSA			"\x1b[95m"
#define AZZURRO			"\x1b[96m"

#define LAMPGRIGIO		"\x1b[90;5m"
#define LAMPBIANCO		"\x1b[1;5m"
#define LAMPROSSO		"\x1b[31;5m"
#define LAMPVERDE		"\x1b[32;5m"
#define LAMPARANCIO		"\x1b[33;5m"
#define LAMPBLU			"\x1b[34;5m"
#define LAMPVIOLA		"\x1b[35;5m"
#define LAMPCELESTE	    "\x1b[36;5m"
#define LAMPROSSOCHIARO	"\x1b[91;5m"
#define LAMPVERDECHIARO	"\x1b[92;5m"
#define LAMPGIALLO		"\x1b[93;5m"
#define LAMPBLUINO		"\x1b[94;5m"
#define LAMPROSASTRO	"\x1b[95;5m"
#define LAMPAZZURRO		"\x1b[96;5m"

#define SOTTBIANCO		"\x1b[4;1m"
#define SOTTGRIGIO		"\x1b[90;4m"
#define SOTTROSSO		"\x1b[31;4m"
#define SOTTVERDE		"\x1b[32;4m"
#define SOTTARANCIO		"\x1b[33;4m"
#define SOTTBLU			"\x1b[34;4m"
#define SOTTVIOLA		"\x1b[35;4m"
#define SOTTCELESTE	"\x1b[36;4m"
#define SOTTROSSOCHIARO	"\x1b[91;4m"
#define SOTTVERDECHIARO	"\x1b[92;4m"
#define SOTTGIALLO		"\x1b[93;4m"
#define SOTTBLUINO		"\x1b[94;4m"
#define SOTTROSA		"\x1b[95;4m"
#define SOTTAZZURRO		"\x1b[96;4m"

#define RIGAROSSA		"\x1b[41m"
#define RIGAVERDE		"\x1b[42m"
#define RIGAARANCIO	"\x1b[43m"
#define RIGABLU		"\x1b[44m"
#define RIGAVIOLA		"\x1b[45m"
#define RIGAAZZURRO	"\x1b[46m"
