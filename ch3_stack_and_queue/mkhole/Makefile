APPS := stack linear_queue circular_queue in_to_postfix cal_postfix
OBJDIR := build

stack_SRCS := stack.c
linear_queue_SRCS := linear_queue.c
circular_queue_SRCS := circular_queue.c
in_to_postfix_SRCS := in_to_postfix.c
cal_postfix_SRCS := cal_postfix.c

ifndef OBJDIR
 $(error "OBJDIR is not defined. Aborting")
endif

ifndef APPS
 $(error "APPS is not defined. Aborting")
endif

define EXPAND_VAR
 $(1)_OBJS :=  $$(patsubst %.c,$(OBJDIR)/%.o,$$($(1)_SRCS))
 OBJS += $$($(1)_OBJS)
 EXES += $$(patsubst %,$(OBJDIR)/%,$(1))
endef

$(foreach app,$(APPS),$(eval $(call EXPAND_VAR,$(app))))

.PHONY : all clean

CFLAGS  += -Wall -g
LDFLAGS +=

all: $(OBJDIR) $(EXES)
	@echo "Finish!"

-include $(OBJDIR)/*.d

$(OBJDIR):
	mkdir -p $@

$(EXES): $(OBJS)
	$(CC) $($(@F)_OBJS) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: %.c
	$(CC) -c $(CFLAGS) -MMD -MT$(@) $< -o $@

clean:
	$(RM) -rf $(OBJDIR)
