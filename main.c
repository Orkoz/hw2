#ifndef STDIO_H_
#include <stdio.h>
#endif

#ifndef STDLIB_H_
#include <stdlib.h>
#endif

#ifndef STRING_H_
#include <string.h>
#endif

#ifndef EX2_H_
#include "ex2.h"
#endif

#ifndef AIRPORT_H_
#include "airport.h"
#endif

#ifndef RUNWAY_H_
#include "runway.h"
#endif

#ifndef FLIGHT_H_
#include "flight.h"
#endif

#define MAX_LINE_SIZE 256

int main()
{
	char szLine[MAX_LINE_SIZE];
	char* delimiters = " \t\n";
	char* command, par1, par2, par3, par4;

	while (fgets(szLine, MAX_LINE_SIZE, stdin))
	{
		command = strtok(szLine, delimiters);
		par1 = strtok(NULL, delimiters);
		par2 = strtok(NULL, delimiters);
		par3 = strtok(NULL, delimiters);
		par4 = strtok(NULL, delimiters);

		switch (command)
		{
		case "Insert":
			//par1 = strtok(NULL, delimiters);
			//par2 = strtok(NULL, delimiters);
			if (par1 == NULL || par2 == NULL)
			{
				fprintf(stderr, "Insert failed: not enough parameters./n");
			}

			break;
		case "Remove":
			//par1 = strtok(NULL, delimiters);
			if (par1 == NULL)
			{
				fprintf(stderr, "Remove failed: not enough parameters./n");
			}
			break;
		case "Add":
			//par1 = strtok(NULL, delimiters);
			//par2 = strtok(NULL, delimiters);
			//par3 = strtok(NULL, delimiters);
			//par4 = strtok(NULL, delimiters);
			if (par1 == NULL || par2 == NULL || par3 == NULL || par4 == NULL)
			{
				fprintf(stderr, "Add failed: not enough parameters./n");
			}
			break;
		case "Depart":
			//par1 = strtok(NULL, delimiters);
			//par2 = strtok(NULL, delimiters);
			if (par1 == NULL || par2 == NULL)
			{
				fprintf(stderr, "Depart failed: not enough parameters./n");
			}
			break;
		case "Change":
			//par1 = strtok(NULL, delimiters);
			//par2 = strtok(NULL, delimiters);
			if (par1 == NULL || par2 == NULL)
			{
				fprintf(stderr, "Change failed: not enough parameters./n");
			}
			break;
		case "Delay":
			//par1 = strtok(NULL, delimiters);
			if (par1 == NULL)
			{
				fprintf(stderr, "Delay failed: not enough parameters./n");
			}
			break;
		case "Print":
			break;
		case "Exit":
			break;
		default:
			fprintf(stderr, "Command not found./n");
			break;
		}
	}

//לקרוא שורה
//לחלק לפרמטרים
//קייס לכל פקודה
//בדיקת פרמטרים
//ביצוע
//
//קלט לא תקין שגיאה
//חוסר בפרמטרים
//פקודה לא מוכרת
//כשלון פקודה
//
//עבור עודף פרמטרים מתעלמים מהעודף וממשיכים כרגיל
//
//אם נגמר הקלט לשחרר מבנה נתונים
//ותסיים


	
	
	return 0;
}