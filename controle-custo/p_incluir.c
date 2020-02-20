/*
   Módulo Produto: Incluir
*/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include <mysql.h>
#include <time.h>
void p_incluir() {
	char chave[13], descricao[61], medida[21];       /* 15, 60, 20 (sempre o último caracter será o controle <enter>)   */
   float preco_venda;
   
   system("cls");
   func_moldura_tela();
   func_moldura_titulo("Produto : Cadastro : Incluir");
   
   /* Textos das entradas de dados */  
	textcolor(4);
   gotoxy(12,11);
   printf("Chave (identifica produto->itens).: ");
	textcolor(1);
   gotoxy(12,12);
   printf("Descrição do produto..............: ");
   gotoxy(12,13);
   printf("Medida/Formato (peça, a X b, etc).: ");
   gotoxy(12,14);
   printf("Preço estipulado para Venda....: R$ ");

   do {
	   /* Variáveis das entradas de dados */
	   gotoxy(48,11);
	   scanf("%[^\n]s",&chave);
	   setbuf(stdin,NULL);
	   if (strcmp(chave,"0")==0) { menu_cadastro_produto(); }
	   
	   MYSQL *instancia;
		instancia = conecta();   /* recebe a instância gerada em conecta()   */
		if (instancia!=NULL) {
			/* printf("%d\n\n",instancia);  // teste para ver se de fato a instância chegou até aqui	  */
			/* Converter os valores decimais DE vírgula PARA ponto   */
			char instrucao[_TAMANHO_QUERY]; 
	      MYSQL_RES *resultado;
	      /* testar primeiro se produto existe com chave já existe */
	      /* concatena a string com os campos preenchidos   */
		   sprintf(instrucao, "SELECT chave FROM produto WHERE chave='%s'", chave); 
	      /* vamos localizar o produto */ 
			if (mysql_real_query( instancia, instrucao, (unsigned int)strlen(instrucao) ) == 0) {  /* zero = sem erro */
			   /* verificar se retornou algum dado */
		      resultado = mysql_store_result( instancia );   /* armazena algum resultado encontrado na busca através de SELECT */
		      if (mysql_affected_rows( instancia ) > 0) {

		         MessageBox(NULL, "Já Existe Produto com esta Chave! Insira outra chave.", "Falhou", MB_OK);

		      } else {
	   
				   gotoxy(48,12);
				   scanf("%[^\n]s",&descricao);
				   setbuf(stdin,NULL);
				   if (strcmp(descricao,"0")==0) { menu_cadastro_produto(); }
				   
				   gotoxy(48,13);
				   scanf("%[^\n]s",&medida);
				   setbuf(stdin,NULL);
				   if (strcmp(medida,"0")==0) { menu_cadastro_produto(); }
				
				   gotoxy(48,14);
				   scanf("%f",&preco_venda);
				   setbuf(stdin,NULL);      /* Para limpar o Buffer de Teclado   */
				
				   /* Converter os valores monetários com vírgula para ponto, para salvar no MySQL.   */
				   char s_preco_venda[19];
					strcpy(s_preco_venda,func_converte_decimal( preco_venda ));
	
			      /* concatena a string com os campos preenchidos   */
				   sprintf(instrucao, "INSERT INTO produto (chave, descricao, medida, preco_venda) \
															   VALUES ('%s', '%s', '%s', '%s')", \
																        chave, descricao, medida, s_preco_venda); 
				   
					if (mysql_real_query( instancia, instrucao, (unsigned int)strlen(instrucao) ) == 0) {  /* INSERIMOS na tabela   */
				      MessageBox(NULL, "Gravado!", "Sucesso", MB_OK);
				  	   func_limpa_campo(48,11,11,13);    /* limpa campo chave */
				  	   func_limpa_campo(48,12,12,61);    /* limpa campo decricao */
				  	   func_limpa_campo(48,13,13,21);    /* limpa campo medida */
				  	   func_limpa_campo(48,14,14,14);    /* limpa campo preco_venda */
					} else {
				    	MessageBox(NULL, "Registro não foi salvo!", "Falhou", MB_OK);
					}
	 		   } 
		   }
	   }
	   mysql_close( instancia );  /* fecha a instância  */
   } while(1);
}

