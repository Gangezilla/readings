# Clickjacking

The most common form of this is an ad covered page with what looks like a video player in the page. When someone clicks the like button, they've really just clicked the like button.

The page you want to control is embedded in an IFrame. By enticing someone to click this link you can do make other stuff happen.

Clickjacking is usually just an oversight not a security problem.

The best mitigation is X-Frame-Options which will stop someone from embedding your page and therefore attacks.