/*
   M�dulo Mat�ria-prima: Incluir
*/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include <mysql.h>
#include <time.h>
void mp_incluir() {
	char chave[13], descricao[61], medida[16];       /* 15, 60, 15 (sempre o �ltimo caracter ser� o controle <enter>)   */
   float quantidade, percentual, preco_unitario;
   system("cls");
   func_moldura_tela();
   func_moldura_titulo("Mat�ria-prima : Cadastro : Incluir");

   /* Textos das entradas de dados  */
	textcolor(4);
   gotoxy(12,11);
   printf("Chave (identifica��o do item->produto): ");
	textcolor(1);
   gotoxy(12,12);
   printf("Descri��o do item.....................: ");
   gotoxy(12,13);
   printf("Unidade Medida (Kg, m, cm, pe�a)......: ");
   gotoxy(12,14);
   printf("Quantidade necess�ria p/ produto......: ");
   gotoxy(12,16);
   textcolor(12);    /* vermelho intenso */
   printf("Aten��o: Entrar com pre�o de custo/compra OU percentual de custo:");
   gotoxy(12,18);
   textcolor(1);    /* volta padr�o azul */
   printf("Pre�o Unit. de Compra Fornecedor...: R$ ");
   gotoxy(12,19);
   printf("(OU) %% de Custo sobre Produto Final...: ");
   //-----------------------------------------------------------------------------
   // Observa��o para c�lculos posteriores considerar duas situa��es distintas:
	//      "Pre�o de Custo" = � quantidade * pre�o de compra
	// OU   "Pre�o de Custo" = � percentual de custo sobre valor final do produto
	// Exemplos: 2 dobradi�as custa = 2 * pre�o de cada dobradi�a
	//           1 solda custa 2% do valor final do produto
   //-----------------------------------------------------------------------------
   /* Vari�veis das entradas de dados    */
   do {
	   gotoxy(52,11);
	   scanf("%[^\n]s",&chave);
	   setbuf(stdin,NULL);        /* Para limpar o Buffer de Teclado   */
	   if (strcmp(chave,"0")==0) { menu_cadastro_mprima(); }
	
	   MYSQL *instancia;
		instancia = conecta();   /* recebe a inst�ncia gerada em conecta()    */
		MYSQL_RES *resultado;
		if (instancia!=NULL) {
			/* printf("%d\n\n",instancia);  // teste para ver se de fato a inst�ncia chegou at� aqui   */
	      /* PRIMEIRO: Vai verificar se a chave existe m Produto, por que se n�o existir n�o deixa cadastrar
			             a mat�ria-prima. S� pode cadastrar mat�ria-prima de produto existente!
		  */
	    	char instrucao[_TAMANHO_QUERY];
			sprintf(instrucao, "SELECT * FROM produto WHERE chave='%s'",chave);
		   /* vamos localizar o produto */ 
			if (mysql_real_query( instancia, instrucao, (unsigned int)strlen(instrucao) ) == 0) {  /* zero = sem erro */
			   /* verificar se retornou algum dado */
	         resultado = mysql_store_result( instancia );   /* armazena algum resultado encontrado na busca atrav�s de SELECT */
	         if (mysql_affected_rows( instancia ) == 0) {
	
	         	MessageBox(NULL, "Produto N�O encontrado! S� pode cadastrar Mat�ria-prima de produto existente.", "Verifica��o", MB_OK);
	
	         } else {
	   
				   gotoxy(52,12);
				   scanf("%[^\n]s",&descricao);
				   setbuf(stdin,NULL);
				   if (strcmp(descricao,"0")==0) { menu_cadastro_mprima(); }
				
				   gotoxy(52,13);
				   scanf("%[^\n]s",&medida);
				   setbuf(stdin,NULL);
				   if (strcmp(medida,"0")==0) { menu_cadastro_mprima(); }
				
				   gotoxy(52,14);
				   scanf("%f",&quantidade);
				   setbuf(stdin,NULL);     
				
				   gotoxy(52,18);
				   scanf("%f",&preco_unitario);    /* est� lendo at� nulos */
				   setbuf(stdin,NULL);  
				   
				   gotoxy(52,19);
				   scanf("%f",&percentual);
				   setbuf(stdin,NULL);
				
				   /* Converter os valores monet�rios com v�rgula para ponto, para salvar no MySQL.  */
				   char s_quantidade[19];
					strcpy(s_quantidade,func_converte_decimal( quantidade ));
				   char s_percentual[19];
					strcpy(s_percentual,func_converte_decimal( percentual ));
				   char s_preco_unitario[19];
					strcpy(s_preco_unitario,func_converte_decimal( preco_unitario ));
				
				   /* teste de valores monetarios
				      printf("%s\n",s_percentual);
				      printf("%s\n",s_preco_unitario);
				   */
					strcpy(instrucao,""); /* limpo a vari�vel instrucao para reutiliz�-la */
				   sprintf(instrucao, "INSERT INTO materia_prima (chave, descricao, unidade_medida, quantidade, \
																				  preco_unitario, percentual) \
																	   VALUES ('%s', '%s', '%s', '%s', '%s', '%s')", \
																		        chave, descricao, medida, s_quantidade, \
																				  s_preco_unitario, s_percentual);
				
				   /* printf("%s",instrucao);  /* teste para ver se a instru��o foi preenchida corretamente   */
				
					if (mysql_real_query( instancia, instrucao, (unsigned int)strlen(instrucao) ) == 0) {  /* INSERIMOS na tabela   */
				      MessageBox(NULL, "Gravado!", "Sucesso", MB_OK);
		        	   func_limpa_campo(52,11,11,19);    /* limpa campo c�digo */
				  	   func_limpa_campo(52,12,12,13);    /* limpa campo chave */
				  	   func_limpa_campo(52,13,13,61);    /* limpa campo descricao */
				  	   func_limpa_campo(52,14,14,16);    /* limpa campo medida */
				  	   func_limpa_campo(52,15,15,19);    /* limpa campo quantidade */
				  	   func_limpa_campo(52,18,20,19);    /* limpa campo percentual */
				  	   func_limpa_campo(52,19,20,19);    /* limpa campo preco_unitario */
					} else {
				    	MessageBox(NULL, "Registro n�o foi salvo!", "Falhou", MB_OK);
					}
		      } 
		   }
	   }
	   mysql_close( instancia );  /* fecha a inst�ncia   */
   } while(1);
}
    
