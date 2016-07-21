/*
# 	Name:  Tatyana Vlaskin + references
# 	Program: chatserve.cpp
#	Description:
# 	This program performs the server side of a chat program. Program is started when the server
#   indicates the port number is would like to use for the program. After that the server waits for
#   the client to connect. if no clients are available to connect the server will wait for them.
#	Press Ctrl-C to kill the server program at any time.
#	When connected to a client and it is the servesr turn to send a message you will see a
#   prompt saying "SERVER>" this is when you enter text you wish to send to the client.
#   If the text is not between 1 - 500 characters, you will be asked to reenter a text
#	You can type "\quit" whenever it is your turn to chat to close the connection with
#   the current client and return to waiting for another.
#	Reference will be provided upon request

*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

using namespace std;


/*
struct sockaddr_in {
    short            sin_family;   // e.g. AF_INET
    unsigned short   sin_port;     // e.g. htons(3490)
    struct in_addr   sin_addr;     // see struct in_addr, below
    char             sin_zero[8];  // zero this if you want to
};
*/
//http://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html
struct sockaddr_in hostAddress;
char serverHandle[510] = "SERVER";	//Used as the handle for the server, hardcoded
char clientMessage[510]; //510 for message and handle
char serverMessage[510];//510 for message and handle
int serversSocket; //is a socket that will be created with socket()
int portNumber;
int clientSocket;
string clientsUserName;
//booleans to control connections
bool clientRequestoToEndConnection;
bool serverRequestToEndConnection;
bool endConnection;//lets the program know is the connection is still running
/*Function to create a socket
//http://www.cis.gvsu.edu/~wolffe/courses/cs656/projects/tutorial_CSockets.html
    receives:   none
    returns:    none
    pre:        none
    post:       none
 */
void createSocket();
/*Function to send messages to the connected client
    receives:   none
    returns:    none
    pre:        none
    post:       none
 */
void serverMessage1();
/*Function to read messages from the client
    receives:   none
    returns:    none
    pre:        none
    post:       none
 */
void clientMessage1();
/*Function to accept an incomming connection and read messages from the client.
note that server handler is hardcoded to SERVER
    receives:   none
    returns:    none
    pre:        none
    post:       none
 */
void maintainConnection();
// Used to handle kill signals from the server Ctrl+C
void sigintHandler(int prameter);

//main
int main(int argc, char **argv){
    int portNumberCheck; //to validate the correct entry was made for port number
    // chartserce on host A waits fon a port[specified by command-line] for a client request
    //using command line, 2 arguments are expected:
    //1.chartserve
    //2. <port # on which to listen for connection requests, must be in the range [1024, 65535]
    // if incorrect number of arguments are entered display an error
  	if(argc!=2){
		cerr << "ERROR: No port specified. Type: ./chatserver.cpp <port number>, port must be in the range [1024-65535] " << endl;
		exit(1);
	}
    //per the following refferences: port # in the range 1024-65535 can be freely used
	//page 193 Computer Networkinng top down approach
	//https://technet.microsoft.com/en-us/library/gg398833.aspx
	//https://books.google.com/books?id=nDnSBQAAQBAJ&pg=PA389&lpg=PA389&dq=port+numbers+used+for+servers+1024-65535+chats&source=bl&ots=P50QoqyGGC&sig=7zbmQcn6m13xumh_aJl3bHB-c5E&hl=en&sa=X&ved=0CEoQ6AEwB2oVChMIudbevKLuyAIVRM9jCh2bEwcD#v=onepage&q=port%20numbers%20used%20for%20servers%201024-65535%20chats&f=false
	// places the port number in the var
	portNumberCheck = atoi(argv[1]);
	if (portNumberCheck < 1024 || portNumberCheck > 65535) {
		cerr << "ERROR: Port number must be in the range [1024 - 65535]" << endl;
		exit(1);
	}

	signal(SIGINT, sigintHandler);
	//place the port # in the variable
	portNumber = atoi(argv[1]);
	//creat new socket
	createSocket();
	// Associate server-side socket with listening port.
	//binding the server socekt [that is, assigning] the port number to the servers socket
	bind(serversSocket, (struct sockaddr*)&hostAddress, sizeof(hostAddress));
    // Listen for connections
    //http://linux.die.net/man/2/listen
    //int listen(int sockfd, int backlog);
    // backlog argument defines the maximum length to which the queue of pending connections for sockfd may grow
    //for more information see http://linux.die.net/man/2/listen
	listen(serversSocket, 10);
	//accept an incomming connection. The read messages from the client.
	maintainConnection();
	return 0;
}

