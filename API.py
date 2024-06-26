import os
import shutil
import tkinter as tk
from tkinter import ttk, messagebox, scrolledtext
import subprocess
import webbrowser

class HttpClientApp:
    def __init__(self, root):
        self.root = root
        self.root.title("HTTP Client Interface")
        self.root.attributes("-fullscreen", True) 

        self.style = ttk.Style()
        self.style.configure("TButton", background="#d9fad9", foreground="black")
        self.style.configure("TEntry", fieldbackground="white", foreground="black")
        self.style.configure("TNotebook.Tab", background="#d9fad9", foreground="black")

        self.root.bind("<Escape>", lambda event: self.exit_fullscreen()) 

        self.root.columnconfigure(0, weight=1)
        self.root.rowconfigure(0, weight=1)

        self.setup_ui()


    def setup_ui(self):
        main_frame = ttk.Frame(self.root, padding="10")
        main_frame.pack(fill=tk.BOTH, expand=True)
        main_frame.columnconfigure(0, weight=1)
        main_frame.rowconfigure(1, weight=1)

        http_methods_frame = ttk.Frame(main_frame)
        http_methods_frame.grid(row=0, column=0, sticky="ew")

        ttk.Label(http_methods_frame, text="Select Request Method:").pack(side=tk.LEFT, padx=10)

        self.request_type_var = tk.StringVar(value="GET")
        methods = ["GET", "POST", "PUT", "DELETE", "HEAD", "TRACE", "CONNECT"]
        for method in methods:
            ttk.Button(http_methods_frame, text=method, command=lambda m=method: self.set_request_type(m)).pack(side=tk.LEFT, padx=5)

        response_frame = ttk.Frame(main_frame, padding="10")
        response_frame.grid(row=1, column=0, sticky="nsew")

        ttk.Label(response_frame, text="Response:").pack(side=tk.TOP, anchor=tk.W)
        self.response_text = scrolledtext.ScrolledText(response_frame, wrap=tk.WORD, width=80, height=20, bg="white", fg="black")
        self.response_text.pack(side=tk.TOP, fill=tk.BOTH, expand=True)

        control_panel_frame = ttk.Frame(main_frame, padding="10")
        control_panel_frame.grid(row=0, column=1, rowspan=2, sticky="nsew")
        control_panel_frame.columnconfigure(0, weight=1)

        ttk.Label(control_panel_frame, text="Host:").grid(row=0, column=0, pady=5, sticky="ew")
        self.host_entry = ttk.Entry(control_panel_frame, width=40)
        self.host_entry.grid(row=1, column=0, pady=5, sticky="ew")

        ttk.Label(control_panel_frame, text="Protocol:").grid(row=2, column=0, pady=5, sticky="ew")
        self.protocol_var = tk.StringVar(value="http")
        ttk.Combobox(control_panel_frame, textvariable=self.protocol_var, values=["http", "https"]).grid(row=3, column=0, pady=5, sticky="ew")

        ttk.Label(control_panel_frame, text="File (/example.php | wordlist):").grid(row=4, column=0, pady=5, sticky="ew")
        self.subdomain_entry = ttk.Entry(control_panel_frame, width=40)
        self.subdomain_entry.grid(row=5, column=0, pady=5, sticky="ew")

        self.post_options_frame = ttk.LabelFrame(control_panel_frame, text="POST Options")
        self.post_options_frame.grid(row=6, column=0, pady=5, sticky="ew")
        self.post_options_frame.grid_remove()

        ttk.Label(self.post_options_frame, text="Username (if needed):").pack(pady=5)
        self.username_entry = ttk.Entry(self.post_options_frame, width=30)
        self.username_entry.pack()

        ttk.Label(self.post_options_frame, text="Password (if needed):").pack(pady=5)
        self.password_entry = ttk.Entry(self.post_options_frame, width=30, show="*")
        self.password_entry.pack()

        ttk.Label(control_panel_frame, text="Number of Requests:").grid(row=7, column=0, pady=5, sticky="ew")
        self.number_of_requests_entry = ttk.Entry(control_panel_frame, width=40)
        self.number_of_requests_entry.grid(row=8, column=0, pady=5, sticky="ew")

        self.cache_var = tk.IntVar()
        ttk.Checkbutton(control_panel_frame, text="Use Cache", variable=self.cache_var).grid(row=9, column=0, pady=5, sticky="ew")

        ttk.Button(control_panel_frame, text="Send Request", command=self.send_request).grid(row=10, column=0, pady=20, sticky="ew")

        self.cleanup_folder_path = os.path.join(os.getcwd(), "Cache")
        self.root.protocol("WM_DELETE_WINDOW", self.on_closing)


    def set_request_type(self, method):
        self.request_type_var.set(method)

        if method == "POST":
            self.post_options_frame.grid()
        else:
            self.post_options_frame.grid_remove()


    def send_request(self):
        self.response_text.delete('1.0', tk.END)

        if self.number_of_requests_entry.get() == "" or not self.number_of_requests_entry.get().isdigit():
            number_of_requests = 1
        else:
            number_of_requests = int(self.number_of_requests_entry.get().strip())

        if number_of_requests <= 0:
            messagebox.showerror("Error", "Number of Requests must be greater than zero.")
            return

        if number_of_requests > 1:
            for _ in range(number_of_requests):
                self.send_single_request(_)
            self.response_text.insert(tk.END, "\nRequests have been sent!\n\n")

        else:
            self.send_single_request(1)


    def send_single_request(self, iteration):
        protocol = self.protocol_var.get()
        host = self.host_entry.get().strip()
        request_type = self.request_type_var.get()
        use_cache = self.cache_var.get()
        subdomain = self.subdomain_entry.get().strip()
        
        if subdomain == "":
            subdomain = "wordlist"

        if not host:
            messagebox.showerror("Error", "Host is required.")
            return

        if request_type == "POST":
            username = self.username_entry.get().strip()
            password = self.password_entry.get().strip()

            if not username:
                messagebox.showerror("Error", "Username is required for POST requests.")
                return
            if password == "":
                password = "wordlist"
            request_body = f"username={username}&password={password}"
            print(f"Request Body: {request_body}")
        else:
            request_body = ""

        try:
            result = subprocess.run(
                ["./bin/http_client", protocol, request_type, host, str(use_cache), subdomain, request_body],
                capture_output=True,
                text=True,
                timeout=30
            )

            print(result.stdout)
            if iteration == 1:
                self.response_text.insert(tk.END, f"Request Type: {request_type}\n")
                self.response_text.insert(tk.END, f"Response:\n{result.stdout}\n\n")

            if request_type == "GET":
                self.root.after(2000, lambda: self.ask_to_open_local_web_page(host))
        
        except subprocess.TimeoutExpired:
            messagebox.showerror("Error", "The request timed out.")
        except Exception as e:
            messagebox.showerror("Error", f"Failed to send request: {str(e)}")


    def ask_to_open_local_web_page(self, subdomain):
        if self.cache_var.get() == 1:
            result = messagebox.askyesno("Open Web Page", "Do you want to open the downloaded web page?")
            if result:
                self.open_local_web_page(subdomain)


    def open_local_web_page(self, subdomain):
        local_file_path = os.path.join(self.cleanup_folder_path, subdomain + ".html")
        print(f"Checking if file exists: {local_file_path}")
        if os.path.exists(local_file_path):
            print(f"Opening file: {local_file_path}")
            webbrowser.open(f"file://{local_file_path}")
        else:
            print("File not found")
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
        try:
            self.cleanup_folder()
        except Exception as e:
            print(f"Error cleaning up: {str(e)}")
        self.root.destroy()


    def exit_fullscreen(self):
        self.root.attributes("-fullscreen", False) 
        self.root.geometry("1300x820+330+80")



if __name__ == "__main__":
    root = tk.Tk()
    app = HttpClientApp(root)
    root.mainloop()



