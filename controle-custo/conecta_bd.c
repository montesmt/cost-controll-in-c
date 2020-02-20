/* 
   Fontes de Recursos para pesquisa:
   http://cienciacomputacao.com.br/tutorial/instalando-a-biblioteca-mysql-no-codeblocks/
   ========================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
/* A biblioteca abaixo necessita de " mysql-connector-c-6.1.9-winx64.msi " para se conectar ao MySQL    */
/* Após instalação a mesma deverá ser encontrada na pasta: c:\Program Files\MySQL\MySQL Connector C 6.1\include\     */
#include <mysql.h>   /* biblioteca para conexão com Bancos de Dados MySQL */
int _faz_uma_vez = 1;
/* Criação da Base de Dados: */
int cria_base_de_dados( MYSQL *socket, char *host,
                                       char *usuario, char *senha, char *base_de_dados,
													int porta, char *socket_name, int flags ) {
	int ok=1;
	static char base_teste[5] = "mysql";  /* tabela mysql SOMENTE estará ativa se houver MySQL instalado e ativo !!  */
	static char estrutura[_TAMANHO_QUERY] = "CREATE DATABASE IF NOT EXISTS controle_custo \
	                                        CHARACTER SET latin1 COLLATE latin1_general_ci ; ";

   if (mysql_real_connect(socket, host, usuario, senha, base_teste, porta, socket_name, flags) != NULL) {
		ok = mysql_real_query(socket,estrutura,_TAMANHO_QUERY);
		if (ok != 0) {
		   printf(">>> Erro Grave(%d) Falhou a criação da Base de Dados [%s].",ok,base_de_dados);
	   }
   }
   printf("\n\n");
   mysql_close(socket);   /* fecha a conexão / soquete / instância  */
   return( ok );
}
/* Criação das Tabelas: */
int cria_tabelas( MYSQL *socket ) {
	int ok, i;
	char tabela[2][_TAMANHO_NOME] = { "produto", "materia_prima" };
    char estrutura[2][_TAMANHO_QUERY] = {
	                                     "CREATE TABLE IF NOT EXISTS produto ( \
   	                                   codigo              int(11)       NOT NULL AUTO_INCREMENT, \
                                         chave               varchar(12)   NOT NULL, \
			                                descricao           varchar(60)   NOT NULL, \
                                         medida              varchar(20),  \
                                         preco_venda         decimal(9,2), \
                                         PRIMARY KEY ( codigo ) \
                               	        ) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=1;",

	  	       								    "CREATE TABLE IF NOT EXISTS materia_prima ( \
	                                      codigo              int(11)      NOT NULL AUTO_INCREMENT, \
                                         chave               varchar(12)  NOT NULL, \
			                                descricao           varchar(60)  NOT NULL, \
                                         unidade_medida      varchar(15)  NOT NULL, \
                                         quantidade          decimal(4,2) NOT NULL, \
                                         preco_unitario      decimal(9,2),  \
                                         percentual          decimal(4,2),  \
                                         PRIMARY KEY ( codigo ) \
                               	        ) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=1;"
	  	       								  };
	printf("\n");
	for (i=0;i<=1;i++) {
		ok = mysql_real_query(socket,estrutura[i],_TAMANHO_QUERY);
		if (ok == 0) {
		   printf(">>> A Tabela [%s] foi carregada com sucesso...\n",tabela[i]);
	   } else {
		   printf(">>> Erro(%d) Falhou a criação da tabela [%s].\n",ok,tabela[i]);
	   }
   }
   printf("\n");
   return( ok );
}
/* ===================================
   Chamada Principal
   ================================== */
