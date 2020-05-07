#include <bits/stdc++.h> 
#define MAX_TREE_HT 256 
using namespace std; 
  
// to map each character its huffman value 
map<char, string> codes; 
  
// to store the frequency of character of the input data 
map<char, int> freq; 
  
// A Huffman tree node 
struct MinHeapNode 
{ 
    char data;             // One of the input characters 
    int freq;             // Frequency of the character 
    MinHeapNode *left, *right; // Left and right child 
  
    MinHeapNode(char data, int freq) 
    { 
        left = right = NULL; 
        this->data = data; 
        this->freq = freq; 
    } 
}; 
  
// utility function for the priority queue 
struct compare 
{ 
    bool operator()(MinHeapNode* l, MinHeapNode* r) 
    { 
        return (l->freq > r->freq); 
    } 
}; 
  
// utility function to print characters along with 
// there huffman value 
void printCodes(struct MinHeapNode* root, string str) 
{ 
    if (!root) 
        return; 
    if (root->data != '$') 
        cout << root->data << ": " << str << "\n"; 
    printCodes(root->left, str + "0"); 
    printCodes(root->right, str + "1"); 
} 
  
// utility function to store characters along with 
// there huffman value in a hash table, here we 
// have C++ STL map 
void storeCodes(struct MinHeapNode* root, string str) 
{ 
    if (root==NULL) 
        return; 
    if (root->data != '$') 
        codes[root->data]=str; 
    storeCodes(root->left, str + "0"); 
    storeCodes(root->right, str + "1"); 
} 
  
// STL priority queue to store heap tree, with respect 
// to their heap root node value 
priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap; 
  
// function to build the Huffman tree and store it 
// in minHeap 
void HuffmanCodes(int size) 
{ 
    struct MinHeapNode *left, *right, *top; 
    for (map<char, int>::iterator v=freq.begin(); v!=freq.end(); v++) 
        minHeap.push(new MinHeapNode(v->first, v->second)); 
    while (minHeap.size() != 1) 
    { 
        left = minHeap.top(); 
        minHeap.pop(); 
        right = minHeap.top(); 
        minHeap.pop(); 
        top = new MinHeapNode('$', left->freq + right->freq); 
        top->left = left; 
        top->right = right; 
        minHeap.push(top); 
    } 
    storeCodes(minHeap.top(), ""); 
} 
  
// utility function to store map each character with its 
// frequency in input string 
void calcFreq(string str, int n) 
{ 
    for (int i=0; i<str.size(); i++) 
        freq[str[i]]++; 
} 
 
string decode_file(struct MinHeapNode* root, string s) 
{ 
    string ans = ""; 
    struct MinHeapNode* curr = root; 
    for (int i=0;i<s.size();i++) 
    { 
        if (s[i] == '0') 
           curr = curr->left; 
        else
           curr = curr->right; 
  
        // reached leaf node 
        if (curr->left==NULL and curr->right==NULL) 
        { 
            ans += curr->data; 
            curr = root; 
        } 
    } 
    // cout<<ans<<endl; 
    return ans+'\0'; 
} 
  
// Driver program to test above functions 
int main() 
{ 
    string str = "geeksforgeeks"; 
    string encodedString, decodedString; 
    calcFreq(str, str.length()); 
    HuffmanCodes(str.length()); 
    cout << "Character With there Frequencies:\n"; 
    for (auto v=codes.begin(); v!=codes.end(); v++) 
        cout << v->first <<' ' << v->second << endl; 
  
    for (auto i: str) 
        encodedString+=codes[i]; 
  
    cout << "\nEncoded Huffman data:\n" << encodedString << endl; 
  
    decodedString = decode_file(minHeap.top(), encodedString); 
    cout << "\nDecoded Huffman Data:\n" << decodedString << endl; 
    return 0; 
} 







//////////////////////////////////////////////////////////////////////















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
#include <pthread.h>
#define NTHREADS 1

using namespace std;

//global variables for hostname and port number
int global_argc;
char **global_argv;
struct letters
{
	char let;
	int count = 0;
	letters* next;
};

//Creates linked list class s
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
	void Bits(string fileData);
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
void s::Bits(string str)
{
	vector<char>symbol;
	char bino;
	letters* temp = new x;
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

//PRINTS OUT CHARACTER AND FREQUENCY
void s::Frequency()
{
	letters* temp = new letters;
	temp = head;
	while (temp != NULL)
	{
		cout << temp->let << " frequency: " << temp->count << endl;
		temp = temp->next;
	}
}

void error(char *msg)
{
    perror(msg);
    exit(0);
}
// Child thread code
void* childThread(void *arg)
{
	char buffer[256];
	s object;
	string bufferData;
	getline(cin,bufferData,'\0');
	for (int i = 0; i < bufferData.length() ; i++)
	{
		object.push(bufferData[i]);
		buffer[i]=bufferData[i];
	}
	object.Frequency();
	cout << "Original Message: " << bufferData ;
//Start of client side socket code

    int sockfd, portno, n;

    struct sockaddr_in serv_addr;
    struct hostent *server;
	object.Bits(bufferData);
    if (global_argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", global_argv[0]);
       exit(0);
    }
    portno = atoi(global_argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error((char*)string("Error opening socket").c_str());
    server = gethostbyname(global_argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error((char*)string("Error connecting").c_str());

    
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error((char*)string("Error writing to socket").c_str());
    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    if (n < 0) 
         error((char*)string("Error reading from socket").c_str());
    //printf("%s\n",buffer);
    return 0;
}


int main(int argc, char *argv[])
{

	global_argc = argc;
	global_argv = argv;
	pthread_t tid[NTHREADS];
	//creates Threads
	for(int i=0; i < NTHREADS; i++)
	{
		if(pthread_create(&tid[i],NULL, childThread, NULL))
		{
			cout << "Error creating thread" << endl;
			return 1;
		}
	}
	for(int x =0; x < NTHREADS; x++)
		pthread_join(tid[x], NULL);
	return 0;
}
