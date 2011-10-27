#include <INCVIDEO.H>


INT2 VIDEO_display_mem_disp(ascii,scan,flag)
BYTE *ascii,
     *scan;
INT2 flag;
{
 DWORD memdisp;
 char  buffer[200];

 if (VD_MTTECLA(*ascii,*scan) == VD_MTTECLA(VD_NULO,104) && !flag &&
     !VIDEO_save_screen_ja_ativo)
    {
     memdisp = farcoreleft();

     sprintf(buffer,VIDEO_memoria_disponivel,memdisp);

     if (VIDEO_MOUSE_cursor_ativo && VIDEO_MOUSE_ativo)
         VIDEO_MOUSE_deshabcursor();

     VIDEO_save_screen_ja_ativo   =TRUE;
     VIDEO_mostra_mens_erro ( buffer, TRUE);
     VIDEO_save_screen_ja_ativo   =FALSE;
     /*
     VD_telaproc(10,10,buffer,
                       VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_BLANK,VD_BRIL));
     if (getch())
        getch();
      */

     if (!VIDEO_MOUSE_cursor_ativo && VIDEO_MOUSE_ativo)
         VIDEO_MOUSE_habcursor();


     if (VIDEO_MOUSE_cursor_ativo && VIDEO_MOUSE_ativo)
         VIDEO_MOUSE_deshabcursor();

     // VD_POPWIN();

     if (!VIDEO_MOUSE_cursor_ativo && VIDEO_MOUSE_ativo)
         VIDEO_MOUSE_habcursor();

     *ascii = VD_NULO;  // Necess rio Interceptar o Comando
     *scan  = VD_NULO;
     VIDEO_tcursor(6,7);
    }

 return(TRUE);
}


/*
INT2 VIDEO_MEM_MOSTRA = FALSE;

VD_VOID *VD_farmalloc(tamanho)
DWORD tamanho;
{
 char buffer[200],*mem;

 mem = farmalloc(tamanho);
 if (VIDEO_MEM_MOSTRA)
    {
     sprintf(buffer,"alloc PTR %p TAM %10lu\n",mem,tamanho);
     saibuf(buffer);
    }
 return(mem);
}

VD_VOID VD_farfree(ptr)
VD_VOID *ptr;
{
 char buffer[200];
 if (VIDEO_MEM_MOSTRA)
    {
     sprintf(buffer,"free  PTR %p \n",ptr);
     saibuf(buffer);
    }
 farfree(ptr);
}

*/
