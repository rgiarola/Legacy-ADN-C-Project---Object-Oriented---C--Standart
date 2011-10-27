/* ----------------------------------------------------------------------------
   VIDEO_getkbd()     -> Leitura initerrupta do teclado
                         Verifica o pressionamento de qq tecla, mouse ou ativa o
                         SAVE SCREEN
   VIDEO_save_screen()-> Save Screen Visao Total

   ---------------------------------------------------------------------------- */
#include <INCVIDEO.H>

extern int VIDEO_save_screen_tempo;

INT2 local_funcao_nula(BYTE ascii,BYTE scan,INT2 flag)
{
 return FALSE;
}

INT2  VIDEO_getkbd(ascii, scan)
BYTE    *ascii,
        *scan;
{
 VD_time tempo[2],
         save_scren,time_work;
 BYTE    far *teclado;
 INT2  (*funcao_salva)();

 INT2    botpres[2] ,numclick[2],
         colclick[2],linclick[2],
         col[2]     ,lin[2]     ,
         flagtime   ,flagtrav   ,
         contpress  ,flagbotom  ;

 teclado = MK_FP(0X0040,0X0017);

 VIDEO_MOUSE_botpres = VIDEO_MOUSE_numclick = 0;

 VIDEO_MOUSE_coluna_ant = VIDEO_MOUSE_coluna_atual;
 VIDEO_MOUSE_linha_ant  = VIDEO_MOUSE_linha_atual;

 contpress = 0;

 VIDEO_MOUSE_coluna_atual = VIDEO_MOUSE_colclick =
 VIDEO_MOUSE_linha_atual  = VIDEO_MOUSE_linclick = FALSE;

#ifndef APLIC_POS4000
 if (VIDEO_MOUSE_ativo && VIDEO_MOUSE_cursor_ativo)
    {
     VIDEO_MOUSE_intbot(&botpres[contpress] ,&numclick[contpress],
                        &colclick[contpress],&linclick[contpress]);
     VIDEO_MOUSE_getpos(&col[contpress],&lin[contpress]);
    }
#endif

 botpres[0]  = botpres[1] = numclick[0] = numclick[1] =
 colclick[0] = colclick[1] = linclick[0] = linclick[1] = 0;

 *ascii = *scan = 0;

 VD_gettime(&save_scren);

 while(!VIDEO_getkey(ascii, scan))
  {
   //char ativo[50];
   //static long cont=0;
   //sprintf (ativo," ATIVADO %d CONT %ld",VIDEO_save_screen_ja_ativo,cont++);
   //VD_tprt_l (1,1,ativo,7);

#ifndef APLIC_POS4000
   VD_gettime(&time_work);
#endif

 if (VIDEO_save_screen_tempo <= 0)
    VIDEO_save_screen_tempo = 180;

#ifndef APLIC_POS4000
   if (((L(VD_timeHor(time_work)) * 3600L - L(VD_timeHor(save_scren)) * 3600L +
         L(VD_timeMin(time_work)) * 60L   - L(VD_timeMin(save_scren)) * 60L   +
         L(VD_timeSeg(time_work))         - L(VD_timeSeg(save_scren))         )
         >  VIDEO_save_screen_tempo) &&
       !VIDEO_save_screen_ja_ativo)
      {
       // VD_gtxy(1,1); printf ("Tempo %d",VIDEO_save_screen_tempo); VIDEO_espera(1);
       disable();
       funcao_salva = VIDEO_TECLADO_funcao_auxiliar;
       VIDEO_TECLADO_funcao_auxiliar = local_funcao_nula;
       VIDEO_save_screen_ja_ativo = TRUE;
       enable();

       if (!VIDEO_save_screen)
           VIDEO_save_screen_default(VIDEO_TECLADO_funcao_auxiliar);
        else
           (*VIDEO_save_screen)(VIDEO_TECLADO_funcao_auxiliar);

       VIDEO_save_screen_ja_ativo = FALSE;

       disable();
       VIDEO_TECLADO_funcao_auxiliar=funcao_salva;
       enable ();
       VD_gettime(&time_work);
       save_scren = time_work;
       continue;
      }

   if (VIDEO_MOUSE_ativo && VIDEO_MOUSE_cursor_ativo)
      {
       if (VIDEO_MOUSE_intbotpres())
          {
           VIDEO_MOUSE_intbot(&botpres[contpress] ,&numclick[contpress],
                              &colclick[contpress],&linclick[contpress]);
           VIDEO_MOUSE_getpos(&col[contpress],&lin[contpress]);

           if (contpress)
              {
               if ((colclick[0] == colclick[1]) &&
                   (linclick[0] == linclick[1]))
                   VIDEO_MOUSE_numclick += numclick[contpress];
                 else
                   {
                    botpres[0]  = botpres[1];
                    numclick[0] = numclick[1];
                    colclick[0] = colclick[1];
                    linclick[0] = linclick[1];
                    contpress = 0;
                    VIDEO_MOUSE_numclick = numclick[contpress];
                    continue;
                   }
              }
            else
              VIDEO_MOUSE_numclick += numclick[contpress];

           VD_gettime(&tempo[contpress]);

           if (contpress)
              {
               long int val1,val2;
               val1 = L(VD_timeHor(tempo[0])) * 360000L +
                      L(VD_timeMin(tempo[0])) * 6000L   +
                      L(VD_timeSeg(tempo[0])) * 100L    +
                      L(VD_timeHsc(tempo[0]));

               val2 = L(VD_timeHor(tempo[1])) * 360000L +
                      L(VD_timeMin(tempo[1])) * 6000L   +
                      L(VD_timeSeg(tempo[1])) * 100L    +
                      L(VD_timeHsc(tempo[1]));

               if (val2 < val1)
                  {
                   tempo[0] = tempo[1];
                   continue;
                  }

               flagtime = ((val2 - val1) < L(VIDEO_MOUSE_timeout));

               flagtrav = ((val2 - val1) < L(VIDEO_MOUSE_timetrav));
              }
            else
              {
               ++contpress;
               continue;
              }


           if (!VIDEO_MOUSE_numclick)
              {
               flagbotom = (botpres[0] > 1 || botpres[1] > 1);

               if ((VIDEO_MOUSE_flagtravado            &&
                    (col[1] == VIDEO_MOUSE_coluna_ant) &&
                    (lin[1] == VIDEO_MOUSE_linha_ant)) || flagbotom)
                  {
                   if (!VIDEO_MOUSE_timetrav && !flagbotom)
                      continue;

                   if (flagtrav)
                      continue;
                  }

               VIDEO_MOUSE_botpres = botpres[0];
               *ascii = VIDEO_MOUSE_botpres;
               *scan  = VIDEO_MOUSE_BOTTRV;
               VIDEO_MOUSE_colclick = VIDEO_MOUSE_coluna_atual = col[1];
               VIDEO_MOUSE_linclick = VIDEO_MOUSE_linha_atual  = lin[1];
               break;
              }
            else
              {
               if (flagtime)
                  continue;

               if (VIDEO_MOUSE_numclick > 2)
                   VIDEO_MOUSE_numclick = 2;

               *ascii = VIDEO_MOUSE_numclick;
               *scan  = VIDEO_MOUSE_BOTCLICK;
               flagtime = numclick[1] > 0;
               VIDEO_MOUSE_botpres = botpres[flagtime];
               VIDEO_MOUSE_colclick = VIDEO_MOUSE_coluna_atual = col[flagtime];
               VIDEO_MOUSE_linclick = VIDEO_MOUSE_linha_atual  = lin[flagtime];
               break;
              }
          }
        else
          {
           long int val1,val2;

           if (!contpress)
              continue;

           VD_gettime(&tempo[contpress]);
           val1 = L(VD_timeHor(tempo[0])) * 360000L +
                  L(VD_timeMin(tempo[0])) * 6000L   +
                  L(VD_timeSeg(tempo[0])) * 100L    +
                  L(VD_timeHsc(tempo[0]));
           val2 = L(VD_timeHor(tempo[1])) * 360000L +
                  L(VD_timeMin(tempo[1])) * 6000L   +
                  L(VD_timeSeg(tempo[1])) * 100L    +
                  L(VD_timeHsc(tempo[1]));

           if (val2 < val1)
              {
               tempo[0] = tempo[1];
               continue;
              }

           flagtime = ((val2 - val1) < L(VIDEO_MOUSE_timeout));

           flagtrav = ((val2 - val1) < L(VIDEO_MOUSE_timetrav));

           if (!VIDEO_MOUSE_numclick)
              {
               flagbotom = (botpres[0] > 1 || botpres[1] > 1);

               if ((VIDEO_MOUSE_flagtravado            &&
                    (col[1] == VIDEO_MOUSE_coluna_ant) &&
                    (lin[1] == VIDEO_MOUSE_linha_ant)) || flagbotom)
                  {
                   if (!VIDEO_MOUSE_timetrav && !flagbotom)
                      continue;

                   if (flagtrav)
                      continue;
                  }

               VIDEO_MOUSE_botpres = botpres[0];
               *ascii = VIDEO_MOUSE_botpres;
               *scan  = VIDEO_MOUSE_BOTTRV;
               VIDEO_MOUSE_colclick = VIDEO_MOUSE_coluna_atual = col[1];
               VIDEO_MOUSE_linclick = VIDEO_MOUSE_linha_atual  = lin[1];
               break;
              }
            else
              {
               if (flagtime)
                  continue;

               if (VIDEO_MOUSE_numclick > 2)
                   VIDEO_MOUSE_numclick = 2;

               if (!((colclick[0] == colclick[1]) &&
                   (linclick[0] == linclick[1])))
                   {
                    botpres[0]  = botpres[1];
                    numclick[0] = numclick[1];
                    colclick[0] = colclick[1];
                    linclick[0] = linclick[1];
                    contpress = 0;
                    VIDEO_MOUSE_numclick = numclick[contpress];
                    continue;
                   }

               *ascii = VIDEO_MOUSE_numclick;
               *scan  = VIDEO_MOUSE_BOTCLICK;
               flagtime = numclick[1] > 0;
               VIDEO_MOUSE_botpres = botpres[flagtime];
               VIDEO_MOUSE_colclick = VIDEO_MOUSE_coluna_atual = col[flagtime];
               VIDEO_MOUSE_linclick = VIDEO_MOUSE_linha_atual  = lin[flagtime];
               break;
              }
          }
      }
#endif
   }

  if ((*scan == PGDN) &&
      (*teclado&(VIDEO_TECLADO_SHIFTESQ|VIDEO_TECLADO_SHIFTDIR)))
     {
      *ascii = B(0X00);
      *scan  = SHIFT_PGDN;
     }

  if ((*scan == PGUP) &&
      (*teclado&(VIDEO_TECLADO_SHIFTESQ|VIDEO_TECLADO_SHIFTDIR)))
     {
      *ascii = B(0X00);
      *scan  = SHIFT_PGUP;
     }

  if (VIDEO_TECLADO_funcao_auxiliar)
      (*VIDEO_TECLADO_funcao_auxiliar)(ascii,scan,TRUE);

  return(TRUE);
}

