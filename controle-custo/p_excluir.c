/*
   M�dulo Produto: Incluir
*/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include <mysql.h>
#include <time.h>
void p_excluir() {
   static int lin=20;
	char chave[13], descricao[61], medida[21];       /* 15, 60, 20 (sempre o �ltimo caracter ser� o controle <enter>)   */
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
   textcolor(1);   /* padr�o */
   gotoxy(12,12);
   printf("Descri��o do produto..............: ");
   gotoxy(12,13);
   printf("Medida/formato (pe�a, a X b, etc).: ");
   gotoxy(12,14);
   printf("Pre�o estipulado para venda....: R$ ");
   do {
	   gotoxy(48,11);
	   scanf("%[^\n]s",&chave);
	   setbuf(stdin,NULL);
	   if (strcmp(chave,"0")==0) { menu_cadastro_produto(); }
	
	   /* Busca o produto  */
	   MYSQL *instancia;
		instancia = conecta();   /* recebe a inst�ncia gerada em conecta()   */
		if (instancia != NULL) {
			/* vamos preparar as vari�veis para pegar os dados da Tabela */
			char *instrucao; 
			MYSQL_RES *resultado;
			MYSQL_ROW registro;
	      /* preparar o select para localizar o produto */     
			sprintf(instrucao, "SELECT * FROM produto WHERE chave='%s'",chave);
		   /* vamos localizar o produto */ 
			if (mysql_real_query( instancia, instrucao, (unsigned int)strlen(instrucao) ) == 0) {  /* zero = sem erro */
			   /* verificar se retornou algum dado */
	         resultado = mysql_store_result( instancia );   /* armazena algum resultado encontrado na busca atrav�s de SELECT */
	         if (mysql_affected_rows( instancia ) == 0) {
	            MessageBox(NULL, "Produto N�O encontrado.", "Busca", MB_OK);
	         } else {
		         while ( registro = mysql_fetch_row( resultado ) ) {  /* s� haver� um �nico registro de produto mesmo */
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
		         /* Ent�o, tendo encontrado o produto vamos perguntar se deseja excluir o produto COM TODAS as suas mat�rias primas */
		         if (MessageBox(NULL, "Todas as mat�rias-primas deste produto tamb�m ser�o exclu�das. \n\nDeseja excluir esse produto?", "Exclus�o", MB_YESNO) == IDYES) {
		         	strcpy(instrucao,"");   /* Limpar Vari�vel instrucao para reutiliz�-la  */
					   sprintf(instrucao, "DELETE FROM materia_prima WHERE chave='%s'",chave);
					   /* vamos localizar e excluir todas as mat�rias-primas do produto */ 
						if (mysql_real_query( instancia, instrucao, (unsigned int)strlen(instrucao) ) == 0) {  /* zero = sem erro */
						   /* verificar se retornou algum dado */
				         resultado = mysql_store_result( instancia ); 
				         if (mysql_affected_rows( instancia ) > 0) {
				            /* SE CONSEGUIU EXCLUIR TODAS AS MAT�RIAS-PRIMAS DO REFERIDO PRODUTO, ENT�O AGORA EXCLUI PRODUTO */
				         	strcpy(instrucao,"");   /* Limpar Vari�vel instrucao para reutiliz�-la  */
							   sprintf(instrucao, "DELETE FROM produto WHERE chave='%s'",chave);
							   /* vamos localizar e excluir o produto */ 
								if (mysql_real_query( instancia, instrucao, (unsigned int)strlen(instrucao) ) == 0) {  /* zero = sem erro */
								   /* verificar se retornou algum dado */
						         resultado = mysql_store_result( instancia );
						         if (mysql_affected_rows( instancia ) > 0) {		         	
						            MessageBox(NULL, "Produto foi exclu�do.", "Exclus�o Realizada", MB_OK);
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
    	mysql_close( instancia );  /* fecha a inst�ncia  */
   } while(1);
}

