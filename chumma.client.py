import socket

def start_client():
    host = ''  # Server's hostname or IP address
    port = 65432        # Port used by the server

    with socket.socket() as client_socket:
        client_socket.connect((host, port))
        messages = ["Hello, Server!\n", "This is the second message.\n"]
        for message in messages:
            client_socket.sendall(message.encode('utf-8'))
            print(f"Sent: {message.strip()}")

if __name__ == "__main__":
    start_client()