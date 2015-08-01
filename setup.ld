/*
 * setup.ld
 *
 * Linker script for the i386 setup code
 */
OUTPUT_FORMAT("binary");

SECTIONS
{
	. = 0x7C00;
	.text : {
		*(.text);
	}

	. = 0x7DFE;
	.signature : {
		SHORT(0xAA55);
	}
}
