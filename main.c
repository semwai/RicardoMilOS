#define WIDTH 1024 
#define HEIGHT 768
#define TEXTBOX_X 0
#define TEXTBOX_Y 0
#define TEXTBOX_W 38
#define TEXTBOX_H 10
#define FONT_WIDTH 9
#define FONT_HEIGT 16

void draw_pixel(int, int, int);
void draw_rect(int x, int y, int sizeX, int sizeY, int color);
void delay(int);
void draw_symb(int,int,char,int);
void draw_char(int,int,char,int);
int getKey();
void CoordUp();
void CoordDown();
void ScrollUp();
void go_gemo();
//void draw_symb_transparent(int,int,char,int);
void plzstop();
void luxury_art(int,int,char*,int,int);
void calc();
void draw_str(char*,int);
void ASCIIstrToMy(char*);
int AsciiToMy(int);
int BackgroundColor;
int FONT_SCALE; //?, ? ???? ????????????
int KEY_COLOR;
int x=0, y=0; // ???? ??????????
int Start()
{  

	BackgroundColor = 0;//0x00BFFF;
	FONT_SCALE=1;
	KEY_COLOR = 0xFFFFFF;
	x=TEXTBOX_X;
	y=TEXTBOX_Y;
	char inputArray[20];//???, ?????????? ????? ???
	int inputLen=0; //???????????
	int i, j,newKey,oldKey;
	char ScanToTable[256]=
	{0,0,16,17,18,19,20,21,22,23,
	 24,15,0,0,0,0,48,54,36,49,
	 51,56,52,40,46,47,0,0,0,0,
	 32,50,35,37,38,39,41,42,43,26,
	 95,0,0,0,57,55,34,53,33,45,
	 44,11,13,14,0,0,0,-1};

	char commands[4][10] = {
	"CALC",
	"EXIT",
	"SYMBOLS",
	"LOL"
	};

	//???? ??? ?? ????????????????? ascii ???
	ASCIIstrToMy(commands[0]);
	ASCIIstrToMy(commands[1]);
	ASCIIstrToMy(commands[2]);
	ASCIIstrToMy(commands[3]);
	//????????????????
	
	go_gemo();
	//delay(5000);
	FONT_SCALE = 3;
	draw_rect(0,0,WIDTH,HEIGHT,BackgroundColor);
	
	
    //?????????? ??????
	draw_rect(TEXTBOX_X-10,TEXTBOX_Y-10,(TEXTBOX_W)*FONT_WIDTH*FONT_SCALE + 20, (TEXTBOX_H)*FONT_HEIGT*FONT_SCALE+16 ,0x333333);
	draw_rect(TEXTBOX_X,TEXTBOX_Y      ,(TEXTBOX_W)*FONT_WIDTH*FONT_SCALE + 5,  (TEXTBOX_H)*FONT_HEIGT*FONT_SCALE+1,BackgroundColor);
    
	 
    while(1){
    	newKey = getKey();
    	if (oldKey==newKey || newKey==0)
    		continue;
  
    	switch (newKey){
    		//case 1://esc
    		//	return 0;
    		break;
    		
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
    			newline();
    			
    			if (!StrCmp(inputArray,commands[0]))
    				calc();
    			if (!StrCmp(inputArray,commands[1]))
    				return 0;
    			if (!StrCmp(inputArray,commands[2]))
    				symbols();
    			

    			draw_rect(x,y+FONT_HEIGT*FONT_SCALE-3,FONT_WIDTH*FONT_SCALE,2,0XFFFFFF);
    			//?????????????????? ????????? ???
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
    				draw_char(x,y,ScanToTable[newKey],KEY_COLOR);
    				if (inputLen<20){
    					
    					inputArray[inputLen++]=ScanToTable[newKey];
    				}
    				
    			}
    		break;
    	}
    	oldKey=newKey;	 
    }
	//asm("HLT");//??????????
}

