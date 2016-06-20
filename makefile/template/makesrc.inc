ifndef dir_loop_fun
define dir_loop_fun
	@for i in $1 ; \
	do \
		echo "make["$(MAKELEVEL)"]: "$(MAKE) $(MAKE_TARGET) $(TARGET) "-C" $$i";"; \
		$(MAKE) $(MAKE_TARGET) -C $$i ;\
	done
endef
endif

MAKE_TARGET=$@

CURRENTDIR=$(shell pwd)

debug:
	$(call dir_loop_fun, $(MAKESRC), $(CURRENTDIR))

.DEFAULT:
	$(call dir_loop_fun, $(MAKESRC), $(CURRENTDIR))
	

