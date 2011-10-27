#include <INCVIDEO.H>

VD_VOID VIDEO_TELA_display_campos(campo,numcampos,param,flaguser)
VIDEO_CAMPO_TELA  *campo;
INT2               numcampos;
VIDEO_NUCLEO_SERV *param;
WORD              flaguser;
{
 VIDEO_EDITA_CAMPO        campoedit;
 char                     *buffer,*old_buffer;
 INT2                     ret,cont_campo;
 VIDEO_TABFUNCAO          *tabfuncuser;
 VIDEO_CAMPO_CONSISTENCIA *consiste;
 BOOLEAN                  dispcampo;

 for (cont_campo = 0;cont_campo < numcampos;cont_campo++,campo++)
     {
      VIDEO_campo_atual = campo;
      VIDEO_cons_atual  = campo->consiste;
      VIDEO_doda_campo  = campo->dodacampo;

      /* Dispara USER-FUNCTION ================================================*/
      if (campo->user_func)
         {
          tabfuncuser = VIDEO_funcao_tabfuncuser(campo->user_func);

          if (flaguser&VIDEO_FLAGUSER_CAMPO)
             {
              if (campo->flag_disparo&VIDEO_TELA_FDISPANT)
                  if (!tabfuncuser || !tabfuncuser->userfunc)
                     {
                      char buffer[200];
                      sprintf(buffer,VIDEO_funcao_nao_enc,campo->user_func);
                      VIDEO_mostra_mens_erro(buffer,TRUE);
                     }
                   else
                     (tabfuncuser->userfunc)(campo,VIDEO_TELA_FDISPANT,param);
             }
         }

      if (flaguser&VIDEO_FLAGVALIDA_CAMPO)
          VIDEO_TELA_busca_dadosrelacional(campo,flaguser);

      dispcampo = TRUE;

      if ((campo->status&VIDEO_EDITA_PROTEGIDO) &&
          (campo->status&VIDEO_EDITA_NAOMOSTRA))
        dispcampo = FALSE;
         else
           if (((consiste = campo->consiste) != VD_NULO) &&
               (consiste->tipocons == VIDEO_TELA_CONS_OLD_BUFFER))
             {
              old_buffer = consiste->objetocons.old_buffer;
              if (!(flaguser&VIDEO_TELA_FLAGRESETDISPLAY))
                 {
                  if (CCHAR((old_buffer+sizeof(int))) &&
                      !memcmp(campo->buffer_binario,
                              old_buffer+sizeof(int)+sizeof(char),
                              CINT(old_buffer)))
                      dispcampo = FALSE;
                 }
              }
            else
              old_buffer = VD_NULO;


      if (dispcampo)
         {
          if (VIDEO_ALLOC_MEM(buffer,campo->tamanho+1) == VD_NULO)
             {
              VIDEO_mostra_mens_erro_alloc(ALOCACAO_DISPLAY_CAMPO);
              return;
             }

          campoedit.pegacaracter = VD_lepos;
          campoedit.col      = campo->col;
          campoedit.lin      = campo->lin;
          campoedit.tamanho  = campo->tamanho;
          campoedit.tipo     = campo->tipo != VIDEO_CAMPO_STRING &&
                               campo->tipo != VIDEO_CAMPO_CARACTER;
          campoedit.tabskip  = campo->tabskip;
          campoedit.buffer   = buffer;
          campoedit.cor      = campo->entrada;
          campoedit.mascara  = campo->mascara                       ?
                         VIDEO_EDITA_expande_mascara(campo->mascara):
                         VIDEO_NILL(char);
          campoedit.decimais = campo->decimais;

          campoedit.autos =
          (campo->autos&VIDEO_EDITA_AUTOSKIP)                         |
          ((campoedit.decimais ? campo->autos&VIDEO_EDITA_EDPONTO : 0)|
          (campo->autos&VIDEO_EDITA_LZEROS)                           |
          (campo->autos&VIDEO_EDITA_LSPACE)                           |
          (campo->autos&VIDEO_EDITA_AUTOIMP)                          |
          (campo->autos&VIDEO_EDITA_SINALMAIS)                        |
          (campo->autos&VIDEO_EDITA_SINALMENOS)                       |
          (campo->autos&VIDEO_EDITA_AUTOBLANK)                        |
          (campo->autos&VIDEO_EDITA_LIMPMASC)                         |
          (campo->autos&VIDEO_EDITA_EDTMASC)                          |
          (campo->autos&VIDEO_EDITA_VALOR)                            |
          (campo->status&VIDEO_EDITA_NAOMOSTRA))                      ;

          *buffer = '\0';

          if (!VIDEO_TELA_monta_buffer_entrada(&campoedit,campo,buffer))
             {
              VIDEO_FREE_ALLOC_MEM(buffer);
              if (campoedit.mascara)
                 VIDEO_free_alloc_parametros(campoedit.mascara);
              return;
             }

          VIDEO_TELA_monta_buffer_saida(&campoedit,campo,buffer);

          if (campoedit.mascara)
             VIDEO_TELA_monta_buffer_mascara(&campoedit,
                campo->buffer_binario,campo->tipo,
                campo->saida);
           else
            {
             VIDEO_CLEAR_PIC(campoedit.col,campoedit.col+campoedit.tamanho-1,
                      campoedit.lin,campoedit.lin,campo->saida);
             if (campo->status&VIDEO_EDITA_NAOMOSTRA)
                {
                 int tam;
                 if ((tam = strlen(buffer)) > 0)
                     --tam;
                 VIDEO_horizontal(campoedit.col,campoedit.col+tam,
                                  campoedit.lin,'*',campo->saida);
                }
              else
                VD_tprt_l(campoedit.col,campoedit.lin,buffer,campo->saida);
            }

          if (campoedit.mascara)
              VIDEO_free_alloc_parametros(campoedit.mascara);

          VIDEO_FREE_ALLOC_MEM(buffer);
         }

      /* Dispara USER FUNCTION ================================================*/
      if (campo->flag_disparo&VIDEO_TELA_FDISPPOS && campo->user_func &&
          (flaguser&VIDEO_FLAGUSER_CAMPO))
          if (!tabfuncuser || !tabfuncuser->userfunc)
             {
              char buffer[200];
              sprintf(buffer,VIDEO_funcao_nao_enc,campo->user_func);
              VIDEO_mostra_mens_erro(buffer,TRUE);
             }
           else
             (tabfuncuser->userfunc)(campo,VIDEO_TELA_FDISPPOS,param);

      if (old_buffer)
         {
          VIDEO_movbloco(old_buffer+sizeof(int)+sizeof(char),
                         campo->buffer_binario,
                         CINT(old_buffer));
          CCHAR((old_buffer+sizeof(int))) = TRUE;
         }
     }
 return;
}
