/*
**                ---  emm_test.c ---
**
**  EXAMPLE CODE: The program tests each of the EMM4C library functions, and
**  exercises the page to frame mapping function by generating random mapping
**  requests. To run, type:
**
**            EMM_TEST <Pages> <Iterations> <MinSize> <MaxSize>
**
*/

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include "emm4c.h"

#define MANAGED_PAGES  50
#define NUMBER_HANDLES 25
#define NUMBER_SLOTS   25
#ifndef FALSE
#define FALSE 0
#define TRUE !FALSE
#endif

#define BYTE unsigned char
#define WORD unsigned int

int ManagedPages;
int ManagedHandles = NUMBER_HANDLES;
int NumberSlots = NUMBER_SLOTS;
int NumberLaps;
unsigned int MinSize;
unsigned int MaxSize;

struct StateTag
{int  Handle;     /* returned handle */
 WORD Size;       /* size in bytes */
 char Mark;       /* mark character ('A' to 'Z') */
} State[NUMBER_SLOTS];

WORD NbrAlloc = 0;        /* number emmAlloc() calls */
WORD NbrFree = 0;         /* number emmFree() calls */
WORD MinAlloc = 0x7fff;   /* smallest allocation */
WORD MaxAlloc = 0;        /* largest allocation */
WORD AvgAlloc = 0;        /* average allocation size */
int Seed = 54321;

#define MAKE_FAR_PTR(seg,off) ((void far *)(((unsigned long)(seg)<<16)|(unsigned)(off)))

void main(argc,argv)
int argc;
char *argv[];
{int i, k;        /* loop counters */
 char c;
 int Lap;         /* main loop counter */
 int Slot;        /* state slot [index] */
 int Code;        /* EMM function return code */
 char far *FarCharPtr;  /* generic far character pointer */
 int far *FarIntPtr;    /* generic far integer pointer */
 WORD FreePages = 0;
 WORD FreeParas = 0;
 /* begin */
 puts("***");
 puts("*** EMM_TEST: Version 1.0");
 puts("***");
 if(argc!=5)
   {puts("Usage: EMM_TEST <Pages> <Iterations> <MinSize> <MaxSize>");
    puts("where:");
    puts("        <Pages> = # pages to manage");
    puts("   <Iterations> = # emmAlloc() / emmFree() calls");
    puts("      <MinSize> = Minimum allocation size (bytes)");
    puts("      <MaxSize> = Maximum allocation size (bytes)");
    exit(1);
   }
 /* fetch & verify parameters */
 if(!Range(argv[1],&ManagedPages,1,MANAGED_PAGES,"Page")) exit(2);
 if(!Range(argv[2],&NumberLaps,1,1000,"Iteration")) exit(2);
 if(!Range(argv[3],&MinSize, 1,65534,"MinSize")) exit(2);
 if(!Range(argv[4],&MaxSize, (1+MinSize),65535,"MaxSize")) exit(2);
 /* echo parameters */
 printf("***       Pages = %d (%d KB)\n",ManagedPages,(16*ManagedPages));
 printf("***  Iterations = %d\n",NumberLaps);
 printf("***    Min Size = %u bytes\n",MinSize);
 printf("***    Max Size = %u bytes\n",MaxSize);
 puts("***");
 puts("Initializing...");
 for(i=0;i<NumberSlots;i++)
   {State[i].Handle = -1;
    State[i].Size = 0;
    State[i].Mark = '@';
   }
 srand(Seed);
 CheckError( emmInit(ManagedPages,ManagedHandles) );
 printf("Ready to start test. Type any key...");
 while( !kbhit() );
 putchar( getchar() );
 /* start test */
 for(Lap=1;Lap<=NumberLaps;Lap++)
   {/* user cancels ? */
    if(kbhit())
       {printf("\nUSER cancels...");
        break;
       }
    /* allocate if no buffers currently allocated */
    if(NbrAlloc==NbrFree)
      {/* allocate another EMS buffer */
       Slot = Allocate();
       if(Slot>=0)
         {printf("(%d) Allocating %u bytes (%d paragraphs)\n",
           Lap,State[Slot].Size,(State[Slot].Size+15)/16);
         }
      }
    else if((NbrAlloc-NbrFree)==NumberSlots)
      {/* free an EMS buffer */
       Slot = Frees();
       if(Slot>=0)
         {printf("(%d) Freeing %u bytes\n",Lap,State[Slot].Size);
          State[Slot].Size = 0;
         }
      }
    else
      {/* decide to allocate or free */
       i = Random(100);
       if(i<=52)
         {/* allocate 52% of the time */
          Slot = Allocate();
          if(Slot>=0)
            {printf("(%d) Allocating %u bytes (%d paragraphs)\n",
               Lap,State[Slot].Size,State[Slot].Size/16);
            }
         }
       else
         {/* free 48% of the time */
          Slot = Frees();
          if(Slot>=0)
            {printf("(%d) Freeing %u bytes\n",Lap,State[Slot].Size);
             State[Slot].Size = 0;
            }
         }
      }
   } /* end for(Lap) */
 /* all done */
 DumpSlots();
 printf("NbrAlloc=%u NbrFree=%u\n",NbrAlloc,NbrFree);
 printf("MinAlloc=%u MaxAlloc=%u AvgAlloc=%u\n",MinAlloc,MaxAlloc,AvgAlloc);
 emmPages(&FreePages,&FreeParas);
 printf("FreePages=%d FreeParas=%u\n",FreePages,FreeParas);
 PageDump(FALSE);
 CheckError( emmDone() );
} /* end main */


