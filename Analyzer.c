#include "stdio.h"
#include "Analyzer.h"
#include "string.h"
#include "ctype.h"
#include <stdlib.h>

char Leksema[10]; // переменная для хранения лексемы
enum {Empty, Number, Operator, Charakter } Type; //тип лексемы
enum {No, Syntax, DivisionByZero} Error;// тип ошибки


void Begin(char *Expr)
{
	
	double result;
	Error=No;
	GetLeksema(Expr);
	Sum(&result,Expr);
	switch (Error)
	{
	case No:
		printf("Результат: %.2f \n", result); 
		break;
	case DivisionByZero: 
		printf("Ошибка: деление на ноль \n "); 
		break;
	default: 
		break;
	}
}

int GetLeksema(char *line)
{
	static int i=0;
	if (line[i]=='\0') 
	{
		i=0;
		return i;
	}
	while (isspace(line[i])) i++;
	int j=0;
	if (isalpha(line[i]))
	{
		Leksema[j]=line[i];
		while(isalpha(line[i+1]))
		{
			j++; i++;
			Leksema[j]=line[i];
		}
		Type=Charakter;
	}
	if (strchr("+-/*()",line[i]))
	{
		Leksema[j]=line[i];
		Type=Operator;
		
	}
	if (isdigit(line[i]))
	{
		Leksema[j]=line[i];
		while ((isdigit(line[i+1])) ||(line[i+1]=='.' || line[i+1]==','))
		{
			j++;
			i++;
			if (line[i]=='.')
				Leksema[j]=',';
			else
			Leksema[j]=line[i];
		}
		Type=Number;
	}
	Leksema[j+1]='\0';
	i++;
	return i;
}

void Sum(double *number,char *Expr)
{
	if (Multi(number,Expr))
		return;
	char oper;
	double tempage;
	while ((oper=*Leksema)=='+' || oper=='-')
	{
		GetLeksema(Expr);
		if (Multi(&tempage,Expr))
		return;
		if (oper=='+')
			*number=*number+tempage;
		else
		*number=*number-tempage;
	}
}

int Multi(double *number,char *Expr)
{
	if (Brack(number,Expr))
		return 1;
	char oper;
	double temp;
	while ((oper=*Leksema)=='*' || oper=='/')
	{
		GetLeksema(Expr);
		if (Elementary(&temp,Expr)) return 1;
		if (oper=='*')
			*number=*number*temp;
		else
		{
			if (temp==0) 
			{
				Error=DivisionByZero;
				return 1;
			}
			*number=*number/temp;
		}
	}
	return 0;
}

int Brack(double *leks,char *Expr)
{
	if (*Leksema=='(')
	{
		GetLeksema(Expr);
		Sum(leks,Expr);
		if (*Leksema!=')')
			return 1;
		GetLeksema(Expr);
	}
	else
		if (Elementary(leks,Expr))
			return 1;
		
		return 0;
}

int Elementary(double *leks,char *Expr)
{
	if (Type==Number)
	{
		*leks=atof(Leksema);
		GetLeksema(Expr);
		return 0;
	}
	else 
	{
		Error=Syntax;
		printf("Недопустимое выражение: %s \n", Leksema); 
		return 1;
	}
}
