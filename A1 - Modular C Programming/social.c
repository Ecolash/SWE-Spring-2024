/*

NAME: TUHIN MONDAL
ROLL NO:22CS10087
DEPARTMENT : Department of Computer Science & Engineering
-----------------------------------------------------------
ASSIGNMENT NO - 1
Modular C Programming
-----------------------------------------------------------
*/

#include "social.h"

/*
GLOBAL VARIABLE : HEAD
-----------------------
It is a pointer to our main list of NODES in our social networking program
It is kept global so that the list can be accesssed and updated by all the functions easily
*/
NODE *HEAD;

NODE *create()
{
    int type, ID, creation_date;
    char name[NAME_SIZE];
    NODE *N = (NODE *)malloc(sizeof(NODE));

    printf("Type of Node to create: (1) Individual | (2) Group | (3) Business | (4) Organisation \nSelect Type(1 - 4): ");
    do
    {
        printf("Enter Type: ");
        scanf("%d", &type);
        if (type < 1 || type > 4) printf("Invalid input! Please enter a value between 1 and 4.\n");
    } while (type < 1 || type > 4);

    printf("--------------------------------------------\n");
    printf("Enter ID: ");
    scanf("%d", &ID);

    if (searchbyID(ID) == NULL)
    {
        N->ID = ID;
        printf("Enter Creation Date (DD-MM-YYYY): ");
        N->creation_date = getDate();

        printf("Enter Name: ");
        scanf(" %[^\n]", name);
        strcpy(N->name, name);

        N->type = type;
        N->head = NULL;

        if (type == 1) (N->pointer) = (int *)create_individual(ID);

        else if (type == 2)
        {
            group *node = create_group(ID);
            (N->pointer) = (int *)node;
            N->head = node->head;
        }

        else if (type == 3)
        {
            business *node = create_business(ID);
            (N->pointer) = (int *)node;
            N->head = node->head;
        }

        else if (type == 4)
        {
            organisation *node = create_organisation(ID);
            (N->pointer) = (int *)node;
            N->head = node->members;
        }

        N->next = NULL;
        printf("--------------------------------------------\n");
        printf("Node with ID : %d created successfully! \n", ID);
        printf("--------------------------------------------\n");

        N->content_head = NULL;
        int flag = 1;
        while (flag == 1)
        {
            printf("Do you want to post any content? (1 for Yes|0 for No): ");
            scanf("%d", &flag);
            if (flag == 1)
            {
                char content[CONTENT_SIZE];
                printf("Enter Content: ");
                scanf(" %[^\n]", content);
                ContentNode *node = searchContent(N->content_head, content);

                if (node == NULL) N->content_head = addContent(N->content_head, content);
                else printf("Content already posted earlier!\n\n");
            }
        }
        printf("==========================================\n");
        return N;
    }

    else
    {
        printf("ID already exist! \nTerminating...\n\n");
        return NULL;
    }
};

individual *create_individual(int curr_ID)
{
    char name[NAME_SIZE];
    char content[CONTENT_SIZE];
    int birthday;

    individual *node = malloc(sizeof(individual));
    printf("--------------------------------------------\n");
    printf("CREATING A NODE OF TYPE : INDIVIDUAL...\n");
    printf("--------------------------------------------\n");
    printf("Enter Birthday (DD-MM-YYYY): ");
    node->birthday = getDate();
    return node;
}

