# Unchecked Redirects

An unchecked redirect is when a web app performs a redirect to an arbitrary URL outside the application.

This can look totally useless, but can be useful as an attacker. An attacker could create an identical clone of your site, but instead of authneticating against your DB she just dumps your login credentials to a file then redirects to the legit site. This means an attacker could send victims a link to your site, which then sends them to the evil site to steal crednetials. 

ANy time you see a redirect, look for the origin of the destination. Often these will come from a user session in a way thats unexploitable. If it's coming from the browser in an unsafe way, say as part of a CSRFable POST you probably can exploit it.

You could mitigate this by removing protocol specification, or getting rid of this entirely.