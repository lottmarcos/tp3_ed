#include <iostream>
#include <cstring>
#include "TP3.h"

using namespace std;

// variaveis globais para as opções
char *name_input = NULL, *name_output = NULL;

// verifica passagem de argumentos
void parse_args(int argc, char **argv)
{
   // variaveis externas do getopt
   extern char *optarg;

   // variavel auxiliar
   int c;

   // getopt - letra indica a opcao, : junto a letra indica parametro
   // no caso de escolher mais de uma operacao, vale a ultima
   while ((c = getopt(argc, argv, "i:I:o:O:h")) != EOF)
   {
      switch (c)
      {
      case 'i':
         name_input = optarg;
         break;
      case 'I':
         name_input = optarg;
         break;
      case 'o':
         name_output = optarg;
         break;
      case 'O':
         name_output = optarg;
         break;
      case 'h':
      default:
         uso();
      }
   }
}

int main(int argc, char **argv)
{
   // avalia linha de comando
   parse_args(argc, argv);

   // verificacao da consistencia das opcoes
   if (argc == 1)
   {
      cout << "ERROR:\n\tnecessario escrever os nomes dos arquivos de entrada e saida" << endl;
      return 0;
   }

   // verifica abertura dos arquivos
   ifstream input_file(name_input);
   ofstream output_file(name_output, ios::trunc);
   if (!input_file.is_open())
   {
      cout << "ERROR:\n\tarquivo de entrada não encontrado" << endl;
      return 0;
   }

   // ----------------- INICIO DO PROGRAMA ----------------- //

      return 0;
}