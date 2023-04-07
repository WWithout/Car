//-------------------------------------------------------------------------------------------------------------------
//  ���:������ͼ����
//  �������ͣ�Ƕ��ʽϵͳ��ͼ������롣
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
uint8 image_thereshold;//ͼ��ָ���ֵ

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
	double OmegaBack = 0, OmegaFore = 0, MicroBack = 0, MicroFore = 0, SigmaB = 0, Sigma = 0; // ��䷽��;
	uint8 MinValue = 0, MaxValue = 0;
	uint8 Threshold = 0;


	for (Y = 0; Y < Image_Height; Y++) //Y<Image_Height��ΪY =Image_Height���Ա���� �ж�ֵ��
	{
		//Y=Image_Height;
		for (X = 0; X < Image_Width; X++)
		{
			HistGram[(int)data[Y * Image_Width + X]]++; //ͳ��ÿ���Ҷ�ֵ�ĸ�����Ϣ
		}
	}
	for (MinValue = 0; MinValue < 256 && HistGram[MinValue] == 0; MinValue++);        //��ȡ��С�Ҷȵ�ֵ
	for (MaxValue = 255; MaxValue > MinValue && HistGram[MinValue] == 0; MaxValue--); //��ȡ���Ҷȵ�ֵ

	if (MaxValue == MinValue)
	{
		return MaxValue;          // ͼ����ֻ��һ����ɫ
	}
	if (MinValue + 1 == MaxValue)
	{
		return MinValue;      // ͼ����ֻ�ж�����ɫ
	}

	for (Y = MinValue; Y <= MaxValue; Y++)
	{
		Amount += HistGram[Y];        //  ��������
	}

	PixelIntegral = 0;
	for (Y = MinValue; Y <= MaxValue; Y++)
	{
		PixelIntegral += HistGram[Y] * Y;//�Ҷ�ֵ����
	}
	SigmaB = -1;
	for (Y = MinValue; Y < MaxValue; Y++)
	{
		PixelBack = PixelBack + HistGram[Y];    //ǰ�����ص���
		PixelFore = Amount - PixelBack;         //�������ص���
		OmegaBack = (double)PixelBack / Amount;//ǰ�����ذٷֱ�
		OmegaFore = (double)PixelFore / Amount;//�������ذٷֱ�
		PixelIntegralBack += HistGram[Y] * Y;  //ǰ���Ҷ�ֵ
		PixelIntegralFore = PixelIntegral - PixelIntegralBack;//�����Ҷ�ֵ
		MicroBack = (double)PixelIntegralBack / PixelBack;//ǰ���ҶȰٷֱ�
		MicroFore = (double)PixelIntegralFore / PixelFore;//�����ҶȰٷֱ�
		Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);//g
		if (Sigma > SigmaB)//����������䷽��g
		{
			SigmaB = Sigma;
			Threshold = (uint8)Y;
		}
	}
	return Threshold;
}

uint8 bin_image[image_h][image_w];//ͼ������
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



uint8 start_point_l[2] = { 0 };//�������x��yֵ
uint8 start_point_r[2] = { 0 };//�ұ�����x��yֵ
uint8 get_start_point(uint8 start_row)
{
	uint8 i = 0, l_found = 0, r_found = 0;
	//����
	start_point_l[0] = 0;//x
	start_point_l[1] = 0;//y

	start_point_r[0] = 0;//x
	start_point_r[1] = 0;//y

	//���м�����ߣ��������
	for (i = image_w / 2; i > border_min; i--)
	{
		start_point_l[0] = i;//x
		start_point_l[1] = start_row;//y
		if (bin_image[start_row][i] == 255 && bin_image[start_row][i - 1] == 0)
		{
			//printf("�ҵ�������image[%d][%d]\n", start_row,i);
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
			//printf("�ҵ��ұ����image[%d][%d]\n",start_row, i);
			r_found = 1;
			break;
		}
	}

	if (l_found && r_found)return 1;
	else {
		//printf("δ�ҵ����\n");
		return 0;
	}
}

//
//��δ�����һ��ͼ����ĳ�����Ҫʵ����ͼ���ֵ������Ѱ������ʼ��Ĺ��ܡ������ǶԴ�������з������ͣ�
//
//#include "image.h"��  �����ⲿ��ͷ�ļ� image.h��
//
//int my_abs(int value)��   �Լ������һ������������ֵ�ĺ�����
//
//int16 limit_a_b(int16 x, int a, int b)��   �Լ������һ�����������ڽ�һ������������һ����Χ�ڣ�������ֵС�� a ʱ������Ϊ a��������ֵ���� b ʱ������Ϊ b�����������ƺ��ֵ��
//
//int16 limit1(int16 x, int16 y)��   �Լ������һ�����������ڽ�һ������������һ����Χ�ڣ�������ֵС�� - y ʱ������Ϊ - y��������ֵ���� y ʱ������Ϊ y�����������ƺ��ֵ��
//
//uint8 original_image[image_h][image_w]; ��   ������һ����ά�������ڴ���ԭʼͼ�������ֵ��
//
//uint8 image_thereshold; ��   ������һ�� uint8 ���͵ı��������ڴ洢ͼ���ֵ������ֵ��
//
//void Get_image(uint8(*mt9v03x_image)[image_w])��   ������һ�����������ڽ�����ͷ�ɼ���ͼ���벢����Ԥ����
//
//uint8 otsuThreshold(uint8* image, uint16 col, uint16 row)��   ������һ�����������ڶ�ͼ����ж�ֵ���������ض�ֵ������ֵ��
//
//uint8 bin_image[image_h][image_w]; ��   ������һ����ά���飬���ڴ����ֵ���������ֵ��
//
//void turn_to_bin(void)��   ������һ�����������ڽ�ԭʼͼ����ж�ֵ������������洢�� bin_image �����С�
//
//uint8 start_point_l[2] = { 0 };//�������x��yֵ��   ������һ���������ڴ洢��೵������ʼλ�á�
//
//uint8 start_point_r[2] = { 0 };//�ұ�����x��yֵ��    ������һ���������ڴ洢�Ҳ೵������ʼλ�á�
//
//uint8 get_start_point(uint8 start_row)��     ������һ��������������Ѱ��������ʼ�㡣
//
