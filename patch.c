#include <swilib/gui.h>


#ifdef NEWSGOLD
    #ifdef ELKA
        #ifdef E71_45
            #include "E71_45.h"
        #endif
    #else
        #ifdef S75_52
            #include "S75_52.h"
        #endif
    #endif
#else
    #ifdef CX70_56
        #include "CX70_56.h"
    #endif
#endif


#define _malloc ((void *(*)(unsigned int size))(ADDR_MALLOC))
#define _mfree  ((void (*)(void *))(ADDR_MFREE))
#define _GetHeaderPointer ((void *(*)(void *gui))(ADDR_GET_HEADER_POINTER))
#define _SetHeaderIcon ((void (*)(void *hdr_pointer, const int *icon, void *malloc_adr, void *mfree_adr))(ADDR_SET_HEADER_ICON))

#define OnCreate_unk ((void (*)(void *gui, void *r1, void *r2))(ADDR_ON_CREATE_UNK))
#define OnChange_unk ((void (*)(GUI *gui))(ADDR_ON_CHANGE_UNK))
#define OnClose_unk  ((void (*)(GUI *gui, void *r1))(ADDR_ON_CLOSE_UNK))

#ifdef NEWSGOLD
    #ifdef ELKA
        #define ICONS_OFFSET 860
        const unsigned char ICONS_TABLE[] = { \
            0x3, 0x1, 0x7,
            0x2, 0x9, 0xB,
            0x6, 0x8, 0x5,
            0x4, 0xA, 0xC,
        };
    #else
        #define ICONS_OFFSET 831
        const unsigned char ICONS_TABLE[] = {
            0x3, 0x1, 0x6,
            0x2, 0x8, 0xA,
            0x5, 0x7, 0x0,
            0x4, 0x9, 0xB
        };
    #endif
#else
    #define ICONS_OFFSET 618
    const unsigned char ICONS_TABLE[] = {
        0xC0, 0xC6, 0xEC,
        0xB8, 0xB2, 0x01, // 3, 5 reversed :-(
        0x45, 0x41, 0xCA
    };
#endif

__attribute__((target("thumb")))
__attribute__((section(".text.NativeMenu_OnCreate")))
void NativeMenu_OnCreate(GUI *gui, void *r1, void *r2) {
    int *icons = _malloc(sizeof(int) * 2);
    icons[0] = ICONS_OFFSET + ICONS_TABLE[4];
    icons[1] = 0;
#ifndef NEWSGOLD
    gui->color1 = (int)icons;
#endif
    OnCreate_unk(gui, r1, r2);
#ifdef NEWSGOLD
    _SetHeaderIcon(_GetHeaderPointer(gui), icons, (unsigned int *)ADDR_MALLOC, (unsigned int *)ADDR_MFREE);
    gui->color1 = (int)icons;
#endif
}

__attribute__((target("thumb")))
__attribute__((section(".text.NativeMenu_OnChange")))
void NativeMenu_OnChange(GUI *gui) {
    OnChange_unk(gui);
    int *icons = (int*)(gui->color1);
    icons[0] = ICONS_TABLE[gui->unk10 - 4] + ICONS_OFFSET;
#ifndef NEWSGOLD
    _SetHeaderIcon(_GetHeaderPointer(gui), icons, (unsigned int *)ADDR_MALLOC, (unsigned int *)ADDR_MFREE);
#endif
}

__attribute__((target("thumb")))
__attribute__((section(".text.NativeMenu_OnClose")))
void NativeMenu_OnClose(GUI *gui, void *r1) {
    _mfree((int*)(gui->color1));
    gui->color1 = 0;
    OnClose_unk(gui, r1);
}
