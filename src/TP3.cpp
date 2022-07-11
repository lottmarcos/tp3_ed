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
void bintree::insere(email e)
{
   insere_recursivo(raiz, e);
}
void bintree::insere_recursivo(tipo_no *&p, email e)
{
   if (p == NULL)
   {
      p = new tipo_no();
      p->e = e;
   }
   else
   {
      if (e.id_msg < p->e.id_msg)
         insere_recursivo(p->esq, e);
      else
         insere_recursivo(p->dir, e);
   }
}
void bintree::limpa()
{
   apaga_recursivo(raiz);
   raiz = NULL;
}
email bintree::pesquisa(email e)
{
   return pesquisa_recursivo(raiz, e);
}
email bintree::pesquisa_recursivo(tipo_no *no, email e)
{
   email aux;
   if (no == NULL)
   {
      aux.id_msg = -1;
      return aux;
   }
   if (e.id_msg < no->e.id_msg)
      return pesquisa_recursivo(no->esq, e);
   else if (e.id_msg > no->e.id_msg)
      return pesquisa_recursivo(no->dir, e);
   else
      return no->e;
}
void bintree::remove(email e)
{
   return remove_recursivo(raiz, e);
}
void bintree::remove_recursivo(tipo_no *&no, email e)
{
   tipo_no *aux;

   ofstream saida(no->e.output_file, ios::app);

   if (no == NULL)
   {
      saida << "ERRO: MENSAGEM INEXISTENTE" << endl;
   }
   if (e.id_msg < no->e.id_msg)
      return remove_recursivo(no->esq, e);
   else if (e.id_msg > no->e.id_msg)
      return remove_recursivo(no->dir, e);
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
   q->e = r->e;
   q = r;
   r = r->esq;
   free(q);
}

// TAD HASH
hashtable::hashtable(int M)
{
   this->table = new bintree[M];
}
int hashtable::hash_id(email e, int M)
{
   int aux = (e.id_msg % M);
   return aux;
}
email hashtable::pesquisa(email e, int M, int Tipo)
{
   int pos;
   email texto_aux;
   pos = hash_id(e, M);
   texto_aux = table[pos].pesquisa(e);

   ofstream saida(e.output_file, ios::app);

   if (Tipo == 1)
   {
      if (texto_aux.id_msg == -1 || texto_aux.id_dest != e.id_dest)
      {
         saida << "CONSULTA " << e.id_dest << " " << e.id_msg << ": MENSAGEM INEXISTENTE" << endl;
      }
      else
      {
         saida << "CONSULTA " << texto_aux.id_dest << " " << texto_aux.id_msg << ": " << texto_aux.texto << endl;
      }
   }
   saida.close();
   return e;
}
void hashtable::insere(email e, int M)
{
   email aux;
   int pos;
   ofstream saida(e.output_file, ios::app);

   aux = pesquisa(e, M, 0);
   pos = hash_id(e, M);
   table[pos].insere(e);

   saida << "OK: MENSAGEM " << e.id_msg << " PARA " << e.id_dest << " ARMAZENADA EM " << pos << endl;

   saida.close();
}
void hashtable::remove(email e, int M)
{
   int pos;
   email texto_aux;
   ofstream saida(e.output_file, ios::app);
   pos = hash_id(e, M);
   texto_aux = table[pos].pesquisa(e);

   if (texto_aux.id_msg == -1)
   {
      saida << "ERRO: MENSAGEM INEXISTENTE" << endl;
   }
   else
      table[pos].remove(e);
   saida.close();
}

// FUNÇÕES GLOBAIS
void entregar_email(hashtable *server, email e, int U, string _texto, int M, int E)
{
   e.id_msg = E;
   e.texto = _texto;
   e.id_dest = U;

   ESCREVEMEMLOG((long int)(&e), (long int)sizeof(int), 0);

   server->insere(e, M);
}
void consultar_email(hashtable *server, email e, int U, int M, int E)
{
   email resposta;
   e.id_msg = E;
   e.id_dest = U;

   ESCREVEMEMLOG((long int)(&e), (long int)sizeof(int), 1);

   resposta = server->pesquisa(e, M, 1);
}
void apagar_email(hashtable *server, email e, int U, int M, int E)
{
   e.id_msg = E;
   e.id_dest = U;

   ESCREVEMEMLOG((long int)(&e), (long int)sizeof(int), 2);

   server->remove(e, M);
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