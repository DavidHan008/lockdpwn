Imports System.Windows
Imports System.Windows.Media.Media3D
Imports System.Windows.Markup
Imports System.IO
Imports System.Xml

Public Class ViewControl3D
    Dim objcpy As New ModelVisual3D
    Dim hardPointMdl As susObject
    Dim axisModel(6) As susObject

    Dim pntDragStart As Point
    Dim pntTarget As Point
    Dim pntcam As Point
    Dim mousestate As Integer
    Dim mousestateListBox As Integer

    Dim camctrl As New cameraControl

    Dim objList As New List(Of susObject)
    Dim pntList As New List(Of Vector3D)
    Dim nPnt As Integer
    Dim bCamHalf As Boolean = True

    Dim timeVal As Single
    Public testvalue As Integer = 0


    Public Sub UpdateHardPointVisualModel()
        timeVal = timeVal + 0.5
        hardPointMdl.sVec = hardPointMdl.Vec3 * (Math.Sin(timeVal) * 0.3 + 0.5)
        hardPointMdl.transformObj()
    End Sub

    Public Sub SetHardPoint(nPin As Integer, pntA() As Vector3D)
        Dim i As Integer
        nPnt = nPin
        pntList.Clear()
        For i = 0 To nPin - 1
            pntList.Add(New Vector3D(pntA(i).X, pntA(i).Y, pntA(i).Z))
        Next
    End Sub
    Public Sub UpdateHardPnt(ncnt As Integer, pnt As Vector3D)
        pntList(ncnt) = pnt
        UpdateScene()
    End Sub

    Public Sub SelectObject(objin As susObject, nDirection As Integer)
        Dim i As Integer
        For i = 0 To 6
            setChild(axisModel(i).obj3D, World, False)
        Next
        If objin Is Nothing = False Then

            If (objin.nType = 6) Then
                setChild(axisModel(nDirection).obj3D, World, True)
                Dim matOut As Matrix3D = New Matrix3D
                matOut = objin.obj3D.Transform.Value

                Dim vecX As Vector3D = New Vector3D(matOut.M11, matOut.M21, matOut.M31)
                Dim vecY As Vector3D = New Vector3D(matOut.M12, matOut.M22, matOut.M32)
                Dim vecZ As Vector3D = New Vector3D(matOut.M13, matOut.M23, matOut.M33)

                vecX.Normalize()
                vecY.Normalize()
                vecZ.Normalize()

                matOut.M11 = vecX.X * axisModel(0).sVec.X
                matOut.M21 = vecX.Y * axisModel(0).sVec.X
                matOut.M31 = vecX.Z * axisModel(0).sVec.X

                matOut.M12 = vecY.X * axisModel(0).sVec.Y
                matOut.M22 = vecY.Y * axisModel(0).sVec.Y
                matOut.M32 = vecY.Z * axisModel(0).sVec.Y

                matOut.M13 = vecZ.X * axisModel(0).sVec.Z
                matOut.M23 = vecZ.Y * axisModel(0).sVec.Z
                matOut.M33 = vecZ.Z * axisModel(0).sVec.Z
                axisModel(nDirection).obj3D.Transform = New MatrixTransform3D(matOut)

            End If
        End If

    End Sub

    Public Sub SelectHardPoint(ncnt As Integer)
        If IsNothing(pntList) Or pntList.Count <= ncnt Or pntList.Count <= 0 Then
            Exit Sub
        End If
        If (ncnt < 0) Then
            setChild(hardPointMdl.obj3D, World, False)
        Else
            setChild(hardPointMdl.obj3D, World, True)
            hardPointMdl.transformObj(pntList(ncnt))
        End If

    End Sub
    Public Sub SetCamInitPos1(ByVal dirIn As Vector3D)
        Dim tget As Vector3D = New Vector3D(0, 0, 0)
        Dim i As Integer
        Dim dist As Single
        camctrl.setCamera(Me.Camera1)

        If (pntList.Count() > 0) Then
            For i = 0 To nPnt - 1
                tget = tget + pntList(i)
            Next
            tget = tget / nPnt
            If (bCamHalf) Then tget.Y = 0
            dist = 0
            For i = 0 To nPnt - 1
                dist = (tget - pntList(i)).Length()
            Next
            dist = dist / nPnt
            If (dist < 0.1) Then dist = 20.0

            dirIn.Normalize()

            camctrl.SetInitPos((tget - dirIn * dist * 100.0) / 1000.0, tget / 1000.0)
        End If

    End Sub

    Public Sub SetCamInitPos2(ByVal pnt1 As Vector3D, ByVal dirIn As Vector3D, ByVal dist As Single)
        dirIn.Normalize()
        camctrl.setCamera(Me.Camera1)
        camctrl.SetInitPos((pnt1 - dirIn * dist) / 1000.0, pnt1 / 1000.0)

    End Sub

    Private Sub ViewControl3D_GotFocus(sender As Object, e As System.Windows.RoutedEventArgs) Handles Me.GotFocus
        Dim i As Integer
        i = 0
    End Sub

    Private Sub UserControl_Loaded(ByVal sender As System.Object, ByVal e As System.Windows.RoutedEventArgs) Handles MyBase.Loaded
        'camctrl.SetInitPos(New Vector3D(0.1, 0.1, 0.1), New Vector3D(0, 0, 0))
        'camctrl.SetInitPos(New Vector3D(-0.029 + 0.5, 0.698004 - 0.5, -0.030939 + 0.5), New Vector3D(-0.029, 0.698004, -0.030939))
        timeVal = 0
        mousestate = 0
        bCamHalf = True
        setChild(Tire, World, False)
        setChild(link, World, False)
        setChild(ball, World, False)
        setChild(Strut, World, False)
        setChild(link2, World, False)
        setChild(Axis, World, False)
        setChild(Axis_X, World, False)
        setChild(Axis_Y, World, False)
        setChild(Axis_Z, World, False)
        setChild(Axis_RX, World, False)
        setChild(Axis_RY, World, False)
        setChild(Axis_RZ, World, False)

        setChild(Bushing, World, False)
        setChild(Triangle, World, False)
        hardPointMdl = New susObject("HardPointObj", "NULL", 3, 0, 0, 0, 0, 0, 0, New Vector3D(100, 100, 100), New Vector3D(0, 0, 0), Nothing)
        hardPointMdl.obj3D = cloneModel(ball)
        hardPointMdl.transformObj()

        axisModel(0) = New susObject("AxisObj", "NULL", 3, 0, 0, 0, 0, 0, 0, New Vector3D(150, 150, 150), New Vector3D(0, 0, 0), Nothing)
        axisModel(1) = New susObject("AxisObj_X", "NULL", 3, 0, 0, 0, 0, 0, 0, New Vector3D(150, 150, 150), New Vector3D(0, 0, 0), Nothing)
        axisModel(2) = New susObject("AxisObj_Y", "NULL", 3, 0, 0, 0, 0, 0, 0, New Vector3D(150, 150, 150), New Vector3D(0, 0, 0), Nothing)
        axisModel(3) = New susObject("AxisObj_Z", "NULL", 3, 0, 0, 0, 0, 0, 0, New Vector3D(150, 150, 150), New Vector3D(0, 0, 0), Nothing)
        axisModel(4) = New susObject("AxisObj_RX", "NULL", 3, 0, 0, 0, 0, 0, 0, New Vector3D(150, 150, 150), New Vector3D(0, 0, 0), Nothing)
        axisModel(5) = New susObject("AxisObj_RY", "NULL", 3, 0, 0, 0, 0, 0, 0, New Vector3D(150, 150, 150), New Vector3D(0, 0, 0), Nothing)
        axisModel(6) = New susObject("AxisObj_RZ", "NULL", 3, 0, 0, 0, 0, 0, 0, New Vector3D(150, 150, 150), New Vector3D(0, 0, 0), Nothing)
        axisModel(0).obj3D = Axis
        axisModel(1).obj3D = Axis_X
        axisModel(2).obj3D = Axis_Y
        axisModel(3).obj3D = Axis_Z
        axisModel(4).obj3D = Axis_RX
        axisModel(5).obj3D = Axis_RY
        axisModel(6).obj3D = Axis_RZ
        Dim i As Integer
        For i = 0 To 6
            axisModel(i).transformObj()
        Next
        'TriangleModel.BackMaterial 



    End Sub

    Public Sub UpdateScene()
        For Each item As susObject In objList
            item.transformObj()
        Next
    End Sub

    Sub addObjecttoWorldTree(ByVal name As String, ByVal obj3d As ModelVisual3D)
        Dim objP As ModelVisual3D
        objP = Nothing
        For Each item As Visual3D In World.Children
            If (name = item.GetValue(FrameworkElement.NameProperty)) Then
                objP = item
            End If
        Next
        If (objP Is Nothing = True) Then
            objP = New ModelVisual3D
            objP.SetValue(FrameworkElement.NameProperty, name)
            setChild(objP, World, True)
        End If
        setChild(obj3d, objP, True)
    End Sub

    Function getIDstring() As String
        Static idCount As Integer = 0
        idCount += 1
        Return "SusObject_" + LTrim(Str(idCount))
    End Function

    Private Function getID(ByVal name As String) As String
        Dim retv As String
        For Each item As susObject In objList
            If (item.getName() = name) Then Return item.getID()
        Next
        Return getIDstring()
    End Function


    Public Sub addModel(ByVal name As String, ByVal mdlType As Integer, ByVal bsym As Boolean, ByVal scalev As Vector3D, Optional ByVal np1 As Integer = 0, Optional ByVal nq1 As Integer = 0, Optional ByVal nq2 As Integer = 0, Optional ByVal nn1 As Integer = 0, Optional ByVal nr As Integer = 0, Optional ByVal nn2 As Integer = 0, Optional ByVal angle3 As Vector3D = Nothing)
        Dim sID As String
        sID = getID(name)
        If (pntList.Count > 0) Then
            If (bsym = True) Then
                addModel("R_" + name, -mdlType, False, scalev, -np1, -nq1, -nq2, nn1, -nr, nn2, angle3)
            End If
            If (mdlType > 0) Then
                addListbox(name)
            Else
                mdlType = -mdlType
            End If
            Select Case mdlType
                Case Is = 1 'wheel
                    Dim objSusMdl As New susObject(name, sID, mdlType, np1, nq1, nq2, nn1, nr, nn2, scalev, angle3, pntList)
                    objSusMdl.obj3D = cloneModel(Tire)
                    addObjecttoWorldTree(sID, objSusMdl.obj3D)
                    objSusMdl.transformObj()
                    objList.Add(objSusMdl)
                Case Is = 2 ' link
                    Dim objSusMdl As New susObject(name, sID, mdlType, np1, nq1, nq2, nn1, nr, nn2, scalev, angle3, pntList)
                    objSusMdl.obj3D = cloneModel(link)
                    addObjecttoWorldTree(sID, objSusMdl.obj3D)
                    objSusMdl.transformObj()
                    objList.Add(objSusMdl)
                Case Is = 3 'ball
                    Dim objSusMdl As New susObject(name, sID, mdlType, np1, nq1, nq2, nn1, nr, nn2, scalev, angle3, pntList)
                    objSusMdl.obj3D = cloneModel(ball)
                    addObjecttoWorldTree(sID, objSusMdl.obj3D)
                    objSusMdl.transformObj()
                    objList.Add(objSusMdl)
                Case Is = 4 'strut
                    Dim objSusMdl As New susObject(name, sID, mdlType, np1, nq1, nq2, nn1, nr, nn2, scalev, angle3, pntList)
                    objSusMdl.obj3D = cloneModel(Strut)
                    addObjecttoWorldTree(sID, objSusMdl.obj3D)
                    objSusMdl.transformObj()
                    objList.Add(objSusMdl)
                Case Is = 5 'link dark
                    Dim objSusMdl As New susObject(name, sID, mdlType, np1, nq1, nq2, nn1, nr, nn2, scalev, angle3, pntList)
                    objSusMdl.obj3D = cloneModel(link2)
                    addObjecttoWorldTree(sID, objSusMdl.obj3D)
                    objSusMdl.transformObj()
                    objList.Add(objSusMdl)
                Case Is = 6 'Bushing
                    Dim objSusMdl As New susObject(name, sID, mdlType, np1, nq1, nq2, nn1, nr, nn2, scalev, angle3, pntList)
                    objSusMdl.obj3D = cloneModel(Bushing)
                    addObjecttoWorldTree(sID, objSusMdl.obj3D)
                    objSusMdl.transformObj()
                    objList.Add(objSusMdl)
                Case Is = 7
                    Dim objSusMdl As New susObject(name, sID, mdlType, np1, nq1, nq2, nn1, nr, nn2, scalev, angle3, pntList)
                    Dim v1 As Vector3D, V2 As Vector3D, V3 As Vector3D
                    If (np1 > 0) Then
                        TrianglePnts.Positions(0) = pntList(np1 - 1) / 1000.0
                    Else
                        v1 = pntList(-np1 - 1) / 1000.0
                        v1.Y = -v1.Y
                        TrianglePnts.Positions(0) = v1
                    End If

                    If (nq1 > 0) Then
                        TrianglePnts.Positions(1) = pntList(nq1 - 1) / 1000.0
                    Else
                        v1 = pntList(-nq1 - 1) / 1000.0
                        v1.Y = -v1.Y
                        TrianglePnts.Positions(1) = v1

                    End If
                    If (nq2 > 0) Then
                        TrianglePnts.Positions(2) = pntList(nq2 - 1) / 1000.0
                    Else
                        v1 = pntList(-nq2 - 1) / 1000.0
                        v1.Y = -v1.Y
                        TrianglePnts.Positions(2) = v1
                    End If

                    v1 = TrianglePnts.Positions(1) - TrianglePnts.Positions(0)
                    V2 = TrianglePnts.Positions(2) - TrianglePnts.Positions(0)
                    V3 = Vector3D.CrossProduct(v1, V2)
                    V3.Normalize()
                    TrianglePnts.Normals(0) = V3
                    TrianglePnts.Normals(1) = V3
                    TrianglePnts.Normals(2) = V3
                    objSusMdl.obj3D = cloneModel(Triangle)
                    addObjecttoWorldTree(sID, objSusMdl.obj3D)
                    objSusMdl.transformObj()
                    objList.Add(objSusMdl)

            End Select
        End If
    End Sub

    Class obj3DKookmin : Inherits Windows.Media.Media3D.ModelVisual3D


    End Class

    Public Sub ClearModel()

    End Sub

    Public Sub addListbox(ByVal name As String)
        Dim bHasitem As Boolean = False
        For Each item In ListBox1.Items
            If (item = name) Then
                bHasitem = True
            End If
        Next
        If bHasitem = False Then ListBox1.Items.Add(name)
    End Sub

    Public Function cloneModel(mdl As ModelVisual3D) As ModelVisual3D
        Dim strXaml As String
        Dim mdlClone As ModelVisual3D
        Dim xmlreader As XmlReader
        strXaml = XamlWriter.Save(mdl)
        Dim StringReader As New StringReader(strXaml)
        xmlreader = XmlReader.Create(StringReader)
        mdlClone = CType(XamlReader.Load(xmlreader), ModelVisual3D)
        Return mdlClone
    End Function

    Public Sub rotateCamera(x As Double, y As Double)
        'camctrl.
    End Sub

    Public Sub setChild(obj As ModelVisual3D, parent As ModelVisual3D, bShow As Boolean)
        If parent.Children.Contains(obj) And bShow = False Then
            parent.Children.Remove(obj)
        ElseIf parent.Children.Contains(obj) = False And bShow = True Then
            parent.Children.Add(obj)
        End If
    End Sub
    Public Sub myMouseCenterDown(pntx As Single, pnty As Single)
        pntDragStart.X = pntx
        pntDragStart.Y = pnty
        mousestate = 2
    End Sub
    Public Sub myMouseDown(pntx As Single, pnty As Single)
        pntDragStart.X = pntx
        pntDragStart.Y = pnty
        mousestate = 1
    End Sub
    Public Sub myMouseUp()
        mousestate = 0
    End Sub

    Private Sub ViewPort3D_MouseDown(sender As System.Object, e As System.Windows.Input.MouseButtonEventArgs)
        Dim pnt As New System.Windows.Point
        pnt = e.GetPosition(Nothing)
        If (e.MiddleButton = Input.MouseButtonState.Pressed) Then
            myMouseCenterDown(pnt.X, pnt.Y)
        ElseIf (e.LeftButton = Input.MouseButtonState.Pressed) Or (e.RightButton = Input.MouseButtonState.Pressed) Then
            myMouseDown(pnt.X, pnt.Y)
        End If
    End Sub


    Private Sub ViewPort3D_MouseLeftButtonUp(sender As System.Object, e As System.Windows.Input.MouseButtonEventArgs)
        myMouseUp()
    End Sub

    Public Sub myMouseMove(pntx As Single, pnty As Single)
        If mousestate = 1 Then
            Dim v As Vector3D
            v.X = -(pntx - pntDragStart.X) / 100.0
            v.Y = (pnty - pntDragStart.Y) / 100.0
            v.Z = 0
            camctrl.MoveDxDy(v)
            pntDragStart.X = pntx
            pntDragStart.Y = pnty
        ElseIf (mousestate = 2) Then
            myMouseWheel(-(pntx - pntDragStart.X) / 0.1 + (pnty - pntDragStart.Y) / 0.1)
            pntDragStart.X = pntx
            pntDragStart.Y = pnty
        End If
    End Sub


    Private Sub ViewPort3D_MouseMove(sender As System.Object, e As System.Windows.Input.MouseEventArgs)
        Dim pnt As New System.Windows.Point
        pnt = e.GetPosition(Nothing)
        myMouseMove(pnt.X, pnt.Y)
    End Sub

    Private Sub UserControl_MouseWheel(sender As System.Object, e As System.Windows.Input.MouseWheelEventArgs)
        myMouseWheel(e.Delta)
    End Sub

    Private Sub ViewPort3D_MouseWheel(sender As System.Object, e As System.Windows.Input.MouseWheelEventArgs) Handles MyBase.MouseWheel
        myMouseWheel(e.Delta)
    End Sub

    Public Sub myMouseWheel(delta As Single)
        camctrl.MoveDz(1 + delta * 0.0005)
    End Sub

    Private Sub UserControl_MouseLeftButtonDown(sender As System.Object, e As System.Windows.Input.MouseButtonEventArgs) Handles MyBase.MouseLeftButtonDown
        Dim pnt As New System.Windows.Point
        pnt = e.GetPosition(Nothing)
        myMouseDown(pnt.X, pnt.Y)
    End Sub

    Private Sub UserControl_MouseLeftButtonUp(sender As System.Object, e As System.Windows.Input.MouseButtonEventArgs) Handles MyBase.MouseLeftButtonUp
        myMouseUp()
    End Sub

    Private Sub UserControl_MouseMove(sender As System.Object, e As System.Windows.Input.MouseEventArgs) Handles MyBase.MouseMove
        Dim pnt As New System.Windows.Point
        pnt = e.GetPosition(Nothing)
        myMouseMove(pnt.X, pnt.Y)
    End Sub

    Private Sub OnViewportMouseMove(sender As System.Object, e As System.Windows.Input.MouseEventArgs)
        Dim pnt As New System.Windows.Point
        pnt = e.GetPosition(Nothing)
        myMouseMove(pnt.X, pnt.Y)
    End Sub

    Private Sub OnViewportMouseUp(sender As System.Object, e As System.Windows.Input.MouseButtonEventArgs)
        myMouseUp()
    End Sub

    Private Sub OnViewportMouseDown(sender As System.Object, e As System.Windows.Input.MouseButtonEventArgs)
        Dim pnt As New System.Windows.Point
        pnt = e.GetPosition(Nothing)
        If (e.MiddleButton = Input.MouseButtonState.Pressed) Then
            myMouseCenterDown(pnt.X, pnt.Y)
        ElseIf (e.LeftButton = Input.MouseButtonState.Pressed) Or (e.RightButton = Input.MouseButtonState.Pressed) Then
            myMouseDown(pnt.X, pnt.Y)
        End If
    End Sub

    Private Sub ListBox1_MouseLeave(sender As Object, e As System.Windows.Input.MouseEventArgs) Handles ListBox1.MouseLeave
        mousestateListBox = 0
    End Sub

    Private Sub ListBox1_MouseMove(sender As Object, e As System.Windows.Input.MouseEventArgs) Handles ListBox1.MouseMove
        If (mousestateListBox = 1) Then
            Dim pnttmp As System.Windows.Point
            Dim pnttmp2 As System.Windows.Point
            pnttmp = e.GetPosition(Nothing)
            pnttmp2 = (pnttmp - pntDragStart)
            ListBox1.Margin = New System.Windows.Thickness(ListBox1.Margin.Left + pnttmp2.X, ListBox1.Margin.Top + pnttmp2.Y, ListBox1.Margin.Right + pnttmp2.X, ListBox1.Margin.Bottom + pnttmp2.Y)
            pntDragStart = pnttmp
        End If
    End Sub

    Private Sub ListBox1_MouseRightButtonDown(sender As Object, e As System.Windows.Input.MouseButtonEventArgs) Handles ListBox1.MouseRightButtonDown
        mousestateListBox = 1
        myMouseUp()
        pntDragStart = e.GetPosition(Nothing)
    End Sub

    Private Sub ListBox1_MouseRightButtonUp(sender As Object, e As System.Windows.Input.MouseButtonEventArgs) Handles ListBox1.MouseRightButtonUp
        mousestateListBox = 0
    End Sub

    Private Sub ListBox1_SelectionChanged(sender As System.Object, e As System.Windows.Controls.SelectionChangedEventArgs) Handles ListBox1.SelectionChanged
        Dim strv As String
        strv = ListBox1.Items(ListBox1.SelectedIndex)
        For Each item As susObject In objList
            If (item.getName() = strv) Then
                SelectObject(item, testvalue)
                camctrl.setTarget(item.Vec1 / 1000)
                Exit For
            End If
        Next
    End Sub
    Public Sub SelectBushObject(ByVal name As String, ByVal nAxisIdx As Integer)
        Dim hasItem As Boolean = False
        For Each item As susObject In objList
            If (item.getName() = name) Then
                SelectObject(item, nAxisIdx)
                camctrl.setTarget(item.Vec1 / 1000)
                hasItem = True
                Exit For
            End If
        Next

        If (hasItem = False) Then SelectObject(Nothing, 0)


    End Sub
    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.Windows.RoutedEventArgs) Handles Button1.Click
        SetCamInitPos1(New Vector3D(1, 1, -1))
    End Sub

    Private Sub Button4_Click(ByVal sender As System.Object, ByVal e As System.Windows.RoutedEventArgs) Handles Button4.Click
        SetCamInitPos1(New Vector3D(0, 0, -1))
    End Sub

    Private Sub Button5_Click(sender As System.Object, e As System.Windows.RoutedEventArgs) Handles Button5.Click
        SetCamInitPos1(New Vector3D(1, 0, 0))
    End Sub

    Private Sub RadioButton1_Checked(sender As System.Object, e As System.Windows.RoutedEventArgs) Handles RadioButton1.Checked
        bCamHalf = True
        Dim tget As Vector3D
        For Each item As Vector3D In pntList
            tget = tget + item
        Next
        tget = tget / pntList.Count
        tget.Y = 0
        If (camctrl Is Nothing = False) Then camctrl.setTarget(tget / 1000)
        'SetCamInitPos1(New Vector3D(1, 1, -1))
    End Sub

    Private Sub RadioButton2_Checked(sender As System.Object, e As System.Windows.RoutedEventArgs) Handles RadioButton2.Checked
        bCamHalf = False
        Dim tget As Vector3D
        For Each item As Vector3D In pntList
            tget = tget + item
        Next
        tget = tget / pntList.Count
        If (camctrl Is Nothing = False) Then camctrl.setTarget(tget / 1000)
        ' SetCamInitPos1(New Vector3D(1, 1, -1))
    End Sub

    Private Sub ViewControl3D_SizeChanged(sender As Object, e As System.Windows.SizeChangedEventArgs) Handles Me.SizeChanged

        grid3D.Height = e.NewSize.Height
        grid3D.Width = e.NewSize.Width
        Border1.Width = grid3D.Width
        Border1.Height = grid3D.Height

    End Sub

    Private Sub UserControl_StylusDown(sender As System.Object, e As System.Windows.Input.StylusDownEventArgs) Handles MyBase.StylusDown

    End Sub

