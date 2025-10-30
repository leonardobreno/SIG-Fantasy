#include "validacoes.h"

int validar_cpf(char *cpf){
    int i;
    int tamanho = strlen(cpf);

    if(tamanho != 11){
        return 0;
    }

    for(i = 0; i < tamanho; i++){
      if(!isdigit(cpf[i])){
          return 0;
      }
    }
    return 1;
}

int validar_id_fantasia(const char *obs) {
    setlocale(LC_CTYPE, "");

    int tamanho = strlen(obs);
    
    if (tamanho < 1) { 
        return 0;
    }

    for (int i = 0; i < tamanho; i++) {
        unsigned char c = obs[i];
        if (isalpha(c) || isdigit(c) || c == ' ' || c == '%' ||
            strchr(".,!?;:-_()[]{}\"'@#$/\\+=*&°ºª|~^´`áàâãäéèêëíìîïóòôõöúùûüçÁÀÂÃÄÉÈÊËÍÌÎÏÓÒÔÕÖÚÙÛÜÇ", c)) {
            continue;
        }
        
        return 0;
    }
    
    return 1;
}

int validar_preco(float preco) {
    
    if(preco <= 0) {
        return 0;
    }
    
    else if(preco > 99999.99){
        return 0;
    }

    return 1;
}

int ano_bissexto(int ano){
  if(ano % 400 == 0){
    return 1;
  } else if((ano % 4 == 0) && (ano % 100 != 0)){
    return 1;
  } else{
    return 0;
  }
}

int valida_dia(int dia, int mes, int ano){
  if((dia < 1) || (mes < 1) || (mes > 12)){
    return 0;
  }
  int max_dias;
  if ((mes == 4) || (mes == 6) || (mes == 9) || (mes == 11)){
    max_dias = 30;
  } else if (mes == 2){
      if(ano_bissexto(ano)){
        max_dias = 29;
      } else{
        max_dias = 28;
      }
  } else{
    max_dias = 31;
  }
  if(dia > max_dias){
    return 0;
  }
  return 1;
}

int ano_atual() {
    time_t segundos_atuais = time(NULL);
    struct tm *data_atual = localtime(&segundos_atuais);
    return data_atual->tm_year + 1900;
}

int valida_ano(int ano){
  int atual = ano_atual();

  if((ano == atual) || (ano == atual + 1)){
    return 1;
  } else{
    return 0;
  }
}

int valida_data(char *data){
    int len, dia, mes, ano;
  len = strlen(data);
  
  if(len != 8){
    return 0;
  }
  
  for (int i = 0; i < len; i++){
    if (!isdigit(data[i])) {
      return 0;
    }
  }
  
  dia = (data[0] - '0') * 10 + (data[1] - '0');
  mes = (data[2] - '0') * 10 + (data[3] - '0');
  ano = (data[4] - '0') * 1000 + (data[5] - '0') * 100 + 
        (data[6] - '0') * 10 + (data[7] - '0');

  if (!valida_dia(dia, mes, ano)){
    return 0;
  }
  
  if(!valida_ano(ano)){
    return 0;
  }

  time_t segundos_atuais = time(NULL);
  struct tm *data_atual = localtime(&segundos_atuais); 
  int dia_atual = data_atual->tm_mday;
  int mes_atual = data_atual->tm_mon + 1; 
  int ano_atual_val = data_atual->tm_year + 1900; 

  if(ano == ano_atual_val){
    if(mes < mes_atual){
      return 0; 
    } else if((mes == mes_atual) && (dia < dia_atual)){
      return 0; 
    }
  }
  
  return 1; 
}