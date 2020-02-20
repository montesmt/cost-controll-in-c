/*
   M�dulo Mat�ria-prima: Incluir
*/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include <mysql.h>
#include <time.h>
void mp_excluir() {
	int codigo;
	char chave[13], descricao[61], medida[16];       /* 15, 60, 15 (sempre o �ltimo caracter ser� o controle <enter>)   */
   float quantidade, percentual, preco_unitario;
   system("cls");
   func_moldura_tela();
   func_moldura_titulo("Mat�ria-prima : Cadastro : Excluir");
   gotoxy(12,33);
   printf("Pressione <s> para sair...");

   /* Textos das entradas de dados  */
   gotoxy(12,11);
   printf("C�digo da Mat�ria-prima...............: ");
   gotoxy(12,12);
   textcolor(4);   /* vermelha */
   printf("Chave (identifica��o do item->produto): ");
   textcolor(1);   /* padr�o */
   gotoxy(12,13);
   printf("Descri��o do item.....................: ");
   gotoxy(12,14);
   printf("Unidade Medida (Kg, m, cm, pe�a)......: ");
   gotoxy(12,15);
   printf("Quantidade necess�ria p/ produto......: ");
   gotoxy(12,17);
   textcolor(4);    /* vermelha */
   printf("Custo informado em valor ou percentual: ");
   gotoxy(12,19);
   textcolor(1);    /* volta padr�o azul */
   printf("Pre�o Unit. de Compra Fornecedor...: R$ ");
   gotoxy(12,20);
   printf("(OU) %% de Custo sobre Produto Final...: ");
   //-----------------------------------------------------------------------------
   // Observa��o para c�lculos posteriores considerar duas situa��es distintas:
	//      "Pre�o de Custo" = � quantidade * pre�o de compra
	// OU   "Pre�o de Custo" = � percentual de custo sobre valor final do produto
	// Exemplos: 2 dobradi�as custa = 2 * pre�o de cada dobradi�a
	//           1 solda custa 2% do valor final do produto
   //-----------------------------------------------------------------------------
   do {
	   /* Vari�veis das entradas de dados    */
	   gotoxy(52,11);
	   scanf("%d",&codigo);
	   setbuf(stdin,NULL);     /* Para limpar o Buffer de Teclado   */
	   if (codigo==0) { menu_cadastro_mprima();	}
	
	   /* Busca o produto  */
	   MYSQL *instancia;
		instancia = conecta();   /* recebe a inst�ncia gerada em conecta()   */
		if (instancia != NULL) {
			/* vamos preparar as vari�veis para pegar os dados da Tabela */
			char *instrucao; 
			MYSQL_RES *resultado;
			MYSQL_ROW registro;
	      /* preparar o select para localizar o produto */     
			sprintf(instrucao, "SELECT * FROM materia_prima WHERE codigo='%d'",codigo);
		   /* vamos localizar a mat�ria-prima */ 
			if (mysql_real_query( instancia, instrucao, (unsigned int)strlen(instrucao) ) == 0) {  /* zero = sem erro */
			   /* verificar se retornou algum dado */
	         resultado = mysql_store_result( instancia );   /* armazena algum resultado encontrado na busca atrav�s de SELECT */
	         if (mysql_affected_rows( instancia ) == 0) {
	            MessageBox(NULL, "Mat�ria-prima N�O encontrada.", "Busca", MB_OK);
	         } else {
		         while ( registro = mysql_fetch_row( resultado ) ) {
					
		            sprintf(chave,"%s",registro[1]);
		            sprintf(descricao,"%s",registro[2]);
		            sprintf(medida,"%s",registro[3]);
		            quantidade = atof(registro[4]);      /* converte de float para string */
		            percentual = atof(registro[5]);      /* converte de float para string */
		            preco_unitario = atof(registro[6]);  /* converte de float para string */
		            
					   gotoxy(52,12);
					   printf("%s",chave);
					   gotoxy(52,13);
					   printf("%s",descricao);
					   gotoxy(52,14);
					   printf("%s",medida);
					   gotoxy(52,15);
					   printf("%.2f",quantidade);
					   gotoxy(52,19);
					   printf("%.2f%%",percentual);
					   gotoxy(52,20);
					   printf("%.2f",preco_unitario);
					   
		         }
		         /* Ent�o, tendo encontrada a mat�ria-prima vamos perguntar se deseja excluir */
		         if (MessageBox(NULL, "Deseja excluir essa mat�ria-prima?", "Exclus�o", MB_YESNO) == IDYES) {
		         	strcpy(instrucao,"");   /* Limpar Vari�vel instrucao para reutiliz�-la  */
					   sprintf(instrucao, "DELETE FROM materia_prima WHERE codigo='%d'",codigo);
					   /* vamos localizar a mat�ria-prima */ 
						if (mysql_real_query( instancia, instrucao, (unsigned int)strlen(instrucao) ) == 0) {  /* zero = sem erro */
						   /* verificar se retornou algum dado */
				         resultado = mysql_store_result( instancia );   /* armazena algum resultado encontrado na busca atrav�s de SELECT */
				         if (mysql_affected_rows( instancia ) > 0) {		         	
				            MessageBox(NULL, "Registro foi exclu�do.", "Exclus�o Realizada", MB_OK);
			            	mysql_free_result( resultado );
						  	   func_limpa_campo(52,11,11,19);    /* limpa campo c�digo */
						  	   func_limpa_campo(52,12,12,13);    /* limpa campo chave */
						  	   func_limpa_campo(52,13,13,61);    /* limpa campo descricao */
						  	   func_limpa_campo(52,14,14,16);    /* limpa campo medida */
						  	   func_limpa_campo(52,15,15,19);    /* limpa campo quantidade */
						  	   func_limpa_campo(52,18,20,19);    /* limpa campo percentual */
						  	   func_limpa_campo(52,19,20,19);    /* limpa campo preco_unitario */
				         }
				      }
		         }
		   	}
		   }
	   }
	   mysql_close( instancia );  /* fecha a inst�ncia / socket  */
   } while(1);
}

