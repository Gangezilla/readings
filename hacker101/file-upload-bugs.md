# File Upload Bugs

Heaps of ways uploads can be handled improperly.

Multi part POSTs used for file uploads. Header looks like a normal POST except for the content type. 

```
Content-Type: multipart/form-data; boundary=------Boundary1234

-----Boundary1234
...

-----Boundary1234
```

The most obvious way to break this is via filename. If you upload a file and see any part of the filename remain, theres a good chance you can manipulate it. For example, directory traversal works well here. What if you upload a file called "../../test.php"

## MIME Types

Often the MIME type sent by the browser is stored in DB and then sent back to the browser. If this is sent down with the file when it's accessed, this can allow XSS attacks if you edit the MIME type.

## Sniffing

Even a totally valid image can be a vuln. PNGs for instance can contain arbitrary chunks that are valid and ignored by the file loader. This allows you to embed any HTML file into a PNG while maintaining a completely proper file.

### Separate domains

Files uploaded by users shouldn't be hosted on your site. If they're hosted on your site, SOP dictates that any JS that is there could access and manipulate the site. 

### Generate filenames

Filenames should never come from a user directly. You should also have a whitelist for file types.

### Type and Disposition

MIME types should be strictly whitelisted. 

### Image stripping

When you accept an image you should remove EXIF data from JPEGs, ancilary chunks from PNG files and all other extraneous data. These spots are great hiding spots for HTML and other malicious content. Removing this data is the only safe route.

### Generalized

User cannot be trusted. Throw away any non-essential data. Any extra bit of data could be used for input.

Don't trust anything you don't have to.