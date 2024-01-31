# ETHERCAT INTRODUCTION
- Master is with standart ethernet port. Ethercat slave devices are with asic and 32-bit mcu.
- Ethercat supports ring redundancy
- Slave Stack Code is freely available.
- EtherCAT uses less RAM and RAM size compare to TCP/IP
- EtherCAT includes distributed clocks for precise synchronization
- ENI -> EtherCAT Network Information File(.xml)
- ESI -> EtherCAT Slave Information File(.xml)
- In typical EtherCAT application, There is Application MCU, ESC(EtherCAT Slave Controller), and EEPROM for configuration data.
- Two type of protocol used with EtherCAT
    1. SDO -> Service Data Object
    2. PDO -> Process Data Object
- Each device has 64K memory but its not mandatory to implement all of them
    1. 4k for local control of device.
    2. 60k dual pool memory for process memory.

- LAN9252
    1. Supports copper & fiber interface.
    2. It can communicate with host mcu via spi, qspi or paralel 8/16bit.

- LAN9253 is more applicable for more performant devices compare to LAN9252
- Bechoff provides EL9800 with LAN9254
- LAN9255 has cortex m with same die with ESC.

- EVB-LAN9253 has 1 LAN9253 and cortex M4 controller.