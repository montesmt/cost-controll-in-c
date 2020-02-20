/*
   Módulo Matéria-prima: Incluir
*/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include <mysql.h>
#include <time.h>
void mp_incluir() {
	char chave[13], descricao[61], medida[16];       /* 15, 60, 15 (sempre o último caracter será o controle <enter>)   */
   float quantidade, percentual, preco_unitario;
   system("cls");
   func_moldura_tela();
   func_moldura_titulo("Matéria-prima : Cadastro : Incluir");

   /* Textos das entradas de dados  */
	textcolor(4);
   gotoxy(12,11);
   printf("Chave (identificação do item->produto): ");
	textcolor(1);
   gotoxy(12,12);
   printf("Descrição do item.....................: ");
   gotoxy(12,13);
   printf("Unidade Medida (Kg, m, cm, peça)......: ");
   gotoxy(12,14);
   printf("Quantidade necessária p/ produto......: ");
   gotoxy(12,16);
   textcolor(12);    /* vermelho intenso */
   printf("Atenção: Entrar com preço de custo/compra OU percentual de custo:");
   gotoxy(12,18);
   textcolor(1);    /* volta padrão azul */
   printf("Preço Unit. de Compra Fornecedor...: R$ ");
   gotoxy(12,19);
   printf("(OU) %% de Custo sobre Produto Final...: ");
   //-----------------------------------------------------------------------------
   // Observação para cálculos posteriores considerar duas situações distintas:
	//      "Preço de Custo" = é quantidade * preço de compra
	// OU   "Preço de Custo" = é percentual de custo sobre valor final do produto
	// Exemplos: 2 dobradiças custa = 2 * preço de cada dobradiça
	//           1 solda custa 2% do valor final do produto
   //-----------------------------------------------------------------------------
   /* Variáveis das entradas de dados    */
   do {
	   gotoxy(52,11);
	   scanf("%[^\n]s",&chave);
	   setbuf(stdin,NULL);        /* Para limpar o Buffer de Teclado   */
	   if (strcmp(chave,"0")==0) { menu_cadastro_mprima(); }
	
	   MYSQL *instancia;
		instancia = conecta();   /* recebe a instância gerada em conecta()    */
		MYSQL_RES *resultado;
		if (instancia!=NULL) {
			/* printf("%d\n\n",instancia);  // teste para ver se de fato a instância chegou até aqui   */
	      /* PRIMEIRO: Vai verificar se a chave existe m Produto, por que se não existir não deixa cadastrar
			             a matéria-prima. Só pode cadastrar matéria-prima de produto existente!
		  */
	    	char instrucao[_TAMANHO_QUERY];
			sprintf(instrucao, "SELECT * FROM produto WHERE chave='%s'",chave);
		   /* vamos localizar o produto */ 
			if (mysql_real_query( instancia, instrucao, (unsigned int)strlen(instrucao) ) == 0) {  /* zero = sem erro */
			   /* verificar se retornou algum dado */
	         resultado = mysql_store_result( instancia );   /* armazena algum resultado encontrado na busca através de SELECT */
	         if (mysql_affected_rows( instancia ) == 0) {
	
	         	MessageBox(NULL, "Produto NÃO encontrado! Só pode cadastrar Matéria-prima de produto existente.", "Verificação", MB_OK);
	
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
				   scanf("%f",&preco_unitario);    /* está lendo até nulos */
				   setbuf(stdin,NULL);  
				   
				   gotoxy(52,19);
				   scanf("%f",&percentual);
				   setbuf(stdin,NULL);
				
				   /* Converter os valores monetários com vírgula para ponto, para salvar no MySQL.  */
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
					strcpy(instrucao,""); /* limpo a variável instrucao para reutilizá-la */
				   sprintf(instrucao, "INSERT INTO materia_prima (chave, descricao, unidade_medida, quantidade, \
																				  preco_unitario, percentual) \
																	   VALUES ('%s', '%s', '%s', '%s', '%s', '%s')", \
																		        chave, descricao, medida, s_quantidade, \
																				  s_preco_unitario, s_percentual);
				
				   /* printf("%s",instrucao);  /* teste para ver se a instrução foi preenchida corretamente   */
				
					if (mysql_real_query( instancia, instrucao, (unsigned int)strlen(instrucao) ) == 0) {  /* INSERIMOS na tabela   */
				      MessageBox(NULL, "Gravado!", "Sucesso", MB_OK);
		        	   func_limpa_campo(52,11,11,19);    /* limpa campo código */
				  	   func_limpa_campo(52,12,12,13);    /* limpa campo chave */
				  	   func_limpa_campo(52,13,13,61);    /* limpa campo descricao */
				  	   func_limpa_campo(52,14,14,16);    /* limpa campo medida */
				  	   func_limpa_campo(52,15,15,19);    /* limpa campo quantidade */
				  	   func_limpa_campo(52,18,20,19);    /* limpa campo percentual */
				  	   func_limpa_campo(52,19,20,19);    /* limpa campo preco_unitario */
					} else {
				    	MessageBox(NULL, "Registro não foi salvo!", "Falhou", MB_OK);
					}
		      } 
		   }
	   }
	   mysql_close( instancia );  /* fecha a instância   */
   } while(1);
}
    
