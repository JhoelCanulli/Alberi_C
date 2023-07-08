#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct nodo{
    struct nodo* p;
    struct nodo* l;
    struct nodo* r;
    int info;
}nodo;

typedef nodo* albero;

/* CREAZIONE ALBERO */
void add_root(albero *t, int info);
albero add_left(albero t, int v);
albero add_right(albero t, int v);

/* SCRIVI SU FILE DOT */
void generaDot(albero radice, FILE* fp);

/* TESTER */
void tester(albero a);

/* PRE TEST */
int conta_foglie(albero t);
bool verifica_esistenza_foglia_destra(albero a);
bool verifica_esistenza_foglia_sinistra(albero a);
bool verifica_esistenza_foglia_info_val(albero a, int val);
bool verifica_esistenza_due_foglie_info_val(albero a, int val);
int altezza_albero(albero a);
int conta_nodi(albero a);
int conta_nodi_info_2(albero a);
bool verifica_nodo_info_come_altezza(albero a);
int conta_nodi_interni(albero a);
int profondo(albero a);
bool verifica_nodo_info_dista_root(albero a);
bool verifica_padri_due_foglie(albero a);
int conta_nodi_info_prof(albero a);
bool verifica_albero_completo(albero a);
int somma_info_nodi(albero a);
bool verifica_solo_figli_sx(albero a);
int conta_nodi_sx(albero a);
bool verifica_gemelli(albero a);
bool verifica_nodo_info_altezza(albero a, int h);
bool verifica_foglia_info_altezza(albero a, int h);
int conta_nodi_info_prof_ric(albero a, int p);

#define MAX 20

int main(){
    albero t1 = NULL;
    int val[MAX];

    srand(time(NULL));
    for(int i = 0; i<MAX; i++){
        val[i] = (rand() % 100)+1;
    }
    val[7] = 3;

    add_root(&t1, val[0]);

    nodo* l = add_left(t1, val[1]);
    nodo* r = add_right(t1, val[2]);
    nodo* ll = add_left(l,val[3]);
    nodo* lr = add_right(l,val[4]);
//    nodo* rl = add_left(r,val[5]);
    nodo* rr = add_right(r,val[6]);
    nodo* lll = add_left(ll,val[7]);
    nodo* llr = add_right(ll, val[8]);
    nodo* lrl = add_left(lr, val[9]);
//    nodo* lrr = add_right(lr, val[10]); 


    /* genero il file dot */
    FILE* fp = fopen("albero.dot", "w");
    fprintf(fp, "digraph {\n");
    generaDot(t1, fp);
    fprintf(fp, "}\n");
    fclose(fp);
    /* genero l'immagine png */
    system("dot -Tpng albero.dot -o albero.png");

    tester(t1);
}

/* CREAZIONE ALBERO */
void add_root(albero *t, int info){
    if((*t) != NULL){
        printf("\nInserimento radice fallito poiché in questo albero già é presente una radice\n");
        return;
    }
    albero root = (albero)malloc(sizeof(nodo));
    root->p = NULL;
    root->l = NULL;
    root->r = NULL;
    root->info = info;
    (*t) = root;
}
albero add_left(albero t, int v){
    if(t->l!= NULL){
        printf("\n Nodo a sinistra già esistente.\n");
    }
    t->l = (albero)malloc(sizeof(nodo));
    t->l->p = t;
    t->l->l = NULL;
    t->l->r = NULL;
    t->l->info = v;

    return t->l;
}
albero add_right(albero t, int v){
    if(t->r != NULL){
        printf("\n Nodo a sinistra già esistente");
    }
    t->r = (albero)malloc(sizeof(nodo));
    t->r->p = t;
    t->r->l = NULL;
    t->r->r = NULL;
    t->r->info = v;

    return t->r;
}


/* SCRIVI SU FILE DOT */
void generaDot(albero radice, FILE* fp) {
    if (radice == NULL)
        return;
    char indirizzo[30];
    sprintf(indirizzo, "%p", (void *) radice);
    fprintf(fp, "\"%s\" [label=%d];\n", indirizzo, radice->info);
    if (radice->l)
    {
        char indirizzo_l[30];
        sprintf(indirizzo_l, "%p", (void *) radice->l);
        fprintf(fp, "\"%s\" -> \"%s\" [label=sx];\n", indirizzo, indirizzo_l);
    }
    if (radice->r)
    {
        char indirizzo_r[30];
        sprintf(indirizzo_r, "%p", (void *) radice->r);
        fprintf(fp, "\"%s\" -> \"%s\" [label=dx];\n", indirizzo, indirizzo_r);
    }
    generaDot(radice->l, fp);
    generaDot(radice->r, fp);
}

