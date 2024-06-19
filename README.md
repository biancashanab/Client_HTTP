# Client_HTTP

 # 17.06.2024

    - am ales tema proiectului

 # 18.06.2024

    -> HttpClientBase      - interfata
    -> HttpClient          - mosteneste clasa HttpClientBase si implementeaza metoda send_request 
                           - send_request este suprascrisa pentru a utiliza o conexiune de tip socket (SocketConnection) pentru a trimite si a primi cereri HTTP
    -> SocketConnection    - gestioneaza conexiunile de retea de tip socket
                           - metode pentru a stabili conexiunea, a trimite si a primi date pe socket
    -> HttpRequest         - reprezinta o cerere HTTP
                           - metode pentru a formata corect o cerere HTTP (metoda, host, headere, corp)
    -> HttpResponse        - reprezinta un raspuns HTTP primit de la server
                           - metode pentru a analiza raspunsul si a extrage corpul si headerele
                        
 # 19.06.2024

    -> HttpsClient         - mosteneste clasa HttpClient si implementeaza, de asemenea, metoda send_request pentru secure
                           - utilizează o conexiune SSL (SslConnection) pentru a se conecta la servere HTTPS
    -> SslConnection       - mosteneste SocketConnection si adauga suport pentru conexiuni securizate SSL/TLS
                           - metode pentru a gestiona conexiuni SSL, cum ar fi conectarea, trimiterea si primirea datelor
    -> TimeoutManagement   - gestioneaza timpul de asteptare pentru operatiuni
                           - permite setarea unui timp de asteptare si verificarea daca acesta a expirat

    -> CacheControl        - gestioneaza directivele de cache pentru HTTP
                           - permite adaugarea si recuperarea directivelor de cache
