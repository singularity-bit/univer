#include <stdio.h>
#include <stdlib.h>
#define SIZE 7
#define White 1
#define Grey 2
#define Black 3

int k,kq,nd[SIZE],color[SIZE],queue[SIZE],mt[SIZE][SIZE];

void introd_nod(int a){
    nd[k]=a;
    ++k;
}

void introd_arc(int a, int b){
    mt[a][b]=mt[b][a]=1;
}

int caut_nod(int a){
    for(int i=0; i<k; i++)
        if(nd[i]==a)
        return 1;
    return 0;
}

int caut_arc(int a, int b){
    for(int i=0; i<k; i++)
        for(int j=0; j<k; j++)
            if(mt[a][b]==1 || mt[b][a]==1)
                return 1;
    return 0;
}

void ster_nod(int a){
    for(int i=0; i<k; i++)
        if(nd[i]==a)
            nd[i]=-1;

    a--;
    for(int i=0; i<k; i++){
        mt[a][i]=0;
        mt[i][a]=0;
    }



}

void ster_arc(int a, int b){
    for(int i=0; i<k; i++)
        for(int j=0; j<k; j++){
            if(mt[a][b]==1) mt[a][b]=0;
            if(mt[b][a]==1) mt[b][a]=0;
        }
}

void afis(){
    for(int i=0; i<k; i++)
        printf(" %d",nd[i]);
    printf("\n");

    for(int i=0; i<k; i++){
        printf("\n");
        for(int j=0; j<k; j++)
            printf(" %d", mt[i][j]);
    }
    printf("\n\n");
}

void DeepSearch(int nod){
    printf("%d - White\n", nd[nod]);
    color[nod]=Grey;
    printf("%d - Grey\n", nd[nod]);
    for(int i=0; i<k; i++)
        if(mt[nod][i]==1 && color[i]==White){
            DeepSearch(i);
        }
    printf("%d - Black\n", nd[nod]);
}

void Deep(){
    for(int i=0; i<k; i++) color[i]=White;
    for(int i=0; i<k; i++) if(color[i]==White) DeepSearch(i);
}

void add_queue(int x){
    queue[kq++] = nd[x];
}

int extrage_queue(){
    int aux;
    aux = queue[0];
    for(int i=0; i<kq; i++) queue[i] = queue[i+1];
    kq--;
    return aux;
}

void BreadthSearch(){
    for(int i=0; i<k; i++) color[i]=White;
    int c = k, nod = 0;
    color[0] = Grey;
    add_queue(0);
    while(c){
        for(int i=0; i<k; i++)
        if(mt[nod][i]==1 && color[i]==White){
            color[i]=Grey;
            add_queue(i);
            i=extrage_queue();
            color[i] = Black;
            c--;
            nod = i;
        }

    }

}

int main(){
    int sw,a,b;

    introd_nod(0);
    introd_nod(1);
    introd_nod(2);
    introd_nod(3);
    introd_nod(4);
    introd_nod(5);

    introd_arc(0,1);
    introd_arc(1,2);
    introd_arc(1,4);
    introd_arc(2,3);
    introd_arc(4,5);

    while(1){
        printf("\n\n[0] Iesire\n");
        printf("[1] Intruducere nod\n");
        printf("[2] Introducere arc\n");
        printf("[3] Cautare nod\n");
        printf("[4] Cautare arc\n");
        printf("[5] Stergere nod\n");
        printf("[6] Stergere arc\n");
        printf("[7] Traversare in adancime\n");
        printf("[8] Traversare prin cuprindere\n");
        printf("[9] Afisare\n");
        printf("Opțiunea:");
        scanf("%d",&sw);
        switch(sw){
            case 0: return 0;
            case 1:{
                printf("\nNod: ");
                scanf("%d", &a);
                introd_nod(a);
            }break;

            case 2:{
                printf("\nArc: ");
                scanf("%d %d", &a, &b);
                introd_arc(a,b);
            }break;

            case 3:{
                printf("\nNod: ");
                scanf("%d", &a);
                if(caut_nod(a)) printf("Nodul exista!");
                else printf("Nodul nu exista!");
            }break;

            case 4:{
                printf("\nArc: ");
                scanf("%d", &a);
                scanf("%d %d", &a, &b);
                if(caut_arc(a,b)) printf("Arcul exista!");
                else printf("Arcul nu exista!");
            }break;

            case 5:{
                printf("\nNod: ");
                scanf("%d", &a);
                ster_nod(a);
            }break;

            case 6:{
                printf("\nArc: ");
                scanf("%d %d", &a, &b);
                ster_arc(a,b);
            }break;

            case 7: Deep();
                break;

            case 8: BreadthSearch();
                break;

            case 9: afis();
                break;
        }
    }
    return 0;
}


