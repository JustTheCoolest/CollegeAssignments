[BITS 16]; Convention: Backwards compatability
[ORG 0x7C00]; Origin. Allotted by convention

mov si, text_label
mov bx, 24h
.loop: lodsb

mov ah, 0x09
or al, al
jz halt
mov cx, 1h
int 0x10; calls video service and executes instruction in AH
inc dl
mov ah, 2h
int 10h
jmp .loop

halt: cli
hlt

text_label: db "Balu", 0
TIMES 510 - ($ - $$) db 0;
DW 0xAA55
