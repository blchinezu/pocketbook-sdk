#ifndef PBKEYBOARDHANDLER_H
#define PBKEYBOARDHANDLER_H

#include "pbieventhandler.h"

class PBKeyboardHandler
{
private:
	enum KeyStates
	{
		stateNone,
		statePress,
		stateHolding,
		stateHoldOff
	};

public:
    PBKeyboardHandler();
    ~PBKeyboardHandler();


    // Disable or enable key mapping. By default enabled
    void keyMapping(bool state);
    void keyMappingJoystick(bool state);

    int registrationRunner(PBIEventHandler *pStarter);
	int HandleEvent(int type, int par1, int par2);

	// set keyboard mapping: txt or pdf
	void setKeyboardMapping(int type);
	void UpdateKeyMapping();
	int DoAction(const char* mappingAction, KeyStates keyState);
	bool IsTurnPageAction(const char* mappingAction);
	bool IsNullAction(const char* mappingAction);
	int ProcessKeyPress(int key);

private:
    KeyStates GetKeyState(int message_type, int repeat_count);
    char *GetKeyMappingAction(int key_code, PBKeyboardHandler::KeyStates keyState);

    PBIEventHandler *m_pStarter;
    char *m_keyact0[32];
    char *m_keyact1[32];
    int  m_mappingtype;
    bool m_keyMapping;
    bool m_keyMappingJoystick;
    bool m_keyReleased;
};

#endif // PBKEYBOARDHANDLER_H
