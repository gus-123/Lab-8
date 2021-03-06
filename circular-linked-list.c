/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */
//연결 리스트의 노드 구조를 구조체로 정의
typedef struct Node {
	int key;
	struct Node* llink;  //왼쪽(이전) 노드에 대한 링크
	struct Node* rlink;  //오른쪽(다음) 노드에 대한 링크
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
    printf("[----- [김현민]  [2018038088] -----]\n");
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	// headNode가 null이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 
	if(*h != NULL)
		freeList(*h);

	// headNode에 대한 메모리를 할당하여 다시 리턴
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){
    listNode* p = h;  //p는 headNode가 가리키는 노드를 할당

	listNode* prev = NULL;  //prev 노드를 초기화
	while(p != NULL) {
		prev = p;
		p = p->rlink;
		free(prev);  //prev의 메모리 할당 해제
	}
	free(h); //headNode의 메모리 할당 해제

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {  //headNode가 null인 경우
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;  //headNode의 rlink를 p에 저장

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	//메모리 주소 출력
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode)); //삽입할 새로운 노드의 동적 메모리 할당
	node->key = key; //새로운 노드의 데이터필드에 key 저장

	node->rlink = h; //headNode를 새로운 노드의 rlink에 저장
	node->llink = h->llink; //headNode의 llink를 새로운 노드의 llink에 저장

	h->llink->rlink = node; //새로운 노드의 주소를 headNode의 llink의 rlink에 저장
	h->llink = node;  //새로운 노드의 주소를 headNode의 llink에 저장

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
    listNode* deleted = h->llink;  //headNode의 llink를 가리키는 노드를 할당

	if (deleted == h) {  //deleted노드가 headNode인 경우
		return 0;
	}

	h->llink = h->llink->llink;  //headNode의 rlink의 llink를 headNode의 llink에 저장
	h->llink->rlink = h;  //headNode를 headNode의 rlink의 llink에 저장
	free(deleted);  //deleted 메모리 할당 해제

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode)); //삽입할 새로운 노드의 동적 메모리 할당
	node->key = key; //새로운 노드의 데이터필드에 key 저장
	
	node->rlink = h->rlink;  //headNode의 rlink를 새로운 노드의 rlink에 저장
	node->llink = h;  //headNode를 새로운 노드의 llink에 저장

	h->rlink->llink = node;  //새로운 노드의 주소를 headNode의 rlink의 llink에 저장
	h->rlink = node;  //새로운 노드의 주소를 headNode의 rlink에 저장

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
    listNode* deleted = h->rlink;  //headNode의 rlink를 가리키는 노드를 할당

	if (deleted == h) {  //deleted노드가 headNode인 경우
		return 0;
	}

	h->rlink = h->rlink->rlink;  //headNode의 rlink의 llink를 headNode의 rlink에 저장
	h->rlink->llink = h;  //headNode를 headNode의 rlink의 llink에 저장
	free(deleted);  //deleted 메모리 할당 해제

	return 1;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
    listNode* nextNode = NULL;  //다음 위치를 참조하는 할당
	listNode* currentNode = h;  //현재 위치를 참조하는 할당
	listNode* preNode = NULL;  //이전 위치를 참조하는 할당
    
    while (currentNode) {  //currentNode인 경우
    	nextNode = currentNode -> rlink;  //currentNode의 rlink를 nextNode에 저장
        currentNode -> rlink = preNode;  //preNode를 currentNode의 rlink에 저장
        preNode = currentNode;  //currentNode를 preNode에 저장
        currentNode = nextNode;  //nextNode를 currentNode에 저장
    }
    h = preNode; //preNode를 headNode로 역순을 시켜줌

	return 0;
}



/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 
 **/
int insertNode(listNode* h, int key) {
    listNode* preNode = h;  //headNode를 가리키는 노드를 할당
    listNode* node = (listNode*)malloc(sizeof(listNode));  //삽입할 새로운 노드의 동적 메모리 할당
	node->key = key;  //새로운 노드의 데이터필드에 key 저장

    if (h == NULL) {  //headNode가 null인 경우
        h->rlink = node;  //새로운 노드의 주소를 headNode의 rlink에 저장
    }
    else {  //headNode가 null이 아닌 경우
		if (node->key < h->key) {  //삽입할 위치가 맨 앞인 경우
			node->rlink = h->rlink;  //headNode의 rlink를 새로운 노드의 rlink에 저장
            h->rlink = node;  //새로운 노드의 주소를 headNode의 rlinK에 저장
        }
        else {
            while (preNode->rlink) {  //preNode의 rlink인 경우
				if (node->key < preNode->rlink->key) {  //삽입할 위치 찾기
					break;
				}
                preNode = preNode->rlink;  //preNode의 rlink를 preNode에 저장
            }
            node->rlink = preNode->rlink;  //preNode의 rlink를 새로운 노드의 rlink에 저장
            preNode->rlink = node;  //새로운 노드의 주소를 preNode의 rlinK에 저장
        }
    }

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
    listNode* p, * deleted;

    if (h->key == key) {  //headNode가 가리키는 key가 key값과 동일한 경우
        deleted = h;  //headNode를 deleted에 저장
        h = h->rlink;  //headNode의 rlink를 headNodek에 저장
        free(deleted);  //deleted 메모리 할당 해제
    }
    else {
        p = h;
        while (p->rlink) {
            if (key == p->rlink->key) {  //삭제할 위치 찾기
                deleted = p->rlink;  //p의 rlink를 deleted에 저장
                p->rlink = p->rlink->rlink;  //p의 rlink의 rlink를 p의 rlink에 저장
                free(deleted);  //deleted 메모리 할당 해제

                return 0;
            }
            p = p->rlink; //p의 rlink를 p에 저장
        }
    }

	return 0;
}