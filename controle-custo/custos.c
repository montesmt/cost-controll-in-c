/*
   MÓDULO PRINCIPAL
*/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <locale.h>
#include <windows.h>
/* #include <conio.h>  */
#include <c:\faculdade\algoritmos\vt controle de custos\conio21\conio.c>
#include <time.h>
/* ---------------------------------
   Declarações das constantes
   ---------------------------------- */
#define _TAMANHO 100          /* quantidade máxima de caracteres de cada linha de texto dos Menus  */
#define _TAMANHO_NOME  15     /* nomes das tabelas  */
#define _TAMANHO_QUERY 1024   /* tamanho do texto das queries, das instruções SQL  */
/* ----------------------------------
   Declarações de variáveis globais
   ---------------------------------- */
char _caixa_erro[] = "Opção Inválida!";
char _caixa_titulo[] = "Controle de Custos";
char _dateStr[11];    /* define a data do Sistema - biblioteca time.h - 10 posições, porém definimos com 11 para limpar sujo no final */
char _timeStr[6];     /* define a hora do Sistema - biblioteca time.h - 5 posições, porém definimos com 6 para limpar sujo no final */
char _empresa[50]  = "E-SIM (Empresa Sistemas de Informação Modelo)";
char _programa[30] = "Aplicativo Controle de Custos";
/* ----------------------------------
   Fontes do Programa
   ---------------------------------- */
#include <c:\faculdade\algoritmos\vt controle de custos\funcoes.c>
#include <c:\faculdade\algoritmos\vt controle de custos\conecta_bd.c>
#include <c:\faculdade\algoritmos\vt controle de custos\conecta.c>
#include <c:\faculdade\algoritmos\vt controle de custos\mp_incluir.c>
#include <c:\faculdade\algoritmos\vt controle de custos\mp_alterar.c>
#include <c:\faculdade\algoritmos\vt controle de custos\mp_excluir.c>
#include <c:\faculdade\algoritmos\vt controle de custos\mp_consultar.c>
#include <c:\faculdade\algoritmos\vt controle de custos\p_incluir.c>
#include <c:\faculdade\algoritmos\vt controle de custos\p_alterar.c>
#include <c:\faculdade\algoritmos\vt controle de custos\p_excluir.c>
#include <c:\faculdade\algoritmos\vt controle de custos\p_consultar.c>
#include <c:\faculdade\algoritmos\vt controle de custos\p_estatistica.c>
/* ==============================================
   Função: Menu dos Cadastros de Matérias-primas
   ==============================================  */
int menu_cadastro_mprima(void){
   func_moldura_tela();  /* moldura na tela   */
   
   char opcao;
   int i;
   char texto[10][_TAMANHO] = {"CADASTRO DE MATÉRIAS-PRIMAS:",
                               "",
                               "Escolha uma opção:",
                               "",
                               "[1] Incluir",
                               "[2] Alterar",
                               "[3] Excluir",
                               "[4] Consultar",
                               "[9] Retornar ao Cadastro Geral",
                               "[0] Retornar ao Menu Principal",
	                           };
   while(1) {
      for (i=0;i<=9;i++) {
			gotoxy(12,9+i);  /* coluna,linha  */
		   if (i == 0) {
			   func_moldura_titulo(texto[0]);
			} else {
			   printf(texto[i]);
		   }
      }
      printf("\n\n");
	   opcao = getch();
      switch(opcao) {
      	case '0':
      		return main();
			case '1':
				/* Incluir Matérias-primas */
            mp_incluir();
            func_moldura_tela();
				break;
			case '2':
            /* Alterar Matérias-primas */
            mp_alterar();
            func_moldura_tela();
				break;
			case '3':
            /* Excluir Matérias-primas */
            mp_excluir();
            func_moldura_tela();
				break;
			case '4':
            /* Consultar Matérias-primas   */
            mp_consultar();
            func_moldura_tela();
            break;
			case '9':
            menu_cadastro_geral();
            break;
	      default:
	      	/* Essa caixa box usa a API do próprio Windows !!   */
            MessageBox(NULL, _caixa_erro, _caixa_titulo, MB_OK);
	   }
  	}
};
/* =======================================
   Função: Menu dos Cadastros de Produtos
   =======================================  */