group *create_group(int curr_ID)
{
    char name[NAME_SIZE];
    char content[CONTENT_SIZE];
    int ID, creation_date;

    group *node = malloc(sizeof(group));
    printf("--------------------------------------------\n");
    printf("CREATING A NODE OF TYPE : GROUP...\n");
    printf("--------------------------------------------\n");

    IDNode *head1 = NULL;
    IDNode *head2 = NULL;
    IDNode *head3 = NULL;

    int flag = 1;
    while (flag == 1)
    {
        int ID;
        printf("Do you want to add members (1 for Yes|0 for No): ");
        scanf("%d", &flag);

        if (flag == 1)
        {
            printf("Enter ID: ");
            scanf("%d", &ID);
            NODE *N = searchbyID(ID);
            if (N != NULL)
            {
                if (N->type == 1)
                {
                    head1 = insertListNode(head1, ID);
                    N->head = insertListNode(N->head, curr_ID);
                    head3 = insertListNode(head3, ID);
                }
                else printf("No Node with ID %d found for individuals!\n\n", ID);
            }
            else printf("No Node with ID %d found for individuals!\n\n", ID);
        }
    }

    flag = 1;
    while (flag == 1)
    {
        int ID;
        printf("Do you want to add business (1 for Yes|0 for No): ");
        scanf("%d", &flag);

        if (flag == 1)
        {
            printf("Enter ID: ");
            scanf("%d", &ID);
            NODE *N = searchbyID(ID);
            if (N != NULL)
            {
                if (N->type == 3)
                {
                    head2 = insertListNode(head2, ID);
                    N->head = insertListNode(N->head, curr_ID);
                    head3 = insertListNode(head3, ID);
                }
                else printf("No Node with ID %d found for business!\n\n", ID);
            }
            else printf("No Node with ID %d found for business!\n\n", ID);
        }
    }

    node->members = head1;
    node->businesses = head2;
    node->head = head3;
    return node;
}

business *create_business(int curr_ID)
{
    char name[NAME_SIZE];
    char content[CONTENT_SIZE];
    int x, y;

    business *node = malloc(sizeof(business));
    printf("--------------------------------------------\n");
    printf("CREATING A NODE OF TYPE : BUSINESS...\n");
    printf("--------------------------------------------\n");

    printf("Enter Location (X, Y): ");
    scanf("%f, %f", &(node->location_x), &(node->location_y));

    IDNode *head1 = NULL;
    IDNode *head2 = NULL;
    IDNode *head3 = NULL;

    int flag = 1;
    while (flag == 1)
    {
        int ID;
        printf("Do you want to add owners (1 for Yes|0 for No): ");
        scanf("%d", &flag);

        if (flag == 1)
        {
            printf("Enter ID: ");
            scanf("%d", &ID);
            NODE *N = searchbyID(ID);

            if (N != NULL)
            {
                if (N->type == 1)
                {
                    head1 = insertListNode(head1, ID);
                    N->head = insertListNode(N->head, curr_ID);
                    head3 = insertListNode(head3, ID);
                }
                else printf("No Node with ID %d found for individual!\n\n", ID);
            }
            else printf("No Node with ID %d found for individual!\n\n", ID);
        }
    }

    flag = 1;
    while (flag == 1)
    {
        int ID;
        printf("Do you want to add customers (1 for Yes|0 for No): ");
        scanf("%d", &flag);

        if (flag == 1)
        {
            printf("Enter ID: ");
            scanf("%d", &ID);
            NODE *N = searchbyID(ID);

            if (N != NULL)
            {
                if (N->type == 1)
                {
                    head2 = insertListNode(head2, ID);
                    N->head = insertListNode(N->head, curr_ID);
                    head3 = insertListNode(head3, ID);
                }
                else printf("No Node with ID %d found for individual!\n\n", ID);
            }
            else printf("No Node with ID %d found for individual!\n\n", ID);
        }
    }
    node->owners = head1;
    node->customers = head2;
    node->head = head3;
    return node;
}

organisation *create_organisation(int curr_ID)
{
    char content[CONTENT_SIZE];
    organisation *node = malloc(sizeof(organisation));

    printf("--------------------------------------------\n");
    printf("CREATING A NODE OF TYPE : ORGANISATION...\n");
    printf("--------------------------------------------\n");

    printf("Enter Location (X, Y): ");
    scanf("%f, %f", &(node->location_x), &(node->location_y));

    IDNode *head1 = NULL;
    int flag = 1;
    while (flag == 1)
    {
        int ID;
        printf("Do you want to add members (1 for Yes|0 for No): ");
        scanf("%d", &flag);
        if (flag == 1)
        {
            printf("Enter ID: ");
            scanf("%d", &ID);
            NODE *N = searchbyID(ID);
            if (N != NULL)
            {
                if (N->type == 1)
                {
                    head1 = insertListNode(head1, ID);
                    N->head = insertListNode(N->head, curr_ID);
                }
                else printf("No Node with ID %d found for individual!\n\n", ID);
            }
            else printf("No Node with ID %d found for individual!\n\n", ID);
        }
    }
    node->members = head1;
    return node;
}