End Class




Public Class susObject
    Dim name As String
    Dim sID As String
    Public nType As Integer
    Public Vec1 As Vector3D
    Public Vec2 As Vector3D
    Public Vec3 As Vector3D
    Public sVec As Vector3D
    Public VecRv As Vector3D
    Public euangle As Vector3D
    Dim nPv As Integer
    Dim nQ1 As Integer
    Dim nQ2 As Integer
    Dim nQ3 As Integer
    Dim nRv As Integer
    Dim nn1v As Integer
    Dim nn2v As Integer
    Dim pntList As List(Of Vector3D)
    Public obj3D As ModelVisual3D


    'Public Sub New(nameInput As String, nTypeInput As Integer, vec1in As Integer, Vec2in As Integer, Vec3in As Integer, Vec4in As Vector3D, pntL As List(Of Vector3D))
    Public Sub New(nameInput As String, sIDin As String, nTypeInput As Integer, np1in As Integer, nq1in As Integer, nq2in As Integer, nn1in As Integer, nrin As Integer, nn2in As Integer, scalev As Vector3D, anglev As Vector3D, pntL As List(Of Vector3D))
        nType = nTypeInput
        If (np1in = 0) Then
            Vec1.X = 0 : Vec1.Y = 0 : Vec1.Z = 0
            sVec = scalev
            euangle = anglev
            Vec3 = sVec
        ElseIf (pntL.Count > 0) Then
            obj3D = New ModelVisual3D
            name = nameInput
            sID = sIDin
            pntList = pntL
            nType = nTypeInput
            sVec = scalev
            nPv = np1in
            nQ1 = nq1in
            nQ2 = nq2in
            nRv = nrin
            nn1v = nn1in
            nn2v = nn2in
            euangle = anglev
            If (nPv > 0) Then
                Vec1 = pntList(nPv - 1)
            ElseIf (nPv < 0) Then
                Vec1 = pntList(-nPv - 1)
                Vec1.Z = -Vec1.Z
            Else
                Vec1.X = 0 : Vec1.Y = 0 : Vec1.Z = 0
            End If
            If (nQ1 > 0) Then
                Vec2 = pntList(nQ1 - 1)
            ElseIf (nQ1 < 0) Then
                Vec2 = pntList(-nQ1 - 1)
                Vec2.Z = -Vec2.Z
            Else
                Vec2.X = 0 : Vec2.Y = 0 : Vec2.Z = 0
            End If
            If (nQ2 > 0) Then
                Vec3 = pntList(nQ2 - 1)
            ElseIf (nQ2 < 0) Then
                Vec3 = pntList(-nQ2 - 1)
                Vec3.Z = -Vec3.Z
            Else
                Vec3.X = 0 : Vec3.Y = 0 : Vec3.Z = 0
            End If

            If (nRv > 0) Then
                VecRv = pntList(nRv - 1)
            ElseIf (nRv < 0) Then
                VecRv = pntList(-nRv - 1)
                VecRv.Z = -Vec3.Z
            Else
                VecRv.X = 0 : VecRv.Y = 0 : VecRv.Z = 0
            End If
        End If
    End Sub

    Function getName() As String
        Return Me.name
    End Function

    Function getID() As String
        Return Me.sID
    End Function

    Public Sub transformObj(pos As Vector3D)
        Vec1 = pos
        transformObj()
    End Sub



    Public Sub transformObj()
        If (pntList Is Nothing = False) Then
            If (nPv > 0) Then
                Vec1 = pntList(nPv - 1)
            ElseIf (nPv < 0) Then
                Vec1 = pntList(-nPv - 1)
                Vec1.Y = -Vec1.Y
            Else
                Vec1.X = 0 : Vec1.Y = 0 : Vec1.Z = 0
            End If
            If (nQ1 > 0) Then
                Vec2 = pntList(nQ1 - 1)
            ElseIf (nQ1 < 0) Then
                Vec2 = pntList(-nQ1 - 1)
                Vec2.Y = -Vec2.Y
            Else
                Vec2.X = 0 : Vec2.Y = 0 : Vec2.Z = 0
            End If
            If (nQ2 > 0) Then
                Vec3 = pntList(nQ2 - 1)
            ElseIf (nQ2 < 0) Then
                Vec3 = pntList(-nQ2 - 1)
                Vec3.Y = -Vec3.Y
            Else
                Vec3.X = 0 : Vec3.Y = 0 : Vec3.Z = 0
            End If

            If (nRv > 0) Then
                VecRv = pntList(nRv - 1)
            ElseIf (nRv < 0) Then
                VecRv = pntList(-nRv - 1)
                VecRv.Z = -Vec3.Z
            Else
                VecRv.X = 0 : VecRv.Y = 0 : VecRv.Z = 0
            End If
        End If

        If (nType = 1) Then             ' wheel
            Dim tformGroup As New Transform3DGroup
            Dim matrot As Matrix3D
            matrot = getRotMat()
            Dim rot As New MatrixTransform3D(matrot)

            tformGroup.Children.Add(New ScaleTransform3D(sVec.X, sVec.Y, sVec.Z))
            tformGroup.Children.Add(rot)

            tformGroup.Children.Add(New TranslateTransform3D(Vec1.X / 1000.0, Vec1.Y / 1000.0, Vec1.Z / 1000.0))
            obj3D.Transform = tformGroup

            'Dim tformGroup As New Transform3DGroup
            'Dim vtx As Vector3D, vty As Vector3D, vtz As Vector3D
            'Dim matrot As Matrix3D
            'vtx = Vec2 - Vec1
            'vtx.Normalize()
            'vty.X = 1 : vty.Y = 0 : vty.Z = 0
            'vtz = Vector3D.CrossProduct(vtx, vty)
            'vtz.Normalize()
            'vty = Vector3D.CrossProduct(vtz, vtx)
            'vty.Normalize()
            'matrot.M11 = vtx.X : matrot.M12 = vtx.Y : matrot.M13 = vtx.Z
            'matrot.M21 = vty.X : matrot.M22 = vty.Y : matrot.M23 = vty.Z
            'matrot.M31 = vtz.X : matrot.M32 = vtz.Y : matrot.M33 = vtz.Z
            'Dim rot As New MatrixTransform3D(matrot)

            'tformGroup.Children.Add(New ScaleTransform3D(sVec.X, sVec.Y, sVec.Z))
            'tformGroup.Children.Add(rot)
            'tformGroup.Children.Add(New TranslateTransform3D(Vec1.X / 1000.0, Vec1.Y / 1000.0, Vec1.Z / 1000.0))
            'obj3D.Transform = tformGroup
        ElseIf (nType = 2) Then     ' Link
            Dim tformGroup As New Transform3DGroup
            Dim vt1 As Vector3D

            Dim vtx As Vector3D, vty As Vector3D, vtz As Vector3D
            Dim matrot As Matrix3D
            vt1 = Vec2 - Vec1
            vtz = vt1
            vtz.Normalize()
            vty.X = 0 : vty.Y = 1 : vty.Z = 0
            vtx = Vector3D.CrossProduct(vty, vtz)
            vtx.Normalize()
            vty = Vector3D.CrossProduct(vtz, vtx)
            vty.Normalize()
            matrot.M11 = vtx.X : matrot.M12 = vtx.Y : matrot.M13 = vtx.Z
            matrot.M21 = vty.X : matrot.M22 = vty.Y : matrot.M23 = vty.Z
            matrot.M31 = vtz.X : matrot.M32 = vtz.Y : matrot.M33 = vtz.Z
            Dim rot As New MatrixTransform3D(matrot)

            tformGroup.Children.Add(New ScaleTransform3D(sVec.X, sVec.Y, vt1.Length))
            tformGroup.Children.Add(rot)

            tformGroup.Children.Add(New TranslateTransform3D(Vec1.X / 1000.0, Vec1.Y / 1000.0, Vec1.Z / 1000.0))
            obj3D.Transform = tformGroup
        ElseIf (nType = 3) Then     'ball
            Dim tformGroup As New Transform3DGroup
            tformGroup.Children.Add(New ScaleTransform3D(sVec.X, sVec.Y, sVec.Z))
            tformGroup.Children.Add(New TranslateTransform3D(Vec1.X / 1000.0, Vec1.Y / 1000.0, Vec1.Z / 1000.0))
            obj3D.Transform = tformGroup
        ElseIf (nType = 4) Then     'piston
            Dim tformGroup As New Transform3DGroup
            Dim vt1 As Vector3D

            Dim vtx As Vector3D, vty As Vector3D, vtz As Vector3D
            Dim matrot As Matrix3D
            vt1 = Vec2 - Vec1
            vtz = vt1
            vtz.Normalize()
            vty.X = 0 : vty.Y = 1 : vty.Z = 0
            vtx = Vector3D.CrossProduct(vty, vtz)
            vtx.Normalize()
            vty = Vector3D.CrossProduct(vtz, vtx)
            vty.Normalize()
            matrot.M11 = vtx.X : matrot.M12 = vtx.Y : matrot.M13 = vtx.Z
            matrot.M21 = vty.X : matrot.M22 = vty.Y : matrot.M23 = vty.Z
            matrot.M31 = vtz.X : matrot.M32 = vtz.Y : matrot.M33 = vtz.Z
            Dim rot As New MatrixTransform3D(matrot)

            tformGroup.Children.Add(New ScaleTransform3D(sVec.X, sVec.Y, vt1.Length))
            tformGroup.Children.Add(rot)

            tformGroup.Children.Add(New TranslateTransform3D(Vec1.X / 1000.0, Vec1.Y / 1000.0, Vec1.Z / 1000.0))
            obj3D.Transform = tformGroup
        ElseIf (nType = 5) Then         'link2
            Dim tformGroup As New Transform3DGroup
            Dim vt1 As Vector3D

            Dim vtx As Vector3D, vty As Vector3D, vtz As Vector3D
            Dim matrot As Matrix3D
            vt1 = Vec2 - Vec1
            vtz = vt1
            vtz.Normalize()
            vty.X = 0 : vty.Y = 1 : vty.Z = 0
            vtx = Vector3D.CrossProduct(vty, vtz)
            vtx.Normalize()
            vty = Vector3D.CrossProduct(vtz, vtx)
            vty.Normalize()
            matrot.M11 = vtx.X : matrot.M12 = vtx.Y : matrot.M13 = vtx.Z
            matrot.M21 = vty.X : matrot.M22 = vty.Y : matrot.M23 = vty.Z
            matrot.M31 = vtz.X : matrot.M32 = vtz.Y : matrot.M33 = vtz.Z
            Dim rot As New MatrixTransform3D(matrot)

            tformGroup.Children.Add(New ScaleTransform3D(sVec.X, sVec.Y, vt1.Length))
            tformGroup.Children.Add(rot)

            tformGroup.Children.Add(New TranslateTransform3D(Vec1.X / 1000.0, Vec1.Y / 1000.0, Vec1.Z / 1000.0))
            obj3D.Transform = tformGroup
        ElseIf (nType = 6) Then     ' Bushing
            Dim tformGroup As New Transform3DGroup
            Dim matrot As Matrix3D
            matrot = getRotMat()
            Dim rot As New MatrixTransform3D(matrot)
            Dim rot2 As New RotateTransform3D(New QuaternionRotation3D(New Quaternion(New Vector3D(0.0, 0.0, 1.0), euangle.Z) * New Quaternion(New Vector3D(0.0, 1.0, 0.0), euangle.Y) * New Quaternion(New Vector3D(1.0, 0.0, 0.0), euangle.X)))

            tformGroup.Children.Add(New ScaleTransform3D(sVec.X, sVec.Y, sVec.Z))
            tformGroup.Children.Add(rot)
            tformGroup.Children.Add(rot2)

            tformGroup.Children.Add(New TranslateTransform3D(Vec1.X / 1000.0, Vec1.Y / 1000.0, Vec1.Z / 1000.0))
            obj3D.Transform = tformGroup
        ElseIf (nType = 7) Then
            'triangle()
        End If
    End Sub

    Function getRotMat() As Matrix3D

        Dim vtx As Vector3D, vty As Vector3D, vtz As Vector3D
        Dim vt1 As Vector3D, vt2 As Vector3D
        Dim nn1L As Integer, nn2L As Integer
        Dim matrot As Matrix3D
        nn1L = nn1v
        nn2L = nn2v
        If (nn1v < 0) Then nn1L = -nn1L
        If (nn2v < 0) Then nn2L = -nn2L

        If (nQ2 = 0) Then
            vt1 = Vec2 - Vec1
        Else
            vt1 = Vec3 - Vec2
        End If
        If (nn2v < 0) Then vt1 = -vt1
        vt1.Normalize()

        If (nRv = 0) Then
            If (nn2L = 1) Then
                vt2.X = 1 : vt2.Y = 0 : vt2.Z = 0
            ElseIf (nn2L = 2) Then
                vt2.X = 1 : vt2.Y = 0 : vt2.Z = 0
            ElseIf (nn2L = 3) Then
                vt2.X = 1 : vt2.Y = 0 : vt2.Z = 0
            End If
        Else
            vt2 = VecRv - Vec1
        End If
        If (nn2v < 0) Then vt2 = -vt2

        If (nn1L = 1 And nn2L = 2) Then
            vtx = vt1
            vty = vt2
            vtz = Vector3D.CrossProduct(vtx, vty)
            vtz.Normalize()
            vty = Vector3D.CrossProduct(vtz, vtx)
            vty.Normalize()
        ElseIf (nn1L = 1 And nn2L = 3) Then
            vtx = vt1
            vtz = vt2
            vty = Vector3D.CrossProduct(vtz, vtx)
            vty.Normalize()
            vtz = Vector3D.CrossProduct(vtx, vty)
            vtz.Normalize()
        ElseIf (nn1L = 2 And nn2L = 1) Then
            vty = vt1
            vtx = vt2
            vtz = Vector3D.CrossProduct(vtx, vty)
            vtz.Normalize()
            vtx = Vector3D.CrossProduct(vty, vtz)
            vtx.Normalize()
        ElseIf (nn1L = 2 And nn2L = 3) Then
            vty = vt1
            vtz = vt2
            vtx = Vector3D.CrossProduct(vty, vtz)
            vtx.Normalize()
            vtz = Vector3D.CrossProduct(vtx, vty)
            vtz.Normalize()
        ElseIf (nn1L = 3 And nn2L = 1) Then
            vtz = vt1
            vtx = vt2
            vty = Vector3D.CrossProduct(vtz, vtx)
            vty.Normalize()
            vtx = Vector3D.CrossProduct(vty, vtz)
            vtx.Normalize()
        ElseIf (nn1L = 3 And nn2L = 2) Then
            vtz = vt1
            vty = vt2
            vtx = Vector3D.CrossProduct(vty, vtz)
            vtx.Normalize()
            vty = Vector3D.CrossProduct(vtz, vtx)
            vty.Normalize()
        End If
        matrot.M11 = vtx.X : matrot.M12 = vtx.Y : matrot.M13 = vtx.Z
        matrot.M21 = vty.X : matrot.M22 = vty.Y : matrot.M23 = vty.Z
        matrot.M31 = vtz.X : matrot.M32 = vtz.Y : matrot.M33 = vtz.Z
        Return matrot
    End Function
