#include <INCVIDEO.H>

INT2 VIDEO_CALC_operacao(campo,flag,param)
VIDEO_CAMPO_TELA  *campo;
INT2              flag;
VIDEO_NUCLEO_SERV *param;
{
 char       *campodisp[] = {BCALC_status,
                            BCALC_operacao,
                            VD_NULO};
 static int servant      =  VD_NULO;
 VIDEO_ESTMANUT    telas = {VIDEO_sistema_calc_fixa,TELA_PADROES_CALCFIXA};

 double varaux;
 campo->tabskip = VIDEO_tabskip_calculadora;

 switch(I(param->VIDEO_servrec))
  {
   case I(VIDEO_MTTECLA(VD_NULO ,ALT_F)):
   case I(VIDEO_MTTECLA('F'     ,ALT_F)):
   case I(VIDEO_MTTECLA('f'     ,ALT_F)):
   case I(VIDEO_MTTECLA(6       ,ALT_F)):VD_GETBUF(BCALC_decimais,BYTE) =
                                         campo->decimais;
                                         if (VIDEO_CRG_executa_tela(&telas) ==
                                             VD_MTTECLA(VD_NULO,ALT_O))
                                             if (VD_GETBUF(BCALC_decimais,BYTE) !=
                                                 campo->decimais)
                                                {
                                                 varaux = pow(D(10.0),D(campo->decimais));
                                                 VIDEO_CALC_memoria_auxiliar/=varaux;
                                                 VIDEO_CALC_memoria_operacao/=varaux;
                                                 VIDEO_CALC_memoria_display/=varaux;
                                                 CDOUBLE(campo->buffer_binario)/=varaux;

                                                 campo->decimais = VD_GETBUF(BCALC_decimais,BYTE);
                                                 varaux = pow(D(10.0),D(campo->decimais));
                                                 VIDEO_CALC_memoria_auxiliar*=varaux;
                                                 VIDEO_CALC_memoria_operacao*=varaux;
                                                 VIDEO_CALC_memoria_display*=varaux;
                                                 CDOUBLE(campo->buffer_binario)*=varaux;
                                                }
                                         break;

   case I(VIDEO_MTTECLA(VD_NULO ,ALT_T)):
   case I(VIDEO_MTTECLA('T'     ,ALT_T)):
   case I(VIDEO_MTTECLA('t'     ,ALT_T)):
   case I(VIDEO_MTTECLA(20      ,ALT_T)):CDOUBLE(campo->buffer_binario) = 0.0 -
                                         CDOUBLE(campo->buffer_binario);
                                         VIDEO_CALC_status |= VIDEO_CALC_REDISPLAY;
                                         break;

   case I(VIDEO_MTTECLA('M'     ,ALT_M)):
   case I(VIDEO_MTTECLA('m'     ,ALT_M)):if (servant == I(param->VIDEO_servrec))
                                            {
                                             VIDEO_CALC_status &= ~VIDEO_CALC_MEMORIA;
                                             VIDEO_CALC_memoria_auxiliar = 0.0;
                                            }
                                          else
                                            {
                                             CDOUBLE(campo->buffer_binario) =
                                             VIDEO_CALC_memoria_auxiliar;
                                            }
                                         break;

   case I(VIDEO_MTTECLA('A'     ,ALT_A)):
   case I(VIDEO_MTTECLA('a'     ,ALT_A)):
   case I(VIDEO_MTTECLA(VD_NULO ,ALT_A)):
   case I(VIDEO_MTTECLA(1       ,ALT_A)):CDOUBLE(campo->buffer_binario) =
                                         VIDEO_CALC_memoria_display     =
                                         VIDEO_CALC_operacao_secundaria =
                                         VIDEO_CALC_operacao_atual      =
                                         VIDEO_CALC_memoria_operacao    =
                                         VD_NULO;
                                         VIDEO_CALC_status =
                                                VIDEO_CALC_RESSET_DISP | VIDEO_CALC_ATIVA |
                                                (VIDEO_CALC_status&VIDEO_CALC_MEMORIA);
                                         VD_GETBUF(BCALC_status,char) =
                                         VD_GETBUF(BCALC_operacao,char) = ' ';
                                         break;

   case I(VIDEO_MTTECLA('C'     ,ALT_C)):
   case I(VIDEO_MTTECLA('c'     ,ALT_C)):
   case I(VIDEO_MTTECLA(VD_NULO ,ALT_C)):
   case I(VIDEO_MTTECLA(3       ,ALT_C)):CDOUBLE(campo->buffer_binario) =
                                         VD_NULO;
                                         VIDEO_CALC_status =
                                                VIDEO_CALC_DIGITACAO    | VIDEO_CALC_ATIVA |
                                                VIDEO_CALC_RESSET_DISP;
                                         break;

   case I(VIDEO_MTTECLA(42      ,55   )):
   case I(VIDEO_MTTECLA(42      ,9    )):/*MULTIPLICACAO*/
                                         VD_GETBUF(BCALC_operacao,char) = '*';
                                         if (!(VIDEO_CALC_status&VIDEO_CALC_NUMERO))
                                            {
                                             VIDEO_CALC_operacao_secundaria =
                                             VIDEO_CALC_operacao_atual =
                                             VIDEO_CALC_MULTIPLICACAO;
                                             break;
                                            }
                                         if (!(VIDEO_CALC_status&
                                               VIDEO_CALC_OPEREFET) && VIDEO_CALC_operacao_atual)
                                            {
                                             VIDEO_CALC_memoria_operacao=
                                             VIDEO_CALC_memoria_display;
                                             VIDEO_CALC_memoria_display =
                                             CDOUBLE(campo->buffer_binario);
                                             VIDEO_CALC_efetua_operacao(campo);
                                            }
                                         VIDEO_CALC_operacao_secundaria =
                                         VIDEO_CALC_operacao_atual =
                                         VIDEO_CALC_MULTIPLICACAO;
                                         VIDEO_CALC_memoria_operacao=
                                         VIDEO_CALC_memoria_display;
                                         VIDEO_CALC_memoria_display =
                                         CDOUBLE(campo->buffer_binario);
                                         VIDEO_CALC_status |=
                                         (VIDEO_CALC_REDISPLAY|VIDEO_CALC_DIGITACAO);
                                         VIDEO_CALC_status &=
                                                ~VIDEO_CALC_OPERACAO;
                                         VIDEO_CALC_status &= ~VIDEO_CALC_OPEREFET;
                                         VIDEO_CALC_status &= ~VIDEO_CALC_NUMERO;
                                         break;


   case I(VIDEO_MTTECLA(47      ,53   )):/*DIVISAO*/
                                         VD_GETBUF(BCALC_operacao,char) = '/';
                                         if (!(VIDEO_CALC_status&VIDEO_CALC_NUMERO))
                                            {
                                             VIDEO_CALC_operacao_secundaria =
                                             VIDEO_CALC_operacao_atual =
                                             VIDEO_CALC_DIVISAO;
                                             break;
                                            }
                                         if (!(VIDEO_CALC_status&
                                               VIDEO_CALC_OPEREFET) && VIDEO_CALC_operacao_atual)
                                            {
                                             VIDEO_CALC_memoria_operacao=
                                             VIDEO_CALC_memoria_display;
                                             VIDEO_CALC_memoria_display =
                                             CDOUBLE(campo->buffer_binario);
                                             VIDEO_CALC_efetua_operacao(campo);
                                            }
                                         VIDEO_CALC_operacao_secundaria =
                                         VIDEO_CALC_operacao_atual =
                                         VIDEO_CALC_DIVISAO;
                                         VIDEO_CALC_memoria_operacao=
                                         VIDEO_CALC_memoria_display;
                                         VIDEO_CALC_memoria_display =
                                         CDOUBLE(campo->buffer_binario);
                                         VIDEO_CALC_status |=
                                         (VIDEO_CALC_REDISPLAY|VIDEO_CALC_DIGITACAO);
                                         VIDEO_CALC_status &=
                                                ~VIDEO_CALC_OPERACAO;
                                         VIDEO_CALC_status &= ~VIDEO_CALC_OPEREFET;
                                         VIDEO_CALC_status &= ~VIDEO_CALC_NUMERO;
                                         break;

   case I(VIDEO_MTTECLA(43      ,13   )):
   case I(VIDEO_MTTECLA(43      ,78   )):/*SOMA*/
                                         VD_GETBUF(BCALC_operacao,char) = '+';
                                         if (!(VIDEO_CALC_status&VIDEO_CALC_NUMERO))
                                            {
                                             VIDEO_CALC_operacao_secundaria =
                                             VIDEO_CALC_operacao_atual =
                                             VIDEO_CALC_SOMA;
                                             break;
                                            }
                                         if (!(VIDEO_CALC_status&
                                               VIDEO_CALC_OPEREFET) && VIDEO_CALC_operacao_atual)
                                            {
                                             VIDEO_CALC_memoria_operacao=
                                             VIDEO_CALC_memoria_display;
                                             VIDEO_CALC_memoria_display =
                                             CDOUBLE(campo->buffer_binario);
                                             VIDEO_CALC_efetua_operacao(campo);
                                            }
                                         VIDEO_CALC_operacao_secundaria =
                                         VIDEO_CALC_operacao_atual =
                                         VIDEO_CALC_SOMA;
                                         VIDEO_CALC_memoria_operacao=
                                         VIDEO_CALC_memoria_display;
                                         VIDEO_CALC_memoria_display =
                                         CDOUBLE(campo->buffer_binario);
                                         VIDEO_CALC_status |=
                                         (VIDEO_CALC_REDISPLAY|VIDEO_CALC_DIGITACAO);
                                         VIDEO_CALC_status &=
                                                ~VIDEO_CALC_OPERACAO;
                                         VIDEO_CALC_status &= ~VIDEO_CALC_OPEREFET;
                                         VIDEO_CALC_status &= ~VIDEO_CALC_NUMERO;
                                         break;

   case I(VIDEO_MTTECLA(45      ,74   )):
   case I(VIDEO_MTTECLA(45      ,12   )):/*SUBTRACAO*/
                                         VD_GETBUF(BCALC_operacao,char) = '-';
                                         if (!(VIDEO_CALC_status&VIDEO_CALC_NUMERO))
                                            {
                                             VIDEO_CALC_operacao_secundaria =
                                             VIDEO_CALC_operacao_atual =
                                             VIDEO_CALC_SUBTRACAO;
                                             break;
                                            }
                                         if (!(VIDEO_CALC_status&
                                               VIDEO_CALC_OPEREFET) && VIDEO_CALC_operacao_atual)
                                            {
                                             VIDEO_CALC_memoria_operacao=
                                             VIDEO_CALC_memoria_display;
                                             VIDEO_CALC_memoria_display =
                                             CDOUBLE(campo->buffer_binario);
                                             VIDEO_CALC_efetua_operacao(campo);
                                            }
                                         VIDEO_CALC_operacao_secundaria =
                                         VIDEO_CALC_operacao_atual =
                                         VIDEO_CALC_SUBTRACAO;
                                         VIDEO_CALC_memoria_operacao=
                                         VIDEO_CALC_memoria_display;
                                         VIDEO_CALC_memoria_display =
                                         CDOUBLE(campo->buffer_binario);
                                         VIDEO_CALC_status |=
                                         (VIDEO_CALC_REDISPLAY|VIDEO_CALC_DIGITACAO);
                                         VIDEO_CALC_status &=
                                                ~VIDEO_CALC_OPERACAO;
                                         VIDEO_CALC_status &= ~VIDEO_CALC_OPEREFET;
                                         VIDEO_CALC_status &= ~VIDEO_CALC_NUMERO;
                                         break;

   case I(VIDEO_MTTECLA(37      ,6    )):/*PERCENTUAL   */
                                         VIDEO_CALC_memoria_operacao=
                                         VIDEO_CALC_memoria_display;
                                         VIDEO_CALC_memoria_display =
                                         CDOUBLE(campo->buffer_binario);
                                         VIDEO_CALC_status &= ~VIDEO_CALC_DIGITACAO;
                                         VIDEO_CALC_calcula_percentual(campo);
                                         VIDEO_CALC_operacao_secundaria = VD_NULO;
                                         VIDEO_CALC_status |=
                                         (VIDEO_CALC_REDISPLAY|VIDEO_CALC_DIGITACAO);
                                         VIDEO_CALC_status &= ~VIDEO_CALC_NUMERO;
                                         VIDEO_CALC_status &= ~VIDEO_CALC_OPEREFET;
                                         VIDEO_CALC_memoria_operacao=
                                         VIDEO_CALC_memoria_display;
                                         VIDEO_CALC_memoria_display =
                                         CDOUBLE(campo->buffer_binario);
                                         break;

   case I(VIDEO_MTTECLA(61      ,13   )):/*IGUAL*/
   case I(VIDEO_MTTECLA(13      ,28   )):/*IGUAL*/
   case I(VIDEO_MTTECLA(10      ,28   )):/*IGUAL*/
   case I(VIDEO_MTTECLA(15      ,13   )):/*IGUAL*/
                                         if (VIDEO_CALC_status&VIDEO_CALC_DIGITACAO)
                                            {
                                             VIDEO_CALC_memoria_operacao=
                                             VIDEO_CALC_memoria_display;
                                             VIDEO_CALC_memoria_display =
                                             CDOUBLE(campo->buffer_binario);
                                             VIDEO_CALC_status &= ~VIDEO_CALC_DIGITACAO;
                                            }
                                         if (VIDEO_CALC_operacao_secundaria)
                                            {
                                             VIDEO_CALC_efetua_operacao(campo);
                                             VIDEO_CALC_memoria_operacao=
                                             VIDEO_CALC_memoria_display;
                                             VIDEO_CALC_memoria_display =
                                             CDOUBLE(campo->buffer_binario);
                                             VIDEO_CALC_status |= VIDEO_CALC_REDISPLAY;
                                             VIDEO_CALC_operacao_secundaria =
                                             VIDEO_CALC_operacao_atual = VD_NULO;
                                            }
                                          else
                                            VIDEO_CALC_status |= (VIDEO_CALC_REDISPLAY|VIDEO_CALC_DIGITACAO);

                                         break;

   case I(VIDEO_MTTECLA(VD_NULO ,F3   )):/*mem +*/
                                         VIDEO_CALC_memoria_auxiliar +=
                                         CDOUBLE(campo->buffer_binario);
                                         VIDEO_CALC_status |= (VIDEO_CALC_REDISPLAY|VIDEO_CALC_MEMORIA);
                                         break;

   case I(VIDEO_MTTECLA(VD_NULO ,F4   )):/*mem -*/
                                         VIDEO_CALC_memoria_auxiliar -=
                                         CDOUBLE(campo->buffer_binario);
                                         VIDEO_CALC_status |= VIDEO_CALC_REDISPLAY;
                                         VIDEO_CALC_status |= (VIDEO_CALC_REDISPLAY|VIDEO_CALC_MEMORIA);
                                         break;

   case I(VIDEO_MTTECLA(VD_NULO ,F5   )):if ((CDOUBLE(campo->buffer_binario) > -0.000000000000001) &&
											 (CDOUBLE(campo->buffer_binario) <	0.000000000000001))
											{
                                             VIDEO_CALC_status |= VIDEO_CALC_ERRO;
                                             VIDEO_CALC_memoria_operacao=
                                             VIDEO_CALC_memoria_display =
                                             CDOUBLE(campo->buffer_binario);
                                             VIDEO_CALC_status |= VIDEO_CALC_REDISPLAY;
                                             VD_GETBUF(BCALC_status,char) = 'E';
											 break;
											}
                                         if (campo->decimais)
											CDOUBLE(campo->buffer_binario) /= pow(D(10.0),D(campo->decimais));
                                         CDOUBLE(campo->buffer_binario) = 1.0 / CDOUBLE(campo->buffer_binario);
                                         if (campo->decimais)
                                            CDOUBLE(campo->buffer_binario) *= pow(D(10.0),D(campo->decimais));
                                         VIDEO_CALC_status |= VIDEO_CALC_REDISPLAY;
                                         break;

   case I(VIDEO_MTTECLA(VD_NULO ,F6   )):/* x e y*/
                                         VIDEO_CALC_memoria_operacao=
                                         VIDEO_CALC_memoria_display =
                                         CDOUBLE(campo->buffer_binario);
                                         VIDEO_CALC_status |= VIDEO_CALC_REDISPLAY;
                                         VIDEO_CALC_operacao_secundaria =
                                         VIDEO_CALC_operacao_atual =
                                         VIDEO_CALC_EXPONECIAL;
                                         break;

   case I(VIDEO_MTTECLA(VD_NULO ,F7   )):if (campo->decimais)
                                            CDOUBLE(campo->buffer_binario) /= pow(D(10.0),D(campo->decimais));
                                         CDOUBLE(campo->buffer_binario) = pow(CDOUBLE(campo->buffer_binario),2);
                                         if (campo->decimais)
                                            CDOUBLE(campo->buffer_binario) *= pow(D(10.0),D(campo->decimais));
                                         VIDEO_CALC_status |= VIDEO_CALC_REDISPLAY;
                                         break;

   case I(VIDEO_MTTECLA(VD_NULO ,F8   )):if (CDOUBLE(campo->buffer_binario) < 0)
                                            {
                                             VIDEO_CALC_status |= VIDEO_CALC_ERRO;
                                             VIDEO_CALC_status |= VIDEO_CALC_REDISPLAY;
                                             VIDEO_CALC_memoria_operacao=
                                             VIDEO_CALC_memoria_display =
                                             CDOUBLE(campo->buffer_binario);
                                             VD_GETBUF(BCALC_status,char) = 'E';
											 break;
                                            }
                                         if (campo->decimais)
                                            CDOUBLE(campo->buffer_binario) /= pow(D(10.0),D(campo->decimais));
                                         CDOUBLE(campo->buffer_binario) = pow(CDOUBLE(campo->buffer_binario),0.5);
                                         if (campo->decimais)
                                            CDOUBLE(campo->buffer_binario) *= pow(D(10.0),D(campo->decimais));
                                         VIDEO_CALC_status |= VIDEO_CALC_REDISPLAY;
                                         break;

   case I(VIDEO_MTTECLA(VD_NULO ,F1   )):break;
  }

 if (CDOUBLE(campo->buffer_binario) > 999999999999999.0 ||
     CDOUBLE(campo->buffer_binario) < -999999999999999.0)
    {
     VIDEO_CALC_status |= VIDEO_CALC_ERRO;
     VD_GETBUF(BCALC_status,char) = 'E';
     VIDEO_CALC_status |= VIDEO_CALC_REDISPLAY;
     VIDEO_CALC_memoria_operacao=
     VIDEO_CALC_memoria_display =
     CDOUBLE(campo->buffer_binario);
    }


 if (!(VIDEO_CALC_status&VIDEO_CALC_ERRO))
     VD_GETBUF(BCALC_status,char) = (VIDEO_CALC_status&VIDEO_CALC_MEMORIA) ?
               'M' : ' ';
 VIDEO_TELA_disp_campo(campo,campodisp,&param,VIDEO_DISPLAY_CAMPO,FALSE);
 servant = I(param->VIDEO_servrec);
 return(TRUE);
}

