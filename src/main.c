#include <stdio.h>
#include <stdlib.h>
#include "../lib/arquivos/argumentos/argumentos.h"
#include "../lib/parser.h"
#include "jogo.h"


int main(int argc, char *argv[]){
Args *args = argumentos_cria(argc, argv);
if(!args){
fprintf(stderr, "Erro ao processar argumentos\n");
return 1;
}


// Inicializa estruturas do jogo
Jogo *j = jogo_cria();


// processa o argumentos contendo informação sobre o arquivo .geo
if(args->geo_file){
if(!parser_processa_geo(j, args->entrada_path, args->geo_file)){
fprintf(stderr, "Erro no parser .geo\n");
}
}


// se houver .qry, processa-os
if(args->qry_file){
if(!parser_processa_qry(j, args->entrada_path, args->qry_file, args->saida_path)){
fprintf(stderr, "Erro no parser .qry\n");
}
}


// finaliza e grava saídas
jogo_destroi(j);
argumentos_destroi(args);
return 0;
}