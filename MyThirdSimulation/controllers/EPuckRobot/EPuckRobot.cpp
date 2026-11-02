#include "EPuckRobot.hpp" 

#include <string>
#include <iostream>
#include <iomanip>

// constructor 
// initialise in member initialiser list & in body (for longer parts) 
EPuckRobot::EPuckRobot()
: mLeftMotor {getMotor("left wheel motor")}, mRightMotor {getMotor("right wheel motor")}
{

  // initialise distance sensors
  const std::array<std::string, N_DIST_SENSORS> psNames {
    "ps0", "ps1", "ps2", "ps3",
    "ps4", "ps5", "ps6", "ps7"
  };
  
  for (int i {0}; i < N_DIST_SENSORS; ++i) {
  // initialising an array of distance sensors & enabling each one
    mPs[i] = getDistanceSensor(psNames[i]);
    mPs[i]->enable(TIME_STEP);
  }
  
  // finish initialising motors
  mLeftMotor->setPosition(INFINITY);
  mRightMotor->setPosition(INFINITY);
  mLeftMotor->setVelocity(0.0);
  mRightMotor->setVelocity(0.0);
}

void EPuckRobot::roam() {
    // reads sensors outputs
    for(int i {0}; i < N_DIST_SENSORS; ++i) {
    // get sensor output values & store them in the array 
      mPsValues[i] = mPs[i]->getValue();
    }
    
    // detect obstacles
    const double obstacleThreshold {80.0};
    mRightObstacle = {
      mPsValues[0] > obstacleThreshold ||
      mPsValues[1] > obstacleThreshold ||
      mPsValues[2] > obstacleThreshold
    };
    mLeftObstacle = {
      mPsValues[5] > obstacleThreshold ||
      mPsValues[6] > obstacleThreshold ||
      mPsValues[7] > obstacleThreshold
    };
    
    // initialize motor speeds at 50% of MAX_SPEED.
    const double speedScale {0.5};
    mLeftSpeed = speedScale * MAX_SPEED;
    mRightSpeed = speedScale * MAX_SPEED;
    
    // modify speeds according to obstacles
    if(mLeftObstacle) {
      // turn right
      mLeftSpeed  = speedScale * MAX_SPEED;
      mRightSpeed = -speedScale * MAX_SPEED;
    } else if(mRightObstacle) {
      // turn left
      mLeftSpeed  = -speedScale * MAX_SPEED;
      mRightSpeed = speedScale * MAX_SPEED;
    }
    
     // write actuators inputs
    mLeftMotor->setVelocity(mLeftSpeed);
    mRightMotor->setVelocity(mRightSpeed);
}

void EPuckRobot::report() const {
  
  // for debugging, you can print the sensor readings to the console
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Time: " << getTime() << ' ';
    std::cout << "DistanceSensors: ";
    for(const auto elem : mPsValues) {
      std::cout << elem << ' ';
    }
    
    // for debugging, print detection results to console 
    std::cout << "leftObstacle: " << mLeftObstacle << ' ' 
              << "rightObstacle: " << mRightObstacle << ' ';
              
    std::cout << "leftSpeed: " << mLeftSpeed << ' ' 
              << "rightSpeed: " << mRightSpeed << std::endl; 

}

void EPuckRobot::run() {
  while(step(TIME_STEP) != -1) { 
    roam();
    report();
  }
    
}


