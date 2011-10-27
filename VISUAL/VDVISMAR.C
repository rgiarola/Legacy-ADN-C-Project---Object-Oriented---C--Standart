#include <INCVIDEO.H>

INT2 VISUAL_menu_arquivos(arquivo)
char *arquivo;
{
 int              ret,coli,lini;
 VIDEO_IMAGEMTELA *imagem;

 VIDEO_VISUAL_flag_int  = TRUE;
 VIDEO_VISUAL_flag_erro = FALSE;

 if (!VIDEO_CRG_carrega_objeto(&VIDEO_VISUAL_imagem_arquivos,1))
    return(FALSE);

 if (!VIDEO_CRG_prepara_tela(&VIDEO_VISUAL_imagem_arquivos))
    return(FALSE);

 imagem = PTR_CAST(VIDEO_TABCRGTELA,
                   VIDEO_VISUAL_imagem_arquivos.strtelacrg)->telasai->imagens;

 coli = imagem->colf - 24;
 lini = imagem->linf;

 VIDEO_CRG_libera_tela(&VIDEO_VISUAL_imagem_arquivos);

 VD_PUSHWIN(1,80,1,25);

 VIDEO_CRG_display_imagem(&VIDEO_VISUAL_imagem_arquivos,1,0);

 do
  {
   VIDEO_VISUAL_flag_int  = TRUE;
   VIDEO_VISUAL_flag_erro = FALSE;
   if ((ret = VIDEO_CRG_display_imagem(&VIDEO_VISUAL_imagem_arquivos,1,2))
       == VD_MTTECLA(VD_NULO,ALT_O))
      {
       char path_orig[100],**tabela;
       int  ret,cont,cont2,driveatual,drivebusca;
       struct ffblk arquivos;

       driveatual = getdisk();
       strcpy(path_orig,VIDEO_montagem_path);
       path_orig[0] = 'A' + driveatual;
       getcurdir(0, path_orig+3);

       VIDEO_VISUAL_flag_int  = FALSE;
       if (strlen(VD_GETEND(BDISP_texto1,char)))
           ret = chdir(VD_GETEND(BDISP_texto1,char));
         else
           ret = FALSE;

       if (VIDEO_VISUAL_flag_erro)
           ret = TRUE;

       if (ret)
          {
           chdir(path_orig);
           sprintf(path_orig,VIDEO_VISUAL_caminho_invalido,
                   VD_GETEND(BDISP_texto1,char));

           VIDEO_mostra_mens_erro(path_orig,TRUE);
           VIDEO_VISUAL_flag_int  = TRUE;
           continue;
          }

       ret = FALSE;

       if (!strlen(VD_GETEND(BDISP_texto2,char)))
           strcpy(VD_GETEND(BDISP_texto2,char),"*.OUT");

       if ((*(VD_GETEND(BDISP_texto1,char)+1) == ':') &&
           ((VD_GETBUF(BDISP_texto1,char)&0XCF) != path_orig[0]))
          {
           drivebusca = (VD_GETBUF(BDISP_texto1,char)&0XCF) - 'A';
           setdisk(drivebusca);
           if (getdisk() != drivebusca || VIDEO_VISUAL_flag_erro)
              {
               setdisk(driveatual);
               chdir(path_orig);
               sprintf(path_orig,VIDEO_VISUAL_caminho_invalido,
                       VD_GETEND(BDISP_texto1,char));
               VIDEO_mostra_mens_erro(path_orig,TRUE);
               VIDEO_VISUAL_flag_int  = TRUE;
               continue;
              }
          }

       cont = 0;
       if (!findfirst(VD_GETEND(BDISP_texto2,char),&arquivos,FA_ARCH))
          {
           do
            {
             ++cont;
            }while(!findnext(&arquivos));

           if (VIDEO_VISUAL_flag_erro)
              {
               VIDEO_VISUAL_flag_int  = TRUE;
               break;
              }

           if (VIDEO_ALLOC_MEM(tabela,cont*sizeof(char *)+2) == VD_NULO)
              {
               setdisk(driveatual);
               chdir(path_orig);
               VIDEO_mostra_mens_erro_alloc(ALOCACAO_VISUAL_3);
               VIDEO_VISUAL_flag_int  = TRUE;
               break;
              }

           VIDEO_setmem(tabela,cont*sizeof(char *)+2,0);
           cont = 0;
           if (findfirst(VD_GETEND(BDISP_texto2,char),&arquivos,FA_ARCH) ||
               VIDEO_VISUAL_flag_erro)
              {
               setdisk(driveatual);
               chdir(path_orig);
               VIDEO_FREE_ALLOC_MEM(tabela);
               VIDEO_VISUAL_flag_int  = TRUE;
               break;
              }
           do
            {
             if (VIDEO_ALLOC_MEM(*(tabela+cont),(strlen(arquivos.ff_name)+1)) == VD_NULO)
                {
                 setdisk(driveatual);
                 chdir(path_orig);
                 for (cont2 = 0;cont2 < cont;cont2++)
                      VIDEO_FREE_ALLOC_MEM(*(tabela+cont2));
                 VIDEO_FREE_ALLOC_MEM(tabela);
                 VIDEO_mostra_mens_erro_alloc(ALOCACAO_VISUAL_4);
                 cont = 0;
                 VIDEO_VISUAL_flag_int  = TRUE;
                 break;
                }
             strcpy(*(tabela+cont),arquivos.ff_name);
             ++cont;
            }while(!findnext(&arquivos));

           if (!cont)
               break;

           if (cont > 1 ||
               (cont == 1 && strcmp(*tabela,VD_GETEND(BDISP_texto2,char))))
              {
               ret = VIDEO_VISUAL_menu_objetos(tabela,cont,coli,lini,13);
               VD_POPWIN();
              }
            else
              ret = 1;

           setdisk(driveatual);
		   chdir(path_orig);
           VIDEO_VISUAL_flag_int  = TRUE;

           if (ret)
              {
               int tamanho;
               strcpy(arquivo,VD_GETEND(BDISP_texto1,char));
               tamanho = strlen(arquivo);
               if (tamanho && *(arquivo+tamanho-1) != '\\')
                   strcat(arquivo,"\\");
               strcat(arquivo,*(tabela+ret-1));
               ret = TRUE;
              }

           for (cont2 = 0;cont2 < cont;cont2++)
                VIDEO_FREE_ALLOC_MEM(*(tabela+cont2));

		   VIDEO_FREE_ALLOC_MEM(tabela);
          }

	   if (!cont)
          {
           setdisk(driveatual);
           chdir(path_orig);
           sprintf(path_orig,VIDEO_VISUAL_nao_ha_arquivos,
                             VD_GETEND(BDISP_texto2,char));
           VIDEO_mostra_mens_erro(path_orig,TRUE);
           VIDEO_VISUAL_flag_int  = TRUE;
           continue;
          }

       if (ret)
           break;
      }
    else
      {
       ret = FALSE;
       break;
      }
  }while(TRUE);

 VD_POPWIN();

 VIDEO_VISUAL_flag_int  = TRUE;
 VIDEO_VISUAL_flag_erro = FALSE;
 return(ret);
}



