file(GLOB U_MODULES "modules/*")
message("${USER_INCLUDES}")

idf_component_register( SRCS

    modules/REPL.cpp
    modules/networking.cpp
    modules/http.cpp
    modules/gps.cpp
    modules/filesystem.cpp
    modules/twai.cpp
    init/serialInit.cpp
    main.cpp

    EMBED_TXTFILES interface/main.html
    EMBED_TXTFILES interface/upload.html
INCLUDE_DIRS ".")
