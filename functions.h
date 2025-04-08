#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

typedef struct
{
    char* name;
    char** values;
} col;

int count_char(int length, char* string, char c);

void add_row(col* CSV,int cols,int rows,char* token);

void add_col(col* CSV,int cols,int rows,char* token);

double average(col* CSV,int index,int rows);

double max (col* CSV,int index,int rows);

double min(col* CSV,int index,int rows);

double sum(col* CSV,int index,int rows);