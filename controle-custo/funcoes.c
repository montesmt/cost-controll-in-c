/*
   M�dulo de Fun��es
*/
/* ============================================================
   Retorna a Data do Sistema j� convertendo para Nosso Formato
   De mm/dd/aaaa PARA dd/mm/aaaa
   ============================================================ */
char retorna_data_sistema(void) {
/*  _strdate( _dateStr );   // pega a data do Sistema (biblioteca time.h)
    printf( "A data atual � %s", _dateStr);
   _strtime( _timeStr );   // pega a hora do Sistema (biblioteca time.h)
   printf( "A hora atual � %s", _timeStr);
*/   

   char data[11]="";
   char horario[6]="";
   char mes[2], ano[4];
   char minuto[2];
   char *semana[7] = { "Domingo","Segunda","Ter�a","Quarta","Quinta","Sexta","S�bado" };
   
	SYSTEMTIME st;       /* pega a hora do Sistema... */
	GetLocalTime(&st);   /* Alternativamente pode-se usar GetSystemTime para vers�o de Fusos de Hor�rios (UTC System) */
	/* Converte as Datas */
	sprintf(data,"%02d",st.wDay);     /* converto de num�rico para string e acrescento zero que faltar � esquerda */
	sprintf(mes, "%02d",st.wMonth);   /* converto de num�rico para string e acrescento zero que faltar � esquerda */
	sprintf(ano, "%04d",st.wYear);    /* converto de num�rico para string e acrescento zero que faltar � esquerda */
	/* Converte os Hor�rios */
	sprintf(horario,"%02d",st.wHour);      /* converto de num�rico para string e acrescento zero que faltar � esquerda */
	sprintf(minuto, "%02d",st.wMinute);    /* converto de num�rico para string e acrescento zero que faltar � esquerda */
   
	strcat(data,"/");     /* junta o dia + barra   */
   strcat(data,mes);     /* junta dia + barra + m�s  */
   strcat(data,"/");     /* junta dia/mes/   */
	strcat(data,ano);     /* junta dia/mes/ano   */
	
   strcat(horario,":");
   strcat(horario,minuto);
   printf("%s - %s, %s �s %s horas",_programa,semana[st.wDayOfWeek],data,horario);

}
/* ==========================================
   Fun��o: Moldura da Tela do Sistema
   USO:    func_moldura_tela()
   ========================================== */
void func_moldura_tela() {
	/*
	   Tabela de cores:
		0 = Black ----------- 8  = Gray
		1 = Blue ------------ 9  = Light Blue
		2 = Green ----------- 10 = Light Green
		3 = Aqua ------------ 11 = Light Aqua
		4 = Red ------------- 12 = Light Red
		5 = Purple ---------- 13 = Light Purple
		6 = Yellow ---------- 14 = Light Yellow
		7 = White ----------- 15 = Bright White
	*/
   system("cls");
   textbackground(4);   /* cor de fundo vermelha (parte externa do programa) faz parte do conio21/conio.c */
   system("cls");
   system("MODE con cols=140 lines=40");  /* Expandindo a Tela do Programa !! */
   static int lin=0, col=0, coluna_ini=10, linha_ini=5, coluna_fim=130, linha_fim=34;
	textcolor(1);  /* cor do texto das fontes */
   /* Monta a Sombra/moldura ao redor de cor preta  */
 	for (lin=linha_ini+3;lin<=linha_fim+3;lin++) {
   	for (col=coluna_ini+3;col<=coluna_fim+3;col++) {
	   	textbackground(8);      /* fundo cinza escuro (na parte de dentro do programa) */
	    	gotoxy(col,lin);        /* preenche coluna a coluna, na mesma linha! */
	   	printf(" ");
      }
   }
   char *localidade;
   localidade = setlocale(LC_ALL,"");
   gotoxy(50,36);
	textcolor(15);  /* cor do texto */
   printf("P�gina de C�digos do Pa�s: %s",localidade);
	textcolor(1);  /* volta com a cor do texto das fontes = azul */
	/* Monta a porte onde ficam as op��es do menu   */
	for (lin=linha_ini;lin<=linha_fim;lin++) {
   	for (col=coluna_ini;col<=coluna_fim;col++) {
	   	textbackground(15);      /* fundo cinza (na parte de dentro do programa) */
	    	gotoxy(col,lin);         /* preenche coluna a coluna, na mesma linha! */
	   	printf(" ");
      }
   }
}
/* ==========================================
   Fun��o: Moldura para T�tulos das Telas
   USO:    func_moldura_titulo()
   ========================================== */
void func_moldura_titulo(char titulo[30]) {
	gotoxy(12,6);
   printf("%s",_empresa);
   gotoxy(12,7);
	retorna_data_sistema();
   
   static int col;
	textcolor(15);   /* cor do texto das fontes dos t�tulos */
	/* Monta a porte onde fica o titulo d tela */
 	for (col=10;col<=130;col++) {
   	textbackground(4);    /* fundo vermelho */
    	gotoxy(col,9);        /* preenche coluna a coluna, na mesma linha!  */
   	printf(" ");
   }
   gotoxy(12,9);
   printf("%s",titulo);
   /* Volta a cor normal */
   gotoxy(12,10);
   textbackground(15);  /* volta o fundo cinza claro */
   textcolor(1);        /* volta a cor normal das fontes */
}
/* =================================================================
   fun��o troca v�rgula por PONTO de vari�veis decimais
   PARA SALVAR NO BANCO DE DADOS MySQL
   USO:  char variavel[19];
 	      strcpy(variavel,func_converte_decimal( valor_enviado ));
   ================================================================= */
char *func_converte_decimal( float valor ) {
	#define SIZE 19    /* precisa ser um tamanho seguro para a truncagem / arredondamento do valor */
   static char buffer[SIZE];
   static int tamanho=0;
   tamanho = snprintf(buffer, SIZE, "%f", valor);    /* converte de float para string para a contagem e retorna o tamanho */
   /* result ter� ent�o a quantidade de caracteres (d�gitos) incluindo a v�rgula do valor float. */
   /* if (tamanho >= SIZE) {
	   /* printf("A string foi truncada\n");   */
	   /* n�o me preocupo com isso, desde que n�o hajam lan�amentos com mais de 6 casas na decimal.  */
   /* }
   /* teste de mostragem */
   /* printf("Retorna o mesmo valor do float como string : %s\n\n", buffer); */
   /* printf("Tamanho da string : %i\n\n", tamanho); */
   
   /* processo para substituir a V�RGULA por um PONTO */
   static int i=0;
   static char novo_valor[SIZE];
   snprintf(novo_valor, SIZE, "%f", valor);  /* converte de float para string */
   for (i=0; i<tamanho; i++) {
	   if (novo_valor[i] == ',') {
   		novo_valor[i] = '.';    /* substitui a v�rgula pelo ponto !!  */
   		break;
     	}
   }
   /* teste de mostragem */
   /* printf("Retorna o mesmo valor de float como string : %s\n\n", novo_valor); */
   return( novo_valor );     
	/* lembre-se: depois do retorno fazer strcpy(var_recebe,esta_funcao);  */
}
/* ==================================================================================
   Fun��o para limpar os campos na tela
   USO: coluna, linha_inicial, linha_final, tamanho da vari�vel
=================================================================================== */
func_limpa_campo( int col, int lin_ini, int lin_fim, int tam) {
   static int x,y;
 	for (x=col;x<=(col+tam);x++) { 
 	   for (y=lin_ini;y<=(lin_fim);y++) {
       	gotoxy(x,y);
	      printf(" ");
	   }
   }
}
