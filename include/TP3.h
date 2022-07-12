#ifndef TP3
#define TP3

#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <getopt.h>
#include <cmath>
#include "memlog.h"
#include "msgassert.h"

using namespace std;

// TAD EMAIL
class email
{
public:
   email();
   void set_email(string _texto);

   int id_msg;
   int id_dest;
   string texto;
};

// TAD BINTREE
class tipo_no
{
public:
   tipo_no();
   email mensagem;
   tipo_no *esq;
   tipo_no *dir;
   friend class bintree;
};
class bintree
{
public:
   bintree();
   ~bintree();
   void insere(email mensagem, int memlog);
   void caminha(int tipo);
   void limpa();
   email pesquisa(email mensagem, int memlog);
   void remove(email mensagem, int memlog);

   void insere_recursivo(tipo_no *&p, email mensagem, int memlog);
   void apaga_recursivo(tipo_no *p);
   email pesquisa_recursivo(tipo_no *p, email mensagem, int memlog);
   void remove_recursivo(tipo_no *&p, email mensagem, int memlog);
   void antecessor(tipo_no *q, tipo_no *&r);
   tipo_no *raiz;
};

// TAD HASH
class hashtable
{
public:
   hashtable(int M);
   email pesquisa(email mensagem, int M, int Tipo, int memlog);
   void insere(email mensagem, int M, int memlog);
   void remove(email mensagem, int M, int memlog);

   int hash_id(email mensagem, int M);
   bintree *table;
};

// FUNÇÕES GLOBAIS
void entregar_email(hashtable *servidor, email mensagem, int U, string texto, int M, int E);
void consultar_email(hashtable *servidor, email mensagem, int U, int M, int E);
void apagar_email(hashtable *servidor, email mensagem, int U, int M, int E);

void set_output(string filename);
void parse_args(int argc, char **argv);
void uso();

#endif