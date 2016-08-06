// Default empty project template
#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include "PropertiesManager.hpp"

using namespace bb::cascades;

ApplicationUI::ApplicationUI(bb::cascades::Application *app) :
		QObject(app) {
	QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
	PropertiesManager *propertiesManager = PropertiesManager::getInstance();
	qml->setContextProperty("propertyManager", propertiesManager);
	qml->setContextProperty("_backend", this);
	AbstractPane *root = qml->createRootObject<AbstractPane>();
	qDebug() << "Starting camera initialization" << endl;
	if (bps_initialize() == BPS_SUCCESS) {
		qDebug() << "BPS SUCCESSFULLY INITIALIZED" << endl;
	} else {
		qDebug() << "BPS COULD NOT START" << endl;
	}
	initCamera();
	//preventScreenLock();
	app->setScene(root);
}

void ApplicationUI::lightFlash() {
	this->on = !this->on;
	camera_error_t error;
	if (this->on) {
		error = camera_config_videolight(camHandle, CAMERA_VIDEOLIGHT_ON);
		if (error != CAMERA_EOK) {
			qDebug() << "error camera_config_videolight ON" << endl;
		}
	} else {
		error = camera_config_videolight(camHandle, CAMERA_VIDEOLIGHT_OFF);
		if (error != CAMERA_EOK) {
			qDebug() << "error camera_config_videolight OFF" << endl;
		}
	}
}

void ApplicationUI::intermitentFlash() {
	intermitent = !intermitent;
	if (intermitent) {
		intermitentThread = new IntermitentThread(this);
		intermitentThread->start(QThread::HighestPriority);
	} else {

		intermitentThread->setActive(false);
		intermitentThread->terminate();
		while (!intermitentThread->isFinished()) {
			//DO NOTHING, Wait for the thread to finish, before deleting
		}
		this->on = true;
		lightFlash();

		delete (intermitentThread);
		intermitentThread = NULL;
	}

}

void ApplicationUI::initCamera() {
	camHandle = CAMERA_HANDLE_INVALID;
	on = PropertiesManager::getInstance() -> autoStart();
	intermitent = false;
	static const char vf_group[] = "viewfinder_window_group";
	camera_error_t error = camera_open(CAMERA_UNIT_REAR, CAMERA_MODE_RW | CAMERA_MODE_ROLL, &camHandle);
	if (error == CAMERA_EOK) {
		qDebug() << "camera Opened Successfully" << endl;

		error = camera_set_photovf_property(camHandle,
				CAMERA_IMGPROP_WIN_GROUPID, vf_group,
				CAMERA_IMGPROP_WIN_ID, "my_viewfinder");

		if (error != CAMERA_EOK) {
			qDebug() << "error camera_set_photovf_property " << endl;
		}
		error = camera_start_video_viewfinder(camHandle, NULL, NULL, NULL);
		if (error != CAMERA_EOK) {
			qDebug() << "error camera_start_video_viewfinder " << endl;
		}

		qDebug() << "can????" << camera_can_feature(camHandle, CAMERA_FEATURE_VIDEOLIGHT);
		PropertiesManager* properties = PropertiesManager::getInstance();
		if(properties->autoStart()){
			qDebug() << "AutoStart option is ON" << endl;
			error = camera_config_videolight(camHandle, CAMERA_VIDEOLIGHT_ON);
			if (error == CAMERA_EOK) {
				qDebug() << "LIGHT Opened Successfully" << endl;
			} else {
				qDebug() << "LIGHT CANNOT Open Successfully" << endl;
			}
		}else{
			qDebug() << "AutoStart option is OFF" << endl;
		}

	} else {
		qDebug() << "camera CANNOT Open Successfully" << endl;
	}

}
