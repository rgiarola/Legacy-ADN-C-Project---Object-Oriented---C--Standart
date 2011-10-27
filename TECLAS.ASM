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
	?debug	S "teclas.c"
	?debug	C E90363A31C087465636C61732E63
	?debug	C E974B55B1D1B433A5C41444E325C56444D4143524F535C494E4356+
	?debug	C 4944454F2E48
	?debug	C E9EA93881B1B433A5C41444E325C56444D4143524F535C434F4E46+
	?debug	C 49472E41444E
	?debug	C E9165F9D1D1B433A5C41444E325C56444D4143524F535C45585443+
	?debug	C 545245452E48
	?debug	C E9C65B951514433A5C43545245455C54435C6374737464722E68
	?debug	C E9C65B951514433A5C43545245455C54435C6374636D706C2E68
	?debug	C E90010971613433A5C42435C494E434C5544455C646F732E68
	?debug	C E90010971615433A5C42435C494E434C5544455C616C6C6F632E68
	?debug	C E90010971615433A5C42435C494E434C5544455C737464696F2E68
	?debug	C E90010971615433A5C42435C494E434C5544455C66636E746C2E68
	?debug	C E9C55B951511433A5C43545245455C6374706F72742E68
	?debug	C E9C45B951511433A5C43545245455C63746C66756E2E68
	?debug	C E90010971616433A5C42435C494E434C5544455C7374646465662E+
	?debug	C 68
	?debug	C E98D90591D14433A5C43545245455C54435C63746F70746E2E68
	?debug	C E95864591D11433A5C43545245455C63746F7074322E68
	?debug	C E9C35B951511433A5C43545245455C6374616572722E68
	?debug	C E9C55B951511433A5C43545245455C63746465636C2E68
	?debug	C E9A864371B11433A5C43545245455C63746966696C2E68
	?debug	C E9C55B951511433A5C43545245455C6374657272632E68
	?debug	C E9CF45221611433A5C52545245455C7274646F64612E68
	?debug	C E9C75B951511433A5C52545245455C7274726C69622E68
	?debug	C E9C65B951511433A5C52545245455C72746465636C2E68
	?debug	C E90E84DC1C1A433A5C41444E325C56444D4143524F535C63747265+
	?debug	C 652E76646F
	?debug	C E93B7B2D1E1B433A5C41444E325C56444D4143524F535C65787470+
	?debug	C 726F746F2E68
	?debug	C E90010971615433A5C42435C494E434C5544455C63747970652E68
	?debug	C E90010971613433A5C42435C494E434C5544455C4449522E48
	?debug	C E90010971615433A5C42435C494E434C5544455C4552524E4F2E48
	?debug	C E90010971612433A5C42435C494E434C5544455C494F2E48
	?debug	C E90010971617433A5C42435C494E434C5544455C50524F43455353+
	?debug	C 2E48
	?debug	C E90010971616433A5C42435C494E434C5544455C6C696D6974732E+
	?debug	C 68
	?debug	C E90010971614433A5C42435C494E434C5544455C6D6174682E68
	?debug	C E90010971613433A5C42435C494E434C5544455C4D454D2E48
	?debug	C E90010971616433A5C42435C494E434C5544455C737472696E672E+
	?debug	C 68
	?debug	C E90010971616433A5C42435C494E434C5544455C56414C5545532E+
	?debug	C 48
	?debug	C E90010971618433A5C42435C494E434C5544455C5359535C535441+
	?debug	C 542E48
	?debug	C E90010971616433A5C42435C494E434C5544455C5354444C49422E+
	?debug	C 48
	?debug	C E90010971614433A5C42435C494E434C5544455C54494D452E48
	?debug	C E982A4281D1C433A5C41444E325C56444D4143524F535C56445649+
	?debug	C 44454F2E56444F
	?debug	C E933818A1B1B433A5C41444E325C56444D4143524F535C4E55434C+
	?debug	C 454F2E56444F
	?debug	C E933818A1B1B433A5C41444E325C56444D4143524F535C47455241+
	?debug	C 49532E56444F
	?debug	C E9A486131D19433A5C41444E325C56444D4143524F535C4D454E55+
	?debug	C 2E56444F
	?debug	C E9A282591D19433A5C41444E325C56444D4143524F535C54454C41+
	?debug	C 2E56444F
	?debug	C E9955E961B1B433A5C41444E325C56444D4143524F535C4152564F+
	?debug	C 52452E56444F
	?debug	C E92D818A1B1A433A5C41444E325C56444D4143524F535C43415247+
	?debug	C 412E56444F
	?debug	C E9C6790F1D19433A5C41444E325C56444D4143524F535C48454C50+
	?debug	C 2E56444F
	?debug	C E9A09C811D1C433A5C41444E325C56444D4143524F535C44454643+
	?debug	C 4153542E56444F
	?debug	C E92E818A1B1D433A5C41444E325C56444D4143524F535C44454642+
	?debug	C 495445532E56444F
	?debug	C E90687131D1D433A5C41444E325C56444D4143524F535C44454654+
	?debug	C 45434C412E56444F
	?debug	C E92F818A1B1D433A5C41444E325C56444D4143524F535C44454646+
	?debug	C 4C4147532E56444F
	?debug	C E9B57C1A1D1D433A5C41444E325C56444D4143524F535C44454641+
	?debug	C 525156532E56444F
	?debug	C E93664761D1D433A5C41444E325C56444D4143524F535C44454657+
	?debug	C 494E444F2E56444F
	?debug	C E930818A1B1D433A5C41444E325C56444D4143524F535C4445464E+
	?debug	C 4F4D45532E56444F
	?debug	C E9F986261E1D433A5C41444E325C56444D4143524F535C44454650+
	?debug	C 524F54542E56444F
	?debug	C E93879261E1D433A5C41444E325C56444D4143524F535C44454645+
	?debug	C 585445522E56444F
	?debug	C E954BC101D1C433A5C41444E325C56444D4143524F535C4445464D+
	?debug	C 454E532E56444F
	?debug	C E96B692D1E1A433A5C41444E325C56444D4143524F535C414C4C4F+
	?debug	C 432E56444F
	?debug	C E976802D1E18433A5C41444E325C56444D4143524F535C4552524F+
	?debug	C 532E48
	?debug	C E90E84DC1C1A433A5C41444E325C56444D4143524F535C43545245+
	?debug	C 452E56444F
