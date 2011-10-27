#include <windows.h>
#include <string.h>
#include <dos.h>
#include <stdlib.h>

#define CTPERM
#include "ctstdr.h"		/* standard i/o header 		*/
#undef   EXTERN
#define  EXTERN /* */
#include "ctoptn.h"		/* c-tree configuration options */
#include "cterrc.h"		/* c-tree error codes		*/
#include "ctstrc.h"		/* c-tree data structures	*/
#include "ctgvar.h"		/* c-tree global variables	*/
#ifndef CTBOUND
#include "ctcomm.h"
#endif






unsigned long far pascal _export BPtr2Lng(LPSTR p);
void movstr(LPSTR p, int len);
unsigned long far pascal _export BPtr2Str(LPSTR p);

/* undocumented function */
/* undocumented function */
extern int FAR PASCAL SysErrorBox(LPSTR msg,LPSTR title, WORD lButton,
												WORD mButton, WORD rButton);

#define SEB_OK       1
#define SEB_CANCEL   2
#define SEB_YES      3
#define SEB_NO       4
#define SEB_RETRY    5
#define SEB_ABORT    6
#define SEB_IGNORE   7

#define SEB_DEFAULT 0x8000

HANDLE hBasWnd;

int FAR PASCAL LibMain( HANDLE hInstance, WORD wDataSeg, WORD wHeapSize,
								LPSTR lpCmdLine )
{
  hBasWnd = hInstance;        // save instance for ViewCtreeError()
	return( TRUE );
}





unsigned long far pascal _export BPtr2Lng(LPSTR p)
{
// Converts a pointer passed in from BASIC to a long.  This is intended to
// be used with IFIL pointers or the like

	return((unsigned long)p);
}

unsigned long far pascal _export BPtr2Str(LPSTR p)
{
	int poff;
	int sel;
	int len;
	unsigned char far *pstr;
	_fmemcpy((char far *)&poff,p,2);
	sel = HIWORD(p);
	pstr = MK_FP(sel,poff);
	_fmemcpy((char far *)&len,pstr,2);
	movstr(pstr,len);
	return(pstr);
}

void movstr(LPSTR p, int len)
{
	int i;
	LPSTR ptr1;
	LPSTR ptr2;

   ptr1 = p;
   ptr2 = p + 2;
   for ( i = 0; i < len; i++)
		*ptr1++ = *ptr2++;
	p[i] = '\0';	                  
}
