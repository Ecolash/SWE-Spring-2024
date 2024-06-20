/*

NAME: TUHIN MONDAL
ROLL NO:22CS10087
DEPARTMENT : Department of Computer Science & Engineering
-----------------------------------------------------------
ASSIGNMENT NO - 1
Modular C Programming
-----------------------------------------------------------
OVERVIEW OF DESIGN AND INPLEMENTATION OF PROGRAM
=================================================
Main Data Structures:
=====================
NODE:
    It is a master Node which stores common parameters of all types of nodes
    It has ID, name, creation date, type, and a pointer to a specific type of entity (individual, group, business, or organization).
    Individual, group, business, organisation: Structures representing different types of entities with specific attributes.
    These additional structures store extra information about nodes, based on its type

Important Functions:
====================
(1) create:             Creates a new node by prompting the user for input, including type, ID, name, and other attributes based on the type.
(2) insertNODE:         Inserts a newly created node into the linked list.
(3) deleteNODE:         Deletes a node based on the provided ID.
(4) search:            Search functions to find nodes based on different criteria.
(5) Print1HopNodes:     Prints information about 1-hop linked nodes of a specified node.
(6) printAllContent:    Prints all content posted by a specific node.
(7) createPost:         Allows a user to create and associate content with a specific node.
(8) searchAllContent:   Searches for content across all nodes.
(9) seeLinkedContent:   Prints all content posted by individuals linked to a specific individual node.
(10) printAllNodes:     Prints information about all nodes in the network.

Summary:
=========
The data structures used for storing information is linked lists.
It is chosen because a linked list provides easy insert, delete and linking operations
Each node can link with a number of other nodes, thus creating a social network
Linked lists can dynamically adjust their size
In a social network, the number of individuals, groups, businesses, and organizations may change over time


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
DEFINED CONSTANTS:
==================
CONTENT_SIZE: It represents the max size of the string content in the ContentNode structure.
NAME_SIZE: It represents the max size of the string name in the NODE structure.
*/
#define CONTENT_SIZE 1000
#define NAME_SIZE 100

/*--------------------------------------------------
STRUCTURES USED IN THIS APPLICATION
----------------------------------------------------*/
struct date;
struct NODE;
struct IDNode;
struct ContentNode;

struct individual;
struct group;
struct business;
struct organisation;

/*
STRUCTURE DESCRIPTION : NODE
------------------------------
This structure is intended to represent a node in our main list.

(1) ID: An integer associated with the node (primary key)
(2) Type: The type of the node
(3) creation_date: A pointer to a structure of type date representing the creation date of the node. 
(4) name: A character array (string) with name associated with the node.
(5) pointer: pointer to additional data or reference based on type of node
(6) next: A pointer to the next NODE in the linked list in our main list of all NODES
(7) head: A pointer to a linked list of IDNodes. Points to list of all connected nodes
(8) content_head: A pointer to a linked list of ContentNode. Points to list of all contents
*/
typedef struct NODE
{
    int ID, type;
    struct date *creation_date;
    char name[NAME_SIZE];
    int *pointer;
    struct NODE *next;
    struct IDNode *head;
    struct ContentNode *content_head;
} NODE;

/*
STRUCTURE DESCRIPTION: IDNODE
------------------------------
This structure is intended to represent a node with ID, used in linked data structures.

(1) ID: An integer representing the identifier associated with the node.
(2) next: A pointer to the next IDNode in the linked list. This indicates the order of nodes in the linked list
*/
typedef struct IDNode
{
    int ID;
    struct IDNode *next;
} IDNode;

/*
STRUCTURE DESCRIPTION: DATE
------------------------------
This structure is intended to represent a date with three components: day, month, and year.

(1) day: An integer representing the day of the date.
(2) month: An integer representing the month of the date.
(3) year: An integer representing the year of the date.
*/
typedef struct date
{
    int day;
    int month;
    int year;
} date;

/*
STRUCTURE DESCRIPTION: CONTENTNODE
------------------------------
This structure is intended to represent a node containing content, typically used in linked data structures.

(1) content: A string of content with a size specified by CONTENT_SIZE. 
(2) next: A pointer to the next ContentNode in the linked list.
*/
typedef struct ContentNode
{
    char content[CONTENT_SIZE];
    struct ContentNode *next;
} ContentNode;

/*
STRUCTURE DESCRIPTION: INDIVIDUAL
------------------------------
This structure is intended to store extra attributes an individual.
(1) birthday: A pointer to a structure of type date, representing the birthday of the individual.
*/
typedef struct individual
{
    date *birthday;
} individual;

/*
STRUCTURE DESCRIPTION: GROUP
------------------------------
This structure is intended to store extra attributes a group node.

(1) members: A pointer to an IDNode representing the linked list of members. Each member is identified using the IDNode structure.
(2) business: A pointer to an IDNode representing the linked list of business associated with the group. Each business is identified using the IDNode structure.
(3) head: A pointer to a linked list of IDNode. It points to the list of all connected nodes, including both members and business.
*/
typedef struct group
{
    IDNode *members, *businesses;
    struct IDNode *head;
} group;

