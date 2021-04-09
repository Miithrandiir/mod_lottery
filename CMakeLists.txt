AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/src/LotteryHelper.hpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/src/LotteryHelper.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/src/LotteryCreature.hpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/src/LotteryCreature.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/src/LotteryWorld.hpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/src/LotteryWorld.cpp")
AC_ADD_SCRIPT_LOADER("Lottery" "${CMAKE_CURRENT_LIST_DIR}/src/LotteryLoader.h")

AC_ADD_CONFIG_FILE("${CMAKE_CURRENT_LIST_DIR}/conf/lottery.conf.dist")