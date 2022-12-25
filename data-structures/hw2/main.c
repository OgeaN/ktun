#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



typedef struct n{
    char *yazi;
    int sayi;
    struct n * sonraki;
}node;

node *top(node *root){
    node *iter=root;
    while(iter->sonraki!=NULL)
        iter=iter->sonraki;
    return iter;
}
void bastir(node * root){
    root=root->sonraki;
    while(root!=NULL){
        printf("%s : %d \n",root->yazi,root->sayi);
        root=root->sonraki;
    }
}
int stacksayisi(node *root){
    int a=0;
    while(root!=NULL){
        root=root->sonraki;
        a++;
    }
    return a;
}
node * push(node * root,char *yazi,int sayi){
    if(root==NULL){
        root=(node *) malloc(sizeof (node));
        root->yazi= (char *)malloc(sizeof(char)* strlen(yazi)+1 );
        //root->yazi=yazi;
        strcpy(root->yazi, yazi);
        root->sayi=sayi;
        root->sonraki=NULL;
        return root;
    }
    node * iter=root;
    while(iter->sonraki!=NULL)
        iter=iter->sonraki;
    node * temp=(node *) malloc(sizeof (node));
    temp->yazi= (char *)malloc(sizeof(char)* strlen(yazi)+1 );
    //temp->yazi=yazi;
    strcpy(temp->yazi, yazi);
    temp->sayi=sayi;
    temp->sonraki=NULL;
    iter->sonraki=temp;
    return root;
}
node * push2(node * root,char *yazi){
    if(root==NULL){
        root=(node *) malloc(sizeof (node));
        root->yazi=yazi;

        root->sonraki=NULL;
        return root;
    }
    node * iter=root;
    while(iter->sonraki!=NULL)
        iter=iter->sonraki;
    node * temp=(node *) malloc(sizeof (node));
    temp->yazi=yazi;

    temp->sonraki=NULL;
    iter->sonraki=temp;
    return root;
}

node *pop(node *root){
    if(root==NULL){
        printf("boþ");
    }
    node * iter=root;
    if (root!=NULL && iter->sonraki == NULL) {
        root=NULL;


    }
    while (iter->sonraki->sonraki!=NULL)
        iter=iter->sonraki;
    node *temp=iter->sonraki;
    root=temp;
    free(temp);
    iter->sonraki=NULL;
    return root;
}

node * pop2(node **pptr)
{
    node *root = *pptr;
    if (root == NULL) {
        printf("boþ");
    }
    node * iter = root;
    if (root && iter->sonraki == NULL) {
        node *temp=iter;
        free(iter);
        *pptr = NULL;
        return temp;
    }
    while (iter->sonraki->sonraki != NULL)
        iter = iter->sonraki;
    iter->sonraki->sonraki = NULL;
    node *temp = iter->sonraki;
    free(iter->sonraki);
    iter->sonraki = NULL;

}

void bastir2(node *root){
    node * iter=root;
    while(top(iter)!=root){
        printf("%s : %d\n", top(iter)->yazi,top(iter)->sayi);
        pop2(&iter);
    }
}


int main() {
    setlocale(LC_ALL, "Turkish");
    node *s1=NULL;
    node *s2=NULL;
    int j;
    char a[30];
    s1= push(s1," ",0);
    s2= push(s2," ",0);
    printf("Bir string dizisi giriniz : ");
    gets(a);
    //strcpy(a,"Kr4(OnNe(SOne3)2)2");
    for(int i=0;i< strlen(a);){
        if(isupper(a[i])!=0){
            char b[10];
            j=0;

            b[j]=a[i];
            i++;
            j++;
            while((isupper(a[i])==0) && isalpha(a[i])!=0 ){
                b[j]=a[i];

                i++;
                j++;
            }
            char c[30];
            strcpy(c,b);
            s1=push(s1, c,1);
            memset(b, 0, sizeof(b));

        }
        else if(isdigit(a[i])){

            if(stacksayisi(s2)==1){

                node *iter=s1;
                while(iter->sonraki!=NULL)
                    iter=iter->sonraki;
                int b=(int)a[i]-'0';
                int gecicisayi=iter->sayi;
                char *geciciyazi=iter->yazi;
                b=gecicisayi*b;
                pop2(&s1);
                s1=push(s1,geciciyazi,b);

            }
            else if(stacksayisi(s2)!=1){

                while (1 < stacksayisi(s2)) {
                    int b=(int)a[i]-'0';
                    int gecicisayi=top(s2)->sayi;
                    char *geciciyazi=top(s2)->yazi;
                    b=gecicisayi*b;
                    s1=push(s1,geciciyazi,b);
                    pop2(&s2);

                }

            }
            i++;
        }
        else if(a[i]=='('){
            char p='(';
            s1= push(s1,&p,0);
            i++;
        }

        else if(a[i]==')') {
            while(strncmp(top(s1)->yazi,"(",1 )!=0){
                int gecicisayi=top(s1)->sayi;
                char *geciciyazi=top(s1)->yazi;
                s2= push(s2,geciciyazi,gecicisayi);
                pop2(&s1);
            }
            pop2(&s1);

            i++;
        }

    }
    printf("\n");
    bastir2(s1);
    bastir(s2);


    return 0;
}
