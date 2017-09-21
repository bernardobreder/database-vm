#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "test.h"

//void signal_callback_handler(int signum) {
//	printf("Caught signal %d\n", signum);
//	sleep(2);
//	exit(signum);
//}
//
//int main() {
//	signal(SIGINT, signal_callback_handler);
//	signal(SIGTERM, signal_callback_handler);
//	while (1) {
//		printf("Program processing stuff here.\n");
//		sleep(1);
//	}
//	printf("Hello\n");
//	return EXIT_SUCCESS;
//}

//#include "ocilib.h"
//
//int main(int argc, char *argv[]) {
//	OCI_Connection* cn;
//	OCI_Statement* st;
//	OCI_Resultset* rs;
//
//	if (!OCI_Initialize(NULL, 0, OCI_ENV_DEFAULT)) {
//		printf("Not Inited");
//		return EXIT_FAILURE;
//	}
//
//	cn = OCI_ConnectionCreate("piedade.tecgraf.puc-rio.br:1521/sismica", "sbb", "sbb", OCI_SESSION_DEFAULT);
//	if (!cn) {
//		printf("Not connected");
//		return EXIT_FAILURE;
//	}
//	st = OCI_StatementCreate(cn);
//
//	OCI_ExecuteStmt(st, "select * from visao");
//
//	rs = OCI_GetResultset(st);
//
//	while (OCI_FetchNext(rs)) {
//		printf("%i - %s\n", OCI_GetInt(rs, 1), OCI_GetString(rs, 2));
//	}
//
//	OCI_Cleanup();
//	printf("Finish\n");
//	return EXIT_SUCCESS;
//}

int main(int argc, char *argv[]) {
	oonsql_test();
	return 0;
}
