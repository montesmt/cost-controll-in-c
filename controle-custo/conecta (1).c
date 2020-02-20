/* Conecta MySQL para Instruções 
   Incluir ou Alterar ou Consultar tabelas
*/
#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
MYSQL *conecta(void) {     /* RETORNO COM O PONTEIRO DA INSTÂNCIA DE MYSQL   */
   MYSQL *socket;
   socket = mysql_init(NULL);     /* pega a instância gerada pelo MySQL  */
   if (socket!=NULL) {    /* testa a instância se existe, e, conecta na Base de Dados !!   */
		static char *host          = "localhost";       /* ou 127.0.0.1 computador local ou servidor do BD.   */
		static char *usuario       = "root";            /* usuário no MySQL server.   */
		static char *senha         = NULL;              /* senha do usuário no MySQL server.  */
		static char *base_de_dados = "controle_custo";  /* nome do Banco de Dados para o programa.  */
		static int  porta          = 3306;              /* porta padrão MySQL é 3306.   */
		static char *socket_name   = NULL;              /* nome do socket.   */
		static unsigned int flags;
      
	   if (!mysql_real_connect(socket, host, usuario, senha, base_de_dados, porta, socket_name, flags)) {
		   socket = NULL;
      }
	} 
	if (socket==NULL) {
		MessageBox(NULL, "Falhou a conexão com o Banco de Dados!", "Falha de Socket", MB_ICONWARNING);
	}
   /* printf("%d\n",socket);  // teste para ver se a instância foi gerada &socket pega o endereço de memória !!  */
	return( socket );          /* retorna o inteiro do socket se tudo ok OU nulo se der tudo errado !!  */
}