/*Function to create a socket
//http://www.cis.gvsu.edu/~wolffe/courses/cs656/projects/tutorial_CSockets.html
    receives:   none
    returns:    none
    pre:        none
    post:       none
 */
void createSocket(){
    /*
    The socket() call creates an unnamed socket and returns a file descriptor to the calling process.
    The function prototype is as follows:  int socket(int domain, int type, int protocol);
    where domain specifies the address domain, type specifies the socket type, and the third
    argument is the protocol (this is usually set to 0 to automatically select the appropriate default).
    Here is a typical socket() call:    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    This establishes a socket in the Internet domain, and configures it for stream-oriented
    communication using the default TCP protocol*/
	serversSocket = socket(AF_INET, SOCK_STREAM, 0);
    //fill memory with a constant byte
	//void *memset(void *s, int c, size_t n);
	// The memset() function fills the first n bytes of the memory area pointed to by s with the constant byte c
	//clearning the buffer by filling it 0
	memset(&hostAddress, '0', sizeof(hostAddress));
    // Configure the server address
	//http://man7.org/linux/man-pages/man7/ip.7.html
	// address family, network is IPv4. According to the book, page 160 we do not
	//need to worry about understanding this right now, we will cover IPv4 in chapter 4
	hostAddress.sin_family = AF_INET;
    //set port number
    //converts the unsigned short integer netshort from network byte order to host byte order
    // convert our byte orderings to "big-endian" before receiving them
	//see http://beej.us/guide/bgnet/output/html/multipage/htonsman.html
	hostAddress.sin_port = htons(portNumber);
    //the socket will be bound to all local interfaces
    // Scince this is a server, the IP address has been set to INADDR_ANY,
    //specifying that connections will be accepted from any other host.
	hostAddress.sin_addr.s_addr = htonl(INADDR_ANY);
}


/*Function to send messages to the connected client
    receives:   none
    returns:    none
    pre:        none
    post:       none
 */
void serverMessage1(){
    //clients handler
	cout << clientsUserName << "> " << clientMessage << endl;
	//server handler
	cout << serverHandle << "> ";
	//can accept up to 500 charactesr
	//sizeof ( line )
	//char outBuffer1[510];
	cin.getline(serverMessage, sizeof(serverMessage));
	//string will be used to check if appropriate size of message was enered
	string validateInput = serverMessage;
	// used to verify string length is over 500
	while(validateInput.length() > 500 || validateInput.length() < 1 ){
		memset(&serverMessage, 0, sizeof(serverMessage));
		if(validateInput.length() > 500){
            cout << "ERROR: Your message is more than 500 characters long. Retype your message." << endl;
		}
        if(validateInput.length() < 1 ){
            cout << "ERROR: Your message is less than 1 character long. Retype your message." << endl;
		}
		cout << serverHandle << "> ";
		cin.clear();
		cin.ignore(validateInput.length(), '\n');
		cin.getline(serverMessage, sizeof(serverMessage));
		//cin.ignore(validateInput.length(), '\n');
		//cin.clear();
		validateInput.clear();
		validateInput = serverMessage;
	}

	// If user would like to quit then quit
	if (validateInput == "\\quit")	{
		cout << "Server requested to close connection. Waiting for new connection..." << endl << endl;
		serverRequestToEndConnection = true;
		endConnection = true;
	}

    if (validateInput.length() < 500){
            validateInput = serverMessage;
            //function sends messages
            //ssize_t send(int sockfd, const void *buf, size_t len, int flags);
            //http://man7.org/linux/man-pages/man2/send.2.html
            //http://beej.us/guide/bgnet/output/html/multipage/sendman.html
            // Used to send data to the client
            //send(clientSocket, serverMessage, strlen(serverMessage), 0);
            send(clientSocket, serverMessage, strlen(serverMessage), 0);
        }

}
/*Function to read messages from the client
    receives:   none
    returns:    none
    pre:        none
    post:       none
 */
