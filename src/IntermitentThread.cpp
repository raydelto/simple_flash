/*
 * IntermitentThread.cpp
 *
 *  Created on: May 30, 2013
 *      Author: Raydelto
 */

#include "IntermitentThread.hpp"
#include "PropertiesManager.hpp"

IntermitentThread::IntermitentThread(ApplicationUI* app) {
	this -> app = app;
	active = true;
	on = true;

}

void IntermitentThread::run() {
	while(active){
		app -> lightFlash();
		msleep(PropertiesManager::getInstance()->intermittentPeriodMs());
	}
	ensureOff();
}

IntermitentThread::~IntermitentThread() {
	ensureOff();
	app = NULL;
}

void IntermitentThread::ensureOff(){
	if (app -> isOn()){
		app -> lightFlash();
	}
}

