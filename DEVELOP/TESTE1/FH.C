/****************************************************************************/
/*                                                                          */
/*  FairCom Help - Error Information Utility                                */
/*                                                                          */
/*  Format: fh <error>                                                      */
/*    Where <error> is the error return code or mnemonic from a c-tree,     */
/*    r-tree or d-tree function.                                            */
/*                                                                          */
/*  This program will search for the given error in the fh database and     */
/*  display the information to the screen.  The fh database must be created */
/*  from fh.txt the first time this program is run.                         */
/*                                                                          */
/****************************************************************************/
#include "ctstdr.h"
#include "ctoptn.h"
#include "ctaerr.h"
#include "cterrc.h"
#include "ctdecl.h" 
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define NODEBUG
#define AUTO_PATH
#define SCREEN_WIDTH   80
#define MAXLINE		 255
#define FIXED_SIZE	  35
#define VAR_SIZE     1000
#define TOTAL_SIZE	FIXED_SIZE + VAR_SIZE
#define WORKSIZE      100

struct errs {
	TEXT	errname[21];
	TEXT	errnum[8];
	TEXT	prodcode[6];
	TEXT	errdesc[VAR_SIZE];
	} ERRS;

ISEG segments[] = {
	{0,20,2},
	{21,7,2}
	};

IIDX ndxs[] = {
	{20, 0,0,1,32,1, segments,"name_key"},		/* ERROR SYMBOLIC NAME 	*/
	{11, 0,1,1,32,1, &segments[1],"code_key"}	/* ERROR CODE */
	};

IFIL errors = {
    "fh",
	-1,
	FIXED_SIZE,
	4096,
	SHARED | CHECKLOCK | VLENGTH,
	2,
	4096,
	SHARED,
	ndxs,
	"errname",
	"errdesc"
	};

#ifdef RESOURCE
DATOBJ doda[] = {
{"errname"     , (TEXT *)0,CT_STRING ,21},/* errname */
{"errnum"      , (TEXT *)0,CT_STRING , 8},/* errnum */
{"prodcode"    , (TEXT *)0,CT_STRING , 6},/* prodcode */
{"errdesc"     , (TEXT *)0,CT_STRING ,VAR_SIZE},/* errdesc */
{"","",0,0,-1}
};
#endif

pFILE fpin;

#ifdef PROTOTYPE
NINT parse_line(pTEXT linebuf);
NINT create_files(VOID);
pTEXT parse_word(pTEXT out_buf, pTEXT in_buf, NINT out_len);
#else
NINT parse_line();
NINT create_files();
pTEXT parse_word();
#endif

