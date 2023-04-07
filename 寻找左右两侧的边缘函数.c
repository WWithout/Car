/*
�������ƣ�void search_l_r(uint16 break_flag, uint8(*image)[image_w],uint16 *l_stastic, uint16 *r_stastic,
							uint8 l_start_x, uint8 l_start_y, uint8 r_start_x, uint8 r_start_y,uint8*hightest)

����˵������������ʽ��ʼ���ұߵ�ĺ�������������е�࣬���õ�ʱ��Ҫ©�ˣ������������һ�������ꡣ
����˵����
break_flag_r			�������Ҫѭ���Ĵ���
(*image)[image_w]		����Ҫ�����ҵ��ͼ�����飬�����Ƕ�ֵͼ,�����������Ƽ���
					   �ر�ע�⣬��Ҫ�ú궨��������Ϊ����������������ݿ����޷����ݹ���
*l_stastic				��ͳ��������ݣ����������ʼ�����Ա����ź�ȡ��ѭ������
*r_stastic				��ͳ���ұ����ݣ����������ʼ�����Ա����ź�ȡ��ѭ������
l_start_x				�������������
l_start_y				��������������
r_start_x				���ұ���������
r_start_y				���ұ����������
hightest				��ѭ���������õ�����߸߶�
�������أ���
�޸�ʱ�䣺2022��9��25��
��    ע��
example��
 */
#define USE_num	300	//�����ҵ�������Ա��������˵300�����ܷ��£�������Щ�������ȷʵ�Ѷ����ඨ����һ��

 //��ŵ��x��y����
uint16 points_l[(uint16)USE_num][2] = { {  0 } };
uint16 points_r[(uint16)USE_num][2] = { {  0 } };
uint16 dir_r[(uint16)USE_num] = { 0 }; /
uint16 dir_l[(uint16)USE_num] = { 0 };
uint16 data_stastics_l = 0;
uint16 data_stastics_r = 0
uint8 hightest = 0;
void search_l_r(uint16 break_flag, uint8(*image)[image_w], uint16* l_stastic, uint16* r_stastic, uint8 l_start_x, uint8 l_start_y, uint8 r_start_x, uint8 r_start_y, uint8* hightest)
{

	uint8 i = 0, j = 0;

	uint8 search_filds_l[8][2] = { {  0 } };
	uint8 index_l = 0;
	uint8 temp_l[8][2] = { {  0 } };
	uint8 center_point_l[2] = { 0 };
	uint16 l_data_statics;
	static int8 seeds_l[8][2] = { {0,  1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1},{1,  0},{1, 1}, };
	uint8 search_filds_r[8][2] = { {  0 } };
	uint8 center_point_r[2] = { 0 };
	uint8 index_r = 0;
	uint8 temp_r[8][2] = { {  0 } };
	uint16 r_data_statics;
	static int8 seeds_r[8][2] = { {0,  1},{1,1},{1,0}, {1,-1},{0,-1},{-1,-1}, {-1,  0},{-1, 1}, };
	l_data_statics = *l_stastic;
	r_data_statics = *r_stastic;
	center_point_l[0] = l_start_x;//x
	center_point_l[1] = l_start_y;//y
	center_point_r[0] = r_start_x;//x
	center_point_r[1] = r_start_y;//y
	while (break_flag--)
	{
		for (i = 0; i < 8; i++)
		{
			search_filds_l[i][0] = center_point_l[0] + seeds_l[i][0];//x
			search_filds_l[i][1] = center_point_l[1] + seeds_l[i][1];//y
		}
		points_l[l_data_statics][0] = center_point_l[0];//x
		points_l[l_data_statics][1] = center_point_l[1];//y
		l_data_statics++;//
		for (i = 0; i < 8; i++)
		{
			search_filds_r[i][0] = center_point_r[0] + seeds_r[i][0];//x
			search_filds_r[i][1] = center_point_r[1] + seeds_r[i][1];//y
		}
		points_r[r_data_statics][0] = center_point_r[0];//x
		points_r[r_data_statics][1] = center_point_r[1];//y

		index_l = 0;
		for (i = 0; i < 8; i++)
		{
			temp_l[i][0] = 0;
			temp_l[i][1] = 0;
		}

		for (i = 0; i < 8; i++)
		{
			if (image[search_filds_l[i][1]][search_filds_l[i][0]] == 0
				&& image[search_filds_l[(i + 1) & 7][1]][search_filds_l[(i + 1) & 7][0]] == 255)
			{
				temp_l[index_l][0] = search_filds_l[(i)][0];
				temp_l[index_l][1] = search_filds_l[(i)][1];
				index_l++;
				dir_l[l_data_statics - 1] = (i);
			}

			if (index_l)
			{

				center_point_l[0] = temp_l[0][0];//x
				center_point_l[1] = temp_l[0][1];//y
				for (j = 0; j < index_l; j++)
				{
					if (center_point_l[1] > temp_l[j][1])
					{
						center_point_l[0] = temp_l[j][0];//x
						center_point_l[1] = temp_l[j][1];//y
					}
				}
			}

		}
		if ((points_r[r_data_statics][0] == points_r[r_data_statics - 1][0] && points_r[r_data_statics][0] == points_r[r_data_statics - 2][0]
			&& points_r[r_data_statics][1] == points_r[r_data_statics - 1][1] && points_r[r_data_statics][1] == points_r[r_data_statics - 2][1])
			|| (points_l[l_data_statics - 1][0] == points_l[l_data_statics - 2][0] && points_l[l_data_statics - 1][0] == points_l[l_data_statics - 3][0]
				&& points_l[l_data_statics - 1][1] == points_l[l_data_statics - 2][1] && points_l[l_data_statics - 1][1] == points_l[l_data_statics - 3][1]))
		{
			break;
		}
		if (my_abs(points_r[r_data_statics][0] - points_l[l_data_statics - 1][0]) < 2
			&& my_abs(points_r[r_data_statics][1] - points_l[l_data_statics - 1][1] < 2)
			)
		{

			*hightest = (points_r[r_data_statics][1] + points_l[l_data_statics - 1][1]) >> 1;

			break;
		}
		if ((points_r[r_data_statics][1] < points_l[l_data_statics - 1][1]))
		{
			continue;
		}
		if (dir_l[l_data_statics - 1] == 7
			&& (points_r[r_data_statics][1] > points_l[l_data_statics - 1][1]))
		{
			center_point_l[0] = points_l[l_data_statics - 1][0];//x
			center_point_l[1] = points_l[l_data_statics - 1][1];//y
			l_data_statics--;
		}
		r_data_statics++;

		index_r = 0;
		for (i = 0; i < 8; i++)
		{
			temp_r[i][0] = 0;
			temp_r[i][1] = 0;
		}
		for (i = 0; i < 8; i++)
		{
			if (image[search_filds_r[i][1]][search_filds_r[i][0]] == 0
				&& image[search_filds_r[(i + 1) & 7][1]][search_filds_r[(i + 1) & 7][0]] == 255)
			{
				temp_r[index_r][0] = search_filds_r[(i)][0];
				temp_r[index_r][1] = search_filds_r[(i)][1];
				index_r++;
				dir_r[r_data_statics - 1] = (i);
				//printf("dir[%d]:%d\n", r_data_statics - 1, dir_r[r_data_statics - 1]);
			}
			if (index_r)
			{
				center_point_r[0] = temp_r[0][0];//x
				center_point_r[1] = temp_r[0][1];//y
				for (j = 0; j < index_r; j++)
				{
					if (center_point_r[1] > temp_r[j][1])
					{
						center_point_r[0] = temp_r[j][0];//x
						center_point_r[1] = temp_r[j][1];//y
					}
				}

			}
		}


	}
	*l_stastic = l_data_statics;
	*r_stastic = r_data_statics;

}


