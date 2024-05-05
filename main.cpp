#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure definitions
typedef struct {
    int book_id;
    char name[50];
    char author[50];
    int restriction_age;
    float weekly_price;
    int rented;
} Book;

typedef struct {
    int customer_id;
    char name[50];
    char surname[50];
    int age;
    float wallet;
} customer;

typedef struct {
    int rental_id;
    int customer_id;
    int book_id;
    int date_of_rental;
    int week;
} Rented;

// Function prototypes
void create_customer();
void deposit_money();
void add_book();
void rent_book();
void deliver_book();
void burn_book();
void update_customer();
void update_book();
void current_rentals();
void list_customers();
void list_books();

// Global variables
customer customers[100]; // 100 is set as the number of max customers, size can be increased this is just for runnning
Book books[100]; // 100 is set as the number of max books, size can be increased this is just for runnning
Rented rented_books[100]; // 100 is set as the number of max rentals, size can be increased this is just for runnning
// helps to keep check on the numbers of each , while also helps in iteration
int noOfCustomers = 0;
int no_Of_books = 0;
int numberofrentals = 0;



int main() {
    // Load data from files
    FILE *mz;

    //  EOF  REFERS TO END OF FILE . IT CHECKS IF TEH END OF FILE BEING OPENED IS REACHED

    mz = fopen("customers.txt", "r"); // this is used to open the customer file 
    if (mz!= NULL) {
        while (fscanf(mz, "%d %s %s %d %f", &customers[noOfCustomers].customer_id, customers[noOfCustomers].name, customers[noOfCustomers].surname, &customers[noOfCustomers].age, &customers[noOfCustomers].wallet)!= EOF) {
            noOfCustomers++;
        }
        fclose(mz);
    }

    mz = fopen("books.txt", "r");// this is used to open the books file 
    if (mz!= NULL) {
        while (fscanf(mz, "%d %s %s %d %f %d", &books[no_Of_books].book_id, books[no_Of_books].name, books[no_Of_books].author, &books[no_Of_books].restriction_age, &books[no_Of_books].weekly_price, &books[no_Of_books].rented)!= EOF) {
            no_Of_books++;
        }
        fclose(mz);
    }

    mz = fopen("rented.txt", "r");// this is used to open the rental file 
    if (mz!= NULL) {
        while (fscanf(mz, "%d %d %d %d %d", &rented_books[numberofrentals].rental_id, &rented_books[numberofrentals].customer_id, &rented_books[numberofrentals].book_id, &rented_books[numberofrentals].date_of_rental, &rented_books[numberofrentals].week)!= EOF) {
            numberofrentals++;
        }
        fclose(mz);
    }

  // Main menu
int main_option;
while (1) {
     
    printf("***Library Booking System***\n");
    printf("1. Create New customer\n");
    printf("2. Deposit Money to the customer\n");
    printf("3. Add New Book\n");
    printf("4. Rent a Book\n");
    printf("5. Deliver a Book\n");
    printf("6. Burn a Book\n");
    printf("7. Update customer Information\n");
    printf("8. Update Book Information\n");
    printf("9. List of Customers Who Rent a Book\n");
    printf("10. List of Customers\n");
    printf("11. List of Books\n");
    printf("Enter your main_option: ");
    scanf("%d", &main_option);


// USING SWITCH CASES TO USE THE SPECIFIED FUNCTION
    switch (main_option) {
        case 1:
            create_customer();
            break;
        case 2:
            deposit_money();
            break;
    
        case 3:
                add_book();
                break;
        case 4:
                rent_book();
                break;
        case 5:
                deliver_book();
                break;
        case 6:
                burn_book();
                break;
        case 7:
                update_customer();
                break;
        case 8:
                update_book();
                break;
        case 9:
                current_rentals();
                break;
        case 10:
                list_customers();
                break;
        case 11:
                list_books();
                break;
        default:
                printf("Invalid mainoption. Please try again.\n");
        }
    }

    return 0;
}

