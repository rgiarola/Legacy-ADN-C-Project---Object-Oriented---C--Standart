#include<INCVIDEO.H>
#include"VDLINALF.H"

/*----------------------------------------------------------------------------
                       EXTRUTURA DE CONTROLE DE LEITURA
----------------------------------------------------------------------------*/
struct VIDEO_MCLIN_CTRL_FONT
 {
  char	*buffer_leitura,
        *origem,*linha;
  DWORD posicao;
  int	descritor,
        lido,posbuffer,
        poslinha ,coment;
  WORD  flags;
  VIDEO_MCLIN_CTRL_FONT *proximo,
                        *anterior;
 };

/*----------------------------------------------------------------------------
                       EXTRUTURA DE CONTROLE DE COMPILACAO
----------------------------------------------------------------------------*/
typedef struct
 {
  INT2   (*gerador_compilacao)();
  struct VIDEO_MCLIN_CTRL_FONT *fonte;
  BYTE   flagdef[10],
         definicao[10];
  VIDEO_MCLIN_CTRL_ANALISE *analise;
  WORD   requisitante;
 }VIDEO_MCLIN_CTRL_COMP;

/*----------------------------------------------------------------------------

INT2 VIDEO_MCLIN_SERV_inicio_compilacao(objcomp,param)
VIDEO_MCLIN_CTRL_COMP **objcomp;
VIDEO_NUCLEO_SERV     **param;
{
 struct VIDEO_MCLIN_CTRL_FONT *fonte;
 VIDEO_MCLIN_CTRL_COMP        *objeto;
 int                          cont;

 objeto = *objcomp;
 objeto->requisitante =
 objeto->analise      = VD_NULO;
 VIDEO_setmem(objeto->flagdef,20,0);
 if (VIDEO_ALLO



}




VIDEO_MCLIN_CTRL_COMP
int  argc;
char *argv[];
{
 VIDEO_MCLIN_STR_EXPAND VIDEO_MCLIN_expande =
 {VD_NULO,VD_NULO,VD_NULO,VD_NULO,VD_NULO,VD_NULO,VD_NULO,VD_NULO,VD_NULO,
  VIDEO_MCLIN_OPEN|VIDEO_MCLIN_ALLOC_MEM|VIDEO_MCLIN_LER_BUFFER};
 char buffer[200];
 char *origem;
 int cont;

 int  situacao = VIDEO_MCLIN_INICIO_COMPILACAO;
 origem = argv[1];

 if (VIDEO_MCLIN_desc_arq == -1)
    {
     DATABASE_GetTempFileName(VIDEO_MCLIN_nome_arq,VD_MAX_TMP_NOME);
     if ((VIDEO_MCLIN_desc_arq = VIDEO_cria(VIDEO_MCLIN_nome_arq)) < 0)
        {
         VIDEO_mostra_mens_erro(VIDEO_texto_pre_proc,VIDEO_ERRO_arquivo_saida_rtree);
         VIDEO_MCLIN_desc_arq = -1;
         return(FALSE);
        }
    }

 do
  {
   if (VIDEO_MCLIN_expande.flags&VIDEO_MCLIN_OPEN)
      {
       VIDEO_MCLIN_expande.origem = origem;
       vtclose();
       if ((VIDEO_MCLIN_expande.descritor = VIDEO_open_ler(origem)) < 0)
		  {
           VIDEO_mostra_mens_erro(VIDEO_texto_pre_proc,VIDEO_ERRO_arquivo_entrada_rtree);
           if (VIDEO_MCLIN_expande.buffer_leitura)
              {
	       for (cont = 2047;cont > -1;cont--)
               if (*(VIDEO_MCLIN_expande.buffer_leitura+cont) != C(0XFF))
                  {
                   if (cont > 1022)
                   VIDEO_mostra_mens_erro(VIDEO_texto_pre_proc,VIDEO_ERRO_1_buffer_prep_danificado);
                   break;
                  }
               VIDEO_FREE_ALLOC_MEM(VIDEO_MCLIN_expande.buffer_leitura);
              }
		   return(FALSE);
		  }
       VIDEO_MCLIN_expande.flags &= ~VIDEO_MCLIN_OPEN;
	  }

   if (VIDEO_MCLIN_expande.flags&VIDEO_MCLIN_POSICIONA)
      {
       VIDEO_lseek(VIDEO_MCLIN_expande.descritor,VIDEO_MCLIN_expande.posicao,VIDEO_INI_ARQ);
       VIDEO_MCLIN_expande.flags &= ~VIDEO_MCLIN_POSICIONA;
	  }

   if (VIDEO_MCLIN_expande.flags&VIDEO_MCLIN_ALLOC_MEM)
      {
       if (VIDEO_ALLOC_MEM(VIDEO_MCLIN_expande.buffer_leitura,2048) == VD_NULO)
		  {
           VIDEO_mostra_mens_erro_alloc(ALOCACAO_PREP_VIDEO_MCLIN_1);
           VIDEO_close(VIDEO_MCLIN_expande.descritor);
           return(FALSE);
		  }
       VIDEO_MCLIN_expande.flags &= ~VIDEO_MCLIN_ALLOC_MEM;
       VIDEO_MCLIN_expande.linha = VIDEO_MCLIN_expande.buffer_leitura;
       VIDEO_setmem(VIDEO_MCLIN_expande.buffer_leitura,2048,C(0XFF));
	  }

   if ((VIDEO_MCLIN_expande.linha =
        VIDEO_MCLIN_filtra_linha(&VIDEO_MCLIN_expande)) == VD_NULO)
      {
       for (cont = 2047;cont > -1;cont--)
           if (*(VIDEO_MCLIN_expande.buffer_leitura+cont) != C(0XFF))
              {
               if (cont > 1022)
                   VIDEO_mostra_mens_erro(VIDEO_texto_pre_proc,VIDEO_ERRO_2_buffer_prep_danificado);
               situacao = VIDEO_MCLIN_FIM_COMPILACAO_ERRO;
               break;
              }
       VIDEO_FREE_ALLOC_MEM(VIDEO_MCLIN_expande.buffer_leitura);
       VIDEO_close(VIDEO_MCLIN_expande.descritor);
       return(TRUE);
      }

   printf("%s\n",VIDEO_MCLIN_expande.linha);
 }while(TRUE);
}


