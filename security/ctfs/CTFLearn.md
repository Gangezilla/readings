# <https://ctflearn.com>

## Basic Injection

Can get all users by typing Luke' OR 1='1, reveals a flag of th4t_is_why_you_n33d_to_sanitiz3_inputs

## Binwalk

`binwalk -e <image>` will give us extracted stuff from the image but zlib doesnt work lol.
So I used CyberChef <https://gchq.github.io/CyberChef/> and the recipe Extract Files and you get the flag `ABCTF{b1nw4lk_is_us3ful}`
