#pragma once 

#include "EPuckRobot.hpp"  
// local provided 
#include <webots/Keyboard.hpp> 
// system provided 

class EPuckGreenRobot : public EPuckRobot {
public:
  EPuckGreenRobot();
  
  void run(); // different run function from the one we inherited 

protected: 
  void display() const;
  void turn(); 

private: 
  webots::Keyboard* mKeyboard {}; 

};