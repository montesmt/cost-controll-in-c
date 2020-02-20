/*
   M�dulo Mat�ria-prima: Incluir
*/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include <mysql.h>
#include <time.h>
void mp_alterar() {
	int codigo;
	char chave[13], descricao[61], medida[16];       /* 15, 60, 15 (sempre o �ltimo caracter ser� o controle <enter>)   */
   float quantidade, percentual, preco_unitario;
   system("cls");
   func_moldura_tela();
   func_moldura_titulo("Mat�ria-prima : Cadastro : Alterar");

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
   printf("Custo informado em valor ou percentual:");
   gotoxy(12,19);
   textcolor(1);    /* volta padr�o azul */
   printf("Pre�o Unit. de Compra Fornecedor...: R$ ");
   gotoxy(12,20);
   printf("(OU) %% de Custo sobre Produto Final...: ");
   do {
	   /* Vari�veis das entradas de dados    */
	   gotoxy(52,11);
	   scanf("%d",&codigo);
	   setbuf(stdin,NULL);     /* Para limpar o Buffer de Teclado   */
	   if (codigo==0) { menu_cadastro_mprima();	}
	
	   /* prepara para receber a inst�ncia gerada em conecta()  */
	   MYSQL *instancia;
		instancia = conecta();   /* recebe a inst�ncia gerada em conecta()    */
		if (instancia!=NULL) {
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
		         while ( registro = mysql_fetch_row( resultado ) ) {  /* s� haver� um �nico registro de produto mesmo */
	
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
		      	mysql_free_result( resultado );  /* libero os resultados de produto que estavam em cache */
		      	
		      	/* Passo a alterar a mat�ria-prima */
				   gotoxy(52,11);
				   scanf("%[^\n]s",&chave);
				   setbuf(stdin,NULL);        /* Para limpar o Buffer de Teclado   */
				   if (strcmp(chave,"0")==0) { menu_cadastro_mprima(); }
				
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
				
			      strcpy(instrucao,"");   /* Limpar Vari�vel instrucao para reutiliz�-la  */
				   sprintf(instrucao, "UPDATE materia_prima SET chave='%s', descricao='%s', unidade_medida='%s', \
					                                         quantidade='%f', preco_unitario='%f', percentual='%f WHERE codigo='%d' ",
		 														        chave, descricao, medida, s_quantidade, \
																		  s_preco_unitario, s_percentual, codigo);
		
					if (mysql_real_query( instancia, instrucao, (unsigned int)strlen(instrucao) ) == 0) {  /* INSERIMOS na tabela   */
				      MessageBox(NULL, "Alterado!", "Sucesso", MB_OK);
				  	   func_limpa_campo(52,11,11,19);     /* limpa campo c�digo */
				  	   func_limpa_campo(52,12,12,13);    /* limpa campo chave */
				  	   func_limpa_campo(52,13,13,61);    /* limpa campo descricao */
				  	   func_limpa_campo(52,14,14,16);    /* limpa campo medida */
				  	   func_limpa_campo(52,15,15,19);    /* limpa campo quantidade */
				  	   func_limpa_campo(52,18,20,19);    /* limpa campo percentual */
				  	   func_limpa_campo(52,19,20,19);    /* limpa campo preco_unitario */
				      
					} else {
	
				    	MessageBox(NULL, "Registro n�o foi alterado!", "Falhou", MB_OK);
					}
		   	}
		   	mysql_close( instancia );  /* fecha a inst�ncia   */
		   }
	   }
   } while(1);
}

