#include "TP3.h"

using namespace std;

// TAD EMAIL
email::email()
{
   id_msg = -1;
   texto = " ";
   id_dest = -1;
}
void email::set_email(string _texto)
{
   int x = _texto.length();
   _texto.erase(x - 1);

   texto = _texto;
}

// TAD BINTREE
tipo_no::tipo_no()
{
   esq = NULL;
   dir = NULL;
}
bintree::bintree()
{
   raiz = NULL;
}
bintree::~bintree()
{
   limpa();
}
void bintree::insere(email mensagem)
{
   insere_recursivo(raiz, mensagem);
}
void bintree::insere_recursivo(tipo_no *&p, email mensagem)
{
   if (p == NULL)
   {
      p = new tipo_no();
      p->mensagem = mensagem;
   }
   else
   {
      if (mensagem.id_msg < p->mensagem.id_msg)
         insere_recursivo(p->esq, mensagem);
      else
         insere_recursivo(p->dir, mensagem);
   }
}
void bintree::limpa()
{
   apaga_recursivo(raiz);
   raiz = NULL;
}
email bintree::pesquisa(email mensagem)
{
   return pesquisa_recursivo(raiz, mensagem);
}
email bintree::pesquisa_recursivo(tipo_no *no, email mensagem)
{
   email aux;
   if (no == NULL)
   {
      aux.id_msg = -1;
      return aux;
   }
   if (mensagem.id_msg < no->mensagem.id_msg)
      return pesquisa_recursivo(no->esq, mensagem);
   else if (mensagem.id_msg > no->mensagem.id_msg)
      return pesquisa_recursivo(no->dir, mensagem);
   else
      return no->mensagem;
}
void bintree::remove(email mensagem)
{
   return remove_recursivo(raiz, mensagem);
}
void bintree::remove_recursivo(tipo_no *&no, email mensagem)
{
   tipo_no *aux;

   ofstream saida(no->mensagem.output_file, ios::app);

   if (no == NULL)
   {
      saida << "ERRO: MENSAGEM INEXISTENTE" << endl;
   }
   if (mensagem.id_msg < no->mensagem.id_msg)
      return remove_recursivo(no->esq, mensagem);
   else if (mensagem.id_msg > no->mensagem.id_msg)
      return remove_recursivo(no->dir, mensagem);
   else
   {
      if (no->dir == NULL)
      {
         aux = no;
         no = no->esq;
         free(aux);
      }
      else if (no->esq == NULL)
      {
         aux = no;
         no = no->dir;
         free(aux);
      }
      else
         antecessor(no, no->esq);

      saida << "OK: MENSAGEM APAGADA" << endl;
      saida.close();
   }
}
void bintree::apaga_recursivo(tipo_no *p)
{
   if (p != NULL)
   {
      apaga_recursivo(p->esq);
      apaga_recursivo(p->dir);
      delete p;
   }
}
void bintree::antecessor(tipo_no *q, tipo_no *&r)
{
   if (r->dir != NULL)
   {
      antecessor(q, r->dir);
      return;
   }
   q->mensagem = r->mensagem;
   q = r;
   r = r->esq;
   free(q);
}

// TAD HASH
hashtable::hashtable(int M)
{
   this->table = new bintree[M];
}
int hashtable::hash_id(email mensagem, int M)
{
   int aux = (mensagem.id_dest % M);
   return aux;
}
email hashtable::pesquisa(email mensagem, int M, int Tipo)
{
   int pos;
   email texto_aux;
   pos = hash_id(mensagem, M);
   texto_aux = table[pos].pesquisa(mensagem);

   ofstream saida(mensagem.output_file, ios::app);

   if (Tipo == 1)
   {
      if (texto_aux.id_msg == -1 || texto_aux.id_dest != mensagem.id_dest)
      {
         saida << "CONSULTA " << mensagem.id_dest << " " << mensagem.id_msg << ": MENSAGEM INEXISTENTE" << endl;
      }
      else
      {
         saida << "CONSULTA " << texto_aux.id_dest << " " << texto_aux.id_msg << ": " << texto_aux.texto << endl;
      }
   }
   saida.close();
   return mensagem;
}
void hashtable::insere(email mensagem, int M)
{
   email aux;
   int pos;
   ofstream saida(mensagem.output_file, ios::app);

   aux = pesquisa(mensagem, M, 0);
   pos = hash_id(mensagem, M);
   table[pos].insere(mensagem);

   saida << "OK: MENSAGEM " << mensagem.id_msg << " PARA " << mensagem.id_dest << " ARMAZENADA EM " << pos << endl;

   saida.close();
}
void hashtable::remove(email mensagem, int M)
{
   int pos;
   email texto_aux;
   ofstream saida(mensagem.output_file, ios::app);
   pos = hash_id(mensagem, M);
   texto_aux = table[pos].pesquisa(mensagem);

   if (texto_aux.id_msg == -1)
   {
      saida << "ERRO: MENSAGEM INEXISTENTE" << endl;
   }
   else
      table[pos].remove(mensagem);
   saida.close();
}

// FUNÇÕES GLOBAIS
void entregar_email(hashtable *servidor, email mensagem, int U, string _texto, int M, int E)
{
   mensagem.id_msg = E;
   mensagem.id_dest = U;
   mensagem.texto = _texto;

   ESCREVEMEMLOG((long int)(&mensagem), (long int)sizeof(int), 0);

   servidor->insere(mensagem, M);
}
void consultar_email(hashtable *servidor, email mensagem, int U, int M, int E)
{
   email resposta;
   mensagem.id_msg = E;
   mensagem.id_dest = U;

   ESCREVEMEMLOG((long int)(&mensagem), (long int)sizeof(int), 1);

   resposta = servidor->pesquisa(mensagem, M, 1);
}
void apagar_email(hashtable *servidor, email mensagem, int U, int M, int E)
{
   mensagem.id_msg = E;
   mensagem.id_dest = U;

   ESCREVEMEMLOG((long int)(&mensagem), (long int)sizeof(int), 2);

   servidor->remove(mensagem, M);
}

void uso()
{
   // -[o|O] : endereço do arquivo de saída
   // -[i|I] : arquivo de entrada

   cout << "\n-- OPÇÕES DE USO --\n";
   cout << "\t-[i|I] : arquivo de entrada" << endl;
   cout << "\t-[o|O] : endereço do arquivo de saída" << endl;
   cout << endl;
}
int count_words(string str)
{
   stringstream s(str);
   string word;

   int count = 0;
   while (s >> word)
      count++;
   return count;
}