#ifndef ARGUMENTOS_H
#define ARGUMENTOS_H

typedef void* Args; 

Args argumentos_cria(int argc, char **argv);

void argumentos_destroi(Args a);

char* argumentos_get_entrada_path(Args a);
char* argumentos_get_geo_file(Args a);
char* argumentos_get_qry_file(Args a);
char* argumentos_get_saida_path(Args a);


#endif