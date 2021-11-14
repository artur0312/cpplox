#Program to create the file containing the astTree

#return the name of the class that is formated conform the classList below
def getClassName(s):
    name=s.split(':')[0]
    return name.strip()
#return a 2D list of the atributes, in each row the first column represents the type and the second one represents the name of the atribute
def getAttributesList(s):
    attributes=s.split(':')[1]
    attributes=attributes.strip()
    attributesList=attributes.split(", ")
    result=[]
    for attribute in attributesList:
        atrType=attribute.split(" ")[0]
        atrName=attribute.split(" ")[1]
        result.append([atrType,atrName])
    return result

#Takes an attribute of the form [type,name] and returns 'type name' with the correct format
#If it is an expression, returns the correct format to declare as a pointer
#Otherwise, return as a normal variable
def declareAttribute(attribute):
    if attribute[0]=="Expr":
        return attribute[0] +"<T> *" +attribute[1]
    else:
        return attribute[0]+" "+attribute[1]

#Returns a string with a comma separated list of the arguments formated by the declareAttribute function
def strAttributes(attributesList):
    result=""
    indexes=range(0,len(attributesList))
    for i in indexes:
        result+=declareAttribute(attributesList[i])
        if i!=len(attributesList)-1:
            result+=", "
    return result


#The classes that will be created
classList=["Binary : Expr left, Token op, Expr right",
        "Grouping : Expr expression",
        "Literal : Token value",
        "Unary : Token op, Expr right"]

#Everything needs to be on the header because I have templates
printer=open("./../../include/astTree.h","w")

printer.write("//The header defining the class for the astTree\n")

printer.write("#ifndef AST_TREE_H\n")
printer.write("#define AST_TREE_H\n")
printer.write("#include \"token.h\"\n")

printer.write("\n//Forward declaration of the classes\n")
for c in classList:
    printer.write("template <class T> class "+getClassName(c)+";\n")
printer.write('\n')

printer.write("//The Visitor class\n")
printer.write("template <class T>\n")
printer.write("class Visitor{\n")
printer.write("\tpublic:\n")
for c in classList:
    className=getClassName(c)
    printer.write("\t\tvirtual T visit"+ className +"("+className +"<T>)=0;\n")
printer.write("};\n")
printer.write('\n')

#The Expr class
printer.write("//See if Expr needs to be an template class or if only the function accept must be a template\n")
printer.write("template <class T=void>\n")
printer.write("class Expr{\n")
printer.write("\t//Expr can't be instantiated, but I can use pointers\n")
printer.write("\tpublic:\n")
printer.write("\t\tvirtual T accept(Visitor<T> &v)=0;\n")
printer.write("};\n\n")

for c in classList:
    className=getClassName(c)
    attributesList=getAttributesList(c)
    printer.write("template <class T=void>\n")
    printer.write("class "+className+": public Expr<T>{\n")
    printer.write("\tpublic:\n")
    #constructor
    printer.write("\t\t"+className+"(")
    printer.write(strAttributes(attributesList))
    printer.write("): ")
    for i in range(0,len(attributesList)):
        printer.write(attributesList[i][1] +"("+attributesList[i][1] +")")
        if i<len(attributesList)-1:
            printer.write(", ")
    printer.write("{\n\t\t}\n\n")
    
    #accept method
    printer.write("\t\tT accept(Visitor<T> &v){\n")
    printer.write("\t\t\treturn v.visit"+className+"(*this);\n")
    printer.write("\t\t}\n\n")

    #Declare the attributes
    for attribute in attributesList:
        printer.write("\t\tconst "+declareAttribute(attribute)+";\n")
    printer.write("};\n")

printer.write("\n")
printer.write("#endif")



