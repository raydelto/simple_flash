/*
 * PropertiesManager.hpp
 *
 *  Created on: Aug 2, 2013
 *      Author: Raydelto
 */

#ifndef PropertiesManager_HPP_
#define PropertiesManager_HPP_

#include <QObject>

class PropertiesManager : public QObject {
	Q_OBJECT
public:
	Q_PROPERTY(int intermittentPeriod READ intermittentPeriod WRITE setIntermittentPeriod NOTIFY intermittentPeriodChanged);
	Q_PROPERTY(bool autoStart READ autoStart WRITE setAutoStart NOTIFY autoStartChanged);
	Q_PROPERTY(bool awake READ awake WRITE setAwake NOTIFY awakeChanged);

	static PropertiesManager *getInstance();
	PropertiesManager(QObject *parent = NULL);
	virtual ~PropertiesManager();

	int intermittentPeriod();
	int intermittentPeriodMs();
	void setIntermittentPeriod(int period);

	bool autoStart();
	void setAutoStart(bool start);

	bool awake();
	void setAwake(bool awake);
private:
	int msTime;


signals:
	void intermittentPeriodChanged(int period);
	void autoStartChanged(bool start);
	void awakeChanged(bool awake);


};

#endif /* PropertiesManager_HPP_ */
