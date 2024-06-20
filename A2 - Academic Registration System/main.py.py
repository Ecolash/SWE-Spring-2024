from tkinter import *
import pickle
import os

class Person:
    def __init__(self,ID,password, attempts = 3):
        self.ID = ID
        self.password = password
        self.attempts_left = attempts

class Teacher(Person):
    def __init__(self, ID, password,name="",dept="",dob="", Reasearch_area=""):
        super().__init__(ID, password)
        self.name = name
        self.dept = dept
        self.dob = dob
        self.ra = Reasearch_area

class Student(Person):
    def __init__(self, ID, password,name="",dept="",dob="",roll_no="", year =""):
        super().__init__(ID, password)
        self.name = name
        self.dept = dept
        self.dob = dob
        self.roll_no = roll_no
        self.year = year

class UGStudent(Student):
    def __init__(self, ID, password, name="", dept="", dob="", roll_no="",year="",CGPA=""):
        super().__init__(ID, password, name, dept, dob, roll_no, year)
        self.CGPA = CGPA

class PGStudent(Student):
    def __init__(self, ID, password, name="", dept="", dob="", roll_no="",year="", specialisation=""):
        super().__init__(ID, password, name, dept, dob, roll_no, year)
        self.sp=specialisation

def delete_frames():
    for frame in main_frame.winfo_children():
        frame.destroy()

def check_valid_mail(ID):
    for object in LIST: 
        if object.ID == ID: return "User ID already exists."

    if "@" in ID and "." in ID: return "Valid"
    return "Invalid User Name"

def check_password(password):
    c1 = (len(password) >= 8)
    c2 = (len(password) <= 12)
    c3 = False 
    c4 = False
    c5 = False
    c6 = False
    c7 = True

    symbols = ['!' ,'@' ,'#' ,'$' ,'%','&','*']
    for x in password:
        if (x.isupper()): c3 = True
        if (x.islower()): c4 = True
        if (x.isdigit()): c5 = True
        if (x in symbols): c6 = True
        if (x == ' '): c7 = False
        
    if (not c1) : text="Password length should be atleast 8!"
    elif (not c2) : text="Password length should be atmost 12!"
    elif (not c3) : text="Password should have atleast 1 Uppercase Letter"
    elif (not c4) : text="Password should have atleast 1 Lowercase Letter"
    elif (not c5) : text="Password should have atleast 1 Numeric Character"
    elif (not c6) : text="Password should have atleast 1 special symbol(! ,@ ,# ,$ , %, &,*)"
    elif (not c7) : text="Password should not contain blank spaces"

    if (c1 and c2 and c3 and c4 and c5 and c6 and c7): return "Registration Successful."
    else : return text

def get(ID):
    for object in LIST: 
        if object.ID == ID: return object

def register_button(label1,ID,password,type):
    if check_valid_mail(ID)=="Valid":
        if check_password(password) == "Registration Successful." :
            label1.config(text=check_password(password))
            if type == "UG": 
                LIST.append(UGStudent(ID,password))
                UGStudent_edit(get(ID))

            elif type == "PG": 
                LIST.append(PGStudent(ID,password))
                PGStudent_edit(get(ID))

            else: 
                LIST.append(Teacher(ID,password))
                Teacher_edit(get(ID))

        else :label1.config(text=check_password(password))
    else: label1.configure(text=check_valid_mail(ID))

