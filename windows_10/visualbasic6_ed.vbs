==================================================================





================================================================





================================================================





===============================================================

'' 경로명의 파일을 불러와 10줄을 읽는 예제 코드 

Private Sub form_click()

Dim msg, f_name, f_line, f_data
msg = "경로명을 입력하세요"

f_name = InputBox(msg, "파일명")


If f_name = "" Then
    End
Else
    Open f_name For Input As #1
End If



For i = 1 To 20
Line Input #1, f_line
If EOF(1) Then Exit For


f_data = f_data & f_line & Chr(10)
Next

Close #1


MsgBox f_data, vbOKOnly, f_name & "파일 (처음 10줄)"


End Sub



================================================================

'' 디렉토리, 드라이브 처리 수행문 예제 코드 (권한부족으로 생성은 안되더라)

Private Sub form_click()
    
    ChDrive "c:"
    ChDir "\users\gyurs\"
    
    Print "현재 디렉토리는 :  " & CurDir
    Print
    
    MkDir "\test"
    Print "test 디렉토리를 생성했습니다"
    del = "test 디렉토리를 삭제할까요?"
    
    MsgBox del, vbYesNo, "삭제"
    
    RmDir "\test"
    Print "삭제했습니다"


End Sub




================================================================

'' 함수 인자 전달방식 value, reference에 대한 예제 코드

Private Sub form_click()

    v = 10
    r = 20
    
    Print
    define_procedure v, r
    
    Print
    Print "call by value와 call by reference"
    Print
    
    Print "call by value: "; v
    Print "call by reference: "; r
       

End Sub


Private Sub define_procedure(ByVal v, ByRef r)
    
    v = 111
    r = 2222
    
    Print "INFUNC[v]: " & v
    Print "INFUNC[r]: " & r

End Sub


===============================================================

'' 모듈 :  main  예제 코드

Public Sub main()

msg = "여기는 main 프로시저입니다"
MsgBox msg

Call udf_proc 'udp_proc 프로시저를 호출합니다

MsgBox msg
End
End Sub


Public Sub udf_proc()

msg = "여기는 udf_prco" & Chr(10)
msg = msg & "main 으로 돌아갈까요?"

n = MsgBox(msg, vbYesNo + vbInformation)



If n = vbYes Then
    Exit Sub

Else
    End
    
End If



End Sub






================================================================

'' 2차원 배열을 이용해 학생들의 석차를 나타내는 예제 코드 

Private Sub Form_click()

Dim n(1 To 4, 4)

' 배열의 요소 값 초기화


n(1, 0) = "홍길동": n(1, 1) = 80: n(1, 2) = 70
n(2, 0) = "성춘향": n(2, 1) = 73: n(2, 2) = 72
n(3, 0) = "이몽룡": n(3, 1) = 88: n(3, 2) = 23
n(4, 0) = "길동이": n(4, 1) = 94: n(4, 2) = 7




' i 번 학생에 대한 합계 구하기
For i = 1 To 4

    n(i, 3) = n(i, 1) + n(i, 2)
Next




' i 번 학생에 대한 석차 구하기
For i = 1 To 4
    석차 = 1
    For j = 1 To 4
    
        If n(j, 3) > n(i, 3) Then
        석차 = 석차 + 1
    End If
    Next

   n(i, 4) = 석차

Next
    
    


' 성적 출력
Print "이름", "국어", "산수", "합계", "석차"

For i = 1 To 4
    Print n(i, 0), n(i, 1), n(i, 2), n(i, 3), n(i, 4)
Next




End Sub



================================================================

'' 난수를 발생시켜 배열 순대대로 정렬하는 예제 코드

Private Sub form_click()

Dim n(9) As Integer
Randomize

Print "난수 발생 결과:"




For i = 0 To 9
    n(i) = Int(Rnd * 10)
    Print n(i);
Next

Print
Print




For i = 9 To 0 Step -1
    Print n(i)
Next

Print


End Sub





================================================================

'' do while을 사용한 예제 코드

Private Sub Form_Click()

i = 10

Do While i <= 50
    Print i
    i = i + 5
Loop


Print " do while : " & i


End Sub




================================================================

'' for문을 활용한 예제코드

Private Sub Form_Click()


For i = 1 To 10
    Print i;
Next i


Print


For n = 10 To 1 Step -2
    Print n
    Sum = Sum + n
Next

Print "합계는: " & Sum


End Sub





================================================================

'' 비교연산자에 대해 알아보는 코드 + like 연산자


Private Sub Form_Click()


Print "비교 연산자"

Print 5 = 3 'false
Print 5 <> 3 'true
Print 5 < 3 'false

Print "duckbaby" Like "d*"; 'True
Print

End Sub




================================================================
'' 폼 코드  (전역변수와 지역변수의 차이를 나타내는 코드()


Private Sub Form_click()

Form1.AutoRedraw = True

Dim n(1 To 9) As Integer

Print "3의 배수와 합계 구하기"

For i = 1 To 9
    n(i) = i * 10: Print n(i);
Next

Print
Print "3의 배수"


Sum = 0

For i = 1 To 9
    If (n(i) Mod 3) = 0 Then
    Sum = Sum + n(i)
    Print n(i)
    End If
	Next

Print "합계 : " & Sum


End Sub



'' 모듈 코드

Global g
Dim x


Public Sub a_procedure()

x = x + 4
g = g + 5

Form1.Print
Form1.Print "<a_procedure>"
Form1.Print "x: " & x, "g: " & g
Form1.Print "-----------------------"

End Sub

Public Sub b_procedure()
x = x + 4
g = g + 5

Form1.Print
Form1.Print "<b_procedure>"
Form1.Print "x: " & x, "g: " & g


End Sub


================================================================

'' inputbox를 사용한 if문의 사용법 예제 코드

Private Sub Form_Click()

n = InputBox("숫자를 입력받습니다", "입력", "0")

If n > 0 Then
    Print "양수!"
Else
    Print "음수!"
    End If
    
If n = 0 Then
End
End If

End Sub




================================================================

'' select case 구문을 사용하는 예제 코드

Private Sub Form_Click()

Key = InputBox("아무키나 누르세요", "입력 창 제목", ".")


Select Case Key
    Case ".":
        End
    Case "0" To "9"
        Print "숫자!"
    Case "A" To "Z":
        Print "대문자!"
    Case "a" To "z":
        Print "소문자!"
    Case Else
        Print "기타!"

End Select




End Sub














