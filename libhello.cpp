#ifndef __hello_c_

#include <stdio.h>
#include <string.h>
//#include "include/dart_api.h"
//#include "include/dart_native_api.h"

#include "include/dart_api.h"
#include "include/dart_native_api.h"

Dart_NativeFunction ResolveName(
  Dart_Handle name,
  int argc, 
  bool* auto_setup_scope);

DART_EXPORT Dart_Handle hello_Init(
  Dart_Handle parent_library
) {
  printf("called hello_Init %p", parent_library);
  Dart_Handle result_code = Dart_SetNativeResolver(
    parent_library, ResolveName, NULL
  );
  if(Dart_IsError(result_code)) {
    return result_code;
  }
  return Dart_Null();
}

void test(Dart_NativeArguments arguments) {
  printf("call test\r\n");
  Dart_EnterScope();
  Dart_Handle arg0 =  Dart_GetNativeArgument(arguments, 0);
  Dart_SetReturnValue(arguments, arg0);
  Dart_ExitScope();
}

void testasw(Dart_Port dest_port_id, Dart_CObject* message) {
  printf("call testasw\r\n");
  Dart_CObject *param =  message->value.as_array.values[0];
  Dart_Port reply_port_id = param->value.as_send_port.id;
  Dart_CObject result;
  result.type = Dart_CObject_kInt64;
  result.value.as_int64 = 13;
  Dart_PostCObject(reply_port_id,&result);
  Dart_PostCObject(reply_port_id,&result);
  Dart_PostCObject(reply_port_id,&result);
//  Dart_CObject result;
//  result.type =  Dart_TypedData_kUint8;
//  result.value.as_int32 = 12;
 // Dart_PostCObject(reply_port_id, &result);
}

void testas(Dart_NativeArguments arguments) {
  printf("call testas\r\n");
  Dart_EnterScope();
  Dart_SetReturnValue(arguments, Dart_Null());

  Dart_Port service_port = Dart_NewNativePort("testas_01", testasw, true);
 // Dart_Handle sendport = Dart_NewSendPort(service_port, tesetasw, true);
  Dart_Handle send_port = Dart_NewSendPort(service_port);
  Dart_SetReturnValue(arguments, send_port);

  Dart_ExitScope();
}

Dart_NativeFunction ResolveName(
  Dart_Handle name,
  int argc, 
  bool* auto_setup_scope) {
    Dart_NativeFunction result = NULL;
    const char *cname;
    Dart_EnterScope();
    Dart_StringToCString(name, &cname);
    //
    printf("called resolveName %s\r\n", cname);
    if(strcmp("test",cname) == 0) {
      *auto_setup_scope = false;
      result = test;
    }
    if(strcmp("testas",cname) == 0) {
      *auto_setup_scope = false;
      result = testas;
    }
    Dart_ExitScope();
    return result;
  }
#endif