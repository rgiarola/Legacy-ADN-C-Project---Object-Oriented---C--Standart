#include <INCVIDEO.H>

#define BAD_DATE	0L
#define base		621049L
#define DPYR		36525L
#define DPMN		306L
#define YRADJ		100L
#define MNADJ		10L

COUNT dpm[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

COUNT leapyr(year,month,day)
COUNT	     year,month,day;
{
    if (day != 29 || month != 2)
		return(NO);
	if ((year % 4) == 0) {
		if ((year % 400) == 0)
			return(YES);
		else if ((year % 100) != 0)
			return(YES);
		else
			return(NO);
	} else
		return(NO);
}

DATET datein(year,month,day)
COUNT	     year,month,day;
{
    if (month < 1 || month > 12)
		return(BAD_DATE);
	if (day > dpm[month] && !leapyr(year,month,day))
		return(BAD_DATE);
	if (month < 3) {
		year--;
		month += 13;
	} else
		month++;
	return(((DPYR * year) / YRADJ) + 
		((DPMN * month) / MNADJ) +
		day - base);
}

/*
  dateout converts a long (computed by datein) into year, month, day &
  day of week (sunday == 0) components
*/

COUNT dateout(datein,pyear, pmonth, pday, pdwk)
DATET	      datein;
pCOUNT		    pyear,pmonth,pday,pdwk;
{
	DATET tdate;

	*pdwk   = datein % 7;
    tdate   = datein + base;
	*pyear  = (tdate * YRADJ) / DPYR;
	tdate  -= ((DPYR * *pyear) / YRADJ);
	*pmonth = (tdate * MNADJ) / DPMN;

	if (*pmonth < 4) {
		tdate    = datein + base - ((DPYR * (*pyear - 1)) / YRADJ);
		*pmonth  = (tdate * MNADJ) / DPMN;
		*pday    = tdate - ((DPMN * *pmonth) / MNADJ);
		*pmonth -= 13;
	} else {
		*pday = tdate - ((DPMN * *pmonth) / MNADJ);
		(*pmonth)--;
	}
	if (*pmonth < 1) {
		*pmonth += 12;
		(*pyear)--;
	}
	if (*pday == 0) {
		(*pmonth)--;
		*pday = dpm[*pmonth];
	}
	return(NO_ERROR);
}

