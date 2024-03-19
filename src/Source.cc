//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Source.h"

namespace lab1_prep {

Define_Module(Source);

Source::Source()
{
    timerMessage = NULL;
}

Source::~Source()
{
    cancelAndDelete(timerMessage);
}

void Source::initialize()
{
    timerMessage = new cMessage("timer"); // New object generated -> needs to be deleted from GC - manual memory management
    scheduleAt(simTime(), timerMessage);
    counter = 0;
}

void Source::handleMessage(cMessage *msg)
{
    counter++;
    ASSERT(msg==timerMessage);

    cMessage *job = new cMessage("job");

    //job->getSrcProcId();

    job->addPar("value"); // create a field in the message transmitted to Sink
    job->par("value")=counter;   // set value for message field

    job->addPar("time");
    job->par("time") = simTime().dbl(); // alternative assign object  - ref

//    job->addPar("ID");
//    job->par("ID") = parent.num; // get ID from configuration file?

    send(job, "out");

    // Alternative 1 - constant delay
    //double delay = 0.005; // Maybe use random number between range
    //sendDelayed(job,delay,"out");

    // Alternative 2 - add delay to network channel - in Network Class - 3.2.2 and 3.9.1 Channel Specification of simulation manual

    scheduleAt(simTime()+par("sendInterval").doubleValue(), timerMessage);
}

}; // namespace
