#include<vector>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <fstream>
#include<iomanip>
#include <iostream>
#include<string>
#include<thread>
#include <string.h>
#include <bits/stdc++.h> 
#include<string>
#include<vector>
#include<string>
#include <algorithm>
#include <stdio.h> 
#include <sys/types.h> 
#define SIZE 26 
#include <unistd.h>
#include <cstring>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


using namespace std;

void error(char *msg)
{
    perror(msg);
    exit(1);
}
struct letters
{
	char let;
	int count = 0;
	letters* next;
};

//CREATES LINKED LIST 
class s
{
private:
	letters* head, * tail;
public:
	s()
	{
		head = NULL;
		tail = NULL;
	}
	void push(char a);
	void Frequency();
	void Bits(string str);
};

//PUTS CHARACTER INTO LINKED LIST AND COUNTS FREQUENCY
void s::push(char a)
{
	bool f = false;
	letters* temp = new letters;
	if (head == NULL)
	{
		temp->let = a;
		temp->next = NULL;
		head = temp;
		tail = temp;
	}
	temp = head;
	while (temp != NULL)
	{
		if (temp->let == a)
		{
			f = true;
			temp->count += 1;
			return;
		}
		temp = temp->next;
	}
	letters* node = new letters;
	node->let = a;
	node->count += 1;
	node->next = NULL;
	tail->next = node;
	tail = node;
}

//PRINTS OUT AND FINDS BIT SYMBOL 
void s::Bits(string str)
{
	vector<char>symbol;
	char bino;
	letters* temp = new letters;
	bool started = false;
	for (int i = 0; i < str.length(); i++)
	{
		bool found = false;
		if (symbol.size() == 0)
			symbol.push_back(str[i]);
		for (int j = 0; j < symbol.size(); j++)
		{
			if (str[i] == symbol[j])
				found = true;
		}
		if (!found)
			symbol.push_back(str[i]);
	}
	while (symbol.size() != 0)
	{
		if (started)
		{
			cout << "Remaining Message: ";
			for (int i = 0; i < str.length(); i++)
			{
				for (int j = 0; j < symbol.size(); j++)
				{
					if (str[i] == symbol[j])
						cout << str[i];
				}
			}
		}
		cout << "\nSymbol " << symbol.front() << " code: ";
		for (int i = 0; i < str.length(); i++)
		{
			for (int j = 0; j < symbol.size(); j++)
			{
				if (str[i] == symbol[j])
				{
					if (str[i] == symbol.front())
						cout << "1";
					else
						cout << "0";
				}
			}
		}
		cout << endl;
		symbol.erase(symbol.begin());
		started = true;
	}

}


int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     //Creates the socket           
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error((char*)string("Error opening socket").c_str());
     bzero((char *) &serv_addr, sizeof(serv_addr));
     //gets port# from user input and sets it 
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error((char*)string("Error on binding").c_str());
     //listen waits for connection to server to be made and accepts new connected socket         
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *)&clilen);

     if (newsockfd < 0) 
          error((char*)string("Error on accept").c_str());
     bzero(buffer,256);
     n = read(newsockfd,buffer,255);

     if (n < 0) error((char*)string("Error reading from socket").c_str());
     //printf("Here is the message: %s\n",buffer);
     //child process that gets the bit symbols
     pid_t child1;
     child1 = fork();
     if(child1 == 0)
     {
        s object;
        for(int i = 0; i < sizeof(buffer); i++)
        {
            object.push(buffer[i]);
        }
        
        exit(0);
     }
     
     //writes back to client
     n = write(newsockfd,buffer,strlen(buffer));
     if (n < 0) error((char*)string("Error writing to socket").c_str());
     return 0; 
}
