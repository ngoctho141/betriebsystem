/* Client mit callrpc() */

#include "arith.h"
#include <rpc/rpc.h>
#include <stdio.h>
main(int argc, char *argv[]) {
 char *server;
 floatpair parameter;
 float *ergebnis;
 int error;
 server = argv[1];
 parameter.a = ...; parameter.b = ...;
 ergebnis = malloc(sizeof(float));
 error =
   callrpc(argv[1],ARITH_PROG,ARITH_VERS,MULT,
            (xdrproc_t)xdr_floatpair,(char *)&parameter,
            (xdrproc_t)xdr_float,(char *)ergebnis);
 if (error!=0) {
  clnt_perrno(error);
  exit(-1); }
 printf("Ergebnis: %f\n",*ergebnis);
} 


/* Client mit clnt_create() */

/*
#include "arith.h"
#include <rpc/rpc.h>
#include <stdio.h>
main(int argc, char *argv[]) {
 CLIENT *cl;
 char *server;
 floatpair parameter;
 float *ergebnis;
 int error;
 server = argv[1];
 cl = clnt_create(server,ARITH_PROG,ARITH_VERS,"udp");
 parameter.a = ...; parameter.b = ...;
 ergebnis = mult_1(&parameter,cl);
 if (ergebnis==NULL) {
  clnt_perrno(error);
  exit(-1); }
 printf("Ergebnis: %f\n",*ergebnis);
}

*/
