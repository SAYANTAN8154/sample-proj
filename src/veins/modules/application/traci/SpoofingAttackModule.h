#ifndef SPOOFINGATTACKMODULE_H_
#define SPOOFINGATTACKMODULE_H_

#include "veins/modules/application/traci/TraCIDemoRSU11p.h"
#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h"
#include "veins/modules/messages/BaseFrame1609_4_m.h"  // Include the header for BaseFrame1609_4

class SpoofingAttackModule : public veins::TraCIDemoRSU11p {
protected:
    simtime_t spoofingInterval;  // Interval for spoofing
    std::string spoofedId;       // ID to spoof
    veins::Coord spoofedPosition; // Spoofed position coordinates
    cMessage* spoofingEvent;     // Spoofing event message

    virtual void initialize(int stage) override;            // Initialization
    virtual void handleSelfMsg(cMessage* msg) override;     // Handle self messages
    virtual void onWSM(BaseFrame1609_4* frame) override;    // Handle WSMs (messages)
    void sendSpoofedMessage();                              // Send a spoofed message
};

#endif
