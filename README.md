
# Project Title

The project centers on crafting a safety headgear tailored for underground tunnel workers. Key features include real-time location tracking and monitoring of temperature, pressure, and air quality. The primary goal is to enhance worker safety in the face of potential hazards like temperature fluctuations, pressure changes, or exposure to gases during tunneling incidents. Wireless communication facilitates connectivity between tunnel workers and the external world, with GPS technology ensuring precise location tracking for emergency response. The design prioritizes portability, cost-effectiveness, and durability to meet the specific needs of underground tunnel workers.

<p float="left">
  <img src="https://static.vecteezy.com/system/resources/previews/012/697/300/original/3d-c-programming-language-logo-free-png.png" width="90" height="90">
  <img src="https://brandslogos.com/wp-content/uploads/images/large/arduino-logo-1.png" width="70" height="70" style="margin-left: 10px;">
</p>

**Overview**

This project comprises two primary components: the Helmet Unit and the Control Unit. Arduino is the cornerstone for developing our mining tracking and safety helmet system. The key objectives involve acquiring real-time data such as location, temperature, air quality, and pressure. A robust communication system has been established between the underground miners' safety helmets and the main control unit situated on the ground surface. The programming for the entire system is done using the C programming language.

The Control Unit predominantly functions as a receiver, while the Helmet Units primarily act as transmitters, relaying location data and other pertinent information. Notably, all three units in the system can operate interchangeably as both transmitters and receivers, showcasing a versatile communication network. This GitHub repository provides the codebase and documentation for seamless understanding and utilization of the project.

