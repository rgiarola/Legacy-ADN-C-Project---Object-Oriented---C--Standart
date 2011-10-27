#include <INCVIDEO.H>

INT2 VIDEO_inicdodabuf(VD_VOID)
{
 INT2              cont,  numbuf,
                  conttab,ret;
 IDE_TABREFERDODA *work,
                  *ptrerro;
 IDE_DODA         *dodas;
 INT2              contdoda;


 ptrerro = work  = VIDEO_bufparamarq->bufdodas;

 conttab = 0;
 // printf ("\n 7a");getch();
 while(work->nome && conttab < VIDEO_bufparamarq->numtab)
  {
   // printf ("\n 7B");getch();
   if (strcmp(VIDEO_mome_dummy_file,work->reduzido))
	  {
	   if (work->tipo == 1 || work->tipo == 3 || work->tipo == 4)
		  {
		   if ((dodas = CTREE_dodaend(work->dodainic)) == VD_NULO)
			  {
			   char buflocal[100];
               sprintf(buflocal,VIDEO_CARGA_mens_doda_inicio,
							   work->dodainic);
               VIDEO_mostra_mens_erro(buflocal,
                                      VIDEO_ERRO_doda_ini_buf_nao_encontrado);
               return(VIDEO_ERRO_doda_ini_buf_nao_encontrado);
			  }

		   if (!(dodas->fadr))
			   {
				char buflocal[100];
				numbuf = work->tipo == 1 ? MIN_BUFFERS : 1;
				if (work->tipo != 4)
				   {
                    // if ((ret=AdnMemAlocPool (work->tamanho*numbuf,
                    //                          &work->buffer))!=FALSE)
                    //   {
                        if ((work->buffer = VIDEO_alloc_parametros(
                                            work->tamanho*numbuf)) == VD_NULO)
                           {
                            VIDEO_mostra_mens_erro_alloc(ALOCACAO_INICDODABUF);

                            while(ptrerro != work)
                             {
                              if (work->tipo == 1 || work->tipo == 3)
                                  VIDEO_free_alloc_parametros(work->buffer);
                              ++ptrerro;
                             }
                            return(VIDEO_ERRO_carga_alloc_doda_buffer);
                           }
                     //  }

                    if (!VIDEO_enddodabuf(work,PTR_CAST(TEXT,work->buffer)))
					   {
						while(ptrerro != work)
						 {
						  if (work->tipo == 1 || work->tipo == 3)
							  VIDEO_free_alloc_parametros(work->buffer);
						  ++ptrerro;
						 }
                        return(VIDEO_ERRO_carga_end_doda_buffer);
					   }

                    VIDEO_setmem(work->buffer,work->tamanho*numbuf,0);
				   }
			   }
			 else
				work->buffer = dodas->fadr;
		  }
	  }
   ++conttab;
   ++work;
  }

 // printf ("\n 7 FIM");getch();
 return(VIDEO_inicdodaespelho());
}



