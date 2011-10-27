/* ----------------------------------------------------------------------------
   NVI
   Estudos e Amplia‡”es
   C¢digo ADN

   ADNBuildPtr
   ADNEmmInicializa
   ADNEmmPaginasLivres
   ADNEmmAlocaPaginas
   ADNEmmMapPaginas
   ADNEmmGetFrameAdres
   ADNEmmDesalocaPaginas

   ADNEmmMapMemoriaTam
   ADNEmmMapLeitura

   ADNEmmCalcEnd

   ADNEmm200LockPaginas
   ---------------------------------------------------------------------------- */
#ifndef MODULO_INCLUSAO
#include  <INCVIDEO.H>
//#include <dos.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <mem.h>
#include <adnmem.h>
#endif
char vADNEmmInicON   =FALSE,
     vADNEmmPagCount ,
     vADNEmmSegCount ,
     vADNEmmSegMax   ;

MAP_MEMORY_LIST *vADNEmmMapMemory;

/* ----------------------------------------------------------------------------
   Routine to convert a segment:offset pair to a far ptr.
   ---------------------------------------------------------------------------- */
char far *ADNBuildPtr (segment, offset)

    unsigned int segment;
    unsigned int offset;
{
    char far *ptr;
    unsigned long AddSeg, AddOff;
    /*
    Address   = segment;
    Address   = Address << 16;
    Address  += offset;
     */
    /*
    ptr = (char far *)((char __seg *)(segment)+ (char __near *)(offset));
     */
    AddSeg = segment;
    AddOff = offset;

    ptr = (char *)(unsigned long) (((unsigned long)AddSeg << 16) + AddOff);
    //printf ("\n PTR(%p)",(char *)(ptr));

    return ((char far *) ptr);
}



/* ----------------------------------------------------------------------------
   Function which determines whether EMM device driver
   is installed.
   ---------------------------------------------------------------------------- */
char ADNEmmInicializa(void)

{
    union REGS input_regs, output_regs;
    struct SREGS segment_regs;
    char *EMM_device_name = "EMMXXXX0";
    char *int_67_device_name_ptr;

    if (vADNEmmInicON)
       {
        return (-1);    // J  Inicializado ...
       }

    /*--------------------------------------------------------*/
    /* AH = DOS get interrupt vector function.                */
    /*--------------------------------------------------------*/
    input_regs.h.ah = 0x35;

    /*--------------------------------------------------------*/
    /* AL = EMM interrupt vector number.                      */
    /*--------------------------------------------------------*/
    input_regs.h.al = EMM_INT;
    intdosx (&input_regs, &output_regs, &segment_regs);

    /*--------------------------------------------------------*/
    /* Upon return ES:0Ah points to location where            */
    /* device name should be.                                 */
    /*--------------------------------------------------------*/
    int_67_device_name_ptr = ADNBuildPtr(segment_regs.es, 0x0A);

    /*--------------------------------------------------------*/
    /* Compare memory with EMM device name.                   */
    /*--------------------------------------------------------*/
    if (memcmp (EMM_device_name, int_67_device_name_ptr,
                                   DEVICE_NAME_LENGTH) == 0)
       {
        vADNEmmInicON = TRUE;
       }

 /*
   N„o Ser  Necess rio ..
 if (vADNEmmInicON)
    {
     vADNEmmPagCount=   // Ser  Necess rio ???
     vADNEmmSegCount= 0;
     
     // C lcula Tamanho do No Segmentos
     if ((vADNEmmSegMax=ADNEmmMapMemoriaTam())<0)
        return (-1);


     // Alloca Estrutura de Controle de Segmentos
     if ((vADNEmmMapMemory =
            malloc (sizeof (MAP_MEMORY_LIST)*vADNEmmSegMax))==NULL)
        {
         return (-2);
        }
                                                  djkasdjfk aqui
     // Inicializa Estrura de MAP de Segmentos de
     if ((ret = ADNEmmMapLeitura(MapMemory))<0)
        {
         return (-3);
        }

    }
 */

 return (vADNEmmInicON);
}


/*
// Aten‡„o: N„o Funciona no WIN 9X
//          N„o ‚ Permitido efetuar o Lock de Mem¢ria
*/
void * ADNEmm200LockPaginas(int handle)
{
 unsigned long XMM_Control = 0;      //  Stores address of XMM control function
 unsigned int  EMBSeg,
               EMBOff,
               RetVal;
/*
 // L¢gica 1
 void (*XMSControl)(void);

 _AX = 0X4310;
 geninterrupt(0x2f);
 XMSControl = ADNBuildPtr(_BX,_ES);
 printf ("\n Pointer XMS %p",XMSControl);getch();

 _AH = 0x0C;
 _DX = handle;
 // geninterrupt (EMM_INT);
 (*XMSControl)();

 if (_AX==0)
    return (NULL);
  else
    return (ADNBuildPtr(_DX,_BX));
  */

 // L¢gica 2
    asm {
    push    es                          // Compatibilizar com BC
    mov ax, 0x4310                      // Get Control Function
    int 0x2f
    mov word ptr [XMM_Control], bx      // Standard Intel LE
    mov word ptr [XMM_Control+2], es    // Segment: Offset notation
	pop	es
    }

    asm {
	mov	dx, handle
    mov ah, 0x0c
    call    [XMM_Control]
	mov	RetVal, ax
	mov	EMBSeg, dx
	mov	EMBOff, bx
    }

 if (RetVal == 0)
    {
     return(0);
    }

 return((void *) (((unsigned long) EMBSeg << 16) + EMBOff));
}