void create_customer() {
    customer new_customer;          // CREATING AN OBJECT OF THE STRUCTURE
    printf("Enter customer name: ");
    scanf("%s", new_customer.name);
    printf("Enter customer surname: ");
    scanf("%s", new_customer.surname);
    printf("Enter customer age: ");
    scanf("%d", &new_customer.age);
    new_customer.wallet = 0;
    new_customer.customer_id = noOfCustomers + 1;

    // Check if customer already exists
    int i;
    for (i = 0; i < noOfCustomers; i++) {
        if (strcmp(customers[i].name, new_customer.name) == 0 && strcmp(customers[i].surname, new_customer.surname) == 0) {
            printf("customer already exists.\n");
            return;
        }
    }

    // Add customer to array
    customers[noOfCustomers] = new_customer;
    noOfCustomers++;

    // Save to file
    FILE *mz;
    mz = fopen("customers.txt", "a");
    fprintf(mz, "%d %s %s %d %f\n", new_customer.customer_id, new_customer.name, new_customer.surname, new_customer.age, new_customer.wallet);
    fclose(mz);
// FPRINTF BASICALLY EDITS THE FILE
    printf("customer created successfully.\n");
}

void deposit_money() {
    int customer_id;
    printf("Enter customer ID: ");
    scanf("%d", &customer_id);

    int i;
    for (i = 0; i < noOfCustomers; i++) {
        if (customers[i].customer_id == customer_id) {
            float amount;
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            customers[i].wallet += amount;

            // Save to file
            FILE *mz;
            mz = fopen("customers.txt", "w");
            for (int j = 0; j < noOfCustomers; j++) {
                fprintf(mz, "%d %s %s %d %f\n", customers[j].customer_id, customers[j].name, customers[j].surname, customers[j].age, customers[j].wallet);
            }
            fclose(mz);

            printf("Deposit successful.\n");
            return;
        }
    }

    printf("customer not found.\n");
}

void add_book() {
    Book new_book;       // CREATING AN OBJECT OF THE STRUCTURE
    printf("Enter book name: ");
    scanf("%s", new_book.name);
    printf("Enter author name: ");
    scanf("%s", new_book.author);
    printf("Enter age limit: ");
    scanf("%d", &new_book.restriction_age);
    printf("Enter price per week: ");
    scanf("%f", &new_book.weekly_price);
    new_book.book_id = no_Of_books + 1;
    new_book.rented = 0;

    // Check if book already exists
    int i;
    for (i = 0; i < no_Of_books; i++) {
        if (strcmp(books[i].name, new_book.name) == 0 && strcmp(books[i].author, new_book.author) == 0) {
            printf("Book already exists.\n");
            return;
        }
    }

    // Add book to array
    books[no_Of_books] = new_book;
    no_Of_books++;

    // Save to file
    FILE *mz;
    mz = fopen("books.txt", "a");
    fprintf(mz, "%d %s %s %d %f %d\n", new_book.book_id, new_book.name, new_book.author, new_book.restriction_age, new_book.weekly_price, new_book.rented);
    fclose(mz);

    printf("Book added successfully.\n");
}

void rent_book() {
    int customer_id, book_id;
    printf("Enter customer ID: ");
    scanf("%d", &customer_id);
    printf("Enter book ID: ");
    scanf("%d", &book_id);
    int i, j;
    for (i = 0; i < noOfCustomers; i++) {
        if (customers[i].customer_id == customer_id) {
            for (j = 0; j < no_Of_books; j++) {
                if (books[j].book_id == book_id) {
                    if (books[j].rented == 1) {
                        printf("Book already rented.\n");
                        return;
                    }
                    if (customers[i].wallet < books[j].weekly_price) {
                        printf("Not enough balance in wallet.\n");
                        return;
                    }
                    customers[i].wallet -= books[j].weekly_price;
                    books[j].rented = 1;

                    // Save to file
                    FILE *mz;
                    mz = fopen("customers.txt", "w");
                    for (int k = 0; k < noOfCustomers; k++) {
                        fprintf(mz, "%d %s %s %d %f\n", customers[k].customer_id, customers[k].name, customers[k].surname, customers[k].age, customers[k].wallet);
                    }
                    fclose(mz);

                    mz = fopen("books.txt", "w");
                    for (int k = 0; k < no_Of_books; k++) {
                        fprintf(mz, "%d %s %s %d %f %d\n", books[k].book_id, books[k].name, books[k].author, books[k].restriction_age, books[k].weekly_price, books[k].rented);
                    }
                    fclose(mz);

                    printf("Book rented successfully.\n");
                    return;
                }
            }
            printf("Book not found.\n");
            return;
        }
    }
    printf("customer not found.\n");
}