int conecta_bd( void ) {
   SetConsoleTitle("Aplicativo Controle de Custos");    /* Comando da API do Windows  */
   textbackground(8);   /* cor de fundo cinza  */
   system("cls");
//   system("MODE con cols=70 lines=26");  /* Expandindo a Tela do Programa !!   */
   textcolor(15); 
   gotoxy(15,2);
   printf("<<< Programa de Controle de Custos >>>\n");
   /* ------------------------
      DEFINIÇÃO DE VARIÁVEIS:
      ----------------------- */
	int volta=0, i;
   /* Definição das variáveis... (asterisco significa que a variável será também identificada pelo seu ponteiro de memória) */
   static char *host          = "localhost";       /* ou 127.0.0.1 computador local ou servidor do BD.  */
   static char *usuario       = "root";            /* usuário no MySQL server.  */
   static char *senha         = NULL;              /* senha do usuário no MySQL server.  */
   static char *base_de_dados = "controle_custo";  /* nome do Banco de Dados para o programa.  */
   static int  porta          = 3306;              /* porta padrão MySQL é 3306.  */
   static char *socket_name   = NULL;              /* nome do socket.  */
   static unsigned int flags;                      /* unsigned inteiros a partir de ZERO  */
   
   /* teste de alimentação das variáveis  */
   /* printf("%s %s %s %s %d %s %d \n\n",host,usuario,senha,base_de_dados,porta,socket_name,flags);  */
   /* teste de ponteiros  */
   /* printf("%d %d %d %d %d %s %d \n\n",&host,&usuario,&senha,&base_de_dados,&porta,&socket_name,&flags);  */
   
   /* Definição do Soquete / Instância  */
   MYSQL *socket;    /* connection handler = camada primitiva de conexão ou instância que identifica a conexão */
   /* Socket : Socket é um mecanismo de comunicação, usado normalmente para implementar um modelo cliente/servidor,
	            que permite a troca de mensagens entre os processos de uma máquina/aplicação servidor e de uma
	            máquina/aplicação cliente.
	*/
   /* =======================
      Prepara a Instância:
      ======================= */
   socket = mysql_init(NULL);     /* inicializa a instância da conexão (socket)   */
   if (socket == NULL) {          /*  se ponteiro for nulo, então MySQL pode não estar presente ou não está ativo!   */
      printf("\n\n");
      printf(">>> Falhou inicialização de MySQL - Verifique o gerenciador MySQL.\n");
      volta=1;
		exit(1);
   } else {
/*   	printf("\n");  */
/*    printf("Ponteiro de memória : %d \n\n",socket);    /* teste de ponteiro */
   }
   /* ------------------------------------------------------------
      Verificamos e criamos a Base de Dados caso ainda não exista
      ------------------------------------------------------------ */
   if (cria_base_de_dados( socket, host, usuario, senha, base_de_dados, porta, socket_name, flags ) != 0) {   /* Cria as tabelas necessárias caso ainda não existam.  */
      printf("\n\n");
      printf(">>> Problema com a Base de Dados - Programa foi encerrado!\n\n");
      exit(1);
   }
   /* ------------------------------------
      Conectamos com o Servidor !!!
      ------------------------------------ */
   socket = mysql_init(NULL);     /* RE-inicializa a instância da conexão (socket) SENÃO dá erro de Soquete Já Usado!!   */
   if (mysql_real_connect(socket, host, usuario, senha, base_de_dados, porta, socket_name, flags) != NULL) {
   	printf("\n\n");
      printf(".......Iniciando processo de carga.......");
   	printf("\n\n");
      printf(">>> Base de Dados [%s] foi conectada com sucesso!",base_de_dados);
   	printf("\n\n");
      printf(".......Carregamento das Tabelas..........");
   	printf("\n\n");
      
      if (cria_tabelas( socket ) != 0) {   /* Cria as tabelas necessárias caso ainda não existam.  */
         printf("\n\n");
         printf(">>> Problema com as Tabelas - Programa foi encerrado!\n\n");
         exit(1);
      } else {
      	/* Frescurinha na abertura do programa...  */
      	if (_faz_uma_vez==1) {
      		_faz_uma_vez=0;  /* para não retornar nesta rotina, fazer um vez só quando abre o programa!  */
	      	printf("\n\n");
	      	char frescura[14]="((((((((( %d ";
	      	for (i=7;i>=0;i--) {
	      		gotoxy(26,20);
	      		char palavra[14];
	            int tamanho = strlen(frescura)-1;       /* pega o tamanho do texto   */
	            strncpy(palavra,&frescura[1],tamanho);  /* retira a frescura da primeira posição   */
	            strcpy(frescura,palavra);               /* coloca o novo conteúdo em frescura   */
	      		strcat(frescura,")");                   /* coloca nova frescura para a direita   */
				  	printf(frescura,i);                     /* mostra a frescura pronta   */
				  	//sleep(1);                               /* pausa de 1 segundo   */
           }
        }
		}
   } else {
      volta= 1;
      printf(">>> Falhou a Conexão com o Banco de Dados %s em MySQL!\n",base_de_dados);
      printf(">>> Erro %d : %s\n", mysql_errno(socket), mysql_error(socket));
   }
   mysql_close(socket);   /* fecha a conexão / soquete / instância  */
   return( volta );
}
