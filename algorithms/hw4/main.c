#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct agac{
	int data;
	struct agac *left,*right;
}node;

node *ilk =NULL;


typedef struct kuyrukDugum {
    node* data;
    struct kuyrukDugum* next;
} kuyrukDugum;

typedef struct kuyruk {
    kuyrukDugum* front;
    kuyrukDugum* rear;
} kuyruk;


void enqueue(kuyruk* queue, node* data) {
    kuyrukDugum* yeniDugum = (kuyrukDugum*)malloc(sizeof(kuyrukDugum));
    yeniDugum->data = data;
    yeniDugum->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = yeniDugum;
    } else {
        queue->rear->next = yeniDugum;
        queue->rear = yeniDugum;
    }
}

node* dequeue(kuyruk* queue) {
    if (queue->front == NULL) {
        return NULL;
    }

    kuyrukDugum* temp = queue->front;
    node* data = temp->data;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    return data;
}


node *olustur(int data){
	node *yenidugum = (node*)malloc(sizeof(node));
	yenidugum->data = data; 
	yenidugum->left = NULL;
	yenidugum->right = NULL;
	return yenidugum;
}

node *ekle(node *ilk,int data){
    if (ilk==NULL)
    {
        ilk=olustur(data);
        return ilk;
    }
    if (data<ilk->data)
    {
        ilk->left=ekle(ilk->left,data);
    }
    else if (data>ilk->data)
    {
        ilk->right=ekle(ilk->right,data);
    }
    return ilk;
}

void oncekok(node* ilk){
    if (ilk == NULL) return;
    printf("%d ",ilk->data);
    oncekok(ilk->left);
    oncekok(ilk->right);
    
}
int queueSize(kuyruk* queue) {
    if (queue->front == NULL)
        return 0;

    int sayac = 0;
    kuyrukDugum* gecici = queue->front;

    while (gecici != NULL) {
        sayac++;
        gecici = gecici->next;
    }

    return sayac;
}


void levelYazdir(node* root) {
    if (root == NULL) return;

    kuyruk* queue = (kuyruk*)malloc(sizeof(kuyruk));
    queue->front = NULL;
    queue->rear = NULL;

    enqueue(queue, root);

    int level = 1;

    while (queue->front!=NULL) {
        int elemanSayisi = queueSize(queue);
        printf("Seviye %d: ", level);

        for (int i = 0; i < elemanSayisi; i++) {
            node* gecici = dequeue(queue);
            printf("%d ", gecici->data);

            if (gecici->left != NULL)
                enqueue(queue, gecici->left);

            if (gecici->right != NULL)
                enqueue(queue, gecici->right);
        }

        printf("\n");
        level++;
    }

    free(queue);
}




node * terscevir(node * ilk){
    node *sag=ilk->right;
    node *sol=ilk->left;
    ilk->right=sol;
    ilk->left=sag;
    return ilk;
}


int main(){
    int dizi[]={40, 70, 50, 30, 25, 80, 75, 5};
    for (int i = 0; i < (sizeof(dizi) / sizeof(dizi[0])); i++)
    {
        ilk=ekle(ilk,dizi[i]);
    }
    printf("Agac: \n");
    levelYazdir(ilk);
    terscevir(ilk);
    printf("\nSimetriden sonra agac :\n");
    levelYazdir(ilk);
}