#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* seat node in singly linked list */
typedef struct seat
{
    int seat_no;
    int booked;
    struct seat *next;
} seat;

/* event node in doubly linked list */
typedef struct event
{
    int event_id;
    char name[50];
    int totalseats;
    seat *seats;
    struct event *next;
    struct event *prev;
} event;

event *eventhead = NULL;

/* creates a linked list of seats numbered from 1 to n */
seat *create_seats(int n)
{
    seat *head = NULL, *temp = NULL;

    for (int i = 1; i <= n; i++)
    {
        seat *newseat = (seat *)malloc(sizeof(seat));
        newseat->seat_no = i;
        newseat->booked = 0;
        newseat->next = NULL;

        if (head == NULL)
        {
            head = newseat;
            temp = newseat;
        }
        else
        {
            temp->next = newseat;
            temp = newseat;
        }
    }
    return head;
}

/* adds a new event to the doubly linked list */
void add_event()
{
    event *newevent = (event *)malloc(sizeof(event));

    printf("enter event id: ");
    scanf("%d", &newevent->event_id);

    printf("enter event name: ");
    scanf(" %[^\n]", newevent->name);

    printf("enter total seats: ");
    scanf("%d", &newevent->totalseats);

    newevent->seats = create_seats(newevent->totalseats);
    newevent->next = eventhead;
    newevent->prev = NULL;

    if (eventhead != NULL)
        eventhead->prev = newevent;

    eventhead = newevent;

    printf("event added successfully!\n");
}

/* displays all events stored in the system */
void view_events()
{
    event *temp = eventhead;

    if (!temp)
    {
        printf("no events available.\n");
        return;
    }

    while (temp)
    {
        printf("id: %d | name: %s | seats: %d\n",
               temp->event_id, temp->name, temp->totalseats);
        temp = temp->next;
    }
}

/* searches for an event by id */
event *find_event(int id)
{
    event *temp = eventhead;
    while (temp)
    {
        if (temp->event_id == id)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

/* shows seat availability for an event */
void view_seats()
{
    int eid;
    printf("enter event id: ");
    scanf("%d", &eid);

    event *ev = find_event(eid);
    if (!ev)
    {
        printf("event not found.\n");
        return;
    }

    seat *s = ev->seats;
    while (s)
    {
        printf("seat %d: %s\n",
               s->seat_no,
               s->booked ? "booked" : "free");
        s = s->next;
    }
}

/* books a seat for an event */
void book_ticket()
{
    int eid, seatno, seats;

    printf("enter event id: ");
    scanf("%d", &eid);

    event *ev = find_event(eid);
    if (!ev)
    {
        printf("event not found.\n");
        return;
    }

    printf("Enter the number of seats you wanna book\n");
    scanf("%d", &seats);
    if (seats > ev->totalseats)
    {
        printf("No Tickets Available\n");
        return;
    }
    for (int i = 0; i < seats; i++)
    {
        printf("Enter seat number\n");
        scanf("%d", &seatno);

        seat *s = ev->seats;
        while (s)
        {
            if (s->seat_no == seatno)
                break;
            s = s->next;
        }

        if (!s)
        {
            printf("invalid seat.\n");
            return;
        }

        if (s->booked == 1)
        {
            printf("seat already booked.\n");
        }
        else
        {
            s->booked = 1;
            printf("seat %d booked successfully!\n", seatno);
        }
    }
}

/* frees all seat nodes of an event */
void free_seats(seat *head)
{
    seat *temp;
    while (head)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

/* frees all events and their seat lists */
void free_all()
{
    event *temp;

    while (eventhead)
    {
        temp = eventhead;
        eventhead = eventhead->next;

        free_seats(temp->seats); /* free all seats */
        free(temp);              /* free event node */
    }
}

/* menu driven program */
int main()
{
    int choice;

    while (1)
    {
        printf("\n--- ticket booking system ---\n");
        printf("1. add event\n");
        printf("2. view events\n");
        printf("3. view seats\n");
        printf("4. book ticket\n");
        printf("5. exit\n");

        printf("enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            add_event();
            break;
        case 2:
            view_events();
            break;
        case 3:
            view_seats();
            break;
        case 4:
            book_ticket();
            break;
        case 5:
            printf("exiting...\n");
            free_all();
            return 0;
        default:
            printf("invalid choice.\n");
        }
    }
}
