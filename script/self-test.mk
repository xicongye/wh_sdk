SOFTWARE_PROGRAM = $(shell ls $(SDK_ROOT)/software)
SOFTWARE_VECTOR_PROGRAM = $(shell ls $(SDK_ROOT)/software_vector)
PLATFORM_LIST = BOARD VCS SPIKE
SOFTWARE_SIM_PROGRAM = coremark dhrystone memory_test pmp_test rtc_test soft_int_test STREAM whetstone

self-test: dist-clean compile-test simulate-test upload-test
compile-test:  build-compile-log  compile-software  compile-software_vector
simulate-test: build-simulate-log simulate-software simulate-software_vector
upload-test:   build-upload-log   upload-software   upload-software_vector

build-compile-log:
	@rm -rf compile-log
	@mkdir compile-log
	@mkdir -p compile-log/BOARD
	@mkdir -p compile-log/VCS
	@mkdir -p compile-log/SPIKE

compile-software: 
	@echo ----------------------------------------
	@echo compile all program in software dir
	@echo ----------------------------------------
	@for program in $(SOFTWARE_PROGRAM); do \
          for platform in $(PLATFORM_LIST); do\
                echo start to compile $$program on $$platform; \
                $(MAKE) software PROGRAM=$$program SOFTWARE=software PLATFORM=$$platform TARGET=$$program-$$platform > compile-log/$$platform/$$program-$$platform.log; \
                rc=$$?; \
                if [ $$rc -ne 0 ]; then \
                        echo "\t$$program compile on $$platform fail"; \
                        exit $$rc; \
                fi ;\
                echo  "\t$$program compile on $$platform pass"; \
          done; \
        done
	@echo ----------------------------------------
	@echo all program in software dir pass
	@echo ----------------------------------------


compile-software_vector:
	@echo ----------------------------------------
	@echo compile all program in software_vector dir
	@echo ----------------------------------------
	@for program in $(SOFTWARE_VECTOR_PROGRAM); do \
          for platform in $(PLATFORM_LIST); do\
                echo start to compile $$program on $$platform; \
                $(MAKE) software PROGRAM=$$program SOFTWARE=software_vector PLATFORM=$$platform TARGET=$$program-$$platform > compile-log/$$platform/$$program-$$platform.log; \
                rc=$$?; \
                if [ $$rc -ne 0 ]; then \
                        echo "\t$$program compile on $$platform fail"; \
                        exit $$rc; \
                fi ;\
                echo "\t$$program compile on $$platform pass"; \
          done; \
        done
	@echo ----------------------------------------
	@echo all program in software_vector dir pass
	@echo ----------------------------------------

build-simulate-log:
	@rm -rf simulate-log
	@mkdir simulate-log


simulate-software:  
	@echo ----------------------------------------
	@echo simulate all program in software dir
	@echo $(SOFTWARE_SIM_PROGRAM)
	@echo ----------------------------------------
	@for program in $(SOFTWARE_SIM_PROGRAM); do \
                echo start to simulate $$program on spike; \
                $(MAKE) run_sim PROGRAM=$$program SOFTWARE=software PLATFORM=SPIKE TARGET=$$program-SPIKE > simulate-log/$$program.log; \
                rc=$$?; \
                if [ $$rc -ne 0 ]; then \
                        echo "\t$$program simulate on $$platform fail"; \
                        exit $$rc; \
                fi ;\
                echo "\t$$program simulate on spike pass"; \
        done
	@echo ----------------------------------------
	@echo all program in software dir pass
	@echo $(SOFTWARE_SIM_PROGRAM)
	@echo ----------------------------------------

simulate-software_vector: 
	@echo ----------------------------------------
	@echo simulate all program in software_vector dir
	@echo ----------------------------------------
	@for program in $(SOFTWARE_VECTOR_PROGRAM); do \
                echo start to simulate $$program on spike; \
                $(MAKE) run_sim PROGRAM=$$program SOFTWARE=software_vector PLATFORM=SPIKE TARGET=$$program-SPIKE > simulate-log/$$program.log; \
                rc=$$?; \
                if [ $$rc -ne 0 ]; then \
                        echo "\t$$program simulate on $$platform fail"; \
                        exit $$rc; \
                fi ;\
                echo "\t$$program simulate on spike pass"; \
        done
	@echo ----------------------------------------
	@echo all program in software_vector dir pass
	@echo ----------------------------------------


build-upload-log:
	@rm -rf upload-log
	@mkdir upload-log

upload-software:
	@echo ----------------------------------------
	@echo upload all program in software dir
	@echo ----------------------------------------
	@for program in $(SOFTWARE_PROGRAM); do \
                echo start to upload $$program; \
                $(MAKE) upload PROGRAM=$$program SOFTWARE=software TARGET=$$program-BOARD > upload-log/$$program.log 2>&1; \
                rc=$$?; \
                sleep 30; \
                if [ $$rc -ne 0 ]; then \
                        echo "\t$$program upload fail"; \
                        exit $$rc; \
                fi ;\
                echo "\t$$program upload successfuly"; \
        done
	@echo ----------------------------------------
	@echo all program in software dir pass
	@echo ----------------------------------------

upload-software_vector:
	@echo ----------------------------------------
	@echo upload all program in software dir
	@echo ----------------------------------------
	@for program in $(SOFTWARE_VECTOR_PROGRAM); do \
                echo start to upload $$program; \
                $(MAKE) upload PROGRAM=$$program SOFTWARE=software_vector TARGET=$$program-BOARD > upload-log/$$program.log 2>&1; \
                rc=$$?; \
                sleep 30; \
                if [ $$rc -ne 0 ]; then \
                        echo "\t$$program upload fail"; \
                        exit $$rc; \
                fi ;\
                echo "\t$$program upload successfuly"; \
        done
	@echo ----------------------------------------
	@echo all program in software dir pass
	@echo ----------------------------------------


