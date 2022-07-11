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

   // inicia registro de acesso
   string lognome = "memlog.out";
   int n = lognome.length();
   char char_array[n + 1];
   strcpy(char_array, lognome.c_str());
   iniciaMemLog(&char_array[0]);
   ativaMemLog();

   // ----------------- INICIO DO PROGRAMA ----------------- //
   // variáveis iniciais e auxiliares
   string CONSULTA = "CONSULTA", APAGA = "APAGA", ENTREGA = "ENTREGA";
   string aux;
   int M = 0, U = 0, E = 0, N = 0;

   // consegue o tamanho da tabela hash
   input_file >> M;

   // criação das estruturas de dados utilizadas
   hashtable *servidor = new hashtable(M);
   email mensagem;
   mensagem.output_file = name_output;

   // loop principal para a execução do programa
   while (input_file >> aux)
   {
      // realiza a função ENTREGAR
      if (aux == ENTREGA)
      {
         defineFaseMemLog(0); // define fase memlog para função ENTREGAR
         string MSG;
         string palavra;
         input_file >> U >> E >> N;

         for (int i = 0; i < N; i++)
         {
            input_file >> palavra;
            MSG += palavra;
            if (i + 1 < N)
            {
               MSG += " ";
            }
         }
         entregar_email(servidor, mensagem, U, MSG, M, E);
      }
      // realiza a função CONSULTAR
      else if (aux == CONSULTA)
      {
         defineFaseMemLog(1); // define fase memlog para função CONSULTAR
         input_file >> U >> E;
         consultar_email(servidor, mensagem, U, M, E);
      }
      // realiza a função APAGAR
      else if (aux == APAGA)
      {
         defineFaseMemLog(2); // define fase memlog para função APAGAR
         input_file >> U >> E;
         apagar_email(servidor, mensagem, U, M, E);
      }
   }

   output_file.close();
   return finalizaMemLog();
}
