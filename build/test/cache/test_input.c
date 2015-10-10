#include "input.h"
#include "unity.h"




void setUp(void)

{

}



void tearDown(void)

{

}





void test_input_data(void)

{

  char buf[200] = "Hello23\0\x1B\n\x1B\n";

  char* exp = "Hello23\0\n\n";

  devcmd cmd;

  int recv = parse_input(&cmd, buf, 12);

  UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((recv)), (((void *)0)), (_U_UINT)21, UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((CMD_COUNT)), (_U_SINT)((cmd)), (((void *)0)), (_U_UINT)22, UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualMemory(( void*)(exp), ( void*)(buf), (_UU32)(10), 1, (((void *)0)), (_U_UINT)23);

}



void test_input_addr(void){

  char buff[200];

  char* command = "++addr\n";

  devcmd cmd;

  memcpy(buff, command, strlen(command));

  int recv = parse_input(&cmd, buff, strlen(command));

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((recv)), (((void *)0)), (_U_UINT)32, UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((CMD_ADDR)), (_U_SINT)((cmd)), (((void *)0)), (_U_UINT)33, UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualMemory(( void*)(command+6), ( void*)(buff), (_UU32)(1), 1, (((void *)0)), (_U_UINT)34);

}



void test_input_addr_cmd(void){

  char buff[200];

  char* command = "++addr 32\n";

  devcmd cmd;

  memcpy(buff, command, strlen(command));

  int recv = parse_input(&cmd, buff, strlen(command));

  UnityAssertEqualNumber((_U_SINT)((4)), (_U_SINT)((recv)), (((void *)0)), (_U_UINT)43, UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((CMD_ADDR)), (_U_SINT)((cmd)), (((void *)0)), (_U_UINT)44, UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualMemory(( void*)(command + 6), ( void*)(buff), (_UU32)(4), 1, (((void *)0)), (_U_UINT)45);

}
