import os
import shutil
import tkinter as tk
from tkinter import ttk
from tkinter import messagebox
import subprocess
import webbrowser
import time

class HttpClientApp:
    def __init__(self, root):
        self.root = root
        self.root.title("HTTP Client Interface")
        self.root.geometry("400x250")
        
        self.host_label = ttk.Label(self.root, text="Host:")
        self.host_label.pack(pady=10)
        self.host_entry = ttk.Entry(self.root, width=40)
        self.host_entry.pack()
        
        self.request_type_label = ttk.Label(self.root, text="Request Type:")
        self.request_type_label.pack(pady=10)
        self.request_type_combobox = ttk.Combobox(self.root, values=["GET", "POST", "HEAD", "PUT", "DELETE", "CONNECT", "TRACE"], width=37)
        self.request_type_combobox.pack()
        
        self.cache_var = tk.IntVar()
        self.cache_checkbox = ttk.Checkbutton(self.root, text="Use Cache", variable=self.cache_var)
        self.cache_checkbox.pack(pady=10)
        
        self.send_request_button = ttk.Button(self.root, text="Send Request", command=self.send_request)
        self.send_request_button.pack(pady=20)
        
        self.cleanup_folder_path = "/home/bianca/Client_HTTP/Cache"
        self.root.protocol("WM_DELETE_WINDOW", self.on_closing)


    def send_request(self):
        host = self.host_entry.get().strip()
        request_type = self.request_type_combobox.get().strip()
        use_cache = self.cache_var.get()
        
        if not host or not request_type:
            messagebox.showerror("Error", "Host and Request Type are required.")
            return
        
        try:
            result = subprocess.run(
                ["/home/bianca/Client_HTTP/bin/http_client", request_type, host, str(use_cache)], 
                capture_output=True, text=True
            )
            response_text = result.stdout
            response_popup = tk.Toplevel(self.root)
            response_popup.title("Response")
            response_popup.geometry("600x400")
            
            response_frame = ttk.Frame(response_popup)
            response_frame.pack(expand=True, fill=tk.BOTH)
            
            response_textbox = tk.Text(response_frame, wrap=tk.WORD)
            response_textbox.pack(expand=True, fill=tk.BOTH)
            response_textbox.insert(tk.END, response_text)
            
            # Dacă cererea este de tip GET, adaugă un buton pentru a deschide fișierul web local
            if request_type == "GET":
                self.root.after(3000, lambda: self.ask_to_open_local_web_page(host))  # Așteaptă 3 secunde înainte de a afișa pop-up-ul

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



if __name__ == "__main__":
    root = tk.Tk()
    app = HttpClientApp(root)
    root.mainloop()
