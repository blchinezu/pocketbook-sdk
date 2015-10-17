# -*- cmake -*-

# - Find PBPN library
# Find the Inkview includes and library
# This module defines
# PBPN_INCLUDE_DIR, where to find json.h, etc.
# PBPN_LIBRARIES, the libraries needed to use jsoncpp.
# PBPN_FOUND, If false, do not try to use jsoncpp.

FIND_PATH(PBPN_INCLUDE_DIR pbpn/broker.h
/include
/usr/include
/usr/local/include
)

FIND_LIBRARY(PBPN_LIBRARIES
  NAMES libpbpn.so
  PATHS /lib /usr/lib /usr/local/lib
)

IF (PBPN_LIBRARIES AND PBPN_INCLUDE_DIR)
  SET(PBPN_FOUND "YES")
ELSE (PBPN_LIBRARIES AND PBPN_INCLUDE_DIR)
  SET(PBPN_FOUND "NO")
ENDIF (PBPN_LIBRARIES AND PBPN_INCLUDE_DIR)


IF (PBPN_FOUND)
  IF (NOT PBPN_FIND_QUIETLY)
    MESSAGE(STATUS "Found PBPN: ${PBPN_LIBRARIES}")
  ENDIF (NOT PBPN_FIND_QUIETLY)
ELSE (PBPN_FOUND)
  IF (PBPN_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could not find PBPN library")
  ENDIF (PBPN_FIND_REQUIRED)
ENDIF (PBPN_FOUND)
