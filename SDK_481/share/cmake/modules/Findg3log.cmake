# -*- cmake -*-

# - Find G3LOG library
# Find the g3log includes and library
# This module defines
# G3LOG_INCLUDE_DIR, where to find g2log.hpp, etc.
# G3LOG_LIBRARIES, the libraries needed to use libg3logger_shared.so.
# G3LOG_FOUND, If false, do not try to use g3log.

FIND_PATH(G3LOG_INCLUDE_DIR g3log/g2log.hpp
/include
/usr/include
/usr/local/include
)

FIND_LIBRARY(G3LOG_LIBRARIES
  NAMES libg3logger_shared.so
  PATHS /lib /usr/lib /usr/local/lib
)

IF (G3LOG_LIBRARIES AND G3LOG_INCLUDE_DIR)
  SET(G3LOG_FOUND "YES")
ELSE (G3LOG_LIBRARIES AND G3LOG_INCLUDE_DIR)
  SET(G3LOG_FOUND "NO")
ENDIF (G3LOG_LIBRARIES AND G3LOG_INCLUDE_DIR)

IF (G3LOG_FOUND)
  IF (NOT G3LOG_FIND_QUIETLY)
    MESSAGE(STATUS "Found G3LOG: ${G3LOG_LIBRARIES}")
  ENDIF (NOT G3LOG_FIND_QUIETLY)
ELSE (G3LOG_FOUND)
  IF (G3LOG_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could not find G3LOG library")
  ENDIF (G3LOG_FIND_REQUIRED)
ENDIF (G3LOG_FOUND)
