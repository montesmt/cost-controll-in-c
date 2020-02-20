/*
   Módulo Produto: Incluir
*/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include <mysql.h>
#include <time.h>
void p_alterar() {
   static int lin=20;
	char chave[13], descricao[61], medida[21];       /* 15, 60, 20 (sempre o último caracter será o controle <enter>)   */
   float preco_venda;
   system("cls");
   func_moldura_tela();
   func_moldura_titulo("Produto : Cadastro : Alterar");
   gotoxy(12,29);
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
	            preco_venda = atof(registro[4]);  /* converte de float para string */
	            
				   gotoxy(48,12);
				   printf("%s",descricao);
				   gotoxy(48,13);
				   printf("%s",medida);
				   gotoxy(48,14);
				   printf("%.2f",preco_venda);
  	         }
	      	mysql_free_result( resultado );  /* libero os resultados de produto que estavam em cache */

            gotoxy(48,12);
			   scanf("%[^\n]s",&descricao);
			   setbuf(stdin,NULL);
			   if (strcmp(descricao,"0")==0) { menu_cadastro_produto(); }

			   gotoxy(48,13);
			   scanf("%[^\n]s",&medida);
			   setbuf(stdin,NULL);
			   if (strcmp(medida,"0")==0) { menu_cadastro_produto(); }

			   gotoxy(48,13);
			   scanf("%[^\n]s",&medida);
			   setbuf(stdin,NULL);
			   if (strcmp(medida,"0")==0) { menu_cadastro_produto(); }
			
			   gotoxy(48,14);
			   scanf("%f",&preco_venda);
			   setbuf(stdin,NULL);      /* Para limpar o Buffer de Teclado   */
			   if (preco_venda==0) { menu_cadastro_produto(); }

			   /* Converter os valores monetários com vírgula para ponto, para salvar no MySQL.   */
			   char s_preco_venda[19];
				strcpy(s_preco_venda,func_converte_decimal( preco_venda ));

				strcpy(instrucao,"");   /* Limpar Variável instrucao para reutilizá-la  */
		      /* concatena a string com os campos preenchidos   */
			   sprintf(instrucao, "UPDATE produto SET descricao='%s', medida='%s', preco_venda='%s' WHERE chave='%s'", 
				                    descricao, medida, s_preco_venda, chave); 
			   
				if (mysql_real_query( instancia, instrucao, (unsigned int)strlen(instrucao) ) == 0) {  /* ALTERAMOS na tabela   */
			      MessageBox(NULL, "Alterado!", "Sucesso", MB_OK);
			  	   func_limpa_campo(48,11,11,13);    /* limpa campo chave */
			  	   func_limpa_campo(48,12,12,61);    /* limpa campo decricao */
			  	   func_limpa_campo(48,13,13,21);    /* limpa campo medida */
			  	   func_limpa_campo(48,14,14,14);    /* limpa campo preco_venda */
		      
				} else {
    		    	MessageBox(NULL, "Registro não foi alterado!", "Falhou", MB_OK);
				}
			}
       	mysql_close( instancia );  /* fecha a instância  */
      }
   }
}

