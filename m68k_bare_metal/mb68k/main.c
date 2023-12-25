#include "machine.h"
#include "mb68ksyscalls.h"
#include <stdbool.h>
int _fmain(void){
    disable_interrupts(true);       // Disable CPU interrupts

        /*
        1. disable CPU interrupts
        2. disable DUART interrupts
        3. initialize DUART
        4. disable rx
        5. hw and memtest
        6. enable CPU interrupts
        7. enable DUART interrupts
        6. enable RX
        */

    while (1){

    };
}