VD_VOID VIDEO_save_screen_default(funcao)
int (*funcao)();
{
 int   col,lin,sentido,corfrente,atribfrente,corfundo,atribfundo,
       fim,tamanho,cont,flagmouse = FALSE,colant,linant,
       colm = 0,linm = 0;
 char  buffer[100],vezes;
 BYTE  ascii,scan;

 if (VIDEO_MOUSE_ativo && VIDEO_MOUSE_cursor_ativo)
    {
     VIDEO_MOUSE_deshabcursor();
     flagmouse = TRUE;
     VIDEO_MOUSE_getpos(&colm,&linm);
    }

 VD_PUSHWIN(1,80,1,25);
 VD_getxy(&colant,&linant);

 tamanho = strlen(VIDEO_save_screen_mens);

 // Teste
 if (VIDEO_display_cascata_save_screen(colm,linm,funcao))
    {
     VD_POPWIN();
     if (flagmouse)
        VIDEO_MOUSE_habcursor();
     VD_gtxy(colant,linant);
     return;
    }


 // Loop
 do
  {
   rand();
   rand();
   VD_CLS;
   vezes = random(30)+1;

   do
    {
     sentido= random(11) > 5;
     col = random(78) + 2;
     lin = random(23) + 2;
     atribfrente = (random(11) > 5) ? VD_BRIL : VD_NORMAL;
     atribfundo  = (random(11) > 5) ? VD_INTER : VD_NORMAL;
     corfrente   = random(8);
     do
      {
       corfundo  = random(8);
       if (funcao)
           (*funcao)((char *) VD_NULO,(int) VD_NULO,(char *) VD_NULO);
      }while(corfundo == corfrente);

     if (!sentido)
        {
         if ((col + tamanho - 1) > 79)
            fim = 79 - col + 1;
          else
            fim = tamanho;
        }
      else
        if ((lin + tamanho - 1) > 24)
            fim = 24 - lin + 1;
          else
            fim = tamanho;

     VIDEO_movbloco(buffer,VIDEO_save_screen_mens,fim);
     buffer[fim] = 0;

     VIDEO_display_abre_save_screen(col,lin,buffer,sentido,
                       VD_FORMATO(corfrente,atribfrente,corfundo,atribfundo),
                       funcao);

     for (cont = 0;cont < 10;cont++)
         {
          /*
             Esta L¢gica est  em Testes ....
             Verificar se realmente ‚ necessario chamar a fun‡„o auxiliar
             que trata teclado, dentro do Save Screen.
             -----------------------------------------
          if (funcao)
              (*funcao)((char *) VD_NULO,(int) VD_NULO,(char *) VD_NULO);
           */

          VIDEO_espera(5);
          VIDEO_MOUSE_getpos(&col,&lin);

          if (VD_getkey(&ascii,&scan) || VIDEO_MOUSE_intbotpres() ||
              (linm && colm && ((colm != col) || (linm != lin))))
             {
              VD_POPWIN();
              if (flagmouse)
                 VIDEO_MOUSE_habcursor();
              VD_gtxy(colant,linant);
              // VIDEO_save_screen_ja_ativo = FALSE;
              return;
             }
         }
    } while(--vezes > 0);

   if (VIDEO_display_cascata_save_screen(colm,linm,funcao))
      {
       VD_POPWIN();
       if (flagmouse)
          VIDEO_MOUSE_habcursor();
       VD_gtxy(colant,linant);
       return;
      }

  }while(TRUE);

}