void clientMessage1(){
    //receives messages from a connected socket
    //no messages are available at the socket, the receive calls wait for a message to arrive
    //ssize_t recv(int sockfd, void *buf, size_t len, int flags);
    /*
    The recv() function takes the following arguments:
        socket    Specifies the socket file descriptor.
        buffer    Points to a buffer where the message should be stored.
        length    Specifies the length in bytes of the buffer pointed to by the buffer argument.
        flags     Specifies the type of message reception.
    */
    //please note that the size of the buffer is 500
	recv(clientSocket, clientMessage, 500, 0);
	string validateInput = clientMessage;
	// If a client wants to quit
	if (validateInput == "\\quit"){
		cout << "Client requested to close connection. Waiting for new connection..." << endl << endl;
		clientRequestoToEndConnection = true;
		endConnection = true;
	}
}

/*Function to accept an incomming connection and read messages from the client.
note that server handler is hardcoded to SERVER
    receives:   none
    returns:    none
    pre:        none
    post:       none
 */
void maintainConnection(){
	// Accept incoming requests.
	while(1){
        // AAccept a connection with the accept() system call.
		//This call typically blocks until a client connects with the server.
		//http://www.tutorialspoint.com/unix_sockets/socket_server_example.htm
		clientSocket = accept(serversSocket, (struct sockaddr*)NULL,NULL);
		cout << "Connection with client opened." << endl;
        //function sends messages
        //ssize_t send(int sockfd, const void *buf, size_t len, int flags);
        //http://man7.org/linux/man-pages/man2/send.2.html
        //http://beej.us/guide/bgnet/output/html/multipage/sendman.html
        // Used to send data to the client
		send(clientSocket, serverHandle, strlen(serverHandle),0);
		//get the clients name
        //fill memory with a constant byte
        //void *memset(void *s, int c, size_t n);
        // The memset() function fills the first n bytes of the memory area pointed to by s with the constant byte c
        //clearning the buffer by filling it 0
        memset(&clientMessage, 0, sizeof(clientMessage));
        //receives messages from a connected socket
        //no messages are available at the socket, the receive calls wait for a message to arrive
        //ssize_t recv(int sockfd, void *buf, size_t len, int flags);
        /*
        The recv() function takes the following arguments:
            socket    Specifies the socket file descriptor.
            buffer    Points to a buffer where the message should be stored.
            length    Specifies the length in bytes of the buffer pointed to by the buffer argument.
            flags     Specifies the type of message reception.
        */
        //please note that the size of the buffer is 500
        int receiveCheck;
        receiveCheck = recv(clientSocket, clientMessage, 500, 0);
        // Error encountered
        if (receiveCheck == -1) {
            cerr << "ERROR: in recv function while receiving message for a connected socket" << endl;
            exit(1);
        }
        else {
            //in this case everything that was typed by the user will be the username
            clientsUserName = clientMessage;
        }
		//Logic sentinels to manage if the client decided to quit or not.
		endConnection = false;
		clientRequestoToEndConnection = false;
		serverRequestToEndConnection = false;

		while(!endConnection){
			// Used to reset the buffers.
			memset(&serverMessage, 0, sizeof(serverMessage));
			memset(&clientMessage, 0, sizeof(clientMessage));
            //read messages from the client
			clientMessage1();
            //if te client requested to end connecting
			if(clientRequestoToEndConnection){
				close(clientSocket);
                // Listen for connections
                //http://linux.die.net/man/2/listen
                //int listen(int sockfd, int backlog);
                // backlog argument defines the maximum length to which the queue of pending connections for sockfd may grow
                //for more information see http://linux.die.net/man/2/listen
				listen(serversSocket, 5);//waits for 5 minutes
			}
			else
                //if still connected send messages to the connected client
				serverMessage1();
            //if the server requested to end connection
			if(serverRequestToEndConnection){
				close(clientSocket);
                // Listen for connections
                //http://linux.die.net/man/2/listen
                //int listen(int sockfd, int backlog);
                // backlog argument defines the maximum length to which the queue of pending connections for sockfd may grow
                //for more information see http://linux.die.net/man/2/listen
				listen(serversSocket, 5);
			}
		}
	}
}

// Used to handle kill signals from the server Ctrl+C
void sigintHandler(int pram){
	cout << "\n Signal Received from the Server. Connection is closed\n" <<  endl;
	close(clientSocket);
	exit(1);
}


























