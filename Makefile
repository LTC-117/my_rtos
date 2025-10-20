.PHONY : all
all:
	./build.sh

.PHONY : clean
clean:
	rm -rf build/*

.PHONY : upload
upload:
	sudo st-flash write build/my_rtos.bin 0x8000000

# para debug: openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program build/F103_RTOS.elf verify reset exit"

.PHONY : reset
reset:
	sudo st-flash erase
