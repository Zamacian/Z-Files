#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <switch.h>

#include "path.hpp"

void welcome(){
    std::cout << "Press '-' to clear, 'A' to perform next action" << std::endl << std::endl;
}

// Main program entrypoint
int main(int argc, char* argv[])
{
    consoleInit(NULL);
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);
    PadState pad;
    padInitializeDefault(&pad);

    welcome();

    Path workingPath(argv[0]);
    workingPath.displayPath();

    int a = 0;

    while (appletMainLoop())
    {
        padUpdate(&pad);

        u64 kDown = padGetButtonsDown(&pad);

        if (kDown & HidNpadButton_Plus){
            break;
        }

        if (kDown & HidNpadButton_Minus){
            consoleClear();
            welcome();
        }

        if (kDown & HidNpadButton_A){
            switch(a){
                case 0:
                    workingPath.ls();
                    break;
                case 1:
                    workingPath.toParent();
                    break;
                case 2:
                    workingPath.ls();
                    break;
                case 3:
                    workingPath.toParent();
                    break;
                case 4:
                    workingPath.ls();
                    break;
                case 5:
                    workingPath.cd("atmosphere");
                    break;
                case 6:
                    workingPath.ls();
                    break;
                default:
                    std::cout << "Done, you can exit or press ZL to restart" << std::endl;
                    break;

            }
            a++;
        }

        if (kDown & HidNpadButton_ZL){
            consoleClear();
            welcome();
            workingPath.setPath(argv[0]);
            a = 0;
        }

        consoleUpdate(NULL);
    }

    consoleExit(NULL);
    return 0;
}
