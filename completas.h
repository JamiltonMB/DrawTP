#ifndef COMPLETAS_H
#define COMPLETAS_H

void color(pixel p,unsigned short r, unsigned short g,unsigned short b){
    p.red=r;
    p.green=g;
    p.blue=b;
}

void linha(pixel **p,reta r){ //https://gist.github.com/mfilipelino/11240714#file-paintopengl-c
    int dy = (r.p2.y - r.p1.y); //Diferença entre os pontos y2 e y1
    int dx = (r.p2.x - r.p1.x); //Diferença entre os pontos x2 e x1
    int sx,sy; //Variaveis que serão utilizadas para armazenar o sinal de x e y afim de saber o quadrante do segmento
    int i=r.p1.y;
    int j=r.p1.x;
    if(r.p1.x<r.p2.x) //Determinar os sinais de x e y
    {
        sx=1;
    }
    else
    {
        sx=-1;
    }

    if(r.p1.y<r.p2.y)
    {
        sy=1;
    }
    else
    {
        sy=-1;
    }                  //fim da determinação de sinais
    
    int erro;
    int erroTemp;
    if(dx>dy) // Definição do erro inicial baseado na maior diferença
    {
        erro=dx/2;
    }
    else
    {
        erro=(-dy)/2;
    }
    
    while(true)
	{
	    color(p[i][j],255,255,255);
        if((i==r.p2.y)&&(j==r.p2.x)) // Testa se chegou ao ponto final e encerra o algoritimo
        {
            break;
        }

        erroTemp=erro;

        if(erroTemp > -dx)
        {
            erro -= dy;
            j += sx;
        }
        
        if(erroTemp < dy)
        {
            erro += dx;
            i += sy;
        }
	}
}


#endif
