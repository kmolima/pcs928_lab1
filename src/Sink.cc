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

#include "Sink.h"

namespace lab1_prep {

Define_Module(Sink);

void Sink::initialize()
{
    lastArrival = simTime();
    iaTimeHistogram.setName("interarrival times");
    arrivalsVector.setName("arrivals");
    arrivalsVector.setInterpolationMode(cOutVector::NONE);

    difference.setName("diff");
    difference.setInterpolationMode(cOutVector::NONE);

}

void Sink::handleMessage(cMessage *msg)
{
    simtime_t d = simTime() - lastArrival;

    double source_time = msg->par("time");
    double time_diff = simTime().dbl() - source_time;

    EV << "Received " << msg->getName() << " on gate: " << msg->getArrivalGateId() << " with value: " << msg->par("value") << " $$$ " << time_diff << endl;

    delete msg; //manual management of memory - garbage collector

    iaTimeHistogram.collect(d);
    arrivalsVector.record(1);
    difference.record(time_diff);

    lastArrival = simTime();
}

void Sink::finish()
{
    recordStatistic(&iaTimeHistogram);
}

}; // namespace
