#include<INCVIDEO.H>

char VIDEO_EDITA_testa_caracter_na_mascara(caracter,mascara,carmont,col)
char *caracter,
     mascara,
     *carmont;
INT2  *col;
{
 BOOLEAN retteste,
         ret;
 char    carac;

 carac = *caracter;

 retteste = VIDEO_ISDIGIT(carac)        |
            (VIDEO_ISCARACMAI(carac)<<1)|
            (VIDEO_ISCARACMIN(carac)<<2)|
            (VIDEO_ISLIMCAR(carac)  <<3)|
            (VIDEO_ISSPACE(carac)   <<4);

 *carmont = ' ';

 if (col)
    ++*col;

 switch(mascara)
  {
   case '9' :*carmont = '0';
             return(VIDEO_EDITA_TESTA_Z(retteste)||0);
   case 'B' :
   case 'Z' :
   case 'z' :
   case 'b' :return(VIDEO_EDITA_TESTA_B(retteste)||0);

/*U     letras maiusculas mais espaco*/
   case 'U' :
   if ((ret = (VIDEO_EDITA_TESTA_U(retteste)||0)) == FALSE)
                  if (VIDEO_ISCARACMIN(carac))
                     {
                      *caracter &= ~VD_B5;
                      ret = TRUE;
                     }
              return(ret);

/*u     letras minusculas mais espaco*/
   case 'u' :if ((ret = (VIDEO_EDITA_TESTA_u(retteste)||0)) == FALSE)
                  if (VIDEO_ISCARACMAI(carac))
                     {
                      *caracter |= VD_B5;
                      ret = TRUE;
                     }
              return(ret);

   case 'l' :return(VIDEO_EDITA_TESTA_l(retteste)||0);

/*F     letras maiusculas mais numeros mais espaco*/
   case 'F' :if ((ret = (VIDEO_EDITA_TESTA_F(retteste)||0)) == FALSE)
                  if (VIDEO_ISCARACMIN(carac))
                     {
                      *caracter &= ~VD_B5;
                      ret = TRUE;
                     }
              return(ret);

/*f     letras minusculas mais numeros mais espaco*/
   case 'f' :if ((ret = (VIDEO_EDITA_TESTA_f(retteste)||0)) == FALSE)
                  if (VIDEO_ISCARACMAI(carac))
                     {
                      *caracter |= VD_B5;
                      ret = TRUE;
                     }
              return(ret);

   case 'H' :return(VIDEO_EDITA_TESTA_H(retteste)||0);

/*X     de 32 a 126 menos letras minusculas*/
   case 'X' :if ((ret = (VIDEO_EDITA_TESTA_X(retteste)||0)) == FALSE)
                  if (VIDEO_ISCARACMIN(carac))
                     {
                      *caracter &= ~VD_B5;
                      ret = TRUE;
                     }
              return(ret);

/*x     de 32 a 126 menos letras maiusculas*/
   case 'x' :if ((ret = (VIDEO_EDITA_TESTA_x(retteste)||0)) == FALSE)
                  if (VIDEO_ISCARACMAI(carac))
                     {
                      *caracter |= VD_B5;
                      ret = TRUE;
                     }
              return(ret);

   case 'Q' :return(VIDEO_EDITA_TESTA_Q(retteste)||0);

/*T     de 32 a 126 menos letras minusculas menos numeros*/
   case 'T' :if ((ret = (VIDEO_EDITA_TESTA_T(retteste)||0)) == FALSE)
                  if (VIDEO_ISCARACMIN(carac))
                     {
                      *caracter &= ~VD_B5;
                      ret = TRUE;
                     }
              return(ret);

/*t     de 32 a 126 menos letras maiusculas menos numeros*/
   case 't' :if ((ret = (VIDEO_EDITA_TESTA_t(retteste)||0)) == FALSE)
                  if (VIDEO_ISCARACMAI(carac))
                     {
                      *caracter |= VD_B5;
                      ret = TRUE;
                     }
              return(ret);

   case 'q' :return(VIDEO_EDITA_TESTA_q(retteste)||0);
   case 'G' :return(TRUE);

/*E     letras maiusculas*/
   case 'E' :if ((ret = (VIDEO_EDITA_TESTA_E(retteste)||0)) == FALSE)
                  if (VIDEO_ISCARACMIN(carac))
                     {
                      *caracter &= ~VD_B5;
                      ret = TRUE;
                     }
              return(ret);

   case 'L' :return(VIDEO_EDITA_TESTA_L(retteste)||0);

/*C     letras maiusculas mais numeros*/
   case 'C' :if ((ret = (VIDEO_EDITA_TESTA_C(retteste)||0)) == FALSE)
                  if (VIDEO_ISCARACMIN(carac))
                     {
                      *caracter &= ~VD_B5;
                      ret = TRUE;
                     }
              return(ret);

   case 'O' :return(VIDEO_EDITA_TESTA_O(retteste)||0);

/*c     letras minusculas mais numeros*/
   case 'c' :if ((ret = (VIDEO_EDITA_TESTA_c(retteste)||0)) == FALSE)
                  if (VIDEO_ISCARACMAI(carac))
                     {
                      *caracter |= VD_B5;
                      ret = TRUE;
                     }
              return(ret);

/*e     letras minusculas*/
   case 'e' :if ((ret = (VIDEO_EDITA_TESTA_e(retteste)||0)) == FALSE)
                  if (VIDEO_ISCARACMAI(carac))
                     {
                      *caracter |= VD_B5;
                      ret = TRUE;
                     }
              return(ret);
   case 'D' :
   case 'M' :
   case 'A' :
   case 'h' :
   case 'm' :
   case 's' :return(VIDEO_EDITA_TESTA_Z(retteste)||0);
   default  :return(C(2));
  }
}

