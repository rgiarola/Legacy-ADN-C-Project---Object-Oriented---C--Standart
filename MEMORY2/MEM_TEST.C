/***    Example of using memory manager to allocate extended memory
        (c) R.J.Taylor August 1993,1994
***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <alloc.h>

#include "memory.h"

#define DEPTH 30
#define WIDTH 1024

char buffs[DEPTH][WIDTH];
char strat[4][30]={"CONVENTIONAL","EXPANDED","VIRTUAL","XMS"};

int farmemcmp (void far *s1,void far *s2,unsigned n) {
    while (n--) if (*(((byte far*)s1)++)!=*(((byte far*)s2)++)) return -1;
    return 0;
}

void main (void) {

    int j,i;
    mem_hand a;
    byte far *p;
    ulong initial_free=coreleft();

    /***    Load up our 60Kb buffer with junk from the first meg
    ***/
    for (i=0;i<DEPTH;i++) {
        p=MK_FP(random(32767)*2,random(32767)*2);
        memcpy((byte *)buffs[i],(byte *)p,WIDTH);
    }

    /***    Loop, allocating each memory type in turn, then reading it back
            to check it went down OK
    ***/
    for (j=0;j<4;j++) {

        /** Set strategy to (whatever) only
        **/
        i=strat[j][1];
        strat[j][1]=0;
        setXMstrat(strat[j]);
        strat[j][1]=i;

        /** Indicate where we're trying to allocate
        **/
        printf("\n\nAttempting to allocate from %s ...\n",strat[j]);

        /** Allocate 100 lines of 1280 bytes each
        **/
        a=xalloc(WIDTH,DEPTH);

        if (a) {
            /***    If we got a buffer
            ***/
            printf("Got it! [Overhead=%lu bytes]   ",initial_free-coreleft());
            printf("mem_type() returns: [%s]\n",mem_type(a));
            printf("Writing junk... \n");

            /***    Write our junk buffer
            ***/
            for (i=0;i<DEPTH;i++){

                if (!xput((byte far*)buffs[i],i,a)) {
                    printf("Couldn't write %d         \n",i);
                } else {
                    printf("\rWrote %d        ",i);
                }

            }

            printf("\n");

            /***    Read it back
            ***/
            for (i=0;i<DEPTH;i++){

                if (!(p=xget(i,a))) {
                    printf("Couldn't read %d              \n",i);
                } else {
                    if (farmemcmp(p,(byte far*)buffs[i],WIDTH)==0) {
                        printf("\rRead %d ok         ",i);
                    } else {
                        printf("\rError reading %d!  \n",i);
                    }
                }
            }

        } else {

            printf("Couldn't allocate this resource\n");

        }

        /***    Free the buffer
        ***/
        xfree(a);
    }
}
