# Task: Sensor Data Synchronization 🤖

## Summary
Modified version of the robot core that uses **Hardware Interrupts** to ensure that data from LiDAR and Ultrasonic sensors are captured at the same temporal window.

## How it works
1. **Interrupts:** Used on Pin 2 & 3 to capture timestamps (`micros()`) immediately.
2. **Synchronization Window:** The system only processes data if the difference between sensor triggers is less than **10ms**.
3. **Logic:** Combines (Fuses) LiDAR and Ultrasonic readings to make safety decisions.

## Files
- `Sensor_Sync_Project.ino`: The main integrated logic.