int menu_cadastro_produto(void){
   func_moldura_tela();  /* moldura na tela  */
   
   char opcao;
   int i;
   char texto[10][_TAMANHO] = {"CADASTRO DE PRODUTOS:",
                               "",
                               "Escolha uma opção:",
                               "",
                               "[1] Incluir",
                               "[2] Alterar",
                               "[3] Excluir",
                               "[4] Consultar",
                               "[9] Retornar ao Cadastro Geral",
                               "[0] Retornar ao Menu Principal",
	                           };
   while(1) {
      for (i=0;i<=9;i++) {
			gotoxy(12,9+i); 
		   if (i == 0) {
			   func_moldura_titulo(texto[0]);
			} else {
			   printf(texto[i]);
		   }
      }
      printf("\n\n");
	   opcao = getch();
      switch(opcao) {
      	case '0':
      		return main();
			case '1':
				/* Incluir Produtos */
            p_incluir();
            func_moldura_tela();
				break;
			case '2':
            /* Alterar Produtos   */
            p_alterar();
            func_moldura_tela();
				break;
			case '3':
            /* Excluir Produtos    */
            p_excluir();
            func_moldura_tela();
				break;
			case '4':
            /* Consultar Produtos   */
            p_consultar();
            func_moldura_tela();
				break;
			case '9':
				menu_cadastro_geral();
				break;
	      default:
	      	/* Essa caixa box usa a API do próprio Windows !!     */
            MessageBox(NULL, _caixa_erro, _caixa_titulo, MB_OK);
	   }
  	}
};
/* ==================================
   Função: Menu dos Cadastros Gerais
   ================================== */
int menu_cadastro_geral(void){
   func_moldura_tela();  /* moldura na tela   */
   char opcao;
   int i;
   char texto[8][_TAMANHO] = {"CADASTRO GERAL:",
                              "",
                              "Escolha uma opção:",
                              "",
                              "[1] Produtos",
                              "[2] Matérias-primas",
                              "[9] Retornar ao Menu Principal",
                              "[0] Encerrar Aplicativo"
	                          };
   while(1) {
      for (i=0;i<=7;i++) {
			gotoxy(12,9+i);
		   if (i == 0) {
			   func_moldura_titulo(texto[0]);
			} else {
			   printf(texto[i]);
		   }
      }
      printf("\n\n");
	   opcao = getch();
      switch(opcao) {
      	case '0':
   	   	if (MessageBox(NULL, "Deseja sair do programa?", "Sair", MB_YESNO) == IDYES) {
               system("cls");
               exit(0);   /* encerra o aplicativo   */
            } else {
				   break;
				}
			case '1':
			   menu_cadastro_produto();
			   break;
			case '2':
			   menu_cadastro_mprima();
			   break;
			case '9':
				main();
				break;
	      default:
	      	/* Essa caixa box usa a API do próprio Windows !!    */
            MessageBox(NULL, _caixa_erro, _caixa_titulo, MB_OK);
	   }
  	}
};
/* =========================================================
   PRINCIPAL - Menu Principal do Programa
   ========================================================= */
int main(void) {
 	conecta_bd();
   func_moldura_tela();  /* moldura na tela   */
   SetConsoleTitle(_programa);    /* Comando da API do Windows para colocar nome na Barra de Titulo   */
   char opcao;
   int i;
   char texto[7][_TAMANHO] = {"PRINCIPAL:",
                              "",
                              "Escolha uma opção:",
                              "",
                              "[1] Cadastro Geral",
                              "[2] Consulta Estatística de Lucro",
                              "[0] Encerrar Aplicativo"
                             };
   while(1) {
      for (i=0;i<=6;i++) {
			gotoxy(12,9+i);  /* coluna,linha  */
		   if (i == 0) {
			   func_moldura_titulo(texto[0]);
		   } else {
			   printf(texto[i]);
		   }
      }
      printf("\n\n");
	   opcao = getch();
   	switch (opcao){
   	   case '0':
   	   	if (MessageBox(NULL, "Deseja sair do programa?", "Sair", MB_YESNO) == IDYES) {
               system("cls");
               exit(0);   /* encerra o aplicativo   */
            } else {
				   break;
				}
	      case '1':
	      	/* Cadastro de Geral de Produtos e Matérias-primas */
			   menu_cadastro_geral();
			   break;
	      case '2':
            /* Consulta Estatística de Lucro e Prejuízo dos Produtos  */
            p_estatistica();
			   break;
	      default:
	      	/* Essa caixa box usa a API do próprio Windows !!      */
            MessageBox(NULL, _caixa_erro, _caixa_titulo, MB_ICONWARNING);   /* comando da API do Windows   */
	   }
   }
}
