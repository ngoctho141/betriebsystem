#include <rpc/rpc.h>
#include "arith.h"
float* mult_1_svc(floatpair *param, struct svc_req *r) {
  static float result;
  result = param->a * param->b;
  return (&result); }
