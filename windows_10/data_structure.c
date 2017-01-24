<자료구조 & 알고리즘>

# 재귀 Recursion 

	# 피보나치 수열 Fibonacci Sequence

	# 하노이탑 Hanoi Tower	


# 리스트 List : 배열 기반 리스트
	
	# 리스트는 데이터를 나란히 저장합니다. 중복된 데이터의 저장을 허용합니다

	# ADT
		typedef int LData;

		typedef struct __ArrayList
		{
			LData arr[LIST_LEN];
			int numofData;
			int curPosition;
		} ArrayList;

		typedef ArrayList List;

		void ListInit(List *plist)
		void LInsert(List *plist,LData data)
		int LFirst(List *plis, LData *pdata)
		int LNext(List *plist, Ldata *pdata)
		LData LRemove(List *plist)
		int LCount(List *plist)




# 연결리스트 Linked List

	# malloc, free를 사용한 동적 메모리를 사용하는 리스트
	
	# 단순 연결 리스트 : 연결의 형태가 한쪽 방향으로 전개되고 시작과 끝이 존재한다

		# ADT
			void ListInit(List *plist)
			void LInsert(List *plist, LData data)
			int LFirst(List *plist, LData *pdata)
			int LNext(List *plist, LData *pdata)
			LData LRemove(List *plist)
			int LCount(List *plist)
			void SetSortRule(List *plist, int (*comp)(LData d1, LData d2))
			





	# 양방향 연결 리스트




# 스택 Stack 





# 큐 Queue





# 트리 Tree
	




# 우선순위 큐와 힙 Priority Queue and Heap 




# 덱 Dequeue




# 정렬 Sort





# 탐색 Search



# 해시테이블 Hash Table



# 그래프 Graph
	# 신장트리
		# 최소비용신장트리
			# 크루스칼 알고리즘







