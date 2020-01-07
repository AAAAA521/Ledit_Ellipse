/*
 * *************************************************************************
 * * FILE: text.c
 * * DESCRIPTION: get data from text
 * *************************************************************************
 */

module textGet
{
	
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ldata.h"     /* Main UPI header. */

#define PI		3.14159265358979323846
#define SIZE		1
#define NUM_WG_POINTS	5
#define LEN_TEXT_WID	5
#define LEN_TEXT_HEI	40
#define POS_TEXT_X_STA	-1000
#define POS_TEXT_Y_CEN	200

#define NUM  56 //划分的份数

   //椭圆   1
  	void drawC_1( LCell Cell, LLayer Layer,  double offsetX, double offsetY )
	{
	    int i=0;
		int	cnt	= NUM;//划分的份数
		float x[NUM],y[NUM];
		float c= 400;//单位nm ，可以通过SIZE调整单位
		float b= 300;
		float a= sqrt(c*c+b*b);
		float e= c/a;
		float p= a*a/c-c;
		
		
		for ( i = 0; i < cnt ; i++ )
		{
			float tho = e*p/(1-e*cos(2*PI*i/NUM));//极坐标椭圆方程
			
			x[i]= tho*cos(2*PI*i/NUM);//极坐标转换为普通坐标
			y[i]= tho*sin(2*PI*i/NUM);
		}
		

        LPoint	*points;
		points = (LPoint *) malloc( (cnt) * sizeof(LPoint) );//get arm
		for ( i = 0; i < cnt ; i++ )
		{
			points[i] = LPoint_Set( x[i] * SIZE + offsetX, y[i] * SIZE + offsetY );//Ledit画点
		}
		LPolygon_New( Cell, Layer, points, cnt  );
		free( points );
		return;
	}
	
	
	// draw heart
	void drawC_2( LCell Cell, LLayer Layer,  double offsetX, double offsetY )
	{
	    int i=0;
		int	cnt	= NUM;//划分的份数
		float x[NUM],y[NUM];
		float a= 400;//单位nm ，可以通过SIZE调整单位
						
		
		for ( i = 0; i < cnt ; i++ )
		{
			float tho = a*(1-sin(2*PI*i/NUM));//极坐标圆心方程
			
			x[i]= tho*cos(2*PI*i/NUM);//极坐标转换为普通坐标
			y[i]= tho*sin(2*PI*i/NUM);
		}
		

        LPoint	*points;
		points = (LPoint *) malloc( (cnt) * sizeof(LPoint) );//get arm
		for ( i = 0; i < cnt ; i++ )
		{
			points[i] = LPoint_Set( x[i] * SIZE + offsetX, y[i] * SIZE + offsetY );//Ledit画点
		}
		LPolygon_New( Cell, Layer, points, cnt  );
		free( points );
		return;
	}
	

	void  drawRowland()
	{
		/*
		 * 绘图函数的入参必须指定cell、文件和图层，需先获取
		 * 获取当前cell和文件
		 */
		LCell	Cell_Now	= LCell_GetVisible();
		LFile	File_Now	= LCell_GetFile( Cell_Now );

		/* 获取当前图层 */
		LLayer Layer_Poly = LLayer_Find( File_Now, "Poly" );
		if ( !Layer_Poly )
		{
			LDialog_AlertBox( "There is no Poly layer.\nMake sure Poly is in the layer map!" );
			return;
		}

		/*LLayer Layer_Active = LLayer_Find( File_Now, "Active" );
		if ( !Layer_Active )
		{
			LDialog_AlertBox( "There is no Active layer.\nMake sure Poly is in the layer map!" );
			return;
		}

		LLayer Layer_Metal1 = LLayer_Find( File_Now, "Metal1" );
		if ( !Layer_Metal1 )
		{
			LDialog_AlertBox( "There is no N Select layer.\nMake sure Metal1 is in the layer map!" );
			return;
		}*/

		double	offsetX = 0;
		double	offsetY = 0;
		

		//椭圆
		drawC_1( Cell_Now, Layer_Poly, offsetX, offsetY );
		
		//heart
		//drawC_2( Cell_Now, Layer_Poly, offsetX, offsetY );

		return;
	}


	void  drawRowland_main( void )
	{
		LMacro_BindToHotKey( KEY_F1, "drawRowland", "drawRowland" );
	}
} /* end of module textGet */

drawRowland_main();