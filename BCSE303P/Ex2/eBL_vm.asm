[BITS 16]; Convention: Backwards compatability
[ORG 0x7C00]; Origin. Allotted by convention

JMP $

TIMES 510 - ($ - $$) db 0;
DW 0xAA55
