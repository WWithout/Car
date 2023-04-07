/*
函数名称：void image_process(void)
功能说明：最终处理函数
参数说明：无
函数返回：无
修改时间：2022年9月8日
备    注：
example： image_process();
 */
void image_process(void)
{
	uint16 i;
	uint8 hightest = 0;
	/*这是离线调试用的*/
	Get_image(mt9v03x_image);
	turn_to_bin();
	/*提取赛道边界*/
	image_draw_rectan(bin_image);
	//清零
	data_stastics_l = 0;
	data_stastics_r = 0;
	if (get_start_point(image_h - 2))
	{

		search_l_r((uint16)USE_num, bin_image, &data_stastics_l, &data_stastics_r, start_point_l[0], start_point_l[1], start_point_r[0], start_point_r[1], &hightest);

	}

	for (i = 0; i < data_stastics_l; i++)
	{
		ips154_drawpoint(points_l[i][0] + 2, points_l[i][1], uesr_BLUE);//显示起点
	}
	for (i = 0; i < data_stastics_r; i++)
	{
		ips154_drawpoint(points_r[i][0] - 2, points_r[i][1], uesr_RED);//显示起点
	}

}


//这段代码是一个图像处理的函数，主要实现了摄像头采集图像、图像二值化、搜寻车道起始点、寻找赛道边界、绘制图像等功能。下面是对代码的逐行分析解释：
//
//void image_process(void)：   定义了图像处理函数。
//
//uint16 i; ：   定义一个 uint16 类型的变量 i。
//
//uint8 hightest = 0; ：   定义一个 uint8 类型的变量 hightest，用于存储赛道最高点的像素值。
//
//Get_image(mt9v03x_image); ：   调用函数 Get_image(mt9v03x_image)，用于获取摄像头采集的图像。
//
//turn_to_bin(); ：    调用函数 turn_to_bin()，用于将原始图像进行二值化处理。
//
//image_draw_rectan(bin_image); ：    调用函数 image_draw_rectan(bin_image)，用于寻找赛道边界。
//
//data_stastics_l = 0; ：   将变量 data_stastics_l 设置为0。
//
//data_stastics_r = 0; ：   将变量 data_stastics_r 设置为0。
//
//if (get_start_point(image_h - 2))：   调用函数 get_start_point()，用于搜寻赛道的左右边界的起始点，参数为 image_h - 2。
//
//search_l_r((uint16)USE_num, bin_image, &data_stastics_l, &data_stastics_r, start_point_l[0], start_point_l[1], start_point_r[0], start_point_r[1], &hightest); ：   调用函数 search_l_r()，用于寻找赛道的左右边界。
//
//for (i = 0; i < data_stastics_l; i++)：   循环遍历左侧赛道的点，画出每个点。
//
//	ips154_drawpoint(points_l[i][0] + 2, points_l[i][1], uesr_BLUE); ：   在图像上画出左侧车道的点，颜色为蓝色。
//
//	for (i = 0; i < data_stastics_r; i++)：   循环遍历右侧赛道的点，画出每个点。
//
//		ips154_drawpoint(points_r[i][0] - 2, points_r[i][1], uesr_RED); ：   在图像上画出右侧车道的点，颜色为红色。