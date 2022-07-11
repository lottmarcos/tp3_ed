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
   void imprime();
   bool vazio();

   int id_msg;
   int id_dest;
   string texto;
   string output_file;
};

// TAD BINTREE
class tipo_no
{
public:
   tipo_no();
   email e;
   tipo_no *esq;
   tipo_no *dir;
   friend class bintree;
};
class bintree
{
public:
   bintree();
   ~bintree();
   void insere(email e);
   void caminha(int tipo);
   void limpa();
   email pesquisa(email e);
   void remove(email e);

   void insere_recursivo(tipo_no *&p, email e);
   void apaga_recursivo(tipo_no *p);
   email pesquisa_recursivo(tipo_no *p, email e);
   void remove_recursivo(tipo_no *&p, email e);
   void antecessor(tipo_no *q, tipo_no *&r);
   tipo_no *raiz;
};

// TAD HASH
class hashtable
{
public:
   hashtable(int M);
   email pesquisa(email e, int M, int Tipo);
   void insere(email e, int M);
   void remove(email e, int M);

   int hash_id(email e, int M);
   bintree *table;
};

// FUNÇÕES GLOBAIS
void entregar_email(hashtable *server, email e, int U, string texto, int M, int E);
void consultar_email(hashtable *server, email e, int U, int M, int E);
void apagar_email(hashtable *server, email e, int U, int M, int E);
void parse_args(int argc, char **argv);
void uso();
int count_words(string str);

#endif