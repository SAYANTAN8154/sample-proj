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

package org.car2x.veins.modules.application.traci;

import org.car2x.veins.modules.application.traci.TraCIDemo11p;

simple SpoofingAttackModule extends TraCIDemo11p {
    parameters:
        double spoofingInterval @unit(s) = default(1s);  // Interval for sending spoofed messages
        string spoofedId = default("fake_vehicle_id");
        double spoofedX = default(1000);  // X-coordinate for spoofed position
        double spoofedY = default(1000);  // Y-coordinate for spoofed position
}
