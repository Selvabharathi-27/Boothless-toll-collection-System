# BOOTHLESS TOLL COLLECTION SYSTEM USING GPS AND ANPR CAMERA
IT IS A DYNAMIC PRICING TECHNIQUE

## OBJECTIVE
Deduct toll charges based on the actual distance traveled by the vehicle on the highway, avoiding fixed toll booths. This helps in dynamic tolling and ensures fair charges for short-distance users.

## COMPONENTS

1. GPS Module:
   Tracks the vehicle's real-time location and calculates the distance traveled on the highway.

3. ANPR (Automatic Number Plate Recognition) Camera:
   Detects and verifies vehicle identity at entry and exit points, ensuring accurate billing and security.

4. Database:
   Stores vehicle data, trip data, toll policies, and billing information.
## SYSTEM FLOW
1. Vehicle Entry:

When a vehicle enters a highway, an ANPR camera captures its license plate and verifies it with a central database.
GPS tracking is activated for this vehicle’s journey, marking the entry point coordinates.

2. Vehicle Journey:

Throughout the journey, the GPS system continuously monitors the vehicle’s location, speed, and distance traveled.
For accuracy, location data is sampled at regular intervals to calculate cumulative distance on the highway.

3. Vehicle Exit and Toll Calculation:

When the vehicle exits the highway, another ANPR camera captures its license plate at the exit point.
The GPS module records the final position, calculates the total highway distance traveled, and computes the toll amount based on a per-kilometer rate or other policies.

4. Toll Deduction:

The toll amount is automatically deducted from the vehicle owner's account or prepaid toll account.
A notification (email/SMS) is sent to the user with details of the toll charge and journey.

## DYNAMIC PRICING
Using a Deep Q-Network (DQN) for dynamic toll pricing allows toll rates to be adjusted based on time of day, traffic conditions, and vehicle type to optimize revenue and manage traffic flow efficiently.

1. DQN Model Setup:

State: Represents highway conditions

Time of Day: Morning, afternoon, evening.

Traffic Conditions: Light, moderate, heavy.

Vehicle Type: Car, truck, motorcycle.

Action: Adjust toll rate (increase, decrease, or keep constant).

Reward: Combines revenue and traffic flow; rewards lower congestion and balanced toll revenue.

2. Training and Execution:
 
Simulate Environment: Train DQN on scenarios reflecting various traffic and time conditions.

Reward Function:

Reward=α×Revenue−β×Congestion
where Revenue is toll income and Congestion measures traffic density.

Model Deployment: After training, deploy the DQN to make real-time toll adjustments based on current highway conditions.

3. Benefits:
Adaptive Pricing: Real-time, data-driven toll adjustments.

Revenue Optimization: Maximizes toll income while preventing congestion.

Congestion Management: Encourages off-peak travel through dynamic pricing.
DQN-based tolling promotes fair, efficient, and revenue-generating use of highways without fixed booths, streamlining toll collection and traffic flow management.

