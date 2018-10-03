#define WIDTH 1024 
#define HEIGHT 768
#define TEXTBOX_X 0
#define TEXTBOX_Y 0
#define TEXTBOX_W 15
#define TEXTBOX_H 15
#define FONT_WIDTH 9
#define FONT_HEIGT 16

void draw_pixel(int, int, int);
void draw_rect(int x, int y, int sizeX, int sizeY, int color);
void delay(int);
void draw_symb(int,int,char,int);
void draw_char(int,int,char,int);
void draw_str(int,int,char*,int);
int getKey();
void CoordUp();
void CoordDown();
void ScrollUp();
int BackgroundColor;
int FONT_SCALE; //то, во сколько раз будет больше шрифт
int x=0, y=0; // позиция курсора у текстбокса
int Start()
{  
	BackgroundColor = 0;//0x00BFFF;
	FONT_SCALE = 3;
	x=TEXTBOX_X;
	y=TEXTBOX_Y;
	char inputArray[64];//Массив, в котором хранится последняя строка
	int inputLen=0; //длина введенной строки
	int i, j,newKey,oldKey;
	char ScanToTable[256]=
	{0,0,16,17,18,19,20,21,22,23,
	 24,15,0,0,0,0,48,54,36,49,
	 51,56,52,40,46,47,0,0,0,0,
	 32,50,35,37,38,39,41,42,43,26,
	 95,0,0,0,57,55,34,53,33,45,
	 44,11,13,14,0,0,0,-1};

	//очистка экрана фоновым цветом
	draw_rect(0,0,WIDTH,HEIGHT,BackgroundColor);

	//убери комменты и посмотри на буквы
	/*for (j=0;j<6;j++)
		for (i=0;i<22;i++)
			draw_symb(i*(FONT_WIDTH+4)*FONT_SCALE,270+(FONT_HEIGT+1)*j*FONT_SCALE,j*22+i,0xFFFFFF);
	FONT_SCALE = 2;

	for (j=0;j<10;j++)
			draw_symb(280 + j*(FONT_WIDTH+4)*FONT_SCALE,270,j+32,0xFFFFFF);
	FONT_SCALE = 3;
	for (j=0;j<10;j++)
			draw_symb(280 + j*(FONT_WIDTH+4)*FONT_SCALE,300,j+32,0xFFFFFF);
	FONT_SCALE = 4;
	for (j=0;j<10;j++)
			draw_symb(280 + j*(FONT_WIDTH+4)*FONT_SCALE,340,j+32,0xFFFFFF);
	FONT_SCALE = 5;
	for (j=0;j<10;j++)
			draw_symb(280 + j*(FONT_WIDTH+4)*FONT_SCALE,385,j+32,0xFFFFFF);
	FONT_SCALE = 6;
	for (j=0;j<10;j++)
			draw_symb(280 + j*(FONT_WIDTH+4)*FONT_SCALE,440,j+32,0xFFFFFF);
	FONT_SCALE = 3;*/
	
    //Красивые рамки для ввода букав
	draw_rect(TEXTBOX_X-10,TEXTBOX_Y-10,(TEXTBOX_W)*FONT_WIDTH*FONT_SCALE + 20, (TEXTBOX_H)*FONT_HEIGT*FONT_SCALE+16 ,0x333333);
	draw_rect(TEXTBOX_X,TEXTBOX_Y      ,(TEXTBOX_W)*FONT_WIDTH*FONT_SCALE + 5,  (TEXTBOX_H)*FONT_HEIGT*FONT_SCALE+1,BackgroundColor);
    while(1){
    	newKey = getKey();
    	if (oldKey==newKey || newKey==0)
    		continue;
  
    	switch (newKey){
    		case 1://esc
    			return 0;
    		break;
    		/*case 2: 
    			FONT_SCALE=1;
    			draw_rect(100,100,200,200,0);
    		break;
    		case 3: 
    			FONT_SCALE++;
    		break;*/
    		case 14://backspace
				draw_rect(x,y+FONT_HEIGT*FONT_SCALE-3,FONT_WIDTH*FONT_SCALE,2,BackgroundColor);
				if (inputLen)
		    		CoordDown();
		    	draw_rect(x,y,FONT_WIDTH*FONT_SCALE,FONT_HEIGT*FONT_SCALE,BackgroundColor);
		    	draw_rect(x,y+FONT_HEIGT*FONT_SCALE-3,FONT_WIDTH*FONT_SCALE,2,0xFFFFFF);
		    	if (inputLen){
		    		inputArray[inputLen--]=0;
		    	}
    		break;
    		case 28://enter
    			draw_rect(x,y+FONT_HEIGT*FONT_SCALE-3,FONT_WIDTH*FONT_SCALE,2,BackgroundColor);
    			x=TEXTBOX_X;
    			y+=FONT_HEIGT*FONT_SCALE; 		
    			if (y>TEXTBOX_Y+FONT_HEIGT*TEXTBOX_H*FONT_SCALE-1){
    				y-=FONT_HEIGT*FONT_SCALE;
    				ScrollUp();
    			}
    			draw_rect(x,y+FONT_HEIGT*FONT_SCALE-3,FONT_WIDTH*FONT_SCALE,2,0XFFFFFF);
    			//отрисовка последней введенной строки и однуление буфера ввода
    			FONT_SCALE=1;
    			draw_rect(0,753,WIDTH,FONT_HEIGT*FONT_SCALE,BackgroundColor);
    			for (i=0;i<inputLen;i++){
    				draw_symb(i*FONT_WIDTH*FONT_SCALE,753,inputArray[i],0XFFFFFF);
    				inputArray[i]=0;
    			}
    			inputLen=0;
    			FONT_SCALE=3;
    		break;
    		default:
    			if (ScanToTable[newKey]!=0){
    				draw_char(x,y,ScanToTable[newKey],0xFFFAFA);
    				if (inputLen<64){
    					
    					inputArray[inputLen++]=ScanToTable[newKey];
    				}
    				
    			}
    		break;
    	}
    	oldKey=newKey;	 
    }
	//asm("HLT");//остановка процессора
}
void ScrollUp(){
	int i,j;
	char *p;
	char *d;
	char *e;
	asm("mov eax, dword ptr[ds:0x8000]");
	asm("mov dword ptr[ebp-12], eax");
	for (i=TEXTBOX_Y;i<TEXTBOX_Y+(TEXTBOX_H)*FONT_HEIGT*FONT_SCALE;i++)
		for (j=TEXTBOX_X;j<TEXTBOX_X+(TEXTBOX_W)*FONT_WIDTH*FONT_SCALE;j++)
		{
			d = p + (i*WIDTH+j)*3;
			e = d+ WIDTH*3*FONT_HEIGT*FONT_SCALE;	
			if (i >= TEXTBOX_Y+(TEXTBOX_H-1)*FONT_HEIGT*FONT_SCALE)
				*(int*)d = BackgroundColor;
			else 
				*(int*)d = *(int*)e;
		}
}
void CoordUp()
{
	draw_rect(x,y+FONT_HEIGT*FONT_SCALE-3,FONT_WIDTH*FONT_SCALE,2,BackgroundColor);
	x+=FONT_WIDTH*FONT_SCALE;
	if (x>(TEXTBOX_X+(TEXTBOX_W-1)*FONT_WIDTH*FONT_SCALE))
	{
		x=TEXTBOX_X;
		y+=FONT_HEIGT*FONT_SCALE;
	}
	if (y>(TEXTBOX_Y+(TEXTBOX_H-1)*FONT_HEIGT*FONT_SCALE))
		{ScrollUp();
		 y-=FONT_HEIGT*FONT_SCALE;
		}
	draw_rect(x,y+FONT_HEIGT*FONT_SCALE-3,FONT_WIDTH*FONT_SCALE,2,0xFFFFFF);
}
void CoordDown(){
	if (x>=FONT_WIDTH*FONT_SCALE+TEXTBOX_X)
		x-=FONT_WIDTH*FONT_SCALE;
	else {
		if (y>TEXTBOX_Y) {
			y-=FONT_HEIGT*FONT_SCALE;
			x=TEXTBOX_X+FONT_WIDTH*(TEXTBOX_W-1)*FONT_SCALE;
		}
	}
}
int getKey(){
 	asm("_test:");
	asm("in al,0x64");
	asm("and al,0x20");
	asm("jnz _test");
	asm("xor eax,eax");
	asm("in al,0x60"); 
}
void draw_char(int x,int y,char num,int color){
	 draw_symb( x,  y+1, num, color);
	 CoordUp();
}
void draw_symb(int x, int y,char num,int color){
	char* data_ptr=(char*)0x9000;
	data_ptr+=num*FONT_HEIGT*FONT_WIDTH;
	int i,j,k,r;
	for (j=0;j<FONT_HEIGT;j++)
		for (i=0;i<FONT_WIDTH;i++){
			if (*data_ptr == 0x23){

				for(k=0;k<FONT_SCALE;k++)
					for(r=0;r<FONT_SCALE;r++)
						draw_pixel(x+i*FONT_SCALE+k,y+j*FONT_SCALE+r,color);
			}
			else 
				for(k=0;k<FONT_SCALE;k++)
					for(r=0;r<FONT_SCALE;r++)
						draw_pixel(x+i*FONT_SCALE+k,y+j*FONT_SCALE+r,BackgroundColor);
							
			data_ptr++;
		}
}
void draw_rect(int x, int y, int sizeX, int sizeY, int color)
{
	int i, j;
	for(i=y;i<sizeY+y;i++)
		for(j=x;j<sizeX+x;j++)
			draw_pixel(j, i, color);
}
void draw_pixel(int x, int y, int color)
{
	if (x<0||y<0||x>=WIDTH||y>=HEIGHT)
		return;
	char* p;
	asm("mov eax, dword ptr[ds:0x8000]");
	asm("mov dword ptr[ebp-4], eax");
	p+=(y*(WIDTH)+x)*3;
	*(int*)p=color;
}
void delay(int amount)
{
	int i=0;
	while((i++)<amount*65536){;}
}