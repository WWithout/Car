/*
�������ƣ�void image_process(void)
����˵�������մ�����
����˵������
�������أ���
�޸�ʱ�䣺2022��9��8��
��    ע��
example�� image_process();
 */
void image_process(void)
{
	uint16 i;
	uint8 hightest = 0;
	/*�������ߵ����õ�*/
	Get_image(mt9v03x_image);
	turn_to_bin();
	/*��ȡ�����߽�*/
	image_draw_rectan(bin_image);
	//����
	data_stastics_l = 0;
	data_stastics_r = 0;
	if (get_start_point(image_h - 2))
	{

		search_l_r((uint16)USE_num, bin_image, &data_stastics_l, &data_stastics_r, start_point_l[0], start_point_l[1], start_point_r[0], start_point_r[1], &hightest);

	}

	for (i = 0; i < data_stastics_l; i++)
	{
		ips154_drawpoint(points_l[i][0] + 2, points_l[i][1], uesr_BLUE);//��ʾ���
	}
	for (i = 0; i < data_stastics_r; i++)
	{
		ips154_drawpoint(points_r[i][0] - 2, points_r[i][1], uesr_RED);//��ʾ���
	}

}


//��δ�����һ��ͼ����ĺ�������Ҫʵ��������ͷ�ɼ�ͼ��ͼ���ֵ������Ѱ������ʼ�㡢Ѱ�������߽硢����ͼ��ȹ��ܡ������ǶԴ�������з������ͣ�
//
//void image_process(void)��   ������ͼ��������
//
//uint16 i; ��   ����һ�� uint16 ���͵ı��� i��
//
//uint8 hightest = 0; ��   ����һ�� uint8 ���͵ı��� hightest�����ڴ洢������ߵ������ֵ��
//
//Get_image(mt9v03x_image); ��   ���ú��� Get_image(mt9v03x_image)�����ڻ�ȡ����ͷ�ɼ���ͼ��
//
//turn_to_bin(); ��    ���ú��� turn_to_bin()�����ڽ�ԭʼͼ����ж�ֵ������
//
//image_draw_rectan(bin_image); ��    ���ú��� image_draw_rectan(bin_image)������Ѱ�������߽硣
//
//data_stastics_l = 0; ��   ������ data_stastics_l ����Ϊ0��
//
//data_stastics_r = 0; ��   ������ data_stastics_r ����Ϊ0��
//
//if (get_start_point(image_h - 2))��   ���ú��� get_start_point()��������Ѱ���������ұ߽����ʼ�㣬����Ϊ image_h - 2��
//
//search_l_r((uint16)USE_num, bin_image, &data_stastics_l, &data_stastics_r, start_point_l[0], start_point_l[1], start_point_r[0], start_point_r[1], &hightest); ��   ���ú��� search_l_r()������Ѱ�����������ұ߽硣
//
//for (i = 0; i < data_stastics_l; i++)��   ѭ��������������ĵ㣬����ÿ���㡣
//
//	ips154_drawpoint(points_l[i][0] + 2, points_l[i][1], uesr_BLUE); ��   ��ͼ���ϻ�����೵���ĵ㣬��ɫΪ��ɫ��
//
//	for (i = 0; i < data_stastics_r; i++)��   ѭ�������Ҳ������ĵ㣬����ÿ���㡣
//
//		ips154_drawpoint(points_r[i][0] - 2, points_r[i][1], uesr_RED); ��   ��ͼ���ϻ����Ҳ೵���ĵ㣬��ɫΪ��ɫ��