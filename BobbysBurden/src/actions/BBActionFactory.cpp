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



std::shared_ptr<Action> BBActionFactory::create(std::string actionType)
{
    std::shared_ptr<Action> action;

    if (actionType == "CustomAction") {

        action = std::make_shared<NoAction>();
    }
    else if (actionType == "DoorToggleAction") {

        action = std::make_shared<DoorToggleAction>();
    }
    else if (actionType == "DoorEnterAction") {

        action = std::make_shared<DoorEnterAction>();
    }
    else if (actionType == "BobbyMoveAction") {

        action = std::make_shared<BobbyMoveAction>();
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
    else if (actionType == "ShowInterfaceAction") {

        action = std::make_shared<ShowInterfaceAction>();
    }
    else if (actionType == "HideInterfaceAction") {

        action = std::make_shared<HideInterfaceAction>();
    }
    else if (actionType == "ToggleBobbyInventory") {

        action = std::make_shared<ToggleBobbyInventory>();
    }
    else if (actionType == "ItemDragTreatmentAction") {

        action = std::make_shared<ItemDragTreatmentAction>();
    }
    else if (actionType == "ItemDropAction") {

        action = std::make_shared<ItemDropAction>();
    }
    else if (actionType == "DisableProximityHintAction") {

        action = std::make_shared<DisableProximityHintAction>();
    }
    else if (actionType == "ToggleBobbyEquip") {

        action = std::make_shared<ToggleBobbyEquipAction>();
    }

    else {
        action = ActionFactory::create(actionType);
    }

    return action;
}