def student_teacher_page(type):
    delete_frames()
    register=Frame(main_frame,bg="#ffd1dc")
    register.pack()
    register.pack_propagate(False)
    register.configure(width=850,height=600)


    intro_label=Label(register,text= (type+" Student Registration" if type!="Teacher" else type+" Registration").upper(),fg="white",bg="#ff007f",width=50,font=("Helvetica",25,"bold"))
    intro_label.pack(side="top",pady=10)

    label2=Label(register,text="User ID",fg="#ee154d",bg="#ffd1dc",width=50,font=("Arial",15,"bold"))
    label2.pack(side="top",pady=10)

    entry1=Entry(register,font=("Helvetica",15,"bold"),bd=3,width=30,fg="#ff007f")
    entry1.pack(side="top",pady=10)

    passwrd=Label(register,text="Password",fg="#ee154d",bg="#ffd1dc",width=50,font=("Arial",15,"bold"))
    passwrd.pack(side="top",pady=5)

    entry2=Entry(register,font=("Helvetica",15,"bold"),bd=3,width=30,fg="#ff007f", show="•")
    entry2.pack(side="top",pady=5)

    s_reg=Button(register,text="Register",command=lambda: register_button(valid,entry1.get(),entry2.get(),type),bg="#ff007f", bd=3,height=1,width=15,fg="white",font=("Helvetica",15,"bold"), padx=10, pady = 5)
    s_reg.pack(side="top",pady=5)

    valid=Label(register,text="",fg="#ee154d",bg="#ffd1dc",width=50,font=("Arial",10,"bold"))
    valid.pack(side="top",pady=5)

    redirect=Label(register,text="",fg="#ee154d",bg="#ffd1dc",width=50,font=("Arial",10,"bold"))
    redirect.pack(side="top",pady=5)

    password_toggle = Button(register,text="Show Password",bg="#ff007f", bd=3,height=1,width=20,fg="white",font=("Helvetica",15,"bold"), padx=10, pady = 5, command= lambda:toggle_password_visibility(password_toggle, entry2) )
    password_toggle.pack(side="top",pady=5)

    logout = Button(register,text="Back to Home Page",bg="#ff007f", bd=3,height=1,width=30,fg="white",font=("Helvetica",15,"bold"), padx=10, pady = 5, command=out )
    logout.pack(side="top",pady=5)


def signin_page():
    delete_frames()
    register=Frame(main_frame,bg="#ffd1dc")
    register.pack()
    register.pack_propagate(False)
    register.configure(width=700,height=500)

    intro_label=Label(register,text="SIGN-IN PAGE",fg="white",bg="#ff007f",width=50,font=("Helvetica",30,"bold"))
    intro_label.pack(side="top",pady=15)

    label2=Label(register,text="User ID",fg="#ee204d",bg="#ffd1dc",width=50,font=("Arial",15,"bold"))
    label2.pack(side="top",pady=10)

    usrID=Entry(register,font=("Helvetica",15,"bold"),bd=3,width=35,fg="#ff007f")
    usrID.pack(side="top",pady=10)

    passwrd=Label(register,text="Password",fg="#ee204d",bg="#ffd1dc",width=50,font=("Arial",15,"bold"))
    passwrd.pack(side="top",pady=10)

    entry2=Entry(register,font=("Helvetica",15,"bold"),bd=3,width=35,fg="#ff007f", show="•")
    entry2.pack(side="top",pady=10)

    s_reg=Button(register,text="Sign In",command=lambda: sign_in_check(valid,usrID.get(),entry2.get(), usrID, entry2),bg="#ff007f", bd=3,height=1,width=10,fg="white",font=("Helvetica",15,"bold"), padx=10, pady = 5)
    s_reg.pack(side="top",pady=5)

    valid=Label(register,text="",fg="#ee204d",bg="#ffd1dc",width=50,font=("Arial",10,"bold"))
    valid.pack(side="top",pady=5)

    password_toggle = Button(register,text="Show Password",bg="#ff007f", bd=3,height=1,width=20,fg="white",font=("Helvetica",15,"bold"), padx=10, pady = 5, command= lambda:toggle_password_visibility(password_toggle, entry2) )
    password_toggle.pack(side="top",pady=5)

    logout = Button(register,text="Back to Home Page",bg="#ff007f", bd=3,height=1,width=30,fg="white",font=("Helvetica",15,"bold"), padx=10, pady = 5, command=out )
    logout.pack(side="top",pady=5)

def sign_in_check(label1,ID,password, entry1, entry2):
    found = 0
    for object in LIST: 
        if object.ID == ID:
            found = 1
            if object.attempts_left != 0 :
                if object.password == password: 
                    object.attempts_left = 3
                    if isinstance(object, Teacher) : Teacher_view(object)
                    elif isinstance(object, UGStudent) : UGStudent_view(object)
                    elif isinstance(object, PGStudent) : PGStudent_view(object)

                else:
                    object.attempts_left -= 1
                    label1.configure(text="Wrong Password! You have " + str(object.attempts_left) + " attempts left!")
                    entry2.delete(0, END)

            else: label1.configure(text="Your account is deactivated!")

    if found == 0: 
        label1.configure(text="Enter Valid Username!")
        entry1.delete(0, END)
        entry2.delete(0, END)
  
