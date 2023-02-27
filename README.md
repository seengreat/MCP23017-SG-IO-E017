MCP23017-SG-IO-E017 from seengreat:www.seengreat.com
 =======================================
# Instructions
## 1.1、Overview
This product adopts I2C interface to realize 16 I/O port expansion. Support for Raspberry Pi Zero/Zero W/Zero WH/2B/3B/3B+/4B etc models as well as Arduino and STM32. We provide C and Python demo codes for the Raspberry Pi, as well as Arduino and STM32 demo codes, that can implement input testing, output testing, and interrupt testing.<br>
## 1.2、Parameters
|parameter	|SG-IO-E017	|SG-IO-E017-A|
|----------------------|----------------------|----------------|
|Size	|45mm(Length)*25mm(width)	|34.5mm(Length)*25mm(width)|
|Control Chip	|MCP23017	|MCP23017|
|Signal interface	|I2C	|I2C|
|Supply voltage	|3.3V/5V	|3.3V/5V|
|Expansion I/O 	|16	|16|
|Interrupt pin	|INTA、INTB	|INTA、INTB|

# Usage
This module demo codes sets the PA port (PA0～PA7) as the output and cycles the high and low levels at an interval of 1 second. The PB port (PB0～PB7) is set as the input. In addition, it is configured that when the level of any pin of the PB port changes, an interrupt is generated through the INTB pin. At this time, the level of the PB port is read.<br>
## 2.1、Raspberry Pi demo codes usage
### 2.1.1、Hardware interface configuration description
The module with Raspberry Pi motherboard wiring is defined in the following table:<br>

|PIN	|Pin Function	|Raspberry Pi|
|----------------------|-----------------------|----------------------|
|VCC	|Power supply positive(3.3V/5V)	|3.3V|
|GND	|Power supply ground	|GND|
|SDA	|I2C data line	|SDA1|
|SCL	|I2C clock line	|SCL1|
|INTA 	|PA port interrupt pin	|P0(wiringpi number)|
|INTB	|PB port interrupt pin	|P1(wiringpi number)|

Table2-1 Definition of SG-IO-E017 and Raspberry Pi pin<br>
The Raspberry Pi is connected to the module, and the wiring diagram is shown in Table2-1.<br>
### 2.1.2、Demo Codes Usage
#### 2.1.2.1、Wiringpi library installation
sudo apt-get install wiringpi<br>

