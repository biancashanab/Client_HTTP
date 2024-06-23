import os
import shutil
import tkinter as tk
from tkinter import ttk
from tkinter import messagebox
import subprocess
import webbrowser
import time

class HttpClientApp:

    def _init_(self, root):
        self.root = root
        self.root.title("HTTP Client Interface")
        self.root.geometry("500x500")
        self.root.resizable(False, False)
        self.root.columnconfigure(0, weight=1)
        self.root.rowconfigure(0, weight=1)
        
        self.root.bind("<Return>", lambda event: self.send_request())        
        self.host_label = ttk.Label(self.root, text="Host:")
        self.host_label.pack(pady=10)
        self.host_entry = ttk.Entry(self.root, width=40)
        self.host_entry.pack()
        
        self.subdomain_label = ttk.Label(self.root, text="Subdomain(if needed):")
        self.subdomain_label.pack(pady=10)
        self.subdomain_entry = ttk.Entry(self.root, width=40)
        self.subdomain_entry.pack()
        
        self.username_label = ttk.Label(self.root, text="Username(if needed):")
        self.username_label.pack(pady=10)
        self.username_entry = ttk.Entry(self.root, width=40) 
        self.username_entry.pack()
        
        self.password_label = ttk.Label(self.root, text="Password(if needed):") 
        self.password_label.pack(pady=10) 
        self.password_entry = ttk.Entry(self.root, width=40, show="*")
        self.password_entry.pack() 
        
        self.number_of_requests_label = ttk.Label(self.root, text="Number of Requests:")
        self.number_of_requests_label.pack(pady=10)
        self.number_of_requests_entry = ttk.Entry(self.root, width=40)
        self.number_of_requests_entry.pack()
        
        self.request_type_label = ttk.Label(self.root, text="Request Type:")
        self.request_type_label.pack(pady=10)
        self.request_type_var = tk.StringVar()
        self.request_type_combobox = ttk.Combobox(self.root, width=37, textvariable=self.request_type_var)
        self.request_type_combobox["values"] = ["GET", "POST", "PUT", "DELETE", "HEAD", "TRACE", "CONNECT"]
        self.request_type_combobox.current(0)
        self.request_type_combobox.pack()
        
        self.cache_var = tk.IntVar()
        self.cache_checkbox = ttk.Checkbutton(self.root, text="Use Cache", variable=self.cache_var)
        self.cache_checkbox.pack(pady=10)
        
        self.send_request_button = ttk.Button(self.root, text="Send Request", command=self.send_request)
        self.send_request_button.pack(pady=20)
        
        self.cleanup_folder_path = ".Cache"
        self.root.protocol("WM_DELETE_WINDOW", self.on_closing)


    def send_request(self):
        try:
            number_of_requests = int(self.number_of_requests_entry.get().strip())
        except ValueError:
            messagebox.showerror("Error", "Number of Requests must be a valid integer.")
            return
        
        if number_of_requests <= 0:
            messagebox.showerror("Error", "Number of Requests must be greater than zero.")
            return
        
        for _ in range(number_of_requests):
            self.send_single_request()


    def send_single_request(self):
        host = self.host_entry.get().strip()
        request_type = self.request_type_var.get()
        use_cache = self.cache_var.get()
        subdomain = self.subdomain_entry.get().strip()
        
        print(f"Host: {host}")
        print(f"Request Type: {request_type}")
        print(f"Use Cache: {use_cache}")
        print(f"Subdomain: {subdomain}")
        
        if not host:
            messagebox.showerror("Error", "Host is required.")
            return
        
        if request_type == "POST":
            username = self.username_entry.get().strip()
            password = self.password_entry.get().strip()
            
            if not username or not password:
                messagebox.showerror("Error", "Username and Password are required for POST requests.")
                return
            
            request_body = f"username={username}&password={password}"
            print(f"Request Body: {request_body}")
        else:
            request_body = None
        
        try:
            result = subprocess.run(
                ["./bin/http_client", request_type, host, str(use_cache), subdomain, request_body or ""],
                capture_output=True,
                text=True
            )
            
            print(result.stdout)
            response_popup = tk.Toplevel(self.root)
            response_popup.title("Response")
            response_popup.geometry("600x400")
            
            response_frame = ttk.Frame(response_popup)
            response_frame.pack(expand=True, fill=tk.BOTH)
            
            response_text = result.stdout
            response_label = ttk.Label(response_frame, text=response_text, wraplength=600)
            response_label.pack(padx=10, pady=10, expand=True, fill=tk.BOTH)
            
            if request_type == "GET":
                self.root.after(3000, lambda: self.ask_to_open_local_web_page(host))
        
        except Exception as e:
            messagebox.showerror("Error", f"Failed to send request: {str(e)}")


    def ask_to_open_local_web_page(self, host):
        result = messagebox.askyesno("Open Web Page", "Do you want to open the downloaded web page?")
        if result:
            self.open_local_web_page(host)


    def open_local_web_page(self, host):
        local_file_path = os.path.join(self.cleanup_folder_path, f"{host}.html")
        print(f"Checking if file exists: {local_file_path}")  # Debug message
        if os.path.exists(local_file_path):
            print(f"Opening file: {local_file_path}")  # Debug message
            webbrowser.open(f"file://{os.path.abspath(local_file_path)}")
        else:
            print("File not found")  # Debug message
            messagebox.showerror("Error", "Local web page not found.")


    def cleanup_folder(self):
        folder_path = self.cleanup_folder_path
        if os.path.exists(folder_path) and os.path.isdir(folder_path):
            for filename in os.listdir(folder_path):
                file_path = os.path.join(folder_path, filename)
                try:
                    if os.path.isfile(file_path) or os.path.islink(file_path):
                        os.unlink(file_path)
                    elif os.path.isdir(file_path):
                        shutil.rmtree(file_path)
                except Exception as e:
                    print(f"Failed to delete {file_path}. Reason: {e}")


    def on_closing(self):
        self.cleanup_folder()
        self.root.destroy()



if __name__ == "_main_":
    root = tk.Tk()
    app = HttpClientApp(root)
    root.mainloop()