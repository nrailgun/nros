/*
 * setup.ld
 *
 * Linker script for the i386 setup code
 */
OUTPUT_FORMAT("binary");

SECTIONS
{
	.text : AT(0x7C00) {
		header.o(.text);
	}

	.signature : AT(0x7DFE) {
		SHORT(0xAA55);
	}
}
