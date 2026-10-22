// File:          MySecondInheritanceController.cpp
// Date:
// Description:
// Author:
// Modifications:

#include "EPuckRobot.hpp"

int main(int argc, char **argv) {

  EPuckRobot ePuckRobot {}; // calls constructor & performs initialisation
  ePuckRobot.run(); // run function conducts all the movement by calling other ftns

  return 0;
}