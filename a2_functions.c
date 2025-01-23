/*****************
    Student Name 	= Charis Nobossi
    Student Number	= 101297742
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <ctype.h>
#include "a2_nodes.h"
#include "a2_functions.h"


#define NUMBER 3
#define PASSWORD_LENGTH 8

// Your solution goes here



/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
    srand(time(NULL));
    user_t *users = NULL;
    char buffer[500];
    fgets(buffer, sizeof(buffer), file); // Read and discard the header line
    int count = 0;
    for (int i = 0; i < num_users; i++)
    {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

        char *token = strtok(buffer, ",");
        char *token2 = strtok(NULL, ",");
        users = add_user(users, token, token2);
        char *username = token;

        token = strtok(NULL, ",");

        user_t *current_user = users;
        for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
            ;

        while (token != NULL && strcmp(token, ",") != 0 && count < 3)
        {
            if (strcmp(token, " ") != 0)
            {
                add_friend(current_user, token);
            }
            token = strtok(NULL, ",");
            count++;
        }
        count = 0;

        // token = strtok(NULL, ",");
        while (token != NULL && strcmp(token, ",") != 0)
        {
            add_post(current_user, token);
            token = strtok(NULL, ",");
        }
    }
    return users;
}

    
    
user_t *add_user(user_t *users, const char *username, const char *password){
    
    user_t *newnode = malloc(sizeof(user_t));
    assert(newnode != NULL);

    strcpy(newnode->username, username); 
    strcpy(newnode->password, password); 

    newnode -> friends = NULL;
    newnode -> posts = NULL;
    newnode -> next = NULL;


    if(users == NULL){     // this conditional statement checks if there are no users in the linked list at the time the function is called
        users = newnode;

        return users;
    }
    else if(users -> next == NULL){  // this conditional statement checks if there's only one user in the linked list at the time the function is called
        if(strcmp(newnode -> username, users -> username) < 0){  // this conditional statement checks if the new user should go before the singular user in the list
            user_t *next_node = users;
            users = newnode;
            users -> next = next_node;
            return users;
        }
        else{
            users -> next = newnode; // this conditional statement checks if the new user should go after the singular user in the list
            return users;
        }
    }

    else{
        user_t *previous = users;
        user_t *current = users -> next;
        assert(previous != NULL);
        assert(current != NULL);


        if(strcmp(newnode -> username, previous -> username) < 0){ // this conditional statement checks if the username is smaller than the first user in the list
            users = newnode;
            users -> next = previous;
            return users;
        }
        while(strcmp(newnode -> username, current -> username) > 0 && current -> next != NULL){ // this while loop checks through the list until either the list is finished, or the position of the new user has been found 
            current = current -> next;
            previous = previous -> next;
        }
        if(current -> next == NULL){  // this conditional statement checks if the reason we stopped incrementing is because we have reached the end of the list
            if (strcmp(newnode -> username, current -> username) > 0){ // this conditional statement checks if the new user's username goes before or after the last element in the list
            current -> next = newnode;
            return users;
            }

            else{
             previous -> next = newnode; 
             newnode -> next = current;
             return users;
            }

        }
        else{  // this conditional statement inserts the user at its correct position in the list when found, provided it is not the very beginning or very end of the list 
             previous -> next = newnode; 
             newnode -> next = current;
             return users;
        }
    }
}

    

user_t *find_user(user_t *users, const char *username){

    user_t *current = users;
    assert(current != NULL);
    while(strcmp(current -> username, username) != 0 && current -> next != NULL){
        current = current -> next;
    }

    if(strcmp(current -> username, username) == 0){
        return current;
    }

    else if(current -> next == NULL && strcmp(current -> username, username) != 0){
        current = NULL;
        return current;
    }
    return current;
    
}


/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t *create_friend(const char *username){
    friend_t *friend = malloc(sizeof(friend_t));

    strcpy(friend -> username, username);
    friend -> next = NULL;
}


/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t *user, const char *friend){

    friend_t *newnode = create_friend(friend);
    friend_t **head = &(user->friends);
    

    
    

    if(user -> friends == NULL){     // this conditional statement checks if there are no users in the linked list at the time the function is called
        user -> friends = newnode;
    }
else if ((*head)->next == NULL) {  // Check if there's only one friend in the linked list
        if (strcmp(newnode->username, (*head)->username) < 0) {  // Check if the new friend should go before the only friend
            friend_t *next_node = *head;
            *head = newnode;
            (*head)->next = next_node;
        } else { // The new friend should go after the only friend
            (*head)->next = newnode; 
        }
    }
    else {
        friend_t *previous = *head;
        friend_t *current = (*head)->next;
        assert(previous != NULL);
        assert(current != NULL);

        if (strcmp(newnode->username, previous->username) < 0) { // Check if the new friend is smaller than the first friend
            *head = newnode;
            (*head)->next = previous;
        } else {
            while (strcmp(newnode->username, current->username) > 0 && current->next != NULL) { 
                current = current->next;
                previous = previous->next;
            }
            if (current->next == NULL) { // Check if we reached the end of the list
                if (strcmp(newnode->username, current->username) > 0) { // New friend goes after the last friend
                    current->next = newnode;
                } else { // New friend goes before the last friend
                    previous->next = newnode; 
                    newnode->next = current;
                }
            } else { // Insert the new friend at the correct position
                previous->next = newnode; 
                newnode->next = current;
            }
        }
    }
}

_Bool delete_friend(user_t *user, char *friend_name){
    
    friend_t *previous = user -> friends;
    friend_t *current = user -> friends -> next;

    if(strcmp(previous -> username, friend_name) == 0){
        user -> friends = previous -> next;
        free(previous);
        previous = NULL;

        printf("\nUpdated");

        display_user_friends(user);

        return true;
    }
    
    if(current == NULL){
        printf("\nInvalid friend's name.\n");
        return 0;
        }


    while(strcmp(current -> username, friend_name) != 0 && current -> next != NULL){
       previous = previous -> next;
       current = current -> next;

    }


    if(strcmp(current -> username, friend_name) == 0){
        previous -> next = current -> next;
        free(current);
        current = NULL;
        printf("\nUpdated");
        display_user_friends(user);

        return true;
    
    }
    else{
        printf("\nInvalid friend's name.\n");
        return false;
    }


}

/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t *create_post(const char *text){
    post_t *post = malloc(sizeof(post_t));
    assert(post != NULL);
    strcpy(post->content, text);
    post -> next = NULL;

    return post;

}

/*
   Function that adds a post to a user's timeline following a stack.
*/
void add_post(user_t *user, const char *text){
    post_t *newnode = create_post(text);

    assert(newnode != NULL);
    strcpy(newnode->content, text);
    
    newnode -> next = user -> posts;
    user -> posts = newnode;
}

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user){
    if(user -> posts == NULL){
        return false;
    }
    else{
        post_t *to_remove = malloc(sizeof(post_t));
        to_remove = user -> posts;
        user -> posts = user -> posts -> next;
        free(to_remove);
        return true;
    }

}

