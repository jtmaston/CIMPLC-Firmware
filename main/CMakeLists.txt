file(GLOB U_MODULES "modules/*")
message("${USER_INCLUDES}")

idf_component_register( SRCS

    modules/REPL.cpp
    modules/networking.cpp
    modules/filesystem.cpp
    modules/twai.cpp
    modules/uart.cpp
    modules/eeprom/main/eeprom.cpp
    modules/eeprom/main/include/eeprom.hpp

    modules/ioctrl/main/pca9555.cpp
    modules/ioctrl/main/include/pca9555.hpp
    modules/IOController.cpp

    main.cpp

    EMBED_TXTFILES interface/main.html
INCLUDE_DIRS "." "modules/ioctrl/main/include" "modules/eeprom/main/include" "modules")
