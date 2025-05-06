import pymysql
import tkinter
import tkinter.messagebox as mbox

def insertData() :
    connect = pymysql.connect(host='127.0.0.1', user='root',
    password='mseoke0518!!', db='market_db', charset='utf8')

    cursor = connect.cursor()

    data1 = edt1.get(); data2 = edt2.get(); data3 = edt3.get(); data4 = edt4.get()
    data5 = edt5.get(); data6 = edt6.get(); data7 = edt7.get(); data8 = edt8.get()

    sql = "INSERT INTO member VALUES(%s, %s, %s, %s, %s, %s, %s, %s)"
    data = (data1, data2, data3, data4, data5, data6, data7, data8)

    cursor.execute(sql, data)
    connect.commit()
    connect.close()

    mbox.showinfo('성공', '1건 등록 완료')
    selectData()

def selectData() :
    strData1, strData2, strData3, strData4 = [], [], [], []
    strData5, strData6, strData7, strData8 = [], [], [], []

    strData1.append("멤버 ID"); strData2.append("멤버 이름")
    strData3.append("멤버 수"); strData4.append("주소")
    strData5.append("phone1"); strData6.append("phone2")
    strData7.append("키"); strData8.append("데뷔날짜")

    strData1.append("-------------"); strData2.append("-------------")
    strData3.append("-------------"); strData4.append("-------------")
    strData5.append("-------------"); strData6.append("-------------")
    strData7.append("-------------"); strData8.append("-------------")

    connect = pymysql.connect(host='127.0.0.1', user='root', password='mseoke0518!!', db='market_db', charset='utf8')
    cursor = connect.cursor()

    sql = "select mem_id, mem_name, mem_number, addr, ifnull(phone1, '-') phone1, ifnull(phone2, '-') phone2, ifnull(height, '-') height, ifnull(debut_date, '-') debut_date from member order by mem_id;"

    cursor.execute(sql)

    while (True) :
        row = cursor.fetchone()

        if row== None:
            break

        strData1.append(row[0]); strData2.append(row[1]); strData3.append(row[2]); strData4.append(row[3])
        strData5.append(row[4]); strData6.append(row[5]); strData7.append(row[6]); strData8.append(row[7])

    listData1.delete(0,listData1.size() - 1); listData3.delete(0,listData3.size() - 1)
    listData2.delete(0,listData2.size() - 1); listData4.delete(0,listData4.size() - 1)
    listData5.delete(0,listData5.size() - 1); listData6.delete(0,listData6.size() - 1)
    listData7.delete(0,listData7.size() - 1); listData8.delete(0,listData8.size() - 1)

    for item1, item2, item3, item4, item5, item6, item7, item8 in zip(strData1, strData2, strData3, strData4, strData5, strData6, strData7, strData8):
        listData1.insert('end', item1); listData2.insert('end', item2)
        listData3.insert('end', item3); listData4.insert('end', item4)
        listData5.insert('end', item5); listData6.insert('end', item6)
        listData7.insert('end', item7); listData8.insert('end', item8)

    connect.close()

def deleteData():
    connect = pymysql.connect(host='127.0.0.1', user='root',
    password='mseoke0518!!', db='market_db', charset='utf8')

    cursor = connect.cursor()

    sql = "delete from member"

    cursor.execute(sql)
    
    connect.commit()
    connect.close()


## 메인 코드부
window = tkinter.Tk()
window.geometry("600x300")
window.title('complete GUI Program')

edtFrame = tkinter.Frame(window); edtFrame.pack()
listFrame = tkinter.Frame(window); listFrame.pack(side ='bottom',fill='both', expand=1)

edt1= tkinter.Entry(edtFrame, width=10); edt1.pack(side='left',padx=10,pady=10)
edt2= tkinter.Entry(edtFrame, width=10); edt2.pack(side='left',padx=10,pady=10)
edt3= tkinter.Entry(edtFrame, width=10); edt3.pack(side='left',padx=10,pady=10)
edt4= tkinter.Entry(edtFrame, width=10); edt4.pack(side='left',padx=10,pady=10)
edt5= tkinter.Entry(edtFrame, width=10); edt5.pack(side='left',padx=10,pady=10)
edt6= tkinter.Entry(edtFrame, width=10); edt6.pack(side='left',padx=10,pady=10)
edt7= tkinter.Entry(edtFrame, width=10); edt7.pack(side='left',padx=10,pady=10)
edt8= tkinter.Entry(edtFrame, width=10); edt8.pack(side='left',padx=10,pady=10)

btnInsert = tkinter.Button(edtFrame, text="insert", command = insertData)
btnInsert.pack(side='left',padx=10,pady=10)

btnSelect = tkinter.Button(edtFrame, text="select", command = selectData)
btnSelect.pack(side='left',padx=10,pady=10)

btnDelete = tkinter.Button(edtFrame, text="delete", command = deleteData)
btnDelete.pack(side='left', padx=10, pady=10)

listData1 = tkinter.Listbox(listFrame,bg = 'gray'); listData2 = tkinter.Listbox(listFrame,bg = 'gray')
listData3 = tkinter.Listbox(listFrame,bg = 'gray'); listData4 = tkinter.Listbox(listFrame,bg = 'gray')
listData5 = tkinter.Listbox(listFrame,bg = 'gray'); listData6 = tkinter.Listbox(listFrame,bg = 'gray')
listData7 = tkinter.Listbox(listFrame,bg = 'gray'); listData8 = tkinter.Listbox(listFrame,bg = 'gray')

listData1.pack(side='left',fill='both', expand=1)
listData2.pack(side='left',fill='both', expand=1)
listData3.pack(side='left',fill='both', expand=1)
listData4.pack(side='left',fill='both', expand=1)
listData5.pack(side='left',fill='both', expand=1)
listData6.pack(side='left',fill='both', expand=1)
listData7.pack(side='left',fill='both', expand=1)
listData8.pack(side='left',fill='both', expand=1)

window.mainloop()