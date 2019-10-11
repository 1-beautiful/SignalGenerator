#include "gui.h"
#include "math.h"


//���ò�����ʱ����ʾ
void ShowParameterNumber()
{
	u16 x,y;
	
	//��ʾ��ֵ
	if(pm.flagParaSelected==ParaAM)
	{
		y=pm.amCoordinateY;
		x=pm.amCoordinateX;
		//x=16*7+x-16;
	
		POINT_COLOR=BLUE;
		BACK_COLOR=WHITE;
		if(pm.amArrayPoint==0)
		{
			POINT_COLOR=WHITE;
			BACK_COLOR=BLUE;
			LCD_ShowChar(x,y,pm.amArray[0]+'0',32,0);
			POINT_COLOR=BLUE;
			BACK_COLOR=WHITE;
		}
		else
			LCD_ShowChar(x,y,pm.amArray[0]+'0',32,0);
		
		x+=16;
		LCD_ShowChar(x,y,'.',32,0);
		x+=16;
		for(u8 i=1;i<pm.amLen;i++){
			if(i==pm.amArrayPoint)
			{
					POINT_COLOR=WHITE;
					BACK_COLOR=BLUE;
			}
			LCD_ShowChar(x,y,pm.amArray[i]+'0',32,0);
			x+=16;
			if(i==pm.amArrayPoint)
			{
					POINT_COLOR=BLUE;
					BACK_COLOR=WHITE;
			}
		}
	}
	//��ʾƵ��
	else 	if(pm.flagParaSelected==ParaFQ)
	{
		y=pm.fqCoordinateY;
		x=pm.fqCoordinateX;
		POINT_COLOR=BLUE;
		BACK_COLOR=WHITE;
		for(u8 i=0;i<pm.fqLen;i++){
			if(i==pm.fqArrayPoint)
			{
					POINT_COLOR=WHITE;
					BACK_COLOR=BLUE;
			}
			LCD_ShowChar(x,y,pm.fqArray[i]+'0',32,0);
			x+=16;
			if(i==pm.fqArrayPoint)
			{
					POINT_COLOR=BLUE;
					BACK_COLOR=WHITE;
			}
		}
	}
	//��ʾг���ϳ���
	else if(pm.flagParaSelected==ParaHAR)
	{
		y=pm.harCoordinateY;
		x=pm.harCoordinateX;
		POINT_COLOR=BLUE;
		BACK_COLOR=WHITE;
		for(u8 i=0;i<pm.harLen;i++)
		{
			if(i==pm.harArrayPoint)
			{
					POINT_COLOR=WHITE;
					BACK_COLOR=BLUE;
			}
			LCD_ShowChar(x,y,pm.harArray[i]+'0',32,0);
			x+=16;
			if(i==pm.harArrayPoint)
			{
					POINT_COLOR=BLUE;
					BACK_COLOR=WHITE;
			}
		}
	
	}

}


void GUI_ShowMenuItem(GUIMenu *gMenu)
{
	u16 n=GUI_ITEM_FONTSIZE+2*GUI_ITEM_FONT_MARGIN;
	
	//���Ʊ���
	LCD_Fill(0,0,LCD_WIDTH,n,BLACK);
	POINT_COLOR=WHITE;
	BACK_COLOR=BLACK;
  LCD_ShowString(GUI_ITEM_MARGIN,GUI_ITEM_FONT_MARGIN,LCD_WIDTH,GUI_ITEM_FONTSIZE,GUI_ITEM_FONTSIZE,gMenu->topicName);
	
	for(u8 i=0;i<gMenu->itemNum;i++){
		n+=GUI_ITEM_FONT_MARGIN;
		//���Ʋ˵���
		POINT_COLOR=gMenu->itemList[i].fontColor;	
		BACK_COLOR=gMenu->itemList[i].backgroundColor;  
		//����:x������Ļ��ߵľ���,y������Ļ����ľ���,������������λ�ַ��������Ͻ�	
		LCD_ShowString(GUI_ITEM_MARGIN,n,LCD_WIDTH,gMenu->itemList[i].fontSize,gMenu->itemList[i].fontSize,gMenu->itemList[i].name);
		
		POINT_COLOR=BLUE;
		n=n+GUI_ITEM_FONT_MARGIN+gMenu->itemList[i].fontSize;
		LCD_DrawLine(0,n,LCD_WIDTH,n);
	}
}

//��������
void GUI_ShowPowerOn(void)
{
		LCD_Clear(WHITE);
		GUI_DrawSineWave(200,RED);delay_ms(200);
		GUI_DrawTrianglewave(100,RED);delay_ms(200);
		GUI_DrawSquarewave(160,RED);delay_ms(200);
		GUI_DrawSquarewave(160,GREEN);delay_ms(100);
		GUI_DrawTrianglewave(100,GREEN);delay_ms(100);
		GUI_DrawSineWave(200,GREEN);delay_ms(100);
		
		u16 w=100,h=100;
		u16 x=60,y=80;
		//��ָ����������䵥����ɫ
		//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
		//color:Ҫ������ɫ
		LCD_Fill(x,y,w+x,y+h,BLUE);
		delay_ms(300);

		x+=20;
		y+=20;
		LCD_Fill(x,y,w+x,y+h,GREEN);
		delay_ms(300);
	
	POINT_COLOR=BLUE;
	BACK_COLOR=WHITE;
	LCD_ShowString(60,240,12*8,16,16,"version:v0.1");
	delay_ms(300);	  
	LCD_ShowString(24,210,16*12,24,24,"Signal Generator");
	

}


//�������Ҳ�
void GUI_DrawSineWave(u16 middleY,u32 color)
{
	double d=0;
	double r=0;
	int h=0,i=0;
	while(d<30)
	{
		r=sin(d);
		h = (int)(r * 20);
		h+=20;
		LCD_Fast_DrawPoint(i,h+middleY,color);
		i++;
		d+=0.1;
	}

}

//���Ʒ���
void GUI_DrawSquarewave(u16 middleY,u32 color)
{
	u16 a=0,b=0;
	POINT_COLOR=color;
	for(u8 i=0;i<6;i++)
	{
		b=middleY+20;
		LCD_DrawLine(a,b,a+20,b);
		a+=20;
		LCD_DrawLine(a,b,a,b-40);
		b-=40;
		LCD_DrawLine(a,b,a+20,b);
		a+=20;
		LCD_DrawLine(a,b,a,b+40);
		b+=40;
	}
}


//�������ǲ�
void GUI_DrawTrianglewave(u16 middleY,u32 color)
{
	u16 a=0;
	POINT_COLOR=color;
	for(u8 i=0;i<6;i++)
	{
		LCD_DrawLine(a,middleY+20,a+20,middleY-20);
		a+=20;
		LCD_DrawLine(a,middleY-20,a+20,middleY+20);
		a+=20;
	}

}









