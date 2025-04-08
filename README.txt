Jmeno projektu: CSV databaze
Autor: David Sklenar
Datum: 3.1. 2023

K programu je prilozena makefile pro snadnejsi pouziti
Projekt je zameren na zpracovani csv souboru a upravovani pomoci nasledujicich commandu:

addrow <sloupec0>,<sloupec1>,<sloupec2>,...,<sloupecN> = Prida radek
addcol <sloupec> <radek0>,<radek1>,<radek2>,...,<radekN> = Prida sloupec
average <nazev-sloupce> = Vypocte prumernou hodnotu sloupce
max <nazev-sloupce> = Vypise nejvetsi hodnotu zadaneho sloupce
min <nazev-sloupce> = Vypise nejmensi hodnotu zadaneho sloupce
sum <nazev-sloupce> = Vypise soucet hodnot zadaneho sloupce
exit = Zapise upravenou databazi na zadanou vystupni cestu a ukonci program


Projekt je spousten se vstupnimi parametry v libovolnem poradi
--input <cesta k souboru> - cesta ke vstupnímu CSV souboru
--output <cesta k souboru> - cesta k výstupnímu CSV souboru


Vstup

name,surname,points
jakub,cocka,51
adam,lezak,60
jarmila,konikova,30
lenka,laskoradova,95

Priklad pouziti programu

$ ./databaze --output modified.csv --input input.csv
Soubor: input.csv, sloupce: 4, radky: 5
Zadejte prikaz: addrow jarek,nohavica,78
Radek byl pridan.
Zadejte prikaz: average points
Prumer sloupce points: 62.8
Zadejte prikaz: sum foo
Sloupec `foo` nebyl nalezen.
Zadejte prikaz: sum points
Soucet sloupce points: 314 
Zadejte prikaz: addcol age 19,25,44,75
Sloupec age byl pridan.
Zadejte prikaz: average age
Prumer sloupce age: 40.75
Zadejte prikaz: sum age
Soucet sloupce age: 163
Zadejte prikaz: sum name
Soucet sloupce name: 0
Zadejte prikaz: exit
Ukladam databazi do souboru modified.csv.