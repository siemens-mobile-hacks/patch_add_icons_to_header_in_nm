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
#endif


#define _malloc ((void *(*)(unsigned int size))(ADDR_MALLOC))
#define _mfree  ((void (*)(void *))(ADDR_MFREE))
#define _GetDataOfItemByID ((void *(*)(void *gui, int id))(ADDR_GET_DATA_OF_ITEM_BY_ID))
#define _SetHeaderIcon ((void (*)(void *hdr_pointer, const int *icon, void *malloc_adr, void *mfree_adr))(ADDR_SET_HEADER_ICON))

#define OnCreate_unk ((void (*)(void *gui, int r1, int r2))(ADDR_ON_CREATE_UNK))
#define OnChange_unk ((void (*)(GUI *gui))(ADDR_ON_CHANGE_UNK))
#define OnClose_unk  ((void (*)(GUI *gui, int r1))(ADDR_ON_CLOSE_UNK))

#ifdef NEWSGOLD
    #ifdef ELKA
        #define ICONS_OFFSET 860
        #ifdef E71_45
            const unsigned char ICONS_TABLE[] = {
                0x3, 0x1, 0x7,
                0x2, 0x9, 0xB,
                0x6, 0x8, 0x5,
                0x4, 0xA, 0xC,
            };
        #endif
    #else
        #define ICONS_OFFSET 831
        const unsigned char ICONS_TABLE[] = {
            0x3, 0x1, 0x6,
            0x2, 0x8, 0xA,
            0x5, 0x7, 0x0,
            0x4, 0x9, 0xB
        };
    #endif
#endif

__attribute__((target("thumb")))
__attribute__((section(".text.NativeMenu_OnCreate")))
void NativeMenu_OnCreate(GUI *gui, int r1, int r2) {
    OnCreate_unk(gui, r1, r2);
    void *hdr_pointer = _GetDataOfItemByID(gui, 2);
    if (hdr_pointer) {
        int *icons = _malloc(sizeof(int) * 2);
        icons[0] = ICONS_OFFSET + ICONS_TABLE[4];
        icons[1] = 0;
        _SetHeaderIcon(hdr_pointer, icons, (unsigned int *)ADDR_MALLOC, (unsigned int *)ADDR_MFREE);
        gui->color1 = (int)icons;
    } else {
        gui->color1 = 0;
    }
}

__attribute__((target("thumb")))
__attribute__((section(".text.NativeMenu_OnChange")))
void NativeMenu_OnChange(GUI *gui) {
    OnChange_unk(gui);
    if (gui->color1) {
        int *icons = (int*)gui->color1;
        icons[0] = ICONS_TABLE[gui->unk10 - 4] + ICONS_OFFSET;
    }
}

__attribute__((target("thumb")))
__attribute__((section(".text.NativeMenu_OnClose")))
void NativeMenu_OnClose(GUI *gui, int r1) {
    if (gui->color1) {
        _mfree((void*)(gui->color1));
    }
    OnClose_unk(gui, r1);
}
