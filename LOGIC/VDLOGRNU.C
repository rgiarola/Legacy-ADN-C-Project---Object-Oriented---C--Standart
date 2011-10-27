#include <INCVIDEO.H>
#include <SIGNAL.H>
#include <LOGIC.H>

/*----------------------------------------------------------------------------
                              RETIRA NUMERO
----------------------------------------------------------------------------*/
VD_VOID VIDEO_LOGIC_retira_numero(elementos,expresao)
VIDEO_LOGIC_OBJETO *elementos;
char               **expresao;
{
 double valor;
 int    tamanho;

 tamanho = 0;
 do
  {
   elementos->objeto[tamanho++] = *((*expresao)++);
  }while(VIDEO_ISDIGIT(*(*expresao)) || (*(*expresao) == '.'));

 elementos->objeto[tamanho] = 0;
 elementos->tipoobjeto    = VIDEO_LOGIC_CONST_NUMERICA;
 elementos->grupo         = VIDEO_LOGIC_CONST;

 valor = atof(elementos->objeto);
 CDOUBLE(elementos->objeto) = valor;
 //printf("VALOR CONV %10.6f\n",CDOUBLE(elementos->objeto));
}


