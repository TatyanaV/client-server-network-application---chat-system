# 	Name:  Tatyana Vlaskin +References
#	email: vlaskint@oregonstate.edu
# 	Class:CS372
#	Assignment: Project #1
# 	Program: chatclient.py
#	Description:
# 	This program performs the client side of a chat program. Program is started when the client
#   indicates the server IP address and the port number of the server it would like to connect
#	with on the command line. Once the connection is established with the chat server, the user is
#	asked for the username that has be to at least 1 characte and maximum 10 characters long.
#   After the username is accepted, a client is asked to enter there first message, which has to be
# 	at least 1 character and at most 500 characters long. After the message is accepted, it is sent to
#  	the server, and the client waits for the response. It will continue to send and wait until the
# 	client or the user enteres the command can send "\quit".
#	References: will be provided upon request


import socket # the socket module forms the basis of all network communications
import getopt
import sys
import os

# Used to process outgoing messages via send()
# also used to display the users chosen username      
def clientMessageFunction(clientSocket, clientUserName):
   #print clientUserName
   sys.stdout.write(clientUserName)
   clientMessage = raw_input("> ")
   
   # Used to verify string length is over 500
   while (len(clientMessage) > 500 or len(clientMessage) < 1 ):
      print "ERROR: Your message has to be between 1 and 500 characters. Retype your message."
      #clientMessage = raw_input(string(clientUserName) + '>')
      sys.stdout.write(clientUserName)
      clientMessage = raw_input("> ")
   #the line below, sends the string with the users name and message using TCP connection
   clientSocket.send(clientMessage)
   if clientMessage == "\quit":
      print "You have requested to close this connection. Good Bye"
      #connection is closed
      clientSocket.close
      sys.exit() 
   

# used to check the command line arguments
# also used to call the messagingClient function, which runs the program

if __name__ == '__main__':
   if len(sys.argv) != 3:
      print "ERROR: Please Enter: python chatclient.py <IP Address> <Port Number>"
      sys.exit()
   #IP address is the second argument
   serverIP = sys.argv[1]
   #port number is the 3rd argument
   serverPort = int(sys.argv[2])
   #creates a clients socket.
   #the 1st parameter indicates the address familyt, AF_INET indicates that the underlighting network is IPv4
   #2nr parameter indicates that the socket is of type SOCK_STREAM, which means that it is TCP socket
   clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
   #before the client can send data to the server using TCP socket, a TCP connection must be first established between
   #server and the client
   #the line below initiates a connection between client and the server
   #the paremeter of the connect() function is the adress of the SERVER side of the connection - IP and PORT #
   clientSocket.connect((serverIP, serverPort))
   #Receives the servers name which is hardcoded as SERVER
   serverName = clientSocket.recv(500)

   # This block is used to get the users desired username.
   clientUserName = raw_input("Please enter a User Name:")
   #print len(clientUserName)
   while 1 > len(clientUserName) or len(clientUserName) > 10:
      clientUserName = raw_input("User Name must be between [1-10] characters. Reenter a User Name: ")
   #the line below, sends the string with the users name theough the client's socket and into the TCP connection
   clientSocket.send(clientUserName)
   while 1:
      #send the username and the message to the server
      #waits for the response from the sender
      clientMessageFunction(clientSocket, clientUserName)
      #when charactes arrive from the server, they get placed into a string. Characters
      #continue to accumulate until the line ends with a carriage character.
      #the buffer size is 500
      #the message from the server is displayed
      serverMessage= str(clientSocket.recv(500))
      #is the message that was sent by the server states that the server wants to quit
      if serverMessage== "\quit":
         print "Server requested to close connection. Good Bye"
         #clients socket is closed
         clientSocket.close()
         sys.exit()
      #if the server does not want to close a connection, a client is prompted to type another message
      else:

         print serverName + "> " + serverMessage
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