int FindFreeSlot()
{int i;
 for(i=0;i<NumberSlots;i++) if(State[i].Handle<0) return(i);
 return(-1);
} /* end FindFreeSlot */


int ChooseSlot()
{int i;
 int List[NUMBER_SLOTS];
 int Count = 0;
 /* put all active slots in list */
 for(i=0;i<NumberSlots;i++) if(State[i].Handle>=0)
    {List[Count++] = i;
    }
 /* choose slot at random */
 if(Count==0) return(-1);
 i = Random(Count);
 return( List[i] );
} /* end ChooseSlot */


int Allocate()
{int i, k;
 int Slot;
 int Code;
 WORD Size;             /* size of buffer to allocate */
 char Mark;             /* mark character */
 int Handle;            /* handle returned from emmAlloc() */
 WORD Segment;          /* segment value return from emmLock() */
 WORD Offset;           /* offset value returned from emmLock() */
 char far *FarCharPtr;  /* generic far character pointer */
 int Page;
 int Dummy;
 float Ratio;
 /* find a free slot */
 Slot = FindFreeSlot();
 if(Slot<0)
   {printf("*** Allocate: No slots available...\n");
    return(-1);
   }
 /* choose a size */
 Size = MinSize + Random(MaxSize - MinSize);
 /* compute minimum & maximum allocations */
 if(Size>MaxAlloc) MaxAlloc = Size;
 if(Size<MinAlloc) MinAlloc = Size;
#if 0
 printf("*** Allocate: Request to allocate %u bytes\n",Size);
#endif
 /* allocate EMS page(s) */
 Handle = emmAlloc(Size);
 if(Handle<0)
   {/* could not allocate! */
    printf("ERROR allocating %u bytes\n",Size);
    return(-1);
   }
 else
   {/* allocation is successful */
    NbrAlloc++;
    /* update average allocation size */
    Ratio = (float)(NbrAlloc-1) / (float)NbrAlloc;
    AvgAlloc = (int) ( Ratio*(float)AvgAlloc + (float)Size/(float)NbrAlloc );
    /* save stats in state variable struct */
    State[Slot].Handle = Handle;
    State[Slot].Size = Size;
    /* select a Mark & record it */
    Mark = 'A' + Random(26);
    State[Slot].Mark = Mark;
    /* get EMS buffer address */
    Code = emmLock(Handle,&Segment);
    if(Code==0)
      {/* save Mark in EMS buffer */
       FarCharPtr = MAKE_FAR_PTR(Segment,0);
       for(k=0;k<Size;k++) *FarCharPtr++ = Mark;
       emmUnlock(Handle);
      }
    else CheckError(Code);
    return(Slot);
   }
} /* end Allocate */


