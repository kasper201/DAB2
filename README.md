# DAB2

In this repository the program to load the database with up-to-date data from Formula 1 races can be found.
The code for the webpage was mostly written without prior experience with HTML, PHP, CSS and JavaScript, so it isn't the most efficient or clean code.

## How to run the importing program
The program is written for Linux systems and has been tested on Arch based systems.
It should work on other Linux distributions, but it hasn't been tested.
In theory, it could also work for windows but I didn't get that to work.

To run the program you need to have CURL installed.

# One Time data pulling
To pull data from existing databases one can use the program of which the code is supplied in this repository. 

## Important
- Check that the file `listcountries.csv` is in the same folder as the executable 
- Check that the file `CountrieCodes.csv` is in the same folder as the executable

# Installation
Before the installation starts it is assumed that XAMPP, a MYSQL IDE and C++ IDE are already installed.

## Change website folder
To change the website folder look for `DocumentRoot "/your/directory"` and change the directory there with the one you have the root of the webpage in. Do that in `<Directory ` just below it as well.

## building the DataBase
If creating the tables and views gets stuck first check the order in which you create these. For example create the functions before the views.
If you still have trouble it might be necessary to upgrade the mysql server.

## MYSQL Password forgotten
If you have forgotten your MYSQL password you can reset it by doing the following:
```mysql
    USE mysql;
    UPDATE user SET password=PASSWORD('new_password') WHERE user='root';
    FLUSH PRIVILEGES;

```
**Important** This changes the password for the root user globally.
