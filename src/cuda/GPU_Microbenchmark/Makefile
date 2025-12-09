BASE_DIR := $(shell pwd)
BIN_DIR := $(BASE_DIR)/bin

GPUAPPS_ROOT ?= $(abspath ../../..)
DEFAULT_INCLUDE ?= $(GPUAPPS_ROOT)/third_party/cuda-helpers $(GPUAPPS_ROOT)/src/cuda-samples/Common
export GPUAPPS_ROOT
export DEFAULT_INCLUDE

targets=$(cd cuda/GPU_Microbenchmark/ubench && \
          find l1_cache l2_cache -mindepth 1 -maxdepth 1 -type d | paste -sd, -)
ONLY="$targets" make GPU_Microbenchmark -j12

comma := ,
ifdef ONLY
ONLY_LIST := $(subst $(comma), ,$(strip $(ONLY)))
SUB_DIRS := $(foreach dir,$(ONLY_LIST),$(wildcard ubench/$(dir)/))
ifeq ($(strip $(SUB_DIRS)),)
$(error ONLY specified but no matching targets were expanded)
endif
else
SUB_DIRS        = $(wildcard ubench/*/*/)
endif
SUB_DIRS_ALL    = $(SUB_DIRS:%=all-%)
SUB_DIRS_CLEAN  = $(SUB_DIRS:%=clean-%)
SUB_DIRS_TUNER = $(SUB_DIRS:%=tuner-%)


all: create_dir $(SUB_DIRS_ALL)
tuner: create_dir $(SUB_DIRS_TUNER)
clean: delete_dir $(SUB_DIRS_CLEAN)

$(SUB_DIRS_ALL):
	$(MAKE) $(MAKE_FLAGS) -C $(@:all-%=%)

$(SUB_DIRS_TUNER):
	$(MAKE) -C $(@:tuner-%=%) tuner
$(SUB_DIRS_CLEAN):
	$(MAKE) $(MAKE_FLAGS) -C $(@:clean-%=%) clean

create_dir:
	mkdir -p $(BIN_DIR)

delete_dir:
	cd $(BIN_DIR); rm -f *
