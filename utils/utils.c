#include <stdio.h>
#include <string.h>

void CaculateWeekDay(int y,int m, int d)
{
	if(m==1||m==2) {
		m+=12;
		y--;
	}
	int week=(d+2*m+3*(m+1)/5+y+y/4-y/100+y/400+1)%7;
	switch(week)
	{
		case 1: printf("星期一\n"); break;
		case 2: printf("星期二\n"); break;
		case 3: printf("星期三\n"); break;
		case 4: printf("星期四\n"); break;
		case 5: printf("星期五\n"); break;
		case 6: printf("星期六\n"); break;
		case 0: printf("星期日\n"); break;
	}
}

