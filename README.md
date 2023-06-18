# JSONParser

* Search specifications
  * str\* - matches every word that begins with the given str
  * \*str - matches every word that ends with the given str
  * \*str\* - matches every word that contains the given str

* File saving specifications
  * files will always be in folder InputFiles

Markup : *Commands

Command list:   |Description                        |Syntax:                       
-----------------------------------------------------------------------------------
open            |opens file                         |open <filename>               
print           |print file on console              |print                         
search          |search by key                      |search \"key\"                
set             |set json value on path             |set \"path\" \"json\"         
create          |creates new object on given path   |create \"path\" \"json\"      
delete          |deletes object on path             |delete \"path\"               
move            |moves object to another path       |move \"pathFrom\" \"pathTo\"  
save            |saves json on path as same file    |save \"path\"                 
saveas          |saves json on path as new file     |saveas \"path\" <filename>    
exit            |exit console                       |exit                          
  