/*
STRUCTURE DESCRIPTION: BUSINESS
------------------------------
This structure is intended to store extra attributes a business node.

(1) location_x, location_y: Floating point numbers representing the x and y coordinates of the business location, indicating its position in a two-dimensional space.
(2) owners: A pointer to an IDNode representing the linked list of owners associated with the business. Each owner is identified using the IDNode structure.
(3) customers: A pointer to an IDNode representing the linked list of customers associated with the business. Each customer is identified using the IDNode structure.
(4) head: A pointer to a linked list of IDNode. It points to the list of all connected nodes, possibly including both owners and customers.
*/
typedef struct business
{
    float location_x, location_y;
    IDNode *owners, *customers;
    struct IDNode *head;
} business;

/*
STRUCTURE DESCRIPTION: ORGANISATION
-----------------------------------
This structure is intended to store extra attributes a organisation node.

(1) location_x, location_y: Floating point numbers representing the x and y coordinates of the organisation location, indicating its position in a two-dimensional space.
(2) members: A pointer to an IDNode representing the linked list of members associated with the organisation. Each members is identified using the IDNode structure.
(3) head: A pointer to a linked list of IDNode. It points to the list of all connected nodes.
*/
typedef struct organisation
{
    float location_x, location_y;
    IDNode *members;
    struct IDNode *head;
} organisation;

/*
NODE *create():
==================
The NODE *create() function is responsible for creating a new node in a social networking program.
It prompts the user to input information such as the type of the node, its unique ID, creation date, and name.
Depending on the specified type, the function calls corresponding substructure creation functions for individual, group, business, or organization nodes.
It ensures that the provided ID is unique, associates the substructure with the new node, and allows the user to post content.
If the ID is already in use, the function notifies the user, and the process terminates without creating a new node.
The function returns a pointer to the newly created node in the linked list of nodes.

*/
NODE *create();

/*
individual *create_individual(int curr_ID):
===========================================
The create_individual function is responsible for generating an individual node in the social networking program.
It prompts the user to input details such as the individual's name and birthday in "DD-MM-YYYY" format.
*/
individual *create_individual(int curr_ID);

/*
group *create_group(int curr_ID):
================================
The group *create_group(int curr_ID) function is designed to create a new group node within the social networking program.
It prompts the user to input information such as the group's name and dynamically allocates memory for the group node.
Additionally, the function allows the user to add members and businesses to the group
*/
group *create_group(int curr_ID);

/*
business *create_business(int curr_ID):
=======================================
The business *create_business(int curr_ID) function is designed to create a new business node within the social networking program.
It prompts the user to input essential information such as the business's location.
Additionally, the function allows the user to add owners and customers to the business
*/
business *create_business(int curr_ID);

/*
organisation *create_organisation(int curr_ID):
===============================================
The organisation *create_organisation(int curr_ID) function is designed to create a new organisation node within the social networking program.
It prompts the user to input essential information such as the organisation's location.
Additionally, the function allows the user to add owners and customers to the business
*/
organisation *create_organisation(int curr_ID);

/*
The getDate function serves as a utility in the social networking program, enabling the user to input a date in the DD-MM-YYYY format. 
It dynamically allocates memory for a date structure, prompts the user for the required date components, and stores the information in the allocated structure. 
*/
date *getDate();

/*
The compDate function compares two date structures for equality. 
It takes two pointers to date structures (d1 and d2) as input parameters 
Returns 1 if the dates are equal and 0 otherwise. 
This function is useful for checking whether two dates match,
*/
int compDate(date *d1, date *d2);

/*
The search function is the entry point for the search functionality in the social networking program. 
It prompts users with a menu that provides options to search nodes.
Search options are based on various criteria, including ID, name, type, and birthday.
*/
void search();

/*
The searchbyID function is designed to search for a node within the social networking program based on its unique identifier (ID). 
Users can input an ID, and the function returns a pointer to the corresponding node if found. 
If no node with the specified ID exists, the function returns NULL.
*/
NODE *searchbyID(int ID);

/*
The searchbyName function is responsible for searching nodes within the social networking program based on the provided name. Users can input a name. 
The function will print information about nodes that match the specified name.
*/
void searchbyName(char *s);

/*
The searchbyType function facilitates searching for nodes within the social networking program based on the specified type. 
Users can input a numeric type (1 for Individual, 2 for Group, 3 for Business, 4 for Organisation). 
The function will display information about nodes that match the specified type.
*/
void searchbyType(int type);

/*
The searchbyBirthday function specializes in searching for individual nodes within the social networking program based on the specified birthday.
Users can input a date, and the function will display information about individual nodes with that birthday.
This makes use of the compDate function.
*/
void searchbyBirthday(date *birthday);

