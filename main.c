#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "functions.h"

 int main(int argc, char** argv)
{
    if (argc != 5)
    {
        printf("Wrong number of parameters\n");
        return 1;
    }

    char in [] = "--input";
    char out [] = "--output";

    char* input;
    char* output;

    if ((strcmp(in,argv[1])==0)&&(strcmp(out,argv[3])==0))
    {
        input = (char*) malloc((strlen(argv[2])+1) * sizeof(char));
        strcpy(input,argv[2]);
        output = (char*) malloc((strlen(argv[4])+1) * sizeof(char));
        strcpy(output,argv[4]);
    }
    else
    {
        if ((strcmp(in,argv[3])==0)&&(strcmp(out,argv[1])==0))
        {
            input = (char*) malloc((strlen(argv[4])+1) * sizeof(char));
            strcpy(input,argv[4]);
            output = (char*) malloc((strlen(argv[2])+1) * sizeof(char));
            strcpy(output,argv[2]);
        }
        else
        {
            printf("Wrong format of parameters\n");
            return 1;
        }
    } 
   
    FILE* inputFile = fopen(input, "r");
    if(inputFile == NULL) 
    {
        printf("Could not load dictionary\n");
        return 1;
    }

    FILE* outputFile = fopen(output, "w");
    if (outputFile == NULL) 
    {
        printf("Could not load output file\n");
        return 1;
    }
    
    char buf[256];
    fgets(buf,sizeof(buf),inputFile);
    buf[strcspn(buf, "\n")] = 0;

    int cols = count_char(strlen(buf),buf,',')+1;
    int rows = 1;
    
    for (char c = getc(inputFile); c != EOF;c = getc(inputFile))
    {   
        if (c == '\n')
        {
            rows = rows + 1;
        }
    }
    rows = rows + 1;
    rewind(inputFile);

    char* token;
    col* CSV = (col*) malloc(cols * sizeof(col));
    fgets(buf,sizeof(buf),inputFile);
    buf[strcspn(buf, "\n")] = 0;
    token = strtok(buf,",");

    for (int i = 0; i < cols; i++)
    {
        CSV[i].name = (char*) malloc((strlen(token)+1)*sizeof(char));
        strcpy(CSV[i].name,token);
        token = strtok(NULL,",");
        CSV[i].values = (char**) malloc((rows-1)*sizeof(char*));
    }
    
    for (int i = 0; i < cols; i++)
    {
        printf("%s ",CSV[i].name);
    }

    
    for (int i = 0; i < (rows-1); i++)
    {
        char buf2[256];
        fgets(buf2,sizeof(buf2),inputFile);
        buf2[strcspn(buf2, "\n")] = 0;
        token = strtok(buf2,",");
        for (int j = 0; j < cols; j++)
        {
            CSV[j].values[i] = (char*) malloc((strlen(token)+1)*sizeof(char));
            strcpy(CSV[j].values[i],token);
            token = strtok(NULL,",");
        }
    }

    printf("Soubor: %s, sloupce: %d, radky: %d\n",input,cols,rows);
   while (1)
    {
        char buf2[256];
        printf("Zadejte prikaz: ");
        fgets(buf2,sizeof(buf2),stdin);
        buf2[strcspn(buf2, "\n")] = 0;
        int correct = count_char(strlen(buf2),buf2,',')+1;
        char* first = strtok(buf2," ");
        if (strcmp(first,"addrow")==0)
        {
            if (correct!=cols)
            {
                printf("Nespravny format.\n");
            }
            else
            {
            token = strtok(NULL,",");
            for (int i = 0; i < cols; i++)
            {
                CSV[i].values = (char**) realloc(CSV[i].values,(rows)*sizeof(char*));
            }
            add_row(CSV,cols,rows,token);
            rows = rows+1;
            printf("Radek byl pridan.\n");
            }
        }
        else
        {
            if (strcmp(first,"addcol")==0)
            {
                if (correct!=rows-1)
                {
                    printf("Nespravny format.\n");
                }
                else
                {
                CSV = (col*) realloc(CSV,(cols+1)*sizeof(col));
                CSV[cols].values = (char**) malloc((rows-1)*sizeof(char*));
                token = strtok(NULL," ");
                CSV[cols].name = (char*) malloc((strlen(token)+1)*sizeof(char));
                strcpy(CSV[cols].name,token);
                token = strtok(NULL,",");
                add_col(CSV,cols,rows,token);
                cols = cols+1;
                printf("Sloupec age byl pridan.\n");
                }
            }
            else
            {
                if (strcmp(first,"average")==0)
                {
                    token = strtok(NULL,"");
                    int exists = 0;
                    int i;
                    for ( i = 0; i < cols; i++)
                    {
                        if(strcmp(CSV[i].name,token)==0)
                        {
                            exists = 1;
                            break;
                        }
                    }
                    if (!exists)
                    {
                        printf("Sloupec `%s` nebyl nalezen.\n",token);
                    }
                    else
                    {
                    printf("Prumer sloupce points: %.1f\n",average(CSV,i,rows));
                    }
                }
                else
                {
                    if (strcmp(first,"max")==0)
                    {
                        token = strtok(NULL,"");
                        int exists = 0;
                        int i;
                        for ( i = 0; i < cols; i++)
                        {
                            if(strcmp(CSV[i].name,token)==0)
                            {
                                exists = 1;
                                break;
                            }
                        }
                        if (!exists)
                        {
                            printf("Sloupec `%s` nebyl nalezen.\n",token);
                        }
                        else
                        {
                        printf("Maximum sloupce points: %.1f\n",max(CSV,i,rows));
                        }
                    }
                    else
                    {
                        if (strcmp(first,"min")==0)
                        {
                            token = strtok(NULL,"");
                            int exists = 0;
                            int i;
                            for ( i = 0; i < cols; i++)
                            {
                                if(strcmp(CSV[i].name,token)==0)
                                {
                                    exists = 1;
                                    break;
                                }
                            }
                            if (!exists)
                            {
                                printf("Sloupec `%s` nebyl nalezen.\n",token);
                            }
                            else
                            {
                            printf("Minimum sloupce points: %.1f\n",min(CSV,i,rows));
                            }
                        }
                        else
                        {
                            if (strcmp(first,"sum")==0)
                            {
                                token = strtok(NULL,"");
                                int exists = 0;
                                int i;
                                for ( i = 0; i < cols; i++)
                                {
                                    if(strcmp(CSV[i].name,token)==0)
                                    {
                                        exists = 1;
                                        break;
                                    }
                                }
                                if (!exists)
                                {
                                    printf("Sloupec `%s` nebyl nalezen.\n",token);
                                }
                                else
                                {
                                printf("Soucet sloupce points: %.1f\n",sum(CSV,i,rows));
                                }
                            }
                            else
                            {
                                if (strcmp(first,"exit")==0)
                                {
                                    for (int i = 0; i < cols; i++)
                                    {
                                        fprintf(outputFile, "%s",CSV[i].name);
                                        if (i!=cols-1)
                                        {
                                            fprintf(outputFile, ",");
                                        }              
                                    }
                                    fprintf(outputFile, "\n");

                                    for (int i = 0; i < rows-1; i++)
                                    {
                                        for (int j = 0; j < cols; j++)
                                        {
                                            fprintf(outputFile, "%s",CSV[j].values[i]);
                                            if (j!=cols-1)
                                            {
                                                fprintf(outputFile, ",");
                                            }
                                        }
                                        if (i!=rows-2)
                                            {
                                                fprintf(outputFile, "\n");
                                            }
                                    }

                                    printf("Ukladam databazi do souboru %s.\n",output);
                                    break;
                                }
                                else
                                {
                                    printf("Neplatny prikaz\n");
                                }
                                
                            }
                        }   
                    }
                }
            }
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    for (int i = 0; i < cols; i++) {
        
        for (int j = 0; j < rows - 1; j++) {
            if (CSV[i].values[j] != NULL) {
                free(CSV[i].values[j]);
            }
        }
        
        if (CSV[i].values != NULL) {
            free(CSV[i].values);
        }
        
        if (CSV[i].name != NULL) {
            free(CSV[i].name);
        }
    }
    free(CSV);

    free(input);
    free(output);
    return 0;
}