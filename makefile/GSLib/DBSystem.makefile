################################################################
#��������
################################################################
include common.inc

################################################################
#�����������
################################################################
include ../template/makecmd.inc

ProjectName=dbSystem

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
DEBUG_LIBS=
RELEASE_LIBS=

# ���ӿ�·��
DEBUG_LIBS_PATH=$(OUT_LIB_DIR) $(THRLIB_DIR)
RELEASE_LIBS_PATH=$(OUT_LIB_DIR) $(THRLIB_DIR)

# ����C++�ļ�����
DEBUG_CXX_FLAGS=-Wno-deprecated
RELEASE_CXX_FLAGS=-Wno-deprecated

# ����C�ļ�����
DEBUG_C_FLAGS=-Wno-deprecated
RELEASE_C_FLAGS=-Wno-deprecated

################################################################
#�����ļ�
################################################################
OBJ_CPP=$(call get_cpp_root_file, CN DB GM GT LG SP)
OBJ_C=
OBJ_S=

################################################################
#��̬���������
################################################################
# ������̬�����
DEBUG_LIB_FLAGS=
RELEASE_LIB_FLAGS=

# �����̬��
DEBUG_LIB_FILE=$(OUT_LIB_DIR)/lib$(ProjectName)_debug.a
RELEASE_LIB_FILE=$(OUT_LIB_DIR)/lib$(ProjectName)_release.a

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
DEBUG_EXE_FILE=
RELEASE_EXE_FILE=

include ../template/makeobj.inc
