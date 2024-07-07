#include "BBActionFactory.h"
#include "BobbyMoveAction.h"
#include "DoorToggleAction.h"
#include "DoorEnterAction.h"
#include "TwistBedKnobAction.h"
#include "OilBedKnobAction.h"
#include "HideUnderBedAction.h"
#include "ShowInterfaceAction.h"
#include "HideInterfaceAction.h"
#include "ToggleBobbyInventory.h"
#include "ItemDragTreatmentAction.h"
#include "ItemDropAction.h"
#include "DisableProximityHintAction.h"
#include "ToggleBobbyEquipAction.h"
#include "PlayCutSceneAction.h"



std::shared_ptr<Action> BBActionFactory::create(std::string actionType, Json::Value properties)
{
    std::shared_ptr<Action> action;

    if (actionType == "CustomAction") {

        action = std::make_shared<NoAction>(properties);
    }
    else if (actionType == "DoorToggleAction") {

        action = std::make_shared<DoorToggleAction>(properties);
    }
    else if (actionType == "DoorEnterAction") {

        action = std::make_shared<DoorEnterAction>(properties);
    }
    else if (actionType == "BobbyMoveAction") {

        action = std::make_shared<BobbyMoveAction>(properties);
    }
    else if (actionType == "HideUnderBedAction") {

        action = std::make_shared<HideUnderBedAction>(properties);
    }
    else if (actionType == "OilBedKnobAction") {

        action = std::make_shared<OilBedKnobAction>(properties);
    }
    else if (actionType == "TwistBedKnobAction") {

        action = std::make_shared<TwistBedKnobAction>(properties);
    }
    else if (actionType == "ShowInterfaceAction") {

        action = std::make_shared<ShowInterfaceAction>(properties);
    }
    else if (actionType == "HideInterfaceAction") {

        action = std::make_shared<HideInterfaceAction>(properties);
    }
    else if (actionType == "ToggleBobbyInventory") {

        action = std::make_shared<ToggleBobbyInventory>(properties);
    }
    else if (actionType == "ItemDragTreatmentAction") {

        action = std::make_shared<ItemDragTreatmentAction>(properties);
    }
    else if (actionType == "ItemDropAction") {

        action = std::make_shared<ItemDropAction>(properties);
    }
    else if (actionType == "DisableProximityHintAction") {

        action = std::make_shared<DisableProximityHintAction>(properties);
    }
    else if (actionType == "ToggleBobbyEquip") {

        action = std::make_shared<ToggleBobbyEquipAction>(properties);
    }
    else if (actionType == "PlayCutSceneAction") {

        action = std::make_shared<PlayCutSceneAction>(properties);
    }

    else {
        action = ActionFactory::create(actionType, properties);
    }

    return action;
}
