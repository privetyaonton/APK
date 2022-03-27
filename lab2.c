#include <stdio.h>
#include <dos.h>

struct VIDEO{
	unsigned char symbol;
	unsigned char color;
};

char color = 0x89;

void print(){
	int i, val, temp;
	struct VIDEO far* screen = (struct VIDEO far *)MK_FP(0xB800, 0);   

	val = inp(0x21);                                    
	for (i = 0; i < 8; i++)                             
	{
		temp = val % 2;                                  
		val = val >> 1;                                  
		screen->symbol = temp + '0';                     
		screen->color = color;                       
		screen++;                                        
	}
	screen++;                                            

	val = inp(0xA1);                                     
	for (i = 0; i < 8; i++)								 
	{
		temp = val % 2;									 
		val = val >> 1;									 
		screen->symbol = temp + '0';					 
		screen->color = color;						
		screen++;										
	}
	screen += 63;									     
	outp(0x20,0x0A);                                     

	val = inp(0x20);                                
	for (i = 0; i < 8; i++)								 
	{
		temp = val % 2;									 
		val = val >> 1;									 
		screen->symbol = temp + '0';					 
		screen->color = color;						 
		screen++;										 
	}
	screen++;                                            

	outp(0xA0,0x0A);                                   
	val = inp(0xA0);                                   
	for (i = 0; i < 8; i++)								 
	{
		temp = val % 2;									
		val = val >> 1;									 
		screen->symbol = temp + '0';					 
		screen->color = color;						 
		screen++;										 
	}
	screen+=63;                                          

	outp(0x20,0x0B);                                     
	val = inp(0x20);                                   
	for (i = 0; i < 8; i++)                              
	{
		temp = val % 2;									 
		val = val >> 1;									 
		screen->symbol = temp + '0';					
		screen->color = color;						 
		screen++;										 
	}
	screen++;                                            
	 
	outp(0xA0,0x0B);                                     
	val = inp(0xA0);                                   
	for (i = 0; i < 8; i++)                              
	{
		temp = val % 2;								     
		val = val >> 1;									
		screen->symbol = temp + '0';					  
		screen->color = color;						 
		screen++;										 
	}
}



/////////////////////////////////////////////////////////

void interrupt(*oldint8)(void);
void interrupt(*oldint9)(void);
void interrupt(*oldint10)(void);
void interrupt(*oldint11)(void);
void interrupt(*oldint12)(void);
void interrupt(*oldint13)(void);
void interrupt(*oldint14)(void);
void interrupt(*oldint15)(void);

void interrupt(*oldint70)(void);
void interrupt(*oldint71)(void);
void interrupt(*oldint72)(void);
void interrupt(*oldint73)(void);
void interrupt(*oldint74)(void);
void interrupt(*oldint75)(void);
void interrupt(*oldint76)(void);
void interrupt(*oldint77)(void);

/////////////////////////////////////////////////////////

void interrupt newint08(void) { print(); oldint8(); }
void interrupt newint09(void) { print(); oldint9(); }
void interrupt newint0A(void) { print(); oldint10(); }
void interrupt newint0B(void) { print(); oldint11(); }
void interrupt newint0C(void) { print(); oldint12(); }
void interrupt newint0D(void) { print(); oldint13(); }
void interrupt newint0E(void) { print(); oldint14(); }
void interrupt newint0F(void) { print(); oldint15(); }

void interrupt newint70(void) { print(); oldint70(); }
void interrupt newint71(void) { print(); oldint71(); }
void interrupt newint72(void) { print(); oldint72(); }
void interrupt newint73(void) { print(); oldint73(); }
void interrupt newint74(void) { print(); oldint74(); }
void interrupt newint75(void) { print(); oldint75(); }
void interrupt newint76(void) { print(); oldint76(); }
void interrupt newint77(void) { print(); oldint77(); }

/////////////////////////////////////////////////////////

void init(){
	oldint8 = getvect(0x08);
	oldint9 = getvect(0x09);
	oldint10 = getvect(0x0A);
	oldint11 = getvect(0x0B);
	oldint12 = getvect(0x0C);
	oldint13 = getvect(0x0D);
	oldint14 = getvect(0x0E);
	oldint15 = getvect(0x0F);


	oldint70 = getvect(0x70);
	oldint71 = getvect(0x71);
	oldint72 = getvect(0x72);
	oldint73 = getvect(0x73);
	oldint74 = getvect(0x74);
	oldint75 = getvect(0x75);
	oldint76 = getvect(0x76);
	oldint77 = getvect(0x77);

	setvect(0x08, newint08);
	setvect(0x09, newint09);
	setvect(0x0A, newint0A);
	setvect(0x0B, newint0B);
	setvect(0x0C, newint0C);
	setvect(0x0D, newint0D);
	setvect(0x0E, newint0E);
	setvect(0x0F, newint0F);

	setvect(0x70, newint70);
	setvect(0x71, newint71);
	setvect(0x72, newint72);
	setvect(0x73, newint73);
	setvect(0x74, newint74);
	setvect(0x75, newint75);
	setvect(0x76, newint76);
	setvect(0x77, newint77);




	_disable();


	outp(0x20, 0x11);
	outp(0x21, 0x08);
	outp(0x21, 0x04);
	outp(0x21, 0x01);

	outp(0xA0, 0x11);
	outp(0xA1, 0x70);
	outp(0xA1, 0x02);
	outp(0xA1, 0x01);


	_enable();

}

/////////////////////////////////////////////////////////

int main(){
	unsigned far *fp;
	system("cls");
	init();
	

	FP_SEG(fp) = _psp;                          
	FP_OFF(fp) = 0x2c;                          
	_dos_freemem(*fp);                         

	_dos_keep(0, (_DS - _CS) + (_SP / 16) + 1); 

	return 0;
}



