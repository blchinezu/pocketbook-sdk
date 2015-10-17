#ifndef _PBPointerHandler_H
#define _PBPointerHandler_H

#include "pbieventhandler.h"
#include <sys/timeb.h>
#include "pbpoint.h"

// callback-функция таймера
void PBPointerHandlerTimer();

class PBPointerHandler
{
    friend void PBPointerHandlerTimer();

    const static int BOOKMARK_MARGIN		= 200;
    const static int PAGE_MARGIN_HEIGHT		= 150;
    const static int PAGE_MARGIN_WIDTH		= 100;
    const static int BACKLINK_BUTTON_WIDTH	= 50;
    const static int BACKLINK_BUTTON_HEIGHT	= 50;
    const static int BAR_HORZ				= 50;
    const static int BAR_VERT				= 50;
    const static int MENU_MARGIN			= 100;
	//const static int TIME_DOUBLECLICK		= 140;

public:
    ~PBPointerHandler();
    PBPointerHandler();

    // регистрация обработчика событий
    int registrationRunner (PBIEventHandler *pRunner);

    // вызывается из main_handler
    int HandleEvent (int type_event, int posX, int posY);

private:
    // возвращает разницу во времени в миллисекундах
	int diffTime(struct timeb *sStart, struct timeb *sEnd);
	int processPointerUpEvent();

    bool checkMotionRigthBottomToLeftBottom();
    bool checkMotionLeftBottomToRigthBottom();
    bool checkMotionTopRigthToBottomRight();
    bool checkMotionBottomRigthToTopRight();
    bool checkMotionCenterTopToCenterBottom();
    bool checkMotionCenterBottomToCenterTop();
    bool checkMotionCenterLeftToCenterRight();
    bool checkMotionCenterRightToCenterLeft();

    bool checkClickTopLeft();
    bool checkClickCenter();
    bool checkClickTopRigth();

    bool checkBookMark2();

private:
    int _curPosX, _curPosY;
    int _prevPosX, _prevPosY;
    int _nextPosX, _nextPosY;
    int _screenWidth, _screenHeight;
    int _pageWidth, _pageHeight;
    PBIEventHandler *_pointerRunner;
    bool _phAddBookMark;
    bool _isLongMotion, _isLongInternal;
    bool _isHoldMotion, _isHoldInternal;
	bool _isClick;
	PBPoint _pointerDownPoint;
	PBPoint _pointerUpPoint;
};

#endif //_PBPointerHandler_H