void print_individual(individual *P)
{
    date *D = P->birthday;
    printf("Birthday: %02d-%02d-%04d\n", D->day, D->month, D->year);
}

void print_group(group *P)
{
    printf("Members: ");
    IDNode *temp = P->members;
    while (temp != NULL)
    {
        printf("%d ", temp->ID);
        temp = temp->next;
    }
    printf("\n");
    printf("Business: ");

    IDNode *temp2 = P->businesses;
    while (temp2 != NULL)
    {
        printf("%d ", temp2->ID);
        temp2 = temp2->next;
    }
    printf("\n");
}

void print_business(business *P)
{
    printf("Location: (%f, %f)\n", P->location_x, P->location_y);
    printf("Owners: ");
    IDNode *temp = P->owners;
    while (temp != NULL)
    {
        printf("%d ", temp->ID);
        temp = temp->next;
    }
    printf("\n");

    printf("Customers: ");
    IDNode *temp2 = P->customers;
    while (temp2 != NULL)
    {
        printf("%d ", temp2->ID);
        temp2 = temp2->next;
    }
    printf("\n");
}

void print_organisation(organisation *P)
{
    printf("Location: (%f, %f)\n", P->location_x, P->location_y);
    printf("Members: ");

    IDNode *temp = P->members;
    while (temp != NULL)
    {
        printf("%d ", temp->ID);
        temp = temp->next;
    }
    printf("\n");
}

void print_NODE(NODE *N)
{
    printf("ID: %d\n", N->ID);
    printf("Name: %s\n", N->name);
    date *D = N->creation_date;

    printf("Creation Date: %02d-%02d-%04d\n", D->day, D->month, D->year);
    int type = N->type;
    if (type == 1)
    {
        printf("Type: INDIVIDUAL\n");
        print_individual((individual *)(N->pointer));
    }
    else if (type == 2)
    {
        printf("Type: GROUP\n");
        print_group((group *)(N->pointer));
    }
    else if (type == 3)
    {
        printf("Type: BUSINESS\n");
        print_business((business *)(N->pointer));
    }
    else if (type == 4)
    {
        printf("Type: ORGANISATION\n");
        print_organisation((organisation *)(N->pointer));
    }
}

void printAllContent(int ID)
{
    NODE *N = searchbyID(ID);
    if (N == NULL)
    {
        printf("No node of this ID found! \n");
        return;
    }
    printf("--------------------------------------------\n");
    printf("CONTENT POSTED BY NODE || ID: %d | Name: %s\n", N->ID, N->name);
    printf("--------------------------------------------\n");

    ContentNode *temp = N->content_head;
    int i = 1;

    while (temp != NULL)
    {
        printf("(%d) | %s\n", (i++), temp->content);
        temp = temp->next;
    }
    if (i == 1) printf("       <<< No Content Posted yet! >>>\n");
    printf("--------------------------------------------\n");
}

void printAllNodes()
{
    NODE *p = HEAD;
    printf("--------------------------------------------\n");
    while (p != NULL)
    {
        print_NODE(p);
        printf("--------------------------------------------\n");
        p = p->next;
    }
}

NODE *searchbyID(int ID)
{
    NODE *p = HEAD;
    while (p != NULL)
    {
        if (p->ID == ID) return p;
        p = p->next;
    }
    return NULL;
}

