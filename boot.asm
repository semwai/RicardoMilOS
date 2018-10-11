org 0x7C00 ;смещение после BIOS
mov ah, 2  ;функция 2 прерывания 13 - загрузка из жесткого диска в оперативную память
mov al, 25  ;берем из диска 5 сектора (512байт*5)
mov bx, 0x1000 ; адрес в оперативной памяти для вставки данных
mov ch, 0 ; )
mov cl, 2 ; )
mov dh, 0 ;)
mov dl, 0x80 ;)
int 0x13 

 
mov ah, 2 ; загрузка букв
mov al, 28
mov bx, 0x9000
mov ch, 0
mov cl, 49 ; 2 = 400 ,  4=600   , 30 = 0x3200  35=0х4400
mov dh, 0
mov dl, 0x80
int 0x13



mov ah, 2 ; загрузка Рикардо рикардо рикардочки 
mov al, 60
mov bx, 0xC000
mov ch, 0
mov cl, 63 ; 2 = 400 ,  4=600   , 30 = 0x3200  35=0х4400
mov dh, 0
mov dl, 0x80
int 0x13


call init_Vesa ; инициализация видеорежима
 
cli ; отключаем прерывания 

mov ax, 0 ; обнуляем сегментные регистры
mov es, ax
mov ds, ax
mov ss, ax
mov fs, ax
mov gs, ax


 
lgdt[gdttable] ; загружаем таблицу, где хранятся флаги нашей запущенной программы

mov eax, cr0 ; устанавливаем 1й бит в единицу, тем самым указываем, что мы в защищенном режиме
or eax, 1
mov cr0, eax

mov esi, [video_table+0x28]
mov [0x8000],esi ; по адресу 0х8000 теперь будет значение адреса начала видеопамяти
mov esp, 0xFFFC ; выставляем значение положения стека
jmp MYCODE:0x1000 ; прыгаем на выполнение нашей основной программы (main.c которая)
ret

init_Vesa:
	mov ax, 0x4f01 
	mov cx, 0x118 ; о режимах - https://www.osp.ru/pcworld/1998/07/159374/
	mov di, video_table ;сюда запишется 4*26 байт информации о  видеосистеме 
	int 0x10
	
	mov ax, 0x4f02
	mov bx, 0x4118 ;4+режим(112) = 4112
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
