#include "stdio.h"
#include "Analyzer.h"
#include "string.h"

extern void Begin(char *expr);

void main()
{
	char Expr[200];
	char NullForExpr[200];
	NullForExpr[0]='0'; NullForExpr[1]='\0';
	
	while (1)
	{
		printf("Введите выражение. \n");
		gets(Expr);
		if (!*Expr)
		{
			break;
			return;
		}
		if (Expr[0]=='-')//if the first symbol-null
		{
			strcat(NullForExpr,Expr);
			Begin(NullForExpr);
		}
		else
			Begin(Expr);
	}
}
