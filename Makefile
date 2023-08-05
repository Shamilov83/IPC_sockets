

CC:=gcc

client: client.c
	$(CC) client.c -o client

server: server.c
	$(CC) server.c -o server
	
rclient: raw_client.c
	$(CC) raw_client.c -o raw_client
	
userver: rserver.c
	$(CC) rserver.c -o udp_server
	
uclient: uclient.c
	$(CC) uclient.c -o udp_client
	
