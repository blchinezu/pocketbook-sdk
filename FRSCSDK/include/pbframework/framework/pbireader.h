#ifndef __PBIREADER_H__
#define __PBIREADER_H__

#include "pbdef.h"
#include "pbwordinfo.h"
#include "pbrect.h"

class PBIReader
{
public:
    // make invert some screen area described by PBRect vector
	virtual void InvertRectange(int /*screen*/, std::vector<PBRect> &/*rectList*/) {REPORT_PROCEDURE};

    // put word array from screen to destination vector. Return true if success.
	virtual bool GetText(int /*screen*/, std::vector<PBWordInfo> &/*dst*/) {REPORT_FUNCTION};

	// disables or enables keymapping for the joystick
	virtual void SetJoystickKeyMapping(bool /*mapping_allowed*/) {REPORT_PROCEDURE};

	// returns true if given page has a bookmark
	virtual bool IsPageHasBookmark(int /*page_number*/) {REPORT_FUNCTION};

	// switch RTL - LTR
	virtual void ChangeTextDirection(int /*rtl*/) {REPORT_PROCEDURE};

protected:

private:
};

#endif /* __PBIREADER_H__ */
