#pragma once
#include "MobyDick.h"

class BBActionFactory : public ActionFactory{



public:

	std::shared_ptr<Action> create(std::string actionType, Json::Value properties, GameObject* parent) override;


private:




};
