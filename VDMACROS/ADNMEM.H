/* ----------------------------------------------------------------------------

   Biblioteca de Manipula‡„o
   de Mem¢ria XMS

   Alocadores
   Desalacadores
   Etc...
   ---------------------------------------------------------------------------- */
#ifndef __ADNMEM_H__
#define __ADNMEM_H__

#define EMM_INT                 0x67  /* EMM interrupt number */
#define GET_PAGE_FRAME          0x41  /* EMM get page frame */
                                      /* function number */
#define GET_UNALLOCATED_PAGE_COUNT  0x42  /* EMM get unallocated */
                                      /* page count */
                                      /* function number */
#define ALLOCATE_PAGES          0x43  /* EMM allocate pages */
                                      /* function number */
#define MAP_PAGES               0x44  /* EMM map pages */
                                      /* function number */
#define DEALLOCATE_PAGES        0x45  /* EMM deallocate pages */
                                      /* function number */
#define DEVICE_NAME_LENGTH      8     /* length of a device */
                                      /* name string */
#ifndef TRUE
#define TRUE                    1
#endif

#ifndef FALSE
#define FALSE                   0
#endif

void * ADNEmm200LockPaginas(int handle);
int    ADNEmm200UnLockPaginas(int handle);

char far
     *ADNBuildPtr           (unsigned int segment,unsigned int offset);
char  ADNEmmInicializa      (void);
char  ADNEmmPaginasLivres   (int pages_needed,int *pages_free);
char  ADNEmmAlocaPaginas    (int pages_needed,unsigned int *emm_handle_ptr);
char  ADNEmmMapPaginas      (unsigned int emm_handle,
                                      int physical_page,
                                      int logical_page);
char  ADNEmmGetFrameAdres   (char **pf_ptr);
char  ADNEmmDesalocaPaginas (unsigned int emm_handle);

typedef struct {
  unsigned  physic_page_segment,
            physic_page_number;
} MAP_MEMORY_LIST;

int   ADNEmmMapMemoriaTam   (void);
int   ADNEmmMapLeitura      (MAP_MEMORY_LIST *Map);

/* ============================================================================

   Implementa‡„o POOL de Mem¢ria

   ============================================================================ */
#define PAGINA_PADRAO DW(0X4000)        // 16Kbytes por P gina

#define ADNMEM_ERRO_NOEMM	  401		// Emm N„o Instalado
#define ADNMEM_ERRO_JAINIC	  402		// J  Inicializado
#define ADNMEM_ERRO_NAOINIC   403       // N„o Inicializado

#define ADNMEM_ERRO_POOLINIC  405		// Pool j  Incializado
#define ADNMEM_ERRO_SEMMEM	  406		// Sem Mem¢ria Suficiente
#define ADNMEM_ERRO_ALLOC	  407		// Erro de Aloca‡„o
#define ADNMEM_ERRO_MAP 	  408		// Erro Map Mem¢ria
#define ADNMEM_ERRO_PAGEFRAME 409		// Erro Map Mem¢ria

#define ADNMEM_ERRO_LIBERA    420       // Erro Libera -> Free Handle

#define ADNMEM_ERRO_ALLOCPOOL 450       // Sem Mem¢ria p/a Trabalhar
#define ADNMEM_ERRO_SEG16     451       // Erro Alloc > 64KBytes

INT2 AdnMemPreparaPool (DWORD Bytes);
INT2 AdnMemLiberaPool  (void);
INT2 AdnMemAlocPool    (DWORD Bytes, char **PonteiroAlloc);
INT2 AdnMemSituacao    (DWORD *Contador, DWORD *Maximo, DWORD *Livre);



#endif



