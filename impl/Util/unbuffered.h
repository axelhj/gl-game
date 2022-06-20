#include <stdio.h>
#include <windows.h>

CHAR GetChWin(VOID)
{
    HANDLE hStdin = GetStdHandle (STD_INPUT_HANDLE);
    INPUT_RECORD irInputRecord;
    DWORD dwEventsRead;
    CHAR cChar;
    while(ReadConsoleInputA (hStdin, &irInputRecord, 1, &dwEventsRead)) /* Read key press */
        if (irInputRecord.EventType == KEY_EVENT
            &&irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_SHIFT
            &&irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_MENU
            &&irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_CONTROL
        ) {
        cChar = irInputRecord.Event.KeyEvent.uChar.AsciiChar;
        ReadConsoleInputA (hStdin, &irInputRecord , 1, &dwEventsRead); /* Read key release */
        return cChar;
    }
    return EOF;
}
