//-------------------------------------------------------------------------------------------------------------------
//  简介:八邻域图像处理
//  代码类型：嵌入式系统的图像处理代码。
//------------------------------------------------------------------------------------------------------------------
#include "image.h"


int my_abs(int value)
{
	if (value >= 0) return value;
	else return -value;
}

int16 limit_a_b(int16 x, int a, int b)
{
	if (x < a) x = a;
	if (x > b) x = b;
	return x;
}


int16 limit1(int16 x, int16 y)
{
	if (x > y)             return y;
	else if (x < -y)       return -y;
	else                return x;
}



uint8 original_image[image_h][image_w];
uint8 image_thereshold;//图像分割阈值

void Get_image(uint8(*mt9v03x_image)[image_w])
{
#define use_num		1	
	uint8 i = 0, j = 0, row = 0, line = 0;
	for (i = 0; i < image_h; i += use_num)          //
	{
		for (j = 0; j < image_w; j += use_num)     //
		{
			original_image[row][line] = mt9v03x_image[i][j];
			line++;
		}
		line = 0;
		row++;
	}
}

uint8 otsuThreshold(uint8* image, uint16 col, uint16 row)
{
#define GrayScale 256
	uint16 Image_Width = col;
	uint16 Image_Height = row;
	int X; uint16 Y;
	uint8* data = image;
	int HistGram[GrayScale] = { 0 };

	uint32 Amount = 0;
	uint32 PixelBack = 0;
	uint32 PixelIntegralBack = 0;
	uint32 PixelIntegral = 0;
	int32 PixelIntegralFore = 0;
	int32 PixelFore = 0;
	double OmegaBack = 0, OmegaFore = 0, MicroBack = 0, MicroFore = 0, SigmaB = 0, Sigma = 0; // 类间方差;
	uint8 MinValue = 0, MaxValue = 0;
	uint8 Threshold = 0;


	for (Y = 0; Y < Image_Height; Y++) //Y<Image_Height改为Y =Image_Height；以便进行 行二值化
	{
		//Y=Image_Height;
		for (X = 0; X < Image_Width; X++)
		{
			HistGram[(int)data[Y * Image_Width + X]]++; //统计每个灰度值的个数信息
		}
	}
	for (MinValue = 0; MinValue < 256 && HistGram[MinValue] == 0; MinValue++);        //获取最小灰度的值
	for (MaxValue = 255; MaxValue > MinValue && HistGram[MinValue] == 0; MaxValue--); //获取最大灰度的值

	if (MaxValue == MinValue)
	{
		return MaxValue;          // 图像中只有一个颜色
	}
	if (MinValue + 1 == MaxValue)
	{
		return MinValue;      // 图像中只有二个颜色
	}

	for (Y = MinValue; Y <= MaxValue; Y++)
	{
		Amount += HistGram[Y];        //  像素总数
	}

	PixelIntegral = 0;
	for (Y = MinValue; Y <= MaxValue; Y++)
	{
		PixelIntegral += HistGram[Y] * Y;//灰度值总数
	}
	SigmaB = -1;
	for (Y = MinValue; Y < MaxValue; Y++)
	{
		PixelBack = PixelBack + HistGram[Y];    //前景像素点数
		PixelFore = Amount - PixelBack;         //背景像素点数
		OmegaBack = (double)PixelBack / Amount;//前景像素百分比
		OmegaFore = (double)PixelFore / Amount;//背景像素百分比
		PixelIntegralBack += HistGram[Y] * Y;  //前景灰度值
		PixelIntegralFore = PixelIntegral - PixelIntegralBack;//背景灰度值
		MicroBack = (double)PixelIntegralBack / PixelBack;//前景灰度百分比
		MicroFore = (double)PixelIntegralFore / PixelFore;//背景灰度百分比
		Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);//g
		if (Sigma > SigmaB)//遍历最大的类间方差g
		{
			SigmaB = Sigma;
			Threshold = (uint8)Y;
		}
	}
	return Threshold;
}

