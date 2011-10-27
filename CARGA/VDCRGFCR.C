#include <INCVIDEO.H>
void *VIDEO_super_alloc (unsigned Tamanho,INT2 Modo);

VD_VOID VIDEO_freecarga(VD_VOID)
{
 IDE_TABREFERDODA *work, *worktab;

 

 if (VIDEO_tabela_doda)
    {
     VIDEO_free_alloc_parametros(VIDEO_tabela_doda);
     VIDEO_tabela_doda = VD_NULO;
    }

 if (VIDEO_tabela_carga)
    {
     VIDEO_free_alloc_parametros(VIDEO_tabela_carga);
     VIDEO_tabela_carga = VD_NULO;
    }

 if (!VIDEO_bufparamarq)
    return;

 work = VIDEO_bufparamarq->bufdodas;

 while(work->nome)
  {
   if (strcmp(VIDEO_mome_dummy_file,work->reduzido))
      {
       if ((work->tipo == 1 || work->tipo == 3) && work->buffer)
           VIDEO_free_alloc_parametros(work->buffer);

       worktab = work +1;

       while(worktab->nome && work->buffer)
        {
         if (worktab->buffer == work->buffer)
             worktab->buffer = VD_NULO;
         ++worktab;
        }
	  }
   ++work;
  }
 /*
  L¢gica Foi Modifcada ...
  para SuperAlloc
  */
 #ifdef MODULO_MEMORIA
 if (AdnMemLiberaPool()==ADNMEM_ERRO_NAOINIC)
    {
     VIDEO_free_alloc_parametros(VIDEO_bufparamarq);
    }
 #endif
 /*
 VIDEO_super_alloc (FALSE,FALSE);
 */


 VIDEO_bufparamarq  = VD_NULO;
 
}