/*
The printMenu function is responsible for displaying the main menu of the social networking program. 
It presents users with a set of options, allowing them to interact with different features and functionalities within the program.
*/
void printMenu();

/*
The print_individual function is designed to display information related to an individual node within the social networking program. 
A pointer to an individual node (P), and the function will print details such as the individual's birthday.
*/
void print_individual(individual *);

/*
The void print_group(group *P) function is designed to print essential information about a node of type "Group" in the social networking program.
It begins by displaying the member IDs associated with the group
It is followed by displaying the business IDs linked to the group.
*/
void print_group(group *);

/*
The void print_business(business *P) function serves the purpose of printing key details of a node with the type "Business" in the social networking program.
The output includes the location coordinates (X, Y)
It begins by displaying the owner IDs associated with the Business
It is followed by displaying the customer IDs linked to the Business.
*/
void print_business(business *);

/*
The void print_organisation(organisation *P) function is designed to display key information about a node with the type "Organisation" in the social networking program. 
It prints the location coordinates (X, Y) of the organization.
It lists the member IDs associated with it.
*/
void print_organisation(organisation *);

/*

The void print_NODE(NODE *N) function serves as a comprehensive print function for displaying common information about a generic node. 
It prints the node's unique identifier (ID), name, creation date, and type. 
Depending on the type of the node (Individual, Group, Business, or Organisation), it dynamically casts the pointer to the appropriate type.
It invokes specific print functions for each type, providing a detailed summary of the node's attributes. 
For example, if the node is of type "Individual," it calls the print_individual function
*/
void print_NODE(NODE *);

/*
The void Print1HopNodes(int ID) function is designed to print information about nodes directly linked to the specified node with the given ID in a social networking program. 
It traverses the linked nodes (1-hop neighbors) of the target node (stored in the head attribute of NODE)
It prints their details using the print_NODE function.
*/
void Print1HopNodes(int ID);

/*
The void printAllNodes() function in the social networking program is responsible for printing information about all nodes present in the network. 
It iterates through the linked list of nodes, invoking the print_NODE function for each node.
*/
void printAllNodes();


/*
IDNode *insertListNode(IDNode *head, int ID):
============================================
Inserts a new node with the given ID at the beginning of the linked list.
If the ID already exists in the list, it does not insert a duplicate.
Returns the head of the updated linked list.
*/
IDNode *insertListNode(IDNode *head, int ID);

/*
IDNode *deleteListNode(IDNode *head, int ID):
============================================
The IDNode *deleteListNode(IDNode *head, int ID) function serves the purpose of deleting a node from a linked list of IDs associated with a particular node. 
It takes the head of the linked list and the ID to be deleted as parameters.
The function iterates through the list, and if the specified ID is found, it removes the corresponding node from the list. 
The modified list is then returned. 
If the head is NULL or the specified ID is not present in the list, the original list is returned unchanged.
*/
IDNode *deleteListNode(IDNode *head, int ID);


/*
ContentNode *addContent(ContentNode *head, char *content):
=========================================================
Inserts a new node with some content in linked list of contents
Returns the head of the updated linked list.
*/
ContentNode *addContent(ContentNode *head, char *content);



/*
ContentNode *searchContent(ContentNode *head, char *content):
=========================================================
Does substring matching of search query with every content posted in linked list
Returns the content node if match found.
*/
ContentNode *searchContent(ContentNode *head, char *content);


void createPost();

/*
void searchAllContent():
=======================
Takes input of search query
Calls searchContent for every node
*/
void searchAllContent();

/*
Takes an integer ID as an argument representing the ID of the individual node.
Finds all individuals within all groups and organisations
Prints all content posted by individuals linked to the specified node.
Traverses the linked list of nodes connected to the specified individual node.
The function relies on other utility functions, such as searchbyID, insertListNode, and printAllContent, to perform specific tasks.
*/
void seeLinkedContent(int ID);

/*
The printAllContent function shows all content posted by a node identified by its unique ID. 
If a node with given ID is found, the function prints a formatted header indicating the node's ID and name. 
It then iterates through the linked list of content nodes associated with the specified node.
The function includes checks to handle cases where no content has been posted, providing a specific message.
*/
void printAllContent(int ID);

/*
The `insertNODE` function takes the current head of the linked list
It prompts the user to create a new node by invoking the `create` function.
If the creation is successful, the new node becomes the head of the list
The updated head is returned.
*/
NODE *insertNODE(NODE *head);

/*
The `deleteNODE` function takes the current head of the linked list
It prompts the user to input the ID of the node to be deleted.
If the node with the specified ID is found, it is removed from the list,
The memory allocated for the node is freed using clear Node function 
The updated head is returned.
*/
NODE *deleteNODE(NODE *head, int ID);

/*
The `clearNode` function takes a node pointer as input
It removes all linked content, members, and connections associated with the node.
The function also handles the removal of this node from the linked lists
Finally, memory allocated for the node and its components is freed
*/
void clearNode(NODE *N);

