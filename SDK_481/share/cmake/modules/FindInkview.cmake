# -*- cmake -*-

# - Find Inkview library
# Find the Inkview includes and library
# This module defines
# INKVIEW_INCLUDE_DIR, where to find json.h, etc.
# INKVIEW_LIBRARIES, the libraries needed to use jsoncpp.
# INKVIEW_FOUND, If false, do not try to use jsoncpp.

FIND_PATH(INKVIEW_INCLUDE_DIR inkview.h
/include
/usr/include
/usr/local/include
)

FIND_LIBRARY(INKVIEW_LIBRARIES
  NAMES libinkview.so
  PATHS /lib /usr/lib /usr/local/lib
)

IF (INKVIEW_LIBRARIES AND INKVIEW_INCLUDE_DIR)
  SET(INKVIEW_FOUND "YES")
ELSE (INKVIEW_LIBRARIES AND INKVIEW_INCLUDE_DIR)
  SET(INKVIEW_FOUND "NO")
ENDIF (INKVIEW_LIBRARIES AND INKVIEW_INCLUDE_DIR)


IF (INKVIEW_FOUND)
  IF (NOT INKVIEW_FIND_QUIETLY)
    MESSAGE(STATUS "Found Inkview: ${INKVIEW_LIBRARIES}")
  ENDIF (NOT INKVIEW_FIND_QUIETLY)
ELSE (INKVIEW_FOUND)
  IF (INKVIEW_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could not find Inkview library")
  ENDIF (INKVIEW_FIND_REQUIRED)
ENDIF (INKVIEW_FOUND)
