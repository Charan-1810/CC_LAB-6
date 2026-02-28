#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    while(true) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

        char buffer[1024] = {0};
        read(new_socket, buffer, 1024);

        std::string response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n\r\n"
            "Served by backend\n";

        send(new_socket, response.c_str(), response.length(), 0);
        close(new_socket);
    }
}    
    std::cout << "Server listening on port 8080 (hostname: " << hostname << ")" << std::endl;
    
    // Accept connections in loop
    while(true) {
        int client_fd = accept(server_fd, NULL, NULL);
        if (client_fd < 0) continue;
        
        // Simple HTTP response
        std::string response = "HTTP/1.1 200 OK\r\n";
        response += "Content-Type: text/plain\r\n";
        response += "Connection: close\r\n\r\n";
        response += "Served by backend: " + std::string(hostname) + "\n";
        
        send(client_fd, response.c_str(), response.length(), 0);
        close(client_fd);
    }
    
    return 0;
}
