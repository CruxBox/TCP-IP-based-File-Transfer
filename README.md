# TCP-IP-based-File-Transfer-Program

Simple file transfer program using C sockets.
For the current version you can only trasfer files when server and client are on the same host.

Arguments for server.c :
{port number} {filename} 

Arguments for client.c :
{port number}

If you get a "Cannot connect" error after running the client, restart the server on another port as the one specified maybe busy.