VD_VOID VIDEO_display_abre_save_screen(col,lin,buffer,sentido,cor,funcao)
int  col,lin;
char *buffer;
int  sentido;
int  cor;
int  (*funcao)();
{
 char texto[100];
 int  lini,linf,coli,colf,
      tam,saida,cont;

 saida = 0;

 cont = 0;

 if (sentido)
    {
     linf = lini = lin+(strlen(buffer)-1)/2;

     coli = col - 1;
     colf = col + 1;

     do
      {
       VD_gtxy(coli,lini);
       if (kbhit())
           return;

       if (lini == linf)
          {
           VD_horizontal_simples(coli,colf,lini,cor);
          }
        else
          {
           VIDEO_box_simples(coli,colf,lini,linf,cor);
           tam = ((linf-1)-(lini+1)) + 1;
           if (tam > 0)
              {
               VIDEO_movbloco(texto,buffer,tam);
               texto[tam] = 0;
               VD_tprt_c(col,lini+1,texto,cor);
              }
          }

       if (lini > lin)
          --lini;
        else
          saida |= B00;

       if (linf < (lin + strlen(buffer)+1) && linf < 25)
          ++linf;
        else
          saida |= B01;

       if (funcao)
           (*funcao)((char *) VD_NULO,(int) VD_NULO,(char *) VD_NULO);

       VIDEO_espera(1);

      }while((saida&(B00|B01)) != (B00|B01));
    }
  else
    {
     colf = coli = col+(strlen(buffer)-1)/2;
     lini = lin - 1;
     linf = lin + 1;
     do
      {
       if (kbhit())
           return;

       VD_gtxy(coli,lini);
       if (colf == coli)
          {
           VD_vertical_simples(lini,linf,coli,cor);
          }
        else
          {
           VIDEO_box_simples(coli,colf,lini,linf,cor);
           tam = ((colf-1)-(coli+1)) + 1;
           if (tam)
              {
               VIDEO_movbloco(texto,buffer,tam);
               texto[tam] = 0;
               VD_tprt_l(coli+1,lin,texto,cor);
              }
          }

       if (coli > col)
          --coli;
        else
          saida |= B00;

       if (colf < (col + strlen(buffer)+1) && colf < 80)
          ++colf;
        else
          saida |= B01;

       if (funcao)
           (*funcao)((char *) VD_NULO,(int) VD_NULO,(char *) VD_NULO);

       VIDEO_espera(1);

      }while((saida&(B00|B01)) != (B00|B01));
    }
}