/*------------------------------------------------------------*/
/* Function which determines if there are enough unallocated  */
/* expanded memory pages for the application.                 */
/*------------------------------------------------------------*/
char ADNEmmPaginasLivres (pages_needed,pages_free)
int pages_needed;
int *pages_free;
{
    union REGS input_regs, output_regs;
    input_regs.h.ah = GET_UNALLOCATED_PAGE_COUNT;
    int86 (EMM_INT, &input_regs, &output_regs);
    *pages_free = output_regs.x.bx;
    if (output_regs.h.ah != 0 || pages_needed > output_regs.x.bx)
        return (FALSE);
    else
        return (TRUE);
}

/*------------------------------------------------------------*/
/* Function which allocates expanded memory pages and passes  */
/* back to the main EMM handle.                               */
/*------------------------------------------------------------*/
char ADNEmmAlocaPaginas (pages_needed,emm_handle_ptr)
    int pages_needed;
    unsigned int *emm_handle_ptr;
{
    union REGS input_regs, output_regs;
    input_regs.h.ah = ALLOCATE_PAGES;
    input_regs.x.bx = pages_needed;
    int86 (EMM_INT, &input_regs, &output_regs);
    if (output_regs.h.ah == 0) {
        *emm_handle_ptr = output_regs.x.dx;
        return (TRUE);
    }
    else
        return (FALSE);
}

/*------------------------------------------------------------*/
/* Routine to map a logical page to a physical page.          */
/*------------------------------------------------------------*/
char ADNEmmMapPaginas (emm_handle, physical_page,logical_page)
    unsigned int emm_handle;
    int physical_page;
    int logical_page;
{
    union REGS input_regs, output_regs;
    input_regs.h.ah = MAP_PAGES;
    input_regs.h.al = physical_page;
    input_regs.x.bx = logical_page;
    input_regs.x.dx = emm_handle;
    int86 (EMM_INT, &input_regs, &output_regs);
    if (output_regs.h.ah == 0)
        return (TRUE);
    else
        return (FALSE);
}


/*------------------------------------------------------------*/
/* Routine which gets the page frame base address from EMM.   */
/*------------------------------------------------------------*/
char ADNEmmGetFrameAdres (pf_ptr)
    char **pf_ptr;
{
    union REGS input_regs, output_regs;
    input_regs.h.ah = GET_PAGE_FRAME;
    int86 (EMM_INT, &input_regs, &output_regs);
    if (output_regs.h.ah != 0)       /* check EMM status */
        return (FALSE);
    else
       *pf_ptr = ADNBuildPtr(output_regs.x.bx,0);

    return (TRUE);
}

/*------------------------------------------------------------*/
/* Routine to release all expanded memory pages allocated     */
/* by an EMM handle.                                          */
/*------------------------------------------------------------*/

char ADNEmmDesalocaPaginas (emm_handle)
    unsigned int emm_handle;
{
    union REGS input_regs, output_regs;
    input_regs.h.ah = DEALLOCATE_PAGES;
    input_regs.x.dx = emm_handle;
    int86 (EMM_INT, &input_regs, &output_regs);
    if (output_regs.h.ah == 0)
        return (TRUE);
    else
        return (FALSE);
}


int  ADNEmmMapMemoriaTam(void)                  // Retorna o Numero de Segmentos
{
 union REGS input_regs, output_regs;
 input_regs.x.ax = 0x5801;
 int86 (EMM_INT, &input_regs, &output_regs);

 if (output_regs.h.ah != 0)
     return (-1);

 return (output_regs.x.cx);
}

int  ADNEmmMapLeitura (MAP_MEMORY_LIST *Map) // Retorna o Numero de Segmentos
{
/*
 input_regs.x.ax = 0x5800;
 input_regs.x.si = FP_SEG (Map);
 input_regs.x.di = FP_OFF (Map);
 int86 (EMM_INT, &input_regs, &output_regs);

 if (!output_regs.h.ah)
    {
     return (output_regs.x.cx); // N£mero de Entradas
    }
 return (output_regs.h.ah * -1);
 */
 _AX = 0x5800;
 _ES = FP_SEG (Map);
 _DI = FP_OFF (Map);

 geninterrupt (EMM_INT);
 if (!_AH)
    {
     return (_CX); // N£mero de Entradas
    }

 return (_AH * -1);
}

