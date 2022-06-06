QCONFIG_BASEDIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
include $(QNX_HOST)/etc/host.mk
include $(QCONFIG_BASEDIR)/qconf-$(HOST_OS).mk
