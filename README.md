<div style="text-align: justify">

# CIMPLC
The CIMPLC is a low-cost, open source high pin-count programmable logic controller, designed as a project while studying at the University of Politehnica, Bucharest. It is designed as a replacement for the aging hardware found inside the CIM ( Computer Integrated Manufacturing ) located in our faculty.

# The software
The firmware is based on FreeRTOS, offering vast functionality. The stand-out feature of this design is the implementation of the concept of vPLC, or virtual PLC. It also implements a fast optimizing compiler to translate IEC 61131-3 instructions to bytecode which can be loaded faster from EEPROM.

Fast, predictible code execution is the goal of every system, and the CIMPLC is no exception. The end-goal of the code is to be implemented according to the most rigorous standards. In its final version, code will be written following the MISRA standard.
## Features [WIP]

### WiFi programmability and monitoring
The software allows both firmware updates over the air (OTA), as well as binary uploads for the PLC.

Furthermore, the status of the PLC can be monitored at any time by the use of a web interface. Pin status, direction, and code execution can be accessed, as well as whatever logs may be produced by the code.

### vPLC
vPLC, short for Virtual PLC, simplifies the concept of a PLC to its simplest form: a finite state machine. This allows for the creation of multiple threads of execution, each with access to I/Os and interfaces, while having distinct memory spaces, program stacks and counters. This allows for higher flexibility of the system.

### WASM
In order to run Structured Text code on the PLC, we need some way to compile it. In order to do that, a parser is used that turns Structured Text into Web Assembly text (.wat), which can then be compiled and run.
  
Interpreting Web Assembly is done using the wasm3 module (https://github.com/wasm3/wasm3)
  
Structured Text parser: https://github.com/mihaicostin34/ST_Parser  
## Limitations

???
## Contributors

Mihai Costin, for the WASM magic [@mihaicostin34](https://github.com/mihaicostin34)
## License

This project is licensed under [GNU AGPLv3](https://choosealicense.com/licenses/agpl-3.0/).
</div>
