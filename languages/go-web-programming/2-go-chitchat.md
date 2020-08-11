# Go ChitChat

## Application design

A client sends a request, and a server responds to it. ChitChat's app logic is coded in the server, while the client triggers the requests and provides the data to the server.

When the request reaches the server, a multiplexer will inspect the URL and redirect the request to the correct handler.

## Data model

ChitChat's data model is simple and consists of four data structures:

- User: Representing the forum user's info
- Session: Representing a user's current login session
- Thread: Representing a forum thread
- Post: Representing a post within a thread

## Receiving and processing requests

### The multiplexer

`mux.HandleFunc('/', index)` this takes the URL as the first param, and the name of the handler function as the second param.

You can also use the multiplexer to serve static files. You can do this like:

```go
files := http.FileServer(http.Dir("/public"))
mux.Handle("/static/", http.StripPrefix("/static/", files))
```

Here we tell the server for all URLs with /static/ to remove /static/ from the URL and then look for a file with the name starting at the public directory. For example, if there’s a request for the file `http:// localhost/static/css/bootstrap.min.css` the server will look for the file `<application root>/css/bootstrap.min.css`

## Handler functions

Handler functions are functions that take a `Response-Writer` as the first param, and a pointer to a `Request` as the second.

We use the `Template` struct from the html/template standard library.

### Access control using cookies

Once the user logs in, you indicate that they've logged in by writing a cookie to the response header. We check this with our authenticate function

```go
func authenticate(w http.ResponseWriter, r *http.Request) {
  r.ParseForm()
  user, _ := data.UserByEmail(r.PostFormValue("email"))
  if user.Password == data.Encrypt(r.PostFormValue("password")) {
    session := user.createSession()
    cookie := http.Cookie{
      Name: "_cookie",
      Value: session.Uuid,
      HttpOnly: true,
    }
    http.SetCookie(w, &cookie)
    http.Redirect(w, r, "/", 302)
  } else {
    http.Redirect(w, r, "/login", 302)
  }
}
```

Now that we have the cookie in the browser, we want to check in the handler if the user is logged in. We do this by creating a session function:

```go
func session(w http.ResponseWriter, r *http.Request) (sess data.Session, err error) {
  cookie, err := r.Cookie("_cookie")
  if err == nil {
    sess = data.Session{Uuid: cookie.Value}
    if ok, _ := sess.Check(); !ok {
      err = errors.New("Invalid session")
    }
  }
}
```

This function gets the cookie from the request, and then (assuming theres no error) then checks the DB to see if the session ID exists. If it does, we check that its valid and return it.