int VerifyMark(Slot)
int Slot;
{int i;
 WORD k;
 WORD Size;
 char c;
 int Handle;
 char Mark;
 int Code;
 WORD Segment;
 WORD Offset;
 char far *FarCharPtr;
 /* begin */
 Handle = State[Slot].Handle;
 if(Handle<0) return(0);
 Mark = State[Slot].Mark;
 Size = State[Slot].Size;
 Code = emmLock(Handle,&Segment);
 if(Code==0)
   {/* check Mark in EMS buffer */
    FarCharPtr = MAKE_FAR_PTR(Segment,0);
    /* verify mark */
    for(k=0;k<Size;k++)
      {c = *FarCharPtr;
       /*if(k<5) printf("%c",c);*/
       if(c != Mark)
         {printf("ERROR: Found mark = '%c' not '%c' (index=%d Segment=%x Size=%d) \n",
            *FarCharPtr,Mark,k,Segment,Size);
          emmUnlock(Handle);
          DumpSlots();
          emmDone();
          exit(1);
         }
       /* next byte */
       FarCharPtr++;
      } /* end for(k) */
    /* mark is verified */
    emmUnlock(Handle);
   } /* end if(Code) */
 return(0);
} /* end VerifyMark */


int Frees()
{int k;
 int Slot;
 int Code;
 int Handle;
 char Mark;
 WORD Size;
 char far *FarCharPtr;
 /* choose slot to free at random */
 Slot = ChooseSlot();
 if(Slot>=0)
   {
    Handle = State[Slot].Handle;
    VerifyMark(Slot);
    Code = emmFree(Handle);
    NbrFree++;
    if(Code==0)
      {State[Slot].Handle = -1;
       State[Slot].Mark = '#';
       return(Slot);
      }
    else CheckError(Code);
   }
 return(-1);
} /* end Free */


int DumpSlots()
{int i;
 int Handle;
 int Code;
 WORD k;
 WORD Size;
 WORD Segment;
 WORD Offset;
 WORD Limit;
 char far *FarCharPtr;
 int LastSlot = 0;
 /* begin */
 for(i=NumberSlots-1;i>0;i--) if(State[i].Handle != -1)
    {LastSlot = i;
     break;
    }
 printf("***** ManagedPages=%d (%d KB) ***** \n",ManagedPages,16*ManagedPages);
 printf("Slot Handle  Size  Mark  Data...\n");
 printf("==== ======  ====  ====  ====\n");
 for(i=0;i<=LastSlot;i++)
   {
    printf("%4d %5d %6u    %c   ",
      i,State[i].Handle,State[i].Size,State[i].Mark);
    Handle = State[i].Handle;
    if(Handle>=0)
      {Code = emmLock(Handle,&Segment);
       if(Code==0)
         {/* get pointer to EMS block */
          FarCharPtr = MAKE_FAR_PTR(Segment,0);
          Size = State[i].Size;
          Limit = Size;
          if(Limit>17) Limit = 17;
          for(k=0;k<Limit;k++)
             {printf("%c",*FarCharPtr);
              FarCharPtr++;
             }
          /* display last character in allocation */
          FarCharPtr = MAKE_FAR_PTR(Segment,Size-1);
          printf("...%c",*FarCharPtr++);
          emmUnlock(Handle);
         }
      } /* end if */
    printf("\n");
   }
 return(0);
} /* end DumpSlot */

int CheckError(Code)
int Code;
{if(Code<0)
  {emmError(Code);
  }
 return(Code);
}

int Random(Modulo)
WORD Modulo;
{WORD r;
 /* rand() returns [0..32767] */
 r = (WORD) rand();
 if(Modulo<=32767) return(r%Modulo);
 return( (r+r) % Modulo);
} /* end Random */

int Range(String,ValuePtr,MinValue,MaxValue)
char *String;
unsigned int *ValuePtr;
unsigned int MinValue;
unsigned int MaxValue;
{unsigned int Value;
 Value = (unsigned int) atoi(String);
 if(Value<MinValue)
   {printf("ERROR: parameter (%s) < minimum (%d)\n",String,MinValue);
    return(FALSE);
   }
 if(Value>MaxValue)
   {printf("ERROR: parameter (%s) > maximum (%d)\n",String,MaxValue);
    return(FALSE);
   }
 *ValuePtr = Value;
 return(TRUE);
} /* range */