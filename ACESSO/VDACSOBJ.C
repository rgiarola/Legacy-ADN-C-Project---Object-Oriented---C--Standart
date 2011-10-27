#include <INCVIDEO.H>
typedef struct
 {
  char ident[21],
       objeto[21];
  BYTE posicao,
       permissao,
       nivel,
       acesso[8];
 }ACESSO_USUARIO;

int IDEO_ACESSO_permissao_acesso(BYTE tipoacesso)
{
 int            teste;
 ACESSO_USUARIO *geral_processo,*geral_sistema,geral_tela,
                *usuario_processo = VD_NULO,*usuario_sistema = VD_NULO,
                *usuario_tela = VD_NULO;

 if (!VIDEO_ACESSO_flag)
     return(TRUE);

 VIDEO_acesso_posicao = VD_NULO;
 if ((geral = VIDEO_ACESSO_permissao_acesso_grupo(BYTE tipoacesso,
                                                  BUSR_geral)) == VD_NULO)
    {
     VIDEO_mostra_mens_erro_alloc(ALOCACAO_CONTROLE_ACESSO);
     return(FALSE);
    }

 if (!geral->posicao)
    return(FALSE);

 if (VD_GETBUF(BUSR_grupo,DWORD))
    {
     VIDEO_acesso_posicao = VD_NULO;
     if ((usuario = VIDEO_ACESSO_permissao_acesso_grupo(BYTE tipoacesso,
                                                        BUSR_grupo)) == VD_NULO)
        {
         VIDEO_mostra_mens_erro_alloc(ALOCACAO_CONTROLE_ACESSO);
         VIDEO_FREE_ALLOC_MEM(geral);
         return(FALSE);
        }
    }
  else
    {
     if (geral->permissao == B('P'))
        {
         if (geral->acesso == 1)
            {
             VIDEO_ACESSO_monta_permissao();

          {
           case 1: VIDEO_FREE_ALLOC_MEM(geral);
                   return(FALSE);

           case 3:

           case 5:

           case 7:
          }
        }
      else
        {
         if (geral->acesso == 1)
             return(FALSE);
        }
    }

 return(FALSE);
}

ACESSO_USUARIO *VIDEO_ACESSO_permissao_acesso(char *grupo)
{
 ACESSO_USUARIO *acesso_processo,*acesso_tela,
 int            teste;

 VIDEO_acesso_posicao = VD_NULO;
 if ((acesso_processo = VIDEO_ACESSO_permissao_acesso_grupo(B('P'),grupo)) == VD_NULO)
    {
     VIDEO_mostra_mens_erro_alloc(ALOCACAO_CONTROLE_ACESSO);
     return(VD_NULO);
    }
 if (!acesso_processo->posicao)
    {
     VIDEO_FREE_ALLOC_MEM(acesso_processo);
     return(VD_NULO);
    }
 if (acesso_processo->permissao == B('P'))
    {
     if (acesso_processo->posicao == 1)
        {
         VIDEO_FREE_ALLOC_MEM(acesso_processo);
         return(VD_NULO);
        }
    }

 if ((acesso_tela = VIDEO_ACESSO_permissao_acesso_grupo(B('T'),grupo)) == VD_NULO)
    {
     VIDEO_mostra_mens_erro_alloc(ALOCACAO_CONTROLE_ACESSO);
     VIDEO_FREE_ALLOC_MEM(acesso_processo);
     return(VD_NULO);
    }
 if (!acesso_tela->posicao)
    {
     VIDEO_FREE_ALLOC_MEM(acesso_processo);
     VIDEO_FREE_ALLOC_MEM(acesso_tela);
     return(FALSE);
    }
 if (acesso_tela->permissao == B('P'))
    {
     if (acesso_tela->posicao == 1)
        {
         VIDEO_FREE_ALLOC_MEM(acesso_processo);
         VIDEO_FREE_ALLOC_MEM(acesso_tela);
         return(VD_NULO);
        }
    }

 switch(I(acesso_processo->permissao))
  {
   case I('P'):

 VIDEO_movbloco(acesso_processo->ident,acesso_tela->ident,21);
 VIDEO_movbloco(acesso_processo->objeto,acesso_tela->objeto,21);
                acesso_processo->posicao,
 acesso_processo->permissao,
 acesso_processo->nivel,
 acesso_processo->acesso;



 return(FALSE);
}


ACESSO_USUARIO *VIDEO_ACESSO_permissao_acesso_grupo(BYTE tipoacesso,
                                                    char *grupo)
{
 int             indacesso,indgrupo,ret,cont;
 char            buffer[200],tipo[2];
 VIDEO_SEG_CHAVE acesso[] = {{VD_NULO   ,       4,CT_SEG_CAMPO_CONST},
                             {tipo      ,       1,CT_SEG_CONST      },
                             {BACS_proj_sist,  21,CT_SEG_CAMPO      },
                             {BACS_objeto,     21,CT_SEG_CAMPO      },
                             {VD_NULO    ,VD_NULO,   VD_NULO        }};
 ACESSO_USUARIO *usuario;

 if (VIDEO_ALLOC_MEM(usuario,sizeof(ACESSO_USUARIO)) == VD_NULO)
     return(VD_NULO);

 VIDEO_setmem(usuario,sizeof(ACESSO_USUARIO),0);

 indacesso = CTREE_keynm(VIDEO_ACESSO_indice_acesso);
 indgrupo  = CTREE_keynm(VIDEO_ACESSO_indice_grupo);

 acesso[0].pointer = grupo;
 tipo[0]           = tipoacesso;
 usuario->posicao  = 1;

 if ((VD_GETBUF(BNIV_numero,DWORD) = VD_GETBUF(grupo,DWORD)) == 0)
     if (!strcmp(VD_GETEND(BUSR_nomeide,"MESTRE")))
         return(usuario);

 if ((ret = CTREE_find(indgrupo,FIND_IGUAL,
                       VD_NULO,CTLE_EXTRA_REPASSA)) != FALSE)
    {
     sprintf(buffer,"Grupo [%ld] N„o Encontrado ST[%d/%d],ret,isam_err);
     VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_grupo_nao_encontrado);
     usuario->posicao = 0;
     return(usuario);
    }

 usuario->permissao = VD_GETBUF(BNIV_permissao",BYTE);

 if ((ret = CTREE_copy(indacesso,indacesso,acesso,
                       TRUE,VIDEO_ACESSO_testa_permissao)) != 101 && ret != 100)
    {
     sprintf(buffer,"Grupo [%ld] Sem Acesso ST[%d/%d],ret,isam_err);
     VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_acesso_danificado);
     usuario->posicao = 0;
     return(usuario);
    }

 if (VIDEO_acesso_posicao)
    {
     if (CTREE_pusharqtest(VIDEO_acesso_posicao))
        {
         VIDEO_poparq(CTREE_keyfil(indacesso),VIDEO_acesso_posicao);
         VIDEO_movbloco(usuario->ident ,VD_GETEND(BACS_proj_sist,char),21);
         VIDEO_movbloco(usuario->objeto,VD_GETEND(BACS_objeto,char)   ,21);
         usuario->posicao   = VIDEO_acesso_posicao;
         usuario->nivel     = VD_GETBUF(BACS_nivel,BYTE);
         VIDEO_movbloco(usuario->acesso,VD_GETEND(BACS_acesso,char),8);
         return(usuario);
        }

      sprintf(buffer,CTREE_MENS_mens_padrao_err,"Acesso",
                     VIDEO_PESQ_mens_troca_pesq,ret,isam_err);
      VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_acesso_danificado);
      usuario->posicao = FALSE;
     }

 return(usuario);
}

int VIDEO_ACESSO_testa_permissao(int flag,int origem,int destino)
{
 if (!VIDEO_ACESSO_retorno)
    {
     switch(I(VD_GETBUF(BACS_nivel,BYTE)))
      {
       case I('P'):if (atol(VD_GETEND(BACS_proj_sist,char)) ==
                       VIDEO_ACESSO_processo)
                      {
                       VIDEO_acesso_posicao = VIDEO_pusharq(origem);
                       VIDEO_ACESSO_retorno =
                         (VD_GETBUF(BNIV_permissao",BYTE) == B('B')) ? 2 : 3;
                      }
                   break;

       case I('T'):if (!strcmp(VD_GETEND(BACS_proj_sist,char),
                               VD_GETEND(VIDEO_CARGA_CRG_sistema,char)))
                      {
                       if (VD_GETBUF(VIDEO_CARGA_CRG_numobj,WORD) ==
                                     atoi(VD_GETEND(BACS_objeto,char)) ||
                           !strcmp(VD_GETEND(VIDEO_CARGA_CRG_objeto,char),
                                   VD_GETEND(BACS_objeto,char)))
                          {
                           VIDEO_acesso_posicao = VIDEO_pusharq(origem);
                           VIDEO_ACESSO_retorno =
                             (VD_GETBUF(BNIV_permissao",BYTE) == B('B') ? 4 : 5):
                          }
                      }
                   break;
      }

     if (VIDEO_acesso_posicao)
         CTREE_find(CTREE_keynm(VIDEO_ACESSO_indice_acesso),
                    VD_NULO,FIND_ULTIMO,CT_LE_EXTRA_REPASSA):
    }

 return(TRUE);
}

