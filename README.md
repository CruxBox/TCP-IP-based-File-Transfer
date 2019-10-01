# TCP-IP-based-File-Transfer-Program

Simple file transfer program using C sockets.
If no server address is provided the program assumes the server to be on the localhost.

# Arguments for server.c :
{port number}

gcc server.c -o server
./server port_number

# Arguments for client.c :
{server address} {port number}

gcc client.c -o client
./client server_address port_number

If you get a "Cannot connect" error after running the client, restart the server on another port as the one specified maybe busy.
