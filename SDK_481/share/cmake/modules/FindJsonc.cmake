# - Find JSON-C
# Find the JSON-C includes and library
# This module defines
# JSONC_INCLUDE_DIR, where to find json.h, etc.
# JSONC_LIBRARIES, the libraries needed to use jsonc.
# JSONC_FOUND, If false, do not try to use jsonc.
# also defined, but not for general use are
# JSONC_LIBRARY, where to find the jsonc library.

FIND_PATH(JSONC_INCLUDE_DIR json.h
    /usr/local/include/json-c
    /usr/include/json-c
)


FIND_LIBRARY(JSONC_LIBRARY
    NAMES json-c json
    PATHS /usr/lib /usr/local/lib
)

IF (JSONC_LIBRARY AND JSONC_INCLUDE_DIR)
    SET(JSONC_LIBRARIES ${JSONC_LIBRARY})
    SET(JSONC_FOUND "YES")
ELSE (JSONC_LIBRARY AND JSONC_INCLUDE_DIR)
    SET(JSONC_FOUND "NO")
ENDIF (JSONC_LIBRARY AND JSONC_INCLUDE_DIR)


IF (JSONC_FOUND)
    IF (NOT JSONC_FIND_QUIETLY)
	MESSAGE(STATUS "Found JSON-C: ${JSONC_LIBRARIES}")
    ENDIF (NOT JSONC_FIND_QUIETLY)
ELSE (JSONCPP_FOUND)
    IF (JSONC_FIND_REQUIRED)
	MESSAGE(FATAL_ERROR "Could not find JSON-C library")
    ENDIF (JSONC_FIND_REQUIRED)
ENDIF (JSONC_FOUND)
