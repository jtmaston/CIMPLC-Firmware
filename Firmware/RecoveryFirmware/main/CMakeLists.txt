file(GLOB U_MODULES "modules/*")
message("${USER_INCLUDES}")

idf_component_register( SRCS

    main.cpp

    EMBED_TXTFILES upload.html
INCLUDE_DIRS ".")