void searchbyName(char *name)
{
    NODE *p = HEAD;
    int flag = 0;
    while (p != NULL)
    {
        if (strcmp(p->name, name) == 0)
        {
            print_NODE(p);
            flag = 1;
        }
        p = p->next;
    }
    if (flag == 0) printf("No node of this type found! \n");
}

void searchbyType(int type)
{
    NODE *p = HEAD;
    int flag = 0;

    printf("--------------------------------------------\n");
    while (p != NULL)
    {
        if (p->type == type)
        {
            print_NODE(p);
            printf("--------------------------------------------\n");
            flag = 1;
        }
        p = p->next;
    }
    if (flag == 0) printf("No node of this type found! \n");
}

void searchbyBirthday(date *birthday)
{
    NODE *p = HEAD;
    int flag = 0;
    printf("--------------------------------------------\n");
    while (p != NULL)
    {
        if (p->type == 1)
        {
            individual *node = (individual *)(p->pointer);
            if (compDate(node->birthday, birthday))
            {
                print_NODE(p);
                printf("--------------------------------------------\n");
                flag = 1;
            }
        }
        p = p->next;
    }
    if (flag == 0) printf("No individual with this birthday found! \n");
}

date *getDate()
{
    date *D = (date *)malloc(sizeof(date));
    scanf("%d-%d-%d", &D->day, &D->month, &D->year);
    return D;
}

int compDate(date *d1, date *d2)
{
    return ((d1->day == d2->day) && (d1->month == d2->month) && (d1->year == d2->year));
}

IDNode *insertListNode(IDNode *head, int ID)
{
    IDNode *node = (IDNode *)malloc(sizeof(IDNode));
    node->ID = ID;
    node->next = NULL;
    if (head == NULL)
    {
        head = node;
        return head;
    }
    else
    {
        IDNode *temp = head;
        while (temp->next != NULL)
        {
            if (temp->ID == ID) return head;
            temp = temp->next;
        }
        if (temp->ID == ID) return head;
        temp->next = node;
    }
    return head;
}

IDNode *deleteListNode(IDNode *head, int ID)
{
    if (head == NULL) return head;
    IDNode *p = head;
    if (p->ID == ID)
    {
        head = head->next;
        free(p);
        return head;
    }

    if (head->next == NULL) return head;
    IDNode *q = head->next;
    while (q->ID != ID && q->next != NULL)
    {
        p = p->next;
        q = q->next;
    }
    if (q->ID == ID)
    {
        p->next = q->next;
        free(q);
    }
    return head;
}

void Print1HopNodes(int ID)
{
    NODE *N = searchbyID(ID);
    if (N == NULL)
    {
        printf("No Node with ID %d found!\n\n", ID);
        return;
    }

    IDNode *head = N->head;
    printf("Linked Contents of Node with ID : %d\n", ID);
    printf("--------------------------------------------\n");
    while (head != NULL)
    {
        int search = head->ID;
        NODE *temp = searchbyID(search);
        print_NODE(temp);
        printf("--------------------------------------------\n");
        head = head->next;
    }
}

NODE *insertNODE(NODE *head)
{
    NODE *temp = create();
    if (temp == NULL) return head;
    temp->next = head;
    return temp;
}

NODE *deleteNODE(NODE *head, int ID)
{
    int flag = 1;
    if (HEAD == NULL)
    {
        printf("ID does not exist!\n\n");
        return HEAD;
    }

    NODE *p = HEAD;
    if (p->ID == ID)
    {
        HEAD = HEAD->next;
        printf("--------------------------------------------\n");
        printf("Node ID : %d deleted successfully! \n", ID);
        printf("--------------------------------------------\n");
        clearNode(p);
        flag = 0;
        return HEAD;
    }

    if (HEAD->next != NULL)
    {
        NODE *q = HEAD->next;
        while (q->ID != ID && q->next != NULL)
        {
            p = p->next;
            q = q->next;
        }

        if (q->ID == ID)
        {
            p->next = q->next;
            printf("--------------------------------------------\n");
            printf("Node ID : %d deleted successfully! \n", ID);
            printf("--------------------------------------------\n");
            clearNode(q);
            flag = 0;
        }

        if (flag == 1) printf("ID does not exist!\n\n");
        return HEAD;
    }
    if (flag == 1) printf("ID does not exist!\n\n");
    else return HEAD;
}

