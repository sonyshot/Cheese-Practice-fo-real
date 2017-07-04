#pragma once

#ifndef REALBUTTONS_H
#define REALBUTTONS_H

#include "Button.h"

class ContextSwitch :public Button {

public:
	ContextSwitch();

	AppContext * swap(AppContext * oldContext, ContextEnum newContext);
};

class SettingEdit :public Button {

};

#endif // !REALCONTEXTS_H