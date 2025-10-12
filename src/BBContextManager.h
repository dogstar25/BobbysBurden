#pragma once

#include "MobyDick.h"
#include "GameConstants.h"


class BBContextManager : public ContextManager
{

public:
	//static MRContextManager& instance();
	BBContextManager() = default;
	
	virtual bool saveSettings() override;
	virtual void loadSettings() override;

private:



};

																																																																																																																	