################################################################
#公共参数
################################################################
include common.inc

################################################################
#编译参数设置
################################################################
include ../template/makecmd.inc

ProjectName=dataServer

#输入cpp目录
CPP_ROOT_DIR=$(BASE_SRC_DIR)/$(ProjectName)

# 输出中间文件目录
DEBUG_OUT_DIR=$(BASE_OBJ_DIR)/$(ProjectName)/Debug
RELEASE_OUT_DIR=$(BASE_OBJ_DIR)/$(ProjectName)/Release

#输出目标目录
OUT_TARGET_DIR=$(OUT_LIB_DIR)

# 包含头文件目录
DEBUG_INCS=$(INC_DIR) $(TOOLS_DIR) $(CPP_ROOT_DIR) 
RELEASE_INCS=$(INC_DIR) $(TOOLS_DIR) $(CPP_ROOT_DIR)

# 宏定义
DEBUG_DEFS=
RELEASE_DEFS=

# 连接库
DEBUG_LIBS=masterSystem_debug rankSystem_debug friendSystem_debug activitySystem_debug shopSystem_debug taskSystem_debug prizeSystem_debug sceneSystem_debug petSystem_debug mailSystem_debug equipSystem_debug skillSystem_debug playerSystem_debug dbSystem_debug loginSystem_debug commonServer_debug network_debug udm_debug database_debug framework_debug utility_debug pthread rt mysqlclient uuid
RELEASE_LIBS=masterSystem_release rankSystem_release friendSystem_release activitySystem_release shopSystem_release taskSystem_release prizeSystem_release sceneSystem_release petSystem_release mailSystem_release equipSystem_release skillSystem_release playerSystem_release dbSystem_release loginSystem_release commonServer_release network_release udm_release database_release framework_release utility_release pthread rt mysqlclient uuid

# 连接库路径
DEBUG_LIBS_PATH=$(OUT_LIB_DIR) $(THRLIB_DIR) ../../lib/BSLib/CentOS ../../lib/GFLib/CentOS ../../lib/GSLib/CentOS /usr/lib64/mysql
RELEASE_LIBS_PATH=$(OUT_LIB_DIR) $(THRLIB_DIR) ../../lib/BSLib/CentOS ../../lib/GFLib/CentOS ../../lib/GSLib/CentOS /usr/lib64/mysql

# 编译C++文件参数
DEBUG_CXX_FLAGS=-Wno-deprecated
RELEASE_CXX_FLAGS=-Wno-deprecated

# 编译C文件参数
DEBUG_C_FLAGS=-Wno-deprecated
RELEASE_C_FLAGS=-Wno-deprecated

################################################################
#编译文件
################################################################
OBJ_CPP=$(call get_cpp_root_file, )
OBJ_C=
OBJ_S=

################################################################
#静态库参数设置
################################################################
# 生产静态库参数
DEBUG_LIB_FLAGS=
RELEASE_LIB_FLAGS=

# 输出静态库
DEBUG_LIB_FILE=
RELEASE_LIB_FILE=

################################################################
#动态库参数设置
################################################################
# 生产静态库参数
DEBUG_DLL_FLAGS=
RELEASE_DLL_FLAGS=

# 输出动态库
DEBUG_DLL_FILE=
RELEASE_DLL_FILE=

################################################################
#可执行文件参数设置
################################################################
# 生产静态库参数
DEBUG_EXE_FLAGS=
RELEASE_EXE_FLAGS=

# 输出静态库
DEBUG_EXE_FILE=$(OUT_BIN_DIR)/$(ProjectName)_d
RELEASE_EXE_FILE=$(OUT_BIN_DIR)$(ProjectName)

include ../template/makeobj.inc
