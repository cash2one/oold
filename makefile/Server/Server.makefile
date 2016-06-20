################################################################
#��������
################################################################
include common.inc

################################################################
#�����������
################################################################
include ../template/makecmd.inc

ProjectName=server

#����cppĿ¼
CPP_ROOT_DIR=$(BASE_SRC_DIR)/$(ProjectName)

# ����м��ļ�Ŀ¼
DEBUG_OUT_DIR=$(BASE_OBJ_DIR)/$(ProjectName)/Debug
RELEASE_OUT_DIR=$(BASE_OBJ_DIR)/$(ProjectName)/Release

#���Ŀ��Ŀ¼
OUT_TARGET_DIR=$(OUT_LIB_DIR)

# ����ͷ�ļ�Ŀ¼
DEBUG_INCS=$(INC_DIR) $(TOOLS_DIR) $(CPP_ROOT_DIR) 
RELEASE_INCS=$(INC_DIR) $(TOOLS_DIR) $(CPP_ROOT_DIR)

# �궨��
DEBUG_DEFS=
RELEASE_DEFS=

# ���ӿ�
DEBUG_LIBS=framework_debug utility_debug pthread rt curses
RELEASE_LIBS=framework_debug utility_release pthread rt curses

# ���ӿ�·��
DEBUG_LIBS_PATH=$(OUT_LIB_DIR) $(THRLIB_DIR) ../../lib/BSLib/CentOS ../../lib/GFLib/CentOS ../../lib/GSLib/CentOS
RELEASE_LIBS_PATH=$(OUT_LIB_DIR) $(THRLIB_DIR) ../../lib/BSLib/CentOS ../../lib/GFLib/CentOS ../../lib/GSLib/CentOS

# ����C++�ļ�����
DEBUG_CXX_FLAGS=-Wno-deprecated
RELEASE_CXX_FLAGS=-Wno-deprecated

# ����C�ļ�����
DEBUG_C_FLAGS=-Wno-deprecated
RELEASE_C_FLAGS=-Wno-deprecated

################################################################
#�����ļ�
################################################################
OBJ_CPP=$(call get_cpp_root_file, )
OBJ_C=
OBJ_S=

################################################################
#��̬���������
################################################################
# ������̬�����
DEBUG_LIB_FLAGS=
RELEASE_LIB_FLAGS=

# �����̬��
DEBUG_LIB_FILE=
RELEASE_LIB_FILE=

################################################################
#��̬���������
################################################################
# ������̬�����
DEBUG_DLL_FLAGS=
RELEASE_DLL_FLAGS=

# �����̬��
DEBUG_DLL_FILE=
RELEASE_DLL_FILE=

################################################################
#��ִ���ļ���������
################################################################
# ������̬�����
DEBUG_EXE_FLAGS=
RELEASE_EXE_FLAGS=

# �����̬��
DEBUG_EXE_FILE=$(OUT_BIN_DIR)/$(ProjectName)_d
RELEASE_EXE_FILE=$(OUT_BIN_DIR)$(ProjectName)

include ../template/makeobj.inc
