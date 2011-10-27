#include <INCVIDEO.H>
#include <SIGNAL.H>
#include <LOGIC.H>

/*----------------------------------------------------------------------------
                      ANALISA BLOCO RETIRADO DA EXPRESAO
----------------------------------------------------------------------------*/
int VIDEO_LOGIC_analise_logica(inicio,elemento,retorno)
VIDEO_LOGIC_OBJETO *inicio,
                   **elemento,
                   *retorno;
{
 VIDEO_LOGIC_OBJETO *work;
 int  cont,flagteste,tam2,
      flagajuste,tamanho,
      ret1,ret2,ret,nivel;
 char *var1,*var2;
 int  (*funcao)();

 //printf("Analize\n");

 flagajuste = FALSE;

/*----------------------------------------------------------------------------
				  PROCESSAO OPERACOES ARITMETICAS DOIS OPERANDOS
----------------------------------------------------------------------------*/
 work = inicio;

 if (work->grupo)
     *retorno = *work;

 nivel = 0;
 do
  {
   if (++nivel >= 3)
       break;

   //printf("Inicio %d\n",nivel);
   work = inicio;

   while(work <= (*(elemento)-1))
	{
/*
     printf("NIVEL %d %d %d %d %d %d\n",nivel,work->grupo,
                                                VIDEO_LOGIC_OPERARIT_NIVEL1,
                                                VIDEO_LOGIC_OPERARIT_NIVEL2,
                                                VIDEO_LOGIC_OPERARIT_NIVEL3,
                                                W(W(FP_OFF((*elemento)))-W(FP_OFF(work)))/
                                                                       sizeof(VIDEO_LOGIC_OBJETO));

*/
     if ((nivel == 1 && (work->grupo == VIDEO_LOGIC_OPERARIT_NIVEL1   ||
                         work->grupo == VIDEO_LOGIC_OPERARIT_NIVEL2)) ||
         (nivel == 2 && (work->grupo == VIDEO_LOGIC_OPERARIT_NIVEL3)))
        {
         if ((ret = VIDEO_LOGIC_consiste_operacao(work,inicio,(*elemento),
                                                      &var1,&var2)) != FALSE)
                 return(ret);

         // TESTA OPERANDO STRING
		 if ((work-1)->tipoobjeto == VIDEO_LOGIC_CONST_STRING)
            {
			 if (work->tipoobjeto == VIDEO_LOGIC_OPERARIT_SOMA)
                {
                 tamanho = strlen(var1);
                 tamanho = tamanho > 20 ? 20 : tamanho;
				 VIDEO_movbloco((work-1)->objeto,var1,tamanho);
                 tam2 = strlen(var2);
                 tam2 = (tamanho + tam2) > 20 ? 20 - tamanho :tam2;
				 VIDEO_movbloco(&(work-1)->objeto[tamanho],var2,tam2);
				 (work-1)->objeto[tam2+tamanho] = 0;

				 flagajuste = TRUE;
                }
             VIDEO_FREE_ALLOC_MEM(var1);
             VIDEO_FREE_ALLOC_MEM(var2);
			 return(VIDEO_LOGIC_INCSTRING);
            }
          else
            {
         // EXECUTA OPERACAO ARITMETICA
//            printf("EXECUTA OPERACAO ARITMETICA\n");

             *retorno = *(work-1);
             switch(work->tipoobjeto)
              {
               case VIDEO_LOGIC_OPERARIT_EXP    :
                    signal(SIGFPE,VIDEO_LOGIC_float_error);
                    CDOUBLE(retorno->objeto) = pow(CDOUBLE(var1),CDOUBLE(var2));
                    if (VIDEO_LOGIC_erro_float_)
                       {
                        VIDEO_FREE_ALLOC_MEM(var1);
                        VIDEO_FREE_ALLOC_MEM(var2);
                        return(VIDEO_LOGIC_POTENCIAINV);
                       }
                    break;

			   case VIDEO_LOGIC_OPERARIT_RAIZ	:
                    signal(SIGFPE,VIDEO_LOGIC_float_error);
					CDOUBLE(retorno->objeto) = pow(CDOUBLE(var1),1./CDOUBLE(var2));
                    if (VIDEO_LOGIC_erro_float_)
                       {
                        VIDEO_FREE_ALLOC_MEM(var1);
                        VIDEO_FREE_ALLOC_MEM(var2);
                        return(VIDEO_LOGIC_POTENCIAINV);
                       }
                    break;

               case VIDEO_LOGIC_OPERARIT_RESTO  :
                    if (CDOUBLE(var2) == 0.)
                       {
                        VIDEO_FREE_ALLOC_MEM(var1);
                        VIDEO_FREE_ALLOC_MEM(var2);
                        return(VIDEO_LOGIC_DIVZERO);
                       }
                    CDOUBLE(retorno->objeto) = CDOUBLE(var1) -
                            (floor(CDOUBLE(var1) / CDOUBLE(var2))*CDOUBLE(var2));
                    break;

               case VIDEO_LOGIC_OPERARIT_SOMA   :
                    CDOUBLE(retorno->objeto) = CDOUBLE(var1) + CDOUBLE(var2);
                    break;

               case VIDEO_LOGIC_OPERARIT_SUB    :
                    CDOUBLE(retorno->objeto) = CDOUBLE(var1) - CDOUBLE(var2);
                    break;

               case VIDEO_LOGIC_OPERARIT_MULT   :
                    CDOUBLE(retorno->objeto) = CDOUBLE(var1) * CDOUBLE(var2);
                    break;

               case VIDEO_LOGIC_OPERARIT_DIVISAO:
                    if (CDOUBLE(var2) == 0.)
                       {
                        VIDEO_FREE_ALLOC_MEM(var1);
                        VIDEO_FREE_ALLOC_MEM(var2);
                        return(VIDEO_LOGIC_DIVZERO);
                       }
                    CDOUBLE(retorno->objeto) = CDOUBLE(var1) / CDOUBLE(var2);
                    break;

               case VIDEO_LOGIC_OPERARIT_SQRT:
                    signal(SIGFPE,VIDEO_LOGIC_float_error);
                    CDOUBLE(retorno->objeto) = pow(CDOUBLE(var2),0.5);
                    if (VIDEO_LOGIC_erro_float_)
                       {
                        VIDEO_FREE_ALLOC_MEM(var2);
                        return(VIDEO_LOGIC_POTENCIAINV);
                       }
                    break;

               case VIDEO_LOGIC_OPERARIT_INT:
//                    printf("INT %10.6f %10.6f\n",CDOUBLE(var2),floor(CDOUBLE(var2)));
                    CDOUBLE(retorno->objeto) = floor(CDOUBLE(var2));
                    break;

               case VIDEO_LOGIC_OPERARIT_DECIMAL:
                    CDOUBLE(retorno->objeto) = CDOUBLE(var2) - floor(CDOUBLE(var2));
                    break;

                default:VIDEO_FREE_ALLOC_MEM(var1);
                        VIDEO_FREE_ALLOC_MEM(var2);
                        return(VIDEO_LOGIC_DESCOPER);
              }

             retorno->tipoobjeto = VIDEO_LOGIC_CONST_NUMERICA;
             retorno->grupo      = VIDEO_LOGIC_CONST;
             flagajuste = TRUE;
            }
        }

//     printf("Flag %d\n",flagajuste);

     if (flagajuste)
        {
         if (work->grupo != VIDEO_LOGIC_OPERARIT_NIVEL1)
            {
             *(work-1) = *retorno;
             flagajuste = 2;
            }
          else
             flagajuste = 1;

//         printf("AJUSTE %d %d %d\n",flagajuste,work->grupo,VIDEO_LOGIC_OPERARIT_NIVEL1);
         VIDEO_movbloco(work,work+flagajuste,W(FP_OFF((*elemento)))-W(FP_OFF(work))-
                        sizeof(VIDEO_LOGIC_OBJETO));

         if (flagajuste == 1)
            {
//             printf("Proximo\n");
             *work = *retorno;
            }

         --(*elemento);

         if (var1)
            {
             --(*elemento);
             VIDEO_FREE_ALLOC_MEM(var1);
            }
         VIDEO_FREE_ALLOC_MEM(var2);
         flagajuste = FALSE;
         continue;
        }
//     printf("Soma\n");
     ++work;
    }
//   printf("Saiu %d\n",nivel);
  }while(TRUE);

/*----------------------------------------------------------------------------
                      PROCESSAO OPERACOES LOGICAS DE COMPARACAO
----------------------------------------------------------------------------*/
 work = inicio;
 while(work <= ((*elemento)-1))
  {
   if (work->grupo == VIDEO_LOGIC_OPERLOGIC)
      {
       if ((ret = VIDEO_LOGIC_consiste_operacao(work,inicio,(*elemento),
            &var1,&var2)) != FALSE)
           return(ret);

       if ((work+1)->tipoobjeto == VIDEO_LOGIC_CONST_NUMERICA)
           funcao = VIDEO_LOGIC_compara_numero;
         else
           funcao = strcmp;

	   *retorno = *(work-1);
	   switch(work->tipoobjeto)
        {
         case VIDEO_LOGIC_OPERLOGICO_MAIOR :
              CDOUBLE(retorno->objeto) = (*funcao)(var1,var2) > 0 ? 1. : 0.;
              break;
         case VIDEO_LOGIC_OPERLOGICO_MAIORI:
              CDOUBLE(retorno->objeto) = (*funcao)(var1,var2) >= 0 ? 1. : 0.;
              break;
         case VIDEO_LOGIC_OPERLOGICO_MENOR :
              CDOUBLE(retorno->objeto) = (*funcao)(var1,var2) < 0 ? 1. : 0.;
              break;
         case VIDEO_LOGIC_OPERLOGICO_MENORI:
              CDOUBLE(retorno->objeto) = (*funcao)(var1,var2) <= 0 ? 1. : 0.;
              break;
         case VIDEO_LOGIC_OPERLOGICO_IGUAL :
              CDOUBLE(retorno->objeto) = (*funcao)(var1,var2) == 0 ? 1. : 0.;
              break;
         case VIDEO_LOGIC_OPERLOGICO_DIFER :
              CDOUBLE(retorno->objeto) = (*funcao)(var1,var2) != 0 ? 1. : 0.;
              break;

		 default:VIDEO_FREE_ALLOC_MEM(var1);
				 VIDEO_FREE_ALLOC_MEM(var2);
				 return(VIDEO_LOGIC_DESCOPER);
        }

       retorno->tipoobjeto = VIDEO_LOGIC_CONST_NUMERICA;
	   retorno->tipoobjeto = VIDEO_LOGIC_CONST_NUMERICA;
       retorno->grupo      = VIDEO_LOGIC_CONST;
	   *(work-1) = *retorno;
	   VIDEO_movbloco(work,work+2,
                      W(FP_OFF((*elemento)))-W(FP_OFF(work))-sizeof(VIDEO_LOGIC_OBJETO));
       --(*elemento);--(*elemento);
       VIDEO_FREE_ALLOC_MEM(var1);
       VIDEO_FREE_ALLOC_MEM(var2);
       continue;
      }
   ++work;
  }

/*----------------------------------------------------------------------------
                    PROCESSAO OPERACOES COM AS PORTAS LOGICAS
----------------------------------------------------------------------------*/
 work = inicio;
 while(work <= ((*elemento)-1))
  {
   if (work->grupo == VIDEO_LOGIC_PORTALOGIC)
      {
       if ((ret = VIDEO_LOGIC_consiste_operacao(work,inicio,(*elemento),
												&var1,&var2)) != FALSE)
		   return(ret);

	   ret1 = ((work-1)->tipoobjeto == VIDEO_LOGIC_CONST_NUMERICA) ?
			  CDOUBLE(var1) != 0.00 							   :
			  strlen(var1)										   ;

	   ret2 = ((work+1)->tipoobjeto == VIDEO_LOGIC_CONST_NUMERICA) ?
			  CDOUBLE(var2) != 0.00 							   :
			  strlen(var2)										   ;

	   *retorno = *(work-1);
	   switch(work->tipoobjeto)
        {
         case VIDEO_LOGIC_OPERLOGICO_AND:
              CDOUBLE(retorno->objeto) = D(ret1 && ret2);
              break;

		 case VIDEO_LOGIC_OPERLOGICO_OR:
              CDOUBLE(retorno->objeto) = D(ret1 || ret2);
              break;

		 default:VIDEO_FREE_ALLOC_MEM(var1);
				 VIDEO_FREE_ALLOC_MEM(var2);
				 return(VIDEO_LOGIC_DESCOPER);
        }

       retorno->tipoobjeto = VIDEO_LOGIC_CONST_NUMERICA;
	   retorno->tipoobjeto = VIDEO_LOGIC_CONST_NUMERICA;
       retorno->grupo      = VIDEO_LOGIC_CONST;

	   *(work-1) = *retorno;
	   VIDEO_movbloco(work,work+2,
                      W(FP_OFF((*elemento)))-W(FP_OFF(work))-sizeof(VIDEO_LOGIC_OBJETO));
       --(*elemento);--(*elemento);
       VIDEO_FREE_ALLOC_MEM(var1);
       VIDEO_FREE_ALLOC_MEM(var2);
       continue;
      }
   ++work;
  }

 return(FALSE);
}

