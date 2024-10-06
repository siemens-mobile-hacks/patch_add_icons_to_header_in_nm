SECTIONS {
    .NativeMenu_OnCreate 0xA0F0F600 : {
        KEEP(*(.text.NativeMenu_OnCreate*))
    }
    .NativeMenu_OnChange 0xA0F0F660 : {
        KEEP(*(.text.NativeMenu_OnChange*))
        KEEP(*(.rodata*))
    }
    .NativeMenu_OnClose 0xA0F0F6D0 : {
        KEEP(*(.text.NativeMenu_OnClose*))
    }
}
