//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;


class Txc1 : public cSimpleModule
{
  private:
    int counter;
    simtime_t delay;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Txc1);

void Txc1::initialize()
{
    //We initialize the delay with the parameter defined in the .ini file
    delay = par("delay");

    enum type {C,D};
    EV << "Sending initial message from "<< getName() <<" with delay of "<< delay << "\n";
    cMessage *msg1 = new cMessage("tictocMsg1",C);
    cMessage *msg2 = new cMessage("tictocMsg2",D);
    if(strcmp("tic",getName())==0){
        //we send the message from tic with the delay defined in the .ini file
        sendDelayed(msg1,delay, "out");
        //another option would be using scheduleAt
        //scheduleAt(delay, msg1);
    } else {
        sendDelayed(msg2,delay, "out");
        //we send the message from toc with the delay defined in the .ini file
        //scheduleAt(delay, msg2);
    }
}

void Txc1::handleMessage(cMessage *msg)
{
    //we are using msg->getName() to return the name and msg->getKind() to return the type
    EV << getName() << " is handling the message "<< msg->getName()<< " of type " << msg->getKind() << "\n";

    //this is how we create the 95% probability.
    if(uniform(0,1) > 0.95){
        //in the case we're in the 5% case, we delete the message
        EV << "The message will be deleted. \n";
        delete msg;
    } else {
        EV << "The message will be send.\n";
        //else, send out the message with no extra delay
        send(msg, "out");
    }



}


