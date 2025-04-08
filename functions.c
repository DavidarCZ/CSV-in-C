#include "functions.h"

int count_char(int length, char* string, char c)
{
    int count=0; 
    for (int i=0;i<length;i++)
    {
        if(string[i] == c)
        {
            count++;
        }
    }
    return count;
}

void add_row(col* CSV,int cols,int rows,char* token)
{
        for (int i = 0; i < cols; i++)
        {
            CSV[i].values[rows-1] = (char*) malloc((strlen(token)+1)*sizeof(char));
            strcpy(CSV[i].values[rows-1],token);
            token = strtok(NULL,",");
        }

}

void add_col(col* CSV,int cols,int rows,char* token)
{
    for (int i = 0; i < rows-1; i++)
    {
        CSV[cols].values[i] = (char*) malloc((strlen(token)+1)*sizeof(char));
        strcpy(CSV[cols].values[i],token);
        token = strtok(NULL,",");
        
    }
}

double average(col* CSV,int index,int rows)
{
    double average = 0;
    for (int i = 0; i < rows-1; i++)
    {
        average = average + atof(CSV[index].values[i]);        
    }
    return average/(rows-1);
}

double max (col* CSV,int index,int rows)
{
    double max = atof(CSV[index].values[0]);
    for (int i = 1; i < rows-1; i++)
    {
        if (max<atof(CSV[index].values[i]))
        {
            max = atof(CSV[index].values[i]);
        }      
    }
    return max;
}

double min(col* CSV,int index,int rows)
{
    double min = atof(CSV[index].values[0]);
    for (int i = 1; i < rows-1; i++)
    {
        if (min>atof(CSV[index].values[i]))
        {
            min = atof(CSV[index].values[i]);
        }      
    }
    return min;
}

double sum(col* CSV,int index,int rows)
{
    double sum = 0;
    for (int i = 0; i < rows-1; i++)
    {
        sum = sum + atof(CSV[index].values[i]);        
    }
    return sum;
}