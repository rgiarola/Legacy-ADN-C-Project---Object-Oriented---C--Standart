#include <dos.h>
#include <bios.h>

main()
{
 double valor  = 134.44363,
	valor2 = 3454782371.645,
	valor3,
	*valor4 = &valor3;
 char   *ptr;

 clrscr();
 _SP -= (sizeof(double)*2+sizeof(double *));
 ptr =  MK_FP(_SS,_SP);
 printf("V %p\n",ptr);

 memcpy(ptr,&valor,sizeof(double));
 memcpy(ptr+sizeof(double),&valor2,sizeof(double));
 memcpy(ptr+sizeof(double)*2,&valor4,sizeof(double *));
 display();
 _SP += (sizeof(double)*2+sizeof(double *));
 printf("\n%10.5f\n",*valor4);
 display(valor,valor2,valor4);
 printf("\n%10.5f\n",*valor4);
}

display(valor1,valor2,valor3)
double valor1,valor2,*valor3;
{
 printf("V %p\n",&valor1);
 printf("VALOR1 %10.5f VALOR2 %10.5f Total %10.5f\n",
    valor1,valor2,valor1*valor2);
 *valor3 = valor1*valor2;
 getch();
}
