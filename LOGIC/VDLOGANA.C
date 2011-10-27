#include <INCVIDEO.H>
#include <SIGNAL.H>
#include <LOGIC.H>

/*----------------------------------------------------------------------------
                       ANALISA EXPRESAO ITEM A ITEM
----------------------------------------------------------------------------*/
int VIDEO_LOGIC_analise_expresao(expresao,retorno,elementos,nivel)
char               *expresao;
VIDEO_LOGIC_OBJETO *retorno,
                   **elementos;
int                nivel;
{
 char *teste = expresao,*ptraux;
 int  fim,tamanho,ret;
 VIDEO_LOGIC_OBJETO *inicio;

 inicio = *elementos;

 if (!strlen(expresao))   //============ EXPRESAO VAZIA
    return(nivel);

 do
  {
//   printf("[%c]",*teste);
   switch(I(*teste))
    {
     //====================================RETIRA STRING DA EXPRESAO
     case I('\"')://printf("RETIRA STRING DA EXPRESAO\n");
                  if ((ptraux = strchr(teste+1,'\"')) == VD_NULO)
                      return(VIDEO_LOGIC_CONST_STRING);
                  tamanho = (FP_OFF(ptraux))-FP_OFF((teste+1));
                  VIDEO_movbloco((*elementos)->objeto,teste+1,tamanho);
                  (*elementos)->tipoobjeto      = VIDEO_LOGIC_CONST_STRING;
                  (*elementos)->objeto[tamanho] = 0;
                  (*elementos)->nivel           = nivel;
                  (*elementos)++->grupo         = VIDEO_LOGIC_CONST;
                  teste = ptraux+1;
				  break;

     //====================================CHAMA COMPILADOR RECURSIVO
     
     case I('(') ://printf("CHAMA COMPILADOR RECURSIVO\n");
                  if ((ret = VIDEO_LOGIC_analise_expresao(++teste,retorno,
                             elementos,nivel+1)) != FALSE)
                     return(ret);
                  break;

     //====================================ANALIZA BLOCO RETIRADO DA EXPRESAO
     case I(')') ://printf("ANALIZA BLOCO RETIRADO DA EXPRESAO\n");
                  if ((ret = VIDEO_LOGIC_analise_logica(inicio,elementos,retorno)) != FALSE)
                      return(ret);
				  tamanho = FP_OFF(teste) - FP_OFF(expresao) + 1;
				  VIDEO_setmem(expresao-1,tamanho+1,' ');
                  if (!nivel)
                      return(VIDEO_LOGIC_PARENTESES);
                  return(FALSE);

     //====================================ANALIZA OPERADOR MAIOR
     case I('>') ://printf("ANALIZA OPERADOR MAIOR\n");
                  (*elementos)->nivel = nivel;
                  (*elementos)->grupo = VIDEO_LOGIC_OPERLOGIC;
				  if (*(++teste) == '=')
					 {
                      (*elementos)++->tipoobjeto = VIDEO_LOGIC_OPERLOGICO_MAIORI;
					  ++teste;
					 }
				   else
                     (*elementos)++->tipoobjeto = VIDEO_LOGIC_OPERLOGICO_MAIOR;
                  break;

     //====================================ANALIZA OPERADOR MENOR
     case I('<') ://printf("ANALIZA OPERADOR MENOR\n");
                  (*elementos)->nivel = nivel;
                  (*elementos)->grupo = VIDEO_LOGIC_OPERLOGIC;
				  if (*(++teste) == '=')
					 {
                      (*elementos)++->tipoobjeto = VIDEO_LOGIC_OPERLOGICO_MENORI;
					  ++teste;
					 }
				   else
                     (*elementos)++->tipoobjeto = VIDEO_LOGIC_OPERLOGICO_MENOR;
                  break;
     //====================================ANALIZA OPERADOR IGUAL
     case I('=') ://printf("ANALIZA OPERADOR IGUAL\n");
                  (*elementos)->nivel    = nivel;
                  (*elementos)->grupo    = VIDEO_LOGIC_OPERLOGIC;
                  (*elementos)++->tipoobjeto = VIDEO_LOGIC_OPERLOGICO_IGUAL ;
                  if (*(teste+1) != '=')
                     return(VIDEO_LOGIC_OPERADOR_IGUAL);
				  teste += 2;
                  break;

     //====================================ANALIZA OPERADOR DIFERENTE
     case I('!') ://printf("ANALIZA OPERADOR DIFERENTE\n");
                  (*elementos)->nivel    = nivel;
                  (*elementos)->grupo    = VIDEO_LOGIC_OPERLOGIC;
                  (*elementos)++->tipoobjeto = VIDEO_LOGIC_OPERLOGICO_DIFER;
                  if (*(teste+1) != '=')
                     return(VIDEO_LOGIC_OPERADOR_DIF);
				  teste += 2;
                  break;

     //====================================ANALIZA PORTA AND
     case I('&') ://printf("ANALIZA PORTA AND\n");
                  (*elementos)->nivel    = nivel;
                  (*elementos)->grupo    = VIDEO_LOGIC_PORTALOGIC;
                  (*elementos)++->tipoobjeto = VIDEO_LOGIC_OPERLOGICO_AND;
                  if (*(teste+1) != '&')
                     return(VIDEO_LOGIC_OPERADOR_AND);
				  teste += 2;
                  break;

     //====================================ANALIZA PORTA OU
     case I('|') ://printf("ANALIZA PORTA OU\n");
                  (*elementos)->nivel    = nivel;
                  (*elementos)->grupo    = VIDEO_LOGIC_PORTALOGIC;
                  (*elementos)++->tipoobjeto = VIDEO_LOGIC_OPERLOGICO_OR;
                  if (*(teste+1) != '|')
                     return(VIDEO_LOGIC_OPERADOR_OU);
				  teste += 2;
                  break;

     //====================================ANALIZA OPERADOR SOMA
     case I('+') ://printf("ANALIZA OPERADOR SOMA\n");
                  if (VIDEO_ISDIGIT((teste+1) || *(teste+1) == '.'))
                  if (((*elementos) == inicio) || ((*elementos) > inicio &&
						 (((*elementos)-1)->grupo == VIDEO_LOGIC_OPERARIT_NIVEL1 ||
						  ((*elementos)-1)->grupo == VIDEO_LOGIC_OPERARIT_NIVEL2 ||
						  ((*elementos)-1)->grupo == VIDEO_LOGIC_OPERARIT_NIVEL3 ||
                          ((*elementos)-1)->grupo == VIDEO_LOGIC_OPERLOGIC)))
                         {
                          VIDEO_LOGIC_retira_numero((*elementos),&teste);
                          (*elementos)->nivel = nivel;
                          break;
                         }
                  (*elementos)->nivel        = nivel;
				  (*elementos)->grupo		 = VIDEO_LOGIC_OPERARIT_NIVEL3;
                  (*elementos)++->tipoobjeto = VIDEO_LOGIC_OPERARIT_SOMA;
				  ++teste;
                  break;

     //====================================ANALIZA OPERADOR SUBTRAI
     case I('-') ://printf("ANALIZA OPERADOR SUBTRAI\n");
                  if (VIDEO_ISDIGIT((teste+1) || *(teste+1) == '.'))
                      if (((*elementos) == inicio) || ((*elementos) > inicio &&
						  (((*elementos)-1)->grupo == VIDEO_LOGIC_OPERARIT_NIVEL1 ||
						   ((*elementos)-1)->grupo == VIDEO_LOGIC_OPERARIT_NIVEL2 ||
						   ((*elementos)-1)->grupo == VIDEO_LOGIC_OPERARIT_NIVEL3 ||
                           ((*elementos)-1)->grupo == VIDEO_LOGIC_OPERLOGIC)))
                         {
                          VIDEO_LOGIC_retira_numero((*elementos),&teste);
                          (*elementos)->nivel = nivel;
                          break;
                         }

                  (*elementos)->nivel = nivel;
				  (*elementos)->grupo = VIDEO_LOGIC_OPERARIT_NIVEL3;
                  (*elementos)++->tipoobjeto = VIDEO_LOGIC_OPERARIT_SUB;
				  ++teste;
                  break;

     //====================================ANALIZA OPERADOR DIVIDE
     case I('/') ://printf("ANALIZA OPERADOR DIVIDE\n");
                  (*elementos)->nivel    = nivel;
				  (*elementos)->grupo	 = VIDEO_LOGIC_OPERARIT_NIVEL2;
                  (*elementos)++->tipoobjeto = VIDEO_LOGIC_OPERARIT_DIVISAO;
				  ++teste;
                  break;

     //====================================ANALIZA OPERADOR POTENCIA
     case I('^') ://printf("ANALIZA OPERADOR POTENCIA\n");
                  (*elementos)->nivel    = nivel;
				  (*elementos)->grupo	 = VIDEO_LOGIC_OPERARIT_NIVEL2;
                  (*elementos)++->tipoobjeto = VIDEO_LOGIC_OPERARIT_EXP;
				  ++teste;
                  break;

     //====================================ANALIZA OPERADOR RESTO
     case I('%') ://printf("ANALIZA OPERADOR RESTO\n");
                  (*elementos)->nivel    = nivel;
                  if (*(teste+1) != '%')
                     {
					  (*elementos)->grupo	 = VIDEO_LOGIC_OPERARIT_NIVEL2;
                      (*elementos)++->tipoobjeto = VIDEO_LOGIC_OPERARIT_RESTO;
                      ++teste;
                     }
                   else
                     {
                      (*elementos)->grupo    = VIDEO_LOGIC_OPERARIT_NIVEL1;
                      (*elementos)++->tipoobjeto = VIDEO_LOGIC_OPERARIT_INT;
                      teste += 2;
                     }
                  break;

	 //====================================ANALIZA OPERADOR RAIZ
     case I('#') ://printf("ANALIZA OPERADOR RAIZ\n");
                  (*elementos)->nivel    = nivel;
                  if (*(teste+1) != '#')
                     {
					  (*elementos)->grupo	 = VIDEO_LOGIC_OPERARIT_NIVEL1;
                      (*elementos)++->tipoobjeto = VIDEO_LOGIC_OPERARIT_SQRT;
                      ++teste;
                     }
                   else
                     {
					  (*elementos)->grupo		 = VIDEO_LOGIC_OPERARIT_NIVEL2;
					  (*elementos)++->tipoobjeto = VIDEO_LOGIC_OPERARIT_RAIZ;
                      teste += 2;
                     }
                  break;

     //====================================ANALIZA OPERADOR DECIMAL
     case I('~') ://printf("ANALIZA OPERADOR DECIMAL\n");
                  (*elementos)->nivel = nivel;
				  (*elementos)->grupo = VIDEO_LOGIC_OPERARIT_NIVEL1;
                  (*elementos)++->tipoobjeto = VIDEO_LOGIC_OPERARIT_DECIMAL;
				  ++teste;
                  break;

     //====================================ANALIZA OPERADOR MULTIPLICA
     case I('*') ://printf("ANALIZA OPERADOR MULTIPLICA\n");
                  (*elementos)->nivel    = nivel;
				  (*elementos)->grupo	 = VIDEO_LOGIC_OPERARIT_NIVEL2;
                  (*elementos)++->tipoobjeto = VIDEO_LOGIC_OPERARIT_MULT;
				  ++teste;
                  break;

     //====================================ESPACO EM BRANCO
     case I(' ') :
     case I(9)   :++teste;
                  //printf("ESPACO EM BRANCO\n");
                  break;

     case    I(0)://printf("FIM INESPERADO\n");
                  if (nivel)
                      return(VIDEO_LOGIC_FIM_INESPERADO);
                  return(VIDEO_LOGIC_analise_logica(inicio,elementos,retorno));

     //====================================ANALIZA CONSTANTE OU VARIAVEL
     default     ://printf("ANALIZA CONSTANTE OU VARIAVEL\n");
                  if (VIDEO_ISDIGIT(*teste))
                     {
                      VIDEO_LOGIC_retira_numero((*elementos),&teste);
                      (*elementos)++->nivel    = nivel;
					 }
				   else
					 {
                      (*elementos)->nivel    = nivel;
					  tamanho = 0;
					  do
					   {
                        (*elementos)->objeto[tamanho++] = *(teste++);
                       }while(VIDEO_ISCARACTER(*teste) || *teste == '_' || VIDEO_ISDIGIT(*teste));
                      (*elementos)->objeto[tamanho] = 0;
                      (*elementos)->tipoobjeto    = VIDEO_LOGIC_DODA;
                      (*elementos)++->grupo       = VIDEO_LOGIC_VAR;
                     }
                  break;
    }
  }while(TRUE);
}
