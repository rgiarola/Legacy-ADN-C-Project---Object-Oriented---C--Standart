	ifndef	??version
?debug	macro
	endm
publicdll macro	name
	public	name
	endm
$comm	macro	name,dist,size,count
	comm	dist name:BYTE:count*size
	endm
	else
$comm	macro	name,dist,size,count
	comm	dist name[size]:BYTE:count
	endm
	endif
	?debug	S "teste.c"
	?debug	C E96087311E0774657374652E63
	?debug	C E90010971613433A5C42435C494E434C5544455C646F732E68
	?debug	C E90010971614433A5C42435C494E434C5544455C62696F732E68
TESTE_TEXT	segment byte public 'CODE'
TESTE_TEXT	ends
DGROUP	group	_DATA,_BSS
	assume	cs:TESTE_TEXT,ds:DGROUP
_DATA	segment word public 'DATA'
d@	label	byte
d@w	label	word
_DATA	ends
_BSS	segment word public 'BSS'
b@	label	byte
b@w	label	word
_BSS	ends
TESTE_TEXT	segment byte public 'CODE'
   ;	
   ;	main()
   ;	
	assume	cs:TESTE_TEXT
_main	proc	far
	push	bp
	mov	bp,sp
	sub	sp,20
   ;	
   ;	{
   ;	 long valor  = 1000000L,
   ;	
	mov	word ptr [bp-2],15
	mov	word ptr [bp-4],16960
   ;	
   ;		valor2 = 3.,
   ;	
	mov	word ptr [bp-6],0
	mov	word ptr [bp-8],3
   ;	
   ;		valor3,
   ;		*valor4 = &valor3;
   ;	
	lea	ax,word ptr [bp-12]
	mov	word ptr [bp-14],ss
	mov	word ptr [bp-16],ax
   ;	
   ;	 char   *ptr;
   ;	
   ;	 clrscr();
   ;	
	call	far ptr _clrscr
   ;	
   ;	
   ;	 ptr =  MK_FP(FP_SEG(&valor),_SP);
   ;	
	mov	word ptr [bp-18],ss
	mov	word ptr [bp-20],sp
   ;	
   ;	 printf("V %p\n",ptr);
   ;	
	push	word ptr [bp-18]
	push	word ptr [bp-20]
	push	ds
	mov	ax,offset DGROUP:s@
	push	ax
	call	far ptr _printf
	add	sp,8
   ;	
   ;	 _SP -= (sizeof(long)*2+sizeof(long *));
   ;	
	sub	sp,12
   ;	
   ;	 memcpy(ptr+sizeof(long)*2,&valor,sizeof(long));
   ;	
	mov	ax,4
	push	ax
	push	ss
	lea	ax,word ptr [bp-4]
	push	ax
	mov	ax,word ptr [bp-20]
	add	ax,8
	push	word ptr [bp-18]
	push	ax
	call	far ptr _memcpy
	add	sp,10
   ;	
   ;	 memcpy(ptr+sizeof(long),&valor2,sizeof(long));
   ;	
	mov	ax,4
	push	ax
	push	ss
	lea	ax,word ptr [bp-8]
	push	ax
	mov	ax,word ptr [bp-20]
	add	ax,4
	push	word ptr [bp-18]
	push	ax
	call	far ptr _memcpy
	add	sp,10
   ;	
   ;	 memcpy(ptr,&valor4,sizeof(long *));
   ;	
	mov	ax,4
	push	ax
	push	ss
	lea	ax,word ptr [bp-16]
	push	ax
	push	word ptr [bp-18]
	push	word ptr [bp-20]
	call	far ptr _memcpy
	add	sp,10
   ;	
   ;	 display();
   ;	
	call	far ptr _display
   ;	
   ;	 _SP += (sizeof(long)*2+sizeof(long *));
   ;	
	add	sp,12
   ;	
   ;	 printf("\n%10ld\n",*valor4);
   ;	
	les	bx,dword ptr [bp-16]
	push	word ptr es:[bx+2]
	push	word ptr es:[bx]
	push	ds
	mov	ax,offset DGROUP:s@+6
	push	ax
	call	far ptr _printf
	add	sp,8
   ;	
   ;	 display(valor,valor2,valor4);
   ;	
	push	word ptr [bp-14]
	push	word ptr [bp-16]
	push	word ptr [bp-6]
	push	word ptr [bp-8]
	push	word ptr [bp-2]
	push	word ptr [bp-4]
	call	far ptr _display
	add	sp,12
   ;	
   ;	 printf("\n%10ld\n",*valor4);
   ;	
	les	bx,dword ptr [bp-16]
	push	word ptr es:[bx+2]
	push	word ptr es:[bx]
	push	ds
	mov	ax,offset DGROUP:s@+14
	push	ax
	call	far ptr _printf
	add	sp,8
   ;	
   ;	}
   ;	
	mov	sp,bp
	pop	bp
	ret	
_main	endp
   ;	
   ;	display(valor1,valor2,valor3)
   ;	
	assume	cs:TESTE_TEXT
_display	proc	far
	push	bp
	mov	bp,sp
   ;	
   ;	long valor1,valor2,*valor3;
   ;	{
   ;	 printf("V %p\n",&valor1);
   ;	
	push	ss
	lea	ax,word ptr [bp+6]
	push	ax
	push	ds
	mov	ax,offset DGROUP:s@+22
	push	ax
	call	far ptr _printf
	add	sp,8
   ;	
   ;	 printf("VALOR1 %10ld VALOR2 %10ld Total %10ld\n",
   ;	
   ;	
   ;	    valor1,valor2,valor1*valor2);
   ;	
	mov	cx,word ptr [bp+8]
	mov	bx,word ptr [bp+6]
	mov	dx,word ptr [bp+12]
	mov	ax,word ptr [bp+10]
	call	far ptr F_LXMUL@
	push	dx
	push	ax
	push	word ptr [bp+12]
	push	word ptr [bp+10]
	push	word ptr [bp+8]
	push	word ptr [bp+6]
	push	ds
	mov	ax,offset DGROUP:s@+28
	push	ax
	call	far ptr _printf
	add	sp,16
   ;	
   ;	 *valor3 = valor1*valor2;
   ;	
	mov	cx,word ptr [bp+8]
	mov	bx,word ptr [bp+6]
	mov	dx,word ptr [bp+12]
	mov	ax,word ptr [bp+10]
	call	far ptr F_LXMUL@
	les	bx,dword ptr [bp+14]
	mov	word ptr es:[bx+2],dx
	mov	word ptr es:[bx],ax
   ;	
   ;	 getch();
   ;	
	call	far ptr _getch
   ;	
   ;	}
   ;	
	pop	bp
	ret	
_display	endp
	?debug	C E9
TESTE_TEXT	ends
_DATA	segment word public 'DATA'
s@	label	byte
	db	'V %p'
	db	10
	db	0
	db	10
	db	'%10ld'
	db	10
	db	0
	db	10
	db	'%10ld'
	db	10
	db	0
	db	'V %p'
	db	10
	db	0
	db	'VALOR1 %10ld VALOR2 %10ld Total %10ld'
	db	10
	db	0
_DATA	ends
TESTE_TEXT	segment byte public 'CODE'
TESTE_TEXT	ends
	extrn	_printf:far
	extrn	_memcpy:far
	public	_display
	extrn	_getch:far
	public	_main
	extrn	_clrscr:far
	extrn	F_LXMUL@:far
	end
