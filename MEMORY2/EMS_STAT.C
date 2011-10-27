/* EMS_STAT */

#include <stdio.h>
#include "ems4c.h"

void main()
{int ErrorNumber;
 int Version;
 int FreePages;
 int TotalPages;
 int Frame;
 int Active;
 /* logon */
 printf("\n***\n*** EMS Status: Version 1.0 \n***\n");
 /* is EMM driver loaded ? */
 ErrorCheck( emsLoaded() );
 /* get EMM manager status */
 ErrorCheck( emsGetStatus() );
 /* get EMM version */
 ErrorCheck( emsVersion(&Version) );
 printf("***     EMM Version = %x.%x\n",Version/16,0x0f&Version);
 if((Version!=0x32)&&(Version!=0x40))
   {printf("Requires EMS version 3.2 or 4.0\n");
    exit(1);
   }
 /* get total number of EMS pages */
 ErrorCheck( emsGetPages(&FreePages,&TotalPages) );
 printf("***  Free EMS Pages = %d (%xH)\n",FreePages,FreePages);
 printf("*** Total EMS Pages = %d (%dH)\n",TotalPages,TotalPages);
 /* get EMS frame address */
 ErrorCheck( emsGetFrame(&Frame) );
 printf("***   Frame Address = %x:0\n",Frame);
 /* get number of active EMS handles */
 ErrorCheck( emsGetHandles(&Active) );
 printf("***  Active Handles = %d\n",Active);
 printf("***    Free handles = %d\n",255-Active);
 printf("***\n");
}

int ErrorCheck(ErrorNumber)
int ErrorNumber;
{if(ErrorNumber)
   {emsError(ErrorNumber);
    exit(1);
   }
 return(ErrorNumber);
} /* end ErrorCheck */
