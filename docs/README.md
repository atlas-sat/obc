# OBC 8-bit AVR Test Program

This repo contains test program that simulates an OBC sender node using the CubeSat Space Protocol (CSP).

The program has 2 FreeRTOS tasks - one simulates a background task to light up an LED and the other sends CSP ping packets to a receiver periodically.

## About Test Programs' Setup


The diagram below shows the how the OBC and Subsystem interacts by the CSP protocol.

```
+---------------+                                   +---------------+
|               |                 CSP               |               |
|      OBC      |-----------------------------------|   Subsystem   |
|               |               I2C Bus             |               |
+---------------+                                   +---------------+
     Addr: 1                                             Addr: 8     
```

The OBC will have a CSP address of 1, while the Subsystem will have a CSP address of 8.

The OBC will establish a socket connection to the Subsystem via the subsystem's CSP address and send the Subsystem data packets to specific ports when it wishes to initiate a communication.

In response, the Subsystem will set up a socket to listen to any incoming connections or data packets from any other subsystems (i.e. the OBC here).

## Expected Output

The following diagram shows the expected output when running both the OBC and Subsystem test programs, while connecting the two hardware subsystems via an I2C bus protocol.

Wiring:

![I2C bus wiring](wiring.jpg)

OBC output: 

![OBC output](Capture_obc.PNG)

Subsystem output: 

![Subsystem output](Capture_subsys.PNG)