/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, Perl, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
    #include <stdio.h>
    #include<stdlib.h>
    #include<conio.h>
    
    typedef int bool;
    #define true 1
    #define false 0
    
    #define RED   "\x1B[31m"
    #define GREEN   "\x1B[32m"
    #define CYAN   "\x1B[36m"
    #define YELLOW   "\x1B[33m"
    #define BLUE   "\x1B[34m"
    #define MAG   "\x1B[35m"
    #define RESET "\x1B[0m"
    
    #define NUMBER_OF_STOPS 25.0f // The bus goes through the 25 stops as a single way.
    #define PRICE_PER_STOP 0.25f // The price per each stop costs 0.25 pence.
    #define AGE_UNDER_TEN 1.0f
    #define AGE_UNDER_SIXTEN 0.50f
    #define AGE_OVER_SIXTY 0.75f
    #define AGE_STUDENT 0.20f
    #define AGE_OTHER_ADULT 0.0f
    
typedef struct Ticket
    {
        bool returnTicket;
        float price;
    }Ticket;
 
typedef struct Person 
    {
        int age;
        bool student;
        Ticket* ticket;
        struct Person* next;
    }Person;
    
int getNumberOfTickets();
int getAge();
bool getReturnTicket();
bool getStudentStatus();
Person* createPerson(int age, bool studentStatus, Ticket* ticket);
Ticket* createTicket(bool returnTicket);
void insert(Person** head, Person* person);
void displayPerson(Person* head);
void calculatePrice(Person* head);
float calculateDiscount(int age, float price, bool student);
float calculateTotalPrice(Person* head);
void displayTotal(float totalPrice);

int main()
{
// Number of tickets = number of persons from user input
    int numberOfTickets = getNumberOfTickets();
    
// For Loop = to create person 
    Person* head = NULL;
    int i;
    for(i=0; i < numberOfTickets; i++)
    {
        // Person age 
        int age = getAge();
        // student yes/no
        bool studentStatus = getStudentStatus();
        // ticket return yes/no
        bool returnTicket = getReturnTicket();
        // create ticket
        Ticket* ticket = createTicket(returnTicket);
        // create person
        Person* person = createPerson(age, studentStatus, ticket);
        insert(&head, person);
    }

// Calculate ticket price for each ticket
calculatePrice(head);

// Calculate total price for all tickets
displayPerson(head);

float totalPrice = calculateTotalPrice(head);

displayTotal(totalPrice);

}

int getNumberOfTickets()
    {
        printf(MAG"\t Welcome to bus ticket sale\n"RESET);
        printf(MAG"\t ==========================\n\n"RESET);
        int number;
        printf(" (HINT: Maximum 10 tickets can be bought)\n");
        printf(" Please, enter how many tickets would you like to buy: ");
        scanf("%d", &number);
        printf(YELLOW" -------------------------------------------------------\n"RESET);
        
        
            while(number <1 || number >10)
            {
                printf(" Maximum ticket should be more than 1 and less than 10, please try again: ");
                scanf("%d", &number);  
            }
        return number;
    }
int counter = 1;

int getAge()
    {
        int age;
        printf(" (Ticket for %i. passenger.)\n", counter++);
        printf(" Please, enter your age in years: ");
        scanf("%d", &age);
        return age;
    }
    
bool getStudentStatus()
    {
        char answer;
        printf(" Are you student? Enter Y or N: ");
        scanf(" %c", &answer);
        
        while (answer != 'Y' && answer != 'y' && answer != 'N' && answer != 'n')
        {
            printf(RED" Your answer has not been recognised, please try it again. "RESET"Y or N: ");
            scanf(" %c", &answer);
        }
        
        if(answer == 'Y'|| answer == 'y')
        {
            return true;
        }    

    return false;
    }
bool getReturnTicket(bool returnTicket)
    {
        char answer;
        printf(" Would you like to buy a return ticket? Enter Y or N: ");
        scanf(" %c", &answer);
        printf(YELLOW" -------------------------------------------------------\n"RESET);
        
        while (answer != 'Y' && answer != 'y' && answer != 'N' && answer != 'n')
        {
            printf(" Your answer has not been recognised, please try it again. Y or N: ");
            scanf(" %c", &answer);
        }
        
        if(answer == 'Y'|| answer == 'y')
        {
            
            return true;
        }
        

    return false;  
    } 
    
Ticket* createTicket(bool returnTicket)
    {
        Ticket* newTicket = (Ticket*)malloc(sizeof(Ticket));
        if(newTicket == NULL)
        {
            printf(" Error creating a new Ticket.\n");
            exit(0);
        }
        newTicket->returnTicket = returnTicket;
        newTicket->price = 0.0f;
        return newTicket;
        }
    
Person* createPerson(int age, bool studentStatus, Ticket* ticket)
    {
        Person* newPerson = (Person*)malloc(sizeof(Person));
        if(newPerson == NULL)
        {
            printf(" Error creating a new Person.\n");
            exit(0);
        }
        newPerson->age = age;
        newPerson->student = studentStatus;
        newPerson->ticket = ticket;
        newPerson->next = NULL;
        return newPerson;
    }
    
void insert(Person** head, Person* person)
    {
    if (*head == NULL)
    {
       *head = person;
    } 
    else 
    {
        Person* temp = *head;
        while(temp->next != NULL)
        {   
            temp = temp->next;
        }
            
        temp->next = person;
        }   
    }
    
void displayPerson(Person* head)
    {
        printf(RED"\n\t .....Ticket info.....\n"RESET);
        printf(BLUE"\t------------------------\n"RESET);
        int counter = 1;
        while(head != NULL)
        {
            
            printf("\tPassenger number: %i\n", counter++);
            printf("\tPassenger age: %i\n", head->age);
            printf("\tTicket price is: £%.2f\n", head->ticket->price);
            printf(BLUE"\t------------------------\n"RESET);
            head = head->next;  
        }
    }

void calculatePrice(Person* head)
{
    while(head != NULL)
    {
        float price = NUMBER_OF_STOPS * PRICE_PER_STOP;
        
        if(head->ticket->returnTicket == true)
        {
            price = price * 2;
        }
        head->ticket->price = calculateDiscount(head->age, price, head->student);
        head = head->next;  
    }
}
    
// Calculate discount
float calculateDiscount(int age, float price, bool student)
{
double count;

 if(age <10)
 {
    count = price - (price * AGE_UNDER_TEN);
 }
 else if(age >=10 && age <16)
 {
    count = price - (price * AGE_UNDER_SIXTEN);
 }
  else if(age >60)
 {
    count = price - (price * AGE_OVER_SIXTY);
 }
 else if(age >=16 && age <=60)
 {
     if (student == true)
     {
        count = price - (price * AGE_STUDENT);
     }
    else
    {
      count = price - (price * AGE_OTHER_ADULT);  
    }
 }
  return count;  
}

float calculateTotalPrice(Person* head)
    {
        double sum;
        while(head != NULL)
        {
            sum += head->ticket->price;
            head = head->next;  
        }
        return sum;
    }
    
void displayTotal(float totalPrice)
{
    printf("\tThe price of ticket in total is: "GREEN"£%.2f\n", totalPrice, RESET);
    printf("\t=======================================");
}





