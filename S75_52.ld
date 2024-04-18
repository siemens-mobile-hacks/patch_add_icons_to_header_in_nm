SECTIONS {
    .NativeMenu_OnCreate 0xA0C9D950 : {
        KEEP(*(.text.NativeMenu_OnCreate*))
    }
    .NativeMenu_OnChange 0xA0C9D99A : {
        KEEP(*(.text.NativeMenu_OnChange*))
        KEEP(*(.rodata*))
    }
    .NativeMenu_OnClose 0xA0C9D9D0 : {
        KEEP(*(.text.NativeMenu_OnClose*))
    }
}