/*��δ�����Ƕ��ʽC���Դ��룬��Ҫʵ�ֵ���һ��Ѱ����������ı�Ե�ĺ�������������ϸ�Ĵ�����ͣ�

��һ���Ƕ���һ���꣬��ʾҪѰ�ҵĵ�ĸ���Ϊ300����
�������ļ��ж�������Ҫ��ŵ��x��y��������飬�Լ���ص�һЩ���������м������
����search_l_r��һ�����а˸������ĺ��������е�һ��������һ������������ʾ���������Ҫִ�ж��ٴΣ��ڶ���������һ��ָ���ά�������͵�ָ�룬��ʾ���ĸ�ͼ����д����������ĸ�������ָ���������ָ�룬��ʾ��������������ҵ��ı�Ե��ĸ��������塢���������Ǳ�ʾ�����ʼ��������ꣻ���ߡ��˸������Ǳ�ʾ�Ҳ���ʼ��������ꣻ���һ�������Ǳ�ʾ��ߵ��ָ�롣
�����еı���i��j�ֱ�������ѭ�������ı�����
search_filds_l��search_filds_r�����������洢����8������ĵ�����顣
points_l��points_r�ֱ�洢��������ı�Ե������ꡣ
dir_l��dir_r�ֱ��ʾ�������ߵķ���
hightest��ʾ��ߵ㡣
���������������㷨�����㷨ϸ�ں�ע�ͣ����ǿ��Զ�������ܽ᣺

�ں����ڲ��������ĵ�����Ϊ�������ʼ�����꣬Ȼ��ѭ��ִ���ĸ����裺

���������ĵ�İ˸�������������Ե�㣨����ɫ���еİ�ɫ�㣩���ҵ�һ����Ե��ͽ���洢��points_l����points_r�С�

�ڴ洢��ǰ��Ĺ����У�ͬʱ��鵱ǰ���Ƿ������ֹ����������������˳�ѭ����

���ŴӴ洢�ı�Ե����ѡ��һ����ϵĵ���Ϊ��һ�����ģ�������һ�ֵ�������

�������Ҳ����ϵĵ������һ����Χ֮��ʱ����������е�һ����Ϊ��ߵ㡣

��������ʵ�ֵĹ��̱Ƚϸ��ӣ���Ҫ������ֿ���⣬����ÿ����������������á����ڴ�����ڵ������ϸ�ڣ���Ҫ����������������
*/