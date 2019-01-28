
/***************************************************************************************
通用状态图搜索算法(Versatile State-Graph Search Algorithm):
1.生成一个仅包含开始节点n0的搜索树Tr。把n0放在OPEN有序列表中。
2.生成空CLOSED列表。
3.如果OPEN为空，则失败退出。
4.选出OPEN中的第一个节点并将其移出，放入CLOSED中，称该节点为n。
5.如果n为目标节点，顺着Tr中的弧从n回溯到n0找到一条路径，获得解决方案。
6.扩展节点n，生成n的后继节点集M。通过在Tr中建立从n到M中每个成员的弧生成n的后继。
7.按照任意模式或启发式方式对OPEN重新排序。
8.返回步骤3。
***************************************************************************************/

#define CAN_STEP 0   //可以步进
#define NOT_STEP 1   //不可步进
#define HAS_STEP 2   //已经步进
#define SET_MARK 3   //已经探测

#define MAP_X 16     //地图的长
#define MAP_Y 16     //地图的宽

//坐标结构
struct Pos
{
	int x;
	int y;
};

//节点结构
struct Node
{
	Pos pare;   //父节点坐标
	Pos self;   //子节点坐标
	int cost;   //代价值
};

//节点链表结构
struct Judge
{
	Node node;
	Judge* next;
};

//方向向量结构
struct Vect
{
	int dx;
	int dy;
};

int map[MAP_X][MAP_Y];   //地图矩阵信息