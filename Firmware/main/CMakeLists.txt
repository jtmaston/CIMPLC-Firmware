file(GLOB U_MODULES "modules/*")
message("${USER_INCLUDES}")

idf_component_register( SRCS

    modules/REPL.cpp
    modules/networking.cpp
    modules/filesystem.cpp
    modules/twai.cpp
    modules/uart.cpp
    modules/eeprom/main/eeprom.cpp
    main.cpp

    EMBED_TXTFILES interface/main.html
INCLUDE_DIRS "." "modules" "modules/eeprom/main/include")
