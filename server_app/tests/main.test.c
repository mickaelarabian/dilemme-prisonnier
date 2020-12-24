#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "./fixtures/fixtures.h"
#include "./unit/utils.test.h"
#include "./unit/protocol.test.h"
#include "./unit/srvcnmanager.test.h"
#include "./unit/game.test.h"
#include "./unit/gameArray.test.h"

/**
 * Making all unit test
 * @brief test_utils() unit test utils
 * @brief test_protocol() unit test protocol
 * @brief test_srvcnmanager() unit test srvcnmanager
 * @brief test_game() unit test game
 * @brief test_game_array() unit test gameArray
 */
int main(){
  printf("\n\033[32;1m");
  printf("\n\n *** Starting tests server ***\n");
  test_utils();
  test_protocol();
  test_srvcnmanager();
  test_game();
  test_game_array();
  printf("\n *** End of tests server *** \n\n\n");
  printf("\033[0m");
  printf("\n");
}