![Screenshot 2023-12-16 221853](https://github.com/rv0fficial/Worker-Safety-Headgear/assets/147927710/35e82e96-8352-42c5-9354-a9ad516fff96)
![Screenshot 2023-12-16 221859](https://github.com/rv0fficial/Worker-Safety-Headgear/assets/147927710/aae75f61-da78-45c9-bf26-7f5fe189941b)

**Technologies, Software, and Main Hardware Components Used**

**RF Wireless Technology**

Utilized for wireless communication, RF technology operates in the electromagnetic spectrum's radio wave frequencies, providing communication channels without the need for an air-based medium.

**Arduino IDE**

The Arduino Integrated Development Environment (IDE) is the software platform for programming and uploading code to the Arduino hardware. It facilitates communication and programming of the Arduino UNO microcontroller.

<img src="https://static.javatpoint.com/tutorial/arduino/images/arduino-ide.png" width="506" height="414">

**NRF24L01+PA+LNA 2.4G Wireless Transceiver Module with SMA Antenna**

The NRF24L01 module facilitates wireless communication between the reporting and helmet sections, operating at 2.4 GHz ISM Band with a baud rate of 250 kbps - 2 Mbps. It allows for easy data transmission and reception.

<img src="https://www.twinschip.com/image/catalog/Products%20Twins%20Chip%20Store%202020/Shield%20Modules/Wireless%20Modules/NRF24L01%20Wireless%202.4GHz%20Transceiver%20Antenna%201100%20Metres%20/NRF24L01%2BPA-LNA%20SMA%20Wireless%202.4GHz%20Transceiver%20Antenna%201100%20Metres%20-Twins%20Chip.jpg" width="384" height="258">

**Arduino UNO Microcontroller**

The Arduino UNO R3 microcontroller, equipped with 14 digital pins, PWM outputs, and six analog inputs, serves as the project's control unit. It features a 16 MHz crystal oscillator, USB port, power jack, ICSP header, and a reset button.

<img src="https://blogger.googleusercontent.com/img/b/R29vZ2xl/AVvXsEgHCfrINVkq9FHGd516DJyBRB5jPHe_Zf-_kiwrNotW_RBjv-jvSQ_C49Dih98iUtHZDkmwGLxhLbUcMX9mRWcteG2P943QoTO2QhTuQ29zXZyY2zYzjtGNg7uxtlbJnXPToBOWArDhGiVw1IpqGakKiFrK5cqCW7th0pr6x9Fy2tiC_xKHiKeVm-R-J1v3/s1011/Arduino%20uno%20board.png" width="506" height="278">

**MQ135 Air Quality Gas Sensor Module**

The project incorporates the MQ-135 digital sensor to measure air quality in parts per million (PPM). This sensor detects various gases in the atmosphere, signaling when gas levels exceed predefined thresholds.

<img src="https://cdn.shopify.com/s/files/1/0527/2692/3444/files/MQ135_-_Air_Quality_Control_Gas_Sensor_Module.jpg?v=1631792819" width="629" height="287">

**MPU-6050 Triple Axis Analog Accelerometer Gyroscope Module**

The MPU6050 sensor module, a 6-axis motion tracking system, includes a 3-axis gyroscope, a 3-axis accelerometer, and a temperature sensor. It communicates via an I2C bus interface and provides accurate temperature readings.

<img src="https://grobotronics.com/images/detailed/106/gy521_01_lrg_grobo.jpg" width="440" height="285">

**BMP180 Pressure Sensor**

The BMP180 high-precision sensor measures barometric pressure digitally, accounting for temperature variations. It is utilized to monitor pressure in underground tunnels.

<img src="https://www.rhydolabz.com/wiki/wp-content/uploads/combined.jpg" width="566" height="221">

**NEO-7M GPS Module with Antenna**

The NEO-7M GPS module employs Ublox technology and a built-in active GPS antenna. It provides accurate positioning data, enhancing performance with multirotor control platforms.

<img src="https://www.orbit-dz.com/wp-content/uploads/2022/12/H41dd931b5c434fcb8e83cbd584e2117fR.jpg" width="320" height="320">

**16x4 LCD Display**

The 16x4 LCD display is employed to showcase outputs from oxygen, carbon dioxide, and temperature sensors. It is chosen for its programmability, ability to display custom characters, and cost-effectiveness.

<img src="https://m.media-amazon.com/images/I/41iRb1AmRsL._AC_UF1000,1000_QL80_.jpg" width="500" height="350">

**I2C module**

Leveraging the I2C module simplifies LCD display control, streamlining communication through a two-wire interface. This method enhances efficiency in managing and presenting information on the LCD screen with reduced wiring complexity.

<img src="https://i0.wp.com/microdigisoft.com/blogadmin/images/Arduino/i2clcd/pin1.png?ssl=1">

**Power Source**

To ensure continuous operation underground, rechargeable batteries and power banks with a capacity of 10,000mAh and 5V are used. The system can run for approximately 27 hours, providing an alternative power source in case of a power failure.

## Hardware Implementation

**Helmet Unit Component Connections to Arduino:**

- **nRF24L01 Module:**
  - CE (Chip Enable): 9
  - CSN (Chip Select Not): 10
  - SCK (Serial Clock): 13
  - MO (Master Out): 11
  - MI (Master In): 12

- **MPU6050 Module:**
  - SCL (Serial Clock Line): A5
  - SDA (Serial Data Line): A4

- **MQ135 Sensor:**
  - Analog Output (A0): A0

- **Neo-7M GPS Module:**
  - TXD (Transmit Data): 4
  - RXD (Receive Data): 3

- **BMP180 Sensor:**
  - SDA (Serial Data Line): SDA
  - SCL (Serial Clock Line): SCL

**Control Unit Component Connections to Arduino:**

- **nRF24L01 Module:**
  - CE (Chip Enable): 9
  - CSN (Chip Select Not): 10
  - SCK (Serial Clock): 13
  - MO (Master Out): 11
  - MI (Master In): 12

- **16x4 LCD Display:**
  - SDA (Serial Data Line): A4
  - SCL (Serial Clock Line): A5

## Demo

Insert gif or link to demo

