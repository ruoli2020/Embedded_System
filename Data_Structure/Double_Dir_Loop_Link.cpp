#include <stdio.h>
#include <stdlib.h>

/*˫��ѭ������ʵ��*/

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

// ʱ�临�Ӷ�	O(N^2)
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
			if (p_move->next != p_head) // ѭ���ڵ�Ľ�����־
			{
				cur = p_move->next; // ��1���ڵ�
				pTemp = cur->next;	// ��2���ڵ�

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
 * @fun: Insert node ����������������
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
	 * ��¼һ������˼�����⣺������Ϊ�����������ݺ���sizeof(arr) �������⣿
	 * ������ʵ����֤��֪��sizeof(arr)Ϊ8��ԭ��arr������6��Ϊ�α����8��
	 * ��Ҫ����Ϊ������Ϊ������������ʱ����ǿ��תΪ�� int *arr, ��int����ָ�룬
	 * ������64λϵͳ������arr����Ϊ8������������Ҳ�ܼ򵥣�˳��ѳ���ֵ������
	 */
	for (i = 0; i < NumOfLink; i++)
	{
		Link *NewNode = (Link *)malloc(sizeof(Link));
		NewNode->num = arr[i];

		NewNode->pre = p_Temp;
		p_Temp->next = NewNode; // �¾ɽڵ�����ƶ�

		NewNode->next = p_head;
		p_head->pre = NewNode; // ͷ�½ڵ��������

		p_Temp = NewNode; // Ϊ����һ���¾��ƶ�,��ͬ�ڲ�ͣ������β����������
	}

	return p_head;
}

/**********************************************************************************
 * @fun: Insert node ��������
 * ������������в�������
 ********************************************************************************/
Link *Insert_Link(Link *p_head, u8 num)
{
	Link *p_Temp = p_head;
	Link *NewNode = (Link *)malloc(sizeof(Link));
	NewNode->num = num;
	NewNode->pre = NULL;
	NewNode->next = NULL;

	/**
	 * �������ĳ�ʼ�����ǿյĻ�
	 * �½ڵ�������µĳ�ʼ����
	 **/
	if (p_Temp->next == p_head)
	{
		p_head->next = NewNode;
		NewNode->pre = p_head;

		NewNode->next = p_head;
		p_head->pre = NewNode;
	}

	/**
	 * ����ͷ����������
	 * �����ݲ��������λ����ͷ��
	 * ����������������У������ǽ�����ô��ʵ����β�����ã���Ϊ�������
	 * �������к���Ȼ���ƶ�����Ҫ��λ��
	 *
	 * */

	/**
	 * --�����в���������--
	 * �����ݲ��������λ�üȲ���ͷ��Ҳ����β������������֮��ʱ
	 * ����������������У������ǽ�����ô��ʵ����β�����ã���Ϊ�������
	 * �������к���Ȼ���ƶ�����Ҫ��λ��
	 */

	/**
	 * --����β����������--
	 * ����˫��ѭ������ṹͼ
	 * p_head->pre ��Ϊ�յĻ�����ô��ָ�����β�ڵ�
	 * */
	if (p_head->pre != p_head)
	{
		p_Temp = p_Temp->pre; // ��ȡβ�ڵ�

		p_Temp->next = NewNode;
		NewNode->pre = p_Temp; // β�ڵ����½ڵ�����

		NewNode->next = p_head;
		p_head->pre = NewNode; // ͷ�½ڵ��������
	}

	/*�����������ݽ�����������*/
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
	 * ɾ���Ľڵ�λ��ͷ��
	 */
	if (Equal(p_del->next->num, num))
	{
		p_del = p_del->next;  // ��һ���ڵ�
		p_temp = p_del->next; // �ڶ����ڵ�

		p_temp->pre = p_head;
		p_head->next = p_temp;

		free(p_del);
	}

	/**
	 * ɾ���Ľڵ�λ��β��
	 */
	else if (Equal(p_del->pre->num, num))
	{
		p_del = p_del->pre;
		p_temp = p_del->pre; // β�ڵ��ǰһ���ڵ�

		p_temp->next = p_head;
		p_head->pre = p_temp;

		free(p_del);
	}
	/**
	 * ɾ���Ľڵ�λ���в�
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
			printf("--------ERROR:ɾ���Ľڵ�����%d����������------!\n", num);
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
{ // ������ͬʱ����ڵ���
	int count = 0;
	Link *p_move = p_head->next;
	while (p_move != p_head)
	{
		count++;
		printf("�ڵ�%d����: %d\n", count, p_move->num);
		p_move = p_move->next;
	}
}

int main()
{
	Link *head = NULL;
	u8 arr[] = {13, 2, 6, 5, 4, 9};
	u8 insert_data = 0;
	u8 delete_data = 0;

	printf("----�����ʼ����\n");
	head = Init_Link(arr, sizeof(arr));
	Print_Data(head);

	printf("----��������Ҫ���������: ");
	scanf("%d", &insert_data);
	head = Insert_Link(head, insert_data);
	Print_Data(head);

	printf("----��������Ҫɾ��������: ");
	scanf("%d", &delete_data);
	head = Delete_Link(head, delete_data);
	Print_Data(head);
	return 0;
}
