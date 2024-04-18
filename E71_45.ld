SECTIONS {
    .NativeMenu_OnCreate 0xA0C9EDF4 : {
        KEEP(*(.text.NativeMenu_OnCreate*))
    }
    .NativeMenu_OnChange 0xA0C9EE78 : {
        KEEP(*(.text.NativeMenu_OnChange*))
        KEEP(*(.rodata*))
    }
    .NativeMenu_OnClose 0xA0C9EF38 : {
        KEEP(*(.text.NativeMenu_OnClose*))
    }
}
