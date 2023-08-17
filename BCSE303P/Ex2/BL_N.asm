[BITS 16]; Convention: Backwards compatability
[ORG 0x7C00]; Origin. Allotted by convention

mov si, text_label
mov ah, 0x0e

.loop: lodsb
or al, al
jz halt
int 0x10; calls video service and executes instruction in AH
jmp .loop

halt: cli
hlt

text_label: db "Andhavarapu Balu", 0
TIMES 510 - ($ - $$) db 0;
DW 0xAA55