End Class







Public Class cameraControl
    Dim campos As Vector3D
    Dim target As Vector3D
    Dim posInit As Vector3D
    Dim TargetInit As Vector3D
    Dim camObj As PerspectiveCamera


    Sub cameraControl()
        camObj = Nothing
    End Sub
    Sub setTarget(tpnt As Vector3D)
        Dim vec1 As Vector3D
        target = tpnt
        If (camObj Is Nothing = False) Then
            vec1 = target - camObj.Position
            vec1.Normalize()
            camObj.LookDirection = vec1
        End If
    End Sub

    Function getMat(direcv As Vector3D, upv As Vector3D) As Matrix3D
        Dim MatOut As New Matrix3D
        Dim xv As Vector3D, yv As Vector3D, zv As Vector3D
        zv = -direcv
        zv.Normalize()
        yv = upv
        xv = Vector3D.CrossProduct(yv, zv)
        xv.Normalize()
        yv = Vector3D.CrossProduct(zv, xv)
        yv.Normalize()
        MatOut.M11 = xv.X : MatOut.M12 = yv.X : MatOut.M13 = zv.X
        MatOut.M21 = xv.Y : MatOut.M22 = yv.Y : MatOut.M23 = zv.Y
        MatOut.M31 = xv.Z : MatOut.M32 = yv.Z : MatOut.M33 = zv.Z
        Return MatOut
    End Function

    Function transformRot(mat As Matrix3D, vec As Vector3D) As Vector3D
        Dim vecOut As New Vector3D
        vecOut.X = mat.M11 * vec.X + mat.M12 * vec.Y + mat.M13 * vec.Z
        vecOut.Y = mat.M21 * vec.X + mat.M22 * vec.Y + mat.M23 * vec.Z
        vecOut.Z = mat.M31 * vec.X + mat.M32 * vec.Y + mat.M33 * vec.Z
        Return vecOut
    End Function

    Sub MoveDxDy(vecLocal As Vector3D)
        Dim vec1 As Vector3D
        Dim vec2 As Vector3D
        Dim vec3 As Vector3D
        Dim vec4 As Vector3D

        Dim mattmp As Matrix3D
        vec1 = target - camObj.Position
        mattmp = getMat(camObj.LookDirection, camObj.UpDirection)
        camObj.UpDirection = New Vector3D(mattmp.M12, mattmp.M22, mattmp.M32)

        vec2 = transformRot(mattmp, vecLocal)
        vec3 = target - (vec2 + camObj.Position)
        vec3.Normalize()
        vec4 = target - vec3 * vec1.Length
        camObj.Position = vec4
        Debug.Print(vec2.X & "," & vec2.Y & "," & vec2.Z & "#     " &
                    vec4.X & "," & vec4.Y & "," & vec4.Z & "#     " &
                    camObj.Position.X & "," & camObj.Position.Y & "#" & vec1.Length)
        setTarget(target)
    End Sub

    Sub MoveDz(dv As Double)
        Dim tmpv As Vector3D
        tmpv = target - camObj.Position
        camObj.Position = target - tmpv * dv
    End Sub


    Sub setCamera(ByRef cam As PerspectiveCamera)
        camObj = cam
    End Sub

    Sub SetInitPos(pInit As Vector3D, tInit As Vector3D)
        campos = pInit
        target = tInit
        Dim tmpv As Vector3D
        tmpv = tInit - pInit
        tmpv.Normalize()

        If (camObj Is Nothing = False) Then
            camObj.Position = pInit
            camObj.UpDirection = New Vector3D(0, 0, 1)
            If (Math.Abs(Vector3D.DotProduct(camObj.UpDirection, tmpv)) > 0.99) Then
                camObj.UpDirection = New Vector3D(1, 0, 0)
            End If

            camObj.LookDirection = tmpv

        End If
    End Sub

End Class