#ifdef PROTOTYPE
main (NINT argc,pTEXT argv[])
#else
main (argc,argv)
NINT   argc;
pTEXT  argv[];
#endif
{

	VRLEN	rec_size;
	NINT	result;
	NINT	i,j;
	TEXT	work[WORKSIZE];

	if (argc != 2)
	{
		printf("\nFormat: fh 1234  OR  fh ERR_NAME");
		ctrt_exit(1);
	}

#ifdef AUTO_PATH
	strcpy(work, argv[0]);
	i = strlen(work);
	if ((i > 4) && (work[i-4] == '.'))
		work[i-4] = (TEXT) NULL;
	errors.pfilnam = work;
#endif

	result = INTISAM(6,10,4);
	if(result)
	{
		printf("\nError initializing c-tree");
		printf("\nError = <%d> <%d>",result, isam_err);
		ctrt_exit(1);
	}

   result = OPNIFIL(&errors); /*test for file*/
	if(result)
	{
		printf("\nError on OPNIFIL");
		printf("\nError = <%d> on file <%d> errno %d\n", isam_err, isam_fil, sysiocod);
		if (isam_err == FNOP_ERR)
			if(create_files())
			{
				CLISAM();
				ctrt_exit(1);
			}

		if (isam_err == DOPN_ERR || isam_err == FCRP_ERR ||
		    isam_err == FCMP_ERR || isam_err == DCRAT_ERR)
		{
			printf("\nAttempting rebuild");
			if(RBLIFIL(&errors))
			{
				printf("\nError on RBLIFIL");
				printf("\nErrors = <%d> <%d> on file <%d>",result, isam_err, isam_fil);
				CLISAM();
				ctrt_exit(1);
			}
			else
			{
			    result = OPNIFIL(&errors); /*test for file*/
				if(result)
				{
					printf("\nError on OPNIFIL after RBLIFIL");
					printf("\nErrors = <%d> <%d> on file <%d>",result, isam_err, isam_fil);
					CLISAM();
					ctrt_exit(1);
				}
				else
					printf("\nRebuild succeeded.\n");
			}
		}
	}

	memset(work,0x20,WORKSIZE);
	i = strlen(argv[1]);
	memcpy(work,argv[1],i);

	if (strchr(argv[1],'_'))
	{
		if (!TFRMKEY(errors.tfilno+1, work))
		{
			printf("\nError %d on TFRMKEY", isam_err);
			CLISAM();
			ctrt_exit(1);
		}

		result = EQLREC(errors.tfilno+1, work, &ERRS);
		if(result)
		{
			printf("\nError not found in database");
#ifdef DEBUG
			getchar();
			chkidx(errors.tfilno+1);
#endif
			CLISAM();
			ctrt_exit(1);
		}
	}
	else
	{

		if (!TFRMKEY(errors.tfilno+2, work))
		{
			printf("\nError %d on TFRMKEY", isam_err);
			CLISAM();
			ctrt_exit(1);
		}

		result = GTEREC(errors.tfilno+2, work, &ERRS);
		if((result) || (strcmp(ERRS.errnum, work)))
		{
			printf("\nError not found in database");
#ifdef DEBUG
			getchar();
			chkidx(errors.tfilno+2);
#endif
			CLISAM();
			ctrt_exit(1);
		}
	}

	rec_size = GETVLEN(errors.tfilno);
	if (rec_size > TOTAL_SIZE)
	{
		printf("\nVariable-length record too large for buffer.");
		printf("\nRecord length %ld  Buffer length %d", rec_size, TOTAL_SIZE);
	}
	else
	{
		result = REDVREC(errors.tfilno, &ERRS, TOTAL_SIZE);
		if(result)
			printf("\nCould not read the vlen portion.  Return: %d",result);
	}
	
	j = SCREEN_WIDTH - 20;		/* Allow for "Error description: " */
	while (j < rec_size - FIXED_SIZE)
	{
		while (ERRS.errdesc[j] != ' ')
			j--;
		ERRS.errdesc[j] = '\n';
		j = j + SCREEN_WIDTH - 1;
	}		

	printf("\nError code:     %s",ERRS.errnum);
	printf("\nError mnemonic: %s",ERRS.errname);
	printf("\nProduct code:   %s",ERRS.prodcode);
	printf("\nError description: %s\n",ERRS.errdesc);

	CLISAM();
	return(0);
}

#ifdef PROTOTYPE
NINT create_files(VOID)
#else
create_files()
#endif
{

/* Defining SMALL_IDX will cause the load process to add the data records
   without indices and then call RBLIFIL() to create the index file.  This
   is the recommended method for doing large database loads since it creates
   the smallest possible indices.  This method will also increase the speed
   of large loads.  Due to the small size of this database using this method
   will cause the load to take longer. */
/* #define SMALL_IDX */

#ifdef SMALL_IDX
	pIIDX save_piidx;
	COUNT save_indices;
#endif
	NINT total_added = 0;
	NINT result;
	pTEXT p;
	TEXT linein[MAXLINE];
	TEXT input_file[MAX_NAME]; /* MAX_NAME set in ctopt2.h - default 255 */

	VRLEN vlen;

	strcpy(input_file,"fh.txt");

	if(!(fpin = fopen(input_file,"rt"))) /* assignment intended */
	{
		printf("\nError opening input file %s.",input_file);
		printf("\nerrno = %d",errno);
		printf("\nBe sure file %s is in your local directory.\n",input_file);
		return(1);
	}

#ifdef SMALL_IDX  /* Prepare to do a load without indices. */
	save_piidx = errors.ix;
	errors.ix = (TEXT) NULL;

	save_indices = errors.dnumidx;
	errors.dnumidx = 0;
#endif

	result= OPNIFIL(&errors); /*test for file*/
	if(result == FNOP_ERR)
	{

		result = CREIFIL(&errors);
		if(result)
		{
			printf("\nError creating file.");
			printf("\nErrors = <%d> <%d> on file <%d>\n",result, isam_err, isam_fil);
			return(0);
		}
#ifdef RESOURCE
		result = PUTDODA(errors.tfilno,doda,(UCOUNT) 4);
		if(result)
		{
			printf("\nError storing DODA.");
			printf("\nErrors = <%d> <%d> on file <%d>\n",result, isam_err, isam_fil);
			return(0);
		}
#endif
	}
	else
	{
		if(result)
		{
			printf("\nError opening file");
			printf("\nErrors = <%d> <%d> on file <%d>\n",result, isam_err, isam_fil);
			return(1);
		}
	}

	if(!(p = fgets(linein,MAXLINE,fpin))) /* assignment intended */
	{
		printf("Error reading first line. error = %d\n",errno);
		fclose(fpin);
		return(1);
	}

	printf("\nImporting data from %s to file %s.", input_file, errors.pfilnam);
	printf("\nThis load could take one minute or more depending on your platform. ");
	printf("\nThis only happens the first time you run this program.");

/* Comment lines may be placed at the top and prefaced with // */
	while (!strncmp((char *)&linein[0],"//",2))
		p = fgets(linein,MAXLINE,fpin);		

	do
	{
		if (!parse_line(linein))
		{
			vlen = ((VRLEN) (ERRS.errdesc - ERRS.errname)) + strlen(ERRS.errdesc) + 1;

			result = ADDVREC(errors.tfilno,&ERRS,vlen);
			if(result)
			{
				printf("\nError <%d> adding record %s %s to file <%d>\n",
					isam_err, ERRS.errnum, ERRS.errname, isam_fil);
			}
			else
				total_added += 1;
		}

		memset(linein,0x20,MAXLINE);
		p = fgets(linein,MAXLINE,fpin);

	} while (p);		

	fclose(fpin);		

#ifdef SMALL_IDX  /* Restore IFIL parameters and create indices. */
	errors.ix = save_piidx;
	errors.dnumidx = save_indices;

	printf("\nRunning rebuild to create indices.");

	CLIFIL(&errors);
	if(RBLIFIL(&errors))
	{
		printf("\nError on RBLIFIL");
		printf("\nErrors = <%d> <%d> on file <%d>",result, isam_err, isam_fil);
		return(1);
	}
#endif

	printf("\n%d records successfully added to file %s.\n", 
		total_added, errors.pfilnam);
	return(0);
}			


