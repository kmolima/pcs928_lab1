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

package assignment1.simulations;

import assignment1.Source;
import assignment1.Sink;


// Delay channel
channel DatarateChannel2 extends ned.DatarateChannel
    {
        // double distance @unit(m);
        // delay = this.distance / 200000km * 1s;
        delay=0.05s;
        per=1e-3;
    }

//
// Sample network, consisting of a source and a sink.
//
network SourceSink
{

    parameters:
        int num = 10;
        @display("bgb=250,200");
    submodules:
        source[num]: Source {
        }
        sink: Sink;
    connections:
        for i=0..num-1 {
            source[i].out --> DatarateChannel2 --> sink.in[i]; //
        }

}
