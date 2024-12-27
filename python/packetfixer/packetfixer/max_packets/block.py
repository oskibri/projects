import re

code = """
function example() {
    let x = 10;
    let y = 20;
    console.log(x + y);
}
some other code;
"""

code2 = """INSERT INTO `simple` VALUES (49,'Snibri',99,NULL,'snibri'),
(50,'Bennis',34,NULL,'snibri'),(51,'Oskibri',30,NULL,'snibri'),
(61,'gibbgibb',99,NULL,'snibri'),(62,'subsni',99,NULL,'snibri'),(63,'happy',99,NULL,'snibri'),(64,'sepsni',99,NULL,'snibri'),(65,'gabb',99,NULL,'snibri'),(66,'gbb',99,NULL,'brebbi'),(67,'anothername',45,NULL,'something'),(68,'longnameentry',23,NULL,'example'),(69,'exampleuser',56,NULL,'test'),(70,'demonstration',44,NULL,'showcase'),(71,'randomuser',22,NULL,'random'),(72,'anotherentry',31,NULL,'sample'),(73,'addition',27,NULL,'insert'),(74,'extra',33,NULL,'addition'),(75,'moredata',28,NULL,'info'),(76,'sampletext',99,NULL,'data'),(77,'username',54,NULL,'reference'),(78,'placeholder',29,NULL,'filler'),(79,'testuser',32,NULL,'insert'),(80,'dataentry',36,NULL,'storage'),(81,'record',47,NULL,'database'),(82,'entrypoint',51,NULL,'values'),(83,'testing',38,NULL,'entry'),(84,'extralongname',43,NULL,'overflow'),(85,'additional',25,NULL,'data'),(86,'recordname',37,NULL,'information'),(1,'s',0,NULL,'i');
"""

with open("code.txt", 'r') as file:
    code = file.read()

# Regex to match a block of code within braces, regardless of lines
match = re.search(r'(INSERT.*?\);)', code, re.DOTALL)

if match:
    print(match.group(1))  # Output: content of the code block within `{ }`
else:
    print("No match found")

