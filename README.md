# Soccer-Lightweight-2025

## Serial Communication in IRRing

- `Serial1` is used for communication because we work with a **Teensy 4.1**.  
- This should be changed depending on the microcontroller being used.  
- The baud rate is set to `115200`.  
- Ensure no other device uses `Serial1` simultaneously to avoid conflicts.
### **Pixy Camera Configuration**
- When setting up the **Pixy camera**, make sure to select the correct communication interface.  
- In our case, we are using **I2C**, but we initially had issues because it was set to **Serial** by default.  
- Double-check the **PixyMon settings** or your initialization code to ensure the correct mode is selected.  
