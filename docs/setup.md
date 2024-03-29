## markdown syntax basics
use 1~6 #'s to represent header_1 ~ header_6\
use *asterisks* or _underscore_ to italicize\
use **double_asterisks** or __double_underscores__ to bold\
use '- * +' for unordered lists; use numbers otherwise

Use links like below:  
[rt-preempt-docs](https://github.com/upoque/rt-preempt-docs)  
Or just: https://github.com/upoque/rt-preempt-docs  
images done similarly

Inline a code by using ``\
Highlight a code by using triple ` and by specifying the language
```java
public static void main(String args[]){
    System.out.println("Hello World!");
}
```

Use quotes by using '>'\
Use three hyphes for a horizontal line  

src: https://heropy.blog/2017/09/30/markdown/

## ubuntu package manager
apt-get
```
apt-get update (repository url update)  
apt-get upgrade (NEVER use this)
apt-get install package
apt-get remove package
```
Upon denied permission: !! - previous command (bash feature)
```
sudo !! 
```
apt-cache: searches through packages with the given key
```
apt-cache search key
```
(-dev: full package, -doc: documents, ...)

for more information on apt-get
```
apt-get -h
```

vim - text editor (cross-platform)  
sublime text  
vs code  

**Some Shortcut Commands**  
open terminal:  
ctrl-alt-t  
shift-insert (paste)  
ctrl-alt-1: lock screen  
ctrl-alt-del: log out  
ctrl-alt-up/down/left/right: switch between workspaces  


## git basic commands
Configure user  
```
git config --global user.name "Jaeseung Park"  
git config --global user.email "jadenpark98@gmail.com"  
```
Configure push options:  
simple: only the current branch  
matching: all local and remote branches with the same name
```
git config --global -push-default matching ??
```
To view all the config settings: 
```
git config --list
```

clone
```
git clone https://github.com/upoque/rt-preempt-docs.git
```
add  
```
git add <filename>
```
commit; commit any added files with '-a'
```
git commit -m "Msg"
git commit -a
```
  
push; --all to push all branches
```
git push
git push origin master
git push --all origin
git push origin :<branchname>
```  
pull
```
git pull
git merge <branchname>
```  
reset; fetch the latest history from the master branch  
```
git reset --hard origin/master
```

etc
```
git grep "directory"
git status
git init
```

## Etc
1. Networks & Port Forwarding
    - Navigate into the router's IP address
    - Manage Network -> Inner Network Settings
        - Configure the IP addresses appropriately
    - NAT/Router Settings -> Port Forwarding Settings
        - External Port: 2222
        - Internal Port: 22
2. SSH Servers
    * Remotely connect to Ubuntu machine
    - sudo apt install openssh-server
    - sudo systemctl status ssh
        - Need to see Active: active (running):
    - sudo ufw allow ssh
        - Ubuntu firewall
    * Connect to SSH Over Internet
        * Use Public IP address and accept data from port 22 to send it to Ubuntu machine
    - ssh username@ip_address
        - log in 
3. PuTTY
    - Work remotely from Windows
        - Set up from external/internal ports as appropriate
