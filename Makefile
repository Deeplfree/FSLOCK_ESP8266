#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#
#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#
PROJECT_NAME := FSLOCK
EXTRA_COMPONENT_DIRS += $(PROJECT_PATH)/../../../
EXTRA_COMPONENT_DIRS += $(IDF_PATH)/examples/common_components/protocol_examples_common

include $(IDF_PATH)/make/project.mk

