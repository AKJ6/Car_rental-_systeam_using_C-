#include <iostream>
#include <cstring>

using namespace std;

typedef struct customers
{
    int Aadhaar_num;
    char First_Name[100];
    char Last_Name[100];
    char Car_Name[100];
    struct customers *next;
} CUS;

typedef struct car_rental
{
    char Car_Name[100];
    float fare; // Added fare attribute
    struct car_rental *next;
} CR;

typedef struct first
{
    CR *top;
} First;

typedef struct first_rented
{
    CUS *top;
} CU;

First Add_cars(First &Head)
{
    CR *new_node = new CR;
    cout << "Enter the name of the car\n";
    cin >> new_node->Car_Name;
    cout << "Enter the fare for the car\n";
    cin >> new_node->fare;
    new_node->next = Head.top;
    Head.top = new_node;
    return Head;
}

First Delete(First &Head, char car[100])
{
    CR *aux = Head.top;
    CR *temp = NULL;

    if (strcmp(aux->Car_Name, car) == 0)
    {
        Head.top = aux->next;
        delete aux;
        return Head;
    }

    temp = aux;
    aux = aux->next;
    while (aux != NULL)
    {
        if (strcmp(aux->Car_Name, car) == 0)
        {
            temp->next = aux->next;
            delete aux;
            break;
        }
        temp = aux;
        aux = aux->next;
    }
    return Head;
}

void Display_available(First Head)
{
    CR *aux = Head.top;
    if (Head.top == NULL)
    {
        cout << "There are no cars available\n";
    }
    else
    {
        while (aux != NULL)
        {
            cout << aux->Car_Name << " - Rs" << aux->fare << "\n";
            cout << "--------------------------------------------------------------\n";
            aux = aux->next;
        }
    }
}

CU Rent_Car(CU &first, First head)
{
    CUS *new_child = new CUS;
    cout << "Please Enter your first name\n";
    cin >> new_child->First_Name;
    cout << "Please Enter your last name\n";
    cin >> new_child->Last_Name;
    cout << "Please enter your Aadhaar number\n";
    cin >> new_child->Aadhaar_num;
    cout << "Please select the car\n";
    Display_available(head);

    int count = 1;
    while (count)
    {
        CR *temp = head.top;
        cin >> new_child->Car_Name;
        while (temp != NULL)
        {
            if (strcmp(new_child->Car_Name, temp->Car_Name) == 0)
            {
                --count;
                head = Delete(head, new_child->Car_Name);
                cout << "Car rented: " << new_child->Car_Name << "\n";
                cout << "Fare: Rs" << temp->fare << "\n";
                break;
            }
            temp = temp->next;
        }

        if (count == 0)
        {
            cout << "Thank you for choosing us as your go-to provider\n";
        }
        else
        {
            cout << "Sorry but the car isn't available\n";
        }
    }
    if (first.top == NULL)
    {
        first.top = new_child;
        new_child->next = NULL;
    }
    else
    {
        new_child->next = first.top;
        first.top = new_child;
    }
    return first;
}

void displayCustomers(CU first)
{
    if (first.top == NULL)
    {
        cout << "There are no customers\n";
    }
    else
    {
        CUS *aux = first.top;
        while (aux != NULL)
        {
            cout << "First name of the customer: " << aux->First_Name << "\n";
            cout << "Last name of the customer: " << aux->Last_Name << "\n";
            cout << "Aadhaar number of the customer: " << aux->Aadhaar_num << "\n";
            cout << "Car rented: " << aux->Car_Name << "\n";
             cout << "--------------------------------------------------------------\n";
            aux = aux->next;
        }
    }
}

void search_customers(CU first)
{
    int count = 0;
    int search;
    cout << "Enter the Aadhaar number\n";
    cin >> search;
    if (first.top == NULL)
    {
        cout << "There are no customers\n";
    }
    else
    {
        CUS *aux = first.top;
        while (aux != NULL)
        {
            if (aux->Aadhaar_num == search)
            {
                count++;
                cout << "Customer details\n";
                cout << "First Name: " << aux->First_Name << "\n";
                cout << "Last Name: " << aux->Last_Name << "\n";
                cout << "Aadhaar number: " << aux->Aadhaar_num << "\n";
                cout << "Car rented: " << aux->Car_Name << "\n";
            }
            aux = aux->next;
        }
        if (count == 0)
        {
            cout << "Customer not found\n";
        }
    }
}

int main()
{
    int ch, n;
    First head;
    CU first;
    first.top = NULL;
    head.top = NULL;

    while (1)
    {
        cout << "1:Add cars\n2:Display the available\n3:Rent\n4:Display customer detail\n5:Search customer\n6:exit\n";
        cin >> ch;

        switch (ch)
        {
        case 1:
            cout << "Enter the number of cars you want to add to\n";
            cin >> n;
            while (n)
            {
                head = Add_cars(head);
                --n;
            }
            break;

        case 2:
            Display_available(head);
            break;

        case 3:
            if (head.top == NULL)
            {
                cout << "There are no cars available\n";
            }
            else
            {
                first = Rent_Car(first, head);
            }
            break;

        case 4:
            displayCustomers(first);
            break;

        case 5:
            search_customers(first);
            break;

        case 6:
            exit(0);
            break;
        }

        if (ch < 1 || ch > 6)
        {
            cout << "Invalid choice. Please enter a valid option.\n";
        }
    }

    return 0;
}