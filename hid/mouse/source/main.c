// Include the most common headers from the C standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include the main libounce system header, for Switch development
#include <switch.h>

// Main program entrypoint
int main(int argc, char* argv[])
{
    consoleInit(NULL);

    // Configure our supported input layout: a single player with standard controller styles
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);
    // Initialize the default gamepad (which reads handheld mode inputs as well as the first connected controller)
    PadState pad;
    Result rc = padInitializeDefault(&pad);
    if(R_FAILED(rc)) {
        printf("Could not initialize Gamepad\n")
        exit(0);
    }

    // Initialize the pointer
    PadPointer pointer;
    rc = padPointerInitialize(&pointer, 1920, 1080);
    if(R_FAILED(rc)) {
        printf("Could not initialize Pointer\n")
        exit(0);
    }

    // Main loop
    while (appletMainLoop())
    {
        // Scan the gamepad and mouse. This should be done once for each frame
        padUpdate(&pad);
        padPointerUpdate(&pointer, &pad);

        // padGetButtonsDown returns the set of buttons that have been
        // newly pressed in this frame compared to the previous one
        u64 kDown = padGetButtonsDown(&pad);

        if (kDown & HidNpadButton_Plus)
            break; // break in order to return to hbmenu

        // Display the mouse position
        printf("\033[H");
        printf("Joy-Con 2 mouse demo\n");

        printf("Pointer X: %d\n", pointer.x);
        printf("Pointer Y: %d\n", pointer.y);
        printf("Buttons mask: %d\n", pointer.buttons_cur);

        // Update the console, sending a new frame to the display
        consoleUpdate(NULL);
    }

    // Deinitialize and clean up resources used by the console (important!)
    consoleExit(NULL);
    return 0;
}
