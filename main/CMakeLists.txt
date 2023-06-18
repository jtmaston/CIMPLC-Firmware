file(GLOB U_MODULES "modules/*")
message("${USER_INCLUDES}")

idf_component_register( SRCS

    modules/REPL.cpp
    modules/networking.cpp
    modules/filesystem.cpp
    modules/twai.cpp
    modules/uart.cpp
    modules/IOController.cpp
    modules/eeprom/main/eeprom.cpp
    modules/ioctrl/main/pca9555.cpp

    main.cpp

    EMBED_TXTFILES interface/main.html
INCLUDE_DIRS "." "modules" "modules/eeprom/main/include")
