#ifndef ANALYZER_H
#define ANALYZER_H



void Begin(char *line);//точка входа приложения
int GetLeksema(char *line); //функция для получения элементарных единиц выражения-лексем
void Sum(double *number,char *line); // функция суммы слагаемых
int Elementary(double *leks,char *line); //функция для получения чисел из лексем
int Multi(double *number,char *line); // функция для умножения и деления
int Brack(double *number,char *line); // функция для выражений в скобках


#endif
