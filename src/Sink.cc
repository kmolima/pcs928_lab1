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

namespace assignment1 {

Define_Module(Sink);

void Sink::initialize()
{
    // Get number of node modules from composed NED simulation file
    size = getAncestorPar("num");

    std::string prefix1 = "interarrival times for channel";
    std::string prefix2 = "time diff for channel";
    std::string prefix3 = "out of order for channel";

    // initialize for each input channel
    for (int i = 0; i < size; i++) {
        std::string i_str=std::to_string(i);

        std::stringstream name1;
        name1 << prefix1 << " " << i;
        lastArrival[i] = simTime();
        iaTimeHistogram[i].setName(name1.str().c_str());

        // Initialize arrival sequential number array (seq no)
        arrivalsVector[i] = 0;

        // Time difference statistics between sending source node and this sink
        std::stringstream name2;
        name2 << prefix2 << " " << i;
        difference[i].setName(name2.str().c_str());
        difference[i].setInterpolationMode(cOutVector::NONE);

        // Initialize out of order counter for each channel with 0
        std::stringstream name3;
        name3 << prefix3 << " " << i;
        outOfOrderVector[i].setName(name3.str().c_str());
        outOfOrderVector[i].setInterpolationMode(cOutVector::NONE);
    }




}

void Sink::handleMessage(cMessage *msg)
{
    simtime_t d = simTime() - lastArrival[msg->getArrivalGate()->getIndex()];

    // Extract parameter values sent by source node
    double source_time = msg->par("time");
    double time_diff = simTime().dbl() - source_time;
    int seq = msg->par("seq");

    // Event on received job
    EV << "Received " << msg->getName() << " with seq. no " << seq << " from source ID: " << msg->getSenderModuleId() << " on gate: " << msg->getArrivalGate()->getIndex() << " with time diff: " << time_diff << endl;

    // Verify sequential order
    int next = arrivalsVector[msg->getArrivalGate()->getIndex()] + 1;
    if( seq != next){
        outOfOrderVector[msg->getArrivalGate()->getIndex()].record(1);
        EV << "#####" << "Received package out of order in channel " << msg->getArrivalGate()->getIndex() << "#####" << endl;
    }


    iaTimeHistogram[msg->getArrivalGate()->getIndex()].collect(d);
    difference[msg->getArrivalGate()->getIndex()].record(time_diff);
    arrivalsVector[msg->getArrivalGate()->getIndex()]=seq;
    lastArrival[msg->getArrivalGate()->getIndex()] = simTime();

    delete msg;
}

void Sink::finish()
{
    for (int i = 0; i < size; i++) {
        recordStatistic(&iaTimeHistogram[i]);
    }
}

}; // namespace
