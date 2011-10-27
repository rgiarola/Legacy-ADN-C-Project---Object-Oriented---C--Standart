/*
**                ---  ems_test.c ---
**
**  EXAMPLE CODE: The program tests each of the EMS4C library functions, and
**  exercises the page to frame mapping function by generating random mapping
**  requests.
**
**  This example program (not the EMS4C library) is donated to
**  the Public Domain by MarshallSoft Computing, Inc. It is
**  provided as an example of the use of the EMS4C.
**
*/
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include "ems4c.h"

#define MAKE_FAR_PTR(seg,off) ((void far *)(((unsigned long)(seg)<<16)|(unsigned)(off)))

int RefCount[512];   /* reference count per EMS page */
int Handle = -1;     /* EMS handle */

void main()
{int i, k;        /* loop counters */
 int Count;       /* reference count in page */
 int Lap;         /* loop counter */
 int Page;        /* EMS logical page */
 int ErrorNumber; /* error number return from EMS4C */
 int Version;     /* EMS version number */
 int FreePages;   /* number of free EMS pages */
 int TotalPages;  /* total number of EMS pages */
 int Frame;       /* EMS frame number [0,1,2,3] */
 int FrameSeg;    /* Segment associated with <Frame> */
 int Active = 0;  /* number of active EMS handles */
 int AllocPages;  /* number of EMS pages to allocate */
 int Total = 0;   /* total accumulated reference count */
 int OwnedPages;  /* number of pages owned by this handle */
 char SrcArray[1];/* dummy Page Map source array */
 char DstArray[1];/* dummy Page Map destination array */
 int Result = -1; /* result variable */
 char far *FarCharPtr;  /* generic far character pointer */
 int far *FarIntPtr;    /* generic far integer pointer */
 /* is EMS driver loaded ? */
 ErrorCheck( emsLoaded() );
 printf("EMS driver is loaded\n");
 /* get EMM manager status */
 ErrorCheck( emsGetStatus() );
 printf("EMS status is OK\n");
 /* get EMM version */
 ErrorCheck( emsVersion(&Version) );
 printf("EMM Version = %x.%x\n",Version/16,0x0f&Version);
 /* get total number of EMS pages */
 ErrorCheck( emsGetPages(&FreePages,&TotalPages) );
 printf("Free EMS Pages = %d (%xH)\n",FreePages,FreePages);
 printf("Total EMS Pages = %d (%dH)\n",TotalPages,TotalPages);
 /* get # free EMS handles */
 ErrorCheck( emsGetHandles(&Active) );
 printf("Free handles = %d\n",255-Active);
 /* get EMS frame address */
 ErrorCheck( emsGetFrame(&FrameSeg) );
 printf("Frame Address = %x:0\n",FrameSeg);
 puts("Beginning EMS testing...");
 /* clear each 16K frame */
 for(i=0;i<4;i++)
   {/* make pointer to start of 16K frame */
    FarCharPtr = MAKE_FAR_PTR(FrameSeg+i*1024,0);
    /* clear 16K bytes */
    printf("Clearing frame %d at %x:0\n",i,FrameSeg+i*1024);
    for(k=0;k<16384;k++) *FarCharPtr++ = '\0';
   }
 /* allocate up to 512 pages */
 if(FreePages<512) AllocPages = FreePages;
 else AllocPages = 512;
 for(i=0;i<AllocPages;i++) RefCount[i] = 0;
 printf("Allocating %d pages\n",AllocPages);
 ErrorCheck( emsAllocate(AllocPages,&Handle) );
 printf("EMS Handle = %d\n",Handle);
 /* expect # owned pages = allocated pages */
 ErrorCheck( emsOwnedPages(Handle,&OwnedPages) );
 if(OwnedPages!=AllocPages)
   printf("WARNING: OwnedPages=%d != AllocPages=%d\n",OwnedPages,AllocPages);
 /* Free pages should now be zero */
 ErrorCheck( emsGetPages(&FreePages,&TotalPages) );
 if(FreePages!=0) printf("WARNING: Free page count %d not 0\n",FreePages);
 puts("Begin random access test...");
 for(Lap=0;Lap<(5*AllocPages);Lap++)
   {/* select frame from [0..3] */
    Frame = Random(4);
    FarIntPtr = MAKE_FAR_PTR(FrameSeg+1024*Frame,0);
    /* select page from [0..AllocPages-1] */
    Page = Random(AllocPages);
#if 0
printf("%d: Mapping page %d to frame %d\n",Lap,Page,Frame);
#endif
    /* map page */
    ErrorCheck( emsMapMemory(Frame,Page,Handle) );
    if(RefCount[Page]==0)
      {/* write 0 to page */
       Count = 0;
      }
    else
      {/* */
       Count = *FarIntPtr;
       if(Count!=RefCount[Page])
         {printf("ERROR: Found ref count %d, expected %d for page %d\n",
           Count,RefCount[Page],Page);
          break;
         }
      }
    /* increment ref count */
    Count++;
    RefCount[Page] = Count;
    *FarIntPtr = Count;
#if 0
printf("%d: RefCount[%d]=%d\n",Lap,Page,Count);
#endif
   } /* end for */
#if 0
 /* display RefCount[] array */
 for(i=0;i<AllocPages;i++)
     printf("RefCount[%d] = %d\n",i,RefCount[i]);
#endif
 for(i=0;i<AllocPages;i++) Total += RefCount[i];
 printf("Average reference count = %f\n",
   (float)Total / (float)AllocPages);
 /* save & restore mapping context */
 ErrorCheck( emsSaveMap(Handle) );
 ErrorCheck( emsRestoreMap(Handle) );
 /* free allocated pages */
 ErrorCheck( emsRelease(Handle) );
 /* display page map array size */
 ErrorCheck( emsPageMap(3,SrcArray,DstArray,&Result) );
 printf("EMS Page Map size = %d\n",Result);
 puts("Test completed\n");
} /* end main */

int ErrorCheck(ErrorNumber)
int ErrorNumber;
{if(ErrorNumber)
   {emsError(ErrorNumber);
    if(Handle>=0) emsRelease(Handle);
    exit(1);
   }
 return(ErrorNumber);
} /* end ErrorCheck */

int Random(Modulo)
int Modulo;
{int r;
 r = rand();
 return(r%Modulo);
}
