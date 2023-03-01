# Alberi_C
File C con elaborazioni su struttura albero, contenente: main, creazione struttura, funzioni varie di esercizio e tester.

Il file "alberi_PRE_TEST_Canulli.c" contiene la funzione generaDot: utilizzata per generare un file Dot che presenta l'albero creato. 
Tale funzione si avvia nel main scrivendo su file utilizzato FILE* fp, sotto il commento /* genero il file dot */ nel main.
La conversione da dot a png viene fatta attraverso la digitazione di "dot -Tpng albero.dot -o albero.png" nella funzione system e per avere successo é necessario istallare 
Graphviz, un software open source per la visualizzazione di grafici, compatibile per linux e windows.

Il file é intitolato PRE_TEST poiché all'interno ci sono alcune funzioni su cui mi sono esercitato per prepararmi al pre-test
dell'esame "algoritmi e strutture dati" presso l'università di ingegneria informatica Roma Tre.
Il pre-test consisteva in un esercizio da svolgere in 15 minuti su una consegna data dal professore inerente a una delle strutture tra "lista" ed "alberi".
Una volta superato il pre-test, l'esame consisteva di scrivere un programma in C penna su carta utilizzando strutture grafi ed alberi.
Superato anche l'esame scritto vi era l'esame orale, in cui venivano richieste implementazioni in pseudocodice su hashtable, commentate ed analizzate facendo il calcolo computazionale del loro costo, in base alla consegna del professore, e veniva richiesta una dimostrazione di teoria inerente a tutto il programma di algoritmi e strutture dati.

