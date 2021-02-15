# CTFs
## A little something to get you started

1. If you play around in the CSS, one of the elements has a background-image set, and that `background.png` has a flag in it.

## Micro-CMS 1

0. Page 6 has "forbidden" on it so it's a bit suss. You can go to edit another page, and then manipulate it to point to 6 and you get a flag.
1. You can put a `'` at the end of the edit page and you'll do a SQLi and get a flag.
2. Use XSS in the title field of a page and then head back to the main listing.
3. There's a button on one of the pages. You can add a click handler to it like `onclick="alert(1)"` and then in the HTML you see a nice flag for you.

## Micro-CMS 2

0. If you try and login as `admin'` you get a helpful stack trace telling you that we're using MariaDB, but also that the query is very simple like `SELECT password FROM admins WHERE username=...`.
if you go `admin' OR 1='1 --` in the username field it tells us 'invalid password' instead of 'unknown user' so we can probably use this.
ahh, so you can do this as the username `' UNION SELECT '123' AS password#` and `123` as password.
there's then a private page you can access that has a flag
1. If you copy the request that edits a page into Repeater in Burp and remove the cookie, you can edit the page and you'll get a flag in the response.
2. You can try and smash through a password list to find the password, but its hard when im time throttled on burp... username `' OR 1=1#`. not sure what the password is, but i think this is how you'd get in.

## Petshop Pro

0. You can take the cart request and change the prices to 0 and its all freeeee and theres a flag. The decoder/encoder tools in burp are really helpful for this
1. there's an admin page at /login. I'm trying to use Hydra to figure it out `hydra -f -L names.txt -p password 35.190.155.168 http-post-form "/06ebc0147c/login:username=^USER^&password=^PASS^:Invalid username"`, you can do the same with `rockyou.txt` to get the password. at the time for me it was `lilla` and `smother` .
2. On the admin page you can edit a listing, and pop an XSS into the name and see it in the cart and there you go.

## Cody's First Blog

0. So you can include some PHP code in the input box and you get a flag. So like `<?php echo "uh oh"; ?>`
1.  There's a vulnerability with this version of PHP that lets you delete the `auth` part from `?page=admin.auth.inc` and get straight to the admin page. Pretty lol.
2. "Cody" if that is his real name, likes the PHP include functionality. You can go to `http://35.227.24.107/8454a796d7/?page=http://localhost/index` after you've approved a comment of `<?php echo readfile("index.php"); ?>` and you'll get a flag and the contents of the php file will be in the HTML. nice.

## Image Gallery

0. You can go here `fetch?id=4 UNION SELECT 'main.py'--` and you get a main.py with the flag.
1. Well, a basic query for this might be like `SELECT * FROM photos where id=1`. So, maybe I can do an injection in here if they're just grabbing the id? One of the hints is the docker container, and a example for this has a `main.py` and a `uwsigi.ini` file.
   1. Running `sqlmap -u "http://34.94.3.143/35ee54c62d/fetch?id=1" --dbs` gave us some info about the available databases, they all look pretty standard except for one called `level5`. 
   2. Running this `sqlmap -u "http://34.94.3.143/35ee54c62d/fetch?id=1" --tables -D level5` gives us the tables `albums` and `photos`
   3. Running this `sqlmap -u "http://34.94.3.143/35ee54c62d/fetch?id=1" --dump -D level5 -T photos` gives us a dump of the info from the table which is really cool. The flag is the filename of the third file. Super cool.
2. The function to get "space used" seems a bit suss. The command used is this `subprocess.check_output('du -ch %s || exit 0' % ' '.join('files/' + fn for fn in fns), shell=True, stderr=subprocess.STDOUT).strip().rsplit('\n', 1)[-1]`
   1. This seems like it's checking the output of this command `'du -ch %s || exit 0' % ' '.join('files/' + fn for fn in fns`

## Postbook

0. `user` `password` gets you right in
1. When you create a post, there's a hidden field that lets you be somebody else
2. Editing isn't secure, so you can change the ID of the post.