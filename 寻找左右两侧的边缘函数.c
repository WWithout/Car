/*
函数名称：void search_l_r(uint16 break_flag, uint8(*image)[image_w],uint16 *l_stastic, uint16 *r_stastic,
							uint8 l_start_x, uint8 l_start_y, uint8 r_start_x, uint8 r_start_y,uint8*hightest)

功能说明：八邻域正式开始找右边点的函数，输入参数有点多，调用的时候不要漏了，这个是左右线一次性找完。
参数说明：
break_flag_r			：最多需要循环的次数
(*image)[image_w]		：需要进行找点的图像数组，必须是二值图,填入数组名称即可
					   特别注意，不要拿宏定义名字作为输入参数，否则数据可能无法传递过来
*l_stastic				：统计左边数据，用来输入初始数组成员的序号和取出循环次数
*r_stastic				：统计右边数据，用来输入初始数组成员的序号和取出循环次数
l_start_x				：左边起点横坐标
l_start_y				：左边起点纵坐标
r_start_x				：右边起点横坐标
r_start_y				：右边起点纵坐标
hightest				：循环结束所得到的最高高度
函数返回：无
修改时间：2022年9月25日
备    注：
example：
 */
#define USE_num	300	//定义找点的数组成员个数按理说300个点能放下，但是有些特殊情况确实难顶，多定义了一点

 //存放点的x，y坐标
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


/*这段代码是嵌入式C语言代码，主要实现的是一个寻找左右两侧的边缘的函数。下面是详细的代码解释：

第一行是定义一个宏，表示要寻找的点的个数为300个。
接下来的几行定义了需要存放点的x，y坐标的数组，以及相关的一些计数器和中间变量。
函数search_l_r是一个带有八个参数的函数，其中第一个参数是一个计数器，表示这个函数需要执行多少次；第二个参数是一个指向二维数组类型的指针，表示对哪个图像进行处理；第三、四个参数是指向计数器的指针，表示函数处理过程中找到的边缘点的个数；第五、六个参数是表示左侧起始点横纵坐标；第七、八个参数是表示右侧起始点横纵坐标；最后一个参数是表示最高点的指针。
函数中的变量i和j分别是用来循环计数的变量。
search_filds_l和search_filds_r是两个用来存储搜索8个方向的点的数组。
points_l和points_r分别存储左右两侧的边缘点的坐标。
dir_l和dir_r分别表示左右两边的方向。
hightest表示最高点。
代码中用了搜索算法，将算法细节和注释，我们可以对其进行总结：

在函数内部，将中心点设置为传入的起始点坐标，然后循环执行四个步骤：

首先在中心点的八个方向上搜索边缘点（即黑色点中的白色点），找到一个边缘点就将其存储在points_l或者points_r中。

在存储当前点的过程中，同时检查当前点是否符合终止条件，如果符合则退出循环。

接着从存储的边缘点中选择一个最靠上的点做为下一个中心，用于下一轮的搜索。

当左侧和右侧的最靠上的点距离在一定范围之内时，将两侧点中的一半作为最高点。

整个函数实现的过程比较复杂，需要将代码分块理解，分析每个变量和数组的作用。对于代码存在的问题和细节，需要具体问题具体分析。
*/