void clearNode(NODE *N)
{
    IDNode *headN = N->head;
    int ID = N->ID;

    while (headN != NULL)
    {
        NODE *temp = searchbyID(headN->ID);
        if (temp != NULL)
        {
            IDNode *IDtemp = temp->head;
            IDtemp = deleteListNode(IDtemp, ID);
            temp->head = IDtemp;

            int type = temp->type;
            if (type == 2)
            {
                group *node = ((group *)(temp->pointer));
                IDtemp = node->members;
                IDtemp = deleteListNode(IDtemp, ID);
                node->members = IDtemp;
                IDtemp = node->businesses;
                IDtemp = deleteListNode(IDtemp, ID);
                node->businesses = IDtemp;
            }
            else if (type == 3)
            {
                business *node = ((business *)(temp->pointer));
                IDtemp = node->owners;
                IDtemp = deleteListNode(IDtemp, ID);
                node->owners = IDtemp;
                IDtemp = node->customers;
                IDtemp = deleteListNode(IDtemp, ID);
                node->customers = IDtemp;
            }
            else if (type == 4)
            {
                organisation *node = ((organisation *)(temp->pointer));
                IDtemp = node->members;
                IDtemp = deleteListNode(IDtemp, ID);
                node->members = IDtemp;
            }
        }
        headN = headN->next;
    }

    free(N->pointer);
    free(N->head);
    free(N->content_head);
    free(N);
    return;
}

ContentNode *searchContent(ContentNode *head, char *content)
{
    ContentNode *p = head;
    int flag = 0;
    while (p != NULL)
    {
        if (strstr(p->content, content))
            return p;
        p = p->next;
    }
    return NULL;
}

void searchAllContent()
{
    char content[CONTENT_SIZE];
    printf("Enter search query for content: ");
    scanf(" %[^\n]", content);

    NODE *p = HEAD;
    int flag = 0;
    printf("--------------------------------------------\n");
    printf("Searching for Content : %s\n", content);
    printf("--------------------------------------------\n");
    while (p != NULL)
    {
        ContentNode *N = searchContent(p->content_head, content);
        if (N != NULL) printf("(%d) ID: %d | Name: %s | Content: %s\n", ++flag, p->ID, p->name, N->content);
        p = p->next;
    }

    printf("--------------------------------------------\n");
    if (flag == 0) printf("No node of this type found! \n");
    else printf("%d nodes posted this content! \n", flag);
    printf("--------------------------------------------\n");
}

ContentNode *addContent(ContentNode *head, char *content)
{
    ContentNode *temp = (ContentNode *)malloc(sizeof(ContentNode));
    strcpy(temp->content, content);
    temp->next = head;
    return temp;
}

void printMenu()
{
    printf("==========================================");
    printf("\nSocial Networking Program Menu:\n");
    printf("==========================================\n\n");

    printf("(1) ---> Create Node\n");
    printf("(2) ---> Delete Node\n");
    printf("(3) ---> Search Nodes\n");
    printf("(4) ---> Print 1-Hop Linked Nodes\n");
    printf("(5) ---> View All Posted Content\n");
    printf("(6) ---> Create and Post Content\n");
    printf("(7) ---> Search Content\n");
    printf("(8) ---> Display Contents of Linked Individual\n");
    printf("(9) ---> Print All Nodes\n");
    printf("(0) ---> Exit\n\n");
}

void printSearchMenu()
{
    printf("---------------------\n");
    printf("\nSearch Menu:\n");
    printf("---------------------\n\n");

    printf("(1) ---> Search by ID\n");
    printf("(2) ---> Search by Name\n");
    printf("(3) ---> Search by Type\n");
    printf("(4) ---> Search by Birthday\n");
    printf("(0) ---> Back to Main Menu\n\n");
}

