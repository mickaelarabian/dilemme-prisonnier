#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "./unit/controller.test.h"

/**
 * Making all unit test
 * @brief test_controller() unit test controller
 * @brief test_socket() unit test protocol
 */
int main(){
  printf("\n\033[32;1m");
  printf("\n\n *** Starting tests client ***\n");
  test_controller();
  printf("\n *** End of tests client *** \n\n\n");
  printf("\033[0m");
  printf("\n");
}
