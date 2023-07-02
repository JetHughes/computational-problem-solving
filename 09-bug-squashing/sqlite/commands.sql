-- How to use:
-- Open a terminal and cd into the folder with this sqlite3.def and sqlite3.dll
-- Copy and paste each of these commands into the terminal.
-- See clientDB_demo.mp4 for a video demonstration

sqlite3 clients.db

CREATE TABLE clients (
  clientID int NOT NULL PRIMARY KEY,
  firstname varchar(80) NOT NULL,
  lastname varchar(80) NOT NULL,
  phone_number varchar(80) NOT NULL,
  email_address varchar(80) NOT NULL
);

INSERT INTO clients (clientID, firstname, lastname, phone_number, email_address)
VALUES
(1,'Bugs', 'Bunny', '64213567890', 'bugs.bunny@toontown.com'),
(2,'Daisy', 'Duck', '64123456789', 'daisy.duck@duckworld.net'),
(3,'Tom', 'Cat', '64234567890', 'tom.cat@catmousefun.org'),
(4,'Jerry', 'Mouse', '64012345678', 'jerry.mouse@catmousefun.org'),
(5,'Mickey', 'Mouse', '64123409876', 'mickey.mouse@disneyland.co'),
(6,'Minnie', 'Mouse', '64098765432', 'minnie.mouse@disneyland.co'),
(7,'Scooby', 'Doo', '64123490234', 'scooby.doo@mysteryincorporated.tv'),
(8,'Pink', 'Panther', '64056712345', 'pink.panther@coolcats.club'),
(9,'Felix', 'Cat', '64123456732', 'felix.cat@vintagecartoons.net');

SELECT * FROM clients;

SELECT * FROM clients ORDER BY firstname;

select firstname from clients where lastname = 'Mouse';