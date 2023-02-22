/**
* @Author: Mats Brorson
* @Date: 2023-01-27
* 
* @Description: Main program used for the built in firmware monitor features. This is an stepping stone into a future OS of
* some kind. But that is way in the future. All things here will be done using Supervisor mode
*/

void _fmain(void)
{
/* Plans and notes here are:
* - define layout of stuff
* - Avoid assembly as long as possible
* - Help function by typing ? (question mark) I need an parser...
* - define commands to be used. Base it on concept of opcode and operands? like "cd 0x300" to change to that address and thereafter commands
    are based from that adress? Memory filesystem-ish? Hmmmm.... treating addresses as directories based on words? Files a byte? Interesting...but is it effective?
* - execute program from adress
* - dump registers and memory/ROM contents. Needs assembly code....
* - change memory data(really?)
* - Breakpoints with traps or trace feature of CPU
* - diagnostics of hardware
* - change VBR. This might not be an good idea....
*/
    while(1);
};