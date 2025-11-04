#ifndef VALIDACOES_H
#define VALIDACOES_H

int validar_nome(char *nome);
int validar_cpf(char *cpf);
int validar_celular(char *celular);
int validar_email(char *email);
int validar_salario_string(char *salario);
int validar_id_fantasia(const char *obs);
int validar_tamanho_fantasia(char *tamanho);
int validar_cor_fantasia(char *cor);
int validar_preco(float preco);
int valida_data(char *data);
int validar_texto_geral(char *texto, int max_tamanho);
int validar_data(char *data);
int validar_id_numerico_string(char *id);


#endif