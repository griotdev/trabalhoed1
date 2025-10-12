#ifndef ARGUMENTOS_H
#define ARGUMENTOS_H


/* API pública do módulo de argumentos. As structs concretas ficam no .c. */


typedef void* Args; /* opaco: na implementação usamos struct concreta */


/* Cria e processa os argumentos da linha de comando. Retorna NULL em erro. */
Args argumentos_cria(int argc, char **argv);


/* Destrói. */
void argumentos_destroi(Args a);


/* Para conveniência, queremos alguns acessores: (ex.: args->entrada_path) */
/* Você pode fornecer funções accessor ou (se preferir) expor uma struct castable.
Exemplo de funções: */


char* argumentos_get_entrada_path(Args a);
char* argumentos_get_geo_file(Args a);
char* argumentos_get_qry_file(Args a);
char* argumentos_get_saida_path(Args a);


#endif