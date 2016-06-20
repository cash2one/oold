ifndef clean_file_fun
define clean_file_fun
	@for i in $1;\
	do\
		if [ -f $$i ]; then echo "rm -f "$$i";"; rm -f $$i; fi \
	done
endef
endif

ifndef create_dir_fun
define create_dir_fun
	@if [ ! -d $1 ]; then echo "mkdir -p "$1";"; mkdir -p $1; fi
endef
endif

ifeq (YES, $(PROFILE))
PG=-pg
endif

ifndef DEBUG_OUT_DIR
DEBUG_OUT_DIR=.
endif

ifndef RELEASE_OUT_DIR
RELEASE_OUT_DIR=.
endif

ifndef CPP_ROOT_DIR
CPP_ROOT_DIR=.
endif

DEBUG_LIB_FLAGS+=$(_DEBUG_LIB_FLAGS)
DEBUG_DLL_FLAGS+=$(_DEBUG_DLL_FLAGS)
DEBUG_EXE_FLAGS+=$(_DEBUG_EXE_FLAGS)
RELEASE_LIB_FLAGS+=$(_RELEASE_LIB_FLAGS)
RELEASE_DLL_FLAGS+=$(_RELEASE_DLL_FLAGS)
RELEASE_EXE_FLAGS+=$(_RELEASE_EXE_FLAGS)

DEBUG_C_FLAGS+=$(_DEBUG_C_FLAGS)
RELEASE_C_FLAGS+=$(_RELEASE_C_FLAGS)
DEBUG_CXX_FLAGS+=$(_DEBUG_CXX_FLAGS)
RELEASE_CXX_FLAGS+=$(_RELEASE_CXX_FLAGS)

DEBUG_LIBS+=$(_DEBUG_LIBS)
RELEASE_LIBS+=$(_RELEASE_LIBS)

DEBUG_LIBS_PATH+=$(_DEBUG_LIBS_PATH)
RELEASE_LIBS_PATH+=$(_RELEASE_LIBS_PATH)

DEBUG_INCS+=$(_DEBUG_INCS)
RELEASE_INCS+=$(_RELEASE_INCS)

DEBUG_DEFS+=$(_DEBUG_DEFS)
RELEASE_DEFS+=$(_RELEASE_DEFS)

TOLUA_H_PKG=$(CPP_PKG:%.pkg=%.tolua.h)
TOLUA_CPP_PKG=$(CPP_PKG:%.pkg=%.tolua.cc)

DEBUG_OBJ_TOLUA_CPP=$(subst $(CPP_ROOT_DIR), $(DEBUG_OUT_DIR), $(TOLUA_CPP_PKG:%.cc=%.d))
DEBUG_OBJ_CPP=$(subst $(CPP_ROOT_DIR), $(DEBUG_OUT_DIR), $(OBJ_CPP:%.cpp=%.d))
DEBUG_OBJ_C=$(subst $(CPP_ROOT_DIR), $(DEBUG_OUT_DIR), $(OBJ_C:%.c=%.d))
DEBUG_OBJ_S=$(subst $(CPP_ROOT_DIR), $(DEBUG_OUT_DIR), $(OBJ_S:%.s=%.d))
DEBUG_OBJ=$(DEBUG_OBJ_TOLUA_CPP) $(DEBUG_OBJ_CPP) $(DEBUG_OBJ_C) $(DEBUG_OBJ_S)

# DEBUG_CPP=$(OBJ_CPP)
# DEBUG_C=$(OBJ_C)
# DEBUG_S=$(OBJ_S)

RELEASE_OBJ_TOLUA_CPP=$(subst $(CPP_ROOT_DIR), $(RELEASE_OUT_DIR), $(TOLUA_CPP_PKG:%.cc=%.o))
RELEASE_OBJ_CPP=$(subst $(CPP_ROOT_DIR), $(RELEASE_OUT_DIR), $(OBJ_CPP:%.cpp=%.o))
RELEASE_OBJ_C=$(subst $(CPP_ROOT_DIR), $(RELEASE_OUT_DIR), $(OBJ_C:%.c=%.o))
RELEASE_OBJ_S=$(subst $(CPP_ROOT_DIR), $(RELEASE_OUT_DIR), $(OBJ_S:%.s=%.o))
RELEASE_OBJ=$(RELEASE_OBJ_TOLUA_CPP) $(RELEASE_OBJ_CPP) $(RELEASE_OBJ_C) $(RELEASE_OBJ_S)

