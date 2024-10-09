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
- tested mysql/mariaDB version: 10.4.32-MariaDB

# Installation

Before the installation starts it is assumed that XAMPP, a MYSQL IDE and the C++ IDE are already installed.

## Change website folder

To use the website one has to change the folder the apache server uses to host the website. This can be done in by doing the following:

Start XAMPP Manager and go to Manage Servers. Then click on Apache Web Server and then Configure. Click on Open Conf File and look for `DocumentRoot "/your/directory"`. Here you can change the directory to the one you have the root of the webpage in. Also do that in `<Directory ` just below it. Then save it.

## Starting 

To start the website and database first open XAMPP Manager and go to Manage Servers. Then click on `MySQL Database` and click on `Start`. Do the same for `Apache Web Server`. 
Congratulations! The website now runs on your localhost. To find the page go to localhost in your browser and open the login page. the login codes are
username: User1
password: password

if this doesn't work continue to MYSQL Password forgotten.

## building the DataBase

To load the database first make sure to run a mysql server. In this case make sure that the schema has the same name as used in [this](https://github.com/kasper201/DAB2/blob/main/webpage/php/login.php) github file. If left unchanged this is ``test`` This is to connect the database to the webinterface.

### MYSQL Password forgotten

If you have forgotten your MYSQL password you can reset it by doing the following:
```mysql
    USE mysql;
    UPDATE user SET password=PASSWORD('new_password') WHERE user='root';
    FLUSH PRIVILEGES;

```
**Important** This changes the password for the root user globally.

## initialising the schema
To initialise the schema do the following in order:
1. tables
2. procedures
3. createViews
4. functions
5. triggers
6. createWebViews
7. inserts

Make sure that casing matches the casing from the inserts. This might change per version and there is a slight chance that this is mismatched causing errors in steps 4, 6 and/or 7. Step 7 is leading and its casing is always correct!
If you still have trouble it might be necessary to upgrade the mysql server since older versions might not react as expected.

# updating

To update several methods can be used. One could update from the backend. This is only adviced for major updates. Minor updates can be done through the webUI. 

# issues
For issues contact Kasper at the email linked in the hosts github or create an issue in this repository.
