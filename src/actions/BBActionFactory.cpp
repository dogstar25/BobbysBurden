#include "BBActionFactory.h"
#include "BobbyMoveAction.h"
#include "DoorToggleAction.h"
#include "DoorEnterAction.h"
#include "TwistBedKnobAction.h"
#include "HideAction.h"
#include "ShowInterfaceAction.h"
#include "HideInterfaceAction.h"
#include "ToggleBobbyInventory.h"
#include "ItemDragTreatmentAction.h"
#include "ItemDropAction.h"
#include "DisableProximityHintAction.h"
#include "ToggleBobbyEquipAction.h"
#include "SpiderDeployAction.h"
#include "ScareBobbyAction.h"
#include "PushGuestBedButtonAction.h"
#include "PlayPhonographAction.h"
#include "GhostMoveAction.h"


std::shared_ptr<Action> BBActionFactory::create(std::string actionType, Json::Value properties, GameObject* parent)
{
    std::shared_ptr<Action> action;

    if (actionType == "CustomAction") {

        action = std::make_shared<NoAction>(properties, parent);
    }
    else if (actionType == "DoorToggleAction") {

        action = std::make_shared<DoorToggleAction>(properties, parent);
    }
    else if (actionType == "DoorEnterAction") {

        action = std::make_shared<DoorEnterAction>(properties, parent);
    }
    else if (actionType == "BobbyMoveAction") {

        action = std::make_shared<BobbyMoveAction>(properties, parent);
    }
    else if (actionType == "HideAction") {

        action = std::make_shared<HideAction>(properties, parent);
    }
    else if (actionType == "TwistBedKnobAction") {

        action = std::make_shared<TwistBedKnobAction>(properties, parent);
    }
    else if (actionType == "ShowInterfaceAction") {

        action = std::make_shared<ShowInterfaceAction>(properties, parent);
    }
    else if (actionType == "HideInterfaceAction") {

        action = std::make_shared<HideInterfaceAction>(properties, parent);
    }
    else if (actionType == "ToggleBobbyInventory") {

        action = std::make_shared<ToggleBobbyInventory>(properties, parent);
    }
    else if (actionType == "ItemDragTreatmentAction") {

        action = std::make_shared<ItemDragTreatmentAction>(properties, parent);
    }
    else if (actionType == "ItemDropAction") {

        action = std::make_shared<ItemDropAction>(properties, parent);
    }
    else if (actionType == "DisableProximityHintAction") {

        action = std::make_shared<DisableProximityHintAction>(properties, parent);
    }
    else if (actionType == "ToggleBobbyEquip") {

        action = std::make_shared<ToggleBobbyEquipAction>(properties, parent);
    }
    else if (actionType == "SpiderDeployAction") {

        action = std::make_shared<SpiderDeployAction>(properties, parent);
    }
    else if (actionType == "ScareBobbyAction") {

        action = std::make_shared<ScareBobbyAction>(properties, parent);
    }
    else if (actionType == "PushGuestBedButtonAction") {

        action = std::make_shared<PushGuestBedButtonAction>(properties, parent);
    }
    else if (actionType == "PlayPhonographAction") {

        action = std::make_shared<PlayPhonographAction>(properties, parent);
    }
    else if (actionType == "GhostMoveAction") {

        action = std::make_shared<GhostMoveAction>(properties, parent);
    }

    else {
        action = ActionFactory::create(actionType, properties, parent);
    }

    return action;
}
