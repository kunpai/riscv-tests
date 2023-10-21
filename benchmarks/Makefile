#=======================================================================
# UCB VLSI FLOW: Makefile for riscv-bmarks
#-----------------------------------------------------------------------
# Yunsup Lee (yunsup@cs.berkeley.edu)
#

XLEN ?= 64

default: all

src_dir = ./benchmarks

instname = riscv-bmarks
instbasedir = $(UCB_VLSI_HOME)/install

#--------------------------------------------------------------------
# Sources
#--------------------------------------------------------------------

bmarks = \
	CCa \
	CCe \
	CCm \
	CCl \
	CCh \
	CCh_st \
	CRd \
	CRf \
	CS1 \
	CS3 \
	DP1d \
	DP1f \
	DPT \
	DPTd \
	DPcvt \
	EF \
	EI \
	ED1 \
	EM1 \
	EM5 \
	MC \
	MCS \
	MD \
	MI \
	MIM \
	MIM2 \
	MIP \
	ML2_BW_ld \
	ML2_BW_ldst \
	ML2_BW_st \
	M_Dyn \
	STc \
	STL2 \
	STL2b \
	MM \
	MM_st \
	ML2 \
	ML2_st \
	CF1 \
	CRm \
	median \
	qsort \
	rsort \
	towers \
	vvadd \
	memcpy \
	multiply \
	mm \
	dhrystone \
	spmv \
	pmp \

#--------------------------------------------------------------------
# Build rules
#--------------------------------------------------------------------

RISCV_PREFIX ?= riscv$(XLEN)-linux-gnu-
RISCV_GCC ?= $(RISCV_PREFIX)gcc
RISCV_GCC_OPTS ?= -DPREALLOCATE=1 -mcmodel=medany -static -std=gnu99 -O2 -ffast-math -fno-common -fno-builtin-printf -fno-tree-loop-distribute-patterns -march=rv$(XLEN)gcv -mabi=lp64d
RISCV_LINK ?= $(RISCV_GCC) -T $(src_dir)/common/test.ld $(incs)
RISCV_LINK_OPTS ?= -static -nostdlib -nostartfiles -lm -lgcc
RISCV_OBJDUMP ?= $(RISCV_PREFIX)objdump --disassemble-all --disassemble-zeroes
RISCV_SIM ?= spike --isa=rv$(XLEN)gcv
PY := python

incs  += -I$(src_dir)/../env -I$(src_dir)/common $(addprefix -I$(src_dir)/, $(bmarks))
objs  :=

define compile_template
$(1).riscv: $(wildcard $(src_dir)/$(1)/*) $(wildcard $(src_dir)/common/*)
	@if [ -e $(src_dir)/$(1)/rand_arr_args.txt ]; then \
		echo "Generating randArr.h for $(1)"; \
		cat $(src_dir)/$(1)/rand_arr_args.txt; \
		$(eval args := $(shell cat $(src_dir)/$(1)/rand_arr_args.txt)) \
		echo "args: $(args)"; \
		$(PY) $(src_dir)/common/rand_c_arr.py $(args); \
		mv randArr.h $(src_dir)/$(1)/; \
	fi
	$$(RISCV_GCC) $$(incs) $$(RISCV_GCC_OPTS) -o $$@ $(wildcard $(src_dir)/$(1)/*.c) $(wildcard $(src_dir)/$(1)/*.S) $(wildcard $(src_dir)/common/*.c) $(wildcard $(src_dir)/common/*.S) $$(RISCV_LINK_OPTS)
endef

$(foreach bmark,$(bmarks),$(eval $(call compile_template,$(bmark))))

#------------------------------------------------------------
# Build and run benchmarks on riscv simulator

bmarks_riscv_bin  = $(addsuffix .riscv,  $(bmarks))
bmarks_riscv_dump = $(addsuffix .riscv.dump, $(bmarks))
bmarks_riscv_out  = $(addsuffix .riscv.out,  $(bmarks))

$(bmarks_riscv_dump): %.riscv.dump: %.riscv
	$(RISCV_OBJDUMP) $< > $@

$(bmarks_riscv_out): %.riscv.out: %.riscv
	$(RISCV_SIM) $< > $@

riscv: $(bmarks_riscv_dump)
run: $(bmarks_riscv_out)

junk += $(bmarks_riscv_bin) $(bmarks_riscv_dump) $(bmarks_riscv_hex) $(bmarks_riscv_out)

#------------------------------------------------------------
# Default

all: riscv

#------------------------------------------------------------
# Install

date_suffix = $(shell date +%Y-%m-%d_%H-%M)
install_dir = $(instbasedir)/$(instname)-$(date_suffix)
latest_install = $(shell ls -1 -d $(instbasedir)/$(instname)* | tail -n 1)

install:
	mkdir $(install_dir)
	cp -r $(bmarks_riscv_bin) $(bmarks_riscv_dump) $(install_dir)

install-link:
	rm -rf $(instbasedir)/$(instname)
	ln -s $(latest_install) $(instbasedir)/$(instname)

#------------------------------------------------------------
# Clean up

clean:
	rm -rf $(objs) $(junk)
