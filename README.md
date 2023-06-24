# JSONParser

* Search specifications
  * str\* - matches every word that begins with the given str
  * \*str - matches every word that ends with the given str
  * \*str\* - matches every word that contains the given str

* File saving specifications
  * files will always be in folder InputFiles

* Commands

Command list     | Description                         |Syntax                        
---------------- | ----------------------------------- |------------------------------
open             | opens file                          |open \<filename\>               
print            | print file on console               |print                         
search           | search by key                       |search \"key\"                
set              | set json value on path              |set \"path\" \"json\"         
create           | creates new object on given path    |create \"path\" \"json\"      
delete           | deletes object on path              |delete \"path\"               
move             | moves object to another path        |move \"pathFrom\" \"pathTo\"  
save             | saves json on path as same file     |save \"path\"                 
saveas           | saves json on path as new file      |saveas \"path\" \<filename\>    
exit             | exit console                        |exit                          
  
* Examples for commands:
  * open json.txt
  * set "management/directorId" "44"
  * set "management/directorId" 0.76
  * set "management/directorId" true
  * create "name/created" "{"name":"value1","address":"value2"}"
  * create "management/presidentId/president2" ""president2""
  * search "add*"
  * search "ress*"
  * search "*dres*"
  * search "address"
  * delete "management"
  * delete "management/directorId"
