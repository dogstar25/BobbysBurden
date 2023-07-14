#include "BBActionFactory.h"
#include "ActorMoveAction.h"
#include "DoorCloseAction.h"
#include "DoorOpenAction.h"
#include "DoorEnterAction.h"
#include "ActorStairsMoveAction.h"
#include "TwistBedKnobAction.h"
#include "OilBedKnobAction.h"
#include "HideUnderBedAction.h"
#include "ShowPuzzleInterfaceAction.h"
#include "StandardHideAction.h"



std::shared_ptr<Action> BBActionFactory::create(std::string actionType)
{
    std::shared_ptr<Action> action;

    if (actionType == "CustomAction") {

        action = std::make_shared<NoAction>();
    }
    else if (actionType == "DoorOpenAction") {

        action = std::make_shared<DoorOpenAction>();
    }
    else if (actionType == "DoorCloseAction") {

        action = std::make_shared<DoorCloseAction>();
    }
    else if (actionType == "DoorEnterAction") {

        action = std::make_shared<DoorEnterAction>();
    }
    else if (actionType == "ActorMove") {

        action = std::make_shared<ActorMoveAction>();
    }
    else if (actionType == "ActorStairsMoveAction") {

        action = std::make_shared<ActorStairsMoveAction>();
    }
    else if (actionType == "HideUnderBedAction") {

        action = std::make_shared<HideUnderBedAction>();
    }
    else if (actionType == "OilBedKnobAction") {

        action = std::make_shared<OilBedKnobAction>();
    }
    else if (actionType == "TwistBedKnobAction") {

        action = std::make_shared<TwistBedKnobAction>();
    }
    else if (actionType == "ShowPuzzleInterfaceAction") {

        action = std::make_shared<ShowPuzzleInterfaceAction>();
    }
    else if (actionType == "StandardHideAction") {

        action = std::make_shared<StandardHideAction>();
    }
    else {
        action = ActionFactory::create(actionType);
    }

    return action;
}