int VIDEO_display_cascata_save_screen(colm,linm,funcao)
int colm,linm;
int (*funcao)();
{
 int    valor,col,lin,colrnd,linrnd,cont;
 BYTE   ascii,scan;
 double passo,tempo;

 valor = random(10)+5;
 col = colm;
 lin = linm;

 switch(random(2))
  {
   case 0:while(valor--)
           {
            VIDEO_MOUSE_getpos(&col,&lin);

            if (VD_getkey(&ascii,&scan) || VIDEO_MOUSE_intbotpres() ||
                (linm && colm && ((colm != col) || (linm != lin))))
               return(TRUE);

            switch(random(4))
             {
              case 0:VIDEO_sobe_jan(1,80,2,25,1,0);
                     break;

              case 1:VIDEO_desce_jan(1,80,1,24,1,0);
                     break;

              case 2:VIDEO_dir_jan(1,79,1,25,1,0);
                     break;

              case 3:VIDEO_esq_jan(2,80,1,25,1,0);
                     break;
             }

            if (funcao)
                (*funcao)((char *) VD_NULO,(int) VD_NULO,(char *) VD_NULO);

            VIDEO_espera(5);
           }

          valor = 500;

          while(valor--)
           {
            colrnd = random(80)+1;
            linrnd = random(24)+1;
            passo  = 5. / (25-linrnd);

            if (*(VIDEO_FISICO(linrnd,colrnd)) && *(VIDEO_FISICO(linrnd,colrnd)) != ' ')
                for (cont = 0;linrnd < 25;linrnd++,cont++)
                    {
                     VIDEO_desce_jan(colrnd,colrnd,linrnd,linrnd,1,0);

                     VIDEO_MOUSE_getpos(&col,&lin);

                     if (VD_getkey(&ascii,&scan) || VIDEO_MOUSE_intbotpres() ||
                         (linm && colm && ((colm != col) || (linm != lin))))
                        return(TRUE);

                     if (funcao)
                         (*funcao)((char *) VD_NULO,(int) VD_NULO,(char *) VD_NULO);

                     if (!((random(100)+1)%5))
                         VIDEO_espera(1);
                    }
                  else
                    {
                     VIDEO_MOUSE_getpos(&col,&lin);

                     if (VD_getkey(&ascii,&scan) || VIDEO_MOUSE_intbotpres() ||
                         (linm && colm && ((colm != col) || (linm != lin))))
                        return(TRUE);
                    }
           }
          break;

   case 1:valor = random(500)+1;
          while(valor--)
           {
            char carac,cor;
            colrnd = random(80)+1;
            linrnd = random(25)+1;
            carac  = random(2)+1;
            cor    = random(255)+1;

            VIDEO_plotcarac(colrnd,linrnd,carac,cor);

            VIDEO_MOUSE_getpos(&col,&lin);

            if (VD_getkey(&ascii,&scan) || VIDEO_MOUSE_intbotpres() ||
                (linm && colm && ((colm != col) || (linm != lin))))
               return(TRUE);

            if (funcao)
                (*funcao)((char *) VD_NULO,(int) VD_NULO,(char *) VD_NULO);

            if (!((random(100)+1)%5))
                VIDEO_espera(1);
           }
          break;
  }


 VIDEO_display_abre_save_screen((80-strlen(display_save_screen_titulo))/2,12,
                                display_save_screen_titulo,FALSE,random(255)+1,
                                funcao);

 switch(random(10))
  {
   case 0:for (cont = 1;cont < 25;cont++)
              {
               VIDEO_MOUSE_getpos(&col,&lin);

               if (VD_getkey(&ascii,&scan) || VIDEO_MOUSE_intbotpres() ||
                   (linm && colm && ((colm != col) || (linm != lin))))
                  return(TRUE);
               VIDEO_sobe_jan(1,80,2,25,1,0);

               if (funcao)
                   (*funcao)((char *) VD_NULO,(int) VD_NULO,(char *) VD_NULO);

               VIDEO_espera(1);
              }
          break;

   case 1:for (cont = 1;cont < 25;cont++)
              {
               VIDEO_MOUSE_getpos(&col,&lin);

               if (VD_getkey(&ascii,&scan) || VIDEO_MOUSE_intbotpres() ||
                   (linm && colm && ((colm != col) || (linm != lin))))
                  return(TRUE);
               VIDEO_desce_jan(1,80,1,24,1,0);

               if (funcao)
                   (*funcao)((char *) VD_NULO,(int) VD_NULO,(char *) VD_NULO);

               VIDEO_espera(1);
              }
          break;

   case 2:for (cont = 1;cont < 80;cont++)
              {
               VIDEO_MOUSE_getpos(&col,&lin);

               if (VD_getkey(&ascii,&scan) || VIDEO_MOUSE_intbotpres() ||
                   (linm && colm && ((colm != col) || (linm != lin))))
                  return(TRUE);
               VIDEO_dir_jan(1,79,1,25,1,0);

               if (funcao)
                   (*funcao)((char *) VD_NULO,(int) VD_NULO,(char *) VD_NULO);

               VIDEO_espera(1);
              }
          break;

   case 3:for (cont = 1;cont < 80;cont++)
              {
               VIDEO_MOUSE_getpos(&col,&lin);

               if (VD_getkey(&ascii,&scan) || VIDEO_MOUSE_intbotpres() ||
                   (linm && colm && ((colm != col) || (linm != lin))))
                  return(TRUE);
               VIDEO_esq_jan(2,80,1,25,1,0);

               if (funcao)
                   (*funcao)((char *) VD_NULO,(int) VD_NULO,(char *) VD_NULO);

               VIDEO_espera(1);
              }
          break;

   case 4:for (cont = 1;cont < 40;cont++)
              {
               VIDEO_MOUSE_getpos(&col,&lin);

               if (VD_getkey(&ascii,&scan) || VIDEO_MOUSE_intbotpres() ||
                   (linm && colm && ((colm != col) || (linm != lin))))
                  return(TRUE);

               VIDEO_esq_jan(2 ,40,1,25,1,0);
               VIDEO_dir_jan(41,79,1,25,1,0);

               if (funcao)
                   (*funcao)((char *) VD_NULO,(int) VD_NULO,(char *) VD_NULO);

               VIDEO_espera(1);
              }
          break;

   case 5:for (cont = 1;cont < 40;cont++)
              {
               VIDEO_MOUSE_getpos(&col,&lin);

               if (VD_getkey(&ascii,&scan) || VIDEO_MOUSE_intbotpres() ||
                   (linm && colm && ((colm != col) || (linm != lin))))
                  return(TRUE);

               VIDEO_dir_jan(1,40,1,25,1,0);
               VIDEO_esq_jan(41,80,1,25,1,0);

               if (funcao)
                   (*funcao)((char *) VD_NULO,(int) VD_NULO,(char *) VD_NULO);

               VIDEO_espera(1);
              }
          break;

   case 6:for (cont = 1;cont < 80;cont++)
              {
               VIDEO_MOUSE_getpos(&col,&lin);

               if (VD_getkey(&ascii,&scan) || VIDEO_MOUSE_intbotpres() ||
                   (linm && colm && ((colm != col) || (linm != lin))))
                  return(TRUE);

               VIDEO_esq_jan(2,80,1,12,1,0);
               VIDEO_dir_jan(1,79,13,25,1,0);

               if (funcao)
                   (*funcao)((char *) VD_NULO,(int) VD_NULO,(char *) VD_NULO);

               VIDEO_espera(1);
              }
          break;


   case 7:for (cont = 1;cont < 80;cont++)
              {
               VIDEO_MOUSE_getpos(&col,&lin);

               if (VD_getkey(&ascii,&scan) || VIDEO_MOUSE_intbotpres() ||
                   (linm && colm && ((colm != col) || (linm != lin))))
                  return(TRUE);

               VIDEO_dir_jan(1,79,1,12,1,0);
               VIDEO_esq_jan(2,80,13,25,1,0);

               if (funcao)
                   (*funcao)((char *) VD_NULO,(int) VD_NULO,(char *) VD_NULO);

               VIDEO_espera(1);
              }
          break;

   case 8:for (cont = 1;cont < 13;cont++)
              {
               VIDEO_MOUSE_getpos(&col,&lin);

               if (VD_getkey(&ascii,&scan) || VIDEO_MOUSE_intbotpres() ||
                   (linm && colm && ((colm != col) || (linm != lin))))
                  return(TRUE);

               VIDEO_sobe_jan(1,80,2,12,1,0);
               VIDEO_desce_jan(1,80,13,24,1,0);

               if (funcao)
                   (*funcao)((char *) VD_NULO,(int) VD_NULO,(char *) VD_NULO);

               VIDEO_espera(1);
              }
          break;

   case 9:for (cont = 1;cont < 13;cont++)
              {
               VIDEO_MOUSE_getpos(&col,&lin);

               if (VD_getkey(&ascii,&scan) || VIDEO_MOUSE_intbotpres() ||
                   (linm && colm && ((colm != col) || (linm != lin))))
                  return(TRUE);

               VIDEO_sobe_jan(1,80,12,25,1,0);
               VIDEO_desce_jan(1,80,1,12,1,0);

               if (funcao)
                   (*funcao)((char *) VD_NULO,(int) VD_NULO,(char *) VD_NULO);

               VIDEO_espera(1);
              }
          break;
  }

 return(FALSE);
}
