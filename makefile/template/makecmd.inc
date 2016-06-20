ifndef get_s_root_file
define get_s_root_file
$(if $(CPP_ROOT_DIR), $(wildcard $(CPP_ROOT_DIR)/*.s), ) $(foreach n, $1, $(if $(CPP_ROOT_DIR), $(wildcard $(CPP_ROOT_DIR)/$(n)/*.s), ))
endef
endif

ifndef get_c_root_file
define get_c_root_file
$(if $(CPP_ROOT_DIR), $(wildcard $(CPP_ROOT_DIR)/*.c), ) $(foreach n, $1, $(if $(CPP_ROOT_DIR), $(wildcard $(CPP_ROOT_DIR)/$(n)/*.c), ))
endef
endif

ifndef get_cpp_root_file
define get_cpp_root_file
$(if $(CPP_ROOT_DIR), $(wildcard $(CPP_ROOT_DIR)/*.cpp), ) $(foreach n, $1, $(if $(CPP_ROOT_DIR), $(wildcard $(CPP_ROOT_DIR)/$(n)/*.cpp), ))
endef
endif

ifndef get_pkg_root_file
define get_pkg_root_file
$(if $(CPP_ROOT_DIR), $(wildcard $(CPP_ROOT_DIR)/*.pkg), ) $(foreach n, $1, $(if $(CPP_ROOT_DIR), $(wildcard $(CPP_ROOT_DIR)/$(n)/*.pkg), ))
endef
endif

ifndef get_h_root_file
define get_h_root_file
$(if $(CPP_ROOT_DIR), $(wildcard $(CPP_ROOT_DIR)/*.h), ) $(foreach n, $1, $(if $(CPP_ROOT_DIR), $(wildcard $(CPP_ROOT_DIR)/$(n)/*.h), ))
endef
endif

ifndef get_hpp_root_file
define get_hpp_root_file
$(if $(CPP_ROOT_DIR), $(wildcard $(CPP_ROOT_DIR)/*.hpp), ) $(foreach n, $1, $(if $(CPP_ROOT_DIR), $(wildcard $(CPP_ROOT_DIR)/$(n)/*.hpp), ))
endef
endif

ifndef add_define_flag
define add_define_flag
$(foreach n,$1,-D$(n))
endef
endif

ifndef add_include_flag
define add_include_flag
$(foreach n,$1,-I$(n))
endef
endif

ifndef add_lib_file_flag
define add_lib_file_flag
$(foreach n,$1,-l$(n))
endef
endif

ifndef add_lib_path_flag
define add_lib_path_flag
$(foreach n,$1,-L$(n))
endef
endif

MAKE_TARGET=$@

_DEBUG_INCS=
_RELEASE_INCS=

_DEBUG_DEFS=_DEBUG _LINUX
_RELEASE_DEFS=_LINUX

_DEBUG_LIBS=
_RELEASE_LIBS=

_DEBUG_LIBS_PATH=
_RELEASE_LIBS_PATH=

CMD_S=gcc
CMD_C=gcc
CMD_CXX=g++
CMD_DLL=g++
CMD_LIB=ar -rsv
CMD_EXE=g++
CMD_TOLUAPP=tolua++

_DEBUG_C_FLAGS=-c -g -Wall -fexec-charset=UTF-8 -finput-charset=GBK
_RELEASE_C_FLAGS=-c -O3 -Wall -fexec-charset=UTF-8 -finput-charset=GBK

#_DEBUG_C_FLAGS=-c -Wall -Wno-format -g
#_RELEASE_C_FLAGS=-c -Wall -Wno-unknown-pragmas -Wno-format -O3

_DEBUG_CXX_FLAGS=$(_DEBUG_C_FLAGS)
_RELEASE_CXX_FLAGS=$(_RELEASE_C_FLAGS)

_DEBUG_DLL_FLAGS=-shared -g -fPIC
_RELEASE_DLL_FLAGS=-shared -fPIC

_DEBUG_EXE_FLAGS=-g
_RELEASE_EXE_FLAGS=

