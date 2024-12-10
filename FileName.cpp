#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
void del_ch(char** password, int* cnt)
{
	if (*cnt <= 1)
	{
		return;
	}

	(*cnt)--;
	(*password)[*cnt - 1] = '\0';


	char* aux = (char*)realloc(*password, (*cnt) * sizeof(char));
	if (aux == NULL && *cnt > 1)
	{
		printf("Memory allocation failed!\n");
		free(*password);
		exit(-1);
	}
	*password = aux;

	printf("\b \b");
}
void copy(char* username, int* k,char *string)
{
	*k = 0;
	for (int i = 0; i < strlen(string); i++)
	{
		username[(*k)++] = string[i];
	}
	username[(*k)] = '\0';

}
void save_password(char** key_password, int* x) 
{
	int cnt = 1;
	*x = 0;
	char ch;

	*key_password = (char*)malloc(cnt * sizeof(char));  
	if (*key_password == NULL)
	{
		printf("Memory allocation failed!\n");
		exit(-1);
	}

	while ((ch = _getch()) != '\r') 
	{  
		if (ch == '\b')
		{
			del_ch(key_password,&cnt);
		}
		else
		{
			printf("*");
			char* aux = (char*)realloc(*key_password, (cnt + 1) * sizeof(char));
			if (aux == NULL)
			{
				printf("Memory allocation failed!\n");
				free(*key_password);
				exit(-1);
			}
			*key_password = aux;

			(*key_password)[(*x)++] = ch;
			cnt++;
		}
	}

	(*key_password)[*x] = '\0';  
}
void create_password(char** password)
{
	int cnt = 1;
	char ch;
	int x = 0;
	*password = (char*)malloc(cnt * sizeof(char));
	if (*password == NULL)
	{
		printf("Memory allocation failed!\n");
		exit(-1);
	}

	while ((ch = _getch()) != '\r')
	{
		if (ch == '\b')
		{
			del_ch(password,&cnt);
		}
		else
		{
			printf("*");
			char* aux = (char*)realloc(*password, (cnt + 1) * sizeof(char));
			if (aux == NULL)
			{
				printf("Memory allocation failed!\n");
				free(*password);
				exit(-1);
			}
			*password = aux;

			(*password)[x++] = ch;
			cnt++;
		}
	}

	(*password)[x] = '\0';
}
void autentification(char *user,char *key_user,char *password,char*key_password)
{
	int attemps = 0;
	bool verify = false;
	while (attemps < 3)
	{
		if ((strcmp(user, key_user) == 0) && (strcmp(password, key_password) == 0))
		{
			printf("\n\nAutentification succesfull !\n");
			printf("Press any key to continue....");
			_getch();
			verify = true;
			break;
		}
		else
			if ((strcmp(user, key_user) == 0) && (strcmp(password, key_password) != 0))
			{
				printf("\n\nIncorect password \nTry again!\n");
				printf("\n");
				printf("User:");
				scanf("%s", user);
				printf("Password:");
				create_password(&password);
				attemps++;

			}
			else
				if ((strcmp(user, key_user) != 0) && (strcmp(password, key_password) == 0))
				{
					printf("\n\nUser incorect \nTry again!\n");
					printf("\n");
					printf("User:");
					scanf("%s", user);
					printf("Password:");
					create_password(&password);
					attemps++;
				}
				else
				{
					printf("\n\nUser & Password incorect \nTry again!\n");
					printf("\n");
					printf("User:");
					scanf("%s", user);
					printf("Password:");
					create_password(&password);
					attemps++;
				}
	}
	if (verify == false)
	{
		printf("\n\nAutentification failed!\n");
		printf("Press any key to continue....");
		_getch();
		

	}
}
int main(void)
{
	printf("Create account");
	printf("\nUsername:");
	char user[21];
	gets_s(user);
	printf("Password:");
	char* key_user=NULL,*key_password=NULL;
	key_user = (char*)malloc(strlen(user) + 1);
	if (key_user == NULL)
	{
		free(key_user);
		exit(-1);
	}
	int k = 0,x=0;
	copy(key_user, &k,user);
	save_password(&key_password, &x);
	printf("\n\nLogin");
	printf("\nUsername:");
	scanf("%s", user);
	printf("Password:");
	char* password = NULL;
	create_password(&password);
	autentification(user, key_user, password, key_password);
	free(key_user);
	free(key_password);
	free(password);

}