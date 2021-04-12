# CMPE382 Project #1 | Atakan SEVİNÇLİ & Öykü Çise Bilik


## How to Run

1) Extract zip file. 
2) To compile our shell program type -> `./MAKEFILE`
3) `shell` is our shell program. There are two ways to run our shell program such as Interactive and Batch Modes.
4) To run in Interactive mod type `./shell`
5) To run in Batch mod type `./shell {filename}`


## Design overview

 In this project we implement a shell which is run in two different ways such as Interactive and Batch Modes. In interactive mode our shell print a prompt as a string `ATAKAN@OYKU:>` and user type some commands (i.e. 'ls -l','pwd',cat file ...) and shell execute them according to some rules that will explain in the rest of the readme file. In batch mode our shell read given file line by line and execute them according to some rules like in interactive mode. Basicly our shell parse given commands and execute them in that rules : input commands may contain (|) and (;) characters. 
 
There are three cases : <br>
**1)** input contains only (;) <br>
**2)** input contains only (|) <br>
**3)** input contains (;) and (|) both. <br>
**4)** input does not contain anything <br>
In first case , we just parse them according to (;)  and send all of them to threads.
In second case , we just parse them according to (|)  and send all of them to system.
In third case ; First of all , we parse them according to (|).
                Secondly, We check that Does the splitted inputs according to (|) contains any (;).
                So, if contains (;) then we parse them and send to the threads if not contains send them to directly system.
In fourth case , shell continue to running.



## Complete Specification

The program will continue to execute the commands even if there are invalid commands on the line beacuse we are using system() parameters.

✔ `|` ,  `;`  , ` `   // if you just type this commands, all are valid and shell does not print any messages.

✔ `lss a;touhhc b;mkdddar c;mkdir d`   //first three commands are invalid so our shell program print an error messages `command not found`, but the last is valid.

✔ `;;;;;;;;;ls -l|||| pwd`  // there are semicolons at the start, but “ls -l” will execute with no problem

✔ ` | ls -l ` // piping works without problems

✔ quit command in interactive mode : `ls -l ; cat file1.txt | quit ` this command is valid  `ls -l ` and `cat file1.txt` send to the thread because of the semicolons and program stop the running. 

✔ quit command in batch mode : as in interactive mod , In batch mod when shell meets the `quit` command 



## Known bugs or problems

If you use `cat {filename}` commands in our shell program and if your file does not contain `\n` character end of the file, So our shell prompt like this 
-->  , assume that file end with "asdf"  string, "asdfATAKAN@OYKU:>"

Our shell program does not work with `cd` command.
