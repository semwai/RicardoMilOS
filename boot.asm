org 0x7C00 ;�������� ����� BIOS
mov ah, 2  ;������� 2 ���������� 13 - �������� �� �������� ����� � ����������� ������
mov al, 25  ;����� �� ����� 5 ������� (512����*5)
mov bx, 0x1000 ; ����� � ����������� ������ ��� ������� ������
mov ch, 0 ; )
mov cl, 2 ; )
mov dh, 0 ;)
mov dl, 0x80 ;)
int 0x13 

 
mov ah, 2 ; �������� ����
mov al, 28
mov bx, 0x9000
mov ch, 0
mov cl, 49 ; 2 = 400 ,  4=600   , 30 = 0x3200  35=0�4400
mov dh, 0
mov dl, 0x80
int 0x13



mov ah, 2 ; �������� ������� ������� ���������� 
mov al, 60
mov bx, 0xC000
mov ch, 0
mov cl, 63 ; 2 = 400 ,  4=600   , 30 = 0x3200  35=0�4400
mov dh, 0
mov dl, 0x80
int 0x13


call init_Vesa ; ������������� �����������
 
cli ; ��������� ���������� 

mov ax, 0 ; �������� ���������� ��������
mov es, ax
mov ds, ax
mov ss, ax
mov fs, ax
mov gs, ax


 
lgdt[gdttable] ; ��������� �������, ��� �������� ����� ����� ���������� ���������

mov eax, cr0 ; ������������� 1� ��� � �������, ��� ����� ���������, ��� �� � ���������� ������
or eax, 1
mov cr0, eax

mov esi, [video_table+0x28]
mov [0x8000],esi ; �� ������ 0�8000 ������ ����� �������� ������ ������ �����������
mov esp, 0xFFFC ; ���������� �������� ��������� �����
jmp MYCODE:0x1000 ; ������� �� ���������� ����� �������� ��������� (main.c �������)
ret

init_Vesa:
	mov ax, 0x4f01 
	mov cx, 0x118 ; � ������� - https://www.osp.ru/pcworld/1998/07/159374/
	mov di, video_table ;���� ��������� 4*26 ���� ���������� �  ������������ 
	int 0x10
	
	mov ax, 0x4f02
	mov bx, 0x4118 ;4+�����(112) = 4112
	int 0x10 ;
ret


ret

gdt_start:
	null_desc:
		dd 0
		dd 0
	code_desc:
		dw 0xFFFF
		dw 0
		db 0
		db 0b10011010
		db 0b11001111
		db 0
	data_desc:
		dw 0xFFFF
		dw 0
		db 0
		db 0b10010010
		db 0b11001111
		db 0
gdt_end:

gdttable:
	dw gdt_end-gdt_start
	dd gdt_start
	
MYCODE: equ code_desc-gdt_start
MYDATA: equ data_desc-gdt_start


video_table: dd 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
