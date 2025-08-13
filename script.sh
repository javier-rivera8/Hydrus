#!/bin/bash

echo "Starting Hydrus movement sequence..."
echo "Moving forward for 3 seconds..."

# Move forward - activate front thrusters (thrusters 2 and 3 based on your code)
# Using 1600 PWM for forward motion
rostopic pub /hydrus/thruster_1 std_msgs/Int16 "data: 1600" &
rostopic pub /hydrus/thruster_2 std_msgs/Int16 "data: 1600" &
rostopic pub /hydrus/thruster_3 std_msgs/Int16 "data: 1600" &
rostopic pub /hydrus/thruster_4 std_msgs/Int16 "data: 1600" &

# Wait for 3 seconds
sleep 3

echo "Stopping all thrusters..."

# Stop all thrusters - set to neutral (1500 PWM)
rostopic pub /hydrus/thruster_1 std_msgs/Int16 "data: 1500" &
rostopic pub /hydrus/thruster_2 std_msgs/Int16 "data: 1500" &
rostopic pub /hydrus/thruster_3 std_msgs/Int16 "data: 1500" &
rostopic pub /hydrus/thruster_4 std_msgs/Int16 "data: 1500" &
rostopic pub /hydrus/thruster_5 std_msgs/Int16 "data: 1500" &
rostopic pub /hydrus/thruster_6 std_msgs/Int16 "data: 1500" &
rostopic pub /hydrus/thruster_7 std_msgs/Int16 "data: 1500" &
rostopic pub /hydrus/thruster_8 std_msgs/Int16 "data: 1500" &

# Wait a moment for commands to be processed
sleep 1

echo "Movement sequence complete!"