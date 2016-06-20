#!/bin/bash

function startall()
{
	echo "启动所有服务"
	./bin/loginServer_d -syskey 11
	./bin/superServer_d -syskey 11
	./bin/centerServer_d -syskey 11
	./bin/dataServer_d -syskey 11
	./bin/gameServer_d -syskey 11
	./bin/gateServer_d -syskey 11
}

function stopall()
{
	echo "关闭所有服务"
	./bin/server_d -k 11 -c "stop all; exit;"
}

case "$1" in
"startall")
	startall;
	;;
"stopall")
	stopall;
	;;
*)
	echo "apppro startall	启动所有服务"
	echo "apppro stopall	关闭所有服务"
	;;
esac






