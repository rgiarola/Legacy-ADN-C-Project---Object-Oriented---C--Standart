#include <INCVIDEO.H>

char *CTREE_posicao_arq(arquivo,serv,buffer_arq)
int  arquivo;
int  serv;
char *buffer_arq;
{
 IDE_ARQUIVOS *work_ifil;
 INT2         tmpfil,ret;
 IDE_INDEX    *work_indice;
 char         *buffer_rec,
              *buffer,
              restaura_posicao_erro = FALSE;
 DWORD        posicao;

#ifdef CTREE_MULTI_USER
#define CTREE_NUM_BUFFER 2
#else
#define CTREE_NUM_BUFFER 1
#endif

 tmpfil    = CTREE_tmpfil(arquivo);
 work_ifil = CTREE_ifilend(arquivo);
 ATIVA_BUF_DADOS;
 buffer_rec = CTREE_filbuf(arquivo);

 if (serv)
	{
	 if (VIDEO_ALLOC_MEM(buffer,CTREE_NUM_BUFFER*work_ifil->dreclen+
								sizeof(DWORD)) == VD_NULO)
		{
		 return(VD_NULO);
		}

	 buffer += sizeof(DWORD);
	 VIDEO_movbloco(buffer,buffer_rec,work_ifil->dreclen);
#ifdef CTREE_MULTI_USER
	 VIDEO_movbloco(buffer+work_ifil->dreclen,buffer_rec+work_ifil->dreclen*2,
											  work_ifil->dreclen);
#endif

     buffer -= sizeof(DWORD);
     CDWORD(buffer) = DATABASE_CurrentFileOffset(tmpfil);
    }
  else
	{
     if (buffer_arq)
        {
         buffer = buffer_arq;

         posicao = CDWORD(buffer);
         buffer += sizeof(DWORD);

         if (posicao)
            {
             if (DATABASE_SetRecord(tmpfil,posicao,buffer,work_ifil->dreclen) ||
                 DATABASE_ReReadRecord(tmpfil,buffer_rec))
                restaura_posicao_erro = TRUE;
            }

         VIDEO_movbloco(buffer_rec,buffer,work_ifil->dreclen);

#ifdef CTREE_MULTI_USER
         VIDEO_movbloco(buffer_rec+work_ifil->dreclen*2,
                        buffer+work_ifil->dreclen,
                        work_ifil->dreclen);
#endif

         VIDEO_FREE_ALLOC_MEM(buffer_arq);

         if (restaura_posicao_erro)
            return(VD_NULO);

        } // Fim de (IF) Buffer

    } // Fim de POPARQ

 return(buffer);
}

           