uint8 bin_image[image_h][image_w];//图像数组
void turn_to_bin(void)
{
	uint8 i, j;
	image_thereshold = otsuThreshold(original_image[0], image_w, image_h);
	for (i = 0; i < image_h; i++)
	{
		for (j = 0; j < image_w; j++)
		{
			if (original_image[i][j] > image_thereshold)bin_image[i][j] = white_pixel;
			else bin_image[i][j] = black_pixel;
		}
	}
}



uint8 start_point_l[2] = { 0 };//左边起点的x，y值
uint8 start_point_r[2] = { 0 };//右边起点的x，y值
uint8 get_start_point(uint8 start_row)
{
	uint8 i = 0, l_found = 0, r_found = 0;
	//清零
	start_point_l[0] = 0;//x
	start_point_l[1] = 0;//y

	start_point_r[0] = 0;//x
	start_point_r[1] = 0;//y

	//从中间往左边，先找起点
	for (i = image_w / 2; i > border_min; i--)
	{
		start_point_l[0] = i;//x
		start_point_l[1] = start_row;//y
		if (bin_image[start_row][i] == 255 && bin_image[start_row][i - 1] == 0)
		{
			//printf("找到左边起点image[%d][%d]\n", start_row,i);
			l_found = 1;
			break;
		}
	}

	for (i = image_w / 2; i < border_max; i++)
	{
		start_point_r[0] = i;//x
		start_point_r[1] = start_row;//y
		if (bin_image[start_row][i] == 255 && bin_image[start_row][i + 1] == 0)
		{
			//printf("找到右边起点image[%d][%d]\n",start_row, i);
			r_found = 1;
			break;
		}
	}

	if (l_found && r_found)return 1;
	else {
		//printf("未找到起点\n");
		return 0;
	}
}

//
//这段代码是一个图像处理的程序，主要实现了图像二值化和搜寻车道起始点的功能。下面是对代码的逐行分析解释：
//
//#include "image.h"：  引用外部的头文件 image.h。
//
//int my_abs(int value)：   自己定义的一个求整数绝对值的函数。
//
//int16 limit_a_b(int16 x, int a, int b)：   自己定义的一个函数，用于将一个整数限制在一个范围内，当它的值小于 a 时将它设为 a，当它的值大于 b 时将它设为 b，并返回限制后的值。
//
//int16 limit1(int16 x, int16 y)：   自己定义的一个函数，用于将一个整数限制在一个范围内，当它的值小于 - y 时将它设为 - y，当它的值大于 y 时将它设为 y，并返回限制后的值。
//
//uint8 original_image[image_h][image_w]; ：   定义了一个二维数组用于储存原始图像的像素值。
//
//uint8 image_thereshold; ：   定义了一个 uint8 类型的变量，用于存储图像二值化的阈值。
//
//void Get_image(uint8(*mt9v03x_image)[image_w])：   定义了一个函数，用于将摄像头采集的图像传入并进行预处理。
//
//uint8 otsuThreshold(uint8* image, uint16 col, uint16 row)：   定义了一个函数，用于对图像进行二值化处理，返回二值化的阈值。
//
//uint8 bin_image[image_h][image_w]; ：   定义了一个二维数组，用于储存二值化后的像素值。
//
//void turn_to_bin(void)：   定义了一个函数，用于将原始图像进行二值化处理，将结果存储到 bin_image 数组中。
//
//uint8 start_point_l[2] = { 0 };//左边起点的x，y值：   定义了一个数组用于存储左侧车道的起始位置。
//
//uint8 start_point_r[2] = { 0 };//右边起点的x，y值：    定义了一个数组用于存储右侧车道的起始位置。
//
//uint8 get_start_point(uint8 start_row)：     定义了一个函数，用于搜寻车道的起始点。
//
