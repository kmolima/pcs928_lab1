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

package lab1_prep.simulations;

import lab1_prep.Source;
import lab1_prep.Sink;

//
// Sample network, consisting of a source and a sink.
//
network SourceSink
{
    parameters:
        int num = 2;

        @display("bgb=204.12001,171.72");
    submodules:
        source[num]: Source {
            @display("p=182.25,140.13");
        }
        sink: Sink;

    connections:
        for i=0..num-1 {
            source[i].out --> sink.in[i];
        }
}
