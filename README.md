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

 # 20.06.2024
    
    -> CookieControl       - gestioneaza cookie-urile pentru cererile HTTP

    - adaug metodele de request HTTP si pot fi:

      GET - Aceasta metoda este folosita pentru a prelua informatii de la un anumit server, pe baza unui URI
      HEAD - Aceasta metoda seamana cu GET, dar transfera doar o linie de status si sectiunea de Header
      POST - Metoda POST produce transmiterea de date către server. Spre exemplu, informațiile utilizatorului, încărcarea unui fișier, etc
      PUT - Metoda PUT produce înlocuirea tuturor reprezentărilor resurselor cu un anumit conținut
      DELETE - Sterge reprezentarile curente din resursele serverului, pe baza unui URI
      CONNECT - Stabileste un tunel de conexiune cu serverul
      OPTIONS - Descrie optiuni de comunicare cu resursele
      TRACE - Folosit pentru testarea trabnsmiterii mesajelor, generand si calea catre resurse
