## Proiect: HTTP Client

Acest proiect implementează un client HTTP modular și extensibil, destinat gestionării cererilor și răspunsurilor HTTP/HTTPS. Utilizează conexiuni socket, suportă SSL și include funcționalități de cache, gestionarea cookie-urilor, timeout și autentificare pentru cereri POST, totul accesibil printr-o interfata in python.

### Structura Proiectului

- **HttpClientBase** - Interfață de bază pentru clasa de client HTTP.

- **HttpClient** - Moștenește `HttpClientBase` și implementează metoda `send_request`.
  - `send_request` utilizează o conexiune de tip socket (`SocketConnection`) pentru a trimite și primi cereri HTTP.

- **SocketConnection** - Gestionează conexiunile de rețea de tip socket.
  - Metode pentru a stabili conexiunea, a trimite și a primi date.

- **HttpRequest** - Reprezintă o cerere HTTP.
  - Metode pentru a formata corect cererea HTTP (metodă, host, headere, corp).

- **HttpResponse** - Reprezintă un răspuns HTTP.
  - Metode pentru a analiza răspunsul și a extrage corpul și headerele.

- **HttpsClient** - Moștenește `HttpClient` și implementează `send_request` pentru conexiuni securizate.
  - Utilizează o conexiune SSL (`SslConnection`) pentru servere HTTPS.

- **SslConnection** - Moștenește `SocketConnection` și adaugă suport SSL/TLS.
  - Metode pentru a gestiona conexiuni SSL, inclusiv trimiterea și primirea datelor.

- **CacheControl** - Gestionează directivele de cache pentru HTTP.
  - Permite adăugarea și recuperarea datelor de cache, setând și verificând timpul de așteptare pentru operațiuni.

- **CookieControl** - Gestionează cookie-urile pentru cererile HTTP.

### Funcționalități ale Metodelor HTTP

Proiectul include metode HTTP standard:
- `GET` - Preia informații de la server.
- `HEAD` - Similară cu `GET`, dar transferă doar statusul și headerele.
- `POST` - Transmite date către server (ex. încărcare fișier, autentificare).
- `PUT` - Înlocuiește reprezentările resurselor.
- `DELETE` - Șterge resursele curente.
- `CONNECT` - Creează un tunel de conexiune.
- `TRACE` - Testează transmiterea mesajelor.

### Actualizări de Funcționalitate

#### 20.06.2024
- **CookieControl** pentru gestionarea cookie-urilor.
- Metode HTTP suplimentare.

#### 21.06.2024
- **Interfață grafică**: Permite introducerea serverului și afișează răspunsul.
- **Cache Control**: Stochează datele într-un folder, șters la finalul sesiunii.

#### 25.06.2024
- **Cache GET**: Fișierele de cache sunt șterse și actualizate periodic.
- **Autentificare POST**: Suport pentru autentificare; parolele sunt citite din `passwords.txt`.

#### 26.06.2024
- Interfața permite selectarea protocolului HTTP sau HTTPS.
