# Alberi_C
File C con elaborazioni su struttura albero, contenente: main, creazione struttura, funzioni varie di esercizio e tester.

Il file "alberi_PRE_TEST_Canulli.c" contiene la funzione generaDot: utilizzata per generare un file Dot che presenta l'albero creato. 
Tale funzione si avvia nel main scrivendo su file utilizzato FILE* fp, sotto il commento /* genero il file dot */ nel main.
La conversione da dot a png viene fatta attraverso la digitazione di "dot -Tpng albero.dot -o albero.png" nella funzione system e per avere successo é necessario istallare 
Graphviz, un software open source per la visualizzazione di grafici, compatibile per linux e windows.
