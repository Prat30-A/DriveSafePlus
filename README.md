# DriveSafePlus 🚗🔒  
A real-time STM32-based driving behavior monitoring system.  

This project uses an LCD, keypad, potentiometer, and temperature sensing to monitor driver behavior (`AGGRESSIVE`, `DROWSY`, `OVERHEATED`, `SAFE`).  
Feedback is provided through the LCD + buzzer, and debug info is sent via UART.  

---

## 📌 Hardware Connections  

### 🔹 LCD (16x2, 4-bit mode – no I²C)  
| LCD Pin | STM32 Pin | Notes |
|---------|-----------|-------|
| RS      | **PC10**  | Register Select |
| RW      | **PA15**  | Read/Write |
| EN      | **PB7**   | Enable |
| D4      | **PC11**  | Data line |
| D5      | **PC12**  | Data line |
| D6      | **PC2**  | Data line |
| D7      | **PC3**  | Data line |

✅ LCD initialized using pre-downloaded HAL driver (`LCD1602.h`).  

---

### 🔹 Potentiometer (Speed Input via ADC)  
- Connected to **PA0** (ADC Channel 0)  
- ADC configured in **polling mode**  
- Resolution: **12-bit** (0–4095 range)  
- Used to simulate speed variations  

---

### 🔹 Temperature Sensor (Analog Input)  
- Connected to **PA1** (ADC input)  
- Logic behavior:  
  - `< 0°C → Extreme Cold → Restrict speed`  
  - `20–40°C → Normal operation`  
  - `> 60°C → Extreme Heat → Restrict speed`  

---

### 🔹 UART (Debug Output)  
- **USART2** enabled  
- Output through **USB COM3**  
- Verified using **PuTTY** (asynchronous transmission)  

---

### 🔹 Keypad (4x4 Matrix)  
| Function         | STM32 Pin |
|------------------|-----------|
| FSM Control      | **PC8**   |
| IDLE State       | **PB5**   |
| USER Input       | **PA12**  |
| Driving Session  | **PB12**  |
| Session Confirm  | **PB13**  |

✅ Used for **Driver ID login** and **mode/session control**.  

---

## ⚙️ Software Behavior  
- FSM manages driving states: `SAFE`, `AGGRESSIVE`, `DROWSY`, `OVERHEATED`.  
- LCD continuously updates driver state.  
- Keypad provides **multi-user input (Driver ID + session selection)**.  
- UART sends debugging info to PC.  
- Potentiometer + temperature inputs simulate **real driving conditions**.  

---

## 🚀 Future Extensions  
- Add cloud sync (via Python UART → Firebase/Google Sheets).  
- Integrate buzzer alerts for unsafe states.  
- Extend FSM for additional driving conditions.  
