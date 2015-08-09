/*
 * setup.ld
 *
 * Linker script for the i386 setup code
 */
OUTPUT_ARCH("i386");
OUTPUT_FORMAT("binary", "binary", "binary");

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

	/DISCARD/ : {
		*(.eh_frame);
		*(.eh_frame_hdr);
	}
}