def register_page():
    delete_frames()
    register=Frame(main_frame,bg="#ffd1dc")
    register.pack()
    register.pack_propagate(False)
    register.configure(width=850,height=600)

    intro_label=Label(register,text="REGISTRATION PAGE",fg="white",bg="#ff007f",width=50,font=("Helvetica",30,"bold"))
    intro_label.pack(side="top",pady=15)

    intro_label1=Label(register,text="Register as: ",fg="black",bg="#ffd1dc",width=50,font=("Helvetica",15,"bold"))
    intro_label1.pack(side="top",pady=5)

    student_ug_btn=Button(register,text="UG Student",command=lambda: student_teacher_page("UG"),bg="#ff007f", bd=3,height=1,width=10,fg="white",font=("Helvetica",15,"bold"), padx=10, pady = 5)
    student_ug_btn.pack(side="top",pady=10)

    student_pg_btn=Button(register,text="PG Student",command=lambda: student_teacher_page("PG"),bg="#ff007f", bd=3,height=1,width=10,fg="white",font=("Helvetica",15,"bold"), padx=10, pady = 5)
    student_pg_btn.pack(side="top",pady=10)

    teacher_btn=Button(register,text="Teacher",command=lambda: student_teacher_page("Teacher"),bg="#ff007f", bd=3,height=1,width=10,fg="white",font=("Helvetica",15,"bold"), padx=10, pady = 5)
    teacher_btn.pack(side="top",pady=10)

    logout = Button(register,text="Back to Home Page",bg="#ff007f", bd=3,height=1,width=30,fg="white",font=("Helvetica",15,"bold"), padx=10, pady = 5, command=out )
    logout.pack(side="top",pady=40)

def home_page():
    delete_frames()
    sign=Frame(main_frame,bg="#ffd1dc")
    sign.pack()
    sign.pack_propagate(False)
    sign.configure(width=850,height=600)

    intro1 = Label(sign,text="WELCOME TO ACADEMIC UNIT",fg="white",bg="#ff007f",width=50,font=("Helvetica",30,"bold"))
    intro2 = Label(sign,text="HOME PAGE",fg="white",bg="#ff007f",width=50,font=("Helvetica",23,"bold"))

    intro1.pack(side="top",pady = 10)
    intro2.pack(side="top",pady = 5)

    question=Label(sign,text="New here? Sign Up!",fg="#ee204d",bg="#ffd1dc",width=50,font=("Arial",14,"bold"))
    question.pack(side="top", pady = 15)

    reg=Button(sign,text="Sign Up",command=register_page,bg="#ff007f", bd=3,height=1,width=10,fg="white",font=("Helvetica",15,"bold"),  padx=10, pady = 5)
    reg.pack(side="top", pady = 20)

    question1=Label(sign,text="Already an user? Sign In",fg="#ee204d",bg="#ffd1dc",width=50,font=("Arial",14,"bold"))
    question1.pack(side="top", pady = 10)

    sign_in=Button(sign,text="Sign In",bg="#ff007f", bd=3,height=1,width=10,fg="white",font=("Helvetica",15,"bold"), padx=10, pady = 5, command=signin_page)
    sign_in.pack(side="top", pady = 20)

    intro3 = Label(sign,text="© Tuhin Mondal | 2024",fg="white",bg="#ff007f",width=100,font=("Helvetica",10,"bold"))
    intro3.pack(side="bottom",pady = 5)

def toggle_password_visibility(button, entry):
    if entry.cget("show") == "•":
        entry.config(show="")
        button.config(text="Hide Password")
    else:
        entry.config(show="•")
        button.config(text="Show Password")