# RELEASE_CPP=$(OBJ_CPP)
# RELEASE_C=$(OBJ_C)
# RELEASE_S=$(OBJ_S)

CLEAN_FILE+=$(DEBUG_OBJ)
CLEAN_FILE+=$(RELEASE_OBJ)

CLEAN_ALL_FILE += $(DEBUG_LIB_FILE) $(DEBUG_DLL_FILE) $(DEBUG_EXE_FILE) $(RELEASE_LIB_FILE) $(RELEASE_DLL_FILE) $(RELEASE_EXE_FILE) $(CLEAN_FILE) $(TOLUA_CPP_PKG) $(TOLUA_H_PKG)

debug: $(DEBUG_LIB_FILE) $(DEBUG_DLL_FILE) $(DEBUG_EXE_FILE)

release: $(RELEASE_LIB_FILE) $(RELEASE_DLL_FILE) $(RELEASE_EXE_FILE)

debuglib: $(DEBUG_LIB_FILE)

debugdll: $(DEBUG_DLL_FILE)

debugexe: $(DEBUG_EXE_FILE)

releaselib: $(RELEASE_LIB_FILE) 

releasedll: $(RELEASE_DLL_FILE)

releaseexe: $(RELEASE_EXE_FILE)

tolua: $(TOLUA_CPP_PKG) $(TOLUA_H_PKG)

clean:
ifdef CLEAN_FILE
	$(call clean_file_fun, $(CLEAN_FILE))
endif

cleanall:
ifdef CLEAN_ALL_FILE
	$(call clean_file_fun, $(CLEAN_ALL_FILE))
endif

touch:
	touch -m *; touch -m *.*;
	
$(DEBUG_LIB_FILE) : $(DEBUG_OBJ)
	$(call create_dir_fun, $(dir $@))
	$(CMD_LIB) $@ $(DEBUG_OBJ) $(DEBUG_LIB_FLAGS) 

$(DEBUG_DLL_FILE) : $(DEBUG_OBJ)
	$(call create_dir_fun, $(dir $@))
	$(CMD_DLL) -o $@ $(DEBUG_OBJ) $(PG) $(DEBUG_DLL_FLAGS) $(call add_lib_file_flag, $(DEBUG_LIBS)) $(call add_lib_path_flag, $(DEBUG_LIBS_PATH))

$(DEBUG_EXE_FILE) : $(DEBUG_OBJ)
	$(call create_dir_fun, $(dir $@))
	$(CMD_EXE) -o $@ $(DEBUG_OBJ) $(PG) $(DEBUG_EXE_FLAGS) $(call add_lib_file_flag, $(DEBUG_LIBS)) $(call add_lib_path_flag, $(DEBUG_LIBS_PATH))
	
$(RELEASE_LIB_FILE) : $(RELEASE_OBJ)
	$(call create_dir_fun, $(dir $@))
	$(CMD_LIB) $@ $(RELEASE_OBJ) $(RELEASE_LIB_FLAGS) 

$(RELEASE_DLL_FILE) : $(RELEASE_OBJ)
	$(call create_dir_fun, $(dir $@))
	$(CMD_DLL) -o $@ $(RELEASE_OBJ) $(PG) $(RELEASE_DLL_FLAGS) $(call add_lib_file_flag, $(RELEASE_LIBS)) $(call add_lib_path_flag, $(RELEASE_LIBS_PATH))

$(RELEASE_EXE_FILE) : $(RELEASE_OBJ)
	$(call create_dir_fun, $(dir $@))
	$(CMD_EXE) -o $@ $(RELEASE_OBJ) $(PG) $(RELEASE_EXE_FLAGS) $(call add_lib_file_flag, $(RELEASE_LIBS)) $(call add_lib_path_flag, $(RELEASE_LIBS_PATH))

