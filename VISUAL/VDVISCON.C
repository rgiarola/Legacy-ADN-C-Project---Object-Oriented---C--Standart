#include <INCVIDEO.H>

/* ============================================================================
   Driver de Configuracao:
   Impressora PADRAO E P S O N
   ============================================================================ */
#define PRT_MAX_COMANDO 7

// FUNCOES DE INTERFACE

 int  VD_printer_busca_comando(int comando, char opcao,
                               char *buffer,int *tamanho);
 int  VD_printer_comando( int comando, char opcao );
 int  VD_comando_buffer_printer( int comandoi, int comandof,char parametro,
                                 char *buffer,int modo);
 int  VD_printer_buffer( char *buffer);

#define PRN_MONTACMD(c,op,buf,tam)  VD_printer_busca_comando(c,op,buf,tam)
#define PRN_PRINT(x)                VD_printer_buffer(x)
#define PRN_COMANDO(x,y)            VD_printer_comando(x,y)
#define PRN_FORMATIN(ci,cf,op,buf)  VD_comando_buffer_printer(ci,cf,op,buf,TRUE)
#define PRN_FORMATOUT(ci,cf,op,buf) VD_comando_buffer_printer(ci,cf,op,buf,FALSE)

#define PRT_INICIALIZA          0
#define PRT_FORMFEED            1
#define PRT_LINE_FEED           2
#define PRT_CONDENSADO_ON       3
#define PRT_CONDENSADO_OFF      4
#define PRT_DUPLACOL_ON         5
#define PRT_DUPLACOL_OFF        6
#define PRT_NEGRITO_ON          7
#define PRT_NEGRITO_OFF         8
#define PRT_STRIKE_ON           9
#define PRT_STRIKE_OFF         10
#define PRT_SOBRESCRITO_ON     11
#define PRT_SUBESCRITO_ON      12
#define PRT_ESCRITO_OFF        13
#define PRT_ITALICO_ON         14
#define PRT_ITALICO_OFF        15
#define PRT_SUBLINHADO_ON      16
#define PRT_SUBLINHADO_OFF     17
#define PRT_ESPACOS_1          18
#define PRT_ESPACOS_3          19

typedef struct      // Estrutura do Driver de Impressao.
{
 int  comando;
 char cmbuffer[PRT_MAX_COMANDO],
      parametro;
} VIDEO_comando_impressora;

VIDEO_comando_impressora VIDEO_tabela_comando_impressora[] = {
{ PRT_INICIALIZA,        { 27, '@',  -1      },  0 },
{ PRT_FORMFEED,          { 12,  -1           },  0 },
{ PRT_LINE_FEED,         { 10,  -1           },  0 },
{ PRT_CONDENSADO_ON,     { 15,  -1           },  0 },
{ PRT_CONDENSADO_OFF,    { 18,  -1           },  0 },
{ PRT_DUPLACOL_ON,       { 27, 'W', '1',  -1 },  0 },
{ PRT_DUPLACOL_OFF,      { 27, 'W', '0',  -1 },  0 },
{ PRT_NEGRITO_ON,        { 27, 'E',  -1      },  0 },
{ PRT_NEGRITO_OFF,       { 27, 'F',  -1      },  0 },
{ PRT_STRIKE_ON,         { 27, 'G',  -1      },  0 },
{ PRT_STRIKE_OFF,        { 27, 'H',  -1      },  0 },
{ PRT_SOBRESCRITO_ON,    { 27, 'S', '1',  -1 },  0 },
{ PRT_SUBESCRITO_ON,     { 27, 'S', '1',  -1 },  0 },
{ PRT_ESCRITO_OFF,       { 27, 'T',  -1      },  0 },
{ PRT_ITALICO_ON,        { 27, '4',  -1      },  0 },
{ PRT_ITALICO_OFF,       { 27, '5',  -1      },  0 },
{ PRT_SUBLINHADO_ON,     { 27, '-', '1',  -1 },  0 },
{ PRT_SUBLINHADO_OFF,    { 27, '-', '0',  -1 },  0 },
{ PRT_ESPACOS_1,         { 27, '0',  -1      },  0 },
{ PRT_ESPACOS_3,         { 27, '2',  -1      },  0 },
{ -1, "" }};    // Terminacao Obrigatoria.


