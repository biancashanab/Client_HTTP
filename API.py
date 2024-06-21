import os
import tkinter as tk
from tkinter import ttk
from tkinter import messagebox
import subprocess

class HttpClientApp:
    def __init__(self, root):
        self.root = root
        self.root.title("HTTP Client Interface")
        self.root.geometry("400x200")
        
        self.host_label = ttk.Label(self.root, text="Host:")
        self.host_label.pack(pady=10)
        self.host_entry = ttk.Entry(self.root, width=40)
        self.host_entry.pack()
        
        self.request_type_label = ttk.Label(self.root, text="Request Type:")
        self.request_type_label.pack(pady=10)
        self.request_type_combobox = ttk.Combobox(self.root, values=["GET", "POST", "HEAD", "PUT", "DELETE", "CONNECT", "TRACE"], width=37)
        self.request_type_combobox.pack()
        
        self.send_request_button = ttk.Button(self.root, text="Send Request", command=self.send_request)
        self.send_request_button.pack(pady=20)
    
    def send_request(self):
        host = self.host_entry.get().strip()
        request_type = self.request_type_combobox.get().strip()
        
        if not host or not request_type:
            messagebox.showerror("Error", "Host and Request Type are required.")
            return
        
        try:
            print("Current directory:", os.getcwd())
            executable_path = "/home/bianca/Client_HTTP/bin/http_client"
            print("Executable path:", executable_path)
            print("Executable exists:", os.path.exists(executable_path))
            
            result = subprocess.run([executable_path, request_type, host], capture_output=True, text=True)
            response_text = result.stdout
            response_popup = tk.Toplevel(self.root)
            response_popup.title("Response")
            response_popup.geometry("600x400")
            
            response_textbox = tk.Text(response_popup, wrap=tk.WORD)
            response_textbox.insert(tk.END, response_text)
            response_textbox.pack(expand=True, fill=tk.BOTH)
        except Exception as e:
            messagebox.showerror("Error", f"Failed to send request: {str(e)}")

if __name__ == "__main__":
    root = tk.Tk()
    app = HttpClientApp(root)
    root.mainloop()