################################################################
#生成 公用的 LUA H文件 CPP文件
################################################################
$(TOLUA_CPP_PKG) : %.tolua.cc: %.pkg
	$(call create_dir_fun, $(dir $@))
	$(CMD_TOLUAPP) -H $(patsubst %.cc, *.h, $@) -o $@ $^

$(TOLUA_H_PKG) : %.tolua.h: %.pkg
	$(call create_dir_fun, $(dir $@))
	$(CMD_TOLUAPP) -H $@ $^

################################################################
#生成 DEBUG 版 OBJ 文件
################################################################
$(DEBUG_OBJ_CPP) : $(DEBUG_OUT_DIR)/%.d: $(CPP_ROOT_DIR)/%.cpp
	$(call create_dir_fun, $(dir $@))
	$(CMD_CXX) -o $@ $(DEBUG_CXX_FLAGS) $(call add_define_flag, $(DEBUG_DEFS)) $(call add_include_flag, $(DEBUG_INCS)) $^

$(DEBUG_OBJ_TOLUA_CPP) : $(DEBUG_OUT_DIR)/%.d: $(CPP_ROOT_DIR)/%.tolua.cc $(CPP_ROOT_DIR)/%.tolua.h
	$(call create_dir_fun, $(dir $@))
	$(CMD_CXX) -o $@ $(DEBUG_CXX_FLAGS) $(call add_define_flag, $(DEBUG_DEFS)) $(call add_include_flag, $(DEBUG_INCS) $<

$(DEBUG_OBJ_C) : $(DEBUG_OUT_DIR)/%.d: $(CPP_ROOT_DIR)/%.c
	$(call create_dir_fun, $(dir $@))
	$(CMD_C) -o $@ $(DEBUG_C_FLAGS) $(call add_define_flag, $(DEBUG_DEFS)) $(call add_include_flag, $(DEBUG_INCS) $^
	
$(DEBUG_OBJ_S) : $(DEBUG_OUT_DIR)/%.d: $(CPP_ROOT_DIR)/%.s
	$(call create_dir_fun, $(dir $@))
	$(CMD_S) -o $@ $(DEBUG_C_FLAGS) $(call add_define_flag, $(DEBUG_DEFS)) $(call add_include_flag, $(DEBUG_INCS) $^

################################################################
#生成 RELEASE 版 OBJ 文件
################################################################
$(RELEASE_OBJ_CPP) : $(RELEASE_OUT_DIR)/%.o: $(CPP_ROOT_DIR)/%.cpp
	$(call create_dir_fun, $(dir $@))
	$(CMD_CXX) -o $@ $(RELEASE_CXX_FLAGS) $(call add_define_flag, $(RELEASE_DEFS)) $(call add_include_flag, $(RELEASE_INCS)) $^

$(RELEASE_OBJ_TOLUA_CPP) : $(RELEASE_OUT_DIR)/%.o: $(CPP_ROOT_DIR)/%.tolua.cc $(CPP_ROOT_DIR)/%.tolua.h
	$(call create_dir_fun, $(dir $@))
	$(CMD_CXX) -o $@ $(RELEASE_CXX_FLAGS) $(call add_define_flag, $(RELEASE_DEFS) $(call add_include_flag, $(RELEASE_INCS)) $<

$(RELEASE_OBJ_C) : $(RELEASE_OUT_DIR)/%.o: $(CPP_ROOT_DIR)/%.c
	$(call create_dir_fun, $(dir $@))
	$(CMD_C) -o $@ $(RELEASE_C_FLAGS) $(call add_define_flag, $(RELEASE_DEFS)) $(call add_include_flag, $(RELEASE_INCS)) $^
	
$(RELEASE_OBJ_S) : $(RELEASE_OUT_DIR)/%.o: $(CPP_ROOT_DIR)/%.s
	$(call create_dir_fun, $(dir $@))
	$(CMD_S) -o $@ $(RELEASE_C_FLAGS) $(call add_define_flag, $(RELEASE_DEFS)) $(call add_include_flag, $(RELEASE_INCS)) $^



