/*
 * PropertiesManager.cpp
 *
 *  Created on: Oct 25, 2012
 *      Author: bslack
 */

#include "PropertiesManager.hpp"
#include "applicationui.hpp"
#include <QSettings>
#include <QMutex>



PropertiesManager *PropertiesManager::getInstance() {
	static PropertiesManager *singleton = NULL;
    static QMutex mutex;
	if(singleton == NULL) {
		mutex.lock();
		if(!singleton) singleton = new PropertiesManager();
		mutex.unlock();
	}
   	return singleton;
}

PropertiesManager::PropertiesManager(QObject *parent) : QObject(parent) , msTime(-1){
}

PropertiesManager::~PropertiesManager() {}


int PropertiesManager::intermittentPeriod() {
	QSettings settings("AST", "SimpleFlash");
	QVariant v = settings.value("intermittent", 2);
	qDebug() << "GET: Intermitent value " << v.toInt(NULL);
	return v.toInt(NULL);
}
void PropertiesManager::setIntermittentPeriod(int period) {
	msTime = -1;
	QSettings settings("AST", "SimpleFlash");
	QVariant v = settings.value("intermittent", 2);
	int c = v.toInt(NULL);
	qDebug() << "SET: period value " << period;
	qDebug() << "SET: v.toInt(NULL) value " << v.toInt(NULL);
	if(c != period) {
		settings.setValue("intermittent", period);
		emit intermittentPeriodChanged(period);
	}
}

bool PropertiesManager::autoStart() {
	QSettings settings("AST", "SimpleFlash");
	QVariant v = settings.value("autoStart", false);
	qDebug() << "GET: autoStart value " << v.toBool();
	return v.toBool();
}
void PropertiesManager::setAutoStart(bool start) {
	QSettings settings("AST", "SimpleFlash");
	QVariant v = settings.value("autoStart", false);
	bool c = v.toBool();
	qDebug() << "SET: start value " << start;
	qDebug() << "SET: v.toBool(NULL) value " << v.toBool();
	if(c != start) {
		settings.setValue("autoStart", start);
		emit autoStartChanged(start);
	}
}

bool PropertiesManager::awake() {
	QSettings settings("AST", "SimpleFlash");
	QVariant v = settings.value("awake", false);
	qDebug() << "GET: awake value " << v.toBool();
	return v.toBool();
}
int PropertiesManager::intermittentPeriodMs() {
	if(msTime == -1){
		int option = intermittentPeriod();
		switch(option){
		case 0:
			msTime = 100;
			break;
		case 1:
			msTime = 250;
			break;
		case 2:
			msTime = 500;
			break;
		case 3:
			msTime = 750;
			break;
		case 4:
			msTime = 1000;
			break;
		default:
			msTime =  500;
			break;
		}
	}
	return msTime;
}

void PropertiesManager::setAwake(bool awake) {
	QSettings settings("AST", "SimpleFlash");
	QVariant v = settings.value("awake", false);
	bool c = v.toBool();
	qDebug() << "SET: awake value " << awake;
	qDebug() << "SET: v.toBool() value " << v.toBool();
	if(c != awake) {
		settings.setValue("awake", awake);
		emit awakeChanged(awake);
	}
}





