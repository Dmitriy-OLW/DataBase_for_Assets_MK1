CREATE DATABASE OLW_Assets_and_Models;
GO

USE OLW_Assets_and_Models;
Go

CREATE TABLE Assets(ID int IDENTITY PRIMARY KEY, name varchar(30), Categoty_id varchar(30));


INSERT into Assets Values ('SCK', 'Space'), ('Aurora', 'Shuter'), ('Sample', 'CutScene');
SELECT * FROM Assets;

ALTER TABLE Assets ADD ImagePath varchar(MAX);
ALTER TABLE Assets ADD Date date;

CREATE TABLE chart
(
Month int IDENTITY,
CountWorkDay float
);

INSERT into chart Values (7, 14), (8, 20), (9, 28), (10, 15), (11, 5);

SELECT * FROM chart;

INSERT INTO chart (CountWorkDay) VALUES
(22), 
(17), 
(9), 
(25), 
(3), 
(19),
(14), 
(20), 
(28), 
(15), 
(5),
(0);


INSERT INTO Assets  VALUES
('NeoFPS', 'FPS'),
('SCK', 'Space'),
('Aurora', 'FPS'),
('Sample', 'Space'),
('SpaceFighter', 'Space'),
('Infinity', 'Space'),
('Build_13', 'Space'),
('Sci-Fi-vfx', 'VFX'),
('Partical_System', 'VFX'),
('Logitech', 'System'),
('2DOF', 'System');



--��������� category � ��������� ������� 
SELECT DISTINCT Categoty_id AS name -- ������ ���������� �������� 
INTO category                    -- �������� � ����� ������� 
FROM Assets 
ORDER BY name; 
 --���������� ������� � ���������� ����� 
ALTER TABLE category ADD id INT IDENTITY PRIMARY KEY; 
 --���������� ������� � ������� product 
ALTER TABLE Assets ADD catID INT; 
 --���������� ������� catID ���������� 
UPDATE Assets SET catID = (SELECT id FROM category  
WHERE Assets.Categoty_id = name); 
 --�������� ������� category �� ������� product 
ALTER TABLE Assets DROP COLUMN Categoty_id; 
 --���������� ����� ����� ����� �������� � product 
ALTER TABLE Assets  
ADD CONSTRAINT FK_product_category  
FOREIGN KEY (catID) REFERENCES category (id);
--�������� 
SELECT *  
FROM Assets a inner join category b  
ON a.Categoty_id = b.name; 

SELECT * FROM category;


ALTER TABLE Assets ADD Categoty_id varchar(30); 

DELETE FROM Assets WHERE catID IS NULL;