#ifdef PROTOTYPE
NINT parse_line(pTEXT linebuf)
#else
NINT parse_line(linebuf)
pTEXT linebuf;
#endif
{
	NINT i;
	NINT buflen;
	pTEXT p;

	buflen = (int)strlen(linebuf);
	if (buflen <= 1)
		return(1);

	memset(ERRS.errname,0x20,sizeof(ERRS));

	p = parse_word(ERRS.errnum,linebuf,sizeof(ERRS.errnum));
	if (!p)
		return(1);

	p = parse_word(ERRS.errname,p,sizeof(ERRS.errname));
	if (!p)
		return(1);

	p = parse_word(ERRS.prodcode,p,sizeof(ERRS.prodcode));
	if (!p)
		return(1);

/* get description */
	p = fgets(linebuf,MAXLINE,fpin);

	if(!p)
	{
		printf("\nNo error description found for <%s> <%s>",ERRS.errname, ERRS.errnum);
		return(0);
	}

	i=0;
	while ((strlen(linebuf) > 1) && (i < VAR_SIZE))
	{
		if ((i + strlen(linebuf)) >= VAR_SIZE)
		{
			printf("\nError %s description truncated", ERRS.errname);
			memcpy(&ERRS.errdesc[i],p,VAR_SIZE-i);
			ERRS.errdesc[VAR_SIZE-1] = (TEXT) NULL;
			return(0);
		}
		memcpy(&ERRS.errdesc[i],p,strlen(linebuf));
		i = i + strlen(linebuf);
		ERRS.errdesc[i-1] = ' ';	/* Replace \n with a blank */
		memset(linebuf,0x20,MAXLINE);
		p = fgets(linebuf,MAXLINE,fpin);
		p = linebuf;
		while ((*(p) == ' ') || (*(p) == '\t'))
			p++;
	}
	
	ERRS.errdesc[i-1] = (TEXT) NULL;

	return(0);
}

#ifdef PROTOTYPE
pTEXT parse_word(pTEXT dest_buf, pTEXT source_buf, NINT dest_len)
#else
pTEXT parse_word(dest_buf, source_buf, dest_len)
pTEXT dest_buf;
pTEXT source_buf;
NINT dest_len;
#endif
{
	pTEXT p;
	pTEXT pp;

/* This section finds the first character */
	for (p=source_buf; ((p-source_buf)<strlen(source_buf)) && ((*p == ' ') ||
			(*p == '\t'));p++);
	if (p-source_buf >= strlen(source_buf))
		return(0);

/* This section finds the end of word */
	for (pp=p; ((pp-p)<strlen(source_buf)) && (*pp != ' ') && (*pp != '\t') &&
			(*pp != (TEXT) NULL); pp++);
	if (pp-p >= strlen(source_buf))
		return(0);

/* This section moves the word to the destination buffer and null terminates */
	memcpy(dest_buf, p, (UCOUNT) (pp-p));
	*(dest_buf+dest_len-1) = (TEXT) NULL;
	return(pp);
}

/* end of fh.c */
