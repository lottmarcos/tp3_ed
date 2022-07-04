#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <getopt.h>
#include <cmath>

using namespace std;

// FUNÇÕES GLOBAIS
void parse_args(int argc, char **argv);
void uso();
int count_words(string str);