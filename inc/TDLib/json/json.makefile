################################################################
#��������
################################################################

################################################################
#�����������
################################################################
include ../../../makefile/template/makecmd.inc

ProjectName=json

#����cppĿ¼
CPP_ROOT_DIR=src

# ����м��ļ�Ŀ¼
DEBUG_OUT_DIR=../../../../srcobj/TDLib/$(ProjectName)/Debug
RELEASE_OUT_DIR=../../../../srcobj/TDLib/$(ProjectName)/Release

#���Ŀ��Ŀ¼
OUT_TARGET_DIR=

# ����ͷ�ļ�Ŀ¼
DEBUG_INCS=inc
RELEASE_INCS=inc

# �궨��
DEBUG_DEFS=
RELEASE_DEFS=

# ���ӿ�
DEBUG_LIBS=
RELEASE_LIBS=

# ���ӿ�·��
DEBUG_LIBS_PATH=
RELEASE_LIBS_PATH=

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
DEBUG_LIB_FILE=lib/lib$(ProjectName)_debug.a
RELEASE_LIB_FILE=lib/lib$(ProjectName)_release.a

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

include ../../../makefile/template/makeobj.inc
