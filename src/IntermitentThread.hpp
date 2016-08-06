/*
 * IntermitentThread.hpp
 *
 *  Created on: May 30, 2013
 *      Author: Raydelto
 */

#ifndef INTERMITENTTHREAD_HPP_
#define INTERMITENTTHREAD_HPP_
#include <QThread>
#include <applicationui.hpp>
class ApplicationUI;
class IntermitentThread: public QThread {
protected:
	virtual void run ();
public:
	IntermitentThread(ApplicationUI* app);
	virtual ~IntermitentThread();

	bool isActive() const {
		return active;
	}

	void setActive(bool active) {
		this->active = active;
	}

private:
	ApplicationUI* app;
	bool on;
	bool active;
	void ensureOff();
};

#endif /* INTERMITENTTHREAD_HPP_ */