wget https://project-downloads.drogon.net/wiringpi-latest.deb  #<br>
Version 4B upgrade of Raspberry Pi<br>
sudo dpkg -i wiringpi-latest.deb<br>
gpio -v #<br>
If version 2.52 appears, the installation is successful <br>
#For the Bullseye branch system, use the following command:<br>
git clone https://github.com/WiringPi/WiringPi<br>
cd WiringPi<br>
./build<br>
gpio -v<br>
#Running gpio - v will result in version 2.70. If it does not appear, it indicates an installation error<br>
If the error prompt "ImportError: No module named 'wiringpi'" appears when running the python version of the sample program, run the following command<br>
#For Python 2. x version <br>
pip install wiringpi<br>
#For Python version 3. X<br>
pip3 install wiringpi<br>
Note: If the installation fails, you can try the following compilation and installation:<br>
git clone --recursive https://github.com/WiringPi/WiringPi-Python.git<br>
Note: The -- recursive option can automatically pull the submodule, otherwise you need to download it manually.<br>
Enter the WiringPi Python folder you just downloaded, enter the following <br>
command, compile and install:<br>
#For Python 2. x version<br>
sudo python setup.py install<br>
#For Python version 3. X<br>
sudo python3 setup.py install<br>
If error occurs,At this time, enter the command sudo apt install swig to install swig. After that, compile and install sudo python3 setup.py install. If a message similar to the following appears, the installation is successful.<br>
#### 2.1.2.2、Open I2C interface
sudo raspi-config<br>
Enable I2C interface:<br>
I nterfacing Options -> I2C -> Yes<br>
Restart the device.<br>
sudo reboot<br>
Run the command to check whether I2C is started.<br>
lsmod<br>
If i2c_bcm2835 and spi_bcm2835 are displayed, it means I2C module is started.<br>
Install the i2c-tools tool to confirm<br>
sudo apt-get install i2c-tools<br>
View connected I2C devices<br>
i2cdetect -y 1<br>
Check the address and indicate that the I/O expansion board and the Raspberry Pi are successfully connected, and the DIP switch is connected to the high level by default, and the displayed address is 0X27;<br>
#### 2.1.2.3、Installation of Python libraries
The demo codes uses the python 3 environment. To run the python sample program, you need to install smbus:
sudo apt-get install -y python-smbus<br>
#### 2.1.2.4、C Demo Codes
Open the demo codes/raspberry_pi/c directory<br>
sudo make clean<br>
sudo make<br>
sudo ./main<br>
Connect the expansion board according to the demo codes description. After running the program, the output result of the Raspberry Pi terminal is as follows:; "Port B: ff" means that all the input pins of the PB port of the module are high by default (0xff: 1111111); "Port A" refers to PA0～PA7 pins, "port A output high" refers to all PA port pins outputting high level, "port A output low" refers to all PA port pins outputting low level, and the module PA port output pins cyclically switch high and low levels at an interval of 1 second. Users can also connect PA0～PA7 to LEDs, and it can be observed that LEDs are flashing constantly. At this time, the output test is normal;<br>
Connect the PB0 port to the GND with a jumper, and then trigger the interrupt on the INTB pin. The Raspberry Pi terminal outputs "portB: fe", that is, the input level of the PB port changes from the original 0xff (11111111) to 0xfe (11111110).<br>
#### 2.1.2.5、python Demo Codes
Open the demo codes\raspberry_pi\python directory<br>
python3 mcp23017.py<br>
The demo codes of Python version is similar to that of C language. <br>
## 2.2、Arduino Demo Codes Usage
### 2.2.1、Wiring instructions
The wiring between the module and Arduino pins is shown in the following table:<br>
|PIN	|Pin function	|Arduino|
|-----------|----------------------|---------|
|VCC	|Power supply positive(3.3V/5V)	|5V|
|GND	|Power supply ground	GND|
|SDA	|I2C data line	|SDA|
|SCL	|I2C clock line	|SCL|
|INTA	|PA port interrupt pin	|D2|
|INTB	|PB port interrupt pin	|D3|<br>

Table2-2 Definition of SG-IO-E017 and Arduino <br>
### 2.2.2、Demo codes usage
Open the project file demo codes\Arduino\mcp23017\mcp23017.ino with the Arduino IED, click Verify, and upload it to the development board after verification.<br>
Click the tool, open the serial port monitor, set the baud rate to 115200, and observe the data changes.<br>
## 2.3、STM32 Demo Codes Usage
### 2.3.1、Wiring instructions
|PIN	|Pin function	|STM32 |
|-----------|----------------------|--------|
|VCC	|Power supply positive(3.3V/5V) |3.3V|
|GND	|Power supply ground	|GND|
|SDA	|I2C data line	|PB11|
|SCL	|I2C clock line	|PB10|
|INTA	|PA port interrupt pin	|PB3|
|INTB	|PB port interrupt pin	|PB4|<br>

Table2-3 Definition of SG-IO-E017 and STM32 <br>
### 2.3.2、Demo codes usage
Open the main. Uvprojx project file in the directory demo codes\STM32\USER with Keil_Vision5 software, and connect the module with STM32 according to the above table; The program is downloaded to the STM32 development board after being compiled without errors;<br>
The debugging information output serial port in the demo codes is USART1, where PA9 is Tx and PA10 is Rx; After connecting the cable, open the Serial Port Debugging Assistant, select the serial port number, adjust the baud rate to 115200, click "Open".<br>
__Thank you for choosing the products of Shengui Technology Co.,Ltd. For more details about this product, please visit:
www.seengreat.com__

