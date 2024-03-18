#include <stdio.h>
#include <stdlib.h>

/*双向循环链表实现*/

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define Equal(x, y) Equal_Compare(x, y)

u8 Equal_Compare(u8 x, u8 y)
{
	if (x == y)
	{
		return (u8)1;
	}
	else
	{
		return (u8)0;
	}
}

typedef struct Node
{
	u8 num;
	struct Node *next;
	struct Node *pre;
} Link;

void Swap(u8 *a, u8 *b)
{
	u8 temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

// 时间复杂度	O(N^2)
Link *BubbleSort(Link *p_head, u8 n) // n --NumOfLink
{
	u8 end = 0;
	u8 i = 0;
	Link *p_move = p_head;
	Link *cur = p_head;
	Link *pTemp = p_head;

	for (end = n; end > 0; --end)
	{
		u8 exchange = 0;

		p_move = p_head;

		for (i = 1; i < end; ++i)
		{
			if (p_move->next != p_head) // 循环节点的结束标志
			{
				cur = p_move->next; // 第1个节点
				pTemp = cur->next;	// 第2个节点

				p_move = cur;
			}
			// Rank in ascending order
			if ((cur->num) > (pTemp->num))
			{
				Swap(&(cur->num), &(pTemp->num));
				exchange = 1;
			}
		}
		if (exchange == 0)
			break;
	}

	return p_head;
}

/**********************************************************************************
 * @fun: Get count of Link
 *
 ********************************************************************************/
u8 GetCountOfLink(Link *p_head)
{
	u8 count = 0;
	Link *p_move = p_head->next;
	while (p_move != p_head)
	{
		count++;
		p_move = p_move->next;
	}

	return count;
}

/**********************************************************************************
 * @fun: Insert node 链表数据升序排列
 *
 ********************************************************************************/
Link *Sort_Link_Ascend(Link *p_head)
{
	u8 NumOfLink = 0;
	NumOfLink = GetCountOfLink(p_head);
	p_head = BubbleSort(p_head, NumOfLink);

	return p_head;
}

/**********************************************************************************
 * Create Linked Creat_HeadNode
 * @func: Init_Link()
 ********************************************************************************/
Link *Init_Link(u8 arr[], u8 NumOfLink)
{
	Link *p_head = (Link *)malloc(sizeof(Link));
	u8 i = 0;
	Link *p_Temp = p_head;

	/**
	 * 记录一个有意思的问题：数组作为函数参数传递后用sizeof(arr) 出现问题？
	 * 经过本实验验证得知，sizeof(arr)为8，原本arr长度是6，为何变成了8？
	 * 主要是因为数组作为函数参数传递时，被强行转为了 int *arr, 是int类型指针，
	 * 本机是64位系统，所以arr长度为8，解决这个问题也很简单，顺便把长度值传过来
	 */
	for (i = 0; i < NumOfLink; i++)
	{
		Link *NewNode = (Link *)malloc(sizeof(Link));
		NewNode->num = arr[i];

		NewNode->pre = p_Temp;
		p_Temp->next = NewNode; // 新旧节点相对移动

		NewNode->next = p_head;
		p_head->pre = NewNode; // 头新节点绝对连接

		p_Temp = NewNode; // 为了下一次新旧移动,等同于不停在链表尾部插入数据
	}

	return p_head;
}

/**********************************************************************************
 * @fun: Insert node 插入数据
 * 在升序的链表中插入数据
 ********************************************************************************/
Link *Insert_Link(Link *p_head, u8 num)
{
	Link *p_Temp = p_head;
	Link *NewNode = (Link *)malloc(sizeof(Link));
	NewNode->num = num;
	NewNode->pre = NULL;
	NewNode->next = NULL;

	/**
	 * 如果链表的初始数据是空的话
	 * 新节点就是最新的初始数据
	 **/
	if (p_Temp->next == p_head)
	{
		p_head->next = NewNode;
		NewNode->pre = p_head;

		NewNode->next = p_head;
		p_head->pre = NewNode;
	}

	/**
	 * 链表头部插入数据
	 * 当数据插入链表的位置是头部
	 * 如果数据是无序排列，非升非降，那么其实插入尾部更好，因为最后数据
	 * 有序排列后，自然会移动到想要的位置
	 *
	 * */

	/**
	 * --链表中部插入数据--
	 * 当数据插入链表的位置既不是头部也不是尾部，而是两者之间时
	 * 如果数据是无序排列，非升非降，那么其实插入尾部更好，因为最后数据
	 * 有序排列后，自然会移动到想要的位置
	 */

	/**
	 * --链表尾部插入数据--
	 * 按照双向循环链表结构图
	 * p_head->pre 不为空的话，那么它指向的是尾节点
	 * */
	if (p_head->pre != p_head)
	{
		p_Temp = p_Temp->pre; // 提取尾节点

		p_Temp->next = NewNode;
		NewNode->pre = p_Temp; // 尾节点与新节点相连

		NewNode->next = p_head;
		p_head->pre = NewNode; // 头新节点绝对连接
	}

	/*最后对链表数据进行升序排列*/
	p_head = Sort_Link_Ascend(p_head);

	return p_head;
}

/**********************************************************************************
 * @fun: delete node
 *
 ********************************************************************************/
Link *Delete_Link(Link *p_head, u8 num)
{
	Link *p_temp = p_head;
	Link *p_del = p_head;
	Link *p_rear = p_head;
	/**
	 * 删除的节点位于头部
	 */
	if (Equal(p_del->next->num, num))
	{
		p_del = p_del->next;  // 第一个节点
		p_temp = p_del->next; // 第二个节点

		p_temp->pre = p_head;
		p_head->next = p_temp;

		free(p_del);
	}

	/**
	 * 删除的节点位于尾部
	 */
	else if (Equal(p_del->pre->num, num))
	{
		p_del = p_del->pre;
		p_temp = p_del->pre; // 尾节点的前一个节点

		p_temp->next = p_head;
		p_head->pre = p_temp;

		free(p_del);
	}
	/**
	 * 删除的节点位于中部
	 */
	else
	{
		while ((p_del->num != num) && (p_del->next != p_head))
		{
			p_temp = p_del;
			p_del = p_del->next;
		}

		if (p_del->next == p_head)
		{
			printf("--------ERROR:删除的节点数据%d不在链表中------!\n", num);
		}
		else
		{
			p_rear = p_del->next;
			p_temp->next = p_rear;
			p_rear->pre = p_temp;

			free(p_del);
		}
		
	}

	return p_head;
}

/**********************************************************************************
 * Print node
 *
 ********************************************************************************/
void Print_Data(Link *p_head)
{ // 遍历的同时计算节点数
	int count = 0;
	Link *p_move = p_head->next;
	while (p_move != p_head)
	{
		count++;
		printf("节点%d数据: %d\n", count, p_move->num);
		p_move = p_move->next;
	}
}

int main()
{
	Link *head = NULL;
	u8 arr[] = {13, 2, 6, 5, 4, 9};
	u8 insert_data = 0;
	u8 delete_data = 0;

	printf("----链表初始数据\n");
	head = Init_Link(arr, sizeof(arr));
	Print_Data(head);

	printf("----输入你想要插入的数据: ");
	scanf("%d", &insert_data);
	head = Insert_Link(head, insert_data);
	Print_Data(head);

	printf("----输入你想要删除的数据: ");
	scanf("%d", &delete_data);
	head = Delete_Link(head, delete_data);
	Print_Data(head);
	return 0;
}
