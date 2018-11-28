How to run and compile:

1) Compile the server by typing in "g++ server.cpp -o server.out"
2) Compile the client by typing in "g++ client.cpp -o client.out"
3) Execute server.out
4) Execute client.out
5) Follow the instructions printed by client.out

Reasoning behind using TCP over UDP:

The reason I chose TCP over UDP was because of the RDT advantages TCP has over UDP. This did however, come with a cost of establishing a connection between the server and client, whereas it would not have been necessary had I used UDP. The system That I have made has some problems with scalability, as it only handles one client at a time. 

Testing:

How I did my testing is that I would incrementally add features and then test them with different cases. I foudn that testing inside a virtual machine is a very reliable way to get consistent results for each test.
