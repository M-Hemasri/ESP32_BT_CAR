# ESP32 Bluetooth-Controlled Car

A simple Arduino project that uses an ESP32 DevKit, a TB6612FNG motor driver, and a servo motor to control a car wirelessly through Bluetooth. The ESP32 receives commands from a smartphone to control the DC motor's direction and the servo motor's steering angle.

## Hardware

- ESP32 DevKit board
- TB6612FNG motor driver
- DC motor
- Servo motor
- 2 \* 7.4 volts battery
- Jumper wires
- Robot car chassis and wheels
- Smartphone with a Bluetooth serial control application
- USB cable
- voltage regulator 

## Wiring

### TB6612FNG Motor Driver

- Connect **IN3** to ESP32 GPIO **26**.
- Connect **IN4** to ESP32 GPIO **27**.
- Connect **ENB** to ESP32 GPIO **33** for PWM speed control.
- Connect **VCC** to the ESP32's **3.3V** logic supply.
- Connect **GND** to ESP32 GND.
- Connect **VM** to a suitable motor power supply.
- Connect the DC motor to the driver's corresponding output terminals.

### Servo Motor

- Connect the servo's signal wire to ESP32 GPIO **13**.
- Connect the servo's power wire Esp32 VN pin
- Connect the servo's ground wire to GND.

### Esp32 POWER SUPPLY

- 7.4 volt battery is connected through voltage regulator
- voltage regulator GND to Esp32 GND
- voltage regulator 5v to Esp32 VN
- if you have 5v battery you can directly use them

NOTE : 5V is the max limit for ESP32 ,Do not connect the battery directly to ESP32 the chip will be fried

## Bluetooth Commands

The Bluetooth device name is **ESP32_car**.

| Command | Action                      |
| ------- | --------------------------- |
| `F`     | Moves the car forward       |
| `B`     | Moves the car backward      |
| `S`     | Stops the DC motor          |
| `L`     | Turns the servo toward 0°   |
| `R`     | Turns the servo toward 170° |
| `C`     | Centers the servo at 90°    |

## Upload

1. Open the sketch in the Arduino IDE.
2. Install the **ESP32Servo** library if it is not already installed.
3. Select your ESP32 board from the **Tools** menu.
4. Select the appropriate port.
5. Click **Verify** to compile the code.
6. Click **Upload** to upload the sketch.
7. Pair your smartphone with **ESP32_car** using a compatible Bluetooth serial application.
8. Send the commands listed above to control the car.

## Working Principle

1. The ESP32 initializes Bluetooth with the name `ESP32_car`.
2. The servo initializes at the center position of 90°.
3. The TB6612FNG motor driver controls the DC motor's direction and speed.
4. Bluetooth commands control forward movement, backward movement, and stopping.
5. The `L`, `R`, and `C` commands adjust the servo's steering position.
6. PWM controls the DC motor speed using an 8-bit resolution and a duty-cycle value of 255.

## Expected Result

The car responds to Bluetooth commands from a smartphone. The DC motor moves forward or backward, stops when commanded, and the servo changes its steering position.

## Notes

- The motor speed is set to `255`, which represents the maximum duty-cycle value for 8-bit PWM.
- The servo moves in 10° increments with a 20-millisecond delay between commands.
- The current code controls one DC motor channel and one servo motor.
- The TB6612FNG's **STBY** pin must be driven HIGH for the motor driver to operate. Connect it to an appropriate logic HIGH or control it with an ESP32 GPIO.
- Use a suitable external power supply for the motors rather than powering them directly from the ESP32's 3.3V pin.
