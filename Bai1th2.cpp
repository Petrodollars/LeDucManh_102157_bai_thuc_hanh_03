#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char hoten[30];
    int masv;
    float d1, d2, d3;
} Data;
typedef struct tagNode {
    Data infor;
    struct tagNode *link;
} Node;
typedef struct {
    Node* pHead;
    Node* pTail;
    int spt;
} LList;
void initList(LList* L) {
    L->pHead = NULL;
    L->pTail = NULL;
    L->spt = 0;
}
int emptyList(LList L) {
    return (L.spt == 0);
}
Node* createNode(Data x) {
    Node* pp = (Node*)malloc(sizeof(Node));
    if (pp != NULL) {
        pp->infor = x;
        pp->link = NULL;
    }
    return pp;
}
void insert_Head(LList* L, Data x) {
    Node* pp = createNode(x);
    if (pp == NULL) return;

    if (emptyList(*L)) {
        L->pHead = pp;
        L->pTail = pp;
    } else {
        pp->link = L->pHead;
        L->pHead = pp;
    }
    L->spt++;
}
void insert_Tail(LList* L, Data x) {
    Node* pp = createNode(x);
    if (pp == NULL) return;
    if (emptyList(*L)) {
        L->pHead = pp;
        L->pTail = pp;
    } else {
        L->pTail->link = pp;
        L->pTail = pp;
    }
    L->spt++;
}
Node* searchNode(LList L, int masv) {
    Node* p = L.pHead;
    while (p != NULL) {
        if (p->infor.masv == masv) {
            return p;
        }
        p = p->link;
    }
    return NULL;
}
void insert_After(LList* L, Node* q, Data x) {
    if (q == NULL) return;
    Node* pp = createNode(x);
    if (pp == NULL) return;
    pp->link = q->link;
    if (q->link == NULL) {
        L->pTail = pp;
    }
    q->link = pp;
    L->spt++;
}
void insert_Before(LList* L, Node* q, Data x) {
    if (q == NULL) return;
    if (q == L->pHead) {
        insert_Head(L, x);
        return;
    }
    Node* prev = L->pHead;
    while (prev != NULL && prev->link != q) {
        prev = prev->link;
    }
    if (prev != NULL) {
        Node* pp = createNode(x);
        if (pp == NULL) return;
        pp->link = q;
        prev->link = pp;
        L->spt++;
    }
}
void del_Head(LList *L) {
    Node *pp;
    if (emptyList(*L)) return;
    else {
        pp = L->pHead;
        L->pHead = pp->link;
        free(pp);
        L->spt--;
        if (L->pHead == NULL) L->pTail = NULL;
    }
}
void del_After(LList *L, Node *q) {
    Node *pp;
    if (NULL == q || NULL == q->link) return;
    else {
        pp = q->link; 
        q->link = pp->link;
        if (NULL == L->pTail || pp == L->pTail)
            L->pTail = q;
        free(pp);
        L->spt--;
    }
}
void del_K(DList *L, char K[30]) {
    Node *pp = L->pHead, *q;
    while (pp != NULL && !strstr(pp->infor.hoten, K))
    	  q = pp; 
        pp = pp->next;
    if (NULL == pp) return;
    else
        if (pp == L->pHead) del_Head(L);
        else {
            q = pp->prev;
            del_After(L, q);
        }
}
void nhap(Data* x) {
    printf("Nhap ma sinh vien: ");
    scanf("%d", &(x->masv));
    if (x->masv > 0) {
        printf("Nhap ho ten sinh vien: ");
        scanf(" %[^\n]", x->hoten);
        printf("Nhap diem mon 1: ");
        scanf("%f", &(x->d1));
        printf("Nhap diem mon 2: ");
        scanf("%f", &(x->d2));
        printf("Nhap diem mon 3: ");
        scanf("%f", &(x->d3));
    }
}
void in(Data x) {
    printf("Ten: %s, Ma: %d, Diem 1: %.2f, Diem 2: %.2f, Diem 3: %.2f\n",
           x.hoten, x.masv, x.d1, x.d2, x.d3);
}
void processList(LList LL) {
    if (emptyList(LL)) {
        printf("Danh sach dang rong!\n");
        return;
    }
    Node* pp = LL.pHead;
    while (pp != NULL) {
        in(pp->infor);
        pp = pp->link;
    }
}
void printReverse(Node* p) {
    if (p == NULL) return;
    printReverse(p->link);
    in(p->infor);
}
void processListReverse(LList LL) {
    if (emptyList(LL)) {
        printf("Danh sach dang rong!\n");
        return;
    }
    printReverse(LL.pHead);
}
void freeList(LList* L) {
    Node* p;
    while (L->pHead != NULL) {
        p = L->pHead;
        L->pHead = L->pHead->link;
        free(p);
    }
    L->pTail = NULL;
    L->spt = 0;
}
int main() {
    LList L;
    int kt = 0, chon, maTim;
    char tenXoa[30];
    Data x;
    Node* q;
    initList(&L);
    do {
        printf("\n=== CHUONG TRINH LAM VIEC VOI DSLK DON SV ===\n");
        printf("1: Them nut vao dau danh sach\n");
        printf("2: Them nut vao cuoi danh sach\n");
        printf("3: Them nut vao sau mot nut khac trong danh sach\n");
        printf("4: Them nut vao truoc mot nut khac trong danh sach\n");
        printf("5: Xoa theo ten\n");
        printf("8: Duyet danh sach (Tu cuoi ve dau)\n");
        printf("9: Duyet danh sach (Tu dau den cuoi)\n");
        printf("0: Thoat\n");
        printf("Moi ban chon: ");
        scanf("%d", &chon);
        switch (chon) {
            case 1:
                printf("\n--- Them dau danh sach ---\n");
                nhap(&x);
                if (x.masv > 0) insert_Head(&L, x);
                break;
            case 2:
                printf("\n--- Them cuoi danh sach ---\n");
                nhap(&x);
                if (x.masv > 0) insert_Tail(&L, x);
                break;
            case 3:
                printf("\n--- Them sau mot sinh vien ---\n");
                printf("Nhap ma sinh vien dung truoc: ");
                scanf("%d", &maTim);
                q = searchNode(L, maTim);
                if (q != NULL) {
                    printf("Da tim thay SV! Nhap thong tin SV moi can chen:\n");
                    nhap(&x);
                    if (x.masv > 0) insert_After(&L, q, x);
                } else {
                    printf("Khong tim thay sinh vien co ma %d!\n", maTim);
                }
                break;
            case 4:
                printf("\n--- Them truoc mot sinh vien ---\n");
                printf("Nhap ma sinh vien dung sau: ");
                scanf("%d", &maTim);
                q = searchNode(L, maTim);
                if (q != NULL) {
                    printf("Da tim thay SV! Nhap thong tin SV moi can chen:\n");
                    nhap(&x);
                    if (x.masv > 0) insert_Before(&L, q, x);
                } else {
                    printf("Khong tim thay sinh vien co ma %d!\n", maTim);
                }
                break;
            case 5:
                printf("\n--- Xoa sinh vien theo ten ---\n");
                printf("Nhap ten sinh vien can xoa: ");
                scanf(" %[^\n]", tenXoa);
                deleteByName(&L, tenXoa);
                break;
            case 8:
                printf("\n--- Danh sach sinh vien duyet nguoc (Tong: %d) ---\n", L.spt);
                processListReverse(L);
                break;
            case 9:
                printf("\n--- Danh sach sinh vien duyet xuoi (Tong: %d) ---\n", L.spt);
                processList(L);
                break;
            case 0:
                freeList(&L);
                printf("Bye bye!\n");
                kt = 1;
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (kt == 0);
    return 0;
}
