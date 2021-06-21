#include <regex>
#include <math.h>
#include <string>
#include <vector>
#include <sstream>

#include "LineProcessor.hpp"

void LinePrinter::processaLinha(const std::string &str) {
  std::cout << str << std::endl;
}

bool ContadorPopRural::linhaValida(const std::string &str) const {
  // Neste exemplo usaremos expressoes regulares para verificar se uma linha
  // eh valida ou nao.
  //
  // Esta expressao regular eh formada por cinco partes. Cada uma dessas
  // partes eh um dos tres tipos de padrao regular abaixo:
  //
  // \\w+ eh qualquer palavra com um ou mais digitos, letras e sublinhas (_)
  // \\s* eh qualquer sequencia de zero ou mais espacos (inclui tab)
  // \\d+ eh qualquer sequencia de um ou mais digitos
  std::regex regularExpr("\\w+\\s*\\d+\\s*\\d+");

  // A funcao regex_match vai retornar verdadeiro se a string str casa-se com
  // a expressao regular que acabamos de criar:
  return std::regex_match(str, regularExpr);
}

void ContadorPopRural::processaLinha(const std::string &str) {
  //
  // Em geral eh mais facil ler dados de uma string se a string eh transformada
  // em um objeto do tipo stringstream:
  std::stringstream ss(str);
  //
  // Iremos ler os dados da string nestas tres variaveis abaixo:
  std::string nomePais;
  unsigned populacao, percUrbana;
  //
  // Como sabemos que a linha contem string int int, podemos fazer a leitura
  // facilmente usando o operador de streaming:
  ss >> nomePais >> populacao >> percUrbana;
  //
  // Note que precisamos arredondar o valor que serah impresso. O arredondamento
  // serah feito via a funcao floor. Ou seja, decimais serao sempre
  // arredondados para baixo:
  unsigned popRural = floor(populacao - (populacao * (percUrbana/100.0)));
  //
  // Uma vez encontrados os valores que precisam ser impressos, seguimos o
  // modelo do enunciado do exercicio:
  std::cout << popRural << " pessoas vivem no campo no " << nomePais << std::endl;
}

bool ContadorNumNaturais::linhaValida(const std::string &str) const {
    for (char c: str) {
        if (!std::isdigit(c) && !std::isspace(c)) 
            return false;
    }
  return true;
}

void ContadorNumNaturais::processaLinha(const std::string &str) {
    std::stringstream ss(str);
    unsigned num = 0, soma = 0;

    while(!ss.eof()){
        ss >> num;
        soma += num;
    }
    std::cout << soma << std::endl;
}

bool LeitorDeFutebol::linhaValida(const std::string &str) const {
  std::regex regularExpr("\\s*[a-zA-Z]+\\s*\\d+\\s*[a-zA-Z]+\\s*\\d+");
  return std::regex_match(str, regularExpr);
}

void LeitorDeFutebol::processaLinha(const std::string &str) {
  std::stringstream ss(str);
  std::string time1, time2;
  unsigned gols1, gols2;

    ss >> time1 >> gols1 >> time2 >> gols2;
    if(gols1 > gols2)
        std::cout << "Vencedor: " << time1 << std::endl;
    else if(gols1 < gols2) 
        std::cout << "Vencedor: "<< time2 << std::endl;
    else
        std::cout << "Empate" << std::endl;
}

void ContadorDePalavras::processaLinha(const std::string &str) {
    std::cout<< contaPalavras(str) << std::endl;
}

unsigned ContadorDePalavras::contaPalavras(const std::string &str){
    std::stringstream stream(str);
    std::string aux;
    unsigned count = 0;
    while(stream >> aux) {
        count += 1;
    }
    return count;
}

bool InversorDeFrases::linhaValida(const std::string &str) const {
    std::regex regPalavra("[a-zA-Z]+");
    std::regex regEspaco("\\s*");
    std::string s;

    for (char c: str) {
        s = c;
        if (!std::regex_match(s, regPalavra) && !std::regex_match(s, regEspaco))
            return false;
    }
    return true;
}

void InversorDeFrases::processaLinha(const std::string &str) {
    std::regex regularExpr("[a-zA-Z]+");
    std::string aux;
    std::stringstream ss(str);
    std::vector<std::string> frase;
    std::vector<std::string>::iterator p;

    while(!ss.eof()){
        ss >> aux;
        frase.push_back(aux);
    }

    reverse(frase.begin(), frase.end());
    for (p = frase.begin(); p < frase.end(); p++) {
        std::cout << *p << " ";
    }

    std::cout << std::endl;
}

bool EscritorDeDatas::linhaValida(const std::string &str) const {
    std::string dateFormat = "\\s*\\d\\d?/\\d\\d?/\\d{4}";
    std::regex regularExpr(dateFormat);
    return std::regex_match(str, regularExpr);
}

void EscritorDeDatas::processaLinha(const std::string &str) {
    std::vector<std::string> meses {"Jan", "Fev", "Mar", "Abr", "Mai", "Jun", "Jul", "Ago", "Set", "Out", "Nov", "Dez"};
    std::vector<std::string> dados;
    std::stringstream ss(str);
    std::regex regMes("(/\\d\\d?/)");
    std::smatch match;
    std::string s; 
    int mes; 

    while(!ss.eof()){
        ss >> s;
        if(std::regex_search(s, match, regMes)){
            std::string aux = match[0];
            for(char c: aux){
                if(std::isdigit(c)){
                    int mes = c - '0';
                    if(mes != 0){
                        std::cout<<meses[mes-1]<<std::endl;
                    }
                }
            }    
        }
    }  
}