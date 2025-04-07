import socket

def start_server():
    host = ''  # Localhost
    port = 65432        # Port to listen on

    with socket.socket() as server_socket:
        server_socket.bind((host, port))
        server_socket.listen()
        print(f"Server listening on {host}:{port}")
        
        conn, addr = server_socket.accept()
        with conn:
            print(f"Connected by {addr}")
            while True:
                data = conn.recv(1024)
                if not data:
                    break
                print(f"Received: {data.decode()}")

if __name__ == "__main__":
    start_server()