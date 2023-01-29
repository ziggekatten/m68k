ENTRY(Reset_Handler)

MEMORY
{
  FLASH(rx):ORIGIN =0x00000000,LENGTH =1024K
  SRAM(rwx):ORIGIN =0x00100000,LENGTH =1024K
}


SECTIONS
{
  .text :
  {
    *(.ipl_vector)
    *(.text)
	*(.text.*)
	*(.init)
	*(.fini)
	*(.rodata)
	*(.rodata.*)
	. = ALIGN(2);
	_etext = .;
  }> FLASH AT>FLASH
  
  _la_data = LOADADDR(.data);
  
  .data :
  {
    _sdata = .;
	*(.data)
	*(.data.*)
	. = ALIGN(2);
	_edata = .;
  }> SRAM AT> FLASH
  
  .bss :
  {
    _sbss = .;
	__bss_start__ = _sbss;
	*(.bss)
	*(.bss.*)
	*(COMMON)
	. = ALIGN(2);
	_ebss = .;
	__bss_end__ = _ebss;
	   . = ALIGN(2); 
	end = .;
	__end__ = .;
  }> SRAM
  
}