#ifndef _PBIEVENTHANDLER_H
#define _PBIEVENTHANDLER_H

#include <stdio.h>
#include <inkview.h>
#include "pbdef.h"

class PBIEventHandler
{
public:
    // default virtual funcs which used if no keymapping
    virtual int onKeyLeft() {REPORT_FUNCTION};
    virtual int onKeyRight() {REPORT_FUNCTION};
    virtual int onKeyUp() {REPORT_FUNCTION};
    virtual int onKeyDown() {REPORT_FUNCTION};
    virtual int onKeyOK() {REPORT_FUNCTION};

    // key mapping functions
    virtual int onPageJNext10() {REPORT_FUNCTION};
    virtual int onPageJNext10Hold() {REPORT_FUNCTION};
    virtual int onPageJNext10Up() {REPORT_FUNCTION};

    virtual int onPageJPrev10() {REPORT_FUNCTION};
    virtual int onPageJPrev10Hold() {REPORT_FUNCTION};
    virtual int onPageJPrev10Up() {REPORT_FUNCTION};

    virtual int onPageSelect() {REPORT_FUNCTION};

    virtual int onPageFirst() {REPORT_FUNCTION};
    virtual int onPageLast() {REPORT_FUNCTION};

    virtual int onBack() {REPORT_FUNCTION};
    virtual int onForward() {REPORT_FUNCTION};

    virtual int onPageHistory() {REPORT_FUNCTION};

    virtual int onPageNext() {REPORT_FUNCTION};							// motionRigthBottomToLeftBottom
    virtual int onPagePrev() {REPORT_FUNCTION};							// motionLeftBottomToRigthBottom

    virtual int onNextSelection() {REPORT_FUNCTION};
    virtual int onPrevSelection() {REPORT_FUNCTION};

    virtual int onBookMarkOpen() {REPORT_FUNCTION};
    virtual int onBookMarkNew() {REPORT_FUNCTION};

    virtual int onNoteNew() {REPORT_FUNCTION};
    virtual int onNoteOpen() {REPORT_FUNCTION};
    virtual int onNoteSave() {REPORT_FUNCTION};

    virtual int onLinkBack() {REPORT_FUNCTION};							// clickTopLeft
    virtual int onLinkOpen() {REPORT_FUNCTION};

    virtual int onContentsOpen() {REPORT_FUNCTION};

    virtual int onSearchStart() {REPORT_FUNCTION};

    virtual int onDictionaryOpen() {REPORT_FUNCTION};

	virtual int onZoomerOpen() {REPORT_FUNCTION}; // motionBottomRigthToTopRigth
	virtual int onZoomIn() {REPORT_FUNCTION}; // motionBottomRigthToTopRigth
    virtual int onZoomOut() {REPORT_FUNCTION}; // motionTopRigthToBottomRigth

    virtual int onPanelHide() {REPORT_FUNCTION};

    virtual int onRotateOpen() {REPORT_FUNCTION};

    virtual int onMainMenu() {REPORT_FUNCTION};

    virtual int onExit() {REPORT_FUNCTION};

    virtual int onMp3Open() {REPORT_FUNCTION};
    virtual int onMp3Pause() {REPORT_FUNCTION};

    virtual int onVolumeUp() {REPORT_FUNCTION};
    virtual int onVolumeDown() {REPORT_FUNCTION};

    virtual int onConfigOpen() {REPORT_FUNCTION};
    virtual int onAboutOpen() {REPORT_FUNCTION};

    virtual int onPdfMode() {REPORT_FUNCTION};

    virtual int onDropConnect() { NetDisconnect(); return 0; };

    virtual int onBookMark1() {REPORT_FUNCTION};							// clickTopRigth
    virtual int onBookMark2() {REPORT_FUNCTION};

    virtual int onMenu() {REPORT_FUNCTION};							// doubleClickCenter

	virtual int onScreenDown (int /*startPosY*/, int /*endPosY*/) {REPORT_FUNCTION};// motionCenterUpToDown
	virtual int onScreenUp   (int /*startPosY*/, int /*endPosY*/) {REPORT_FUNCTION};// motionCenterDownToUp
	virtual int onScreenRight(int /*startPosX*/, int /*endPosX*/) {REPORT_FUNCTION};// motionCenterLeftToRight
	virtual int onScreenLeft (int /*startPosX*/, int /*endPosX*/) {REPORT_FUNCTION};// motionCenterRightToLeft

	virtual int onScrollDown(int /*startPosY*/, int /*endPosY*/) {REPORT_FUNCTION};// motionHoldCenterUpToDown
	virtual int onScrollUp  (int /*startPosY*/, int /*endPosY*/) {REPORT_FUNCTION};// motionHoldCenterDownToUp

	virtual int onTouchClick(int /*x*/, int /*y*/) {REPORT_FUNCTION};

    virtual int onFOREGROUND() {REPORT_FUNCTION};
    virtual int onBACKGROUND() {REPORT_FUNCTION};
};

#endif //_PBEVENTHANDLER_H
