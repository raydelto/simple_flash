// Default empty project template
#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include <QObject>
#include <bb/system/phone/Call>
#include <bb/system/phone/Phone>
#include <camera/camera_api.h>
#include <bps/bps.h>
#include <IntermitentThread.hpp>

namespace bb { namespace cascades { class Application; }}
class IntermitentThread;
using namespace bb::system::phone;
/*!
 * @brief Application pane object
 *
 *Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class ApplicationUI : public QObject
{
    Q_OBJECT
public:
    ApplicationUI(bb::cascades::Application *app);
    virtual ~ApplicationUI() {
	}
    Q_INVOKABLE
	void lightFlash();
    Q_INVOKABLE
	void intermitentFlash();
    Q_INVOKABLE
	bool isIntermitent() const {
		return intermitent;
	}
    Q_INVOKABLE
	bool isOn() const {
		return on;
	}


private:
	camera_handle_t camHandle;
	void initCamera();
	bool on;
	bool intermitent;
	IntermitentThread *intermitentThread;
};


#endif /* ApplicationUI_HPP_ */
