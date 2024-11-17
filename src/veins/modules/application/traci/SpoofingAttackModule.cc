#include "veins/modules/application/traci/SpoofingAttackModule.h"
#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h"

using namespace veins;

Define_Module(SpoofingAttackModule);

void SpoofingAttackModule::initialize(int stage) {
    TraCIDemoRSU11p::initialize(stage);
    if (stage == 0) {
        // Load spoofing parameters from omnetpp.ini
        spoofingInterval = par("spoofingInterval").doubleValue();
        spoofedId = par("spoofedId").stdstringValue();
        spoofedPosition = Coord(par("spoofedX").doubleValue(),
                                par("spoofedY").doubleValue(), 0);

        EV << "SpoofingAttackModule initialized with parameters:\n"
           << "    Spoofing Interval: " << spoofingInterval << "\n"
           << "    Spoofed ID: " << spoofedId << "\n"
           << "    Spoofed Position: (" << spoofedPosition.x << ", " << spoofedPosition.y << ")\n";

        spoofingEvent = new cMessage("SpoofingEvent");
        scheduleAt(simTime() + spoofingInterval, spoofingEvent);
    }
}

void SpoofingAttackModule::handleSelfMsg(cMessage* msg) {
    if (msg == spoofingEvent) {
        sendSpoofedMessage();
        scheduleAt(simTime() + spoofingInterval, spoofingEvent);
    } else {
        TraCIDemoRSU11p::handleSelfMsg(msg);
    }
}

void SpoofingAttackModule::onWSM(BaseFrame1609_4* frame) {
    TraCIDemo11pMessage* wsm = check_and_cast<TraCIDemo11pMessage*>(frame);

    EV << "SpoofingAttackModule received a WSM with content: " << wsm->getWsmData() << endl;

    // Optionally modify or rebroadcast the message
    sendDelayedDown(wsm->dup(), 2 + uniform(0.01, 0.2));
}

void SpoofingAttackModule::sendSpoofedMessage() {
    TraCIDemo11pMessage* spoofedMessage = new TraCIDemo11pMessage("SpoofedTraCIDemo11pMessage");

    spoofedMessage->addPar("spoofedId").setStringValue(spoofedId.c_str());
    spoofedMessage->addPar("spoofedX").setDoubleValue(spoofedPosition.x);
    spoofedMessage->addPar("spoofedY").setDoubleValue(spoofedPosition.y);
    spoofedMessage->addPar("isSpoofed").setBoolValue(true);
    spoofedMessage->setByteLength(100);

    EV << "RSU [ID: " << spoofedId << "] sending spoofed position ("
       << spoofedPosition.x << ", " << spoofedPosition.y << ") at time "
       << simTime() << endl;

    // Change RSU color to indicate spoofing
    this->getDisplayString().setTagArg("i", 1, "red");

    // Send the spoofed message
    sendDown(spoofedMessage);

    // Reset RSU color after a delay
    cMessage* resetColorMessage = new cMessage("resetColor");
    scheduleAt(simTime() + 0.5, resetColorMessage);
}
