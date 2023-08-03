create_database (){
    if [ -f "student.db" ]; then
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

view_database() {
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
        if grep -q -i ">$rollno|" student.db; then
            echo "Student record found. What do you want to modify?"
            echo "1) Roll No"
            echo "2) Other fields"
            read choice

            case "$choice" in
                1)
                    echo "Enter the new Roll No:"
                    read newrollno
                    sed -i "s/>$rollno|/>$newrollno|/" student.db
                    echo "Roll No modified successfully.";;
                2)
                    stringg=$(grep ">$rollno|" student.db)
                    echo "$stringg"
                    echo "Enter new data:"
                    echo "Enter Student Name:"
                    read name
                    echo "Enter Marks 1:"
                    read marks1
                    echo "Enter Marks 2:"
                    read marks2
                    echo "Enter Marks 3:"
                    read marks3
                    echo "Enter city:"
                    read city
                    # Using sed to update the entry with the given student_id
                    sed -i "s/$stringg/>$rollno|$name|$marks1|$marks2|$marks3|$city/" student.db

                    echo "\nUpdated Successfully.";;
                *)
                    echo "Invalid choice. No modifications made.";;
            esac
        else
            echo "Student with Roll No $rollno not found."
        fi
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
        f) echo "Exiting the program."
           break;;
        *) echo "Invalid choice. Please try again.";;
    esac
done
