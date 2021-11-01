#ifndef KEYBOARD_SHORTCUTS_HANDLER_H
#define KEYBOARD_SHORTCUTS_HANDLER_H

class KeyShortcuts
{
public:
    KeyShortcuts(void) = delete;
    KeyShortcuts(const KeyShortcuts&) = delete;
    ~KeyShortcuts(void) = delete;
    KeyShortcuts& operator=(const KeyShortcuts&) = delete;


    static bool isUndo(void);
    static bool isAnyCtrl(void);
};

#endif //KEYBOARD_SHORTCUTS_HANDLER_H