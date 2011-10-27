
int VIDEO_DISPLAY_endereca_tela(strtelacrg)
VIDEO_TABCRGTELA *strtelacrg;
{
 VIDEO_SEG_CHAVE    *segchave;
 VIDEO_IMAGEMTELA   *imagem;
 VIDEO_CAMPO_TELA   *campos;
 VIDEO_TRANSP_DADOS *transpdados;
 int                cont;

 cont = 0;
 imagem = strtelacrg->telasai->imagens;
 do
  {

   if (imagem->nmindarq)
	  {
       printf("IMAGEM %2d TAMARQ %2d ARQ %s \n",cont,
               strlen(imagem->nmindarq),imagem->nmindarq);

	  }
	else
	  {
       printf("IMAGEM %2d SEM NMINDARQ \n",cont);

	  }

   if (imagem->nmindsub)
	  {
       printf("IMAGEM %2d TAMSUB %2d SUB %s \n",cont,
               strlen(imagem->nmindsub),imagem->nmindsub);

	  }
	else
	  {
       printf("IMAGEM %2d SEM NMINDSUB \n",cont);

	  }

   if (imagem->nmindpai)
	  {
       printf("IMAGEM %2d TAMPAI %2d PAI %s \n",cont,
               strlen(imagem->nmindpai),imagem->nmindpai);

	  }
	else
	  {
       printf("IMAGEM %2d SEM NMINDPAI \n",cont);

	  }

   if (imagem->userfunc)
	  {
       printf("IMAGEM %2d TAMUSERFUNC %2d USERFUNC %s \n",cont,
               strlen(imagem->userfunc),imagem->userfunc);

	  }
	else
	  {
       printf("IMAGEM %2d SEM USERFUNC \n",cont);

	  }

   if (imagem->userserv)
	  {
       printf("IMAGEM %2d TAMUSERSERV %2d USERSERV %s \n",cont,
               strlen(imagem->userserv),imagem->userserv);

	  }
	else
	  {
       printf("IMAGEM %2d SEM USERSERV \n",cont);

	  }

   if (imagem->mensagem)
	  {
       printf("IMAGEM %2d TAMMENSAGEM %2d MENSAGEM %s \n",cont,
               strlen(imagem->mensagem),imagem->mensagem);

	  }
	else
	  {
       printf("IMAGEM %2d SEM MENSAGEM \n",cont);

	  }

   if (imagem->nomehelp)
	  {
       printf("IMAGEM %2d TAMNOMEHELP %2d NOMEHELP %s \n",cont,
               strlen(imagem->nomehelp),imagem->nomehelp);

	  }
	else
	  {
       printf("IMAGEM %2d SEM NOMEHELP \n",cont);

	  }

   if (imagem->segchave)
      {
       segchave = imagem->segchave;
       while(segchave->pointer)
        {
         printf("IMAGEM %2d POINTER %2d %20s TIPO %2d TAMANHO %2d\n",cont,
				 strlen(segchave->pointer),segchave->pointer,segchave->tipo,
                 segchave->tamanho);
         ++segchave;
        }
      }
    else
      {
       printf("IMAGEM %2d SEM SEGCHAVE \n",cont);
      }

   if (imagem->transpdados)
      {
       transpdados = imagem->transpdados;
       while(transpdados->destino)
        {
         printf("IMAGEM %2d ORIGEM %2d %20s DESTINO %2d %20s \n",cont,
				 strlen(transpdados->origem) ,transpdados->origem,
                 strlen(transpdados->destino),transpdados->destino);
         ++transpdados;
        }
      }
    else
      {
       printf("IMAGEM %2d SEN TRANSPDADOS \n",cont);
      }

   if (imagem->campos)
      {
       if (!VIDEO_DISPLAY_endereca_campos(imagem->campos->VIDEO_campos,
                                          imagem->campos->VIDEO_numcampos,
                                          strtelacrg))
          return(FALSE);
      }

   ++imagem;

  }while(++cont < strtelacrg->contimagemsai);

 return(TRUE);
}