TECLAS_TEXT	segment byte public 'CODE'
TECLAS_TEXT	ends
DGROUP	group	_DATA,_BSS
	assume	cs:TECLAS_TEXT,ds:DGROUP
_DATA	segment word public 'DATA'
d@	label	byte
d@w	label	word
_DATA	ends
_BSS	segment word public 'BSS'
b@	label	byte
b@w	label	word
_BSS	ends
TECLAS_TEXT	segment byte public 'CODE'
   ;	
   ;	main()
   ;	
	assume	cs:TECLAS_TEXT
_main	proc	far
	push	bp
	mov	bp,sp
	sub	sp,224
   ;	
   ;	{
   ;	 BYTE     ascii,scan,
   ;	          teclas,
   ;	          far *teclado,
   ;	          far *tec2;
   ;	 char     buffer[200];
   ;	 BYTE *buffer_teclado = MK_FP(0X0040,0X001E);
   ;	
	mov	word ptr [bp-14],64
	mov	word ptr [bp-16],30
   ;	
   ;	 WORD *inicio_teclado = MK_FP(0X0040,0X001A),
   ;	
	mov	word ptr [bp-18],64
	mov	word ptr [bp-20],26
   ;	
   ;	      *fim_teclado    = MK_FP(0X0040,0X001C);
   ;	
	mov	word ptr [bp-22],64
	mov	word ptr [bp-24],28
   ;	
   ;	
   ;	 teclado = MK_FP(0X0040,0X0017);
   ;	
	mov	word ptr [bp-6],64
	mov	word ptr [bp-8],23
   ;	
   ;	 tec2    = MK_FP(0X0040,0X0018);
   ;	
	mov	word ptr [bp-10],64
	mov	word ptr [bp-12],24
   ;	
   ;	
   ;	 clrscr();
   ;	
	call	far ptr _clrscr
   ;	
   ;	 ascii = scan = 0;
   ;	
	mov	al,0
	mov	byte ptr [bp-2],al
	mov	byte ptr [bp-1],al
@1@50:
   ;	
   ;	 do
   ;	  {
   ;	// if(kbhit())
   ;	//   VD_getkbd(&ascii,&scan);
   ;	     VD_getkey(&ascii,&scan);
   ;	
	push	ss
	lea	ax,word ptr [bp-2]
	push	ax
	push	ss
	lea	ax,word ptr [bp-1]
	push	ax
	call	far ptr _VIDEO_getkey
	add	sp,8
   ;	
   ;	
   ;	   teclas = *teclado;
   ;	
	les	bx,dword ptr [bp-8]
	mov	al,byte ptr es:[bx]
	mov	byte ptr [bp-3],al
   ;	
   ;	   sprintf(buffer,"IN %d CL %d NL %d SL %d AL %d CT %d SE %d SD %d ASCII %d SCAN %d CAR %c   ",
   ;	
   ;	
   ;	   ((teclas & VD_B7) ? 1 : 0),
   ;	   ((teclas & VD_B6) ? 1 : 0),
   ;	   ((teclas & VD_B5) ? 1 : 0),
   ;	   ((teclas & VD_B4) ? 1 : 0),
   ;	   ((teclas & VD_B3) ? 1 : 0),
   ;	   ((teclas & VD_B2) ? 1 : 0),
   ;	   ((teclas & VD_B1) ? 1 : 0),
   ;	   ((teclas & VD_B0) ? 1 : 0),
   ;	   ascii,scan,ascii);
   ;	
	mov	al,byte ptr [bp-1]
	mov	ah,0
	push	ax
	mov	al,byte ptr [bp-2]
	mov	ah,0
	push	ax
	mov	al,byte ptr [bp-1]
	mov	ah,0
	push	ax
	test	byte ptr [bp-3],1
	je	short @1@98
	mov	ax,1
	jmp	short @1@122
@1@98:
	xor	ax,ax
@1@122:
	push	ax
	test	byte ptr [bp-3],2
	je	short @1@170
	mov	ax,1
	jmp	short @1@194
@1@170:
	xor	ax,ax
@1@194:
	push	ax
	test	byte ptr [bp-3],4
	je	short @1@242
	mov	ax,1
	jmp	short @1@266
@1@242:
	xor	ax,ax
@1@266:
	push	ax
	test	byte ptr [bp-3],8
	je	short @1@314
	mov	ax,1
	jmp	short @1@338
@1@314:
	xor	ax,ax
@1@338:
	push	ax
	test	byte ptr [bp-3],16
	je	short @1@386
	mov	ax,1
	jmp	short @1@410
@1@386:
	xor	ax,ax
@1@410:
	push	ax
	test	byte ptr [bp-3],32
	je	short @1@458
	mov	ax,1
	jmp	short @1@482
@1@458:
	xor	ax,ax
@1@482:
	push	ax
	test	byte ptr [bp-3],64
	je	short @1@530
	mov	ax,1
	jmp	short @1@554
@1@530:
	xor	ax,ax
@1@554:
	push	ax
	test	byte ptr [bp-3],128
	je	short @1@602
	mov	ax,1
	jmp	short @1@626
@1@602:
	xor	ax,ax
@1@626:
	push	ax
	push	ds
	mov	ax,offset DGROUP:s@
	push	ax
	push	ss
	lea	ax,word ptr [bp-224]
	push	ax
	call	far ptr _sprintf
	add	sp,30
   ;	
   ;	   VD_tprt_l(2,3,buffer,7);
   ;	
	xor	ax,ax
	push	ax
	mov	al,7
	push	ax
	push	ss
	lea	ax,word ptr [bp-224]
	push	ax
	mov	ax,3
	push	ax
	mov	ax,2
	push	ax
	call	far ptr _VIDEO_tprt
	add	sp,12
   ;	
   ;	   VD_gtxy(1,10);
   ;	
	mov	ax,10
	push	ax
	mov	ax,1
	push	ax
	call	far ptr _VIDEO_gtxy
	pop	cx
	pop	cx
   ;	
   ;	   printf("%04X %04X",*inicio_teclado,*fim_teclado);
   ;	
	les	bx,dword ptr [bp-24]
	push	word ptr es:[bx]
	les	bx,dword ptr [bp-20]
	push	word ptr es:[bx]
	push	ds
	mov	ax,offset DGROUP:s@+75
	push	ax
	call	far ptr _printf
	add	sp,8
   ;	
   ;	
   ;	   teclas = *tec2;
   ;	
	les	bx,dword ptr [bp-12]
	mov	al,byte ptr es:[bx]
	mov	byte ptr [bp-3],al
   ;	
   ;	   sprintf(buffer,"IN %d CL %d NL %d SL %d PA %d SY %d AE %d CE %d ",
   ;	
   ;	
   ;	   ((teclas & VD_B7) ? 1 : 0),
   ;	   ((teclas & VD_B6) ? 1 : 0),
   ;	   ((teclas & VD_B5) ? 1 : 0),
   ;	   ((teclas & VD_B4) ? 1 : 0),
   ;	   ((teclas & VD_B3) ? 1 : 0),
   ;	   ((teclas & VD_B2) ? 1 : 0),
   ;	   ((teclas & VD_B1) ? 1 : 0),
   ;	   ((teclas & VD_B0) ? 1 : 0));
   ;	
	test	byte ptr [bp-3],1
	je	short @1@674
	mov	ax,1
	jmp	short @1@698
@1@674:
	xor	ax,ax
@1@698:
	push	ax
	test	byte ptr [bp-3],2
	je	short @1@746
	mov	ax,1
	jmp	short @1@770
@1@746:
	xor	ax,ax
@1@770:
	push	ax
	test	byte ptr [bp-3],4
	je	short @1@818
	mov	ax,1
	jmp	short @1@842
@1@818:
	xor	ax,ax
@1@842:
	push	ax
	test	byte ptr [bp-3],8
	je	short @1@890
	mov	ax,1
	jmp	short @1@914
@1@890:
	xor	ax,ax
@1@914:
	push	ax
	test	byte ptr [bp-3],16
	je	short @1@962
	mov	ax,1
	jmp	short @1@986
@1@962:
	xor	ax,ax
@1@986:
	push	ax
	test	byte ptr [bp-3],32
	je	short @1@1034
	mov	ax,1
	jmp	short @1@1058
@1@1034:
	xor	ax,ax
@1@1058:
	push	ax
	test	byte ptr [bp-3],64
	je	short @1@1106
	mov	ax,1
	jmp	short @1@1130
@1@1106:
	xor	ax,ax
@1@1130:
	push	ax
	test	byte ptr [bp-3],128
	je	short @1@1178
	mov	ax,1
	jmp	short @1@1202
@1@1178:
	xor	ax,ax
@1@1202:
	push	ax
	push	ds
	mov	ax,offset DGROUP:s@+85
	push	ax
	push	ss
	lea	ax,word ptr [bp-224]
	push	ax
	call	far ptr _sprintf
	add	sp,24
   ;	
   ;	   VD_tprt_l(2,4,buffer,7);
   ;	
	xor	ax,ax
	push	ax
	mov	al,7
	push	ax
	push	ss
	lea	ax,word ptr [bp-224]
	push	ax
	mov	ax,4
	push	ax
	mov	ax,2
	push	ax
	call	far ptr _VIDEO_tprt
	add	sp,12
   ;	
   ;	  }while(ascii != 27);
   ;	
	cmp	byte ptr [bp-1],27
	je	@@0
	jmp	@1@50
@@0:
   ;	
   ;	}
   ;	
	mov	sp,bp
	pop	bp
	ret	
_main	endp
	?debug	C E9
TECLAS_TEXT	ends
_DATA	segment word public 'DATA'
s@	label	byte
	db	'IN %d CL %d NL %d SL %d AL %d CT %d SE %d SD %d ASCII %d SCAN'
	db	' %d CAR %c   '
	db	0
	db	'%04X %04X'
	db	0
	db	'IN %d CL %d NL %d SL %d PA %d SY %d AE %d CE %d '
	db	0
_DATA	ends
TECLAS_TEXT	segment byte public 'CODE'
TECLAS_TEXT	ends
	extrn	_VIDEO_gtxy:far
	extrn	_printf:far
	extrn	_VIDEO_getkey:far
	extrn	_VIDEO_tprt:far
	extrn	_sprintf:far
	public	_main
	extrn	_clrscr:far
	end