void newline(){
	draw_rect(x,y+FONT_HEIGT*FONT_SCALE-3,FONT_WIDTH*FONT_SCALE,2,BackgroundColor);
	x=TEXTBOX_X;
    y+=FONT_HEIGT*FONT_SCALE; 		
    if (y>TEXTBOX_Y+FONT_HEIGT*TEXTBOX_H*FONT_SCALE-1){
    	y-=FONT_HEIGT*FONT_SCALE;
    	ScrollUp();
    }
}
void go_gemo(){
	square_recursion(WIDTH/2,HEIGHT/2,WIDTH/2,9);
	int key;
	delay(2000);
	char str[] = "RicardoMilOS";
	ASCIIstrToMy(str);
	luxury_art(WIDTH/2,HEIGHT/2+100,str,0xFF0000,9);
	FONT_SCALE = 3;
	char str2[] = "PRESS ENTER TO ENJOY";
	int r = 128;
	
	
	do{
		key = getKey();
		r++;
		delay(10);
		draw_str_coord(str2,128+r%127<<16,250,550);
	} while(key!=28);
}

void RicardoMilOS(int x,int y,int s){
	int i,j;
	
	int k=0;
	int ii,jj;
		char*p=0xFFF2+44*20+3*9;
		for (i=39;i>0;i--)
			for (j=0;j<44;j++){
				for (ii=0;ii<s;ii++)
					for (jj=0;jj<s;jj++)
						draw_pixel(x+j*s+ii,y+i*s+jj,*p%255<<24  | (*(p+1)%255)<<16| (*(p+2)%255)<<8 ); 
				p+=3;
			}
	
}
void square_recursion(x,y,r,n){
	if(n==0)
		return;
	draw_rect(x,y,r,r,x*y<<8+(255-x));
	draw_rect(x+1,y+1,r-2,r-2,0);
	square_recursion(x+r/2,y+r/2,r/2,n-1);
	square_recursion(x-r/2,y+r/2,r/2,n-1);
	square_recursion(x-r/2,y-r/2,r/2,n-1);
	square_recursion(x+r/2,y-r/2,r/2,n-1);
}
void nice_rect(int x,int y,int w,int h){

	int k,l;
			for (k=x;k<x+w;k++){
				for (l=y;l<y+h;l++){
					draw_pixel(k,l,k*l%127<<16 | ((k*l/16)%127<<8) );
			
				}
				
			}
}
void luxury_art(int x,int y,char* symb,int color,int iteration){
	int i,j;
 
	nice_rect(0,0,WIDTH,HEIGHT);
	for (j=1;j<=iteration;j++){
		FONT_SCALE=j;
			//int*p = (int*)0x7f80;

			nice_rect(0,y- FONT_HEIGT*FONT_SCALE/2,WIDTH,FONT_HEIGT*FONT_SCALE);
			for (i=0;symb[i];i++)
				draw_symb(x - FONT_WIDTH*FONT_SCALE/2 +(i-5)*FONT_WIDTH*FONT_SCALE- FONT_WIDTH*FONT_SCALE/2 ,y- FONT_HEIGT*FONT_SCALE/2 ,symb[i],color);
			RicardoMilOS(WIDTH/2-22*j,0,j);
			delay(110);
		
	}
	//delay(1000);
}
void symbols(){
	int  i;
	for (i=0;i<100;i++)
		draw_char(x,y,i,0X00FF00);	
	
	newline();
}
void calc(){
	
	//char str[22] = "CALC:";
	int first_number = 0;
	int second_number = 0;
	KEY_COLOR = 0xFF0000;
	//draw_str(str,KEY_COLOR);
	//newline();
	
	 
	first_number = get_number();
	//newline();
	int oldKey,newKey;
	int sign=0;
	while(1){
		newKey=getKey();
		if (newKey==0 || newKey==oldKey) continue;
		if (newKey==13){
			sign = '+';
			draw_char(x,y,'+'-33,KEY_COLOR);
			//break;
		}
		if (newKey==12){
			sign = '-';
			draw_char(x,y,'-'-33,KEY_COLOR);
			//break;
		}
		if (newKey==9){
			sign = '*';
			draw_char(x,y,'*'-33,KEY_COLOR);
			//break;
		}
		if (newKey==53){
			sign = '/';
			draw_char(x,y,'/'-33,KEY_COLOR);
			//break;
		}
		if (newKey==28)
			if (sign)
				break;
		oldKey=newKey;
	}
	//newline();
	second_number = get_number();


	char str2[] = "NaN";
	ASCIIstrToMy(str2);
	//newline();
	draw_char(x,y,'='-33,KEY_COLOR);
	switch (sign){
		case '+':
			draw_numb(first_number+second_number);
		break;
		case '-':
			draw_numb(first_number-second_number);
		break;
		case '*':
			draw_numb(first_number*second_number);
		break;
		case '/':
			if (second_number)
				draw_numb(first_number/second_number);
			else
				draw_char(x,y,str2,KEY_COLOR);
		break;
	}
	
	newline();
	KEY_COLOR=0xFFFFFF;
	return;
}
int get_number(){
	int number=0;
	int newKey,oldKey;
	delay(300);
	while(1){
		newKey=getKey();
		if (newKey==oldKey || newKey==0)
			continue;
		if (newKey>1&&newKey<11){
			draw_char(x,y,newKey+14,KEY_COLOR);
			number*=10;
			number+=newKey-1;
		}
		if (newKey==11)
			if (number){
				draw_char(x,y,15,KEY_COLOR);
				number*=10;
			}
		if (newKey==14){
			if (number){
				draw_rect(x,y,FONT_WIDTH*FONT_SCALE,FONT_HEIGT*FONT_SCALE,BackgroundColor);
				CoordDown();
				draw_rect(x,y,FONT_WIDTH*FONT_SCALE,FONT_HEIGT*FONT_SCALE,BackgroundColor);
				number/=10;
			}
		}
		if (newKey==28)
		break;
		oldKey=newKey;
	}	
	return number;
}

