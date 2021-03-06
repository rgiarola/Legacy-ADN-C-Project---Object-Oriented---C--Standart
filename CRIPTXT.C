#include <INCVIDEO.H>
#define  TAMBUFFER   I(30000)
#define  INICIO      I(0)
int conttexto = 0;

main (argc, argv)
int       argc;
char      *argv[];
{
char    fonte[80],
        destino[80],
        senha[100],buffer[20];

int     descfonte,
        descdestino,
        cont;
        
void    cripto(int ,int ,char *);

if (argc < 2)
   {
    printf ("FONTE : ");
    gets(fonte);
   }
 else strcpy(fonte,argv[1]);

if (argc < 3)
   {
    printf ("DESTINO : ");
    gets(destino);
   }
 else strcpy(destino,argv[2]);

 if (strcmp(fonte,destino) == 0)
    {
     printf ("FONTE TEM QUE SER DIFERENTE DO DESTINO");
     exit(0);
    }

 if ((descfonte = VIDEO_open_ler(fonte)) <= 0)
    {
     printf ("problema na abertura do fonte ==> %s",fonte);
     exit(0);
    }  
    
 if ((descdestino = VIDEO_cria(destino)) <= 0)
    {
     printf ("problema na abertura do destino ==> %s",destino);
     exit(0);
    }      

cont = 0;
randomize();
do
 {
  if ((senha[cont] = random(256)) > 0)
     ++cont;
 }while(cont < 40);

senha[40] = 0;

conttexto = 0;
saisenha(descdestino,senha,40);
strcpy(buffer,"};\xd\xa\xd\xa");
write(descdestino,buffer,strlen(buffer));
conttexto = 0;

cripto(descfonte,descdestino,senha);

close(descfonte);
close(descdestino);
}


void cripto(descf,descd,senha)
int   descf,
      descd;
char  *senha;

{
long int     lseek(),
             tamarq,
             posleit,
             filelength();
int          tamleit,
             contabyte,   
             contabit,
             *bits, *monta(char *),
             desvio;
char         buffer[30000];
static char  invbits[] = {BIT0,BIT1,BIT2,BIT3,BIT4,BIT5,BIT6,BIT7};

tamarq  = filelength(descf);

printf ("TAMANHO DO FONTE  %ld \n",tamarq);

posleit = 0L;

desvio = strlen(senha);
desvio *= 2;
bits = monta(senha);      
--desvio;
do
  {
   lseek(descf,posleit,INICIO);
//   lseek(descd,posleit+40,INICIO);
   tamleit = tamarq > TAMBUFFER ? TAMBUFFER : I(tamarq);
   tamarq  = tamarq > TAMBUFFER ? tamarq - L(TAMBUFFER) : 0L;
   posleit += tamleit;
   read(descf,&buffer[0],tamleit);

   for (contabyte = 0,contabit = 0;contabyte < tamleit;contabyte++)
       {
         if (((buffer[contabyte] & invbits[bits[contabit]]) ? 1 : 0))
            {
             buffer[contabyte] = ~buffer[contabyte];
             buffer[contabyte] = buffer[contabyte]  |  invbits[bits[contabit]];
             buffer[contabyte] = ~buffer[contabyte];
            } 
          else
             buffer[contabyte] = buffer[contabyte]  |  invbits[bits[contabit]];
         contabit = contabit == desvio ? 0 : ++contabit;
       }            
    saitexto(descd,&buffer[0],tamleit);
  }while(tamarq > 0L);

 strcpy(buffer,"};\xd\xa\xd\xa");
 write(descd,buffer,strlen(buffer));
 sprintf(buffer,"int CRIPTO_tamanho = %u;\xd\xa\xd\xa",conttexto);
 write(descd,buffer,strlen(buffer));
}

int   *monta(senha)
char  *senha;
{
int      tamsenha,
         aux1, *aux2, aux4, aux5;
char     *aux3;

aux4 = tamsenha = strlen(senha);
tamsenha *= 2;
aux2     = (int *) malloc(sizeof(int) * tamsenha);
aux3     = (char *) malloc(tamsenha);
memcpy (aux3,senha,aux4);
memcpy (aux3+aux4,senha,aux4);

for (aux1 = 0;aux1 < tamsenha;aux1++)
    {
     *(aux2 + aux1) = (unsigned char)*(aux3+aux1);
     *(aux2 + aux1) = (*(aux2+aux1)%I(8));
    } 
--tamsenha;

for (aux5 = 0;aux5 < 2;aux5++)
    {
     for (aux1 = aux4;aux1 < tamsenha;aux1++)
         {
          if (*(aux2+aux1) == *(aux2+aux1+1))
              *(aux2+aux1) = (((*(aux2+aux1+1)+*(aux2+aux1))+aux1*2)%I(8));
          else
              *(aux2+aux1+1) = (*(aux2+aux1+1) + 2*aux1) > 7 ? ((*(aux2+aux1+1)+aux1*3)%I(8)):*(aux2+aux1+1) + 2*aux1;
         }
    }
 return(aux2);
}

saitexto(desc,texto,tam)
int  desc;
BYTE *texto;
int  tam;
{
 char buffer[100];

 do
  {
   if (!conttexto)
      {
       strcpy(buffer,"char CRIPTO_texto[] = {");
       write(desc,buffer,strlen(buffer));
      }
   if (!(conttexto%15))
      {
       strcpy(buffer,"\xD\xA");
       write(desc,buffer,strlen(buffer));
      }
   sprintf(buffer,"0X%02X,",*texto++);
   write(desc,buffer,strlen(buffer));
   ++conttexto;
  }while(--tam);
}

saisenha(desc,texto,tam)
int  desc;
BYTE *texto;
int  tam;
{
 char buffer[100];

 do
  {
   if (!conttexto)
      {
       strcpy(buffer,"char CRIPTO_senha[] = {");
       write(desc,buffer,strlen(buffer));
      }
   if (!(conttexto%15))
      {
       strcpy(buffer,"\xD\xA");
       write(desc,buffer,strlen(buffer));
      }
   sprintf(buffer,"0X%02X,",*texto++);
   write(desc,buffer,strlen(buffer));
   ++conttexto;
  }while(--tam);

 if (!(conttexto%15))
    {
     strcpy(buffer,"\xD\xA");
     write(desc,buffer,strlen(buffer));
    }
 strcpy(buffer,"0X00");
 write(desc,buffer,strlen(buffer));
}


