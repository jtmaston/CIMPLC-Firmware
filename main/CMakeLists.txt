idf_component_register( SRCS

# Firmware-specific modules
    modules/REPL.cpp
    modules/networking.cpp
    modules/filesystem.cpp
    modules/twai.cpp
    modules/uart.cpp
    modules/IOController.cpp

# Driver sources
    modules/eeprom/main/eeprom.cpp
    modules/ioctrl/main/src/pca9555.cpp

# Executable sources
    main.cpp

# Text files
    EMBED_TXTFILES interface/main.html

INCLUDE_DIRS "." "modules/ioctrl/main/include" "modules/eeprom/main/include" "modules/")