/*
   Function that  displays a specific user's posts (All posts)
*/
void display_all_user_posts(user_t *user){
    post_t *current = user -> posts;
    
    printf("\n---------------------------------------------------\n        %s's posts\n", user -> username);
    while(current != NULL){
        printf("\n %s", current -> content);
        current = current -> next;
    }
    printf("\n---------------------------------------------------\n\n");
}


/*
   Function that displays a specific user's friends (All friends)
*/
void display_user_friends(user_t *user){

    friend_t *current = user -> friends;

    if(current != NULL){
        printf(" List of %s's friends:\n", user -> username);
    }

    else{
        printf("\n%s has no friends to display\n", user -> username);
    }

    while(current != NULL){
        printf("%s\n", current -> username);
        current = current -> next;

    }

    
    
}

/*
   Function that displays "number" of posts for a given user.
   After displaying "number" posts, it prompts if you want to display
   more posts.
   If there are no more post or the user types “n” or “N”, the function returns. 
*/
void display_posts_by_n(user_t *users, int number){
    int count = 0;


    post_t *current = users -> posts;

    if(current != NULL){
        printf("\n---------------------------------------------------\n        %s's posts\n", users -> username);
    }

    else{
        printf("\n%s has no posts to display\n", users -> username);
    }

    
    while(current != NULL){
            for(int i = 1; i <= NUMBER && current != NULL; i ++){  // this for loop prints three posts, or as many as it can up to three, before asking the user if they want to print more
                printf("\n %s", current -> content);
                current = current -> next;
                count ++;
            }

            if (current == NULL) {
                break; // Exit the loop since there are no more posts
            }
            char choice;
            printf("\nWould you like to display more posts?(Y/y or N/n) ");
            scanf("%s",&choice);
            while (getchar() != '\n');

            if(choice == 'Y' || choice == 'y'){
                count = 0;
            }

            else if(choice == 'N' || choice == 'n'){
                break;
            }

            else{
                printf("\nInvalid input.");
                break;
            }
    }

    if(current == NULL){
    printf("\nAll posts have been displayed\n");
    }


    
    
}

/*
   Function that free all users from the database before quitting the application.
*/
void teardown(user_t *users){
    while(users != NULL){

        
        friend_t *current_friend;
        while(users -> friends != NULL){
            current_friend = users -> friends;
            users -> friends = users -> friends -> next;
            free(current_friend);
            current_friend = NULL;
        }

        post_t *current_post;
        while(users ->posts != NULL){
            current_post = users -> posts;
            users -> posts = users -> posts -> next;
            free(current_post);
            current_post = NULL;
        }

        user_t *current_user;
        current_user = users;
        users = users -> next;
        free(current_user);
        current_user = NULL;
    }
}

/*
   Function that prints the main menu with a list of options for the user to choose from
*/
void print_menu(char *username){
    printf("\n************************************************************\n                        Welcome %s:                      \n************************************************************\n 1. Manage profile (change password)\n 2. Manage posts(add/remove)\n 3. Manage friends(add/remove)\n 4. Display a friend's posts\n 5. Exit\n\nEnter your choice:  ", username);
}

void print_main(){
    printf("************************************************************\n                        MAIN MENU:                      \n************************************************************\n 1. Register a new user\n 2. Login with an existing user's information\n 3. Exit\n\nEnter your choice:  ");

}

// user_t lowercase(user_t *users){
//     user_t *current = users;
//     assert(current != NULL);

//     while(current != NULL){
//         char *str = users -> username;
//         for (int i = 0; i < strlen(str); i++){
//             str[i] = tolower(str[i]);
//             }
//         }
// }

void lowercase(char *str){
    
    for (int i = 0; i < strlen(str); i++){
            str[i] = tolower(str[i]);
            }
    }

_Bool password_check(char *str){
    if(strlen(str) >= PASSWORD_LENGTH){
        return true;
    }

    else{
        return false;
    }
}