void return_a_book() {
    int book_id;
    printf("Enter book ID: ");
    scanf("%d", &book_id);
    int i;
    for (i = 0; i < no_Of_books; i++) {
        if (books[i].book_id == book_id) {
            if (books[i].rented == 0) {
                printf("Book is not rented.\n");
                return;
            }
            books[i].rented = 0;

            // Save to file
            FILE *mz;
            mz = fopen("books.txt", "w");
            for (int j = 0; j < no_Of_books; j++) {
                fprintf(mz, "%d %s %s %d %f %d\n", books[j].book_id, books[j].name, books[j].author, books[j].restriction_age, books[j].weekly_price, books[j].rented);
            }
            fclose(mz);

            printf("Book returned successfully.\n");
            return;
        }
    }
    printf("Book not found.\n");
}

void show_customer_details() {
    int customer_id;
    printf("Enter customer ID: ");
    scanf("%d", &customer_id);
    int i;
    for (i = 0; i < noOfCustomers; i++) {
        if (customers[i].customer_id == customer_id) {
            printf("Name: %s\n", customers[i].name);
            printf("Surname: %s\n", customers[i].surname);
            printf("Age: %d\n", customers[i].age);
            printf("Wallet: %f\n", customers[i].wallet);
            return;
        }
    }
    printf("customer not found.\n");
}

void show_book_details() {
    int book_id;
    printf("Enter book ID: ");
    scanf("%d", &book_id);
    int i;
    for (i = 0; i < no_Of_books; i++) {
        if (books[i].book_id == book_id) {
            printf("Name: %s\n", books[i].name);
            printf("Author: %s\n", books[i].author);
            printf("Age limit: %d\n", books[i].restriction_age);
            printf("Price per week: %f\n", books[i].weekly_price);
            if (books[i].rented == 1) {
                printf("Rented: Yes\n");
            } else {
                printf("Rented: No\n");
            }
            return;
        }
    }
    printf("Book not found.\n");
}

void list_customers() {
    int i;
    for (i = 0; i < noOfCustomers; i++) {
        printf("%d. %s %s (%d)\n", customers[i].customer_id, customers[i].name, customers[i].surname, customers[i].age);
    }
}

void list_books() {
    int i;
    for (i = 0; i < no_Of_books; i++) {
        printf("%d. %s by %s (Age limit: %d, Price per week: %f, Rented: %s)\n", books[i].book_id, books[i].name, books[i].author, books[i].restriction_age, books[i].weekly_price, books[i].rented == 1 ? "Yes" : "No");
    }
}

void list_customers_who_rented_books() {
    int i;
    for (i = 0; i < noOfCustomers; i++) {
        if (customers[i].wallet < 0) {
            printf("%d. %s %s (%d)\n", customers[i].customer_id, customers[i].name, customers[i].surname, customers[i].age);
        }
    }
}

void update_customer() {
    int customer_id;
    printf("Enter customer ID: ");
    scanf("%d", &customer_id);
    int i;
    for (i = 0; i < noOfCustomers; i++) {
        if (customers[i].customer_id == customer_id) {
            printf("Enter new name: ");
            scanf("%s", customers[i].name);
            printf("Enter new surname: ");
            scanf("%s", customers[i].surname);
            printf("Enter new age: ");
            scanf("%d", &customers[i].age);

            // Save to file
            FILE *mz;
            mz = fopen("customers.txt", "w");
            for (int j = 0; j < noOfCustomers; j++) {
                fprintf(mz, "%d %s %s %d %f\n", customers[j].customer_id, customers[j].name, customers[j].surname, customers[j].age, customers[j].wallet);
            }
            fclose(mz);

            printf("customer information updated successfully.\n");
            return;
        }
    }
    printf("customer not found.\n");
}

