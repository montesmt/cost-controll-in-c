/*
   Módulo Produto: Incluir
*/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include <mysql.h>
#include <time.h>
void p_excluir() {
   static int lin=20;
	char chave[13], descricao[61], medida[21];       /* 15, 60, 20 (sempre o último caracter será o controle <enter>)   */
   float preco_venda;
   system("cls");
   func_moldura_tela();
   func_moldura_titulo("Produto : Cadastro : Excluir");
   gotoxy(12,33);
   printf("Pressione 0 (zero) para sair...");

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
		         /* Então, tendo encontrado o produto vamos perguntar se deseja excluir o produto COM TODAS as suas matérias primas */
		         if (MessageBox(NULL, "Todas as matérias-primas deste produto também serão excluídas. \n\nDeseja excluir esse produto?", "Exclusão", MB_YESNO) == IDYES) {
		         	strcpy(instrucao,"");   /* Limpar Variável instrucao para reutilizá-la  */
					   sprintf(instrucao, "DELETE FROM materia_prima WHERE chave='%s'",chave);
					   /* vamos localizar e excluir todas as matérias-primas do produto */ 
						if (mysql_real_query( instancia, instrucao, (unsigned int)strlen(instrucao) ) == 0) {  /* zero = sem erro */
						   /* verificar se retornou algum dado */
				         resultado = mysql_store_result( instancia ); 
				         if (mysql_affected_rows( instancia ) > 0) {
				            /* SE CONSEGUIU EXCLUIR TODAS AS MATÉRIAS-PRIMAS DO REFERIDO PRODUTO, ENTÃO AGORA EXCLUI PRODUTO */
				         	strcpy(instrucao,"");   /* Limpar Variável instrucao para reutilizá-la  */
							   sprintf(instrucao, "DELETE FROM produto WHERE chave='%s'",chave);
							   /* vamos localizar e excluir o produto */ 
								if (mysql_real_query( instancia, instrucao, (unsigned int)strlen(instrucao) ) == 0) {  /* zero = sem erro */
								   /* verificar se retornou algum dado */
						         resultado = mysql_store_result( instancia );
						         if (mysql_affected_rows( instancia ) > 0) {		         	
						            MessageBox(NULL, "Produto foi excluído.", "Exclusão Realizada", MB_OK);
								  	   func_limpa_campo(48,11,11,13);    /* limpa campo chave */
								  	   func_limpa_campo(48,12,12,61);    /* limpa campo decricao */
								  	   func_limpa_campo(48,13,13,21);    /* limpa campo medida */
								  	   func_limpa_campo(48,14,14,14);    /* limpa campo preco_venda */
					            	mysql_free_result( resultado );
					            }
					         } 
				         }
				      }
		         }
				}
	      }
	   }
    	mysql_close( instancia );  /* fecha a instância  */
   } while(1);
}

