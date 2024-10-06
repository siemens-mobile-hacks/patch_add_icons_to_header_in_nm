CFLAGS = -I "../sdk/dietlibc/include" -I "../sdk/swilib/include/"

define gcc
	arm-none-eabi-gcc -mcpu=arm926ej-s -std=gnu99 -Os -mthumb-interwork -msoft-float -mlittle-endian -c $(CFLAGS) $(1) patch.c -o patch.o
endef

define ld
	arm-none-eabi-ld -zmax-page-size=1 patch.o -o patch.elf -T $(1).ld
endef

define obj
	arm-none-eabi-objcopy -O binary -j .NativeMenu_OnCreate patch.elf patch1.bin
	arm-none-eabi-objcopy -O binary -j .NativeMenu_OnChange patch.elf patch2.bin
	arm-none-eabi-objcopy -O binary -j .NativeMenu_OnClose patch.elf patch3.bin
	arm-none-eabi-objdump -D patch.elf
	cat patch1.bin | xxd -ps -c 80
	cat patch2.bin | xxd -ps -c 90
	cat patch3.bin | xxd -ps -c 40
endef

e71_45:
	$(call gcc,-DNEWSGOLD -DELKA -DE71_45)
	$(call ld,E71_45)
	$(call obj)

s75_52:
	$(call gcc,-DNEWSGOLD -DS75_52)
	$(call ld,S75_52)
	$(call obj)

cx70_56:
	$(call gcc,-DSGOLD -DCX70_56)
	$(call ld,CX70_56)
	$(call obj)

clean:
	rm -f patch.o patch.elf patch*.bin