void update_book() {
    int book_id;
    printf("Enter book ID: ");
    scanf("%d", &book_id);
    int i;
    for (i = 0; i < no_Of_books; i++) {
        if (books[i].book_id == book_id) {
            printf("Enter new name: ");
            scanf("%s", books[i].name);
            printf("Enter new author: ");
            scanf("%s", books[i].author);
            printf("Enter new age limit: ");
            scanf("%d", &books[i].restriction_age);
            printf("Enter new price per week: ");
            scanf("%f", &books[i].weekly_price);

            // Save to file
            FILE *mz;
            mz = fopen("books.txt", "w");
            for (int j = 0; j < no_Of_books; j++) {
                fprintf(mz, "%d %s %s %d %f %d\n", books[j].book_id, books[j].name, books[j].author, books[j].restriction_age, books[j].weekly_price, books[j].rented);
            }
            fclose(mz);

            printf("Book information updated successfully.\n");
            return;
        }
    }
    printf("Book not found.\n");
}
void deliver_book() {
    int customer_id, book_id, returned_week;
    printf("Enter customer ID: ");
    scanf("%d", &customer_id);
    printf("Enter book ID: ");
    scanf("%d", &book_id);
    printf("Enter week of return: ");
    scanf("%d", &returned_week);

    // Find the corresponding rental
    int i, rental_index = -1;
    for (i = 0; i < numberofrentals; i++) {
        if (rented_books[i].customer_id == customer_id && rented_books[i].book_id == book_id) {
            rental_index = i;
            break;
        }
    }

    if (rental_index == -1) {
        printf("Rental record not found.\n");
        return;
    }

    Rented rental = rented_books[rental_index];
    if (returned_week < rental.week) {
        int weeks_early = rental.week - returned_week;
        float refund_amount = weeks_early * books[book_id - 1].weekly_price;
        customers[customer_id - 1].wallet += refund_amount;
        printf("Book returned early. Refund amount: %.2f TL added to wallet.\n", refund_amount);
    }

    // Mark the book as not rented
    books[book_id - 1].rented = 0;

    // Update the rented_books record by removing or marking this entry
    // Simple approach for this context: set week to 0 (indicates no active rental)
    rented_books[rental_index].week = 0;

    // Update files
    FILE *mz;
    mz = fopen("customers.txt", "w");
    for (i = 0; i < noOfCustomers; i++) {
        fprintf(mz, "%d %s %s %d %f\n", customers[i].customer_id, customers[i].name, customers[i].surname, customers[i].age, customers[i].wallet);
    }
    fclose(mz);

    mz = fopen("books.txt", "w");
    for (i = 0; i < no_Of_books; i++) {
        fprintf(mz, "%d %s %s %d %f %d\n", books[i].book_id, books[i].name, books[i].author, books[i].restriction_age, books[i].weekly_price, books[i].rented);
    }
    fclose(mz);

    mz = fopen("rented.txt", "w");
    for (i = 0; i < numberofrentals; i++) {
        // We write only active rentals back to file
        if (rented_books[i].week != 0) {
            fprintf(mz, "%d %d %d %d %d\n", rented_books[i].rental_id, rented_books[i].customer_id, rented_books[i].book_id, rented_books[i].date_of_rental, rented_books[i].week);
        }
    }
    fclose(mz);

    printf("Book delivered successfully.\n");
}



void burn_book() {
    int book_id;
    printf("Enter book ID: ");
    scanf("%d", &book_id);
    int i;
    for (i = 0; i < no_Of_books; i++) {
        if (books[i].book_id == book_id) {
            if (books[i].rented == 1) {
                printf("Cannot burn a rented book.\n");
                return;
            }
            books[i].book_id = -1;

            // Save to file
            FILE *mz;
            mz = fopen("books.txt", "w");
            for (int j = 0; j < no_Of_books; j++) {
                if (books[j].book_id != -1) {
                    fprintf(mz, "%d %s %s %d %f %d\n", books[j].book_id, books[j].name, books[j].author, books[j].restriction_age, books[j].weekly_price, books[j].rented);
                }
            }
            fclose(mz);

            printf("Book burned successfully.\n");
            return;
        }
    }
    printf("Book not found.\n");
}

void current_rentals() {
    int i;
    for (i = 0; i < noOfCustomers; i++) {
        if (customers[i].wallet < 0) {
            printf("%d. %s %s (%d)\n", customers[i].customer_id, customers[i].name, customers[i].surname, customers[i].age);
        }
    }
}


