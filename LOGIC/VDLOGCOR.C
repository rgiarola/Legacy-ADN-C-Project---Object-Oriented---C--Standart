#include <INCVIDEO.H>
#include <SIGNAL.H>
#include <LOGIC.H>

/*----------------------------------------------------------------------------
                            CONSISTE OPERACAO
----------------------------------------------------------------------------*/

int VIDEO_LOGIC_consiste_operacao(work,inicio,objeto,var1,var2)
VIDEO_LOGIC_OBJETO *work,*inicio,*objeto;
char			   **var1,**var2;
{
 int ret;

 *var1 = *var2 = VD_NULO;

 // HA SOMENTE O OPERADOR
// printf("HA SOMENTE O OPERADOR\n");
 if (work == inicio && work->grupo == VIDEO_LOGIC_OPERARIT_NIVEL2)
	 return(VIDEO_LOGIC_PRIMEIRO_OPER);

 // NAO HA O SEGUNDO OPERANDO
// printf("NAO HA O SEGUNDO OPERANDO\n");
 if ((work+1) >= objeto)
	 return(VIDEO_LOGIC_SEGUNDO_OPER);

 // PRIMEIRO OPERANDO NAO E COMPATIVEL
// printf("PRIMEIRO OPERANDO NAO E COMPATIVEL\n");
 if (work->grupo == VIDEO_LOGIC_OPERARIT_NIVEL2)
     if ((work-1)->grupo != VIDEO_LOGIC_CONST &&
         (work-1)->grupo != VIDEO_LOGIC_VAR)
          return(VIDEO_LOGIC_PRIMEIRO_OPER);

 // SEGUNDO OPERANDO NAO E COMPATIVEL
// printf("SEGUNDO OPERANDO NAO E COMPATIVEL\n");
 if ((work+1)->grupo != VIDEO_LOGIC_CONST &&
	 (work+1)->grupo != VIDEO_LOGIC_VAR)
	 return(VIDEO_LOGIC_SEGUNDO_OPER);

 // CONVERTE OPERANDO PARA VAR1
 if (work->grupo > VIDEO_LOGIC_OPERARIT_NIVEL1)
     if ((ret = VIDEO_LOGIC_converte_operando(work-1,var1)) != FALSE)
         return(ret);
// printf("CONVERTE OPERANDO PARA VAR1\n");

 // CONVERTE OPERANDO PARA VAR2
 if ((ret = VIDEO_LOGIC_converte_operando(work+1,var2)) != FALSE)
	{
	 VIDEO_FREE_ALLOC_MEM(*var1);
	 return(ret);
	}
// printf("CONVERTE OPERANDO PARA VAR2\n");

 // TESTA COMPATIBILIDADE DE OPERANDOS
// printf("TESTA COMPATIBILIDADE DE OPERANDOS\n");
 if (work->grupo == VIDEO_LOGIC_OPERARIT_NIVEL2)
    {
     if ((work+1)->tipoobjeto != (work-1)->tipoobjeto)
        {
         VIDEO_FREE_ALLOC_MEM(*var1);
         VIDEO_FREE_ALLOC_MEM(*var2);
         return(VIDEO_LOGIC_INCPER);
        }
    }
  else
    if ((work+1)->grupo != VIDEO_LOGIC_CONST_NUMERICA)
       {
        VIDEO_FREE_ALLOC_MEM(*var2);
        return(VIDEO_LOGIC_INCPER);
       }

// printf("Consistencia Sem Erro\n");
 return(FALSE);
}

