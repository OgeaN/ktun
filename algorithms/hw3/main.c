#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct agac{
	char harf;
	int frekans;
	struct agac *next,*left,*right;
}node;

node *ilk = NULL;


node *olustur(char harf){
	node *yenidugum = (node*)malloc(sizeof(node));
	yenidugum->frekans = 1; 
	yenidugum->harf = harf;
	yenidugum->next = NULL;
	yenidugum->left = NULL;
	yenidugum->right = NULL;
	return yenidugum;
}

void kuyrugaEkle(char harf){ 
	
	node *kuyrugaEklenecek = olustur(harf); 
	if (ilk == NULL){ 
		ilk = kuyrugaEklenecek;
		return;
	}
	int kontrol=0; 
	node *current = ilk;
	while(current != NULL){
		if (current->harf == harf){ 
			current->frekans++; 
			kontrol++; 
			return;
		}
		current = current->next;
	}
	if (kontrol == 0){  
		node *temp = ilk;
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = kuyrugaEklenecek;
	}
	else{
		ilk = current;
	}
}

node *insertion_sort(node* ilk)  
{
    node *temp1, *temp2, *temp3;
    temp1 = ilk;
    ilk = NULL;
 
    while(temp1 != NULL)
    {
        temp3 = temp1;
        temp1 = temp1->next;
        if (ilk != NULL)
        {
            if(temp3->frekans > ilk->frekans)
            {
                temp2 = ilk;
                while ((temp2->next != NULL) && (temp3->frekans> temp2->next->frekans))
                {
                    temp2 = temp2->next;
                }
                temp3->next = temp2->next;
                temp2->next = temp3;
            }
            else
            {
                temp3->next = ilk;
                ilk = temp3;
            }
        }
        else
        {
            temp3->next = NULL;
            ilk = temp3;
        }
    }
    return ilk;
}

void huffman(){
	
	int sayici=0;
	node *sayac = ilk;
	while(sayac != NULL){ 
		sayici++; 
		sayac = sayac->next;
	}
	while(sayici!=1){ 
		node *tut = ilk; 
		node *temp = (node*)malloc(sizeof(node));
		temp->frekans = tut->frekans+tut->next->frekans; 
		temp->harf = ' '; 
		temp->left = tut;
		temp->right = tut->next;
		ilk = tut->next->next;


		node *current;
		current = temp; 
		current->next = ilk;
		ilk = current;
		ilk = insertion_sort(ilk);
		
		sayici--; 
	}
}

void yazdir(){ 
	node *temp = ilk;
	while(temp != NULL){
		printf("%d%c  ",temp->frekans,temp->harf);
		temp = temp->next;
	}
}

void yazdir_level(node* tree, int level)
{ 
    if (tree == NULL){
    	return;
	}  
    if (level == 1){
    	printf("%d%c  ",tree->frekans,tree->harf); 
	}
    else if (level > 1) 
    { 
        yazdir_level(tree->left,level-1); 
        yazdir_level(tree->right,level-1); 						   	   
    } 
} 

void paketYazdir(node *ilk, char *prefix, int size_prefix){
	 if (ilk->left == NULL && ilk->right == NULL)
    {
        prefix[size_prefix] = 0;
        for (int i = 0; i < ilk->frekans; i++)
		{
			printf("%s ", prefix);
		}
		
        return;
    }
    if (ilk->left)
    {
        prefix[size_prefix++] = '0';
        paketYazdir(ilk->left, prefix, size_prefix);
        size_prefix--;
    }
    if (ilk->right)
    {
        prefix[size_prefix++] = '1';
        paketYazdir(ilk->right, prefix, size_prefix);
        size_prefix--;
    }
}

void bitYazdir(node *ilk, char *prefix, int size_prefix)
{
    if (ilk->left == NULL && ilk->right == NULL)
    {
        prefix[size_prefix] = 0;
        printf("%c: %s \n", ilk->harf, prefix);
        return;
    }
    if (ilk->left)
    {
        prefix[size_prefix++] = '0';
        bitYazdir(ilk->left, prefix, size_prefix);
        size_prefix--;
    }
    if (ilk->right)
    {
        prefix[size_prefix++] = '1';
        bitYazdir(ilk->right, prefix, size_prefix);
        size_prefix--;
    }
}

int toplamByte(node* ilk,int steps) {
    if (ilk == NULL) {
        return 0;
    }

    if (ilk->left == NULL && ilk->right == NULL) {
        return ilk->frekans*steps;
    }

    return toplamByte(ilk->left,steps+1) + toplamByte(ilk->right,steps+1);
}


int agacYuksekligi(node *tree) 
{ 
    if (tree==NULL){
    	return 0;
	}  
    else{ 
		int left_height = agacYuksekligi(tree->left); 
        int right_height = agacYuksekligi(tree->right);
        
        if (left_height > right_height){ 
        	return (left_height+1);
		} 
        else {
        	return (right_height+1);	
		} 
    } 
} 

int main(){
	char text[200];
	printf("\n Bir yazi giriniz : ");
	gets(text);
	printf("\n");
	int i=0;
	while(text[i] != '\0'){	
		kuyrugaEkle(text[i]); 
		i++;
	}
	yazdir();
	printf("\n\n Siralanmis liste :\n\n");
	ilk = insertion_sort(ilk);
	yazdir();
	
	printf("\n\n Huffman Agaci :\n\n");
	huffman();
	
	int a,b,treeheight;
	treeheight = agacYuksekligi(ilk);
	for (a=1;a<=treeheight;a++){
		yazdir_level(ilk,a);
		printf("\n");
	}	
	
	char *buffer = malloc(256);
	printf("Karakterlere gore bitler :\n");
    bitYazdir(ilk, buffer, 0);

	printf("Paket sekilde yazdirma : \n");
	paketYazdir(ilk, buffer, 0);

    printf("\nHuffman oncesi Byte :%d \n",strlen(text)*8);
    printf("Huffman Sonrasi Byte :%d \n",toplamByte(ilk,0));
    float sk=(1-((float)toplamByte(ilk,0) / (float)(strlen(text)*8)))*100;
    printf("Sikistirma Yuzdesi :%%%.2f",sk);
    
	return 0;
}
	