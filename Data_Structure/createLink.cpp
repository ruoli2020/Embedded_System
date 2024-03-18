#include <stdio.h>
#include <stdlib.h>

/*��������ʵ��*/

typedef unsigned char u8;

typedef struct Node
{
	u8 num;
	struct Node *next;
} Link;

typedef struct Binary_Search
{
	Link **p_arr;
	u8 data_location;
	u8 NumOfLink;

} Array_Binary_Search_st;

static u8 FindNum_Not_in_the_Link = 0;
/**********************************************************************************
* @fun: BubbleSort
*
********************************************************************************/
void Swap(u8 *a, u8 *b)
{
	u8 temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

// ʱ�临�Ӷ�	O(N^2)
Link *BubbleSort(Link *phead, u8 n) // n --NumOfLink
{
	u8 end = 0;
	u8 i = 0;
	Link *pre = phead;
	Link *cur = phead;
	Link *pTemp = phead;

	for (end = n; end > 0; --end)
	{
		int exchange = 0;

		pre = phead;

		for (i = 1; i < end; ++i)
		{
			if (pre->next != NULL)
			{
				cur = pre->next;   // ��1���ڵ�
				pTemp = cur->next; // ��2���ڵ�

				pre = cur;
			}

			if ((cur->num) > (pTemp->num))
			{
				Swap(&(cur->num), &(pTemp->num));
				exchange = 1;
			}
		}
		if (exchange == 0)
			break;
	}

	return phead;
}

/**********************************************************************************
* @fun: Get count of Link
*
********************************************************************************/
u8 GetCountOfLink(Link *head)
{
	u8 count = 0;
	Link *p_move = head->next;

	while (p_move != NULL)
	{
		count++;
		p_move = p_move->next;
	}

	return count;
}

u8 BinarySearch(Link *p_head, Link* p_arr[],u8 n, u8 num)
{
	u8 begin = 0;
	u8 end = n - 1;
	u8 mid;
	u8 data_location = 0;

	if (p_head != NULL)
	{
		// [begin, end]��begin��end������ұ����䣬�����=��
       if ((begin == end) && (num != p_arr[begin]->num)) //ֻ��һ�����ݵ�ʱ��
       {
           FindNum_Not_in_the_Link = 1;
       }
       else if (num == p_arr[begin]->num)
		{
			data_location = begin;
		}
		else if (num == p_arr[end]->num)
		{
			data_location = end;
		}
		else
		{
			while (begin < end)
			{
				mid = begin + ((end - begin) >> 1);

				if ((p_arr[mid]->num) < num)
				{
					begin = mid + 1;
                   if ((p_arr[begin]->num) == num)
					{
						data_location = begin;
						break;
					}
					else
					{
						FindNum_Not_in_the_Link = 1;
					}
				}
				else if ((p_arr[mid]->num) > num)
				{
                   if (mid == 0) //(��������������)����2�����ݵ�����£���һ���Ȳ��ҵ����ݻ�Ҫ���Ǿ��Ǳ�ʾû�ҵ�
                   {
                       FindNum_Not_in_the_Link = 1;
                       break;
                   }
                   else
                   {
                       end = mid - 1;
                   }

                   if ((p_arr[end]->num) == num)
					{
						data_location = end;
						break;
					}
					else
					{
						FindNum_Not_in_the_Link = 1;
					}
				}
				else
				{
					data_location = mid;
					FindNum_Not_in_the_Link = 0;
					break;
				}
			}
		}
	}

	return data_location;
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
* @fun: Create pointer arrar by link
*
********************************************************************************/
Array_Binary_Search_st Creat_Point_Array(Link *p_head,u8 data)
{
	u8 i = 0;
	u8 count = 0;
	u8 data_location = 0;
	u8 NumOfLink = 0;

	NumOfLink = GetCountOfLink(p_head);
	Link *p_move = p_head->next;
	Link *p_arr[NumOfLink] = {NULL};
	Array_Binary_Search_st Arr_Binary_Search;

	p_head = Sort_Link_Ascend(p_head);// �����Ѿ�����

	for (i = 0; i < NumOfLink; i++)
	{
		p_arr[i] = (Link *)malloc(sizeof(Link));
	}

	while (p_move != NULL)
	{
		p_arr[count] = p_move; // �������ڵ�������ַ����count��λ
		count++;
		p_move = p_move->next;
		
	}
	
	data_location = BinarySearch(p_head,p_arr,NumOfLink,data);

	Arr_Binary_Search.data_location = data_location;
	Arr_Binary_Search.p_arr = p_arr;
	Arr_Binary_Search.NumOfLink = NumOfLink;

	return Arr_Binary_Search;
}
/**********************************************************************************
* Create Linked Creat_HeadNode
* @func: Init_Link()
********************************************************************************/
Link *Init_Link(u8 arr[],u8 NumOfLink)
{
	Link *p_head = (Link *)malloc(sizeof(Link));
	Link *previous = p_head;
	u8 i = 0;
	
	/**
	 * ��¼һ������˼�����⣺������Ϊ�����������ݺ���sizeof(arr) �������⣿
	 * ������ʵ����֤��֪��sizeof(arr)Ϊ8��ԭ��arr������6��Ϊ�α����8��
	 * ��Ҫ����Ϊ������Ϊ������������ʱ����ǿ��תΪ�� int *arr, ��int����ָ�룬
	 * ������64λϵͳ������arr����Ϊ8������������Ҳ�ܼ򵥣�˳��ѳ���ֵ������
	*/
	for (i = 0; i < NumOfLink; i++)
	{
		Link *Current = (Link *)malloc(sizeof(Link));
		Current->num = arr[i];
		Current->next = NULL;

		/*Previous node must connect to Current node*/
		previous->next = Current;
		/*Then Previous node become Current node for the link grows loop*/
		previous = Current;
	}

	p_head = Sort_Link_Ascend(p_head);

	return p_head;
}

/**********************************************************************************
* @fun: delete node
*
********************************************************************************/
Link *Delete_Link(Link *p_head, u8 num)
{
	Link *p_del = p_head->next;
	Link *p_move = p_head;
	u8 flag = 0;
	Link **p_arr = NULL;
	u8 data_location = 0;
	u8 data_location_Pre = 0;
	u8 NumOfLink = 0;
	Array_Binary_Search_st Arr_Binary_Search_Result;
	
	/*���ö��ֲ��ҷ�����*/

	Arr_Binary_Search_Result = Creat_Point_Array(p_head,num);
	p_arr = Arr_Binary_Search_Result.p_arr;
	data_location = Arr_Binary_Search_Result.data_location;
	NumOfLink = Arr_Binary_Search_Result.NumOfLink;

	/*ɾ���Ľڵ�λ��ͷ�ڵ����һ���ڵ�*/
	if ((p_head->next->num == p_arr[data_location]->num) && (FindNum_Not_in_the_Link != 1))
	{
		// ͷ�ڵ㲢û�д洢����num,ֻ�洢����һ���ڵ��ַ
		p_head->next = p_arr[data_location]->next;
		p_del = p_arr[data_location];
		free(p_del);
	}

	/*ɾ���Ľڵ�λ���в�*/
	else if ((p_head->next->num != p_arr[data_location]->num) && (FindNum_Not_in_the_Link != 1))
	{
		data_location_Pre = data_location - 1;
		p_arr[data_location_Pre]->next = p_arr[data_location]->next;
		p_del = p_arr[data_location];
		free(p_del);
	}

	/*ɾ���Ľڵ�λ��β��*/
	else if ((p_arr[NumOfLink-1]->num == num)&& (FindNum_Not_in_the_Link != 1))
	{
		data_location_Pre = data_location - 1;
		p_arr[data_location_Pre]->next = NULL;
		p_del = p_arr[data_location];
		free(p_del);
	}

	/*ɾ���Ľڵ㲻��������*/
	if (FindNum_Not_in_the_Link)
	{
		FindNum_Not_in_the_Link = 0;
		printf("--------ERROR:ɾ���Ľڵ�����%d����������------!\n", num);
	}

	p_head = Sort_Link_Ascend(p_head);

	return p_head;
}

/**********************************************************************************
* @fun: Insert node ��������
* ������������в�������
********************************************************************************/
Link *Insert_Link(Link *p_head, u8 num)
{
	Link *p_move = p_head;
	Link *p_Temp = p_head;
	Link *p_pre = p_head;
	u8 lock_others = 0;
	u8 Flag = 0;
	u8 lock_MIDDLE_Insert = 0;

	Link *p_new = (Link *)malloc(sizeof(Link));
	p_new->num = num;
	p_new->next = NULL;

	/*����Ľڵ�λ��ͷ�ڵ�����һ���ڵ�֮��*/
	// ����֮����һ���ڵ�֮ǰ
	if (p_move->next->num >= num)
	{
		lock_others = 1;
		p_Temp = p_move->next; // ԭͷ�ڵ����һ���ڵ��ַ
		p_move->next = p_new;  // �µĽڵ��Ϊ ͷ�ڵ����һ���ڵ��ַ
		p_new->next = p_Temp;  // �½ڵ�� ͷ�ڵ����һ���ڵ�������
	}

	/*����Ľڵ�λ���в���β��*/
	// ��һ���ڵ�֮��
	if ((p_move->next->num <= num) && (lock_others != 1))
	{
		while (p_move->next->num <= num)
		{
			p_pre = p_move;
			p_move = p_move->next;
			if (p_move->next == NULL)
			{
				Flag = 1;
				break;
			}
		}

		if (Flag == 1)
		{
			p_move->next = p_new;
			lock_MIDDLE_Insert = 1;
		}
		
		if (lock_MIDDLE_Insert != 1)
		{
			p_Temp = p_pre->next;
			p_pre->next = p_new;
			p_new->next = p_Temp;
		}
	}

	p_head = Sort_Link_Ascend(p_head);

	return p_head;
}

/**********************************************************************************
* Print node
*
********************************************************************************/
void Print_Data(Link *p_head)
{ 
	// ������ͬʱ����ڵ���
	int count = 0;
	Link *p_move = p_head->next;
	while (p_move != NULL)
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
	head = Init_Link(arr,sizeof(arr));
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
