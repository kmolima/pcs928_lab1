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

#ifndef __ASSIGNMENT1_SINK_H
#define __ASSIGNMENT1_SINK_H

#include <omnetpp.h>

using namespace omnetpp;

namespace assignment1 {

/**
 * Message sink; see NED file for more info.
 */
class Sink : public cSimpleModule
{
  private:
    // state
    simtime_t lastArrival[30];
    int arrivalsVector[30];

    // statistics
    cHistogram iaTimeHistogram[30];
    cOutVector outOfOrderVector[30];
    cOutVector difference[30];

    //number of nodes  - NED parameter
    int size;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

}; // namespace

#endif
