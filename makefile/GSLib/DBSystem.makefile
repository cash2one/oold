################################################################
#公共参数
################################################################
include common.inc

################################################################
#编译参数设置
################################################################
include ../template/makecmd.inc

ProjectName=dbSystem

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
DEBUG_LIBS=
RELEASE_LIBS=

# 连接库路径
DEBUG_LIBS_PATH=$(OUT_LIB_DIR) $(THRLIB_DIR)
RELEASE_LIBS_PATH=$(OUT_LIB_DIR) $(THRLIB_DIR)

# 编译C++文件参数
DEBUG_CXX_FLAGS=-Wno-deprecated
RELEASE_CXX_FLAGS=-Wno-deprecated

# 编译C文件参数
DEBUG_C_FLAGS=-Wno-deprecated
RELEASE_C_FLAGS=-Wno-deprecated

################################################################
#编译文件
################################################################
OBJ_CPP=$(call get_cpp_root_file, CN DB GM GT LG SP)
OBJ_C=
OBJ_S=

################################################################
#静态库参数设置
################################################################
# 生产静态库参数
DEBUG_LIB_FLAGS=
RELEASE_LIB_FLAGS=

# 输出静态库
DEBUG_LIB_FILE=$(OUT_LIB_DIR)/lib$(ProjectName)_debug.a
RELEASE_LIB_FILE=$(OUT_LIB_DIR)/lib$(ProjectName)_release.a

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
DEBUG_EXE_FILE=
RELEASE_EXE_FILE=

include ../template/makeobj.inc