void draw_numb(int num){
	int count = 0;
	int num2= num;
	do{
		
		num2/=10;
		count++;
	} while(num2);

	int symb;
	int x_old = x;
	do{
		symb = num%10;
		num/=10;
		draw_char((count-1)*FONT_WIDTH*FONT_SCALE+ x_old ,y,symb+15,KEY_COLOR);
		count--;
	} while(num);
	
}
void draw_str_coord(char * str,int color,int x,int y){
	int i;
	for(i=0;str[i];i++){
		if (str[i]!=' '){
			draw_symb(x+i*FONT_WIDTH*FONT_SCALE,y,str[i]-33,color);
		}else{
			draw_symb(x+i*FONT_WIDTH*FONT_SCALE,y,-1,color);
		}
	}
}
void draw_str(char * str,int color){
	int i;
	for(i=0;str[i];i++){
		if (str[i]!=' '){
			draw_char(x,y,str[i]-33,color);
		}else{
			draw_char(x,y,-1,color);	
		}
	}
}
void ASCIIstrToMy(char *a){
	int i;
	for (i=0;a[i];a[i]-=33,i++);
}
int StrCmp(char *a,char*b){
	int i,j;
	for ( i=0;a[i];i++);
	for ( j=0;b[j];j++);
	if (i!=j) return 1;
	if (i>j){
		for (j=0;b[j];j++)
			if (b[j]!=a[j]) return 1;
	}else{
		for (i=0;a[i];i++)
			if (b[i]!=a[i]) return 1;
	}
	
	return 0;
}
int AsciiToMy(int a){
	return (a-33);//???? ??? ???????? ???? ? 33 ???
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
			/*else 
				for(k=0;k<FONT_SCALE;k++)
					for(r=0;r<FONT_SCALE;r++)
						draw_pixel(x+i*FONT_SCALE+k,y+j*FONT_SCALE+r,BackgroundColor);
					*/		
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
	char* p=0;
	asm("mov eax, dword ptr[ds:0x8000]");
	asm("mov dword ptr[ebp-4], eax");
	p+=(y*(WIDTH)+x)*3;
	*(char*)p=color&255;
	*(char*)(p+1)=(color>>8)&255;
	*(char*)(p+2)=(color>>16)&255;
}
void delay(int amount)
{
	int i=0;
	while((i++)<amount*65536){;}
}