void search()
{
    int choice, birthday, type, ID;
    char str[50];
    do
    {
        printSearchMenu();
        printf("Enter your search choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter ID to search: ");
            scanf("%d", &ID);
            NODE *ans = searchbyID(ID);
            if (ans == NULL) printf("No node of this ID found! \n");
            else print_NODE(ans);
            break;

        case 2:
            printf("Enter name to search: ");
            scanf("%s", str);
            searchbyName(str);
            break;

        case 3:
            printf ("Type of Nodes: (1)Individual | (2)Group | (3)Business | (4)Organisation\n");
            do
            {
                printf("Enter Type (1 - 4): ");
                scanf("%d", &type);
                if (type < 1 || type > 4) printf("Invalid input! Please enter a value between 1 and 4!\n");
            } while (type < 1 || type > 4);
            searchbyType(type);
            break;

        case 4:
            printf("Enter birthday to search (DD-MM-YYYY): ");
            date *D = getDate();
            searchbyBirthday(D);
            break;

        case 0:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice! Please enter a valid option.\n");
        }

    } while (choice != 0);
}

void createPost()
{
    int ID;
    char content[CONTENT_SIZE];
    printf("Enter ID of Node to create a post: ");
    scanf("%d", &ID);
    printf("Enter content: ");
    scanf(" %[^\n]", content);
    NODE *ans = searchbyID(ID);

    if (ans == NULL) printf("No node of this ID found! \n");
    else
    {
        ans->content_head = addContent(ans->content_head, content);
        printf("--------------------------------------------\n");
        printf("Content posted by Node ID : %d successfully! \n", ID);
        printf("--------------------------------------------\n");
    }
}

void seeLinkedContent(int ID)
{
    NODE *ans = searchbyID(ID);
    if (ans == NULL)
    {
        printf("No node of this ID found! \n");
        return;
    }
    if (ans->type != 1)
    {
        printf("Node not of type Individual! \n");
        return;
    }

    IDNode *linked = NULL;
    IDNode *head = ans->head;
    while (head != NULL)
    {
        int id = head->ID;
        NODE *N = searchbyID(id);
        if (N->type == 2 || N->type == 4)
        {
            IDNode *curr = N->head;
            while (curr != NULL)
            {
                NODE *currNode = searchbyID(curr->ID);
                if (currNode->type == 1 && currNode->ID != ID) linked = insertListNode(linked, currNode->ID);
                curr = curr->next;
            }
        }
        head = head->next;
    }

    printf("--------------------------------------------------------------------------------------\n");
    printf("ALL CONTENT POSTED BY INDIVIDUAL LINKED TO NODE ID : %d | NAME : %s\n", ID, ans->name);
    printf("--------------------------------------------------------------------------------------\n");
    IDNode *printer = linked;
    while (printer != NULL)
    {
        printAllContent(printer->ID);
        printer = printer->next;
    }
}

int main()
{
    int choice, ID;
    char name[NAME_SIZE];
    char content[CONTENT_SIZE];
    HEAD = NULL;

    do
    {
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            HEAD = insertNODE(HEAD);
            break;

        case 2:
            printf("Enter node ID to delete: ");
            scanf("%d", &ID);
            HEAD = deleteNODE(HEAD, ID);
            break;

        case 3:
            search(HEAD);
            break;

        case 4:
            printf("Enter node ID: ");
            scanf("%d", &ID);
            Print1HopNodes(ID);
            break;

        case 5:
            printf("Enter node ID to view all posted content: ");
            scanf("%d", &ID);
            printAllContent(ID);
            break;

        case 6:
            createPost();
            break;

        case 7:
            searchAllContent(content);
            break;

        case 8:
            printf("Enter node ID of individual node to see all content posted by individuals linked to it: ");
            scanf("%d", &ID);
            seeLinkedContent(ID);
            break;

        case 9:
            printAllNodes(HEAD);
            break;

        case 0:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 0);
    return 0;
}