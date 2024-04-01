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

namespace assignment1 {

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
    timerMessage = new cMessage("timer");
    scheduleAt(simTime(), timerMessage);
    counter=0;
}

void Source::handleMessage(cMessage *msg)
{
    ASSERT(msg==timerMessage);

    //Increment internal source node job counter
    counter++;

    // Data to be sent by source node
    cMessage *job = new cMessage("job");


    // Add job counter for this source node
    job->addPar("seq");
    job->par("seq") = counter;

    // Add source node time as reference to calculate latency
    job->addPar("time");
    job->par("time") = simTime().dbl();



    // Send Job
    // send(job, "out");

    // Send job with constant delay
    double delay = 0.05;
    sendDelayed(job, delay, "out");

    // Schedule the event for the next job transmission
    scheduleAfter(par("sendInterval").doubleValue(), timerMessage);
    // equivalent to line below - simulation manual section 4.7.1
    // scheduleAt(simTime()+par("sendInterval").doubleValue(), timerMessage);
}

}; // namespace
