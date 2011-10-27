/* ----------------------------------------------------------------------------
   BACKUP E RESTORE

                       Controle de backup e restore do sistema

   ---------------------------------------------------------------------------- */

/* ============================================================================
   Funcao faz um check do drive especificado
   ============================================================================ */
#include <INCVIDEO.H>
#include <padroes.h>

VIDEO_valida_drive(campos,flagmens,param)
VIDEO_CAMPO_TELA  **campos;
BOOLEAN           flagmens;
VIDEO_NUCLEO_SERV **param;
{
 int driveatual,drivebusca;

 driveatual = getdisk();

 VIDEO_VISUAL_flag_erro = FALSE;
 VIDEO_VISUAL_flag_int  = TRUE;
 VIDEO_VISUAL_velha_int24 = getvect(0X24);
 setvect(0X24,VIDEO_VISUAL_nova_int24);
 drivebusca = (*(campos)->buffer_binario)&0XCF) - 'A';
 VIDEO_VISUAL_flag_int  = FALSE;
 setdisk(drivebusca);

 if (VIDEO_VISUAL_flag_erro || (getdisk() != drivebusca))
    {
     VIDEO_VISUAL_flag_erro = FALSE;
     VIDEO_VISUAL_flag_int  = TRUE;
     setvect(0X24,VIDEO_VISUAL_velha_int24);
     if (flagmens)
         VIDEO_mostra_mens_erro(VIDEO_drive_invalido,TRUE);
     setdrive(driveatual)
     return(TRUE);
    }
 setdrive(driveatual);
 return(FALSE);
}


VIDEO_valida_diretorio(campos,flag,param)
VIDEO_CAMPO_TELA  **campos;
BOOLEAN           flag;
VIDEO_NUCLEO_SERV **param;
{
 int  driveatual,ret;
 char path_orig[100];

 driveatual = getdisk();
 strcpy(path_orig,VIDEO_montagem_path);
 path_orig[0] = 'A' + driveatual;
 getcurdir(0, path_orig+3);

 VIDEO_VISUAL_flag_erro = FALSE;
 VIDEO_VISUAL_flag_int  = TRUE;
 VIDEO_VISUAL_velha_int24 = getvect(0X24);
 setvect(0X24,VIDEO_VISUAL_nova_int24);
 VIDEO_VISUAL_flag_int  = FALSE;

 ret =   strlen((*campos)->buffer_binario) ?
         chdir((*campos)->buffer_binario) ||
         VIDEO_VISUAL_flag_erro            : FALSE;

 chdir(path_orig);

 VIDEO_VISUAL_flag_erro = FALSE;
 VIDEO_VISUAL_flag_int  = TRUE;
 setvect(0X24,VIDEO_VISUAL_velha_int24);

 if (ret)
    {
     if (flagmens)
         VIDEO_mostra_mens_erro(VIDEO_caminho_invalido,TRUE);
     return(TRUE);
    }

 return(FALSE);
}


VIDEO_valida_arq_backup(campos,flagmens,param)
VIDEO_CAMPO_TELA  **campos;
BOOLEAN           flagmens;
VIDEO_NUCLEO_SERV **param;
{
 char *arquivo = (*campos)->buffer_binario;
 int  ret      = FALSE;

 if (strcmp(arquivo,VIDEO_nome_central) &&
     strcmp(arquivo,VIDEO_nome_contas))
    {
     if (VIDEO_existe_arquivo(arquivo))
        {
         if (flagmens)
            {
             char buffer[200];
             sprintf(buffer,VIDEO_mensagem_remover,arquivo);
             if (VD_telaconf((80-strlen(buffer))/2,10,buffer,PD_COR_01) == TRUE)
                {
                 VIDEO_VISUAL_flag_erro = FALSE;
                 VIDEO_VISUAL_flag_int  = TRUE;
                 VIDEO_VISUAL_velha_int24 = getvect(0X24);
                 setvect(0X24,VIDEO_VISUAL_nova_int24);
                 VIDEO_VISUAL_flag_int  = FALSE;
                 VIDEO_unlink(arquivo);

                 VIDEO_VISUAL_flag_int  = TRUE;
                 setvect(0X24,VIDEO_VISUAL_velha_int24);
                 if (VIDEO_VISUAL_flag_erro)
                    {
                     VIDEO_VISUAL_flag_erro = FALSE;
                     sprintf(buffer,VIDEO_VISUAL_erro_delecao,arquivo);
                     VIDEO_mostra_mens_erro(buffer,TRUE);
                     return(TRUE);
                    }
                }
            }
        }
     return(TRUE);
    }

 if (flagmens)
     VIDEO_mostra_mens_erro(VIDEO_arquivo_invalido,TRUE);

 return(TRUE);
}

