gcc `pkg-config --cflags gtk+-3.0` -o run main.c funcoes.c -Wall -Werror -g -std=c99 `pkg-config --libs gtk+-3.0`
if [ $? -eq 0 ];then 
   echo "compilado com sucesso!"
    ./run
else
    echo "nao compilado"
fi
