ifndef file_loop_fun
define file_loop_fun
	@for i in $1;\
	do\
		echo "make["$(MAKELEVEL)"]: "$(MAKE) $(MAKE_TARGET) "-f" $$i";"; \
		$(MAKE) $(MAKE_TARGET) -f $$i;\
	done
endef
endif

MAKE_TARGET=$@

debug:
	$(call file_loop_fun, $(MAKEFILE))

.DEFAULT:
	$(call file_loop_fun, $(MAKEFILE))
