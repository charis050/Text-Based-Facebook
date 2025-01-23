/********* main.c ********
    Student Name 	= Charis Nobossi
    Student Number	= 101297742
*/
// gcc main.c a2_functions.c -o a2_nodes   # Compile
//  ./a2_nodes                            # Run

// problem is that add_friend doesn't return anything, so you're not actually updating the pointer you're only updating it in the function locally not in main. add_user worked fine because it had a return value. how to fix? idk 

// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "a2_nodes.h"
#include "a2_functions.h"

#define NUMBER 3
#define POST_CHARS 250

int main()
{
    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);

    fclose(csv_file);
   
    // *******************************************************************************//


    int init_choice = 0;
    _Bool main_success = false;
    
    printf("\n************************************************************\n                  Welcome to Text-Based Facebook                   \n************************************************************\n\n\n");
    char *username = malloc(30 * sizeof(char));
    assert(username != NULL);

    while(init_choice != 3 && main_success != true){

        print_main();

        while(scanf("%d", &init_choice) != 1){

            printf("\nInvalid choice. Please enter an integer: ");
            while (getchar() != '\n'); // Clearing the invalid input
        }       

        switch(init_choice){
            case 1:
            {
                printf("\nEnter a username: ");
                scanf("%s", username);

                lowercase(username);
                user_t *user = find_user(users, username);

                if(user != NULL){
                    printf("\nError. User already exists in the system.\n");
                    break;
                }

                else{
                    char *password = malloc(15 * sizeof(char));
                    assert(password != NULL);

                    printf("\nEnter a password between 8 and 15 characters: ");
                    scanf("%s", password);

                    _Bool valid_password = password_check(password);

                    while(valid_password != true){
                        while (getchar() != '\n');
                        printf("\nInvalid password. Password must be at least 8 characters: ");
                        scanf("%s", password);

                        valid_password = password_check(password);

                    }

                    users = add_user(users, username, password);
                    
                    printf("\n******** User added! ********\n\n\n");
                    main_success = true;
                    break;
                }


            }
            case 2:
            {

                printf("\nEnter a username: ");
                scanf("%s", username);

                lowercase(username);
                user_t *user = find_user(users, username);

                if(user != NULL){
                    
                    char *password = malloc(15 * sizeof(char));
                    assert(password != NULL);
                    printf("\nEnter %s's password: ", user -> username);
                    scanf("%s", password);

                    if(strcmp(password, user -> password) == 0){
                        main_success = true;

                        
                    }
                    else{
                        printf("\nInvalid password.");
                    }
                }
                else{
                    printf("\nUser not found.");
                }
            break;

            }

            case 3:
            {
                main_success = false;
            }
            default:
            {
                printf("\nInvalid choice. Please try again.\n");
            }
    
    }
    }
    
    int choice = 0;

    while(choice != 6 && main_success == true)
    {       
        
        print_menu(username);

        while(scanf("%d", &choice) != 1){

            printf("\nInvalid choice. Please enter an integer: ");
            while (getchar() != '\n'); // Clearing the invalid input
        }

        switch(choice){
            case 1:
            {
                
               user_t *user = find_user(users, username);
               
               char *password = malloc(15 * sizeof(char));
                    assert(password != NULL);
                    printf("\nEnter the password: ");
                    scanf("%s", password);

                    if(strcmp(password, user -> password) == 0){
                        char *newpassword = malloc(15 * sizeof(char));
                        assert(newpassword != NULL);
                        printf("\nEnter a new password up to 15 characters: ");
                        scanf("%s", newpassword);
                        
                        _Bool valid_password = password_check(newpassword);

                        while(valid_password != true){
                        while (getchar() != '\n');
                        printf("\nInvalid password. Password must be at least 8 characters: ");
                        scanf("%s", newpassword);

                        valid_password = password_check(newpassword);

                        }
                        strcpy(user->password, newpassword); 
                    }
                    else{
                        printf("\n----------------------------------------\n                   Invalid password                   \n ----------------------------------------\n");
                    }

            }    

            break;

            case 2:
            {
                user_t *user = find_user(users, username);

                if(user != NULL){
                    printf("\n----------------------------------------\n           Managing %s's posts            \n ----------------------------------------\n", username);
                    
                    if(user -> posts == NULL){
                        printf("\nNote: no posts available for %s", username);
                    }
                    int choice = 0;
                    while(choice != 3){

                        printf("\n1. Add a new post \n2. Remove a post \n3. Return to main menu \n\nEnter your choice: ");


                         if (scanf("%d", &choice) != 1) {
                             while(scanf("%d", &choice) != 1){
                             printf("\nInvalid choice. Please enter an integer: ");
                             while (getchar() != '\n'); // Clearing the invalid input
                             }
                        }

                        if(choice == 1){
                            printf("\nEnter your post content: ");
                            char *text = malloc(POST_CHARS * sizeof(char));
                            scanf(" %[^\n]", text);

                            add_post(user, text);

                            display_all_user_posts(user);

                            while (getchar() != '\n'); // Clearing the invalid input
                        }

                        else if(choice == 2){
                            if (delete_post(user) == false){
                                printf("\nError: no posts available for %s\n", username);
                            }
                            else{
                                display_all_user_posts(user);
                            }
                            while (getchar() != '\n'); // Clearing the invalid input
                        }

                        else if(choice != 3){  
                            printf("\nInvalid choice\n");
                            while (getchar() != '\n'); // Clearing the invalid input
                        }
                
                    }
            }
            break;
            }
            
            case 3:
            {
                user_t *user = find_user(users, username);

                if(user != NULL){


                    printf("\n----------------------------------------\n           Managing %s's friends            \n ----------------------------------------\n", username);    
                    int choice = 0;
                    while(choice != 3){
                            printf("\n1. Add a new friend \n2. Remove a friend \n3. Return to main menu \nEnter your choice: ");
                    
                             if (scanf("%d", &choice) != 1) {
                                while(scanf("%d", &choice) != 1){
                                printf("\nInvalid choice. Please enter an integer: ");
                                while (getchar() != '\n'); // Clearing the invalid input
                                }
                             }

                            if (choice == 1){
                                printf("\nEnter a new friend's name: ");

                                char *friend = malloc(30 *sizeof(char));
                                assert(friend != NULL);
                                scanf("%s", friend);

                                user_t *friend_user = find_user(users, friend);
                                if(friend_user != NULL){
                                    
                                    add_friend(user,friend);

                                    printf("\nFriend %s has been added successfully\n", friend);
                               
                                    while (getchar() != '\n'); // Clearing the invalid input
                                }

                                else{
                                    printf("\nError. Friend cannot be added because %s does not exist.\n", friend);
                                }

                                
                                

                                
                            }
                            else if(choice == 2){

                                display_user_friends(user);

                                if(user -> friends != NULL){     // this conditional statement serves to check if the user has any friends to delete before prompting the user to enter a username
                                    printf("\nEnter a friend's name to delete: ");

                                char *name = malloc(30 * sizeof(char));
                                assert(name != NULL);
                                scanf("%s", name);
                                
                                delete_friend(user, name);
                                }
                            }
                                
                        
                            else if(choice != 3){
                                printf("\nInvalid choice\n");
                                while (getchar() != '\n'); // Clearing the invalid input
                            }
                                
                            }

            
                }
            break;
            }

            case 4:
            {
                char *username = malloc(30 *sizeof(char));
                assert(username != NULL);

                printf("\nEnter a friend's username to display their posts: ");
                scanf("%s", username);

                user_t *user = find_user(users, username);

                if(user != NULL){
                    display_posts_by_n(user, NUMBER);
                }
                break;
            }
            
            case 5:
            {        
            break;
            }

            default:
            printf("\nInvalid choice. Please try again.\n");
        }
    
    }
    printf("\nThank you for using Facebook today. We hope you enjoyed yourself and we'll see you soon! ");
    teardown(users);
}
