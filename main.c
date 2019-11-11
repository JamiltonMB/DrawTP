#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "funcoes.h"

int main(){
    int x,y;
    pixel **p;
    p=abrir_arquivo("n.ppm");
    
    
    reta r;
    /*printf("Digite o tamanho da imagem:\n");
    scanf("%d",&x);
    scanf("%d",&y);
    p=image(x,y);*/
    printf("Digite o x1/y1:\n");
    scanf("%d",&r.p1.x);
    scanf("%d",&r.p1.y);
    printf("Digite o x2/y2:\n");
    scanf("%d",&r.p2.x);
    scanf("%d",&r.p2.y);
    linha(p,r);
    /*int k[3],l[3];
    k[0]=0;
	l[0]=400;
	
    k[1]=300;
    l[1]=200;
    
    k[2]=600;
    l[2]=400;
    
    polygon(p,3,k,l);
    */save(p);
return 0;
}
