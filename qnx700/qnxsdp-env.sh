#!/bin/bash
# This script is sets environment variables requires to use this version of QNX Software Development Platform 7.0
# from the command line. To use the script, you have to "source" it into your shell,
# source qnxsdp-env.sh
# if source command is not available use "." (dot) command instead
#
test "$BASH_SOURCE" = "" && echo "This script only can be run from bash" && return
SCRIPT_SOURCE=$BASH_SOURCE
test "$SCRIPT_SOURCE" = "$0" && echo "Script is being run, should be sourced" && exit 1

HOST_OS=$(uname -s)
SCRIPT_DIR=$(dirname "${SCRIPT_SOURCE}")
QNX_BASE=$(cd "${SCRIPT_DIR}"; pwd)
case "$HOST_OS" in
	Linux)
    QNX_HOST=$QNX_BASE/host/linux/x86_64
		;;
	Darwin)
    QNX_HOST=$QNX_BASE/host/darwin/x86_64
		;;
	*)
    QNX_HOST=$QNX_BASE/host/win64/x86_64
		;;
esac

QNX_TARGET=$QNX_BASE/target/qnx7
QNX_CONFIGURATION=$HOME/.qnx
MAKEFLAGS=-I$QNX_BASE/target/qnx7/usr/include
PATH=$QNX_HOST/usr/bin:$QNX_CONFIGURATION/bin:$QNX_BASE/jre/bin:$PATH

export QNX_TARGET QNX_HOST QNX_CONFIGURATION MAKEFLAGS PATH
unset PYTHONPATH

echo QNX_HOST=$QNX_HOST
echo QNX_TARGET=$QNX_TARGET
echo MAKEFLAGS=$MAKEFLAGS