INT2 VIDEO_VISUAL_tela_conf_imp(imagem,flag,param)
VIDEO_IMAGEMTELA  **imagem;
int               flag;
VIDEO_NUCLEO_SERV **param;
{
 int ret;

 if (((*param)->VIDEO_servrec == I(VD_MTTECLA(VD_NULO,F5))) ||
     ((*param)->VIDEO_servrec == I(VD_MTTECLA(VD_NULO,ALT_MENOS))))
    {
     if ((ret = VIDEO_CRG_executa_menu(&VIDEO_VISUAL_menu_config)) < 1)
        {
         if (isam_err)
            {
             char buffer[100];
             sprintf(buffer,VIDEO_CARGA_mens_exec_tela,
                            VIDEO_VISUAL_menu_config.sistcrg,
                            VIDEO_VISUAL_menu_config.telacrg,isam_err);
             VIDEO_mostra_mens_erro(buffer,
                                    VIDEO_ERRO_tela_nao_encontrada);
            }
         return(TRUE);
        }

     VD_telaproc((80-strlen(VIDEO_VISUAL_mens_config_impress))/2,
                 10,VIDEO_VISUAL_mens_config_impress,
           VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_BLANK,VD_BRIL));

     VD_printer_comando( ret -1 , 0 );

     VD_POPWIN();
    }

 return(TRUE);
}


/* ============================================================================
   COMANDOS DE IMPRESSAO
   VD_printer_busca_comando -> Localiza o Comando Desejado no Driver de Impres.
   VD_printer_comando       -> Imprime comando para impressora.
   ============================================================================ */


int  VD_printer_busca_comando( comando, opcao, buffer, tamanho )
int  comando;
char opcao,
     *buffer;
int  *tamanho;
{
 register int posicao;
 VIDEO_comando_impressora *tabprinter;

 if (comando<0)
    return(-1);

 tabprinter = VIDEO_tabela_comando_impressora;

 while( tabprinter->comando != -1 )
   {
    if ( tabprinter->comando == comando )
       break;
    ++tabprinter;
   }

 if ( tabprinter->comando == -1 )
    return( -2 );

 posicao=0;
 while( tabprinter->cmbuffer[posicao] != -1 &&
        posicao < PRT_MAX_COMANDO )
   {
    *buffer = tabprinter->cmbuffer[posicao];
    ++posicao;
    ++buffer;
   }

 if (posicao > PRT_MAX_COMANDO)
    return(-3);

 if (tabprinter->parametro)
    {
     *buffer=opcao;
     *tamanho=posicao+1;
    }
 else
    *tamanho=posicao;

 return(FALSE);
}

int  VD_printer_comando( comando, opcao )
int  comando;
char opcao;
{
 register char buffer[20];
 int           ret,impressora,cont,
               tamanho=0;
 BYTE          ascii,scan;

 if ( (ret=VD_printer_busca_comando( comando, opcao, buffer, &tamanho))!=FALSE)
    return(ret);
 
 impressora = 0;
 switch(VD_GETBUF(BREL_selec3,char))
  {
   case '3':++impressora;
   case '2':++impressora;
   case 'P':
   case '1':++impressora;
  }

 cont = 0;
 do
  {
   ret = VIDEO_IMPRESS_envia(buffer[cont],impressora);

   if (ret&(B08|B11|B13) || !(ret&B12))
      {
       ret = VIDEO_mostra_mens_erro(
              VIDEO_IMPRESS_erro_impressora,FALSE);
       --cont;
      }
    else
      ret = FALSE;

   if (VD_getkey(&ascii,&scan) && !ret)
       ret = VD_MTTECLA(ascii,scan);

   if (ret == VD_MTTECLA(ESCAPE,ESCAPESCAN))
       if (VD_telaconf(30,10,VIDEO_VISUAL_cancela_impress,
             VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_BLANK,VD_BRIL)) == TRUE)
           break;
  }while(++cont < tamanho);

 return(FALSE);
}