/* PRE TEST */
/* Conta il numero dei nodi che sono foglie */
int conta_foglie(albero t){
    if(t == NULL) return 0;
    if((t->l == NULL) && (t->r == NULL)) return 1;
    return conta_foglie(t->l) + conta_foglie(t->r);

}
/* versione alternativa 
int conta_foglie(albero a){
    if(a==NULL) return 0;
    int count = 0;
    if(a->l==NULL && a->r==NULL) count++;
    return (count + conta_foglie(a->l) + conta_foglie(a->r));
}*/

/* Verifica se esiste una foglia a destra */
bool verifica_esistenza_foglia_destra(albero a){
    if(a == NULL) return false;
    if(a->r != NULL && (a->r->l == NULL && a->r->r == NULL)) return true;
    return (verifica_esistenza_foglia_destra(a->l) || verifica_esistenza_foglia_destra(a->r));
}
/* Verifica se esiste una foglia a sinistra */
bool verifica_esistenza_foglia_sinistra(albero a){
    if(a==NULL) return false;
    if(a->l!=NULL && (a->l->l==NULL && a->l->r==NULL)) return true;
    return (verifica_esistenza_foglia_sinistra(a->l) || verifica_esistenza_foglia_sinistra(a->r));
}
/* Verifica se esiste almeno una foglia con campo info uguale ad un valore (val) da input */
bool verifica_esistenza_foglia_info_val(albero a, int val){
    if(a == NULL) return false;
    if(a->info == val && (a->l == NULL && a->r == NULL)) return true;
    return (verifica_esistenza_foglia_info_val(a->l, val) || verifica_esistenza_foglia_info_val(a->r, val));
}
/* Verifica se esistono due foglie con campo info uguale ad un valore (val) da input */
bool verifica_esistenza_due_foglie_info_val(albero a, int val){
    int static count = 0;
    if(a==NULL) return false;
    if(a->info==val && (a->l==NULL && a->r==NULL)) count++;
    if(count==2) return true;
    return (verifica_esistenza_due_foglie_info_val(a->l,val) || verifica_esistenza_due_foglie_info_val(a->r, val));
}

/* senza static non funziona 
int conta_foglie_info(albero a, int val){
    int c = 0;
    if(a == NULL) return 0;
    if(a->l == NULL && a->r == NULL && a->info == val){
        c++;  
    }else{
        c = c+verifica_esistenza_due_foglie_info_val(a->l, val)+verifica_esistenza_due_foglie_info_val(a->r, val);
    }
    return c;
}

bool verifica_esistenza_due_foglie_info_val(albero a, int val){
    if(a == NULL) return false;
    if(conta_foglie_info(a,val) == 2) return true;
    return false;
}*/

// Funzione che calcola l'altezza dell'albero
int altezza_albero(albero a){
    if(a==NULL) return -1;
    int hl = altezza_albero(a->l);
    int hr = altezza_albero(a->r);
    if(hl < hr) return hr+1;
    return hl+1;
}

/* versione alernativa  
int altezza_albero(albero a){
    if(a==NULL) return -1;

    int hleft = altezza_albero(a->l);
    int hright = altezza_albero(a->r);

    int max = hleft;
    if(hright > max){
        max = hright;
    }
    
    return max+1;
}*/

/* Funzione che calcola il numero dei nodi dell'albero */
int conta_nodi(albero a){
    if(a == NULL) return 0;
    return 1 + conta_nodi(a->l) + conta_nodi(a->r);
}
/* Conta il numero dei nodi con campo info uguale a 2 */
int conta_nodi_info_2(albero a){
    if(a==NULL) return 0;
    if(a->info == 2) return 1;
    return (conta_nodi_info_2(a->l) + conta_nodi_info_2(a->r));
}
/* Verifica se esiste un nodo con campo info pari all'altezza dell'albero */
bool verifica_ric(albero a, int h){
    if(a==NULL) return false;
    if(h == a->info) return true;
    return (verifica_ric(a->l, h) || verifica_ric(a->r, h));
}

bool verifica_nodo_info_come_altezza(albero a){
    return verifica_ric(a, altezza_albero(a));
}

/* Conta i nodi interni */
int conta_nodi_interni(albero a){
    if(a == NULL) return 0;
    int count = 0;
    if(!(a->l==NULL && a->r==NULL)) count++;
    return count + conta_nodi_interni(a->l) + conta_nodi_interni(a->r);
}

