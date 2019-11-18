#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "funcoes.h"

int main(){
    int x,y;
    pixel **p;
    //p=abrir_arquivo("n.ppm"); 
    reta r;
    printf("Digite o tamanho da imagem:\n");
    scanf("%d",&x);
    scanf("%d",&y);
    p=image(x,y);
    
    printf("Digite o ponto do centro do circulo e seu raio:\n");
    ponto c;
    int raio;
    scanf("%d",&c.x);
    scanf("%d",&c.y);
    scanf("%d",&raio);
    circulo(p,c,raio);
    pixel colorido;
    colorido.red=0;
    colorido.green=0;
    colorido.blue=255;
    pixel borda;
    borda.red=0;
    borda.green=0;
    borda.blue=0;
    fill(p,c.x,c.y,colorido,borda);
    react(p,50,50,100,100);
    fill(p,51,51,colorido,borda);

/*    
    printf("Digite o x1/y1:\n");
    scanf("%d",&r.p1.x);
    scanf("%d",&r.p1.y);
    printf("Digite o x2/y2:\n");
    scanf("%d",&r.p2.x);
    scanf("%d",&r.p2.y);
    linha(p,r);
	int x1=99, y2=99, A=800, L=800; //Teste da função que desenha retângulos
	react(p, x1, y2, A, L);
 */   

    save(p);
return 0;
}
