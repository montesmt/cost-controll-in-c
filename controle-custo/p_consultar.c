/*
   Módulo Produto: Incluir
*/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include <mysql.h>
#include <time.h>
void p_consultar() {
   static int lin=20;
	char chave[13], descricao[61], medida[21];       /* 15, 60, 20 (sempre o último caracter será o controle <enter>)   */
   float preco_venda;
   system("cls");
   func_moldura_tela();
   func_moldura_titulo("Produto : Cadastro : Consultar");
   gotoxy(12,33);
   printf("Digite 0 (zero) para sair...");

   /* Textos das entradas de dados */   
   gotoxy(12,11);
   textcolor(4);   /* vermelha */
   printf("Chave (identifica produto->itens).: ");
   textcolor(1);   /* padrão */
   gotoxy(12,12);
   printf("Descrição do produto..............: ");
   gotoxy(12,13);
   printf("Medida/formato (peça, a X b, etc).: ");
   gotoxy(12,14);
   printf("Preço estipulado para venda....: R$ ");
   do {
      gotoxy(48,11);
	   scanf("%[^\n]s",&chave);
	   setbuf(stdin,NULL);
	   if (strcmp(chave,"0")==0) { menu_cadastro_produto(); }
	
	   /* Busca o produto  */
	   MYSQL *instancia;
		instancia = conecta();   /* recebe a instância gerada em conecta()   */
		if (instancia != NULL) {
			/* vamos preparar as variáveis para pegar os dados da Tabela */
			char *instrucao; 
			MYSQL_RES *resultado;
			MYSQL_ROW registro;
	      /* preparar o select para localizar o produto */     
			sprintf(instrucao, "SELECT * FROM produto WHERE chave='%s'",chave);
		   /* vamos localizar o produto */ 
			if (mysql_real_query( instancia, instrucao, (unsigned int)strlen(instrucao) ) == 0) {  /* zero = sem erro */
			   /* verificar se retornou algum dado */
	         resultado = mysql_store_result( instancia );   /* armazena algum resultado encontrado na busca através de SELECT */
	         if (mysql_affected_rows( instancia ) == 0) {
	            MessageBox(NULL, "Produto NÃO encontrado.", "Busca", MB_OK);
	         } else {
		         while ( registro = mysql_fetch_row( resultado ) ) {  /* só haverá um único registro de produto mesmo */
		            sprintf(descricao,"%s",registro[2]);
		            sprintf(medida,"%s",registro[3]);
		            preco_venda = atof(registro[4]);  /* converte de string para float  */
		            
					   gotoxy(48,12);
					   printf("%s",descricao);
					   gotoxy(48,13);
					   printf("%s",medida);
					   gotoxy(48,14);
					   printf("%.2f",preco_venda);
	  	         }
		      	mysql_free_result( resultado );  /* libero os resultados de produto que estavam em cache */
		      	/* Uma vez que achou o produto, vamos mostrar todas as suas matérias-primas */
	   	      /* preparar o select para localizar todas as matérias-primas */     
	   	      strcpy(instrucao,""); /* limpo a variável instrucao para reutilizá-la */
					sprintf(instrucao, "SELECT * FROM materia_prima WHERE chave='%s'",chave);
				   /* vamos localizar o produto */ 
					if (mysql_real_query( instancia, instrucao, (unsigned int)strlen(instrucao) ) == 0) {  /* zero = sem erro */
					   /* verificar se retornou algum dado */
			         resultado = mysql_store_result( instancia );   /* armazena algum resultado encontrado na busca através de SELECT */
			         if (mysql_affected_rows( instancia ) == 0) {
			         	gotoxy(12,17);
			         	textcolor(4);
			            printf("Ainda Não existem matérias-primas cadastradas para este produto.");
			            textcolor(1);
			         } else {
						   /* Monto a tela de matérias-primas  */
						   gotoxy(12,16);
						   textcolor(4);
						   printf("Matérias-primas");
						   textcolor(1);
						   gotoxy(12,17);
						   printf("-----------------------------------------------------------------------------------------------------------------");
						   gotoxy(12,18);
						   printf("Cód.");
						   gotoxy(18,18);
							printf("Chave");
						   gotoxy(26,18);
							printf("Descrição");
						   gotoxy(48,18);
							printf("Unid.");
						   gotoxy(62,18);
							printf("Quant.");
						   gotoxy(70,18);
							printf("Pr.Custo");
						   gotoxy(84,18);
							printf("%%Custo");
						   gotoxy(12,19);
		               printf("-----------------------------------------------------------------------------------------------------------------");
		               int codigo=0;
		               lin=20;
		               char chave[13], descricao[61], medida[21];       /* 15, 60, 20 (sempre o último caracter será o controle <enter>)   */
	                  float quantidade, preco_unitario, percentual;
				         while ( registro = mysql_fetch_row( resultado ) ) {
		    	            codigo = atof(registro[0]);
							   sprintf(chave,"%s",registro[1]);
		   	            sprintf(descricao,"%s",registro[2]);
			               sprintf(medida,"%s",registro[3]);
			               quantidade = atof(registro[4]);      /* converte de string para float */
			               preco_unitario = atof(registro[5]);  /* converte de string para float */
			               percentual = atof(registro[6]);      /* converte de string para float */
							   gotoxy(12,lin);
						      printf("%4d",codigo);
							   gotoxy(18,lin);
						      printf("%s",chave);
							   gotoxy(26,lin);
						      printf("%s",descricao);
							   gotoxy(48,lin);
						      printf("%s",medida);
							   gotoxy(62,lin);
						      printf("%4.2f",quantidade);
							   gotoxy(69,lin);
						      printf("%9.2f",preco_unitario);
							   gotoxy(84,lin);
						      printf("%4.2f%%",percentual);
							   lin++;
				         }
				   	}
				     	mysql_free_result( resultado );
				   }
				}
	       	mysql_close( instancia );  /* fecha a instância  */
	      }
	   }
	   char opcao = getch();
  	   func_limpa_campo(48,11,11,13);    /* limpa campo chave */
  	   func_limpa_campo(48,12,12,61);    /* limpa campo decricao */
  	   func_limpa_campo(48,13,13,21);    /* limpa campo medida */
  	   func_limpa_campo(48,14,14,14);    /* limpa campo preco_venda */
  	   func_limpa_campo(12,20,lin,115);   /* limpa a linha toda das matérias-primas */
   } while (1);
}

