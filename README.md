# client-server-network-application---chat-system

NOTE:   This program was tested on OSU's flip servers on the same computer, by opening 2 different terminals.

#OBJECTIVE:
1. Implement a client-server network application<br />
2. Learn to use the sockets API<br />
3. Use the TCP protocol<br />
4. Refresh programming skills<br />

#PROGRAM REQUIREMENTS:
Design and implement a simple chat system that works for one pair of users, i.e., create two programs: a chat server and a chat client.<br /> The final version of your programs must accomplish the following tasks:<br />
1. chatserve starts on host A.<br />
2. chatserve on host A waits on a port (specified by command-line) for a client request.<br />
3. chatclient starts on host B, specifying host A’s hostname and port number on the command line.<br />
4. chatclient on host B gets the user’s “handle” by initial query (a one-word name, up to 10 characters).<br />
 chatclient will display this handle as a prompt on host B, and will prepend it to all messages sent to host A. e.g., “ SteveO> Hi!!”<br />
5. chatclient on host B sends an initial message to chatserve on host A : PORTNUM. <br />
This causes a connection to be established between Host A and Host B. Host A and host B are now peers, and may alternate <br />
sending and receiving messages. Responses from host A should have host A’s “handle” prepended.<br />
6. Host A responds to Host B, or closes the connection with the command “\quit”<br />
7. Host B responds to Host A, or closes the connection with the command “\quit”<br />
8. If the connection is not closed, repeat from 6.<br />
9. If the connection is closed, chatserve repeats from 2 (until a SIGINT is received).<br />
<br />
# HOW TO RUN A PROGRAM:
SERVER SIDE:<br />

(1) Open a terminal that will be your server terminal.<br /><br />
(2) Type: make to compile chatserve.cpp program<br />
(3) After the program is compiled.<br />
a. Type: hostname –i<br />
b. An IP address will be displayed, write down that number<br />
(4) Type ./chatserve <port #><br /><br />
a. Please note that only ports in the range 1024 -65535 will be accepted. Those ports are not used for most of the applications and can be freely used. <br />
b. If you type a number not in the range 1024 -65535, you will be asked a reenter a port number<br />
c. If you forget to type port number, you will be asked to enter a port number<br />

(5) You are done with the server side for NOW.  <br />

CLIENT SIDE:<br />
(1) Open second terminal that will be used as a client.<br />
(2) Type: python chatclient.py IP address portNumber<br />
a. <IP address> is the address that you found by typing hostname –i in the server terminal<br />
b. <portNumber> is the same port used by the server<br />
(3) You will be prompted to enter a username<br />
a. A username needs to be between 1 and 10 characters<br />
b. If you type a username that is not between 1 and 10 characters inclusive, you will be asked to reenter a username<br />
c. After the username is accepted, you will see a prompt to type your 1st message. Entered username> <br />
d. Type your message and press enter<br />
e.  If you type a message that is less than 1 or more than 500 characters,  you will get an error and will be asked to reenter a message<br />
(4) You are done with the client side for now<br />
a. Please note that if you do not send any messages you will be timed out and disconnected after around 5 minutes of inactivity.<br />
b. 
SERVER:<br />
(1) On the server side,  clients handle and clients message will be displayed<br />
(2) There will be a prompt for a server to enter a response. The handle for the header is hardcoded. SERVER><br />
(3) Type a response and press enter<br />
a. Please note if a message is less than 1 character and more than 500 characters, you will get an error message and will be asked to retype a message<br />
(5) You are done with the Server side for now<br />
a. Please not that you can press Ctrl-C to kill the server program at any time.<br />
	
    CONTINUE:<br />
(1) Alternate between client and server for sending/receiving.<br />
a. Please note that you can send only ONE message at a time<br />
(2) Send a message from chatclient to chatserve, or enter "\quit" to        close connection.<br />
(3) Send a message from chatserve to chatclient, or enter "\quit" to        close connection.<br />
(4) If connection was closed either by client or server, the sever will be waiting for the new connection, go to the client terminal and repeat everything stated under the client section of this README document<br />
(5) Press Ctrl-C to kill the server program at any time.<br />
a. Please NOTE – Ctrl-C should be used only after either client or server terminated connection using \quit. Otherwise unpredicted behavior is expected.<br />


<br />
#MOCK RUN - THOUGH THE PROGRAM 
SERVER SIDE:

[vlaskint@flip2 ~]$ clear<br />
[vlaskint@flip2 ~]$ make<br />
g++ -std=c++0x -Wall -pedantic-errors -g chatserve.cpp  -o chatserve<br />
[vlaskint@flip2 ~]$ hostname -i<br />
128.193.54.7<br />
[vlaskint@flip2 ~]$ ./chatserve<br />
ERROR: No port specified. Type: ./chatserver.cpp <port number>, port must be in the range [1024-65535]<br />
[vlaskint@flip2 ~]$ ./chatserve 1027<br />
Connection with client opened.<br />
tatyana> hi<br />
SERVER> hi<br />
tatyana> resending<br />
SERVER> hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh<br />
ERROR: Your message is more than 500 characters long. Retype your message.<br />
SERVER> resending as well<br />
Client requested to close connection. Waiting for new connection...<br />

Connection with client opened.<br />
mike> hi<br />
SERVER> \quit<br />
Server requested to close connection. Waiting for new connection...<br />




CLIENT SIDE:<br />
[vlaskint@flip2 ~]$ python chatclient.py 128.193.54.7 1027<br />
Please enter a User Name:555555555555555555555555555555<br />
User Name must be between [1-10] characters. Reenter a User Name: tatyana<br />
tatyana> hi<br />
SERVER> hi<br />
tatyana> hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh<br />
Please enter a message between [1-500] characters.<br />
tatyana> resending<br />
SERVER> resending as well<br />
tatyana> \quit<br />
You have requested to close this connection. Good Bye<br />
[vlaskint@flip2 ~]$ python chatclient.py 128.193.54.7 1027<br />
Please enter a User Name:mike<br />
mike> hi<br />
Server requested to close connection. Good Bye<br />

