#include <INCVIDEO.H>

VD_VOID VIDEO_ADMEM_organiza(VD_VOID)
{
#if defined(__VIDEO_ADMEM_CARGA_PARAMETROS)
 register VIDEO_ADMEM_DESCRITOR
                      *cont1 = VIDEO_ADMEM_parametros->VIDEO_ADMEM_area_mem,
                      *cont2;
 register WORD        cont3 = 0,
                      cont4;

 for (;(((char *) cont1) < VIDEO_ADMEM_parametros->VIDEO_ADMEM_base) &&
              (cont3 < VIDEO_ADMEM_parametros->VIDEO_ADMEM_ct_stack);
      cont1++)
      if (!(cont1->endvar))
         {
          for (cont2 = cont1 + 1;((char *) cont2) <
                           VIDEO_ADMEM_parametros->VIDEO_ADMEM_base;cont2++)
               if (cont2->endvar)
                  {
                   VD_movbloco(cont1,cont2,sizeof(VIDEO_ADMEM_DESCRITOR));
                   ++cont3;
                   cont2->endvar = VD_NILL(char *);
                   break;
                  }
         }
        else 
           ++cont3;

VIDEO_ADMEM_parametros->VIDEO_ADMEM_topo =
                   (VIDEO_ADMEM_parametros->VIDEO_ADMEM_area_buffer +
                   (VIDEO_ADMEM_TAM_AREA_DEFAULT - 1));
cont1 = VIDEO_ADMEM_parametros->VIDEO_ADMEM_area_mem;
for (;cont3;cont3--,cont1++)
    {
     if (PTR_CAST(char,PTR_CAST(char,cont1->end)+(cont1->tam)-1) !=
                                   VIDEO_ADMEM_parametros->VIDEO_ADMEM_topo)
         VD_copbloco(VIDEO_ADMEM_parametros->VIDEO_ADMEM_topo -
                    (cont1->tam) + 1,cont1->end,cont1->tam);
     VIDEO_ADMEM_parametros->VIDEO_ADMEM_topo -= cont1->tam,
     *(cont1->endvar) = cont1->end = VIDEO_ADMEM_parametros->VIDEO_ADMEM_topo
                                     + 1;
    }
 VIDEO_ADMEM_parametros->VIDEO_ADMEM_num_tab =
 VIDEO_ADMEM_parametros->VIDEO_ADMEM_ct_stack;

#else
 register VIDEO_ADMEM_DESCRITOR *cont1 = VIDEO_ADMEM_area_mem,
                                *cont2;
 register unsigned INT2          cont3 = 0,
                                cont4;

 for (;(((char *) cont1) < VIDEO_ADMEM_base) && (cont3 < VIDEO_ADMEM_ct_stack);
      cont1++)
      if (!(cont1->endvar))
         {
          for (cont2 = cont1 + 1;((char *) cont2) < VIDEO_ADMEM_base;cont2++)
               if (cont2->endvar)
                  {
                   memcpy(cont1,cont2,sizeof(VIDEO_ADMEM_DESCRITOR));
                   ++cont3;
                   cont2->endvar = VD_NILL(char *);
                   break;
                  }
         }
        else 
           ++cont3;

VIDEO_ADMEM_topo = (VIDEO_ADMEM_area_buffer +
                   (VIDEO_ADMEM_TAM_AREA_DEFAULT - 1));
cont1 = VIDEO_ADMEM_area_mem;
for (;cont3;cont3--,cont1++)
    {
     if (PTR_CAST(BYTE,PTR_CAST(BYTE,cont1->end) + (cont1->tam) -1)
        != VIDEO_ADMEM_topo)
         VD_copbloco(VIDEO_ADMEM_topo - (cont1->tam) + 1,cont1->end,cont1->tam);
     VIDEO_ADMEM_topo -= cont1->tam,
     *(cont1->endvar) = cont1->end = VIDEO_ADMEM_topo + 1;
    }
 VIDEO_ADMEM_num_tab = VIDEO_ADMEM_ct_stack;
#endif
}
