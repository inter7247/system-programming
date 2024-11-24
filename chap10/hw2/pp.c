#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

struct node {
   int data;
   struct node *next;
};

void addq(struct node **head, struct node **tail, int data);
int delete(struct node **head, struct node **tail);

int main() {
   int data;
   struct node *head, *tail = NULL;

   while(scanf("%d", &data) == 1) {
      if(data <= 0) {
         break;
      }
      addq(&head, &tail, data);
   }

   printf("print queue\n");

   while (head != NULL)  {
      printf("%d\n", delete(&head, &tail));
   }
   
   exit(0);
}

void addq(struct node **head, struct node **tail, int data) {
   struct node *p = (struct node *) malloc(sizeof(struct node));
   p->data = data;
   p->next = NULL;
   if(*tail == NULL) { //큐가 처음 생성 or 모든 데이터 제거 상태
      *head = p; // 새 노드를 가리킴(고정)
      *tail = p; // 새 노드를 가리킴(이후 변동)
   } else {
      (*tail)->next = p; //기존 tail의 next를 새 노드로 연결
      *tail = p; //tail을 새 노드로 이동
   }
}

int delete(struct node **head, struct node **tail) {
    struct node *temp = *head; //head를 temp에 임시 저장
    int data = temp->data; //제거할 노드가 가진 데이터를 저장
    *head = temp->next; //현 head를 다음 노드로 연결
    free(temp);//임시 저장 노드 메모리 해제
    return data; //제거된 노드의 데이터를 반환  
}

/* 큐 이해
1) [NULL]
   (head/tail)
2) [808]       → [NULL]
   (head/tail)
3) [808] → [9147] → [NULL]
   (head)  (tail)
4) [808] → [9147] → [5555] → [NULL]
   (head)           (tail)
5) [9147] → [5555] → [NULL] //delete 실행시
   (head)   (tail)
*/