def Teacher_edit(Teacher):
    delete_frames()
    sign=Frame(main_frame,bg="#ffd1dc")
    sign.pack()
    sign.pack_propagate(False)
    sign.configure(width=850,height=600)

    intro0 = Label(sign,text="UPDATE YOUR INFO",fg="white",bg="#ff007f",width=30,font=("Helvetica",28,"bold"))
    intro0.grid(row = 0, columnspan= 3, pady = 20)

    intro1 = Label(sign,text="User ID: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    intro2 = Label(sign,text=Teacher.ID,width=30,font=("Helvetica",15,"bold"),bg="#ffd1dc")
    intro1.grid(row = 1 , column = 0)
    intro2.grid(row = 1 , column = 1, columnspan = 2, pady = 5)

    type1 = Label(sign,text="Profile Type: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    type2 = Label(sign,text="Teacher",width=20,font=("Helvetica",15,"bold"),bg="#ffd1dc")
    type1.grid(row = 2 , column = 0)
    type2.grid(row = 2 , column = 1, columnspan = 2, pady = 5)

    field1 = Label(sign,text="Name: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry1 = Entry(sign, font=("Helvetica",15,"bold"),bd=3,width=35,fg="#ff007f")
    entry1.insert(0, Teacher.name)
    field1.grid(row = 3 , column = 0, pady = 5)
    entry1.grid(row = 3 , column = 1, columnspan = 20, pady = 5)

    field2 = Label(sign,text="Department: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry2 = Entry(sign, font=("Helvetica",15,"bold"),bd=3,width=35,fg="#ff007f")
    entry2.insert(0, Teacher.dept)
    field2.grid(row = 4 , column = 0, pady = 5)
    entry2.grid(row = 4 , column = 1, columnspan = 20, pady = 5)

    field3 = Label(sign,text="Date of Birth: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry3 = Entry(sign, font=("Helvetica",15,"bold"),bd=3,width=35,fg="#ff007f")
    entry3.insert(0, Teacher.dob)
    field3.grid(row = 5 , column = 0, pady = 5)
    entry3.grid(row = 5 , column = 1, columnspan = 20, pady = 5)

    field4 = Label(sign,text="Reasearch Areas: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry4 = Entry(sign, font=("Helvetica",15,"bold"),bd=3,width=35,fg="#ff007f")
    entry4.insert(0, Teacher.ra)
    field4.grid(row = 6 , column = 0, pady = 5)
    entry4.grid(row = 6 , column = 1, columnspan = 20, pady = 5)

    submit = Button(sign,text="Save Changes",bg="#ff007f", bd=3,height=1,width=10,fg="white",font=("Helvetica",15,"bold"), padx=10, pady = 5, command=lambda : submits_Teacher(Teacher, entry1.get(), entry2.get(), entry3.get(), entry4.get()))
    submit.grid(row = 10, column= 1, padx = 20, pady = 60)


def UGStudent_edit(UGStudent):
    delete_frames()
    sign=Frame(main_frame,bg="#ffd1dc")
    sign.pack()
    sign.pack_propagate(False)
    sign.configure(width=850,height=600)

    intro0 = Label(sign,text="UPDATE YOUR INFO",fg="white",bg="#ff007f",width=30,font=("Helvetica",28,"bold"))
    intro0.grid(row = 0, columnspan= 3, pady = 20)

    intro1 = Label(sign,text="User ID: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    intro2 = Label(sign,text= UGStudent.ID,width=30,font=("Helvetica",15,"bold"),bg="#ffd1dc")
    intro1.grid(row = 1 , column = 0)
    intro2.grid(row = 1 , column = 1, columnspan = 2, pady = 5)

    type1 = Label(sign,text="Profile Type: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    type2 = Label(sign,text="UG Student",width=20,font=("Helvetica",15,"bold"),bg="#ffd1dc")
    type1.grid(row = 2 , column = 0)
    type2.grid(row = 2 , column = 1, columnspan = 2, pady = 5)

    field1 = Label(sign,text="Name: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry1 = Entry(sign, font=("Helvetica",15,"bold"),bd=3,width=35,fg="#ff007f")
    entry1.insert(0, UGStudent.name)
    field1.grid(row = 3 , column = 0, pady = 5)
    entry1.grid(row = 3 , column = 1, columnspan = 2, pady = 5)

    field2 = Label(sign,text="Department: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry2 = Entry(sign, font=("Helvetica",15,"bold"),bd=3,width=35,fg="#ff007f")
    entry2.insert(0, UGStudent.dept)
    field2.grid(row = 4 , column = 0, pady = 5)
    entry2.grid(row = 4 , column = 1, columnspan = 2, pady = 5)

    field3 = Label(sign,text="Date of Birth: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry3 = Entry(sign, font=("Helvetica",15,"bold"),bd=3,width=35,fg="#ff007f")
    entry3.insert(0, UGStudent.dob)
    field3.grid(row = 5 , column = 0, pady = 5)
    entry3.grid(row = 5 , column = 1, columnspan = 2, pady = 5)

    field4 = Label(sign,text="Roll Number: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry4 = Entry(sign, font=("Helvetica",15,"bold"),bd=3,width=35,fg="#ff007f")
    entry4.insert(0, UGStudent.roll_no)
    field4.grid(row = 6 , column = 0, pady = 5)
    entry4.grid(row = 6 , column = 1, columnspan = 2, pady = 5)

    field5 = Label(sign,text="CGPA: ",width=15, fg="#ee205d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry5 = Entry(sign, font=("Helvetica",15,"bold"),bd=3,width=35,fg="#ff007f")
    entry5.insert(0, UGStudent.CGPA)
    field5.grid(row = 7 , column = 0, pady = 5)
    entry5.grid(row = 7 , column = 1, columnspan = 2, pady = 5)

    field6 = Label(sign,text="Year of Graduation: ",width=15, fg="#ee205d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry6 = Entry(sign, font=("Helvetica",15,"bold"),bd=3,width=35,fg="#ff007f")
    entry6.insert(0, UGStudent.year)
    field6.grid(row = 8 , column = 0, pady = 5)
    entry6.grid(row = 8 , column = 1, columnspan = 2, pady = 5)

    submit = Button(sign,text="Save Changes",bg="#ff007f", bd=3,height=1,width=10,fg="white",font=("Helvetica",15,"bold"), padx=10, pady = 5, command=lambda:submits_UGStudent(UGStudent, entry1.get(), entry2.get(), entry3.get(), entry4.get(), entry5.get(), entry6.get()))
    submit.grid(row = 10, column= 1, padx = 20, pady = 15)


def PGStudent_edit(PGStudent):
    delete_frames()
    sign=Frame(main_frame,bg="#ffd1dc")
    sign.pack()
    sign.pack_propagate(False)
    sign.configure(width=850,height=600)

    intro0 = Label(sign,text="UPDATE YOUR INFO",fg="white",bg="#ff007f",width=30,font=("Helvetica",28,"bold"))
    intro0.grid(row = 0, columnspan= 3, pady = 20)

    intro1 = Label(sign,text="User ID: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    intro2 = Label(sign,text= PGStudent.ID,width=30,font=("Helvetica",15,"bold"),bg="#ffd1dc")
    intro1.grid(row = 1 , column = 0)
    intro2.grid(row = 1 , column = 1, columnspan = 2, pady = 5)

    type1 = Label(sign,text="Profile Type: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    type2 = Label(sign,text="PG Student",width=20,font=("Helvetica",15,"bold"),bg="#ffd1dc")
    type1.grid(row = 2 , column = 0)
    type2.grid(row = 2 , column = 1, columnspan = 2, pady = 5)

    field1 = Label(sign,text="Name: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry1 = Entry(sign, font=("Helvetica",15,"bold"),bd=3,width=35,fg="#ff007f")
    entry1.insert(0, PGStudent.name)
    field1.grid(row = 3 , column = 0, pady = 5)
    entry1.grid(row = 3 , column = 1, columnspan = 2, pady = 5)

    field2 = Label(sign,text="Department: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry2 = Entry(sign, font=("Helvetica",15,"bold"),bd=3,width=35,fg="#ff007f")
    entry2.insert(0, PGStudent.dept)
    field2.grid(row = 4 , column = 0, pady = 5)
    entry2.grid(row = 4 , column = 1, columnspan = 2, pady = 5)

    field3 = Label(sign,text="Date of Birth: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry3 = Entry(sign, font=("Helvetica",15,"bold"),bd=3,width=35,fg="#ff007f")
    entry3.insert(0, PGStudent.dob)
    field3.grid(row = 5 , column = 0, pady = 5)
    entry3.grid(row = 5 , column = 1, columnspan = 2, pady = 5)

    field4 = Label(sign,text="Roll Number: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry4 = Entry(sign, font=("Helvetica",15,"bold"),bd=3,width=35,fg="#ff007f")
    entry4.insert(0, PGStudent.roll_no)
    field4.grid(row = 6 , column = 0, pady = 5)
    entry4.grid(row = 6 , column = 1, columnspan = 2, pady = 5)

    field5 = Label(sign,text="Specialisation: ",width=15, fg="#ee205d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry5 = Entry(sign, font=("Helvetica",15,"bold"),bd=3,width=35,fg="#ff007f")
    entry5.insert(0, PGStudent.sp)
    field5.grid(row = 7 , column = 0, pady = 5)
    entry5.grid(row = 7 , column = 1, columnspan = 2, pady = 5)

    field6 = Label(sign,text="Year of Graduation: ",width=15, fg="#ee205d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry6 = Entry(sign, font=("Helvetica",15,"bold"),bd=3,width=35,fg="#ff007f")
    entry6.insert(0, PGStudent.year)
    field6.grid(row = 8 , column = 0, pady = 5)
    entry6.grid(row = 8 , column = 1, columnspan = 2, pady = 5)

    submit = Button(sign,text="Save Changes",bg="#ff007f", bd=3,height=1,width=10,fg="white",font=("Helvetica",15,"bold"), padx=10, pady = 5, command=lambda:submits_PGStudent(PGStudent, entry1.get(), entry2.get(), entry3.get(), entry4.get(), entry5.get(), entry6.get()))
    submit.grid(row = 10, column= 1, padx = 20, pady = 15)

def Teacher_view(Teacher):
    delete_frames()
    sign=Frame(main_frame,bg="#ffd1dc")
    sign.pack()
    sign.pack_propagate(False)
    sign.configure(width=850,height=600)

    intro0 = Label(sign,text="PROFILE INFO",fg="white",bg="#ff007f",width=30,font=("Helvetica",28,"bold"))
    intro0.grid(row = 0, columnspan= 3, pady = 20)

    intro1 = Label(sign,text="User ID: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    intro2 = Label(sign,text=Teacher.ID,width=30,font=("Helvetica",15,"bold"),bg="#ffd1dc")
    intro1.grid(row = 1 , column = 0)
    intro2.grid(row = 1 , column = 1, columnspan = 2, pady = 5)

    type1 = Label(sign,text="Profile Type: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    type2 = Label(sign,text="Teacher",width=20,font=("Helvetica",15,"bold"),bg="#ffd1dc")
    type1.grid(row = 2 , column = 0)
    type2.grid(row = 2 , column = 1, columnspan = 2, pady = 5)

    field1 = Label(sign,text="Name: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry1 = Label(sign,text=Teacher.name,width=20,font=("Helvetica",15,"bold"),bg="#ffd1dc")
    field1.grid(row = 3 , column = 0, pady = 5)
    entry1.grid(row = 3 , column = 1, columnspan = 20, pady = 5)

    field2 = Label(sign,text="Department: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry2 = Label(sign,text=Teacher.dept,width=20,font=("Helvetica",15,"bold"),bg="#ffd1dc")
    field2.grid(row = 4 , column = 0, pady = 5)
    entry2.grid(row = 4 , column = 1, columnspan = 20, pady = 5)

    field3 = Label(sign,text="Date of Birth: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry3 = Label(sign,text=Teacher.dob,width=20,font=("Helvetica",15,"bold"),bg="#ffd1dc")
    field3.grid(row = 5 , column = 0, pady = 5)
    entry3.grid(row = 5 , column = 1, columnspan = 20, pady = 5)

    field4 = Label(sign,text="Reasearch Areas: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry4 = Label(sign,text=Teacher.ra,width=20,font=("Helvetica",15,"bold"),bg="#ffd1dc")
    field4.grid(row = 6 , column = 0, pady = 5)
    entry4.grid(row = 6 , column = 1, columnspan = 20, pady = 5)

    edit = Button(sign,text="Edit",bg="#ff007f", bd=3,height=1,width=10,fg="white",font=("Helvetica",15,"bold"), padx=10, pady = 5, command = lambda :edits_Teacher(Teacher))
    edit.grid(row = 10, column= 0, padx = 20, pady = 15)

    logout = Button(sign,text="Sign Out",bg="#ff007f", bd=3,height=1,width=10,fg="white",font=("Helvetica",15,"bold"), padx=10, pady = 5, command=out )
    logout.grid(row = 10, column= 2, padx = 20, pady = 15)

    deregister = Button(sign,text="Deregistration request",bg="#ff007f", bd=3,height=1,width=30,fg="white",font=("Helvetica",15,"bold"), padx=10, pady = 5, command = lambda:delete_user(Teacher) )
    deregister.grid(row = 11, column= 0, padx = 25, pady = 10, columnspan= 3)


def UGStudent_view(UGStudent):
    delete_frames()
    sign=Frame(main_frame,bg="#ffd1dc")
    sign.pack()
    sign.pack_propagate(False)
    sign.configure(width=850,height=600)

    intro0 = Label(sign,text="PROFILE INFO",fg="white",bg="#ff007f",width=30,font=("Helvetica",28,"bold"))
    intro0.grid(row = 0, columnspan= 3, pady = 5)

    intro1 = Label(sign,text="User ID: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    intro2 = Label(sign,text=UGStudent.ID,width=30,font=("Helvetica",15,"bold"),bg="#ffd1dc")
    intro1.grid(row = 1 , column = 0)
    intro2.grid(row = 1 , column = 1, columnspan = 2, pady = 5)

    type1 = Label(sign,text="Profile Type: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    type2 = Label(sign,text="UG Student",width=20,font=("Helvetica",15,"bold"),bg="#ffd1dc")
    type1.grid(row = 2 , column = 0)
    type2.grid(row = 2 , column = 1, columnspan = 2, pady = 5)

    field1 = Label(sign,text="Name: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry1 = Label(sign,text=UGStudent.name,width=20,font=("Helvetica",15,"bold"),bg="#ffd1dc")
    field1.grid(row = 3 , column = 0, pady = 5)
    entry1.grid(row = 3 , column = 1, columnspan = 20, pady = 5)

    field2 = Label(sign,text="Department: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry2 = Label(sign,text=UGStudent.dept,width=20,font=("Helvetica",15,"bold"),bg="#ffd1dc")
    field2.grid(row = 4 , column = 0, pady = 5)
    entry2.grid(row = 4 , column = 1, columnspan = 20, pady = 5)

    field3 = Label(sign,text="Date of Birth: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry3 = Label(sign,text=UGStudent.dob,width=20,font=("Helvetica",15,"bold"),bg="#ffd1dc")
    field3.grid(row = 5 , column = 0, pady = 5)
    entry3.grid(row = 5 , column = 1, columnspan = 20, pady = 5)

    field4 = Label(sign,text="Roll Number: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry4 = Label(sign,text=UGStudent.roll_no,width=20,font=("Helvetica",15,"bold"),bg="#ffd1dc")
    field4.grid(row = 6 , column = 0, pady = 5)
    entry4.grid(row = 6 , column = 1, columnspan = 20, pady = 5)

    field5 = Label(sign,text="CGPA: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry5 = Label(sign,text=UGStudent.CGPA,width=20,font=("Helvetica",15,"bold"),bg="#ffd1dc")
    field5.grid(row = 7 , column = 0, pady = 5)
    entry5.grid(row = 7 , column = 1, columnspan = 20, pady = 5)

    field6 = Label(sign,text="Year of Graduation: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry6 = Label(sign,text=UGStudent.year,width=20,font=("Helvetica",15,"bold"),bg="#ffd1dc")
    field6.grid(row = 8 , column = 0, pady = 5)
    entry6.grid(row = 8 , column = 1, columnspan = 20, pady = 5)

    edit = Button(sign,text="Edit",bg="#ff007f", bd=3,height=1,width=10,fg="white",font=("Helvetica",15,"bold"), padx=10, pady = 5, command = lambda :edits_UGStudent(UGStudent))
    edit.grid(row = 10, column= 0, padx = 20, pady = 5)

    logout = Button(sign,text="Sign Out",bg="#ff007f", bd=3,height=1,width=10,fg="white",font=("Helvetica",15,"bold"), padx=10, pady = 5, command=out )
    logout.grid(row = 10, column= 2, padx = 20, pady = 5)

    deregister = Button(sign,text="Deregistration request",bg="#ff007f", bd=3,height=1,width=30,fg="white",font=("Helvetica",15,"bold"), padx=10, pady = 5, command = lambda:delete_user(UGStudent) )
    deregister.grid(row = 11, column= 0, padx = 25, pady = 5, columnspan= 3)

def PGStudent_view(PGStudent):
    delete_frames()
    sign=Frame(main_frame,bg="#ffd1dc")
    sign.pack()
    sign.pack_propagate(False)
    sign.configure(width=850,height=600)

    intro0 = Label(sign,text="PROFILE INFO",fg="white",bg="#ff007f",width=30,font=("Helvetica",28,"bold"))
    intro0.grid(row = 0, columnspan= 3, pady = 5)

    intro1 = Label(sign,text="User ID: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    intro2 = Label(sign,text=PGStudent.ID,width=30,font=("Helvetica",15,"bold"),bg="#ffd1dc")
    intro1.grid(row = 1 , column = 0)
    intro2.grid(row = 1 , column = 1, columnspan = 2, pady = 5)

    type1 = Label(sign,text="Profile Type: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    type2 = Label(sign,text="PG Student",width=20,font=("Helvetica",15,"bold"),bg="#ffd1dc")
    type1.grid(row = 2 , column = 0)
    type2.grid(row = 2 , column = 1, columnspan = 2, pady = 5)

    field1 = Label(sign,text="Name: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry1 = Label(sign,text=PGStudent.name,width=20,font=("Helvetica",15,"bold"),bg="#ffd1dc")
    field1.grid(row = 3 , column = 0, pady = 5)
    entry1.grid(row = 3 , column = 1, columnspan = 20, pady = 5)

    field2 = Label(sign,text="Department: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry2 = Label(sign,text=PGStudent.dept,width=20,font=("Helvetica",15,"bold"),bg="#ffd1dc")
    field2.grid(row = 4 , column = 0, pady = 5)
    entry2.grid(row = 4 , column = 1, columnspan = 20, pady = 5)

    field3 = Label(sign,text="Date of Birth: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry3 = Label(sign,text=PGStudent.dob,width=20,font=("Helvetica",15,"bold"),bg="#ffd1dc")
    field3.grid(row = 5 , column = 0, pady = 5)
    entry3.grid(row = 5 , column = 1, columnspan = 20, pady = 5)

    field4 = Label(sign,text="Roll Number: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry4 = Label(sign,text=PGStudent.roll_no,width=20,font=("Helvetica",15,"bold"),bg="#ffd1dc")
    field4.grid(row = 6 , column = 0, pady = 5)
    entry4.grid(row = 6 , column = 1, columnspan = 20, pady = 5)

    field5 = Label(sign,text="Specalisation: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry5 = Label(sign,text=PGStudent.sp,width=20,font=("Helvetica",15,"bold"),bg="#ffd1dc")
    field5.grid(row = 7 , column = 0, pady = 5)
    entry5.grid(row = 7 , column = 1, columnspan = 20, pady = 5)

    field6 = Label(sign,text="Year of Graduation: ",width=15, fg="#ee204d",bg="#ffd1dc",font=("Helvetica",15,"bold"))
    entry6 = Label(sign,text=PGStudent.year,width=20,font=("Helvetica",15,"bold"),bg="#ffd1dc")
    field6.grid(row = 8 , column = 0, pady = 5)
    entry6.grid(row = 8 , column = 1, columnspan = 20, pady = 5)

    edit = Button(sign,text="Edit",bg="#ff007f", bd=3,height=1,width=10,fg="white",font=("Helvetica",15,"bold"), padx=10, pady = 5, command = lambda :edits_PGStudent(PGStudent))
    edit.grid(row = 10, column= 0, padx = 20, pady = 5)

    logout = Button(sign,text="Sign Out",bg="#ff007f", bd=3,height=1,width=10,fg="white",font=("Helvetica",15,"bold"), padx=10, pady = 5, command=out )
    logout.grid(row = 10, column= 2, padx = 20, pady = 5)

    deregister = Button(sign,text="Deregistration request",bg="#ff007f", bd=3,height=1,width=30,fg="white",font=("Helvetica",15,"bold"), padx=10, pady = 5, command = lambda:delete_user(PGStudent) )
    deregister.grid(row = 11, column= 0, padx = 25, pady = 5, columnspan= 3)

def submits_Teacher(Teacher, s1, s2, s3, s4):
    Teacher.name = s1
    Teacher.dept = s2
    Teacher.dob = s3
    Teacher.ra = s4
    Teacher_view(Teacher)

def submits_UGStudent(UGStudent, s1, s2, s3, s4, s5, s6):
    UGStudent.name = s1
    UGStudent.dept = s2
    UGStudent.dob = s3
    UGStudent.roll_no = s4
    UGStudent.CGPA = s5
    UGStudent.year = s6
    UGStudent_view(UGStudent)

def submits_PGStudent(PGStudent, s1, s2, s3, s4, s5, s6):
    PGStudent.name = s1
    PGStudent.dept = s2
    PGStudent.dob = s3
    PGStudent.roll_no = s4
    PGStudent.sp = s5
    PGStudent.year = s6
    PGStudent_view(PGStudent)

def edits_Teacher(Teacher):
    Teacher_edit(Teacher)

def edits_UGStudent(UGStudent):
    UGStudent_edit(UGStudent)

def edits_PGStudent(PGStudent):
    PGStudent_edit(PGStudent)

def out():
    home_page()

def delete_user(x):
    for object in LIST: 
        if object.ID == x.ID: 
            LIST.remove(object)
            break
    
    home_page()

window=Tk()
window.geometry("700x500")
window.title("Academic Registration System")

try:
    with open("file.pkl", "rb") as file:
        LIST = pickle.load(file)
except EOFError:
    pass

main_frame = Frame(window)
main_frame.pack()
home_page()
window.mainloop()

with open("file.pkl", "wb") as file:
    pickle.dump(LIST, file)