/* versione alternativa 
int conta_nodi_interni(albero a){
    if(a==NULL) return 0;
    if(!(a->l == NULL && a->r == NULL)) return 1 + conta_nodi_interni(a->l) + conta_nodi_interni(a->r);
}*/
/* Conta la profondità di un nodo che gli viene passato, ossia la sua distanza dalla radice */
int profondo(albero a){
    if(a == NULL) return -1;
    return 1 + profondo(a->p);
}
/* Funzione che verifica se esiste almeno un nodo con campo info uguale alla sua profondità */
bool verifica_nodo_info_dista_root(albero a){
    if(a==NULL) return false;
    if(a->info == profondo(a)) return true;
    return verifica_nodo_info_dista_root(a->l) || verifica_nodo_info_dista_root(a->r);
}

/* Funzione che verifica se esiste un nodo che ha entrambi i figli foglie */
int is_foglia(albero a){
    if(a == NULL) return false;
    if(a->l == NULL && a->r == NULL) return true;
    return false;
}

bool verifica_padri_due_foglie(albero a){
    if(a == NULL) return false;
    if(a->l != NULL && a->r != NULL && 
        is_foglia(a->l) && is_foglia(a->r)) return true;
    return verifica_padri_due_foglie(a->l) || verifica_padri_due_foglie(a->r);
}

/* alternativa 
bool verifica_padri_due_foglie(albero t){
    if (t == NULL)
        return false;

    if (t->l != NULL && t->r != NULL && t->l->l == NULL && t->l->r == NULL && t->r->l == NULL && t->r->r == NULL)
        return true;

    return verifica_padri_due_foglie(t->l) || verifica_padri_due_foglie(t->r);
}
*/

/* Numero nodi con campo info pari alla distanza dalla radice */
int conta_nodi_info_prof_ric(albero a, int p){
    if(a==NULL) return 0;
    int count = 0;
    if(a->info == p) count++;
    return count+conta_nodi_info_prof_ric(a->l, p+1)+conta_nodi_info_prof_ric(a->r, p+1);
}

int conta_nodi_info_prof(albero a){
    return conta_nodi_info_prof_ric(a, 0);
}

/* alternativa
int conta_nodi_info_prof_(albero a){
    if(a==NULL) return 0;
    int count = 0;
    if(a->info == profondo(a)) count++;
    return (count + conta_nodi_info_prof_(a->l) + conta_nodi_info_prof_(a->r));
}
*/

/* Verifica se ogni nodo dell'albero ha due figli (albero completo)*/
bool verifica_albero_completo(albero a){
    if(a==NULL) return false;
    if(a->l == NULL && a->r == NULL) return true;
    return (verifica_albero_completo(a->l) && verifica_albero_completo(a->r));
}

int somma_info_nodi(albero a){
    if(a == NULL) return 0;
    int somma = a->info;
    return (somma + somma_info_nodi(a->l) + somma_info_nodi(a->r));
}
/* verifica se l'albero ha solo nodi a sinistra */
bool verifica_solo_figli_sx(albero a){
    if(a == NULL) return false;
    if(a->l != NULL && a->r == NULL) return true;
    return (verifica_solo_figli_sx(a->l) && verifica_solo_figli_sx(a->r));
}
/* Conta quanti sono i nodi a sx (variante a dx) *//*
int conta_nodi_sx(albero a){
    if(a==NULL) return 0;
    int count = 0;
    if(a->l!=NULL) count++;
    return (count+conta_nodi_sx(a->l)+conta_nodi_sx(a->r));
}*/
/* alternativa */
int conta_nodi_sx(albero a){
    if(a==NULL) return 0;
    if(a->l!=NULL) return (1+conta_nodi_sx(a->l)+conta_nodi_sx(a->r));
}
/* Verifica se esiste almeno un nodo che abbia due nodi figli e il figlio a sx ha campo info uguale al figlio a dx */
bool verifica_gemelli(albero a){
    if(a == NULL) return false;
    if((a->l != NULL && a->r != NULL) && (a->l->info == a->r->info)) return true;
    return (verifica_gemelli(a->l) || verifica_gemelli(a->r));
}

/* verifica se esiste almeno un nodo itnerno con campo info uguale altezza totale dell'albero */
bool verifica_nodo_interno_info_altezza(albero a, int h){
    if(a==NULL) return false;
    if(!(a->l==NULL && a->r==NULL) && (a->info == h)) return true;
    return (verifica_nodo_interno_info_altezza(a->l, h) || verifica_nodo_interno_info_altezza(a->r, h));
}

/* verifica se almeno un nodo foglia con campo info uguale altezza totale dell'albero */
bool verifica_foglia_info_altezza(albero a, int h){
    if(a==NULL) return false;
    if((a->l==NULL && a->r==NULL) && a->info == h) return true;
    return (verifica_foglia_info_altezza(a->l,h) || verifica_foglia_info_altezza(a->r,h));
}


