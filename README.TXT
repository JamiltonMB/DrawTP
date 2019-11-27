NOME DO PROJETO(SOFTWARE): DrawTP
link: https://github.com/JamiltonMB/DrawTP

1 - DESCRIÇÃO: DrawTP é um programa de desenho gráfico, onde as imagens são representadas por pixels, ou seja, representação ponto-a-ponto da imagem. O software gera e manipula imagens no formato PPM, usando o padrão RGB, onde cada componente do pixel pode receber um valor máximo de 255. As chamadas das funções são realizadas através do arquivo de especificação, que trata-se de um arquivo.txt onde são informadas as primitvas gráticas com seus respectivos valores. Abaixo podemos ver como cada informação deve ser colocada no arquivo .txt:

imagem: gera uma imagem com tamanho definido pelo usuário, deve ser apresentada da seguinte forma: image x y, onde x e y são números inteiros que armazenam a largura e altura da imagem;

color: define a cor que será usada, deve ser apresentada da seguinte forma: color x y z, onde x, y, z são números inteiros com valores máximo igual a 255;

clear: Limpa a imagem, setando todos os pixels para a cor especificada, deve ser apresentada da seguinte forma: clear x y z, onde x, y, z são números inteiros com valores máximo igual a 255;

rect: desenha um retângulo, deve ser apresentada da seguinte forma: rect x y A L, onde x e y são números inteiros que armazena a posição do pixel do canto superior esquerdo do retângulo e A e L são a aultura e largura respectivamente;

circle: desenha um círculo, é implementado da seguinte forma: circle x y z, onde x e y são números inteiros que armazena a posição do centro do cículo e z é um inteiro que armazena o tamanho do raio;

polygon: desnha um polígono, é implementado da seguinte forma: polygon n x[n] y[n]. O inteiro n armazena o número de linhas do polígono e os vetiros de inteiros x[n] e y[n] armazenam os pontos de cada linha informada;

fill: pinta uma área da figura, não ultrapassando áreas fechadas, ou seja, quando chamada dentro de um cículo por exemplo, ela irá pintar todo o interior do cícrulo. É implementada da seguinte forma: fill x y. O inteiros x e y armazem a posição do pixel que será pintado;

save: salva a imagem em um arquivo, deve ser usada da seguine forma: save nome_arquivo.ppm;

O DrawTP usa uma API gráfica de interface com o usuário, para isso foi usada a biblioteca GTK. Na interface o usuário pode gerar e salvar o arquivo de especificação e visualiar a imagem, para esse processo são usados três botões:

LER: O usuário deve preencher o campo ao lado do botão com o nome do arquivo de especificação, ao clicar em ler toda informação do arquivo será exibida no campo de edicação de textos, onde o usuário poderá fazer alterações;

SALVAR: O usuário pode usar esse botão para duas atividades: 1 - Salvar alterações do arquivo.txt lido através do botão ler, 2 - Criar um novo arquivo que vai salvar as informações inseridas no campo de edição de texto em um arquivo.txt com o nome inserido no campo de leitura de arquuvo que ficao ao lado do botão ler;

ATUALIZAR: Ler o nome do arquivo .ppm, que foi inserido no arquivo de espeficição informado no campo que recebe o nome do arquivo, após a leitura a imagem será exibida em um frame no canto esquerdo da janela do programa.

2 - LIMITAÇÕES: O DrawTP não mostra as alterações realizadas na imagem em tempo real, pois não usada nenhuma API gráfica de desenho. O usuário não pode usar o nome "aux.txt" para o arquivo de especificação, pois ele é reservado para uso do programa.

3 - FUTURAS MODIFICAÇÕES: Melhorar a interativdade com o usário através da implementaçaõ de APIs de desenho gráfico.

4 - COMPILAÇÃO: Para compilar os arquivos deve-se informar o seguinte comando no terminal: gcc `pkg-config --cflags gtk+-3.0` -o run main.c funcoes.c `pkg-config --libs gtk+-3.0`

Foi usada a biblioteca GTK na versão GTK+3.

5 - EQUIPE DE DESENVOLVIMENTO:

Jamilton Medeiros Barbosa
Fernando Breno dos Santos Barbosa

Contribuição individual:

Jamilton Medeiros Barbosa - Primeira versão do programa com a função image e alocação dinâmica de memória, funções de leitura do arquivo de especificação, função de desenho de retângulos, desenvolvimento da interface gráfica com o GTK;

Fernando Breno dos Santos Barbosa - Segunda versão do programa com a nova função image, funções de desenho de: retas, círculos e polígonos, função fill, modularização do programa, organização do código, uso do valgrind.
