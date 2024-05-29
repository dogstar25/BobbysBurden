#include "BBEnvironmentEventFactory.h"

#include "LightningMaker.h"
#include "LightningEvent.h"
#include "RainEvent.h"
#include "LightningWindowFlashEvent.h"
#include "LightningBoltEvent.h"


std::shared_ptr<EnvironmentEvent> BBEnvironmentEventFactory::create(std::string eventType, std::variant<std::string, EventLevel, float> param, Timer durationTimer)
{
    std::shared_ptr<EnvironmentEvent> event;

    if (eventType == "lightningMaker") {

        event =  std::make_shared<LightningMaker>(param, durationTimer);
    }
    else if (eventType == "lightningEvent") {

        event = std::make_shared<LightningEvent>(param, durationTimer);
    }
    else if (eventType == "rainEvent") {

        event = std::make_shared<RainEvent>(param, durationTimer);
    }
    else if (eventType == "lightningWindowFlashEvent") {

        event = std::make_shared<LightningWindowFlashEvent>(param, durationTimer);
    }
    else if (eventType == "lightningBoltEvent") {

        event = std::make_shared<LightningBoltEvent>(param, durationTimer);
    }
    else {
        event = EnvironmentEventFactory::create(eventType, param, durationTimer);
    }

    return event;
}
