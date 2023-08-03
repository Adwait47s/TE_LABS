create_database (){
    if [  -f "student.db"  ]; then
        echo "Database already exists."

    else
        touch student.db
        echo "Database created successfully."
    fi
}

display_options() {
    echo "Options:"
    echo "a) Create database"
    echo "b) View database"
    echo "c) Insert a record"
    echo "d) Delete a record"
    echo "e) Modify a record"
    echo "f) Exit"
}

view_database(){
		cat student.db
}

insert_record() {
		echo "Enter roll number:"
    read rollno
    
    echo "Enter the student's name:"
    read name

    echo "Enter marks1:"
    read marks1

    echo "Enter marks2:"
    read marks2
		
		echo "Enter marks3:"
    read marks3
    
    echo "Enter city:"
    read city

    echo ">$rollno|$name|$marks1|$marks2|$marks3|$city|" >> student.db
    echo "Student record added successfully!"
}

delete_record() {
    echo "Enter the roll number to delete:"
    read rollno

    if [ -f "student.db" ]; then
        grep -i -v ">$rollno|" student.db > tmpfile 
        mv tmpfile student.db
        echo "Student record deleted successfully."
    else
        echo "Database not found. Create one first."
    fi
}

modify_record() {
    echo "Enter the roll number to modify:"
    read rollno

    if [ -f "student.db" ]; then
        
        echo "Please enter your new roll no :"
        read newrollno
        sed -i "s/$rollno/$newrollno/g" student.db
       
    else
        echo "Database not found. Create one first."
    fi
}

while true; do
		display_options
		
    echo "Enter your choice (a/b/c/d/e/f):"
    read choice

    case "$choice" in
    
        a) create_database;;
        
        b) view_database;;
            
        c) insert_record;;
            
        d) delete_record;;
            
        e) modify_record;;
            
        f)  echo "Exiting the program."
            break;;
            
        *) echo "Invalid choice. Please try again.";;
    esac
done
