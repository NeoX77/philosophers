# 🖱 42Paris Project | philosophers

## Objectives

The goal of this project is to understand how threads is working.  
The projet takes the situation of 1 or more philosophers around a table that have a large bowl of spaghetti in the middle.  
The philosophers alternatively **eat**, **think**, or **sleep**.  
While they are eating, they are not thinking nor sleeping;  
while thinking, they are not eating nor sleeping;  
and, of course, while sleeping, they are not eating nor thinking.  
To eat in the bowl they have forks but there are as many forks as philosophers. To eat, every philosophers have to takes their right and left hand fork.  

![image](https://user-images.githubusercontent.com/16923245/235950289-c376ab4c-4ac2-48ba-820e-4fb54c198043.png)

## Usage

`make` to compile the program.  
`clean` to clean objects files.  
`fclean` to clean objects files and program file.  

**Execute**: `./philosophers` `number_of_philosophers` `time_to_die` `time_to_eat` `time_to_sleep` `number_of_times_each_philosopher_must_eat (optional)`

## Help

All variables that can be accessed by two threads at the same time have to be protected with a mutex to avoid dataraces and leaks.  
This [link](https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/ "link") explain how it works.