void tester(albero t1){
    
    int foglie = conta_foglie(t1);
    printf("\nnumero foglie albero: %d\n", foglie);

    bool foglia_destra_esiste = verifica_esistenza_foglia_destra(t1);
    if(foglia_destra_esiste){
        printf("\nl'albero possiede una foglia destra\n");
    }
    else{
        printf("\nl'albero non possiede una foglia destra\n");
    }

    bool foglia_sinistra_esiste = verifica_esistenza_foglia_sinistra(t1);
    if(foglia_sinistra_esiste){
        printf("\nl'albero possiede una foglia sinistra\n");
    }
    else{
        printf("\nl'albero non possiede una foglia sinistra\n");
    }
    
    int valore = 24;
    bool esiste_foglia_val = verifica_esistenza_foglia_info_val(t1, valore);
    if(esiste_foglia_val){
        printf("\nl'albero possiede una foglia con valore %d\n",valore);
    }
    else{
        printf("\nl'albero non possiede una foglia con valore %d\n",valore);
    }

    valore = 14;
    bool esistono_due_foglie_val = verifica_esistenza_due_foglie_info_val(t1, valore);
    if(esistono_due_foglie_val){
        printf("\nl'albero possiede due foglie con valore %d\n",valore);
    }
    else{
        printf("\nl'albero non possiede due foglie con valore %d\n",valore);
    }

    int altezza = altezza_albero(t1);
    printf("\nl'altezza dell'albero è %d archi\n",altezza);

    int tot_nodi = conta_nodi(t1);

    printf("\nil numero totale dei nodi dell'albero corrisponde a %d\n", tot_nodi);

    int conta_nodi_2 = conta_nodi_info_2(t1);
    printf("\nIl numero di nodi con valore pari a 2 é %d\n",conta_nodi_2);

    bool verifica_nodo_come_altezza = verifica_nodo_info_come_altezza(t1);
    if(verifica_nodo_come_altezza){
        printf("\nesiste un nodo con info pari all'altezza dell'albero\n");
    }else{
        printf("\nnon esiste alcun un nodo con info pari all'altezza dell'albero\n");
    }

    int conta_interni = conta_nodi_interni(t1);
    printf("\nIl numero di nodi interni corrisponde a %d\n",conta_interni);

    int verifica_nodo_come_prof_root = verifica_nodo_info_dista_root(t1);
    if(verifica_nodo_come_prof_root){
        printf("\nesiste almeno un nodo con info pari alla sua profondità\n");
    }else{
        printf("\nnon esiste nessun un nodo con info pari alla sua profondità\n");
    }

    bool verifica_padri = verifica_padri_due_foglie(t1);
    if(verifica_padri){
        printf("\nesiste almeno un nodo che ha entrambi i figli e sono foglie\n");
    }else{
        printf("\nnon esiste nessun nodo che ha entrambi i figli e sono foglie\n");
    }

    int nodi_prof_info = conta_nodi_info_prof(t1);
    printf("\nil numero di nodi con info pari a profondità é %d\n",nodi_prof_info);

    bool t_completo = verifica_albero_completo(t1);
    if(t_completo){
        printf("\nl'albero é un albero completo\n");
    }else{
        printf("\nl'albero non é un albero completo\n");
    }

    int somma_val_nodi = somma_info_nodi(t1);
    printf("\nla somma dei valori dei nodi corrisponde a %d\n", somma_val_nodi);

    bool solo_figli_sx = verifica_solo_figli_sx(t1);
    if(solo_figli_sx){
        printf("\nl'albero possiede solo figli a sinistra\n");
    }else{
        printf("\nl'albero non possiede solo figli a sinistra\n");
    }

    int conta_sx = conta_nodi_sx(t1);
    printf("\nil numero dei figli a sx é %d\n",conta_sx);

    bool gemelli = verifica_gemelli(t1);
    if(gemelli){
        printf("\nesiste almeno un nodo con due figli gemelli, ossia con lo stesso valore\n");
    }else{
        printf("\nnon esiste alcun nodo con due figli con lo stesso valore\n");
    }
    bool nodo_interno_info_h = verifica_nodo_interno_info_altezza(t1, altezza);
    if(nodo_interno_info_h){
        printf("\nesiste almeno un nodo interno con info pari all'altezza dell'albero\n");
    }else{
        printf("\nnon esiste alcun nodo interno con info pari all'altezza dell'albero\n");
    }

    bool foglia_info_h = verifica_foglia_info_altezza(t1, altezza);
    if(foglia_info_h){
        printf("\nesiste almeno una foglia col campo info pari all'altezza dell'albero\n");
    }else{
        printf("\nnon esiste alcuna foglia con campo info pari all'altezza dell'albero\n");
    }

}
