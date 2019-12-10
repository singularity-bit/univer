#include<stdio.h>
#include<stdlib.h>
#define SIZE 20
struct coada{
    int elemente[SIZE];
    int prim;
    int ultim;
};
struct coada*creareCoada();
void introduceCoada(struct coada*q,int);
int scoateCoada(struct coada*q);
void afisare(struct coada*q);
int isEmpty(struct coada*q);
void afisareCoada(struct coada*q);
struct nod{
    int nod;
    struct nod*next;
};
struct nod*creareNode(int);
struct graf{
    int nrNod;
    struct nod**adjList;
    int*vizitat;
};
struct graf*creareGraf(int noduri);
void addEdge(struct graf*graf,int src,int dest);
void afseazaGraf(struct graf*graf);
void bfs(struct graf*graf,int startNod);
void bfs(struct graf*graf,int startNod){
    struct coada*q=creareCoada();
    graf->vizitat[startNod]=1;
    introduceCoada(q,startNod);
    while(!isEmpty(q)){
        afisareCoada(q);
        int nodCurent=scoateCoada(q);
        printf("\nVizitat %d\n",nodCurent);
        struct nod*temp=graf->adjList[nodCurent];
        while(temp){
            int adjNod=temp->nod;
            if(graf->vizitat[adjNod]==0){
                graf->vizitat[adjNod]=1;
                introduceCoada(q,adjNod);
            }
            temp=temp->next;
        }
    }
}
struct nod*creareNode(int v){
    struct nod*nodNou=malloc(sizeof(struct nod));
    nodNou->nod=v;
    nodNou->next=NULL;
    return nodNou;
}
struct graf*creareGraf(int nod){
    struct graf*graf=malloc(sizeof(struct graf));
    graf->nrNod=nod;
    graf->adjList=malloc(nod*sizeof(struct nod*));
    graf->vizitat=malloc(nod*sizeof(int));
    int i;
    for(i=0;i<nod;i++){
        graf->adjList[i]=NULL;
        graf->vizitat[i]=0;
    }
    return graf;
}
void addEdge(struct graf*graf,int src,int dest){
    struct nod*nodNou=creareNode(dest);
    nodNou->next=graf->adjList[src];
    graf->adjList[src]=nodNou;
    nodNou=creareNode(src);
    nodNou->next=graf->adjList[dest];
    graf->adjList[dest]=nodNou;
}
struct coada*creareCoada(){
    struct coada*q=malloc(sizeof(struct coada));
    q->prim=-1;
    q->ultim=-1;
    return q;
}
int isEmpty(struct coada*q){
    if(q->ultim==-1)
        return 1;
    else 
        return 0;
}
void introduceCoada(struct coada*q){
    int element;
    if(isEmpty(q)){
        printf("\nCoada este goala");
        element=-1;
    }else{
        element=q->elemente[q->prim];
        q->prim++;
        if(q->prim>q->ultim){
            printf("\nResetare coada!");
            q->prim=q->ultim=-1;
        }
    }
    return element;
}
void afisareCoada(struct coada*q){
    int i=q->prim;
    if(isEmpty(q)){
        printf("\nCoada este goala!");
    }else{
        printf("\nCoada contine\n");
        for(i=q->prim;i<q->ultim+1;i++){
            printf("%d",q->elemente[i]);
        }
    }
}
int main(){
        struct graf* graf = creareGraf(6);
        addEdge(graf, 0, 1);
        addEdge(graf, 0, 2);
        addEdge(graf, 1, 2);
        addEdge(graf, 1, 4);
        addEdge(graf, 1, 3);
        addEdge(graf, 2, 4);
        addEdge(graf, 3, 4);
     
        bfs(graf, 0);
        return 0;
}