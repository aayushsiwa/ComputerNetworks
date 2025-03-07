// Write a connection-oriented client and server program in C using command line 
// arguments. At the server side, pass the port number (to whom the server will bind 
// to) in the command line. At the client side, pass the IP address and the port 
// number of the server (to whom the client will connect to) as command line 
// argument and carry out the following tasks.
// ◦ After establishment of connection print the IP Address and port number of the 
// client to whom the server is connected now. 
// ◦ Then exchange messages. 
// ◦ After message exchange is over then the client sends a “close” message to the 
// server to tear down the connection.

exec following in command line
gcc -o server server.c
gcc -o client client.c
./server 12345
./client 127.0.0.1 12345
